.. _changelog-r83:

***************************
Release December 17th 2020
***************************
The last release of the year - lets hope for a bit more regular year for 2021 :)
The following changes has started rolling out, all backend/api changes have been deployed while Client changes are propagating gradually over the next couple of days.

We are continuing to do changes behind the covers, mostly related to performance, but quite a bit related to resilliency for external services as well.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Vipps Recurring Mobile Payments (Preview)

    * Orders can now be placed with Vipps Parameters, similar to Swedbank Pay parameters.
    * Vipps Settlement files can be imported to generate payments (Sorry but Vipps has no API for this).
    * Possibility to register Vipps Agreements and connect them to a subscription.

* Adjusted the Swedbank Payee Reference to be a truly unique reference, and added it for local tracking. Previously it was not unique among organizations, which could cause some problems.
* Adjusted handling of subscription plan changes (package changes), so that changes with a target date equal to the end date of the period will be accepted as occuring on the end time (note the subtle difference between time and date here!)
* Fixed some Swagger/OAS2.0 validation issues with duplicate naming
* Subscriber and Payment Demand endpoints now provides more meaningful validation messages (Unknown Error Occured is not that helpful!)
* Exposed new events for Subscriber and Subscriber Contact related occurences. Refer to the swagger definition for all available events.
* Payment Agreement now includes a payment method "Mobile", in support for Vipps and other future mobile providers.
* Invoice Payment agreements are now marked properly as "InvoiceOnly" in all cases, previously some agreements were not marked with a payment method.
* Invoice Documents now include optional periods so that no all entries needs to have a timeline.
* Fixed an issue where Enterprise Plan Payment Demand generation were scheduled a period later than desired.
* Fixed an issue where the Minimum Due Days was not taking into consideration when scheduling Enterprise Plan Payment Demands.
* Subscription Plans without a description will no longer fail in Swedbank Pay as the Subscription Plan Name is used instead (still subject to character limitation cut-off).
* Multiple fixes related to changing payment agreement for a running subscription.
  This includes behavioural changes in billing when switching from Invoice to a Card, Mobile or Direct Debit and visa versa.

Clients
=======
The following new features and improvements are now available in the clients.

Most of the UI work this time has been related to internal house-keeping and features not yet completed.

* Support for Vipps Recurring Mobile Payments (Preview) - Salesposter, Self-Service and Merchant.
* Added configuration option for requiring address when defining organisation number. Not in the UI, please contact us if you require this option toggled.
* Handling of local culture decimal notation on corrections.
* Subscription plan price is now correctly recalculated in case the list price has changed since the template plan was created.