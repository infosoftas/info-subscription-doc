.. _changelog-r120:

**************************
Release January 4th 2024
**************************

Happy new year to everyone.

We start the new year with a new release. This one mostly contains bug fixes and minor adjustments to existing behaviours.


API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Changed
-------

* The integration setup for Distribution Innovation has been simplified so that URLs are now determine automatically during deployment and configuration of the URL is no longer possible.
* Multiple improvements to the address splitting routine for automatic address lookups using Kartverket. Improves precision for multiple edge cases such as names being partial matches in longer names.
* |eFaktura| Scanning now skips using known invalid phone and zip codes during agreement lookups.
* If a subscription has an invoice contact, it will no longer be automatically switched to an |eFaktura| payment agreement.
* Updating out-of-band Payment Agreements (such as |eFaktura| and |AvtaleGiro|) now triggers automatic switch of Payment Agreements on running subscriptions.

Fixed
-----

* An issue where order demand schedules would remain even if the resulting subscription was deleted.
* An issue where payment stop would not act on the first subscription period.
* Marking billing account transaction as included in the ledger in all cases.
* An issue where some charges and allowance transactions would not be reverted during automatic crediting (from cancellations).
* An issue where the API did not populate tax details on Enterprise Plan payment demands.
* An issue leading to multiple |eFaktura| Agreements with the same identifier.
* An issue where invalid EHF files would be produced when a transaction did not have an End Time.
* An issue where the first file to be imported after a release or catastrophic failure would hang until processed manually.
* An issue where scheduled Subscriber contact changes would include a blank newline at the end.

Removed
-------

* It is no longer possible to do file based settlement for |Vipps| charges. It has not been exposed in the UI for some time, and has been replaced by the automatic API based settlement.

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

* UI Support for additional event types on the trigger setup

    * SubscriptionDeactivated
    * ReminderIssued
    * UserAuthorizationGranted
    * UserAuthorizationRevoked

* The ledger summary total now shows outstanding transactions (yet to be Invoiced), if ledger billing is enabled.
* Added support for showing transfer transactions on the account.
* Support for registering Email and EHF as payment agreements during Orders.

Changed
-------

* AutoGiro crediting now longer displays an option for specifying a custom due time when re-issuing is requested.
* Minor translation and general language improvements.

Fixed
-----

* An issue with missing organization information on the account transactions.
* An issue with the reminders filter where "All states" would end up displaying nothing.
* An issue where filtering grid data would have no effect on the exported file.
* An issue where the default Currency symbol was not applied on invoice details/lines.


Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self-service client

Fixed
-----

* An issue where the default Currency symbol was not applied on invoice details/lines.