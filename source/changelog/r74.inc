.. _changelog-r74:

**************************
Release May 19th 2020
**************************
The following changes rolled out to production on May 19th 2020.
This one took a bit to complete but better late than never.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Support for generating a DI Initialization file to export everything to Distribution Innovation regardless of previous exported state.
* Added support for specifying text/reason when creating subscriber ledger balancing transactions.
* Fixed a bug that would generate the wrong distribution date for Distribution Innovation change files.
* Fixed an issue where subscribers without an organizationnumber in certain edge cases would cause the billing engine to not produce invoices.
* Added support for creating payments with External Invoice Identifiers short than the length of the Subscriber Number (they will now be imported but not matched to anything).
* Fixed an issue that caused empty Identifications to be stored.
* Support for SwedbankPay (formerly PayEx eCommerce).

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* UI/UX changes for multiple organizations.
* Added support for registering subscriber ledger balancing transactions (corrections).
* Minor layout changes for Importing Payments and Billing Plans.
* Added sorting for Subscriber Number and Name for Enterprise Plans.
* Fixed an issue where it was possible to use Inactive Subscription Plans for new orders.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* UI/UX Changes for multiple organizations.
* Support for using SwedbankPay (PayEx eCommerce).
* Added support for redirecting to tenant website on logout (contact support for details - requires some configuraiton assistance)
* Added display of end date for subscription periods.

SwedbankPay/PayEx eCommerce
============================
This release includes a new feature ment to replace an old feature.
Currently all online payment card processing is done using the Payment Service Provider (PSP) PayEx and a rather old processing gateway called POPS.
PayEx has developed a new processing gateway (eCommerce), and POPS will be shut down on June 30th 2020.

To accomodate the change INFO-Subscription now supports SwedbankPay (formerly known as PayEx ecommerce).

There are some adjustments to be made for integrating clients, otherwise tenants will be migrated one by one, and you will be contacted by support prior to the migration.