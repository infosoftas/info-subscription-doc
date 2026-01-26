.. _billing-cycle:

Billing Overview
----------------

|projectName| automates billing depending on the rules setup by the selling organization via Billing Plans and Dunning Processes.

A general understanding of how the various stages of the billing cycle work is important for building successful integrations.

This document outlines the basics of the billing cycle, including key stages and developer integration points. Some details are left out for clarity.

The cycle is event-driven, and each stage offers opportunities for custom integrations via events and API endpoints.

Billing Cycle Stages & Integration Points
-----------------------------------------

The following state chart outlines the overall billing cycle and state transitions.
Each stage is explained in more detail following the diagram.

.. mermaid::

   stateDiagram-v2
	   [*] --> OrderCompleted: Order/Initial Subscription
	   OrderCompleted --> SubscriptionCreated
	   SubscriptionCreated --> PaymentDemandScheduled
	   PaymentDemandScheduled --> InvoiceIssued: Time passes
	   InvoiceIssued --> PaymentRequestScheduled: For integrated providers
	   InvoiceIssued --> WaitForPayment
	   PaymentRequestScheduled --> PaymentRequestProcessed: Wait for processing time
	   PaymentRequestProcessed --> WaitForPayment
       WaitForPayment --> CreditNoteIssued: Invoice credited
	   WaitForPayment --> InvoicePaid: Payment received
	   WaitForPayment --> ReminderIssued: Payment not received
	   ReminderIssued --> InvoicePaid: Payment received
       ReminderIssued --> MultipleReminders: Another reminder
       MultipleReminders --> ReminderIssued
	   ReminderIssued --> SubscriptionCancelled: Payment not received
	   InvoicePaid --> End
       CreditNoteIssued --> End
	   SubscriptionCancelled --> End
       End --> [*]

.. important::
    The billing cycle is associated with a specific subscription, and each `SubscriptionCreated` event starts a separate billing cycle.
    
    Multiple billing cycles typically overlap because payments are not always received and settled in a timely manner.

.. _in-advance-billing:

In-Advance Billing Model
-------------------------

|projectName| operates on an **in-advance billing model**, meaning subscribers are billed at the beginning of each subscription period for services to be provided during that period. This is in contrast to an **in-arrears billing model**, where billing occurs at the end of a period for services already consumed.

Understanding the Billing Timeline
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In the in-advance billing model:

1. **Subscription Start as Due Date**: When a subscription begins or renews, the **subscription start time** (or renewal time) serves as the **due date** for the payment demand/invoice. This means payment is expected at the beginning of the service period.

2. **Billing Plan Minimum Due Days**: Billing Plans can define a "minimum due days" parameter that specifies how many days before the due date (subscription start) the invoice should be issued. This allows organizations to give subscribers advance notice before payment is required.
   
   - For example, if a subscription renews on February 1st and the billing plan has 15 minimum due days, the invoice will be issued around January 17th (15 days before the due date of February 1st).
   - The minimum due days are **relative to the subscription start/renewal date**, ensuring subscribers receive their invoices with sufficient time to review and prepare for payment.

3. **Payment Processing Timing**: For integrated payment providers, payment requests are scheduled and processed based on the provider's requirements and the billing plan configuration. Some providers (like direct debit systems) require several days of lead time before the due date, which is why minimum due days are important.

**Visual Example**

The following diagram illustrates the in-advance billing timeline for a single subscription period:

.. mermaid::

    gantt
        title In-Advance Billing Timeline Example
        dateFormat  YYYY-MM-DD
        section Subscription Period
            Service Period (Jan 1 - Jan 31)   :active, period, 2025-01-01, 30d
        section Billing Events
            Invoice Issued (15 days before due)   :milestone, issued, 2024-12-17, 0d
            Invoice Due = Period Start   :crit, due, 2025-01-01, 0d
            Payment Expected   :milestone, payment, 2025-01-01, 0d

In this example:

