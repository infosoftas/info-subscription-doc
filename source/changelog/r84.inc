.. _changelog-r84:

*************************
Release January 20th 2021
*************************
The following changes started rolling out on January 20th. All backend/api changes have been deployed while Client changes are propagating gradually over the next couple of days.

We are pleased to announce that with the release all tenants have now been migrated to the new version of our salesposter.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added option to export EHF Invoices and Credit Notes separately. Default behaviour continues to be exporting everything in one package.
* Payments that fail matching can now be deleted. Once matched and settled they cannot be deleted. This allows cleaning up extranous payments.
* Mutiple adjustments and fixes to the Vipps Recurring integration **Preview**.
* Reminders now include a separate property ReminderNumber to help determine how far in a reminder sequence the specific document is. This sequence number is local to the invoice and associated reminders.
* Expanded account demand handling to provide more explicit error messages **Preview**.
* Added option so subscriber accounts are generated already when an order is processed **Preview**.
* Payment Demands now contains a detailed Tax Breakdown grouped by Products, also available in the reporting sub system.
* Fixed an issue where Invoice PayableAmount would not include invoice fees.
* Fixed an issue where it was not possible to remove an AvtaleGiro Account configuration.
* Fixed an issue that would sometimes cause Invoice Lines to be duplicated by the billing routine.
* Adjusted handling of subscriber address changes in the Delivery subsystem to avoid multiple daily changes to Distribution Innovation **Preview**.
* Fixed a but where Invoice draft would not use the upcoming Invoice Contact as the address/recipient of the Invoice (it would be corrected for the actual issued invoice).


Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added UI support for new event types added to backend in December.
* Support for configuring Vipps Recurring accounts and agreements **Preview**.
* Added support for AvtaleGiro Account Configuration **Preview**.
* Adjustments to displaying of Invoice and Reminder amounts (base amounts, taxes and fees).
* Fixed an issue where registering a new subscription on an existing subscriber with an existing invoice contact would generate a subscription with the wrong contact.
* Changed how language switching works to avoid some errors with partially switched language setting.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Added support for Vipps Recurring as a payment provider in the Salesposter **Preview**.
* Added support for Vipps Recurring agreements in Self-Service **Preview**.
* Added multiple new translations for registration of Swedbank Pay agreements in self-service and salesposter.