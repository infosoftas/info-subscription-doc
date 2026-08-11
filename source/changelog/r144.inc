.. _changelog-r144:

**********************
Release August 12th
**********************

Summer vacations are officially over, and we are back with a new release. 
Since we have been on vacation ourselves, this release is mostly a bug fixing and maintenance release.


API and Backend
===============

Added
-----

* New endpoint for scheduling subscription cancellations (as opposed to immediate cancellations). The difference is mainly that the cancellation action is now scheduled for execution at a later time, meaning side-effects won't occur until later. It also allows cancellations to happen outside the current active period.
* SwedbankPay agreements that have been deactivated now include a deactivation time.

Fixed
-----

* An issue in billing where a non-sequential reminder setup would cause reminders to be silently skipped. Now they are handled as if they were sequential. New reminder configurations have long been sequential, but some older configurations may still be non-sequential.
* An issue where reminder due dates would be incorrect for Enterprise Plans for a rare edge case.
* An issue with processing of schedule delivery changes would use the wrong timezone.
* An issue that would lead to a user authorization not being removed during Subscription Deletion.

Deprecated
----------

These items will be removed in a future release.

* The Map User API endpoint in the simplified Order API is now deprecated, and removed from the reference documentation. This endpoint was used to map user identities during subscriber creation and order completion. The functionality has been replaced with a more streamlined approach.
* Purchased Additional Products in the SubscriptionPlan object will be removed in a future release (Products with IncludedInPlan = false). They can be accessed via the `PurchasedAdditionalProducts` property on the Subscription object instead. This change was made to better separate the concept of products included in the plan and products that were added on top of the plan.

Merchant Client
===============

Added
-----

* Scheduled subscription cancellations.

    * Displaying existing schedules.
    * Registering new scheduled cancellations.

* When changing an active subscription plan with an Invoice Contact, the user is now prompted to carry on the contact to the new/changed subscription.
* Display an in-progress information view when preparing to edit an invoice for an Enterprise Plan (as opposed to no feedback at all).
* Exporting shared users, now also includes the main/owning user.

Changed
-------

* Input focus on the confirmation dialog when adjusting subscriber information.
* Sorting of the permanent discount list when ordering new subscription.
* The Payment Agreements view is now visually split into two parts to better separate the active agreements from the inactive ones. 


Fixed
-----

* Missing "Enter/Return" key handling for the send Invoice, Reminder and Credit Note buttons.
* An issue where Payment Agreements would not be displayed correctly when no remote status was available.
* An issue where some invoices would display the previous Subscription Plan Name instead of the one actually invoiced.
* Translations were fixed in the Subscription view.
* An issue where changing subscription plan would try to keep price overrides even though the target plan did not support it.

Self-Service, Sales Poster and Checkout
========================================

Added
-----

* Scheduled subscription cancellations.

    * Displaying existing schedules.
    * Registering new scheduled cancellations.

* **Preview** New checkout journey type for trial subscriptions. Requires subscription plans to be marked for automatic cancellation.
* **Preview** Support for SmartResponse (https://smartresponse.dk/ ) activity tracking in checkout.

Changed
-------

* Now prevents adding new shared users for a subscriptions with a future cancellation.

Fixed
-----

* An issue where the "Pay with Vipps" or "Pay with MobilePay" buttons would be displayed on a credited Invoice.
* An issue where the same price would be shown twice during checkout.
* An issue where it was possible to start an order on an expired template plan, which would not complete, now the user is presented with an error message instead.