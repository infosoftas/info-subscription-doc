.. _changelog-r92:

*************************
Release August 26th 2021
*************************
The following changes started rolling out on August 26th.
The API and backend are being rolled out to all tenants at the same time, and the client will be propagated over the next couple of days.

This is our first release after the summer, so it has taken a bit more time to get it ready. The team has been working on lots of things, some small, some large.
Mostly the things included in the actual release is on the smaller side of things (bug fixes), but we are working in parallel on several larger features and this release also sees significant internal changes (not included in the changelog).


API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* The API now include endpoints for querying the billing engine for preliminary demands (similar to draft invoices).
* Expanded the API to include subscriber account transactions that are not consumed (allowances and charges), to give an insight into which transactions might be put on the next demand in addition to the subscription.
* Added support for undoing future subscription cancellations **Preview**

    * New endpoints included in the API
    * All artificates related to billing, deliveries and subscriptions will be re-generated when the cancellation is removed.

* Added support for using AvtaleGiro without Bank Notifications **Preview**.

    * This is simply a new flag on the avtalegiro account. The billing lifecycle becomes simpler, but all invoicing must be done by the tenant/organization instead of via the bank.

* Double credits on ledgers for the same Invoice will now be blocked. This is mostly to avoid issues where clients are aggresively crediting without waiting for the interim processing.
* Adjustments and bug fixing to handle Credit Card capture failures automatically **Preview**.

    * Now payment requests retries are configured as number of days to follow up instead of using a complex schedule.
    * Capture failures are reported from the individual services.
    * Followup captures are scheduled immediately and removed once a payment is actually received.

* Fixed an issue where multiple AvtaleGiro claims would be generated with the same KID. Now these are blocked.
* Fixed an issue related to Due Date calculation for AvtaleGiro where claims would be sent too late if the last day of the month happened not to be a working day.
* Payment Request failures are now reported in an event including provider specific details. The event is called 'PaymentProcessingFailed'. It is slightly different from the existing PaymentRequestFailed as it happens when the provider is invoked but something happens at the provider level.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added support for editing or removing future subscription cancellations **Preview**.
* Invoices and Payment rows are now collapsed into one shared/matched row in the Subscription Overiew. Previously it was one table with some rows representing invoices and some representing payments.
* Translations adjustments related to temporary stops, invoices and paymentagreements.
* Updated the view for configuration of Payment Request failure handling to reflect the changed API **Preview**.
* Included support for configuring default Contract terms on subscription plans.
* Subscription view now includes contract information if present.
* Account Demands can now be filtered/hidden on the Invoice view.


Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Adjust how current state is shown for a given subscription to better reflect the state shown in the merchant client.
* Removed 'Administer Users' menu item if shared users is not enabled and configured.