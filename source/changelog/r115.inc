.. _changelog-r115:

************************
Release August 10th 2023
************************

Summer vacations are almost over for everyone in the dev team, and a new release is ready, roughly 2 months since the previous release.
This release is a mixed bag of fixes, small incremental improvements and a single new feature in preview.

We are still trying out the new format for the changelog, following a type of change convention outlined on https://keepachangelog.com/

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Added new public event types for ``UserAuthorizationGranted``, ``UserAuthorizationRevoked``, ``EmailDomainAuthorizationGranted`` and ``EmailDomainAuthorizationRevoked``. Enables additional external reactions based on user authorization changes.
* Added support for Tax Details on Charges and Allowances. This means that Charges on Payment Demands will now include a Tax Detail breakdown instead of a single Tax Percent. The net effect being that multiple charges will be merged into a single Charge with multiple taxes in several scenarios.
* Support for removing InvoiceContact via a scheduled subscription plan change.
* Added support for switching Payment Agreement during Subscription restarts.
* **[Preview]** Support for User Email Domain and Authorization mapping.
* **[Preview]** |eFaktura| Mandate/Agreement Scanning will now be executed on a recurring schedule, with partial scans every day and full scans every week.

Fixed
-----

* Updating an existing BillingPlan without specifying a frequency will now produce a validation error.
* Fixed an issue where Account Payment Demands would issue a reminder with a Payable Amount of 0.00 in cases where an outstanding Allowance should have settled the demand.
* |Vipps| charges now have a due date the day after the Payment Demand to avoid issues with early cancellations of time based subscriptions.
* Added missing validation for creating multiple |AvtaleGiro| account setups with the same Bank Account Number.
* Fixed an issue where an additional empty Payment Demand would be generated for Enterprise Plans upon a partial credit.
* **[Preview]** |eFaktura| transactions with multiple identical Tax Groups will now be bundled together to produce a better visual experience.
* **[Preview]** Fixed an issue where |eFaktura| transactions would not be generated in case the issuing Organization was missing phone number or contact email.


Changed
-------

* Payment Import API has been slightly modified in terms of the output. The input is unchanged.
* Simplified account configuration for |AvtaleGiro| and |eFaktura|. Multiple input fields has been removed (defining them will not break things, they will just be ignored).
* Subscription Restarts will now be routed through the Order processing to facilitate handling of multiple Payment Agreement scenarios.
* Multiple adjustments to the underlying Payment Import file processing, in order to improve feedback and resilience.
* Scheduled Subscription Plan changes will no longer split the existing Subscription in cases where there is no need. For instance when changes are set to affect a future Subscription period.


Deprecated
----------
We call out the following deprecations, the endpoints/field will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* We are deprecating the endpoints ``/paymentdemand/{id}/credit/completely`` and ``/paymentdemand/{id}/credit/partially`` in favor of the afore mentioned ``/paymentdemand/{id}/credit`` endpoint.
* We are deprecating the field ``TaxPercentage`` on the endpoint for creating Account Payment Demand transaction ``POST /paymentdemand/``, in favour of specifying a list of Tax Details.


[Preview] New Feature : Email Domain based User Authorization
-------------------------------------------------------------

This release introduces building blocks for automating User Authorization based on the domain name of their email address.
It is an alternative to :ref:`Site Access <_auth-site-access>` where all users created with a specific domain name, will be authorized to a given domain.

It will work side-by-side with other user Authorization mapping concepts, so you can mix and match as you see fit.

This is still in preview, and some of the UI elements are not yet in place. 
Additionally some external modifications are needed in the IdP and a custom sign-up experience responsible for mapping the user to the domain authorization.

Interested in participating in the preview? Contact support, find the details on {SUPPORTPAGE}.


Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* Merchants can now configure Self-Service behaviour for Subscription Cancellations.
* Added an indicator showing if there are existing notes on a given subscriber.
* **[Preview]** Support for listing the sum of not-invoice Billing Account transactions on the ledger summary.
* **[Preview]** Support for configuring Domain Authorization on Subscriptions.


Fixed
-----

* An issue with the wrong Tax Amount being shown for Reminder and Invoice Fees.
* An issue where product with an adjusted price would be displayed as expired.
* Tenant selection should again be persisted between session on the same browser.
* An invalid Subscription Plan would sometimes be displayed when doing refunds.
* An issue where it was not possible to remove a planned cancellation of an already renewed Subscription.
* Removed an invalid button from |eFaktura| payment agreement view.
* An issue with custom grid sorting for |eFaktura| and |AvtaleGiro| transactions being ignored.
* An issue where the wrong API endpoint was used for Enterprise Plan Payment Demand crediting.

Changed
-------

* Minor Visual adjustments to the following views:

    * Enterprise Plan Details
    * Invoices
    * Logout confirmation
    * |AvtaleGiro| and |eFaktura| account setup

* Payment Import has been adjusted to reflect the API changes, and provide better user feedback.
* Adjusted translations for |eFaktura| and |AvtaleGiro| agreements
* Exporting Refunds now include the underlying External Reference field.

Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self-service client

Changed
-------

* Translations in relation to Subscription Cancellations.

Fixed
-----

* An issue where temporary delivery changes would not include the existing Subscriber Contact Name in the change.
* An issue where the Product id would be shown instead of the product name on cancelled subscriptions.
* Default Country would not be set when doing temporary delivery changes.