.. _changelog-r89:

*************************
Release May 11th 2021
*************************
The following changes started rolling out on Tuesday May 11th 2021.
The API and backend is being rolled out to all tenants at the same time, and the client will be propagated over the next couple of days.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added option for exporting Bankgirot Autogiro Mandate files **Preview**.
* Subscription Contract now includes properties for Fee/Surcharges. This goes for creating subscriptions, orders and changing subscription plans.
* Contracts Fees/Surcharges included in reporting sub-system.
* Added new crediting endpoint for Enterprise Plan Demands - this will replace the existing credit subscriptions option **Preview**.
* AvtaleGiro Mandates now include Import and Deactivation timestamps.
* Transactions for Swedbank Pay now include properties for cancellation time and creation time.
* Fixed a bug where a new AvtaleGiro claim would not be generated when crediting and automatically re-issuing a demand.
* Improved error handling for Vipps transactions.
* The backend will now forcefully cut-off description and product names to the max length to avoid failures. This will lead to weird names in the Vipps App but everything will work otherwise.
* An issue has been fixed whre subscriptions on an Enterprise Plan would not take price adjustments into consideration when issuing new demands.
* Subscriptions on Enterprise Plans which have been cancelled are now removed from Payment Demands when issued **Hotfix Already Deployed**
* In previous versions importing Bankgirot BGMAX files would not convert dates to UTC with the right timezone, this has been fixed using swedish time for the timezone to convert from.
* Ledger entries used the wrong date from payments when importing. Specifically the use of booking/value date and bank date has been switched around.
* Multiple adjustments to prevent double subscriptions during renewal in high load scenarios.
* PayEx POPS is now officially out of service, and all attempts to do POPS agreement transactions are blocked.


Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added new view for Payment Agreements and details. **Preview**
* Payment and Accounting Reports now include Fees.
* Added multiple Norwegian Newspaper/Magazine related reports for our Norwegian newspaper/magazine related tenants. Detailed information added in a directed e-mail.
* Fixed multiple issues with the Subscription Cancellation report

    * Missing subscriber information
    * Counting some subscriptions twice
    * Adjusted date formatting

Payment Agreements
------------------
With this release we are rolling out preview support for a new payment agreement overview for the merchant client.

Using this view it is now possible to get an overview of all the payment agreements registered on a given subscriber.
It is also possible to create a new Invoice agreement if required.

A detailed view is available for each agreement making it possible to view the details of that agreement.
The information available varies from provider to provider.

* Swedbank Pay

  * Card Brand (Visa, Mastercard, American Express etc)
  * Card Mask
  * Expiration time

* AvtaleGiro

  * Account Number
  * Mandate KID as provided by MasterCardPaymentServices
  * Bank Notification
  * Active/InActive
  * Imported
  * Cancelled

* Vipps

  * Account Name (Which of the configured accounts is the agreement related to)
  * Vipps Agreement Id as provided by Vipps.
  * Phone Number
  * Status

Also available with the details is a list of transactions registered on the given agreement. 
Transactions represents the payment requests sent to the provider, and will often include a reference that can be used with the provider for identification purposes.
Similar to the agreements, the transaction details differs between providers.

This feature is currently in preview. Contact our support to be included in the preview.

Moving forward new provider integrations will be included in this overview, and we will work on improving the level of detail and workflow.