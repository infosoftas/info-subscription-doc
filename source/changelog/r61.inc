.. _changelog-r61:

************************
Release August 19th 2019
************************
The following changes were rolled out to production on August 19th 2019

API and Backend
===============
The following new features and improvements are now available in the API and the backend

* Added support for overriding the price calculation on Orders. If a price is specified all price calculations are ignored.
* Added support for plan validation with price overrides.
* Additional filter options for Invoices and creditnotes
* Added support for getting/querying for Reminders.
* Added option for defining a custom start date on new orders. If not given the subscription will start immediately.
* Added support for querying current sequencenumber state for SubscriberNumber and InvoiceNumber sequence
* Fixed an issue where creating or updating a dunning process with a stop rule would do nothing.
* Fixed an issue where data corruption would lead to no subscribers being retrieved when querying for subscribers.
* Added support for generating reminders on the order payment demand (previously they would only be generated for recurring periods)
* Fixed an intermediate issue with file creation causing internal false-positive alarms
* Fixed an issue where cancelation dates would be stored in the wrong format
* Data and storage changes to avoid rounding errors in reporting


Client
======
The following new features and improvements are now available in the web client

* Extended managing options Enterprise Plan, such as adding new susbcriptions directly to the plan *Preview Feature*
* Support for adding Subscriber metadata to an Auth0 user *Preview Feature*
* Fixed an issue where saving the Arvato configuration would result in an error.
* Fixed an issue where assigning a "high" balance threshold on the dunning process stop rules would cause an error
* Fixed an issue where it was not possible to configure a Subscription Plan with a fixed initial period and an automatic stop
* Changed sorting of the ledger transactions on the subscriber view.
* Added payment registration date on the payments overview
* Lots of layout and minor design changes across most views
* Added Norwegian translation for the Susbcriber Notes feature
* Collapsable submenu items in the Merchant System menu
* Extended support for configuring Invoice Number sequence
* Added support for configuring External Invoice Identifier for various providers
* Removed the option to directly register payments on Invoices that have amount zero (still possible using manual payments)

Refer to the developer and user documentation for details on the various features.

Known Issues
============

* External Invoice Identifiers may be generated in a way that exceeds the allowed length when Subscriber Number and Invoice Number lengths exceeds the max length.