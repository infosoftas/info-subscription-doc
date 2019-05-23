.. _changelog-r57:

***********************
Release May 23rd 2019
***********************
The following changes were rolled out to production on May 23rd 2019

API and Backend
===============
The following new features and improvements are now available in the API and the backend

* Support for cancelling subscriptions with a start time in the future.
* Support for getting ALL Invoice configurations and not just by a known Id.
* Removed support for shorter than 1 day billing frequencies as a different billing and dunning concept is needed for these.
* Simplified contracts that had both Billing Plan and Billing Frequency as input by removing Billing Frequency.
* Extended the payment demand contract with additional properties.
* Credit time is now added properly to the PaymentDemand and the Invoice once a demand is credited.
* PaymentDemands are now included in the reporting data.

Client
======
The following new features and improvements are now available in the client

* Self-Service now includes an way to view invoice details.
* The merchant client now includes an option for setting up an Invoice sequence.
* Restricted the option for registering payments on invoices of 0 amount.
* Fixed an issue where the credit date was shown as the issue date of the invoice in the merchant.
* Fixed an issue where it was not possible to cancel an Invoice Payer once registered.
* Fixed an issue where registering invoice payer on the sales poster would not connect to the created subscription.

Known Issues
============

* The Norwegian version of the self-service invoice view is lacking some translations.
* External Invoice Identifiers may be generated in a way that exceeds the allowed length when Subscriber Number and Invoice Number lengths exceeds the max length.