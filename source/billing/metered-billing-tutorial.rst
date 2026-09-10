.. _metered-billing-tutorial:

***********************************************
Building Your Own Metered Billing Solution
***********************************************

|projectName| doesn't ship a dedicated "metering" feature — there's no built-in concept of reading a meter, tracking consumption, or converting usage into money. What it does provide are a small set of flexible billing primitives — Products, prices, and billing account charges — that you can combine to build usage-based (metered) billing yourself, on top of a regular subscription.

This tutorial is a worked example of that: a case study in extending |projectName| with a capability it doesn't natively support, using the pieces it already gives you. It's aimed at integrators who already have subscribers and subscriptions in place and now want to bill for consumption — API calls, transactions, printed pages, or any other unit that scales with usage — instead of, or in addition to, a fixed subscription fee.

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

.. _metered-billing-conversion:

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

This returns an array of ``ProductPriceView`` entries:

.. code-block:: json
    :name: Get Product Price - Response

    [
        {
            "id": "6b1b6f2a-df44-4b8e-9c8f-1c1d9a8e2b40",
            "productId": "4e9f6b1a-2c3d-4f5e-8a7b-9c0d1e2f3a4b",
            "billingFrequencyId": 1,
            "numberOfEditions": null,
            "priceTypeId": "0f1e2d3c-4b5a-6978-8f9e-0d1c2b3a4958",
            "price": 0.50,
            "currency": "USD",
            "startDate": "2025-01-01T00:00:00Z",
            "expiryDate": null
        }
    ]

Multiply the returned ``price`` by the number of billable units from Step 2 to get the total charge amount — 43 units x 0.50 USD = 21.50 USD in this example.

**Advanced: maintain your own price list**

If you need per-subscriber pricing, negotiated contract rates, tiered/volume pricing, or any other mechanism that doesn't fit a single published price per Product, maintain a separate price list in your own system instead. |projectName| doesn't need to know *how* the amount was calculated — only the final amount you want billed. This is also the right approach if the billable "product" is more of an internal accounting concept than something you want to expose through the |projectName| product catalog.

.. important::
    Even when the price itself comes from an external price list, you still need the ``id`` of a :term:`Product` in |projectName|. It has no bearing on the calculated price, but it's a required field on a ``Purchase`` charge, and it's what ties the charge to a specific product for accounting, reporting, and subscriber-facing invoice detail — see :ref:`Step 4 <metered-billing-charging>` below.

Either way, the outcome of this step is the same: a total **amount**, in a given **currency**, tied to a **Product**, that should be added to the subscriber's billing account.

Step 4: Injecting the Charge
=============================

.. _metered-billing-charging:

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
        "description": "API usage - January 2025",
        "startTime": "2025-01-01T00:00:00Z",
        "endTime": "2025-01-31T23:59:59Z",
        "taxDetails": [
            {
                "productId": "4e9f6b1a-2c3d-4f5e-8a7b-9c0d1e2f3a4b",
                "description": "API usage - January 2025 (43 x 1,000 calls @ 0.50 USD)",
                "quantity": 43,
                "taxableAmount": 0.50,
                "taxPercent": 0,
                "amount": 0.50
            }
        ]
    }

A few notes on the fields that matter most for a metered billing use case:

- The top-level ``amount`` is the **total** amount for the entire charge (21.50 USD in this example) — it must equal ``taxDetails[].amount`` (or ``taxDetails[].taxableAmount`` if tax applies) **multiplied by** ``taxDetails[].quantity``, summed across all tax detail entries. Unlike the top-level field, ``taxDetails[].amount``/``taxDetails[].taxableAmount`` are **per-unit** amounts, not totals — get this backwards and the charge will be billed for the wrong amount.
- ``taxDetails`` is where the actual billed **Product** is referenced, via ``productId`` on each entry — not on the charge itself. For a ``Purchase`` charge, ``productId`` is **required**: omitting it fails validation, since it's what ties the charge to a specific product for accounting, reporting, and itemized invoice detail.
- ``taxDetails[].quantity`` is a good place to record the number of billable units from Step 2 (43, in this example), separate from the human-readable ``description``.
- ``taxDetails[].description`` is what typically ends up on the invoice line itself; the top-level ``description`` is a fallback if no tax details are provided.
- ``startTime``/``endTime`` describe the usage period the charge covers, which is useful both for your own auditing and for subscriber-facing invoice detail.
- The charge is **not** billed immediately. It sits on the billing account until the next :ref:`payment demand <billing-cycle>` is generated, at which point it is billed in-arrears alongside the in-advance subscription fee.

