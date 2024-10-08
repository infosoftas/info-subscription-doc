.. _changelog-r128:

*********************
Release October 11th
*********************

Another month, and yet another release. This time around we are excited to offer support for automatic generation of subscriber contacts based on Vipps and MobilePay approval.
This will only light up in case of custom ordering processes, but we are working on supporting it in our own sales process.

Another noteworthy change is the option for enlisting Subscription Plans in a routine for preventing/reducing repeated purchases of offers/discounted subscriptions. 
This feature is highly dependant on user/subscriber identification, but will essentially prevent users from shopping between offers without ever paying the full price.

Of course we also have a list of minor improvements and bug fixes that makes day to day life better!

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Option for preventing repeat orderings of offer/discounted subscription plans. This affects both Subscription Plans and the Ordering process.
* Profile Sharing requests and related automatic subscriber contact generation for |Vipps| and |MobilePay| orders. Simplifies onboarding/checkout for subscribers buying with |Vipps| and |MobilePay|.
* A new trigger/webhook for Invoice Paid.
* New pre-calculated KPIs for Users, Invoices and Subscription Revenue in the reporting subsystem.

Changed
-------

* Crediting Payment Demands now supports crediting specific charges and allowances as well as the specific details/lines.
* Behind the scenes change of lookups related to EHF validation, the lookup now handles organizations that are not in the Peppol Directory.

Fixed
-----

* Issue where fetching MySupply VaxTransfer account configuration would ignore querying parameters.
* An issue where some details would not be recalculated when crediting and reissuing a new demand. Specifically changes in Payment Agreement would not be updated in all scenarios.
* An issue where partial payments on Enterprise Plan would be accounted even though accounting transactions are not enabled for Enterprise Plans yet.
* An issue in the reporting subsystem causing duplicate products on renewal.
* An issue where NextSubscription would be lost in the reporting subsystem if credit and reissue was done post-renewal time.


Deprecated
----------

We call out the following deprecations, the endpoints/field will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* We are deprecating the field ``TaxPercentage`` on the endpoint for creating Account Payment Demand transaction ``POST /paymentdemand/``, in favour of specifying a list of Tax Details.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* Option for rescheduling reminder creation time. Essentially extending the due date for the payment demand.
* An option for mapping multiple users to the same subscriber. This essentially corresponds to multiple owners of any subscriptions that subscriber may have.

Changed
-------

* When ordering new subscription the default Payment Method will now be adjusted based on existence of email on the subscriber contact.
* Support for overriding price per unit instead of total price when changing subscription plans on active subscriptions (with and without VAT).
* EHF/OIO are now hidden from view when not configured/available.
* **[Preview]** Editions are now shown on the Invoice details instead of dates.

Fixed
-----

* An issue where creating a user that already exists would result in an error.
* An issue where editing the dunning process would needlessly block the UI after the second step.
* An issue where Payment Method was not displayed when searching for payments.
* An issue where some older Payment Agreements on |PayEx| would not display details and transactions.


Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self service and sales poster.

Changed
-------

* Handling of default selected payment method is now dependant on whether the subscriber contact has an email address.