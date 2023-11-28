.. _changelog-r119:

**************************
Release November 27th 2023
**************************

This release is a bit light on the feature side, however lots of stuff is going on behind the scenes to improve stability, resilience, security and performance.

However a few existing features are now exposed in the Merchant UI.

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Automatic cancellation/deactivation of Vipps Payment Agreements when a cancelled subscription has ended.
* Introduced support for semi-atomic transferring of billing account transactions between billing accounts, and between subscribers. This includes a transfer log for reporting and analytics.

Changed
-------

* Recurring/Agreement payments on Swedbank Pay now supplies the final VAT Amount of the transaction. This is only a reporting value, and only sparingly available in the Swedbank Merchant Portal.

Fixed
-----

* An error where credited and re-issued Payment Demands would not be exported for AutoGiro (Bankgirot Sweden).
* An error which made it impossible to cancel/remote AutoGiro mandates

Deprecated
----------
We call out the following deprecations, the endpoints/field will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* We are deprecating the endpoints ``/paymentdemand/{id}/credit/completely`` and ``/paymentdemand/{id}/credit/partially`` in favor of ``/paymentdemand/{id}/credit`` endpoint.
* We are deprecating the field ``TaxPercentage`` on the endpoint for creating Account Payment Demand transaction ``POST /paymentdemand/``, in favour of specifying a list of Tax Details.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* Option to toggle whether to reduce reminder amounts with surplus accounted payments (allowances).
* It is now possible to cancel Vipps Payment Agreements.
* When ordering from merchant it is possible to choose payment types besides Invoice.
* Adding an Organization Number validation for tenants with Norwegian organizations when attempting to switch/use an EHF Payment Agreement.
* Introduced option for quick navigation to Enterprise Plan owners from the Enterprise Plan configuration.

Changed
-------

* Exposed existing Payment Provider Types for EHF and Email in various workflows.
* All credit operations now go through the new endpoint and credit flows will transfer back account transactions as mentioned in the previous release.
* Removed/Sanitized the Invoices and Payments grid in the subscriber overview.
* Refunds are now highlighted with a separate colour.

Fixed
-----

* Removed possibility to delete Enterprise Plan owners with active enterprise plans.
* An issue where Cancellation Cause would disappear when changing a previously registered cancellation.
* An issue where Invoice/CreditNote copy on Enterprise Plan would not redirect back to the details.