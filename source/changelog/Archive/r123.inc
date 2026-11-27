.. _changelog-r123:

***********************
Release April 15th 2024
***********************

"ABC 123", this release numbers 123 since the inception of |projectName|, as so often before with bug fixes and minor improvements spread throughout the platform.


API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Business audit for crediting of payment demands.
* **[Preview]** VippsMobilePay API adjustments for Orders and Agreements with support for MobilePay Denmark and Finland.
* **[Preview]** Proration support for Edition/Issue based frequencies on cancellations.
* Country Code for VippsMobilePay Account Configuration, mostly affects branding (|Vipps| or MobilePay) today.

Changed
-------

* Deliveries are no longer generated for subscriptions which are entirely in the past (mostly affects migrations).
* Upon cancellation of a Subscription, any scheduled changes are now removed automatically. Restarts will have to reschedule changes. This only affects cancellations not plan changes.
* It is no longer possible to add an Invoice Contact or change Payment Agreement on Subscription belonging to an Enterprise Plan. It had no effect previously, but was the cause of some confusion.
* Up to date product list prices are now calculated when getting Subscription Plans.

Fixed
-----

* An issue where an immediate change of SubscriptionPlan would not supply the correct cancellation type to the subscription.
* An issue where crediting and reissuing of an Enterprise Plan demand would sometimes lead to a missing period for new orders yet to be billed.
* An issue where a reminder on an Enterprise Plan would be reported to belong to the latest issued invoice on the same plan, instead of the one actually being reminded.
* An issue where Enterprise Plan demands would be generated a day off for cases near the DST switch. Now it correctly calculates based on the configured timezone for the issuing organization.
* An issue where deliveries might be split even though no address change occurred. In turn this would lead to surplus notifications to Distribution Innovation or other third parties.
* An issue where it was impossible to delete Denial Orders in case there were multiple registrations on the same subscriber.
* Fixed an edge case where the end calculation for Subscriptions would be invalid if the end time was supposed to be exactly on the switch to DST.
* **[Preview]** An error with processing of |BetalingsService| mandates and payments during file import.

Deprecated
----------
We call out the following deprecations, the endpoints/field will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* We are deprecating the endpoints ``/paymentdemand/{id}/credit/completely`` and ``/paymentdemand/{id}/credit/partially`` in favor of ``/paymentdemand/{id}/credit`` endpoint.
* We are deprecating the field ``TaxPercentage`` on the endpoint for creating Account Payment Demand transaction ``POST /paymentdemand/``, in favour of specifying a list of Tax Details.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* Option to delete payments that have yet to be completed.
* Option to sort subscriptions on Enterprise Plans based on number or name.
* Filtering for subscriptions on Enterprise Plans.
* Requirement for additional information based on chosen Payment Agreement, specifically for Email and EHF.
* Quick link for unmatched payments from the subscriber payments view.
* **[Preview]** View to configure |BetalingsService| integration.
* **[Preview]** Subscriber Payment Agreement view for |BetalingsService|.

Changed
-------

* During Cancellation: Removed checkbox for calculating contract fee if no contract is present.
* Payment Management is redesigned with a new tab order and refreshed grids/list.

Fixed
-----

* An issue where it was not possible to credit a payment demand without reissuing for AvtaleGiro, AutoGiro and BetalingsService.
* An issue where it was was not possible to credit AND reissue Account Payment Demands.
* An issue where listing domain users would fail in case one of the underlying users was removed from the source.


Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self service and sales poster.

Added
-----

* **[Preview]** View for |BetalingsService| payment agreements.


Fixed
-----

* An issue where existing shared users ordering a new subscription would lead to error messages.
* An issue where adding the last shared users was not allowed (counter error).