.. _changelog-r147:

**************************
2026 Release December 2nd
**************************

This release is big, with several major updates and features, as well as a long list of minor improvements, enhancements and fixes across the board.

Highlights include:

* A WordPress plugin, making it easy to put WordPress content behind your |ProjectName| subscriptions.
* A refreshed self-service UI, providing a unified look and feel with the checkout design.

Hope you enjoy the new features! As always, we welcome your feedback and suggestions.

Merry Christmas and a Happy New Year! 

See you with a new release early in 2027.


Self-Service UI Refresh
=======================

The previous release contained a major refresh of the checkout UI. 
This time around, self-service has gotten the same treatment. 
A new refreshed UI has been implemented inline with the checkout design to provide a unified look and feel.

It aims to provide an even more neutral and visually appealing experience for users, without getting in the way for your company's branding.

This is a big change so expect some adjustments and refinements as we gather feedback.
Feel free to send us your feedback so we can continue to improve the experience.


INFO-Subscription Access WordPress Plugin
=========================================

We are launching the first version (v0.1.0) of the "INFO-Subscription Access" WordPress plugin, allowing you to restrict access to articles on your WordPress site based on your subscribers' |ProjectName| subscriptions.

Visitors sign in with their |ProjectName| account through your tenant's Azure AD B2C sign-in using OpenID Connect, so no WordPress user accounts are needed for your subscribers. The plugin uses the id_token form_post flow and does not require a client secret.

Each article can be configured with one of the following access modes:

* **AllAccess** - the article is available to everyone.
* **UserLoggedIn** - the article is available to all signed-in users.
* **SelectedProducts** - the article is available to signed-in users with access to any one of the selected products, based on the ``extension_Products`` claim.

Visitors without access are shown a teaser with links to sign in or subscribe, or are redirected to a subscribe page.

Editors pick the products for an article from a list loaded from the |ProjectName| API. To load the list, an administrator signs in interactively using the authorization code flow with PKCE. Tokens are never stored by the plugin, and product IDs can also be entered manually.

The plugin requires WordPress 5.6 or newer, PHP 8.0 or newer and HTTPS. 
It is not yet available in the WordPress.org plugin directory; instead, an installable ``infosub.zip`` is attached to the v0.1.0 release on GitHub at https://github.com/infosoftas/info-subscription-wordpress. The plugin is licensed under the MIT licence.

JavaScript/Standalone Soft-Access Plugin
----------------------------------------

We are also introducing a proof-of-concept implementation of a JavaScript based soft-paywall/soft-access plugin.

You can find the details about it on the GitHub repository at https://github.com/infosoftas/info-subscription-paywall 


API and Backend
===============

Added
-----

* |Mollie| Payments now support an `Accounting` reference carrying object for payments similar to the other PSP integrations.
* Added new webhook event for subscription cancellation removal, and at the same time restoring the behaviour of Subscription Cancelled events to mean cancellation registration time regardless of invoked endpoint.
* The MCP server now supports the MCP v2 protocol, and adds support for prompting users for tenants if missing in the tool selection.
* The MCP server now exposes tools for authorization mappings, allowing users to troubleshoot and/or identify potential authorization issues.
* All new orders for subscribers with an e-mail address will now create a corresponding payment agreement with type Email, regardless of the payment method used. Allows fallback to Email instead of Invoice in more cases.
* Scheduled Cancellations are now surfaced in the Reporting subsystem.
* Quantity is now a property on Payment Demand Details for reporting purposes, allowing easier aggregations.
* It is now possible to navigate directly to Invoices from PaymentDemands using the OData API. Simplifies cross queries where details are expanded on the Demand but the actual result sought after is on the Invoice.
* Added validation when registering a Scheduled plan change, if an existing scheduled cancellation is in place the change is rejected. So it is not possible to order an upgrade or downgrade while a future cancellation is in place. The reverse is NOT true, meaning it is possible to regret a change and decide to cancel the subscription without first removing the change.
* |Vipps| and |MobilePay| initial charges can now carry an optional future Due Date.

Fixed
-----

