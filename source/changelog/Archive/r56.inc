.. _changelog-r56:

***********************
Release May 2nd 2019
***********************
The following changes were rolled out to production on May 2nd 2019

New Features and improvements
=============================
* Added payment stop rule for dunning process
* Added support for viewing, registering and updating notes on subscribers
* Exposed new OrderProcessed event for web hooks to consume
* Added proration for cancelled subscriptions
* EHF Credit Notes are now generated so they pass validation
* Added support for automatically stopping a subscription at the end of a period (first period, or chained)

Refer to the user documentation for details on how to use the new features.

Client
---------------------
The following changes affects only the client (merchant or self-service).

* Support for configuring EHF Invoicing
* Adjustments to the displaying of Invoice Payer on subscriptions
* Self-Service page now displays VAT for subscriptions
* Creating a new invoice payer from the merchant client now associates that payer with the next subscription period
* Crediting a demand now shows the date the credit was registered

API
---
The following new features are only visible in the API and does not affect the clients

* Added resource for Payment Demand Details as a property on Payment Demands.

Bug fixes
=========

* Fixed an issue where the Merchant client was counting orders multiple times for the KPI Overview
* Fixed an issue where no data was retrieved when generating a report on credit notes
* Fixed an issue where payment files were uploaded even if the user answered "No" to the prompt to proceed
* Fixed a series of bad translations in merchant and salesposter
* Fixed an error where enabling and then disabling fixed price on plan configuration would cause a validation error
* Fixed an issue where registering multiple discount percentages when configuring a plan would case a validation error
* Fixed an issue when creating an invoice payer without an email
* Fixed an issue when ordering a new subscription with an existing user
* Fixed an issue where organization number was not saved when creating an order with an invoice payer
* Fixed an issue where amount in EHF files was not rounded to two decimals
* Fixed an issue that caused failures when ordering with an invoice payer with a blank (not empty) telephone number
* Fixed an issue where it was not possible to register web hooks using the API