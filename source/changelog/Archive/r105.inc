.. _changelog-r105:

****************************
Release September 12th 2022
****************************
A new month, a new release. As always the API and backend has been rolled out entirely, and the frontend/UI will be rolled out over the next couple of days, some UI instances have already been deployed.

Those of you on the new administrative merchant UI instance are all upgraded to the latest version.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* New "helper" API to support the GDPR "right to erasure". This now supports getting rid of Subscribers, Deliveries and Invoices with sensitive data. The legally required data of the Invoices are kept while subscriber information is scrubbed.
* Fixed an issue where querying for available products on a user would give an invalid result **Preview**.
* Getting a specific Credit Note file from the Invoice/CreditNote API would always cause an 500 Internal Server error. This has now been fixed.
* Extended information on contract surcharge fees when cancelling subscriptions.
* Fixed an issue where subscriptions would sometimes use the wrong organization configuration.
* Multiple adjustments to the billing handling of subscription cancellations with a calculated surcharge fee, such as:

    * Include support for VAT transfers of unsettled demands.
    * Initial/Order demands, not settled, will now be automatically accounted and included in the surcharge demand.

* Ordering new subscriptions with an existing AvtaleGiro payment agreement/mandate will now correctly issue the AvtaleGiro claim.
* Added sanity check to prevent cases where multiple payment requests (charges) would occur when payment card retries were configured.
* Fixed an issue where ordering on existing Swedbank Pay payment agreements could lead to payments being generated even when the charge/transaction fails.
* Crediting Recurring and Account Demands with a replacement demand now supports keeping any Account transactions (charges and allowance) associated with the original demand.
* For subscription plans with an initial offering of "until years end" would not adjust for the local time zone of the organization. This has now been fixed.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Various additional features and fixes related to ADB2C as end-user authorization backend **Preview**.
* Added multiple translations for views related to connecting subscribers with users.
* Added new configuration option to allow/deny orders with a historic start time.
* For multi-tenant users the list of available tenants now scrolls instead of being endlessly long past the edge of the screen.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Multiple ADB2C user authorization adjustments and fixes **Preview**.
* Added new configuration options to toggle on/off some of the self-service features (administrative UI will come in a later release).