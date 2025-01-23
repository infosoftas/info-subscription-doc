.. _changelog-r131:

***********************
Release January 29th
***********************

As we enter the new year, we bring a new release with additional features and improvements.

This time around we are ready to announce a few big items

* **Checkout**: A brand new checkout experience. See the `main announcement <https://www.info-subscription.com/>`_ and `conceptual docs <https://docs.info-subscription.com/en/latest/managed-experience/selfservice/checkout.html>`_ for more information.
* **OData Analytics API**: We have added the ability to run OData queries directly from the API. This allows you to extract data for reporting and analytics purposes. See the `announcment <https://www.info-subscription.com/>`_ for more information.

While not directly coupled to this release, we would also like to call out our new Orders SDK for TypeScript/JavaScript developers. 
This SDK is available on `npm <https://www.npmjs.com/package/@infosoftas/s4-orders-js-sdk>`_ and on `GitHub <https://github.com/infosoftas/s4-orders-js-sdk>`_.

Without further ado, here is the full list of changes for this release:

API and Backend
===============

Added
-----

* Endpoint to validate organization number and GLN via MySupply Lookup API.
* OData queries for reporting and analytics can now be run directly from the API.
* Support for manually removing expired denial orders.
* Order support for different campaigns with |VippsMobilePay| depending on subscription plan setup.
* Enabled removal of automatic cancellation.
* Support for all |VippsMobilePay| campaign types. 

Changed
-------

* Extended status information for |AvtaleGiro| claims.
* Exposed additional products included in the subscription plan to the Payment Demands and Invoice respectively.
* Improved handling of partner authentication.
* Support for checking |VippsMobilePay| cancellation statuses on order completion.
* Include ExternalIdentifier when retrieving a subscriber if available.

Fixed
-----

* **Hotfix** Sorting for dunning setup to avoid wrong fees on reminders.
* Adjusted handling of mandates if creation and deletion happen on the same day to avoid multiple mandates.
* Resolved an issue where covering an account claim with extra payment created an invalid allowance.
* A bug where not completed orders were skipped by the automated clean up routine.
* Resolved a problem with Swedbank Pay transactions not being canceled when the order was aborted.
* An issue where |BetalingsService| did not handle rejected payments correctly.
* A bug in |eFaktura| synchronization that prevented new agreements if a previous agreement was canceled.
* Additional products are now included when calculating the next subscription period.

Merchant Client
===============

Added
-----

* Display planned reminders and potential deductions in the invoice detail view.
* Show additional products on the subscription details tab.

Changed
-------

* Removed view of failed card capture attempts, as it never worked.
* Show error and warning messages after importing payment files.
* Improved subscription display if there is a planned change to an edition-based plan.
* Show more information for rejected |AvtaleGiro| transactions (including code and text).
* Display external identifier for the subscriber if present in the main contact information line.

Fixed
-----

* **Hotfix**: Fixed broken links in some search results.
* Corrected MRR display so that an increase no longer appears in red in some cases.
* Fixed tab order when registering payments.
* Resolved an issue with fixed discount registration where fields were not cleared after saving.
* Fixed a display error on paid invoices that could indicate an overpayment when a subscriber was reminded.
* Fixed tooltip translation issues in the invoice list.
* Resolved creation of a new billing address even when choosing an existing address for an order.
* Corrected subscription list sorting so active subscriptions appear first.
* Fixed an error when uploading the same OCR error twice.
* Addressed a problem with subscription plan creation that could remove the option to select the number of issues.
* Fixed an error where migrated periods appeared as the invoice period on the first invoice.
* Corrected statuses in the completed payments list (hotfix).
* Fixed tooltips with EHF-payment agreements when validation fails.
* **Search**: Resolved UI mixing of Norwegian and English when switching languages.
* **Search**: Fixed detail view for orders.
* **Search**: Corrected content when downloading payments.
* **Search**: Fixed date display when searching for payments.
* **Search**: Addressed an issue when navigating between subscriber and search views.

* Future cancelled subscriptions are now displayed properly on enterprise plans.
* Addressed an error when creating orders after adding and removing an email for Enterprise Plans.


Self-Service and Sales Poster
=============================

Added
-----

* Checkout: New checkout solution available in preview. Contact support for more information.

Changed
-------

* Various UI improvements when used on devices with smaller screens.

Fixed
-----

* A user maintenance bug where the search field behaved oddly.
* Improved handling of ADB2C errors during signin.