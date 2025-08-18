.. _changelog-r136:

*******************
Release August 18th
*******************

We are back after a long summer absence, with the 6th release of the year.

This time around there is an emphasis on improving the visuals in the Merchant Client and Self-Service. While each change is minor the number of changes contributes to a more polished and cohesive user experience.

There are some public features and fixes in the API, but mostly the changes are under the covers.


API and Backend
===============

Added
-----

* **[Preview]** Support for automatic cancellation of subscription when subscribers disable their |Vipps| and |MobilePay| agreements.
* Support for updating a few of the |VippsMobilePay| account options.
* Automatic deactivation of |eFaktura| agreements that are no longer valid with Mastercard Payment Services.
* Support for deactivating |SwedbankPay| agreements before card expiry.
* The reporting subsystem now contains Subscriber Contact information directly on the `AccountTransactions` and `AccountTransactionHistory` views.
* `AccountTransactionHistory` is now available in the OData API.


Changed
-------

* A validation error will now be returned if an Enterprise Plan is re-activated without having been activated earlier.
* Product details are included when getting scheduled subscription changes.

Fixed
-----

* An issue where calculating the next subscription with scheduled changes would not generate the correct results.
* An issue where payment demands with fees and zero priced or included additional products would fail to be generated.
* An issue in Reminders that would generate the wrong Payable Amount and Line Extension Amount when one or more allowances with non-zero VAT value were present on one of the reminders (but not in the invoice).
* Filtering of PaymentAgreements now actually filter out deactivated agreements, causing the query parameter `IncludeDeactivated` to work as intended.


Merchant Client
===============

Added
-----

* **[Preview]** Support for transferring not-billed allowances and charges to new billing accounts and between subscribers.
* **[Preview]** Scheduled Subscription changes to be executed at a later time instead of immediately as is the current behaviour (Contact support if you want to use this feature).
* Support for maintaining some of the Checkout Configuration options directly (refer to the documentation for details).
* Option to re-submit Invoices to the PEPPOL Network directly from the Merchant Client.

Changed
-------

* Extended the dashboard with values for ACV (Average Customer or Subscription Value) and CLTV (Customer or Subscription Lifetime Value).
* The dashboard now also contains a chart for outstanding invoices and invoices due.
* The layout and styling of the dashboard.
* Layout for self-service configuration.
* Better support for handling search without an assigned organization filter for multiple search views.
* Visual improvements to payment agreement related elements.
* Searching for corrections now include a textual description if available in the result for each correction.

Fixed
-----

* An issue where switching a subscription plan, when both the number of units and the fixed price were changed, would not display the correct final price.
* Removed a non-functional option to generate emails for invoice drafts.
* Prevented restarting subscriptions with a future cancellation time (it is still possible to undo/remove the cancellation).
* Error handling for cases where ordering a restart of a subscription reports failures. Previously, there was inadequate feedback to the user.


Self-Service, Sales Poster and Checkout
========================================

Added
-----

* Support for deactivating old and unused payment agreements.
* Support for paying a single outstanding invoice via Vipps and MobilePay if those payment methods are enabled. Does not require a payment agreement. Refer to the documentation for details.
* Tracking/Tracing of user interactions and events within the checkout workflow.
* Checkout configuration now includes options for setting different default subscription plans for each journey type.

Changed
-------

* It is no longer possible to remove registered cancellations on subscriptions with a 100% permanent discount, preventing unintended eternally-free subscriptions.
* Improved the error handling in checkout when Denial Orders are present on a subscriber.

Fixed
-----

* Checkout now reports configuration errors more clearly, instead of just showing a generic error message and "crashing".
* An issue where mapping users would fail in case of password reset flow being used during orders.