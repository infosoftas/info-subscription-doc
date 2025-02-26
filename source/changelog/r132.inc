.. _changelog-r132:

*******************
Release March 4th
*******************

Second release of the year, with just a few new features and improvements.
We are chipping away at various UI related pain points and improving the overall user experience.
We are also working on a new feature that will allow you to add additional products to a subscription.

API and Backend
===============

Added
-----

* **[Preview]** Support for additional products on running subscriptions and new orders with billing and proration. :ref:`Contact support <reporting-bugs>` if you want to participate in the preview.

Changed
-------

* Restriction to prevent changing to a different Organization or Currency during plan change.
* Prevent attempts to cancel charges that are already given up (by Vipps) or canceled.

Fixed
-----

* **[Hotfix]** An issue where invoice documents would not be generated and sent to the PEPPOL network.
* Fixed an issue with incorrect topic name usage causing tenant name changes to break event handling.
* An issue where Revenue KPI calculations use full days instead of fractional days similar to the rest of the billing logic.

Merchant Client
===============

Added
-----

* Option to select payment method when creating or changing an enterprise plan.
* New mechanism to initiate password change/reset for end users.
* Option to select or create a new billing account when manually creating an account invoice.

Changed
-------

* Made starttime mandatory when creating an account invoice.
* Improvements to the orders view allowing for better overview of failed and aborted orders.
* Extended price display in various views to show both inclusive and exclusive of VAT, previously it was always inclusive.
* Changed the grid/view for configuring subscription plans as a PoC for other grids.

Fixed
-----

* An issue where creating a new main user would lead to an in-intelligible error message.

Self-Service, Sales Poster and Checkout
========================================

Added
-----

* Support for Spanish language in the Checkout.
* Support for Spanish in Self-Service.

Fixed
-----

* **[Hotfix]** An issue in checkout where starting the order process would always fail.
* **[Hotfix]** A rendering issue in checkout causing multiple "rerenders" after user registration in ADB2C.
* An issue where rewriting the url if initiated with the pilot version URL would dump all passed parameters.