* Initial Charges using |Vipps| and |MobilePay| for future-dated subscriptions are now charged at their due time and not immediately.
* An issue where missing data would lead to errors for eFaktura, a fallback description is now used to let the eInvoice be processed.
* An issue where deactivated Agreements could be selected for automatic agreement fallback, fallback is invoked in cases where out of band deactivations forces an agreement to become inactive. The selection mechanism would not always verify if the agreement selected was active before switching.
* Fixed an issue on payment demand details where the Quantity was always set to 1 regardless of actual input quantity.
* Fixed an issue with consumption proration calculations during transition from DST to "standard" time. Calculations were affected when the boundary was exactly on the DST transition date.
* An API documentation issue where the account transactions endpoint documented an incorrect response type.
* [Hotfix] Fixed an issue where Start Time was not considered in case of inline Subscription Plans on an order.
* An issue where the ledger summary transactions were not correctly carrying subscriber information in case of multiple billing accounts.

Changed
-------

* The Simple Order API now wraps the order completion process in an entirely async manner, removing the artificial sync over async behaviour.
* The error messages for Vipps and MobilePay with unsupported currency has been improved to reflect supported currencies.
* Streamlined the handling of text when converting PaymentDemand Details to Invoice Lines so that text is now processed identically regardless of Detail Type (Subscription, Direct Transaction, Order, Product Purchase, Billing Account Transaction).
* The GDPR Right to be forgotten implementation is now slightly changed so that Invoice documents are no longer completely anonymized, bringing them in line with regulatory requirements superseding GDPR rules.
* Attempts to create Email Payment Agreements for subscribers with an existing agreement will now re-use the existing agreement instead of creating duplicates, depending on the input supplied.

Removed
-------

* The TemplatePlan rule for percentage discounts based on number of products selected in dynamic packages has been removed. It was never used and is causing headaches for a new feature we are working on.
* The last remnants of the PriceTypeId has been removed. It has not been used for years, but a few fields were still present with static values. These are now removed.

Deprecated
----------

These items will be removed in a future release.

* The Map User API endpoint in the simplified Order API is now deprecated, and removed from the reference documentation. This endpoint was used to map user identities during subscriber creation and order completion. The functionality has been replaced with a more streamlined approach.
* Purchased Additional Products in the SubscriptionPlan object will be removed in a future release (Products with IncludedInPlan = false). They can be accessed via the `PurchasedAdditionalProducts` property on the Subscription object instead. This change was made to better separate the concept of products included in the plan and products that were added on top of the plan.

Merchant Client
===============

Added
-----

* Merchant Readiness Checklist - A new view providing merchants with a quick status of whether they are ready to start selling subscriptions. Use it when you want to set up a new Organization/Sales Unit and want to ensure everything is in order.
* Tailored Subscription Plans can now also be used when changing subscription plans on a running subscription.
* Added UI for registering new Subscription Cancellation event webhooks.
* Removed Template Plan Rule for percentage discounts based on number of products selected in dynamic plans.

Changed
-------

* The Invoice Search has been reworked and now fully utilizes the underlying OData filtering capabilities, overall providing a much smoother experience. Filtering is done via filtering handlers in the column headers.
* The KPI dashboard for Invoices now carries links to the Invoice Search to list the relevant invoices.
* Managing payments has changed default sorting when listing invoices during matching.

Fixed
-----

* A counting issue when adding users to a subscription plan. Previously Additional Products purchased after the fact was not included.
* An issue where modifying an existing Subscription Plan or Template Plan would not pre-fill Additional Products correctly.
* [Hotfix] An issue where it was not possible to consume account balance when ordering using Tailored Subscription Plans.
* An issue where it was possible to schedule subscription changes directly on subscriptions in an Enterprise Plan. This is now removed.
* An issue with configuring Cancellation Reason Codes where it was not possible to add new codes.
* An issue where scheduled cancellations on a subscription was submitted with an invalid processing type in some edge cases.
* An issue where it was possible to attempt a Reversal on a failed Swedbank Pay transaction. The reversal would fail, but the option is now removed.

Self-Service, Sales Poster and Checkout
========================================

Added
-----

* The JS-Order-SDK and the Checkout has been updated to support the no-wait mode for the Simple Order API, providing better overall feedback in cases where order processing takes a long time.
* Verification token process in the checkout to prevent hijacking local orders.
* The self-service and checkout now comes with new info-subscription branded domains. Refer to the documentation for details.
* CDN hosting for fast delivery of static assets in the self-service and checkout across different regions.

Changed
-------

* The Checkout now provides clearer feedback when an order is being processed in no-wait mode, reducing confusion for end-users during longer processing times.
* Swedbank Pay payments now does a full redirect in checkout, it improves the overall stability and removes a class of security and compatibility issues related to the iFrame mode.

Fixed
-----

* A colour scheme selection error in the login/signup process.