.. _changelog-r117:

*************************
Release October 10th 2023
*************************

This time around we have been hard at work to iron out issues with deliveries, as well as some other features and bugs here and there.
Due to autumn vacations the release has been a bit delayed.


API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* New SwedbankPay API endpoint. This is just a re-branding of the old PayEx and PayEx eCommerce endpoints.
* Added option for deleting Organizations from the API.
* An optional failure state and reason on processed payment requests handled by the Swedbank Pay integration (Card payments).
* Added an option to update a few details on a SwedbankPay Account configuration, such as the encryption key.

Fixed
-----

* An issue where an unknown organization id would cause an internal server error, it now correctly produces a client error (400 Bad Request).
* An issue where Enterprise Plans with many subscriptions (150+) would end up not being settled properly when processing payments.
* An issue where future orders on |eFaktura| and |AvtaleGiro|, would have a missing date part in the statement text for the period.
* An issue where an unknown organization id would cause an order processing failure instead of a client error.
* An issue where product authorization would not be properly deleted on deleted users. No authorization was granted, but the record of previous authorization was kept indefinitely.
* Multiple issues related to Deliveries and the associated Distribution Innovation integration, including:

    * Mixing delivery stop and temporary address changes would lead to invalid or missing restarts.
    * Manual use of the "Source" field would cause processing failures if no DI integration was configured.
    * Delivery stops with a delivery restarts overlapping a cancelled subscription could lead to deliveries being started on cancelled subscriptions.
    * Updating an address on subscription end would register an invalid delivery split.
    

Changed
-------

* Payment Demand Charges and Payment Demand Allowances now include the original transaction type as it was on the account.
* Empty address lines on Subscriber Contacts are now stripped away during updates and creation.
* Payments that are processed on a subscriber with only one Subscriber Account will now be automatically associated with that account.
* Improved the mapping of |Vipps| recurring agreements when querying for the remote status of a charge.

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

* Support for adding scheduled contact changes, such as a future address change.
* Adding an Subscriber Organization Number will now verify it against the PEPPOL database for validity in terms of receiving EHF invoices. A visual clue will be displayed if it does not exist.
* Added validation for delivery changes to allow processing on the next day at the earliest. Changes further into the future are still accepted.

Fixed
-----

* The Distribution Innovation overview now allows omitting integration values that are not available.
* Delivery changes are now stored with midnight as the time of change instead of the current time part.
* An issue where an invalid amount was shown for reminders.
* An issue where the payment registration view would not always reset the input fields as required.
* An issue where reminder settings order would not be persisted.

Changed
-------

* Replaced the grids for Invoices, Payments and the combined view so it now supports paging the results. Reducing the consumption of screen real estate.
* Multiple text adjustments and additions for Payment Agreements.


Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self-service client

Added
-----

* Added validation for delivery changes to only allow processing on the next day.

Fixed
-----

* Support for adding scheduled contact changes, such as a future address change.
* Delivery changes are now stored with midnight as the time of change instead of the current time part.