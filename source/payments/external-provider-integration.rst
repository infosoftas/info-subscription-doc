.. _external_payment_provider_integration:

Bring Your Own Payment Provider
===============================

This guide describes how a third-party (API consumer) can integrate an external payment provider with INFO-Subscription using only the public API and webhooks. The integration is based on invoice-related events and reporting payment results via the Payments API.

Overview
--------
Third-party systems can:

- Listen for billing/invoice related events via webhooks.
- Initiate payments with their own provider when invoices are due.
- Report payment results to INFO-Subscription using the Payments API.

Integration Steps
-----------------
Multiple steps are involved in the integration process, and there are differences and nuances depending on the external payment provider's capabilities. 
The following is a high-level overview of the integration steps:

1. Register Payment Agreements
   - Use the API to create and manage payment agreements for the subscribers.
   - POST Agreement details to `/paymentagreement`.
   - Store provider-specific references in your own system.

2. Listen for Invoice Events via Webhooks
   - Subscribe to invoice-related webhooks (e.g., `InvoiceIssued`).
   - Implement a webhook receiver to process these events.

3. Handle Invoice Payment Requests
   - On receiving an invoice event (such as `InvoiceIssued`), fetch paymentdemand, invoice and subscriber details using the API.
   - Initiate payment with your external provider using the agreement reference.

4. Report Payment Results
   - After processing the payment, report the result to INFO-Subscription using the Payments API.
   - POST payment (success/) to `/payment`.

5. Manage Agreement Lifecycle
   - Use the API to update, switch, or terminate payment agreements as needed.
   - Listen for agreement lifecycle events via webhooks to keep your system in sync. (e.g., `CreditNoteIssued`, `SubscriptionCancelled`, `PaymentAgreementDeleted`)

6. Import Agreements (Optional)
   - If agreements are registered outside INFO-Subscription, use the API to import them.

Example Workflow
----------------
1. User subscribes and registers a payment agreement via your UI.
2. You POST the agreement to INFO-Subscription’s API.
3. INFO-Subscription triggers a webhook when an invoice is issued.
4. Your system receives the webhook, processes the payment externally, and reports the result via the Payments API.

The following is a sequence diagram depicting this example workflow.

.. mermaid::

   %%{init: { 'sequence': { 'mirrorActors': false } } }%%
   sequenceDiagram
      actor Subscriber
      participant ThirdPartySystem
      participant INFO-Subscription
      participant ExternalPaymentProvider

      Subscriber->>ThirdPartySystem: Register payment agreement
      
      ThirdPartySystem->>INFO-Subscription: Create agreement (`POST /paymentagreement`)
      
      activate INFO-Subscription
      Note right of INFO-Subscription: Wait for billing
      INFO-Subscription-->>ThirdPartySystem: Event: InvoiceIssued
      deactivate INFO-Subscription

      ThirdPartySystem->>INFO-Subscription: GET /invoice/{id}, GET /subscriber/{id}
      ThirdPartySystem->>ExternalPaymentProvider: Initiate payment
      ExternalPaymentProvider-->>ThirdPartySystem: Payment result
      ThirdPartySystem->>INFO-Subscription: POST /payment
      INFO-Subscription-->>ThirdPartySystem: Payment status updated

References
----------
- See :ref:`events` for webhook documentation.
- See :api-ref:`Payments API <Payment>` for payment details.
- See :ref:`subscribers` for subscriber management.