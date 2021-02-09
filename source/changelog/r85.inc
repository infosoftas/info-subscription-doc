.. _changelog-r85:

*************************
Release Feburary 9th 2021
*************************
The following changes started rolling out on Feburary 9th. All backend/Api changes have been deployed while Client changes are propagating gradually over the next couple of days.


API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* **Breaking** Added additional order and plan validation to prevent orders for products with no price line. This means products that are free of charge now need to register a price of 0. All existing products in production already have price 0 but new ones will break if not configured correctly.
* Expanded the API/Swagger reference documentation for Vipps Recurring support.
* New reports for Subscription Plans and Payments.
* Changed payment matching to prevent settlement of credited demands/invoices.
* Additional data added for reminders, billing accounts and account transactions in the reporting sub-system.
* Fixed multiple bugs related to Tax and Fee handling payment demands.
* Change behaviour such that subcriber accounts are generated on the first order and not only on first payment or renewal.
* Changed delivery to bundles events when exporting to Distribution Innovation on the same date.
* Fixed a bug where Contract timestamps would not be stored as UTC on package changes.


Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Support for live address validation with Distribution Innovation **Preview**.
* Support for querying subscriber delivery status with Distribution Innovation **Preview**.
* Added option for querying reminders.
* Includes option for importing Vipps Settlement file **Preview**.
* Fixed an issue related to registration of Vipps accounts **Preview**.
* Fixed an issue that cause the screen to turn grey in case of missing contact information.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Added Swedish as a supported Self-Service language.
* Added support for browser auto-complete for country in sales process.
* Added Google Tag Manager new event completed orders.
* Changed sales poster to prevent accidental double-click when completing an order (causing double registrations).