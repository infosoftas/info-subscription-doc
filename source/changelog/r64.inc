.. _changelog-r64:

***************************
Release October 17th 2019
***************************
The following changes were rolled out to production on October 17th 2019

API and Backend
===============
The following new features and improvements are now available in the API and the backend

* Added support for managing Denial Orders on subscribers.
* Added state filtering when querying for Payments.
* Added Invoice Reference on Reminders to facilitate simpler backtracking to the original Invoice.
* Reporting now updates demands upon renewal with the target susbcription id.
* Fixed multiple issues related billing of Enterprise Plans where the Contact Id was used instead of the Owner Subscriber Id on demands and invoices.
* Fixed an issue where the Billing Plan was not populated all the way through for Orders, causing stop rules to not be evaluated for the first Subscription period.

Client
======
The following new features and improvements are now available in the web client

* Relaxed requirement for email when creating new subscribers in the merchant client.
* Added Denial Order Message in merchant when creating orders for subscribers with a denial order.
* Extended the overview for Enterprise Plans and Subscribers connected to enterprise plans.
* Fixed an issue where Invoice and Credit note reports would not render for some locales due to the way dates was send back to the API.
* Added Merchant support for price override on orders
* Added new payment management UI (preview feature)
* Added Denial Order display on subscribers.
* Fixed an error that allowed to register multiple pauses on the same subscription.
* Fixed an issue in the salesposter related to validation of phonenumbers.
* Fixed an issue in the sales poster where existing users could not order subscriptions.

Known Issues
============

* When demands and invoices with reminders (that has fees) are paid, it is not obvious from the API and the client whether the fee on the demand has been settled or not.
* External Invoice Identifiers may be generated in a way that exceeds the allowed length when Subscriber Number and Invoice Number lengths exceeds the max length.
* Pausing subscriptions twice before being started in the new period causes strange result - recommend to cancel and order a new subscription instead.