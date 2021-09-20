.. _changelog-r86:

*************************
Release March 4th 2021
*************************
The following changes started rolling out on March 4th 2021. 
The release has propagated to all tenants.


API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Behaviour changed for automatic credited periods. Automatic crediting will now count all days that have started as consumed entirely and not credit them. 
  Previously if a cancellation and related automatic credit would potentially give an entire day away for free if the timestamp was not exactly at the new start time. 
  While technically correct, it was rarely the desired behaviour.
  Automatic crediting now handles this case in the similar way as manual crediting so all started days are consumed entirely.
* Added support for scheduled subscription plan changes, to avoid immediate plan changes causing new demands and invoices when there is a likelyhood additional changes will happen **Preview**.
* Added support for configuring Default and Swedish External Invoice Identifier providers, this allows to actually generate these types of External Invoice Identifier **Preview**.
* Fixed serveral issues related to AvtaleGiro.
* Fixed an issue where draft subscription plans would show the wrong price during orders (directly affected the sales poster). Note this only caused a display error during the order process, the actual plan was correct.
* Fixed an issue that would sometimes cause wrong tax calculations for subscriptions and payment demands.
* Data sources are now automatically refreshed for Power BI reporting.
* Updated default reports for payments and subscription plans.
* Fixed an issue where payment demands would not be re-generated in cases where they should.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Support for configuring Swedish Bankgirot as External Invoice Identifier model **Preview**.
* Added support for listing original order details for a subscription plan.
* Crediting now allows adjusting the credit reason.
* Added UI for using system defined Swedish Tax Groups.
* Change the number of results of paginated views from 20 up to 50.
* Fixed an issue where Enterprise plan views would link to the wrong subscriber.
* Fixed a bug where querying for payments would lead to errors if there were no results for an organization.
* Adjusted behaviour with date inputs so the timezone is now considered in all cases.
* Multiple adjustments to interactive Distribution Innovation query support **Preview**.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Removed invoice draft.
* Fixed an issue where no confirmation/receipt would be shown when cancelling a subscription.
* Fixed issue with missing order confirmation on the salesposter when completing an order using Swedbank Pay.
