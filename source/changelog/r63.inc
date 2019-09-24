.. _changelog-r63:

***************************
Release September 24th 2019
***************************
The following changes were rolled out to production on September 24th 2019

API and Backend
===============
The following new features and improvements are now available in the API and the backend

* Added support Recurring Deliveries.
* Expanded Payment Demand and related query field with EnterprisPlanId.
* Removed an unintentional API surface for invoking the renewal engine directly.
* Fixed an issue related to plan switching that caused a period to remain unbilled.
* Changed reminder fee implementation so it is now added as a fee if there is only one line on the invoice. In all other cases it remains a separate line.
* Fixed an error that caused evaluation of payment stop rules to not work as intended (i.e. not really stop anything).
* Fixed some robustness issues for the reporting engine.
* Fixed an error where scheduled payment requests where only partially removed after a cancel or credit.
* Fixed an issue where the Invoice would reflect the wrong amount after a partial credit (the demand was correct).
* Added new method to configure automatic denial orders for subscribers which exceed a given ledger balance.
* Added collection/saving of failed PayEx transactions to facilitate troubleshooting
* Fixed an issue where crediting would generate a replacement demand with the wrong DueDate and an associated Invoice with the wrong period.
* Fixed an issue where orders on existing PayEx Payment Agreements would fail to do an actual payment at the provider.

Recurring Deliveries
--------------------
This release features the initial phase of the feature Recurring Deliveries which helps with recurring distribution on a subscription.
Typical needed for newspapers, surprise/discovery box subscriptions or similar subscription with a physical distributed component.

From a backend/API point of view the feature includes:

    * Option to main delivery matrices (which day of a week the item is distributed) and connecting these with products
    * Option to starting and ending deliveries for subscribers manually.
    * The backend automatically starts and end deliveries for subscribers that has products with a delivery matrix configured.

    .. Note::

        At the current time of writing the feature is not exposed in the merchant client interface.

Client
======
The following new features and improvements are now available in the web client

* Added support for custom price overrides when creating new subscriptions in the merchant.
* As a merchant it is now possible to configure Denial Orders for subscribers based on balance limits.
* Improved the layout and information on Enterprise Plans.
* Minor adjustments to the displayed messages when pausing subscriptions.
* New Payment Management View for Merchants

    * List of all registered payments per organization, including the current processing state.
    * Centralized view for registering payments manually in bulk.

Expect more changes to the payment management view in future releases.

* Fixed an issue with the KPI for active subscriptions on the Dashboard.
* Removed the option for adding a pause with a future subscription period.

Refer to the developer and user documentation for details on the various features.

Known Issues
============

* When demands and invoices with reminders (that has fees) are paid, it is not obvious from the API and the client whether the fee on the demand has been settled or not.
* External Invoice Identifiers may be generated in a way that exceeds the allowed length when Subscriber Number and Invoice Number lengths exceeds the max length.
* Pausing subscriptions twice before being started in the new period causes strange result - recommend to cancel and order a new subscription instead.