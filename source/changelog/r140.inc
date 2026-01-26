.. _changelog-r140:

**********************
Release January 28th
**********************

Happy new year and welcome to 2026. We are ready with the first release of the year, bringing a mix of fixes and improvements. 
As always under the covers we are continuing with stability and performance improvements across the board.



API and Backend
===============

Added
-----

* The OpenAPI document is now versioned. The current version is v1 (or unversioned). No breaking changes are introduced in this release. The documentation has been updated with information about what we consider breaking changes.

Changed
-------

* Improved the handling of Payment Stop processing to cancel future subscriptions correctly in cases where the stop evaluation is configured to run after renewal processing. This ensures that future subscriptions are cancelled as expected when a payment stop is in place.

Fixed
-----

* A mapping issue where the PaymentMethod 'eFaktura' was not mapped to a string on orders, resulting in a number being return if querying for an order completed with eFaktura as payment method (no known impact, but fixed for consistency).
* An issue where DenialOrders would not be validated correctly when creating new orders via the API, causing blind failures when the order was processed with no feedback to the caller.
* An issue where self-chaining would cause template subscription plans to break.
* An issue where Payment Demands for Enterpriseplans would not point to the correct `NextSubscriptionId` when the subscriptions were renewed in the reporting subsystem.

Merchant Client
===============

Added
-----

* Added configuration option for listing default Reporting Tags when creating new subscriptions. This allows merchants to have certain tags always applied to new subscriptions, reducing manual work.
* Support for adding Tax Group when manually creating charges and allowances corrections to a subscriber account (credits and debits).
* Extended the corrections views with Tax Group information when applicable as well as Timestamps for when the correction was created.

Changed
-------

* **[Preview]** Multiple adjustments to the new bulk crediting and write-off tool introduced in the previous release.
* **[Preview]** Multiple improvements to simplify the creation of transactional invoices.
* Adjusted Vipps and MobilePay agreement views to align with other list/grid views in the Merchant Client.
* Invoice and Reminder Fees are now grouped together to simplify the view and reduce clutter.
* Column width on Template Subscription Plan view.

Fixed
-----

* Texts related to bulk price updates.
* A display error when registering a payment on a reminder.
* An issue where invalid TAX was shown when creating a new order with a discount.
* An issue where the daily paid amounts were displaced due to timezone differences.

Self-Service, Sales Poster and Checkout
========================================

Added
-----

* Option for creating Vipps and MobilePay agreements on existing subscriptions, similar to how SwedbankPay agreements can be created. This allows subscribers to add these payment methods to existing subscriptions without needing to create a new order.

Changed
-------

* Invoice and Reminder Fees are now grouped together to simplify the view and reduce clutter.

Fixed
-----

* An issue where it was not possible to remove a future cancellation of a subscription.
* An issue where the wrong source address was used when creating a temporary delivery address change.