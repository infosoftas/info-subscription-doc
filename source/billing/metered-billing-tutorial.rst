.. _metered-billing-tutorial:

*******************************************
Building a Simplified Metered Billing Model
*******************************************

This tutorial walks through a simplified pattern for **usage-based (metered) billing** on top of a regular |projectName| subscription. It is aimed at integrators who already have subscribers and subscriptions in place and now want to bill for consumption — API calls, transactions, printed pages, or any other unit that scales with usage — instead of, or in addition to, a fixed subscription fee.

.. note::
    |projectName| does not ingest raw meter readings itself. Instead, **you** are responsible for reading your own meters, converting the raw usage into whole payable units, and injecting the resulting cost as a charge on the subscriber's :term:`billing account <Billing Account>`. This tutorial describes that workflow end to end.

.. tip::
    This pattern is essentially an application of the :ref:`hybrid billing model <hybrid-billing>`: the base subscription fee is billed in-advance as usual, while metered usage from the *previous* period is billed in-arrears, alongside it, on the next invoice.

Prerequisites
=============

Before you start injecting usage charges, make sure the following building blocks already exist:

- A **subscriber** and an active **subscription**, created through the normal :ref:`order flow <subscription-orders>`.
- A **billing account** for the subscriber (created automatically with the subscription in the common case).
- A **Product** in |projectName| representing the billable unit (for example "API Call Package" or "Overage Unit"), with a price configured for the currencies you bill in — unless you intend to price usage entirely outside of |projectName| (see :ref:`Determining the Price <metered-billing-pricing>` below).

The Workflow at a Glance
========================

At a high level, a metered billing integration repeats the following cycle, typically once per billing period, but the read frequency and the charge frequency don't have to match (see :ref:`Reading Your Meters <metered-billing-reading>`):

.. mermaid::

    flowchart LR
        A[1. Read meter/usage source] --> B[2. Convert to whole payable units]
        B --> C[3. Determine price per unit]
        C --> D[4. Calculate total amount]
        D --> E["5. POST charge (type=Purchase) to billing account"]
        E --> F[6. Charge is billed in-arrears on next invoice]

.. _metered-billing-reading:

Step 1: Reading Your Meters
============================

"Meter" here is deliberately generic — it can be a counter in your own system (API gateway request counts, message queue throughput, storage usage snapshots) or a reading pulled from a third-party device or service. |projectName| has no opinion on how you obtain this number; it only cares about the final payable amount.

A few things to plan for when designing the read step:

- **Cadence**: You can read as often as you like (e.g. hourly aggregation) but you don't have to charge that often. It's common to aggregate reads and inject a single charge per subscriber per billing period, timed to land before the next invoice is generated.
- **Idempotency**: Since a charge is a simple monetary entry, re-reading the same usage window twice and posting it twice will double-bill the subscriber. Keep track of which usage windows have already been converted into a charge (for example, by recording the ``endTime`` you last billed up to).
- **Alignment with the billing cycle**: To keep the "in-arrears usage alongside in-advance subscription fee" story intuitive for subscribers, align your read/charge cadence with the subscriber's :ref:`billing cycle <billing-cycle>` so usage from period N appears on the invoice for period N+1, not scattered across unrelated invoices.

Step 2: Converting to Payable Units
====================================

Raw meter output is rarely in a unit you can bill directly — a subscriber does not want an invoice line for "14,382.5 kB transferred" or "6.7 minutes of call time". |projectName| only expects a final **amount**, so converting the raw, "weird" unit into a whole, payable unit is entirely your responsibility.

A typical conversion involves:

1. **Bucket** the raw usage into your chosen billable unit (for example, 1 payable unit = every 1,000 API calls).
2. **Round or truncate** according to your business rules — do you round up any partial bucket (typical for prepaid-style overage billing), round to the nearest unit, or carry the remainder forward to the next period?
3. **Carry forward remainders** if you don't round up, so usage isn't silently lost between periods.

Example — API call metering:

.. code-block:: text

    Raw usage this period:      42,700 API calls
    Billable unit:               1,000 API calls
    Rounding rule:                round up (any partial bucket is billed in full)

    42,700 / 1,000 = 42.7  ->  43 billable units

This conversion step is where most of the "business logic" of your metered billing model lives, and it's worth unit-testing thoroughly and independently from the rest of the flow described here.

.. _metered-billing-pricing:

Step 3: Determining the Price
==============================

Once you know how many billable units to charge for, you need a price per unit. There are two common approaches:

**Simple: look up the price on the Product in |projectName|**

If a flat, published price per unit is enough for your model, create a :term:`Product` representing the billable unit and fetch its price:

