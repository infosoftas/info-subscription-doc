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
