.. _changelog-r79:

***************************
Release September 24th 2020
***************************
we are back with another release, the following changes rolled out on September 24th 2020.
On the visible side, this is a rather minor release, but we have been working on a lot of things under the covers and a few unfinished features.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added initial support for creating payment demands out of band from the regular recurring subscription timeline/flow.
  Can be used for generating final invoices (settling the account balance), selling singular items while still maintaining the subscription account.
* Added support for omitting fees for the initial demand/invoice from an order.
* Expanded API query filtering support for products and Payment Demands.
* Fixed an issue where product text was not included in the Invoice Document.
* Fixed multiple issues related to the handling of demand/invoice fees not appearing on invoices.
* Added support for defining the same product multiple times on a Subscription Plan (Package), for orders with customized choices.
* Fixed an issue where Payment Demands for Enterprise Plans did not have a value for Payment Provider Type.
* Added support for configuring Payment Request Failure Handling and Retries **Preview**.
* Multiple enhancements and bug fixes to delivery subsystem (still in Preview).

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Minor adjustments to the Invoice and Payment views.
* Adjustments and added information for Enterprise Plans.
* Fixed an issue where exporting the list of Credit Notes would not include the amounts.
* Changed how subscriptions are grouped in the view so they now follow the same timeline.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* An entirely new sales poster flow, includes a better mobile view among other things. **Preview**
* Fixed an issue where end time was not shown on subscriptions.

Contact support for questions and details on participating in various previews - some are available for everyone but may change in API and behaviour, while others requires enablement.