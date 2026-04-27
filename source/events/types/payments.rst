.. _payment-request-scheduled-event:

Event: com.info-subscription.PaymentRequestScheduled
-----------------------------------------------------
When a payment request is created and scheduled for processing against a payment agreement, a ``PaymentRequestScheduled`` event is triggered.

The event is raised at the point when the system has registered the intent to charge a payment agreement, before the actual processing attempt takes place.

The event includes key details such as the payment request identifier, the associated invoice, the payment agreement, the payment provider type, the subscriber identifier, and the number of previous attempts (useful for distinguishing initial attempts from retries).

Example Use Case
~~~~~~~~~~~~~~~~
The ``PaymentRequestScheduled`` event can be used to:

* Monitor and log scheduled payment activity in external systems.
* Trigger pre-payment notifications or warnings to subscribers.
* Feed real-time dashboards showing pending payment activity.

Related events:

* ``com.info-subscription.PaymentRequestProcessed``

.. _payment-request-processed-event:

Event: com.info-subscription.PaymentRequestProcessed
-----------------------------------------------------
Once a payment request has been processed against a payment agreement, a ``PaymentRequestProcessed`` event is triggered.

This indicates that the payment provider has handled the payment request, regardless of the outcome. For the actual invoice state change, refer to the ``InvoicePaid`` event.

The event includes the payment request identifier, the associated invoice and payment agreement, the transaction identifier from the payment provider, the payment provider type, and the subscriber identifier.

Example Use Case
~~~~~~~~~~~~~~~~
The ``PaymentRequestProcessed`` event can be used to:

* Reconcile payment activity with external financial or ERP systems.
* Trigger follow-up actions based on processed payments, such as updating external entitlement systems.
* Build real-time payment processing statistics and dashboards.

Related events:

* ``com.info-subscription.PaymentRequestScheduled``
* ``com.info-subscription.InvoicePaid``
