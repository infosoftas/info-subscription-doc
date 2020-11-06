.. _changelog-r81:

***************************
Release November 5th 2020
***************************
The following changes started rolling out on November 5th. The API and backend changes have already rolled out to everyone, while the client roll out will happen gradually during the next couple of days.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added support to query for uploaded, and processed payment files (Payment Import).
* Introduced support to query for reporting tags.
* The order endpoint now includes error message from underlying sub-system improving client support. 
  For instance when the underlying system determines that the validation failed on client input for some reason, the validation message is now given to the client, thus enabling the client to give a better error message, or fix the error.
* Payment Demands now includes preliminary support for a tax/product breakdown for each detail.
* Fixed an issue where payment demands would have a 0 valued fee when no fee was configured, instead of just omitting the fee.
* Added more details to the PayEx transaction query results.
* Expanded payment details in the reporting sub-system to better reflect state of unidentified payments.
* Expanded reporting sub-system with references between payments and payment demands.
* Fixed an issue in the billing engine where the number of units would not carry over to the final invoice for subscription on an enterprise plan.
* Fixed an issue where a change of payment agreement during an active subscription period, would lead to the wrong payment agreement being used for the next payment demand.
* Added subscriber name and number on lines for enterprise plan invoices.
* EHF files now includes localized date/times for ALL date entries in the document (released as a hotfix).
* Fixed an issue where querying for invoices with an invalid subscriber Id cause all invoices to be returned.
* Adjusted the order process so the payment type and payment provider type is set even on existing agreements. 

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Extended the dunning process settings view to support omitting fee for the order.
* Adjusted the subscriber listing/search view to improve overall performance for tenants with many subscribers.
* Adjusted the subscription cancellation view to make it easier to do the "right" registration.
* Added credit time for creditted invoices.
* Fixed an issue where there was two buttons for adding an invoice contact when registering a new order.
* Updated version of the orders report, including more details and adjustments to how date filtering works.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Fixed an issue in the salesposter that would display the default subscription plan even when a custom plan was specified.
* Adjustments to the subscription overview making it clearer which subscriptions have passed/are inactive and which are current.