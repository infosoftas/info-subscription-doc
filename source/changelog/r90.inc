.. _changelog-r90:

*************************
Release June 2nd 2021
*************************
The following changes started rolling out on Wedensday June 2nd 2021.
The API and backend is being rolled out to all tenants at the same time, and the client will be propagated over the next couple of days.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added new API for directly querying Vipps about their status of a given Vipps transaction.
* Additional input validation for creating Vipps transactions to fail early.
* Added SubscriberId query filter for Vipps Agreements.
* Extended the Vipps Charge API to allow updating the Agreement details - reflecting any changes in the Vipps App. This is now carried out by the billing service each time a new demand is issued.
* The Payment Import endpoint now includes additional totals once an import has been completed.
* Simplified Distribution Innovation queries to avoid the need for Product Id as input.
* Fixed all known outstanding OAS/Swagger syntax errors.
* Prevented registration of new Enterprise Plan related orders on billing plans that does not align with the billing plan choosen for the Enterprise Plan.
* Credited Invoices are now being registered with the registration time as CreditedOn when automatically credited due to subscription cancellations. Previously the Cancellation time was used.
* Added Payment matching type that allows bypassing of most validation parameters if using "External Invoice Identifier".
* Fixed an issue where multiple payments in Payment File would lead to multiple settlements of the same demand.
* Power Bi Reports now supports adding reports with external datasources.
* The reporting subsystem now removes deleted subscriptions from the list of subscriptions (note deleted subscriptions are different from cancelled subscriptions).
* Fixed an issue where IssueDate was not correctely populated on reminders in the reporting subsystem.
* Fixed an issue where the billing engine would not include product descriptions on tax details.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Multiple minor adjustments to Enterprise Plan related views.
* Added option to directly navigate to Enterprise Plan Owner from a subscriber on an Enterprise Plan.
* Added support for exporting Distribution Innovation delivery files.
* Invoice View adjustments to support standalone Account Demands and Invoices.
* Added support to query for external/remote Vipps status on Vipps transactions.
* Improved generic UI support for multiple currencies.
* Fixed an issue that would sometimes cause issues when filtering reminders.
* Translation adjustments.
* Updated the Subscription Cancellation Power Bi report.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* New login mechanism for shared users **Preview**.
* Adjusted default logo size on salesposter.
* Translation adjustments.