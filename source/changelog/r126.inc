.. _changelog-r126:

*******************
Release August 13th
*******************

Hope you all had a nice summer!
The |projectName| dev team is back from our vacations, but we haven't been completely idle during the summer, so here is a new release. 
The most significant improvements are related to Editions, but also contains a series of minor improvements/enhancements in other areas.

We will hopefully be back with another release in september.


API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* **[Preview]** Preliminary support for letting payment stops be defined by schedules instead of a historic filter.
* Support for configuring renewal texts on template plans to differentiate between the initial offer and the running subscription.
* It is now possible to assign some payment agreements to Enterprise Plans, enabling `EHF`, `OIO`` and `EMail`` in addition to the default `Invoice`.
* Added support for non-recurring payments for |Vipps| and |MobilePay|, in their terminology called an `EPayment`, this open up scenarios for simpler one-off payments of invoices, reminders, filling up pre-paid accounts, or simply paying for single item purchases.

Changed
-------

* Extended User Authorization events to cover a few more cases than previously.
* Calculation of demand scheduling times for |BetalingsService| to produce valid times for the end of each month.
* Improved handling of invalid organization numbers and phone numbers for the |eFaktura| scanning process, enabling even more subscribers for |eFaktura| agreements.

Fixed
-----

* An issue where filtering of demandschedules on some properties would ignore the filter value.
* An issue where subscription chaining would not recalculate product list prices, causing invalid price adjustments in cases where list prices change during the chain lifetime.
* An issue in the reporting subsystem where a cyrillic char was used instead of an english char, causing invalid OData lookups for Subscriber Contacts.
* **[Preview]** An issue where list price calculations were invalid for Edition frequencies.
* **[Preview]** An issue where it was not possible to update/change number of editions on a template Subscription Plan.


Deprecated
----------
We call out the following deprecations, the endpoints/field will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* The PaymentProvider type with the Name `PayEx` is being removed, in favour of the name `SwedbankPay` this is purely a name/branding related change.
* We are deprecating the field ``TaxPercentage`` on the endpoint for creating Account Payment Demand transaction ``POST /paymentdemand/``, in favour of specifying a list of Tax Details.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* **[Preview]** Support configuring subscriptions with Editions instead of time.
  * Products can be configured with one or more Edition calendars.
  * Template SubscriptionPlans can be created with a number of Editions.
  * Billing Plans can be configured to work with Editions.
  * Orders can be assigned with a custom number of Editions.

* Additional columns included when downloading the Economic Journal.
* Options for choosing existing mandates from |BetalingsService|, |AvtaleGiro| and |eFaktura| during order creation.

Changed
-------

* Improved invoice and invoice contact search with changed column order, additional columns and option to sort on more columns.
* When cancelling a subscription and removing the cancellation time, the reason field will now be cleared as well.
* Improved the validation/error message when adding a shared user that is also an administrative user in the underlying IdP.

Fixed
-----

* An issue with the date filtering for recurring deliveries.
* An issue that would display an invalid total for the Economic Journal for Enterprise Plan accounts.
* An issue where Currencies were predefined instead of being configurable (as they were some places already).
* **[Regression]** An issue where deleted users would cause the list of shared and domain users to not be displayed.

Removed
-------

* Removed support for adding a custom "source" on all the various payment registration views (it was removed on some views but not all).


Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self service and sales poster.

Added
-----

* **[Preview]** Support for ordering subscriptions using editions instead of time.