- **Service Period**: January 1 - January 31 (the subscription period being billed)
- **Invoice Issued**: December 17 (15 days before the due date, based on billing plan minimum due days)
- **Invoice Due Date**: January 1 (the subscription period start date)
- **Payment Expected**: At the beginning of the service period (in-advance)

The subscriber is billed **before** the service period begins, receives the invoice 15 days in advance, and payment is due at the start of the period they're being billed for.

.. note::
    For a more comprehensive view of how billing and dunning work across multiple periods, including reminders and payment processing, see the :ref:`Billing and Dunning Timeline <Billing_Dunning_Timeline>` section below.

Hybrid Billing: In-Advance + In-Arrears
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

While the core subscription billing operates in-advance, |projectName| also supports a **hybrid billing model** that combines in-advance and in-arrears billing through the use of **charges and allowances** on billing accounts.

**How Charges and Allowances Work:**

- **Charges**: Additional costs that are added to a subscriber's billing account. These can represent usage-based fees, one-time charges, or any services consumed during a billing period.
- **Allowances**: Credits or adjustments that reduce the amount owed on a billing account.

When a payment demand is created for the next subscription period (in-advance billing), the system can optionally include any outstanding charges or apply allowances from the billing account. This effectively creates an in-arrears component within the in-advance billing structure:

- The **subscription fee** is billed in-advance (for the upcoming period)
- Any **charges** accumulated during the previous period are billed in-arrears (added to the current invoice)
- Any **allowances** are applied to reduce the total amount due

This hybrid approach is particularly useful for:

- Usage-based billing models where consumption is tracked during a period and billed at the next renewal
- Additional services or products consumed outside the regular subscription
- Adjustments, credits, or refunds that need to be applied to future invoices
- Scenarios combining fixed subscription fees with variable consumption charges

For more details on creating transactional invoices that settle account balances, see :ref:`Transaction (Non-Recurring) Invoices <standalone-paymentdemands>`.

.. tip::
    When designing your billing model, consider how the timing of invoice issuance and payment due dates align with your subscribers' payment cycles and cash flow. The minimum due days configuration is key to ensuring subscribers have adequate time to review invoices and arrange payment.


1. **Order Completed / Initial Subscription Creation**
	- Triggered by an incoming order or initial subscription.
	- Integration: Listen for :ref:`OrderProcessed <order-processed-event>` or :ref:`SubscriptionCreated <subscription-created-event>` events to trigger custom onboarding or provisioning logic.

2. **Subscription Created**
	- The subscription is created and the billing cycle begins.
	- Integration: Use the API to track subscription status and details.
	- Event Reference: :ref:`SubscriptionCreated <subscription-created-event>`

3. **Payment Demand Scheduling**
	- A payment demand/invoice is scheduled for the next subscription period. This leads also to a Preliminary Payment Demand and an Open Invoice.
	- Integration: Subscribe to invoice events or query via API.
	- Event Reference: :ref:`InvoiceIssued <invoice-issued-event>`

4. **Invoice Issued**
	- The invoice is issued, with a Due time set to the start of the subscription period.
	- Integration: Listen for :ref:`InvoiceIssued <invoice-issued-event>` events to trigger notifications or syncs.

5. **Payment Request Scheduling (Repeatable)**
	- For some payment providers, a payment request is scheduled after invoice issuance.
	- Integration: Listen for `PaymentRequestScheduled` events to react to payment provider flows.
	- See `Repeated Payment Request Flow`_ for details on retries.

6. **Payment Request Processing**
	- Payment request is processed and sent to the provider.
	- Integration: Listen for `PaymentRequestProcessed` events to update payment status or trigger external payment APIs.

7. **Wait For Payment**
	- The system waits for payment or other resolution (e.g., credit note, reminders).

8. **Credit Note Issued**
	- If the invoice is credited, a credit note is issued. The billing cycle ends for this Payment Demand.
	- Integration: Listen for :ref:`CreditNoteIssued <credit-note-issued-event>` events to update accounting or trigger refunds.

