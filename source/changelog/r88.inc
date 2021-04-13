.. _changelog-r88:

*************************
Release April 19th 2021
*************************
The following changes started rolling out on Monday April 19th 2021.
The API and backend has been rolled out to all tenants, and the client will be propagated over the next couple of days.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Fixed an issue where cancelled subscriptions belonging to an Enterprise Plan would not be removed from future demands and invoices.
* Added additional validation for Orders during order cancellation to inform the consumer about the order already being completed or cancelled.
* Multiple behind the covers improvements on Vipps Recurring **Preview**.
* Fixed an issue where Vipps Recurring Agreements would be created with their reduced/offer price instead of with the plan full price **Preview**.
* Fixed an issue where AvtaleGiro Claims would be rejected because of an upstream error when generating multiple claims in a short timespan **Preview**.
* Adjusted validation for generating External Invoice Identifiers for `Default` and `Bankgirot` providers, and added a requirement for a Subscriber Number Position.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added option for viewing a subscribers known payment agreements, similar to the one available from the Self-Service side of things.
* Move the option to stop an Enterprise Plan subscription away from the Invoice/Demand and into the general list of subscription on Enterprise Plans, making it possile to cancel subscriptions BEFORE and Invoice is produced.
* Changed which dates are shown when searching for Payments. So it aligns with the actual payment booking date.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Minor visual adjustments to the Invoice Reference in the salesposter.
* Added information about credited invoices.
