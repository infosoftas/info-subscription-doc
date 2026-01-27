.. _invoice-issued-event:

Event: com.info-subscription.InvoiceIssued
-------------------------------------------
Whenever a new Invoice is issued/finalized an ``InvoiceIsued`` event is triggered.

The event is typically triggered during automatic billing routines.
It contains a few default properties such as the ``DueDate`` and the ``Number`` that it has been assigned.

Other operations that may trigger Invoices to be generated are 

* Merchant initiated credits with associated corrections (generates a new invoice).
* Removal of future cancellations (re-instates previously creditted invoices).
* Manual issuance of invoices (rarely)

Example Use Case
~~~~~~~~~~~~~~~~
The ``InvoiceIssued`` event may be used to keep external system in sync, typically finance or ERP systems.

The use cases for the event are varied and it can also be used for other things such as:

* Generating an advance notice about an upcoming Invoice.
* Used as a source for distribution/inventory management to pickup new parcels for delivery (with the Invoice).
* External distribution of Invoices, for instance via specialized vendors with support for multiple communication formats.
* As a source document for factoring integrations.

.. _reminder-issued-event:

Event: com.info-subscription.ReminderIssued
--------------------------------------------
Reminders are triggered at scheduled interval relative to the original ``InvoiceIssued`` event. 

They are only triggered if reminders are configured, an no payments exist.

Example Use Case
~~~~~~~~~~~~~~~~
The ``ReminderIssued`` event is typically used in much the same way as ``InvoiceIssued``, such as:

* Generating SMS message about a lack of payment.
* As a source for debt collection integrations.

.. _credit-note-issued-event:

Event: com.info-subscription.CreditNoteIssued
---------------------------------------------
All operations that result in a new credit note will result in a ``CreditNoteIssued`` event being triggered.

The event points to the original invoice as well as a few key pointers about the new credit note.

Typical source of the event are:

* Subscription cancellations (future Invoices are automatically credited).
* Merchant initiated credits.

.. _invoice-paid-event:

Event: com.info-subscription.InvoicePaid
---------------------------------------------
All operations that result in an Invoice being settled/paid will result in a ``InvoicePaid`` event being triggered.

The event points to the invoice being paid as well as a few key pointers about the invoice. Very similar to the ``InvoiceIssued`` event.

Typical source of the event are:

* Payment received in full.
* Settlement due to allowances/discounts and payments.
