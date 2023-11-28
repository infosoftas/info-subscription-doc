.. _changelog-r55:

**********************
Release April 2nd 2019
**********************
The following changes were rolled out to production on April 2nd 2019

New Features and improvements
=============================

* Additional KPI values in the overview/dashboard
* Journal/Report for Credit Notes
* Removed restriction on country when registrering new subscribers from the merchant interface
* Support for generating EHF Invoices for Subscribers with an Organization Number (Configurable using API only at the current time)

    * Credit Notes are generated, but they do not conform to the EHF 3.0 validation procedure. This will be fixed in the upcoming release.

* Added handling of password complexity error messages on the SalesPoster
* Added option for configuring stopping a subscription after the initial period effectively disabling renewals

Please refer to the user documentation on http://docs.infosoft.no for details on using the various features.

API Specific Features
---------------------

* Option for supplying contact details when creating a new subscriber
* Added resource to query for credit notes
* Added resource for importing completed PayEx agreements (for migration scenarios)


Bug fixes
=========
* A long series of text and translation adjustments to streamline terminology and fix errors
* Fixed issue where it was not possible to create billing plans with 24 month frequency
* Fixed an issue where organization number was not saved if no phone number was given on the SalesPoster
* Fixed an issue where organization information was not populated correctly on the ledger in the reporting data.
* Fixed a series of display discrepancies with prices in the merchant client (rules not being evaluated correctly for preview prices)