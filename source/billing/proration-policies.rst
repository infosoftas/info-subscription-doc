.. _proration-policies:

*************************************
Proration Policies for Cancellations
*************************************

|projectName| supports configurable proration policies for subscription cancellations through the **Dunning Process** configuration. These policies determine how subscribers are charged or credited when a subscription is cancelled during an active billing period.

This document explains the proration policy options, their effects, and provides examples with calculations and visual timelines.

.. note::
    Proration policies are configured via the **CancellationProration** property in the Dunning Process, which references a **ProrationPolicy** entity. 
    See the `ProrationPolicy API documentation <https://api.info-subscription.com/swagger/index.html#/ProrationPolicy/CreateProrationPolicy>`_ for technical details.

Understanding Cancellation Proration
====================================

When a subscription is cancelled before its natural end date, two distinct billing scenarios may apply, depending on the timing of the cancellation:

1. **Cancellation in a Paid/Settled Period** – The subscriber has already paid for the current subscription period.
2. **Cancellation in an Invoiced Period** – The subscriber has been invoiced for the upcoming period but has not yet paid.

The proration policy you configure determines what happens in each scenario.

.. _proration-types:

Types of Proration Policies
============================

|projectName| supports different proration strategies. Each policy can be configured independently for the two cancellation scenarios mentioned above.

The primary options are:

- **Full Proration** – Credit or charge the subscriber based on the exact time remaining in the period.
- **No Proration** – No adjustment is made; the subscriber keeps access for the full period or loses the amount already paid/invoiced.

Scenario 1: Cancellation in a Paid/Settled Period
=================================================

In this scenario, the subscriber has **already paid** for the current subscription period, and the cancellation occurs before the period ends.

**Policy Options:**

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * - Policy
     - Effect
   * - **Full Proration**
     - The subscriber is credited for the unused portion of the period. A credit note or allowance is issued for the prorated amount.
   * - **No Proration**
     - No refund or credit is issued. The subscriber retains access until the end of the already-paid period, but no new billing periods are created.

Visual Timeline: Full Proration (Paid Period)
----------------------------------------------

.. mermaid::

    gantt
        title Cancellation with Full Proration (Paid Period)
        dateFormat  YYYY-MM-DD
        section Subscription Period
            Paid Period (Jan 1 - Jan 31)   :done, period, 2025-01-01, 30d
            Cancellation Date   :milestone, cancel, 2025-01-15, 0d
            Unused Period (Credited)   :crit, unused, 2025-01-15, 16d
        section Billing Events
            Invoice Paid (Jan 1)   :milestone, paid, 2025-01-01, 0d
            Credit Note Issued   :milestone, credit, 2025-01-15, 0d

In this example:

- **Subscription Period**: January 1 - January 31 (30 days, already paid)
- **Cancellation Date**: January 15 (after 14 days of service)
- **Unused Period**: 16 days (from January 15 to January 31)
- **Credit Issued**: The subscriber receives a credit for 16/30 of the paid amount

**Calculation Example:**

Assume the subscriber paid **$90.00** for the 30-day period.

.. code-block:: text

    Paid Amount: $90.00
    Period Length: 30 days
    Days Used: 14 days (Jan 1 - Jan 14)
    Days Unused: 16 days (Jan 15 - Jan 31)

    Proration Calculation:
    Credit Amount = (Days Unused / Period Length) × Paid Amount
    Credit Amount = (16 / 30) × $90.00
    Credit Amount = $48.00

The subscriber receives a **$48.00** credit or refund for the unused portion of the period.

Visual Timeline: No Proration (Paid Period)
--------------------------------------------

.. mermaid::

    gantt
        title Cancellation with No Proration (Paid Period)
        dateFormat  YYYY-MM-DD
        section Subscription Period
            Paid Period (Jan 1 - Jan 31)   :done, period, 2025-01-01, 30d
            Cancellation Registered   :milestone, cancel, 2025-01-15, 0d
            Access Continues   :active, access, 2025-01-15, 16d
        section Billing Events
            Invoice Paid (Jan 1)   :milestone, paid, 2025-01-01, 0d
            No Credit Issued   :milestone, nocredit, 2025-01-15, 0d

In this example:

