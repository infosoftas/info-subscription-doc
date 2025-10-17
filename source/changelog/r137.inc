.. _changelog-r137:

********************
Release October 27th
********************

Is a minor release to fix two issues related to the order flow and evaluation of template subscription plan rules.

Fixed
-----

* An issue where chosen products would not flow to the next step in a chain of plans, causing the second and subsequent period to contain all available products instead of the chosen ones.
* An issue where the overridden price for an order would not flow to the next step in a chain of plans, causing the second and subsequent period to use the list prices instead of the overridden one.

**********************
Release September 23rd
**********************

Its autumn and while the rain pours down outside and the temperature drops, we sit behind our screens whittling away at the backlog.
Measured in number of changes, this is probably the largest release we have ever had. 
From the list below you can see there are a lot of different areas affected, and these are just the observable changes.

As some may have noticed the developer docs are also getting a needed expansion, for this reason we have added a short section here about doc changes as well.

We probably have 1 or 2 more releases for you this year, so stay tuned, and enjoy this release!

API and Backend
===============

Added
-----

* Support for Order Reference. A free form text field similar to Buyer Reference. Instead of following the subscriber, the order reference follows the subscription.
  
  - The order reference can be set on Orders, Subscription and Enterprise Plans.
  - IS carried on to the Invoice if present.
  - Available in the reporting data model for demands (if set).
  - It is also possible to set/remove order references during subscription changes.
  
* Support for handling |VippsMobilePay| agreements being stopped in the |Vipps| or |MobilePay| app. By default subscriptions will be set to another payment agreement, the behaviour can be changed to cancel the subscription instead.
* New orders can now consume existing account charges and allowances, the behaviour can be toggled with a parameter in the order flow.
* Support for reversals of |SwedbankPay| transactions.
* |Vipps| and |MobilePay| charges can now be refunded if captured.
* Subscriber contact information is included for account transactions in the reporting model.
* OrganizationId is added to the Payment Stop Schedule to ease querying and filtering.
* Support for DeactivationTime on PaymentAgreements.
* Improved validation when configuring how External Invoice Identifiers should be generated.
* Support for re-scheduling a reminder on an Account Demand.

Changed
-------

* Orders with |Vipps| or |MobilePay| profile collection will now cause a contact replacement. This is a change in behaviour, previously the contact would be added side-by-side in case of existing contact.
* Querying for PaymentDemands now includes settlement account transactions if they exist. This allows the caller to determine how a demand was settled instead of assuming it was paid directly.
* Removed simulated synchronicity behaviour for a series of endpoints:

    - Create Payment ( `POST /payment` )
    - Cancel Subscription ( `POST /subscription/{id}/cancel` )

* |AvtaleGiro| payment agreements are now deactivated when the underlying mandate is cancelled. Previously they were deleted from the query results.
* Extended Authorization product generation to include Additional Products included in subscription plans (purchased AddOns are not included until renewal, this will be added in a future release).

Fixed
-----

* An issue where |VippsMobilePay| account reference would not be validated in the API, leading to a bad caller experience (processing failure after acceptance of the request).
* Fixed an issue where the MerchantRedirectUrl for |VippsMobilePay| was not verified during order creation leading to a bad caller experience (processing failure after acceptance of the request).
* Fixed an issue with missing currency on account transactions when allowances were split during settlement.

Removed
-------

* The endpoint for changing packages (`/subscription/{id}/changepackage`) have been removed from the API. This was a deprecated endpoint and has been replaced by the more flexible scheduled subscription changes feature.
* The Enum value PayEx for PaymentProviderType has been removed. The value PayEx is still present where it was used as a string.

Merchant Client
===============

Added
-----

* Support for configuring deactivation behaviour for |VippsMobilePay| accounts. Default is to leave the subscription, but it can be changed to cancel the current subscription.
* Support for adding and showing the new Order Reference field.
  The support includes new Orders, subscription changes, displaying on running subscriptions and on Invoices.
* Password reset support for shared and email domain based users.
* Support for configuring invoice fees for additional payment provider types.

Changed
-------

* Changing to Email payment agreements now verify the existence of an email address on the subscriber.
* The data source used for searching/listing account transactions.
* Simplified the configuration of External Invoice Identifier generation scheme.
* Previewing Order details now adjusts for Permanent Discount settings.
* |Vipps| and |MobilePay| agreements now display the external Agreement Identifier making it easier to identify the right one.

Fixed
-----

* An issue where it was possible to attempt changing historic subscription periods.
* An issue where purchased Additional Products would not count toward the total number of shared users available.
* An issue where the display start time for deliveries was not adjusted for the distribution offset.
* An issue where display start time for product deliveries was not adjusted for the distribution offset.
* Formatting of some numbers in the dashboard.
* An issue where KPIs would show incorrect values in case of summaries being 0 (or not present for the given day).
* An issue where filtering choices for deliveries would not be consistent with the content shown in the result.


Self-Service, Sales Poster and Checkout
========================================

Added
-----

* Support for creating Vipps, MobilePay, Email and PEPPOL payment agreements on running subscriptions.
* Warning message for expired card payment agreements in use on a running subscription.

Changed
-------

* Changed order of subscriber contact information fields.
* Improved stepwise tracking support in checkout.

Fixed
-----

* General translation corrections for multiple languages.

Developer Documentation
=======================

A short list of things that have been added or significantly expanded upon in the documentation since july.

* Introduction to Additional Products (Add-ons).
* A primer on querying using OData and the Analytics API.
* References to test data for payment providers.
* Scenario description for bringing your own payment provider.
* More details and concept explanations in relation to billing.
* Visualizations for various entity relationships and timelines.
* New sequence diagram for orders including Vipps/SwedbankPay examples.