.. _changelog-r93:

****************************
Release September 14th 2021
****************************
The following changes started rolling out on September 14th.
The API and backend are being rolled out to all tenants at the same time, and the client will be propagated over the next couple of days.

In terms of backend features this is a very small release.
Mostly because we are busy with a few larger features and there are a lot of internal improvements.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Fixed an issue where disabling event hook pre-validation would not have an effect.
* Improved error message for orders failing creation due to validation issues (such as missing prices or frequencies).
* Fixed an issue where a cancellation inside a subscription period would not lead to a proper proration (full credit was done instead of a partial).
* Fixed an issue where contract fee surcharge was calculated based on milliseconds instead of entire days.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Support for disabling AvtaleGiro bank notifications across the board **Preview**
* Reduced some clutter in the subscription overview.
* Added reminder numbers in order to make it easier to see which reminder is which. Dates where already here, but it may be faster to just see the number.
* Minor visual adjustments to Payment Agreement overview.


Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Support for registering temporary delivery addresses **Preview**
