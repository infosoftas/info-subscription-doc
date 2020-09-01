.. _changelog-r77:

************************
Release August 25th 2020
************************
Due to the summer holidays, the release has been some time coming (as announced previously).
The following changes rolled out to production on August 25th 2020.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added support for payment request failure handling (Payment Request Settings), allowing to configure how many times to retry payment requests, capture on card for instance. **(Preview)**

    * By default only one attempt is made on each payment request, and not all payment providers are subject to retry handling.
    * Feature must be configured to take effect.

* Added support for scheduling subscriber contact changes, both temporary and permanent.
* Added support to cancel/stop deliveries without stopping the subscription.
* New API for listing all generated Distribution Innovation transactions
* Preliminary support for Additional Products
* Added support for querying demand and reminder schedules, showcasing the planned generation time for Payment Demands and related Reminders.
* Preiminary support for contracts in Orders (binding the subscriber to a specific set of terms, subject to a fee if cancelled/changed ahead of time).
* Fixed an issue that allowed ExternalInvoiceIdentifier configuration to be created multiple times.
* Changed the behaviour of how Distribution Innovation Exports handles Address lines on the Subscriber Contact. Now extra lines are mapped to a separate information field.
* Extended the Invoice Document model with additional text lines beyond the default Text description.
* Template Packages with long descriptions will now have their descriptions truncated to the max limit allowed by SwedbankPay (formerly PayEx eCommerce).
* Fixed an issue in the reporting system leaving subscriber contact information after deleting the subscriber.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* New view for listing generated Distribution Innovation transactions **(Preview)**
* Added option to delete future subscription, typical for Orders starting in the future.
* Added support for additional products **(Preview)**
* Support for Shared Digital Access/Authorization - multiple users for single subscriptions managed by the subscriber **(Preview)**

    * Requires the use of Auth0.
    * Requires the use of Additional Products for template packages.    

* Expanded multiple list views with filtering support.
* New merged view for listing Invoices and Payments together.
* Adjusted the sorting and order of columns in listing for Invoices, Payments, Subscribers and Enterprise Plans.
* Re-arranged the reporting menu and sub-menus.
* Adjusted selection of payment method when placing new orders.
* Multiple visual adjustments to the Invoice Contact view, including several translation fixes.
* Fixed an issue where payments were not matched and approved automatically when registered manually (i.e not via an Invoice).
* Fixed an issue when displaying the subscription when crediting an Invoice.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Adjustments to overview/home view for subscribers.
* Multiple design adjustments for registering subscription changes.
* Additional information and minor visual improvements on the subscriber Invoice/Economy view.
* Improvements on mobile/tablet visuals.
* Added support for Shared Digital Access/Authorization - multiple users for single subscriptions managed by the subscriber **(Preview)**

Contact support for questions and details on participating in various previews - some are available for everyone but may change in API and behaviour, while others requires enablement.