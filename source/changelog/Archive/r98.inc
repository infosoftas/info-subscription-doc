.. _changelog-r98:

***************************
Release Feburary 8th 2022
***************************
Another release started rolling out on Feburary 8th 2022.
The API and backend has been upgraded, and the self-service and merchant clients has finished rolling out.

Sorry for the delay of the changelog, but Covid-19 hits everyone and in this case the changelog author :)

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Payment Agreements can now be filtered based on Expiry date.
* When cancelling subscriptions, it is now possible to indicate the contract cancellation fee should be ignored.
* Fixed an issue where scheduled changes would be saved without timezone information.
* The backend now includes settings for configuring and using "Permanent Discounts".
* Added support support for automated settlement using Vipps **Preview**.
* Fixed an issue where in some cases a future payment demands would remain scheduled even when the subscription was deleted.
* Fixed issues with EHF generation where a mix of products with VAT would cause an invalid file.
* Fixed a bug where Subscription Plan Contract Time would be deleted when updating the contract.
* Fixed an issue where Vipps Payments would not be registered in cases where the related payment demand was credited.
* The Vipps integration now reports System and Plugin headers as requested by Vipps.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Scheduled Subscription Plan changes are now included in the subscription views.
* Fixed an error with the wrong details being displayed on Credit Notes.
* Changed the time shown for creditted payment demands.
* Included Additional Text on the Invoice lines.
* Fixed an issue that would lead to contact information not being saved for new invoice contacts.
* The merchant now allows crediting of Payment Demands created with AvtaleGiro.
* Fixed a bug where, in some cases, when creating or editing a Template Subscription Plan the valid from field would be wrong.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* It is now possible to configure required country on the salesposter.
* Street address is required if an organization number is supplied during registration.
* Multiple minor adjustments to the Kilkaya conversion tracking **Preview**.
