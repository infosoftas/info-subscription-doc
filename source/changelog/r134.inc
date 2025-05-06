.. _changelog-r134:

****************
Release May 8th
****************

A new release of INFO-Subscription is ready, we didn't make it in time for May 4th, so no Star Wars references this time.
Contrary to the last release notes we would like to announce that the INFO-Subscription team is still here, and we are committed to providing you with the best possible service. 
So don't worry, INFO-Subscription is not going anywhere!

This release includes a number of improvements and bug fixes both to existing features and to the preview features we are working on.
As always there are a number of under-the-hood changes that are not listed here, but which should improve the overall performance and stability of the platform, or make room for new features in the future.

API and Backend
===============

Added
-----

* **[Preview]** Support for removing Additional Product from a running subscription (will be wrapped as a scheduled change).
* **[Preview]** Support for adding units to Account Payment Demand transactions.
* **[Preview]** Support for generating payments directly from the SwedbankPay integration instead of via Billing. This allows for automatic payment generation for non-recurring SwedbankPay transactions, letting INFO-Subscription take care of the bookkeeping directly.
* Added a new trigger for the event type `PaymentProcessingFailed`, it is now also triggered when an operation fails related to |VippsMobilePay| EPayments (non-recurring).
* Updated versions of the default supplied Power Bi reports.

Changed
-------

* **[Preview]** Adding an additional product to a subscription will now validate if there is an active price for the product chosen, that matches with the frequency of the subscription.
* Crediting a PaymentDemand on |AvtaleGiro|, |BetalingsService|, |AutoGiro| or |eFaktura| (with a replacement), now allows for switching the payment method to a different one with a specific Due time. Previously it was only possible to switch if leaving the time to be determined by the system.
* Added validation to prevent deletion of a Product which is used as an Additional Product on a Subscription.
* Retry handling and queue wait time in the POST /order/{id}/complete endpoint has been changed to reduce the mean time to complete the order. The retry handling is now more aggressive.
* Allowed |VippsMobilePay| descriptions to be longer than 50 characters. The limit is now set at 100 characters. This is to follow the new API limitations from |VippsMobilePay|.


Fixed
-----

* Invalid response code in the documentation for a few endpoints. The documentation now states the correct response codes for the following endpoints (most of  them were listing a lot of status codes that were not relevant):

  * GET /authorizations/source/account/{id}
  * GET /authorizations/domain/{id}
  * GET /authorizations/source/emaildomain/{id}
  * GET /authorizations/source/external/{id}
  * GET /vippsmobilepay/account
  * GET /vippsmobilepay/account/{id}
  * GET /authorizations/source/subscriber/{id}
  * GET /subscription/scheduledsubscriptionchange/{id}/execute
  * GET /vipps/vippsaccount
  * GET /vipps/vippsaccount/{id}
  * GET /vipps/agreement/{id}
  * GET /vipps/charge/{id}
  * GET /vipps/charge

* An issue where billing would generate a 0 amount allowance during settlement, in cases where existing allowances and a payment would be used to cover the exact demand amount.
* An issue where automatic payment demand crediting would not work. This happened on future orders where the subscription was deleted before being started.
* An issue where the |VippsMobilePay| agreement product description was not being set correctly during orders, but instead would duplicate the plan name.
* An issue where a Payment `Updated` timestamp would be set during approval, even if the payment was not updated.
* The accounting time on account transactions in the reporting subsystem was not set correctly during billing.
* An issue where `TaxPercent` was not set on account charges in the reporting subsystem.


Merchant Client
===============

Added
-----

* **[Preview]** Support for selecting additional products when ordering a new subscription.
* **[Preview]** Support for adding and removing additional products on a running subscription.


Changed
-------

* Unified the look and feel of the newly introduced price tooltip, so that it is consistent across all places where it is used. This is the tooltip that show prices with and without VAT and the VAT percentage.
* Unified the formatting of dates on Payments in all related views.


Fixed
-----

* **[Hotfix]** An issue where searching for subscribers required a configuration value that not all tenants have a value for.
* An issue where removing a shared user from a subscriber account would remove it from all accounts, not just the one it was removed from.


Self-Service, Sales Poster and Checkout
========================================

Changed
-------

* Handling of the automatic |SwedbankPay| account selection during checkout and orders via sales poster to behave in a consistent manner with multiple organizations and accounts.

Fixed
-----

* **[Hotfix]** An issue where it was not possible to create a subscriber without a valid email address in the sales poster.
* **[Preview] Multiple issues related to the checkout application including (but not limited to)

  * Handling of not-supported SwedbankPay languages so it now defaults to English instead of breaking.
  * Better redirect handling for |VippsMobilePay| app switch scenarios.
  * Improved user and subscriber existence check to avoid duplicate subscribers.