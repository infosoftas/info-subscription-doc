.. _changelog-r62:

************************
Release September 3rd 2019
************************
The following changes were rolled out to production on September 3rd 2019

API and Backend
===============
The following new features and improvements are now available in the API and the backend

* Expanded the API to include querying options for reminders
* Added support for tracking Subscriber Accounts
* Some performance adjustments to package/plan related actions
* Fixed an error causing the External Invoice Identifier routine to generate invalid Ids
* Major changes to the payment import process to better track state (and errors) and progress
* Fixed multiple issues related to crediting orders (first period)
* Enterprise Plans created without billing alignment now defaults to monthly billing (previously they were invalid)
* Fixed an issue where payment requests would fail to materialize in the API when subscriptions were created backwards in time (migration scenario)
* Fixed an issue where invoices and demands for enterprise plans would get the wrong amount and due date.
* Adjusted routine for handling billing on cancelled subscriptions to make it more robust and transparent.
* Fixed an issue with EHF files being fed back to the system in InvoiceFile with type XML instead of EHF.

Client
======
The following new features and improvements are now available in the web client

* Enterprise Plan Management improvements

    * Create new subscriptions on a plan or connect existing subscribers
    * Display all subscribers on a plan
    * Plans can now be activated upon creation

* Added option to filter subscribers on payment agreement reference and payment agreement expiry date
* Reminders are now shown on the invoice overview on both the self-service and merchant clients.
* Fixed multiple issues with adding notes to subscribers without subscriptions
* Fixed an issue where the economic journal/ledger for subscribers would show all organizations (even when the subscriber had no subscriptions for the organization).

Refer to the developer and user documentation for details on the various features.

Known Issues
============

* When demands and invoices with reminders (that has fees) are paid, it is not obvious from the API and the client whether the fee on the demand has been settled or not.
* External Invoice Identifiers may be generated in a way that exceeds the allowed length when Subscriber Number and Invoice Number lengths exceeds the max length.
* Pausing subscriptions twice before being started in the new period causes strange result - recommend to cancel and order a new subscription instead.