.. code-block:: http
    :name: Get Product Price

    GET https://api.info-subscription.com/product/{id}/price?Currency=USD HTTP/1.1
    Host: api.info-subscription.com
    S4-TenantId: 3fce3f93-97a7-4045-952d-f8af685a47cb
    Authorization: ******

This returns one or more ``ProductPriceView`` entries, each with a ``price`` and ``currency``. Multiply the returned price by the number of billable units from Step 2 to get the total charge amount.

**Advanced: maintain your own price list**

If you need per-subscriber pricing, negotiated contract rates, tiered/volume pricing, or any other mechanism that doesn't fit a single published price per Product, maintain a separate price list in your own system instead. |projectName| doesn't need to know *how* the amount was calculated — only the final amount you want billed. This is also the right approach if the billable "product" is more of an internal accounting concept than something you want to expose through the |projectName| product catalog.

Either way, the outcome of this step is the same: a total **amount**, in a given **currency**, that should be added to the subscriber's billing account.

Step 4: Injecting the Charge
=============================

With a calculated amount in hand, add it to the subscriber's billing account as a charge with ``transactionType`` set to ``Purchase``:

.. code-block:: http
    :name: Add a Purchase Charge to a Billing Account

    POST https://api.info-subscription.com/billing/accounts/{id}/charges HTTP/1.1
    Host: api.info-subscription.com
    S4-TenantId: 3fce3f93-97a7-4045-952d-f8af685a47cb
    Authorization: ******
    Content-Type: application/json

    {
        "amount": 21.50,
        "accountingTime": "2025-01-31T23:59:59Z",
        "transactionType": "Purchase",
        "description": "API usage - January 2025 (43 x 1,000 calls @ 0.50 USD)",
        "startTime": "2025-01-01T00:00:00Z",
        "endTime": "2025-01-31T23:59:59Z"
    }

A few notes on the fields that matter most for a metered billing use case:

- ``amount`` is the total you calculated in Step 3 — |projectName| does not recalculate or validate it against a Product price.
- ``startTime``/``endTime`` describe the usage period the charge covers, which is useful both for your own auditing and for subscriber-facing invoice detail.
- ``description`` ends up on the invoice line, so make it meaningful to the subscriber (avoid raw internal unit counts if they won't mean anything to them).
- The charge is **not** billed immediately. It sits on the billing account until the next :ref:`payment demand <billing-cycle>` is generated, at which point it is billed in-arrears alongside the in-advance subscription fee.

.. tip::
    If you need the usage charge billed **immediately** — for example a one-off purchase that shouldn't wait for the next renewal — use an :ref:`Account Payment Demand <standalone-paymentdemands>` instead, which creates an invoice right away rather than deferring to the next cycle.

Step 5: How It Surfaces on the Invoice
========================================

When the subscriber's next payment demand is created, |projectName| includes any outstanding charges from the billing account alongside the regular subscription fee — this is the :ref:`hybrid billing model <hybrid-billing>` in action. The result is a single invoice containing:

- The subscription fee for the **upcoming** period (in-advance)
- The metered usage charge(s) for the **previous** period (in-arrears)

See :ref:`Payment Matching, Settlement, and Billing Account Reconciliation <payment-matching-settlement>` for what happens if a subscriber only partially pays such an invoice.

Edge Cases and Gotchas
=======================

- **Cancellations with outstanding usage** — if a subscription is cancelled before its usage has been billed, the charge remains on the billing account and is picked up by the final settlement invoice. Read :ref:`Proration Policies <proration-policies>` for how this interacts with prorated subscription fees.
- **Corrections** — if you overcharge (for example due to a metering bug), you can offset it with an allowance rather than a negative charge; see :ref:`Billing Account Role <billing-account-role>`.
- **Multi-currency subscribers** — make sure the Product price (or your own price list) is looked up in the same currency as the subscriber's billing account.
- **Duplicate reads** — see the idempotency note in :ref:`Step 1 <metered-billing-reading>`; this is the most common source of double-billed usage in metered billing integrations.

See Also
========

- :ref:`Hybrid Billing: In-Advance + In-Arrears <hybrid-billing>` — the underlying billing model this tutorial builds on
- :ref:`Billing Cycle In Depth <billing-cycle>` — how and when payment demands and invoices are generated
- :ref:`Transaction (Non-Recurring) Invoices <standalone-paymentdemands>` — for billing usage immediately instead of deferring to the next cycle
- :ref:`Payment Matching, Settlement, and Billing Account Reconciliation <payment-matching-settlement>` — how charges are settled once the invoice is paid