- **Subscription Period**: January 1 - January 31 (30 days, already paid)
- **Cancellation Date**: January 15 (cancellation registered)
- **Access**: The subscriber retains access until January 31
- **Credit**: No credit is issued; the subscriber paid for the full period and keeps access

**Financial Impact:**

.. code-block:: text

    Paid Amount: $90.00
    Credit Issued: $0.00
    Subscriber Retains: Full access until end of period (Jan 31)

The subscriber keeps access for the remaining 16 days but does not receive a refund. No new billing period is created.

Scenario 2: Cancellation in an Invoiced (But Unpaid) Period
===========================================================

In this scenario, the subscriber has been **invoiced** for the upcoming subscription period, but the invoice has **not been paid** yet.

**Policy Options:**

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * - Policy
     - Effect
   * - **Full Proration**
     - The invoice amount is adjusted (prorated) to reflect only the portion of the period that will be used before cancellation.
   * - **No Proration**
     - The full invoice amount remains due. The subscriber is expected to pay for the entire period, even though the subscription will be cancelled.

Visual Timeline: Full Proration (Invoiced Period)
--------------------------------------------------

.. mermaid::

    gantt
        title Cancellation with Full Proration (Invoiced But Unpaid Period)
        dateFormat  YYYY-MM-DD
        section Subscription Period
            Future Period (Feb 1 - Feb 28)   :active, period, 2025-02-01, 28d
            Cancellation Date   :milestone, cancel, 2025-02-10, 0d
            Period Used   :done, used, 2025-02-01, 9d
            Period Discarded   :crit, discarded, 2025-02-10, 18d
        section Billing Events
            Invoice Issued (Jan 15)   :milestone, issued, 2025-01-15, 0d
            Invoice Adjusted   :milestone, adjusted, 2025-01-25, 0d
            Invoice Due (Feb 1)   :milestone, due, 2025-02-01, 0d

In this example:

- **Subscription Period**: February 1 - February 28 (28 days)
- **Invoice Issued**: January 15 (for the upcoming period)
- **Cancellation Date**: January 25 (before period starts, after invoice issued)
- **Planned Service Period**: February 1 - February 10 (9 days only)
- **Invoice Adjustment**: The invoice is reduced to charge only for 9 days

**Calculation Example:**

Assume the invoice amount is **$84.00** for the 28-day period.

.. code-block:: text

    Original Invoice Amount: $84.00
    Period Length: 28 days
    Days to Be Used: 9 days (Feb 1 - Feb 10)
    Days Discarded: 19 days (Feb 11 - Feb 28)

    Proration Calculation:
    Adjusted Amount = (Days to Be Used / Period Length) × Invoice Amount
    Adjusted Amount = (9 / 28) × $84.00
    Adjusted Amount = $27.00

The invoice is adjusted to **$27.00**, reflecting only the 9 days of service the subscriber will receive.

Visual Timeline: No Proration (Invoiced Period)
------------------------------------------------

.. mermaid::

    gantt
        title Cancellation with No Proration (Invoiced But Unpaid Period)
        dateFormat  YYYY-MM-DD
        section Subscription Period
            Future Period (Feb 1 - Feb 28)   :active, period, 2025-02-01, 28d
            Cancellation Date   :milestone, cancel, 2025-02-10, 0d
            Period Used   :done, used, 2025-02-01, 9d
            No Service After Cancellation   :crit, noservice, 2025-02-10, 18d
        section Billing Events
            Invoice Issued (Jan 15)   :milestone, issued, 2025-01-15, 0d
            No Adjustment   :milestone, noadjustment, 2025-01-25, 0d
            Full Amount Due (Feb 1)   :crit, due, 2025-02-01, 0d

In this example:

- **Subscription Period**: February 1 - February 28 (28 days, invoiced)
- **Cancellation Date**: January 25 (cancellation registered before period starts)
- **Invoice**: Remains at full amount ($84.00)
- **Service**: Subscriber receives service only until February 10

**Financial Impact:**

.. code-block:: text

    Original Invoice Amount: $84.00
    Adjusted Amount: $84.00 (no adjustment)
    Days of Service: 9 days (Feb 1 - Feb 10)
    Subscriber Pays: Full $84.00 for partial service

The subscriber must pay the full invoice amount even though the subscription ends on February 10, receiving only 9 days of the 28-day period.

