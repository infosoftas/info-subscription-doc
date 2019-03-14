*********************
Release March 15 2019
*********************
The following changes were rolled out to production on March 15 2019

New Features and improvements
=============================

* Improvements to the sales poster/order page (see separate section)
* Invoice Address/Contact administration
* The Administration overview/dashboard now shows real values for most KPIs (previously they were dummy fields for demonstration purposes)
* Support for administration of Subscriber Organization Number
* Support for generating Invoice data to Arvato Factoring
* Administrative option for specifying number of units on new subscriptions
* Support for crediting demands and invoices (limited preview)
* New Billing Frequencies 2 Days and 2 Years

Sales Poster Improvements
-------------------------
With this release the sales poster has been updated with a few extra features

* Introduced configuration through query parameters allows turning options on and off as required. Some of the options available are listed here:

    * Language
    * Available payment type
    * Invoice Address/Contact
    * Organization Number support
    * Subscription Plan
    * Redirect after order
    
* Translation into Swedish and English (previously it was Norwegian only), together with the language selection options
* Styling changes to closer resemble the look and feel of the self-service pages


Bug fixes
=========

* Fixed an issue where already logged in customer would get an internal server error when ordering new subscriptions
* Fixed an issue where creating a new product and auto-generating a subscription plan would lead to a Bad Request Error message.
* Fixed an issue where updating a subscription plan with a discount would generate an error message
* Fixed an issue where subscriptionplans with no fixed price would be displayed with price 0 when administratively placing new orders.
* Fixed an issue where the wrong total was shown on the subscribers balance.
* Changed how manual payment are registered when entering an Invoice Number so it associated with the Invoice correctly. 
* Fixed multiple errors related to date and time registration and display.
* Fixed an error that caused subscription to not be stopped when registred with automatic stop and an offer.