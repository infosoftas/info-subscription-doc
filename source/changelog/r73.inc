.. _changelog-r73:

**************************
Release April 23rd 2020
**************************
The following changes rolled out to production on April 23rd 2020.
Despite the raging Corona/Covid-19 pandemic this release includes quite a few changes.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added new feature "Reporting Tags" and included support for automatically defining them on new orders.
* Organizations can now be associated with products and subscription plans. They are not verified and are mostly here for filtering/display purposes for now. This also includes a query filter for products and plans.
* Added support for registering subscriber ledger correction/balancing transactions to manually adjust for discrepancies or handling of other system-external actions.
* Recurring deliveries can now be queried using a `CoversDate` filter which the delivery should be within (i.e. the starttime should be earlier than and then endtime should be later than the given value).
* Fixed an issue where payment demands that were credited would still be subject to evaluation of payment stops, causing subscriptions to be stopped even though the demand was credited.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Support for registering tags on orders, these are carried over to the reporting data model for various reporting purposes.
* Added option to enable event notifications/web hooks infrastructure.
* Improved validation and error messages during web hook registration.
* More filtering options for payments.
* Fixed an issue that would display the wrong amount for reminders in case of an included reminder fee.
* Adjusted display of time to consider timezone properly for subscriptions spanning summertime/wintertime changes.
* Minor layout adjustsments to CSV Exports for payments.
* Fixed an issue where registering multiple stop rules caused an error.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Added Organization parameter to the salesposter to support orders on multiple organizations.
* Added display Care-of for addresses.
* Expired/Stopped subscriptions are now displayed with the expiration/cancellation time. Previously expired subscriptions were hidden from view.
* Fixed an issue in the salesposter where the order amount would be displayed wrongly when using safari.


Reporting Tags
==============
This release includes a new feature mainly aimed at associating external values/parameters to entities for reporting. We have named these Reporting Tags (very inventive!)

In its simplest form a tag is just an arbitrary string value, which can be associated with an entity (using a type and an id).
These tags can then be used in reporting, as an example a new order may have a `store id:12345` tag, so the entity would be `Order`, the Id would be `OrderId` and the value would be `store id:12345`.

For convenience the Order API has been adapted to automatically create such tags if provided as input to the order creation workflow.