9. **Invoice Paid**
	- Payment is received and the invoice is settled.
	- Integration: Listen for :ref:`InvoicePaid <invoice-paid-event>` events to unlock services or update accounting systems.

10. **Reminder Issued (Repeatable)**
	- If payment is not received, reminders may be issued repeatedly.
	- Integration: Listen for :ref:`ReminderIssued <reminder-issued-event>` events to trigger custom reminder flows or escalate actions.
	- See `Repeated Reminder Flow`_ for details on retries.

11. **Subscription Cancellation**
	- If payment is not received after reminders, the subscription may be cancelled.
	- Integration: Listen for :ref:`SubscriptionCancelled <subscription-cancelled-event>` and :ref:`SubscriptionDeactivated <subscription-deactivated-event>` events to clean up resources or notify users.
	- For details on how cancellations affect billing and proration, see :ref:`Proration Policies for Cancellations <proration-policies>`.

12. **End**

	- The billing cycle ends for this subscription instance (either paid, credited, or cancelled).

.. _Repeated_Payment_Request_Flow:

Repeated Payment Request Flow
-----------------------------

For some integrated payment providers, the process of requesting payments can be repeated in case of failures (Card providers at the current time). 
The following diagram and explanation describe this retry logic and how it relates to the overall billing cycle:

.. mermaid::

    stateDiagram-v2
            [*] --> PaymentRequestScheduled: First attempt
            PaymentRequestScheduled --> PaymentRequestProcessed: Request processed
            PaymentRequestProcessed --> PaymentRequestScheduled: Retry (if attempt count not exceeded)
            PaymentRequestProcessed --> InvoicePaid: Payment received
            PaymentRequestProcessed --> CreditNoteIssued: Invoice credited
            InvoicePaid --> [*]: Remove scheduled payment request
            CreditNoteIssued --> [*]: Remove scheduled payment request

**Flow Explanation:**

- The first payment request is scheduled.
- The request is processed by the payment provider.
- If the payment fails and the maximum attempt count is not exceeded, another payment request is scheduled and processed.
- This cycle repeats until either the invoice is paid, a credit note is issued, or the attempt count is exceeded.
- When payment is received or the invoice is credited, any scheduled payment requests are removed.

.. _Repeated_Reminder_Flow:

Repeated Reminder Flow
----------------------

Depending on the Dunning Process and Billing Plan configurations, reminders can be scheduled and issued repeatedly if payment is not received. 
The following diagram and explanation describe this reminder retry logic:

.. mermaid::

    stateDiagram-v2
            [*] --> ReminderScheduled: First reminder scheduled
            ReminderScheduled --> ReminderIssued: Reminder sent
            ReminderIssued --> ReminderScheduled: Schedule next reminder (if configured)
            ReminderIssued --> InvoicePaid: Payment received
            ReminderIssued --> CreditNoteIssued: Invoice credited
            InvoicePaid --> [*]: Remove scheduled reminder
            CreditNoteIssued --> [*]: Remove scheduled reminder

**Flow Explanation:**

- The first reminder is scheduled if configured.
- The reminder is issued to the subscriber.
- If payment is still not received and additional reminders are configured, another reminder is scheduled and issued.
- This cycle repeats until either the invoice is paid, a credit note is issued, or no further reminders are configured.
- When payment is received or the invoice is credited, any scheduled reminders are removed.

.. _Billing_Dunning_Timeline:

Billing and Dunning Timeline
----------------------------

The following chart illustrates the essential points in the billing cycle across two subscription periods (N and N+1). 

.. mermaid::

    gantt
        title Billing and Dunning Timeline
        dateFormat  YYYY-MM-DD
        section Period N
            Subscription N (30d)   :done, n, 2025-01-01, 30d
            Invoice Issued   :vert, m1, 2025-01-15, 0d
            Invoice Due: vert, m2, 2025-01-31, 0d
        section Period N+1
            Subscription N+1 (30d)       :active, n1, 2025-01-31, 30d
            Reminder Issued  :vert, m3, 2025-02-05, 0d
            Invoice Paid: vert, m4, 2025-02-15, 0d
