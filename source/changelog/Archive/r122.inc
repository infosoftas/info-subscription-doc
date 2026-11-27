.. _changelog-r122:

***********************
Release March 12th 2024
***********************

In addition to general bug fixing and minor improvements we continue to march on with components to do billing based on Editions, the initial feature is mostly ready, with the only notable exception being a lack of automatic proration on cancellations.

This release also extends the preview for |BetalingsService| payment agreements with additional feature areas and fixes.


API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Support for directly utilizing the Infosoft Partner credentials in |Vipps| communication, added as an option on the Account configuration - resulting in simplified setup/onboarding of new Vipps Sales Units.
* **[Preview]** Support for configuration |BetalingsService| accounts, using Infosoft as the Data Supplier.
* **[Preview]** Support for importing Payments and Mandates files from |BetalingsService|.
* **[Preview]** Support for exporting requests for Payments files to |BetalingsService|.
* **[Preview]** Support for adding subscription plans for products using editions.
* **[Preview]** The order endpoint now understands products and packages configured with Editions, and added support for indicating the number of editions during registrations.

Changed
-------

* **[Preview]** Subscriptions on editions can now be created and renewed like regular time based subscriptions.
* The automated |AvtaleGiro| mandate lookup is now set up to query multiple in case of intermittent issues with the Mastercard Payment Services API. The change should be mostly transparent as mandates are already imported multiple times each day.
* Calendars now only operate with Dates and not a combination of Date and Time, since the calendar is supposed to present entire days, not time ranges.
* **[Preview]** Allowed switching to |BetalingsService| Payment Agreements on subscriptions.
* **[Hotfix]** Changed handling of payments such that an exactly matching External Invoice Identifier incoming on a wrong organization is moved to the matching organization invoice. The source of these payments are typically handcrafted files, poorly written integrations, or previous misconfigurations.

Fixed
-----

* Distribution Innovation file export timestamps now include timezone information.
* Missing `UserAuthorizationGranted` and `UserAuthorizationRevoked` events when connecting users to subscribers or subscriber accounts.
* An error where manually defining a new due date during credit with a replacement request would be ignored, leading to an invalid due date for the replacement demand.
* An issue where reminder fee would not be included in the Invoice Reminder for Enterprise Plans.
* An issue where |Vipps| agreements could be imported without currency.
* An error where rare circumstances could lead to the same demand reminder being generated multiple times.
* A rounding error for invoices leading to invalid EHF files.
* **[Hotfix]** An error with multiple capture attempts on orders with |SwedbankPay| in case of intermittent errors from the API.
* **[Hotfix]** A regression for capturing payments for |SwedbankPay| where the description extended above the 45 chars limit defined by |SwedbankPay|.
* Fixed an issue that would lead to Power Bi datasets (and reports), to not be automatically refreshed, causing wait times for users when opening the reports every day.

Deprecated
----------
We call out the following deprecations, the endpoints/field will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* We are deprecating the endpoints ``/paymentdemand/{id}/credit/completely`` and ``/paymentdemand/{id}/credit/partially`` in favor of ``/paymentdemand/{id}/credit`` endpoint.
* We are deprecating the field ``TaxPercentage`` on the endpoint for creating Account Payment Demand transaction ``POST /paymentdemand/``, in favour of specifying a list of Tax Details.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* Exposed configuration for how to calculate VAT on billing fees.
* Additional validation to allow switching payment agreement to EHF or E-mail.
* Search for ADB2C users based on email address.

Changed
-------

* |Vipps| setup to support use of Infosoft Partner credentials.
* Switching Subscription Plan now displays the total amount of the new plan.

Fixed
-----

* A performance issue with payments in the overview dashboard to reduce load times.
* An issue where invalid export time was shown for Distribution Innovation (related to missing timezone in the API/Backend).
* An issue where it was not possible to switch to existing |AvtaleGiro| or |eFaktura| Payment Agreements.
* An issue where expired products were available for selection during creation of new subscription plans.
* A calculation issue in the dashboard which would include not-completed orders in the totals.

Self-Service and Sales Poster
=============================
No subscriber/user facing changes to self-service or the sales poster for this release.