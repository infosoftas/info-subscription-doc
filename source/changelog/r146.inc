.. _changelog-r146:

****************************
2026 Release October 20th
****************************

Another autumn release with a refreshed checkout UI and several backend improvements.

Hope you enjoy the new features! As always, we welcome your feedback and suggestions.


Checkout UI Refresh
===================

We are launching a refreshed UI for the checkout process. It aims to provide an even more neutral and visually appealing experience for users, without getting in the way for your company's branding.
It also enhances the signup and signin experience, so the transition between solutions is even more transparent for most users.

We have incorporated multiple user feedback points to improve the overall checkout experience, and while we cannot provide a solution that is ideal for everyone, we are committed to making it more intuitive and user-friendly, and hope this is a step in the right direction for everyone.

INFO-Subscription SDKs
======================

We are launching the first versions of the INFO-Subscription SDKs, providing developers with ready-to-use packages that simplify integrating with the INFO-Subscription API and include authentication building blocks. 
The SDKs are available for JS/TS on https://www.npmjs.com/package/@infosoftas/info-subscription-ts and for dotnet/C# on https://www.nuget.org/packages/Infosoft.Info.Subscription.Dotnet.

The source code is available on GitHub at https://github.com/infosoftas/info-subscription-sdk. Feel free to contribute and submit issues or pull requests.

API and Backend
===============

Added
-----

* Support for scheduled Subscription Pause, allowing users to plan temporary pauses in their subscriptions. Essentially pauses are implemented as scheduled cancellations that take effect automatically at the specified time, followed by a subsequent resumption at a later date.
* Unit Price and Quantity are now included in the Account Transaction API responses.
* It is now possible to filter Enterprise Plans by Organization Id.

Fixed
-----

* An issue where Payment Type based Fees for orders would break for Mollie.
* Minor resilience improvements for Mollie related to capture reconciliation of payments.
* An edge case issue where malformed Reminder Settings would cause dunning to not progress if there were "holes" in the reminder sequence schedules.
* An issue where re-issuing account invoices would lose their configured invoice fee.
* An issue where cancelling Additional Products in the same period as they were added would not correctly be reflected for the next billing cycle.
* An issue where it was not possible to create a non-zero amount Vipps or MobilePay agreement without an Initial Charge. For instance a campaign with 1 week free, then 100 NOK a month after that.
* An issue where it was possible to schedule a cancellation on a historic subscription, now a validation prevents this.


Changed
-------

* Allow client generated Id for Vipps, MobilePay and SwedbankPay agreements, simplifying idempotency checks and streamlining the agreement creation process as much as possible between PSP integrations.
* The `SubscriptionCancelled` event is now raised only when the cancellation has been processed entirely. Previously a small window existed where the event could be raised before the cancellation was fully completed, potentially causing inconsistencies in event handling for third parties not aware of this window.
* In the previous release, we introduced conversion of charges with type `Purchase` into `AdditionalProductDetailLines` when billing. This had a few consequences in how they were handled in terms of being reverted to the billing account during credits. With this release, such converted detail lines are now reverted back into charges during credit (following the same logic as other charges and allowances).


Deprecated
----------

These items will be removed in a future release.

* The Map User API endpoint in the simplified Order API is now deprecated, and removed from the reference documentation. This endpoint was used to map user identities during subscriber creation and order completion. The functionality has been replaced with a more streamlined approach.
* Purchased Additional Products in the SubscriptionPlan object will be removed in a future release (Products with IncludedInPlan = false). They can be accessed via the `PurchasedAdditionalProducts` property on the Subscription object instead. This change was made to better separate the concept of products included in the plan and products that were added on top of the plan.

Merchant Client
===============

Added
-----

* **[Preview]** Support for onboarding Mollie accounts/profiles from the Merchant.
* It is possible to write-off payment demands without crediting them (marking them as bad debt/loss).
* When searching/listing invoices it is now possible to filter by the "Write off" status.
* Subscriber Ledger displays write-off entries as its own type.

Changed
-------

* Orders with custom price overrides now use sliders for tax and quantity instead of checkboxes, matching the layout used when changing packages.

Fixed
-----

* A spelling mistake when configuring webhooks for one of the event types.
* An issue where changing subscriber contact would revert to the original payment agreement.
* An issue where registering scheduled cancellations would be added with type `Immediate` instead of `OnRenewal`.

Self-Service, Sales Poster and Checkout
========================================

Added
-----

* Refreshed the UI for checkout.
* In self-service adding new payment agreements to a subscription is now bounded by the subscription instead of a global agreements list. Prevents confusion on where the agreement is being added. The list of agreements still shows all agreements.

Changed
-------

* Moved configuration errors for Payment setup to warnings in the console to allow multi-country configurations without blocking the user during checkout.