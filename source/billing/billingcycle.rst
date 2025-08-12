Billing in |projectName|
------------------------

|projectName| automates billing depending on the rules setup by the selling organization. 

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
	- Integration: Listen for `OrderCompleted` or `SubscriptionCreated` events to trigger onboarding or provisioning logic.
	- Event Reference: :doc:`../events/types/subscription`

2. **Subscription Created**
	- The subscription is created and the billing cycle begins.
	- Integration: Use the API to track subscription status and details.
	- Event Reference: :doc:`../events/types/subscription`

3. **Payment Demand Scheduling**
	- A payment demand/invoice is scheduled for the next period.
	- Integration: Subscribe to payment demand events or query via API.
	- Event Reference: :doc:`../events/types/invoice`

4. **Invoice Issued**
	- The invoice is issued when the period starts.
	- Integration: Listen for `InvoiceIssued` events to trigger notifications or syncs.
	- Event Reference: :doc:`../events/types/invoice`

5. **Payment Request Scheduling (Repeatable)**
	- For some payment providers, a payment request is scheduled after invoice issuance.
	- Integration: Listen for `PaymentRequestScheduled` events to initiate payment provider flows.
	- Event Reference: :doc:`../events/types/invoice`

6. **Repeated Payment Request Flow (for Integrated Providers)**
	------------------------------------------------------

	For some payment providers, the process of requesting payments can be repeated in case of failures. The following diagram and explanation describe this retry logic:

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

6. **Payment Request Processing**
	- Payment request is processed and sent to the provider.
	- Integration: Listen for `PaymentRequestProcessed` events to update payment status or trigger external payment APIs.
	- Event Reference: :doc:`../events/types/invoice`

7. **Wait For Payment**
	- The system waits for payment or other resolution (e.g., credit note, reminders).

8. **Credit Note Issued **
	- If the invoice is credited, a credit note is issued.
	- Integration: Listen for `CreditNoteIssued` events to update accounting or trigger refunds.
	- Event Reference: :doc:`../events/types/invoice`

9. **Invoice Paid**
	- Payment is received and the invoice is settled.
	- Integration: Listen for `InvoicePaid` events to unlock services or update accounting systems.
	- Event Reference: :doc:`../events/types/invoice`

10. **Reminder Issued (Repeatable)**

	Repeated Reminder Flow
	----------------------

	For some configurations, reminders can be scheduled and issued repeatedly if payment is not received. The following diagram and explanation describe this reminder retry logic:

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

11. **Subscription Cancellation**
	- If payment is not received after reminders, the subscription may be cancelled.
	- Integration: Listen for cancellation events to clean up resources or notify users.
	- Event Reference: :doc:`../events/types/subscription`

12. **End**
	- The billing cycle ends for this subscription instance (either paid, credited, or cancelled).