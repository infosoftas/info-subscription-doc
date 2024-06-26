.. _changelog-r125:

******************
Release June 26th
******************

Another summer is approaching, and this will be the last release before summer holidays sets in.

This release contains a new UI for non-recurring/manually added transactional invoices, similar to what you know from regular ERPs, as well as the usual bug fixes and minor improvements.

We will back again with a new release, most likely during August.

Happy holidays from the dev team at Infosoft.


API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Support for scheduling Payment cancellations/stops and related APIs to manage these schedules, including a rescheduling option.
* An option to configure a cancellation proration policy, with support for automatic billing based on the configured policy. 
  Previously changes in a subscription period would always be prorated, now it is configurable with the default still being to prorate as previously.
* The reporting subsystem for subscriptions now includes a reference to the previous subscription as well as a source of what generated the current subscription. Useful for generating a renewal timeline for instance.

Changed
-------

* Calendar creation now requires start and expiry on exception calendars, as well as the option to specify active state during creation.
* Currency aware rounding of charges and allowances generated during automatic proration. Previously all charges and allowances would be rounded to 4 decimals. For most cases the new behaviour translates to rounding to 2 decimals. As with existing rounding practices, rounding is done using Bankers Rounding.
* Improved support for updating Card Metadata when agreements on Swedbank Pay are updated because of Network Tokenization, i.e. when a new payment card has been used transparently.
* |Vipps| and |MobilePay| orders with 8 digit phone numbers will now generate a draft agreement without the phone number pre-initialized in cases where the number is deemed invalid by VippsMobilePay. Previously the orders would be rejected with a rather unintelligible error message.

Fixed
-----

* **[Hotfix]** An issue where no final demand would be generated for subscription plans without tax details.
* **[Hotfix]** An issue where automatic settlement would be aborted for |Vipps| and |MobilePay|, if the original payment demand was due before 10:00 CET and the payment was received on the last day of retries (on the 8th day).
* An issue related to rescheduling of reminders that would lead to the new schedule not being applied correctly.
* An issue where it was not possible to create |AvtaleGiro|, |AutoGiro| and |BetalingsService| mandates on the same subscriber.

Removed
-------

* As previously announced the endpoints for crediting, ``/paymentdemand/{id}/credit/completely`` and ``/paymentdemand/{id}/credit/partially``, has now been removed. 
  Our telemetry indicates it has not been in use for some time now.
* The use of the `PayEx` name for new agreements using `SwedbankPay`.

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

* An option to select Subscriber Account matching during manual payment registrations. The primary use case is extraordinary account payments that the subscriber wants to use for deductions later.
* An options to connect already completed payments to a subscriber account, useful for cases where a payment was incorrectly completed without associating it with an invoice.
* **[Preview]** A new audit log/overview for subscribers identifying important operations on the selected subscriber.
* **[Preview]** Option to register calendars for use with edition based billing.
* **[Preview]** A new view for manually creating transactional/non-recurring payment demands/invoices. Contact Support ({SUPPORTPAGE}) if you want to participate in the preview.

Changed
-------

* OIO and EHF Invoicing as the payment method(s) is now only available for tenants where it is configured.

Fixed
-----

* An issue where it was not possible to define a decimal value for price overrides.
* An issue where the Zip Code would not be automatically filled out on Subscriber Contacts when using the Distribution Innovation Address Helper.
* An issue where the available currencies shown would include more currencies than configured. Specifically NOK would always be displayed.


Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self service and sales poster.

Fixed
-----

* An issue with input validation during registration temporary delivery changes.
* An issue where the Payment Agreement overview would include previous subscription periods when summarizing the number of active subscriptions where it is applied.