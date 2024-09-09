.. _changelog-r127:

**********************
Release September 11th
**********************

Autumn is here and we are ready with a new release, mostly with a bunch of minor bug fixes. 
The largest new feature in this release is a new payment flow for |SwedbankPay| and an Subscription Plan rule to help deal with subscribers repeatedly shopping only for offers and discounts.

Under the covers we have renewed and upgraded several internal and external APIs and performed various technical changes to improve security, performance and resiliency.


API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Support for creating |SwedbankPay| transactions without agreements. Allows for workflows that pays single invoices and reminders.
* Added a new variation of Denial Orders where Subscription Plans can be configured with a rule that injects temporary Denial Orders based on time parameters. Used to prevent "offer/discount" shoppers, while still allowing them to buy full priced subscriptions.
* New column for cancellation registration time in the reporting subsystem.
* **[Preview]** Billing and Subscription support for adjusting end times for edition based subscriptions.

Changed
-------

* General VAT in Finland increased to 25.5%.

Fixed
-----

* An issue with Distribution Innovation where adding source to subscriber contact would not be used in communication with the DI service.
* An issue where the "Forget Me" action would not sufficiently anonymize the Subscriber Contact on historic invoices.
* An issue where an "invalid" timestamp for subscriptions with Editions could cause ambiguity about the end of a subscription or the start of a new one (overlaps).
* **[Preview]** An issue where scheduled payment stop would be processed at the wrong time.
* **[Preview]** An issue where billing would prorate an Edition based subscription if cancelled before the first Edition was "delivered".

Removed
-------

* As previously announced the PaymentProvider type with the Name `PayEx` has been removed, in favour of the name `SwedbankPay`. This is purely a name/branding related change.

Deprecated
----------

We call out the following deprecations, the endpoints/field will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* We are deprecating the field ``TaxPercentage`` on the endpoint for creating Account Payment Demand transaction ``POST /paymentdemand/``, in favour of specifying a list of Tax Details.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* UI support for maintaining reporting groups for grouping products in analytics and reports.
* **[Preview]** Added support for displaying from/to Editions instead of from/to date for subscription periods.

Changed
-------

* Event logs now display username and application name where possible.
* Adjusted the modal dialog for crediting enterprise plan payment demands to make it more like the dialog for other payment demands.


Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self service and sales poster.

Added
-----

* **[Preview]** Added support for displaying from/to Editions instead of from/to date for subscription periods.

Changed
-------

* Support for the new workflow for |SwedbankPay| transactions, resulting in perceived performance improvements during orders.