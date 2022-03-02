.. _changelog-r99:

***********************
Release March 2nd 2022
***********************
Our third release of the year has begun rolling out on March 2nd 2022.
As always we are rolling out the backend in one go, and clients will be rolled out over the next few days.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Fixed discount are now included as a preview feature in the API (refer to separate section for more details).
* The Vipps integration now reports Merchant Serial Number with all requests, as required by Vipps.
* An issue was fixed in billing where reminder fees where not considered when settling demands.
* Fixed multiple errors in EHF generation that would cause validation errors. All of them related to missing Fee and Tax handling.
* Fixed an issue where updating demand details on Enterprise Plans in the reporting system would not be carried out during renewal.
* Re-introduced an OData PaymentDemand navigation property on reminders, allowing expansion to Payment Demands directly within the OData query.

Fixed Discounts in Preview
--------------------------
It is now possible to configure fixed discounts. 
The idea is to use them for long running/permanent discounts provided to employees or other special groups of people.

The backend and API now supports the following:

 * Configuration fixed discounts.
 * Reporting groups for fixed discounts.
 * Fixed Discount can be specified for new orders and new subscriptions.

Fixed discounts will also be included in the clients in a later release.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added support for displaying scheduled payment demand generation on the subscription details views **Preview**.
* Contract time is now shown in a tooltip in the subscription details view.
* Added a link to switch to a parent Enterprise Plan from subscription details.
* Added a link to display the upcoming/next Invoice from subscription details (if present).
* Renamed account number in Vipps Account setup to match Vipps terminology.
* Fixed issue where invoices for standalone payment demands would display a period.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Kilkaya configuration now requires the entire Kilkaya host endpoint and not just the installation id **Preview**.