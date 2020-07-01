.. _changelog-r76:

**************************
Release June 30th 2020
**************************
The following changes rolled out to production on June 30th 2020.
Due to issues with the previous release, this is essentially two releases rolled into one.

This will also be the last release before summer hits us - so don't hold your breath till the next one. It probably wont arrive before late August at the earliest.
Have a nice summer!

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Extended recurring deliveries with support for only allowing single deliveries of a product. Previously parallel/concurrent deliveries were always allowed.
* Fixed an issue for recurring deliveries where cancelling a single subscription would stop all deliveries for that subscriber regardless of subscription.
* Support for adjusting a sequence number series upwards. Downwards adjustments are disallowed to avoid sequence conflicts.
* Fixed a series of minor issues related to SwedbankPay (PayEx eCommerce).
* Expanded the Invoice API with support for Charges and Allowances.
* Changed the behaviour of initial period length configuration so that after the initial period, the full price will be selected instead of the plan price. This is more in line with the expected behaviour.
* In extension to the above we have added support for configuring subscription plans with automatic stop together with a custom initial period length. This was previously rejected as an invalid plan setup.
* Fixed an issue where switching payment agreements would not generate a new payment request, if the request was scheduled but not sent.
* Changed operation names in the API to avoid Swagger/OpenAPI errors.
* Extended the reporting data with contact and enterprise plan information.
* Improved validation for External Invoice Identifier configuration changes.
* Fixed an issue where cancelling a running subscription would not lead to an automatic credit proration of the remaining period.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added configuration views for Distribution Innovation for recurring deliveries export (Preview).
* Added configuration support for SwedbankPay (PayEx eCommerce).
* New view for listing corrections (Preview).
* It is now possible to register manual corrections on Enterprise Plans in addition to regular subscriptions.
* When manually registering payment of an Invoice the amount is now pre-filled - reminders are not yet considered.
* Fixed an issue that allowed manual registration of payments for an Invoice on the wrong Organization.
* Fixed various issues related to handling of multiple organizations, both with registration and displaying of information.
* Added option for querying for Subscriptions using Invoice Contact details.
* Extended user management support to delete subscriber users from Auth0.
* Added translated messages for the various payment matching rejections.
* Fixed an error related to configuring External Invoice Identifiers.
* Included multiple default subscription reports (Preview).

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Added multiple missing translations for both English, Swedish and Norwegian in the salesposter.
* Added support for logging in as an existing user during order registration.