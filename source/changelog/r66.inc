.. _changelog-r66:

**************************
Release November 27th 2019
**************************
The following changes were rolled out to production on November 27th 2019

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

.. Important::

    The proration calculation approach has been changed. Previously proration calculations would be based on precise timing values down to the `milisecond`.
    The new approach assumes entire days. Additionaly when a day has been started, it is considered consumed immediately.
    The direct consequence being that when a subscription is started, the first day is already consumed, where previously only the time that goes by is consumed.

    We are planning to introduce an approach for defining proration resolution at a later date, but for now it is deemded that the most beneficial approach is to have a resolution of 1 day.

* Added Support for Buyer Reference (See separate section for details).
* Summary totals are now available on the Invoice, CrediteNotes and Reminders.
* Added support for defining Product Groups in reporting. Provides a mapping option that allows grouping products into different conceptual groups, such as "Digital", "Freemium" or similar.
* Restricted direct cancellation of subscriptions on an Enterprise Plan. The Subscriptions will now have to be cancelled via the Enterprise Plan.

    .. Note::

    This also affects Pause and Plan/Package change as these are currently both implemented as wrappers for "stop" and "start" with new options.

* Fixed issue with a missing Order reference when querying for Payment Demands from Orders.
* Fixed multiple issues related to Delivery Configuration and Delivery Management.
* The Billing Engine now supports crediting entire subscriptions on Enterprise Plans when the subscriptions are cancelled in bulk.
* Fixed an issue where proration calculation for Subscriptions on Enterprise Plans would be wrong for the initial period if set with a future start date, and converted to a resolution of 1 day.
* Expanded reporting model with Cancellation Cause from Subscriptions.
* Fixed issue where automatic crediting on cancellation of Orders (initial subscription) would produce the wrong amount. Changed the resolution to 1 day.
* Fixed issue where Subscriber Account was not carried on during renewal.
* Fixed issue where a previous null value in External Id would cause a subsequent update to fail.
* Fixed an issue where Payment Stop rules would not evaluate amount configured.
* Fixed an issue where Credit Card Payments would be processed as UTC times when registered in other timezones.

Client
======
The following new features and improvements are now available in the web client

* Added support infrastructure for Google Tag Manager in Salesposter and Self-Service. Still requires some manual deployment changes per Tenant, contact us for more details.
* Added support for defining an alternate e-mail when sending re-sending an Invoice.
* Added support for defining cancellation cause.
* Added support for defining future start date when ordering new subscriptions.
* Visual changes to the Subscriber overview
* Fixed issue with Order KPI calculation in the dashboard.
* Fixed an issue related to defining the address of an Invoice Payer (Subscriber Contact).

Buyer Reference
===============
This release features the support for Buyer Reference on Invoices.
This includes the following changes

* UI Support for Adding/Updating a textual Buyer Reference on the Subscriber Contact. 
  This will show up as an `Identificiation` entry on the contact.
* Textual fields Buyer Reference on the Invoice Document.
* The Billing Engine will populate Buyer reference based on the Primary Contact or the assigned Invoice Contact if there is a Buyer Reference to populate.
* The EHF Invoice will be generated and exported with the Buyer Reference if present on the Invoice

Known Issues
============

* When demands and invoices with reminders (that has fees) are paid, it is not obvious from the API and the client whether the fee on the demand has been settled or not.
* External Invoice Identifiers may be generated in a way that exceeds the allowed length when Subscriber Number and Invoice Number lengths exceeds the max length.