.. _changelog-r102:

***********************
Release May 23rd 2022
***********************
Yet another release has hit the shelves. 
The API and backend has been rolled out entirely, and the frontend/UI will be rolled out over the next couple of days.


API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Billing account charges and allowances now include an optional reference to the source demand that generated them. These are also available once billing issues a demand for them.
* Added support for automated generation of replacement/followup demands when crediting a standalone account demand. Previously it was up to the caller to generate a new one.
* Changed demand generation for contract surcharges so that any existing account transactions are included on the final/balance demand.
* Fixed an issue where crediting Enterprise Plan demands would generate invalid ledger records.
* Crediting Payment Demands with an Invoice Payment Agreement now calculates a new Due Date for the replacement demand if specified by the command. Previously the original Due Date would always be re-used.
* Fixed an issue where an empty Description tag `<Description />` would be created for EHF files with no additional text to be included in the description. This caused the validator to fail even though the field is optional.
* The reporting subsystem now correctly updates all parts of the subscription when a payment agreement is changed. Previously the data was only partially updated.
* Fixed a few issues in how Months are calculated for Subscription length. This affects subscriptions with an end time in the last few days of a calendar month, especially during Feburary, and while switching back and forth between Daylight Savings Time.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* It is now possible to ignore the contract surcharge fee when canceling subscriptions with a contract fee.
* When ordering a new subscription it is now possible to select products if the template subscription plan contains a product choice collection.
* Multiple visual and navigation improvements to the Ledger view, for instance it is now possible to navigate to Invoices and Payments directly from the Ledger view.
* The Invoice View has received a major overhaul, lines are now more easily identifiable, and the charge/allowance details are now more easily accessible.
* Some minor adjustments to registration of ledger corrections.


Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Added support for Northern Sami as a language for the salesposter and the self-service client.