The request returns ``202 Accepted`` with no body — the charge is queued onto the billing account rather than returned as a finished resource.

.. tip::
    If you need the usage charge billed **immediately** — for example a one-off purchase that shouldn't wait for the next renewal — use an :ref:`Account Payment Demand <standalone-paymentdemands>` instead, which creates an invoice right away rather than deferring to the next cycle.

Step 5: How It Surfaces on the Invoice
========================================

When the subscriber's next payment demand is created, |projectName| includes any outstanding charges from the billing account alongside the regular subscription fee — this is the :ref:`hybrid billing model <hybrid-billing>` in action. Concretely:

1. Each outstanding charge on the billing account is attached to the new payment demand as an entry in its ``charges`` collection, alongside the ``details`` generated for the subscription fee itself.
2. Each of these demand charges carries forward the ``taxDetails`` (and therefore the ``productId``) you supplied when injecting the charge in Step 4.
3. When the invoice is generated from the demand, each **Purchase** charge becomes its **own invoice line** — one line per charge entry, not one combined lump sum. This per-charge splitting is specific to the ``Purchase`` charge type; other charge types are bundled together onto a single invoice line today. It's precisely this behavior that makes ``Purchase`` charges well-suited for metered billing, since it lets several usage charges accumulated over a period (for example, usage injected weekly instead of monthly) show up as separate, itemized lines rather than one merged total.
4. The ``productId`` on each charge's tax details is what lets the resulting invoice line reference the correct Product for tax, reporting, and subscriber-facing description purposes, in the same way a regular subscription fee line does.

The result is a single invoice containing:

- The subscription fee for the **upcoming** period (in-advance)
- One invoice line per metered usage charge for the **previous** period (in-arrears)

See :ref:`Payment Matching, Settlement, and Billing Account Reconciliation <payment-matching-settlement>` for what happens if a subscriber only partially pays such an invoice.

Real-World Example: How INFO-Subscription Bills Itself
=========================================================

This pattern isn't just theoretical — it's how Infosoft bills our own tenants for their |projectName| services. Several independent consumption sources feed into the same billing account, each following the same steps described above:

.. list-table::
   :header-rows: 1
   :widths: 25 35 40

   * - Consumption source
     - What is "read" (Step 1)
     - How it's converted and charged (Steps 2-4)
   * - Payment service providers
     - Transactions processed on the tenant's behalf (card payments, direct debits, mobile payments, etc.)
     - Per-transaction or per-volume fees are converted into a payable amount and injected as a charge tied to the relevant PSP fee Product
   * - Document/invoicing partners
     - Documents produced and distributed (paper invoices printed and mailed, eInvoices, EHF/Peppol documents, and similar)
     - Per-document fees are aggregated per tenant and charged against a Product representing that distribution channel
   * - SMS/messaging providers
     - Number of SMS messages delivered (for example, payment reminders or one-time codes)
     - Aggregated per billing period and charged against an SMS Product
   * - INFO-Subscription itself
     - Platform usage metrics, where the tenant's contract specifies usage-based pricing (for example, API call volume or number of active subscribers)
     - Converted the same way any other tenant would convert their own metered usage, and charged against the relevant internal Product

Each of these sources is read on its own schedule, converted into whole payable units the same way described in :ref:`Step 2 <metered-billing-conversion>`, priced against a Product the same way described in :ref:`Step 3 <metered-billing-pricing>`, and injected as a ``Purchase`` charge the same way described in :ref:`Step 4 <metered-billing-charging>`. All of it lands on a single billing account in Infosoft's own internal |projectName| tenant, which is what we then use to bill our tenants.

In other words: if you follow this tutorial, you're building the same kind of integration we rely on to invoice our own customers.

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
