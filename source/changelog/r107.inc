.. _changelog-r107:

****************************
Release November 9th 2022
****************************
Another month another release. Quite a few minor improvements and as always some work behind the scenes on new features and technical adjustments.

The API, backend and merchant has been rolled out, the self-service clients will be rolled out progressively during the next few days.
This time around we are not rolling out an upgraded version of the individual merchant instance, only the one accessible at https://merchant.info-subscription.com will be upgraded.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Option for registration of refunds, either based on payments or free standing **Preview**.
* The EHF generation now queries the Peppol registry for Organization Number and only produces EHF files for recipients registered as Invoice recipients.
* Added configuration option for Distribution Innovation setup for a custom filename.
* The Distribution Innovation export now uses the configured custom filename as well as the given distribution date.
* Introduced a settlement policy configuration controlling when to settle payment demands **Preview**.
* Processed Payment Requests now includes a counter for number of previous request processing attempts.
* Swedbank Pay Payment Agreements are now populated with cardmask, expiry date and brand during if not given during agreement import.
* Fixed an issue where the reporting subsystem would not have the correct information on Subscriptions and Subscription Plans.
* Fixed an issue where not all reminders would be generated in the reporting subsystem.
* Added a validation mechanism to prevent multiple reminders being generated with the same Id.
* Improved validation messages for payment matching failures.
* Improved resiliency so generating multiple payment agreements is less likely to cause a delay in handling.
* Introduce a new API IdP (token provider), refer to the separate section for details.

New API IdP (Token provider)
----------------------------
This release we also introduce a new provider for generating authorisation tokens to the API.
Previously |projectName| has relied entirely on Auth0 as the IdP, but for various reasons we are switching to ADB2C moving forward.

As an API consumer you do not have to do anything at the current time. We will be onboarding new tenants using the new IdP while old ones will continue to work for quite some time.

If you want to start migrating already you can read more about the :ref:`auth process <authorization>` and you can reach out to :ref:`support <reporting-bugs>` 

.. important::
    
    We are NOT switching off the Auth0 IdP in the near future, and you WILL get an advance notice before we switch off anything.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Exposed event configuration for new evens `PaymentRequestProcessed` and `PaymentRequestScheduled`
* Various minor text and translation adjustments
* Fixed an issue where number of units was not transfered when pausing a subscription.
* Fixed an issue where it was not possible to specify a custom email for Invoice and Credit Note copies for Enterprise Plan invoices.
* Introduced configuration for default currency, mostly relevant for payment registrations currently.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Better feedback when registering new shared/family users. 
* Proper error message in case of insufficinet password complexity during user creation in the order process.
* Fixed an issue where the contact was duplicated when reusing an existing contact during orders.