Configuring Proration Policies
===============================

Proration policies are configured at the **Dunning Process** level via the **CancellationProration** property. This property references a **ProrationPolicy** entity that defines how cancellations should be handled.

Steps to Configure
------------------

1. **Create a ProrationPolicy** using the API:

   .. code-block:: http

       POST https://api.info-subscription.com/ProrationPolicy HTTP/1.1
       Host: api.info-subscription.com
       S4-TenantId: {your-tenant-id}
       Authorization: Bearer {token}
       Content-Type: application/json

       {
         "name": "Standard Proration Policy",
         "paidPeriodPolicy": "FullProration",
         "invoicedPeriodPolicy": "FullProration"
       }

2. **Associate the ProrationPolicy with a Dunning Process**:

   When creating or updating a Dunning Process, set the ``cancellationProrationId`` to reference the ProrationPolicy you created.

   .. code-block:: http

       POST https://api.info-subscription.com/DunningProcess HTTP/1.1
       Host: api.info-subscription.com
       S4-TenantId: {your-tenant-id}
       Authorization: Bearer {token}
       Content-Type: application/json

       {
         "name": "Standard Dunning Process",
         "cancellationProrationId": "{proration-policy-id}",
         // ... other dunning process properties
       }

Policy Options Reference
------------------------

.. list-table::
   :header-rows: 1
   :widths: 40 60

   * - Property
     - Description
   * - **paidPeriodPolicy**
     - Defines how to handle cancellations when the period is already paid/settled. Options: ``FullProration``, ``NoProration``
   * - **invoicedPeriodPolicy**
     - Defines how to handle cancellations when the period is invoiced but not paid. Options: ``FullProration``, ``NoProration``

Business Considerations
=======================

When choosing a proration policy, consider the following:

**Full Proration:**

- **Pros**: Fair to subscribers; they only pay for what they use. Can improve customer satisfaction and reduce churn.
- **Cons**: More complex accounting; requires issuing credits and adjusting invoices. May result in small credits that are difficult to process.

**No Proration:**

- **Pros**: Simpler accounting; no need to issue credits or adjust invoices. Clear policy for subscribers.
- **Cons**: May be perceived as unfair by subscribers who cancel mid-period. Could lead to negative customer feedback.

**Hybrid Approach:**

You can configure different policies for paid vs. invoiced periods. For example:

- **Paid Period**: No Proration (subscribers keep access for the full period)
- **Invoiced Period**: Full Proration (adjust invoice to reflect actual usage)

This approach balances simplicity (no credits for already-paid periods) with fairness (adjusted charges for future periods).

Integration with Events
=======================

When a subscription is cancelled and proration is applied, the following events may be triggered:

- :ref:`SubscriptionCancelled <subscription-cancelled-event>` – Indicates that a cancellation has been registered
- :ref:`CreditNoteIssued <credit-note-issued-event>` – Issued when proration results in a credit for a paid period
- **InvoiceAdjusted** – May be used when proration adjusts an invoiced period (implementation-specific)

Developers integrating with |projectName| should listen for these events to keep external systems in sync with subscription and billing changes.

For more details on events, see the :ref:`Events and Webhooks section <events>`.

Related Documentation
=====================

- :ref:`Billing Overview <billing-cycle>` – Understand the overall billing cycle and how cancellations fit in
- :ref:`Subscription Cancellation Event <subscription-cancelled-event>` – Details on the cancellation event
- :ref:`Dunning Process <Billing_Dunning_Timeline>` – How dunning processes work with billing
- `ProrationPolicy API <https://api.info-subscription.com/swagger/index.html#/ProrationPolicy/CreateProrationPolicy>`_ – API reference for creating and managing proration policies

Summary
=======

Proration policies provide flexible control over how subscription cancellations are handled financially:

1. **Paid Periods**: Choose whether to credit subscribers for unused time or let them retain access for the full period.
2. **Invoiced Periods**: Choose whether to adjust invoices to reflect actual usage or require full payment.

By configuring these policies appropriately, you can balance customer satisfaction, operational simplicity, and revenue protection.

For technical implementation details, consult the `API documentation <https://api.info-subscription.com/swagger/>`_ or :ref:`contact support <reporting-bugs>` for assistance.
