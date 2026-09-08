.. _changelog-r145:

**********************
Release September 16th
**********************


**[Preview]** Mollie as a PSP
=============================

We are launching a new PSP integration, enabling the use of Mollie as a payment service provider within |ProjectName|. 
This allows merchants/tenants to accept payments through Mollie, providing a seamless and secure payment experience for their customers.

With the Mollie integration |ProjectName| now supports card payments in a wider range of countries and currencies, and with Google Pay and Apple Pay as additional payment options.

The integration has full support for:

* One-Off and Recurring Payments using Cards (including Google Pay and Apple Pay)
* Refunds
* New Subscription Orders via Checkout
* Mandate (Agreement) management via Self-Service

Tenants require a Mollie account to enable this integration.

The feature is still in preview, and may undergo further changes before its general availability.
Contact support if you want to know more.


API and Backend
===============

Added
-----

* **[Preview]** Support for Mollie as a PSP. Refer to the main announcement further up for details.
* Support for writing off payment demands and invoices without issuing a credit note. Effectively marking them as "bad debt".
* Support for generating `Summary` ledger entries when consolidating transactions due to history limit cleanup (Automatic GDPR compliance).
* Support for Balance/Final Demands to be issued via Email payment agreements, as well as automatic creation of an Invoice agreement if no applicable agreement exists.

Fixed
-----

* An issue where Charges and Allowances registered directly on an account via the API would ignore/discard the Quantity when being billed.
* An issue where deleting a future subscription would not always cleanup Distribution Innovation records associated with it.
* An issue where discount rules for orders would not be applied when using chains.
* An issue where plan Units and ProductTaxDetails Quantity would be 0 in the reporting model.

Changed
-------

* Subscriber Contact information pulled from Vipps or MobilePay will now strip newline characters.

Deprecated
----------

These items will be removed in a future release.

* The Map User API endpoint in the simplified Order API is now deprecated, and removed from the reference documentation. This endpoint was used to map user identities during subscriber creation and order completion. The functionality has been replaced with a more streamlined approach.
* Purchased Additional Products in the SubscriptionPlan object will be removed in a future release (Products with IncludedInPlan = false). They can be accessed via the `PurchasedAdditionalProducts` property on the Subscription object instead. This change was made to better separate the concept of products included in the plan and products that were added on top of the plan.

Merchant Client
===============

Added
-----

* **[Preview]** Support for Mollie as PSP. Refer to the main announcement further up for details.
* Support for adding scheduled future cancellations effective after the current subscription period.
* Support for configuring Self-Service and Checkout integration with Google Tag Manager. Requires an existing GTM container.
* Support for new ledger transaction types `Summary` and `WriteOff`.
* Support for displaying new Payment Demand and Invoice state for `WriteOff`.

Changed
-------

* Default cursor focus has changed for multiple search views, providing a better default experience.
* Streamline logo handling for payment agreements.
* For ADB2C Users without a valid display name, the name is now hidden instead of displaying the `Unknown` placeholder.

Fixed
-----

* An issue where creating a new Invoice Contact would keep `Email` as the payment agreement, even when the contact had no email address.
* An issue where it was not possible to collapse expanded feature groups when configuring Checkout and Self-Service behaviour.
* An issue where the counter was invalid for deactivated Payment Agreements.
* An issue where the Dunning Process would not be saved if `SettlementPolicy` is given with a fixed amount limit.

Self-Service, Sales Poster and Checkout
========================================

Added
-----

* **[Preview]** Support for Mollie as PSP in Self-Service, and Checkout. Refer to the main announcement further up for details.
* Support for displaying new Payment Demand and Invoice state for `WriteOff`.
   

Changed
-------

* Streamline logo handling for payment agreements.
* For ADB2C Users without a valid display name, the name is now hidden instead of displaying the `Unknown` placeholder.


Fixed
-----

* An issue where the max number of shared/connected users was too high.