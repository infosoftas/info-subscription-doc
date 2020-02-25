.. _changelog-r69:

**************************
Release Feburary 25th 2020
**************************
The following changes were rolled out to production on Feburary 25th 2020.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added direct reference to the originating Invoice on reminders.
* Changed the generated Invoice Specification for Enterprise Plans so the subscriber name and number is included in the line text.
* Improved parsing of subscriber organization number for EHF file generation.
* Expanded reporting:

    * Subscriber Contact Model: Address lines are now exported individually instead of as an JSON String Array
    * Orders Model: Now contains StartTime and EnterprisePlanId
    * Ledger/Economy Model: Includes marker for stopped demands/subscripions stopped by the billing engine (payment stop).

* Fixed an issue that prevented Reminders to be generated for demands related to Enterprise Plans.
* Fixed an issue where subscriptions on enterprise plans would always be created with an empty chain.

Client
======
The following new features and improvements are now available in the web client

* Improvements to filtering of orders in merchant
* Improvements to filtering of payments in merchant
* Ledger entries with value 0 er now hidden in the merchant overview on the subscriber so as to not cause confusion.
* Adjusted the "status" descriptor for subscriptions in merchant so it is possible to differentiate between "is going to be stopped" and "has already been cancelled and is stopped right now"
* Adjustments to the detailed subscriber view
* Adjusted Enterprise Plan Demand Details to show creditted and stopped subscriptions.
* Fixed issue where the wrong duedate was shown on reminders
* Removed the option for profile-registration on non-subscribers in the self-service.
* Added support to display and switch between payment agreements in self-service and merchant (preview)

Known Issues
============

* When demands and invoices with reminders (that has fees) are paid, it is not obvious from the API and the client whether the fee on the demand has been settled or not.
* External Invoice Identifiers may be generated in a way that exceeds the allowed length when Subscriber Number and Invoice Number lengths exceeds the max length.