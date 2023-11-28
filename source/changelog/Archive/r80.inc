.. _changelog-r80:

***************************
Release October 15th 2020
***************************
The following changes rolled out on October 15th 2020.
Again quite a few changes under the covers and work on unreleased features, but there is still a bit of public improvements.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added new template plan/package rule for allowing any number of available products to be selected.
* Fee information is now included on Payment Demands.
* Fixed an issues where invoices with ``null`` in quantity would cause clients to fail because it is not allowed by the swagger definition. These are now mapped to quantity ``0``.
* Extenions to reporting data

    * Subscription Contract Date
    * Essential Invoice metadata
    * Subscriber Account and Account balance

* Changed behaviour of automatic agreement switching so that subscriptions with a short length is not automatically switched to AvtaleGiro. Refer to the user documentation for details.
* Billing now re-calculates demand schedules and payment request processing and only switches outstanding schedules if it is possible to do within the limitations of the provider. The following demand will be handled according to the new agreement regardless. Refer to the user documentation for details.
* Fixed an issue where payment requests would sometimes be generated for the provider with an amount 100 times larger than specified on the plan (conversion error).
* EHF files will now have all dates converted to the local timezone defined on the Organization. Typically avoids issue where all dates are off by one day due to timezone issues (UTC to CEST or similar).
* Fixed an issue where EHF generation would fail when the demand and invoice included fees.
* Fixed an issue where failed SwedbankPay payments would still lead to payments being generated and demands settled as if the transaction was completed.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added support for configuring event hooks for failed payment requests. **Preview**
* Included a new view for listing failed payment requests. **Preview**
* Fixed a performance issue on the view for managing unmatched payments.
* Extended configuration options for Distribution Innovation. **Preview**
* Fixed an issue where duplicate products would not be shown in the subscription plan.
* Added option to configure new package/plan rule for allowing selection of any number of available products.
* Fixed a mapping issue with shared authorizations and updated the authorization routine to look at the shared authorizations to map the subscriber. **Preview**


Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Fixed an issue in the salesposter where the session would be stuck with the spinner after completing PayEx/SwedbankPay card payment, typically causing the subscriber to do another purchase.

* Several minor adjustments to the new salesposter included in previous release. **Preview**
  
  * Translations adjustments
  * Cookie handling adjustments related to language detection
  * Better handling of information retrieval when using Google as the social provider.
  * Fixed amount display for discounted subscription plans.


Contact support for questions and details on participating in various previews - some are available for everyone but may change in API and behaviour, while others requires enablement.