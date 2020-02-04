.. _changelog-r69:

**************************
Release Feburary 4th 2020
**************************
The following changes were rolled out to production on Feburary 4th 2020.
We skipped a sprint due to holidays so this is the first release of 2020.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Reporting datamodel extended with Enterprise Plan information
* Fixed an issue where creating a new subscriber contact would all historic reporting entries to be overridden with the new contact
* Fixed an issue in the reporting datamodel where cancelled subscriptions would not be updated correctly in some cases.
* Added support for changing Payment Agreement on a running subscription (Preview feature)
* Added support for directly crediting subscriptions on an Enterprise Plan (previously it was only possible to Cancel and thus implicitly credit)
* When changing subscription plans on a running subscription it is now possible to include an Invoice Contact
* Expanded the Organization to include a "home"" timezone, primarily used for reporting purposes
* Orders with offers of type "the rest of this year" now use the home timezone to determine when the year ends (previously it was always UTC based).
* Fixed an issue where it was not possible to create payment agreements for 'Invoice' without specfiying card details
* Fixed an issue where Payment Agreement creation would validate the given SubscriberId as if it was a CustomerId
* Change of billing behaviour such that future changes are scheduled according to the billing plan instead of being billed immediately, the following actions are affected
    
    * Orders with future start
    * Plan changes in the future
    * Pause to subscriptions

* Fixed an issue that cause payment stops to be re-evaluated continously after a subscription has been cancelled.
* Multiple adjustments to EHF related to PartyTaxScheme and Financial AccountNumber
* Added support for handling of 0 valued payments and agreement creations for PayEx.
* Added initial endpoint validation when creating new event web hooks.
* Fixed an issue with event notifications/web hooks that caused tenants with whitespace and weird characters to not receive any events.


Client
======
The following new features and improvements are now available in the web client

* Merchant support for adding Invoice Contact on Subscription Plan Change.
* Added support for selecting payment agreement when creating new subscriptions from the Merchant interface.
* Added support for cancelling and crediting subscriptions on Enterprise Plans (preview feature).
* Expanded EHF configuration settings with bank account number.
* Option to export invoice from the Invoice view.
* When cancelling a subscription it is now possible to define the time of cancellation - previously it defaulted to the end of the period.
* Fixed a redirect error in the salesposter.
* Fixed an issue where defining an Invoice Contact during registration of an Invoice Contact would lead to the contact not being selectable for existing subscriptions.
* Fixed an issue in self-service where the subscription start time would be shown as UTC instead of local time.
* Multiple fixes related to login after completing an Order via the Salesposter
* Added support for Subscriber authorization without the need for mapping to customer such that the process is more akin to what third parties are recommended to use.
* It is no longer possible to register a payment on an already paid invoice in the merchant client.
* Self-Service now includes a view of existing payment agreements for the subscriber.
* Fixed an issue where it was not possible to approve payments awaiting approval.

Known Issues
============

* When demands and invoices with reminders (that has fees) are paid, it is not obvious from the API and the client whether the fee on the demand has been settled or not.
* External Invoice Identifiers may be generated in a way that exceeds the allowed length when Subscriber Number and Invoice Number lengths exceeds the max length.
* Crediting Subscriptions on Enterprise Plans in "multiple" attempts (i.e. crediting three subscriptions one at a time for instance) will lead to invalid invoices.