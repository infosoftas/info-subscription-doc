.. _changelog-r101:

***********************
Release April 26th 2022
***********************
This release contains mostly bugfixes and UI support of recent API additions.

The backend/API has been rolled out entirely, while the frontend/UI clients will roll out over the next couple of days.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added new events for exposing Scheduled Payment Requests and Processed Payment Requests as web hook triggers. 
  This allows consumers to handle scenarios such as sending notification once an AvtaleGiro request has been submitted to Mastercard, or informing that a Debit/Credit Card payment has occurred.
* Fixed an issue with rounding of charges on invoices caused invalid totals.
* Fixed an issue with trying to cancel already cancelled Vipps charges.
* Fixed a problem where querying for all dunning processes, the Payment Request settings collection was never populated.
* An issue was fixed that cause the billing engine to skip processing payment demands for future orders, if specific changes were registered on other subscriptions on the same subscriber.
* Streamlined the decimal rounding for the EHF Invoice generator.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added support for managing permanent discounts.
* Added support for ordering subscriptions with permanent discounts.
* Configuration of Reminder Settings now supports the recently introduced ordering mechanism, meaning the visual order of reminder settings is now the ACTUAL order they are processed in.
* Fixed an issue that prevent re-activation of enterprise plans.
* Fixed multiple minor issues with adjusting dunning process settings.
* Fixed an issue where the counting of shared users would be based on the wrong value (implicitly granting more shared users than desired).

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Update the error message when shared users attempted to log in to the self-service area.
* Fixed an issue when ordering with experied subscriptionplans via the salesposter.
* Fixed an issue where refreshing the order confirmation page on the salesposter would lead to a duplicate order being generated.