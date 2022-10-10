.. _changelog-r106:

****************************
Release October 10th 2022
****************************
Its october and there is a new release ready for you. Mostly bug fixes and minor visual adjustments.

The API and backend has been rolled out, the self-service and merchant clients will be rolled out progressively during the next few days.

Those of you on the *new* merchant setup will see the changes on the 11th.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Option for adding number of units when create subscriptions directly (not using Orders).
* Multiple improvements bug fixes to the user authorization product list generation **Preview**.
* The API now accepts token issued by our new Azure ADB2C instance **Preview**.
* Added dunning process configuration to limit automatic settlment based on amount paid relative to the issued demand **Preview**.
* Credit Notes now have their own model in the reporting sub system similar to invoices.
* Fixed an issue where Invoice Contact information would be put into the Invoice Document with an invalid reference type (it would refer Subscriber when it was indeed a Subscriber Contact).
* Ledger transactions now includes optional reference fields for Credit Note, Refund and Reminders.
* Improved the process for handling Vipps charge settlement automatically to reduce the timewindow between charges being processed by and settlement time in |projectName|.
* Fixed an issue where multiple AvtaleGiro mandate adjustments would lead to multiple mandates being created.
* Fixed an issue in billing where the Invoice Contact was not used correctly (crediting with re-issue).
* EHF Invoices now produce the right VAT breakdown when using more than 2 VAT groups.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Multiple adjustments to text and visual element placement, streamlining the experience mostly.
* Re-arranged views for Enterprise Plan which should provide a more intuitive navigation and management of these plans and related resources.
* Multiple improvements for filtering and sorting in almost all grid/list views for the subscriber.
* Fixed a bug with invalid dates for exported invoices, reminders, creditnotes, payments and ledger transactions.
* Fixed spelling and translation issue with registration of new payments.
* Fixed an issue where it was possible to save a subscription plan change with a price override violating the rules/limits, the regular price would be used. This has now been fixed to prevent saving these changes.


Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Added information/help text on shared users view for ADB2C authorization **Preview**.