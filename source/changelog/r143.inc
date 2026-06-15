.. _changelog-r143:

**********************
Release June 16th
**********************

Another release before everyone starts thinking more about their vacations than about subscription management! 

This release is mostly a bug fixing release. 
Under the covers we have been hard at work on technical changes to improve average performance, as well as laying the groundwork for future features.

Have a nice summer, and as always, reach out if you have any questions or feedback!

API and Backend
===============

Added
-----

* **[Preview]** Automatic cleanup of historic data for a series of entities. Done to ensure automatic compliance with data retention rules and laws (GDPR and similar applicable regulations), and to improve performance by reducing the amount of stale data in the system. The cleanup process will run periodically and remove data that is older than a certain threshold, while ensuring that necessary data for reporting and auditing purposes is retained. This was previously a manual process to be implemented by the tenant.
* The Invoice endpoint now includes filtering on multiple states using `OR` semantics.

Changed
-------

* **[Preview]** Tailor made subscription plans now support inline chain definitions.
* Vipps and MobilePay agreements include deactivation time.
* Reporting now adjusts subscriber order information pro-actively on all orders regardless of payment method. Previously this was only done for Vipps and MobilePay orders.

Fixed
-----

* **[Preview]** Payment Matching policies now correctly handle multiple matching states.
* An issue where the synchronization of Organizations and Products would fail in some cases, leading to missing/invalid data in reports.
* An issue where rescheduling a Payment Demand Reminder would NOT actually reschedule the due date, but only the processing date.
* An issue where updating a cancellation time for a subscription would not rerate it, nor credit the outstanding payment demand, which could happen if the subscription was originally cancelled at the end of the billing period.
* An issue with the Invoice endpoint where it would not respect input time zones for the date filtering fields. These fields are deprecated and better served with the Analytics API, but now they will at least work as intended.
* Multiple issues with payment matching, discovered by the introduction of policies.
* An issue in reporting where allowance transaction would not be closed when consumed on a reminder.
* An issue in reporting where some account transactions would lose tax breakdown information.
* A very rare edge case issue where subscriptions would not be updated with new subscriber information during orders.

Deprecated
----------

These items will be removed in a future release.

* The Map User API endpoint in the simplified Order API is now deprecated, and removed from the reference documentation. This endpoint was used to map user identities during subscriber creation and order completion. The functionality has been replaced with a more streamlined approach.
* Purchased Additional Products in the SubscriptionPlan object will be removed in a future release (Products with IncludedInPlan = false). They can be accessed via the `PurchasedAdditionalProducts` property on the Subscription object instead. This change was made to better separate the concept of products included in the plan and products that were added on top of the plan.

Merchant Client
===============

Added
-----

* **[Preview]** Option to configure tailor made Subscription Plans. This allows merchants to create custom plans for specific subscribers, with a tailored set of products and pricing. This is useful for handling special cases that do not fit into the standard plans, such as one-off offers or grandfathering existing subscribers into legacy plans.

Changed
-------

* Multitude of minor adjustments to the UI 

  * Alignment/Styling for Invoice Contact button in the subscription view.
  * Adjusted scheduled plan changes to make it more clear that they are scheduled and not active.
  * Layout corrections for the price adjustment process.
  * Filtering for configuring 'next-best-offer' in checkout.
  * Default sorting on Subscriber list/search view.

* Multitude of text and language adjustments to make the UI more clear and consistent.
* Improved user-feedback and performance for actions related to Subscription Plan changes when validating and calculating updated prices specifically.

Fixed
-----

* An issue where loosing the authenticated state would lead to a blank page with no indication of what went wrong. This is now handled with a prompt to re-authenticate.
* An issue where changing subscriber information would sometimes prompt for a change of payment method when an Invoice Contact was associated.
* Removed the option for registering payments on a draft/open invoice.
* Removed the option for crediting already settled Enterprise Plan Payment Demands, as this is not a supported flow and can lead to confusion.
* An issue where crediting and reissuing an Invoice would lead to an error message in some scenarios.
* An issue where adding a new order would be blocked due to an invalid handling of an expired Denial Order.
* An issue where the invoice filtering "eye icon", would filter ALL invoices in some cases.


Self-Service, Sales Poster and Checkout
========================================

Added
-----

* Added support for displaying scheduled subscription plan changes, similar to the subscription view in Merchant. This allows subscribers to see upcoming changes to their subscription plan, such as a scheduled downgrade or upgrade, and better understand their subscription lifecycle.

Changed
--------

* Additional state handling improvements for Vipps and MobilePay in checkout when the user navigates back and forth.

Fixed
-----

* An issue where 'next-best-offer' in checkout would be shown multiple times.
* An issue where invoice lines on subscription with editions would show the time range and not the edition numbers.
* An issue where one-of payments of reminders would display the original invoice amount instead of the reminder amount (i.e. without the added fees or reductions by allowances).
* An issue in checkout where invoice fees was not shown in the order summary.