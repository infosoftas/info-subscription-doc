.. _changelog-r110:

***************************
Release Feburary 16th 2023
***************************
In this release we are consolidating some of the internal services and resources.
Primarily the consolidation is an internal resource and cost optimization, but it also provides lower latency and imporved performance for a series of operations related to Products, Prices, Template Plans, Organizations and Taxes.
There are no changes to the API or the functionality associated with these changes.

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

* Added EHF (Norwegian UBL Billing format) as a separate Payment Provider Type for new Payment Agreements and Orders **Preview**.
* Fixed an issue where switching subscription plan immediately would lead to a new Subscriber Account being created where an existing account should have been re-used.
* All new Webhook registration now includes a TenantId header in each published event, refer to the event docs for more details.
* Removed the order restriction on products being required for all types of choices - if not defined ALL products on the template are choosen.
* The reporting subsystem now includes optional StartTime and EndTime on PaymentDemandDetails to simplify reporting and analytics based on subscription periods. We will be applying the historic data for 2023. Reach out to support if you require data for previous periods.
* Custom Power Bi reports data refresh is now scheduled semi-randomly when importing/uploading new reports.
* Fixed a series of technical issues with the Mastercard Payment Services eFaktura integration, related to large queries and better status reporting.
* A series of adjustments in how the subscriber ledger is updated when ledger based billing is toggled on. Fixes a series of issues where the ledger is out-of-sync with the underlying billing account and actually invoiced items.
* Added handling of AvtaleGiro claims generation on weekends so that the duedate is pushed acording to the deadline calculations as if they were produced on the following monday.
* Fixed an issue where trying to generate an Account Demand with an invalid payment agreement would return HTTP 500 instead of HTTP 400 with a proper description.
* Fixed an issue where Account Transaction types and descriptions would not be stored correctly.
* Adjusted the EHF Organization validation so it only creates one record in the validation result regardless of the number of invoices where it has failed.
* Fixed an issue with rounding during tax total caulcations for EHF.
* Changed the handling of amount calculation in EHF to support multiple units.

EHF as Payment Provider
-----------------------
This release includes a new Payment Provider Type: EHF.

The main reason for adding EHF as a separate provider is to allow subscribers to toggle off EHF invoicing even in cases where they are required to accept them by law.
In addition it will become possible to adjust Fee values separatly in a future release.

New Payment Agreements can be created with this type, either directly through the Payment Agreement endpoint, alternatively during order creation with a set of parameters.

A future release will provide UI in self-service and merchant for switching to/from an EHF agreement as well as sales poster support for EHF invoicing.

Since EHF was already supported as a "document" format, this new type will need to be enabled for each tenant and existing payment agreements will need to be migrated to EHF where applicable.
Please contact support to get started with this feature.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added support for showing planned Subscription Plan changes on a subscription.
* Multiple text adjustments in the Norwegian localization.
* Adjusted visualization of Refunds in the Subscriber Ledger/Economic Journal view.
* Aligned Enterprise Plan Invoice crediting so it resembles the regular crediting more closely.
* Adjusted descriptions when assigning users to subscribers.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* The Self-Service invoice view now closely resembles the view in Merchant.
* Added option to allow a logout redirect back to the Tenant/Organization website.
* Change page title from INFO-Subscription to "My Page" or similar for other localizations.
* Improvements to the responsive layout for small screen devices.
* Fixed an issue with how organization number and address lines are displayed on invoices.
* Multiple text adjustments in the Norwegian localization.