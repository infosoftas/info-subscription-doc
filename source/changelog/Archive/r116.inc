.. _changelog-r116:

***************************
Release September 5th 2023
***************************

A short sprint this time around, and thus also a minor release. Mostly this release contains bug fixes, but a few new features have been shoehorned in!


API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* **[Preview]** Added support for automatically settling payment demands and crediting reminder fees when receiving payments on the original demand amount.
* Added new endpoint to calculate the next subscription period for any given subscription, based on the current registered information.
* The |eFaktura| integration now supplies the issuing organization number during agreement scanning, effectively ensuring that subscribers who opt-out of |eFaktura| for a given issuer will not be automatically added.

Fixed
-----

* A validation issue where changing the plan of an existing subscription required more options to be set than specified by the documentation and internal requirements.
* The API reference documentation with the correct status code, ``HTTP 202``, for a successful change of payment agreement.
* An issue where it was possible to provide an empty/default ``UUID`` for Invoice Identifier generation configuration.
* An issue where the recently introduced event types for domain authorization would not be published correctly.
* An issue where tenants with a special character in the name could not enable the event notification infrastructure.
* An issue with billing where the payment demand schedule for an order would be deleted in case the order was in the future, and the subscription was configured with automatic cancellation at the end of the first period.

Changed
-------

* |Vipps| based orders should now trim away white spaces in the phone number, reducing the number of invalid requests sent to |Vipps|. |Vipps| have also deployed a change in their validation routine to allow different formatted phone numbers.
* Details on Enterprise Plan payment demands would not be generated with a new Id after partial credits. This has now been changed so that the details are regenerated with a new Id.


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

* Support for restarting a cancelled subscription with the exact same plan as it was on previously. Useful for handling cases with late payments and similar.
* Support for removing invoice contacts as a scheduled change.
* **[Preview]** Connected domain users are now listed on the users list.

Fixed
-----

* An issue where temporary delivery changes would cause a validation error, but the changes would still be partially applied.
* An issue where setting/changing the Kilkaya installation URL would not have any effect.
* Visuals for frequency during order creation in chrome.
* **[Preview]** A validation issue that prevented registration of domain names with a dash (-) in the domain authorization.

Changed
-------

* Replaced the subscriptions grid view on the overview and on the subscriptions tab.
* Multiple text adjustments and additions for Payment Agreements.

Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self-service client

Fixed
-----

* An issue where temporary delivery changes would cause a validation error, but the changes would still be partially applied.
* **[Preview]** An issue where connecting a new user with a domain authorization would occasionally fail to register.