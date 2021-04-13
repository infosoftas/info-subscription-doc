.. _changelog-r87:

*************************
Release March 24th 2021
*************************
The following changes started rolling out on March 24th 2021. 
The API and backend has been rolled out to all tenants, and the client will be propagated over the next couple of days.


API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Behaviour changes for Enterprise plans

  * No Automatic crediting on cancellations: Previously when a subscription on an enterprise plan was cancelled, the related demand would be automatically credited like a regular subscription.
    However, customer feedback indicates that this is not the desired behaviour, so it has been disabled globally until we implement a policy to configure this behaviour.
  * Enterprise Plan demands are now grouped by their Due Date instead of by the Subscription Start date. This will cause additional demands to be generated, but the resulting due date is predictable.

* Additional configuration options for the Distribution Innovation integration **Preview**.
* Relaxed constraints for generating Payment Agreements to facilitate non-invoice and non-card agreements.
* Multiple adjustments related to scheduling and due date calculations for AvtaleGiro **Preview**.
* Changing of subscription plans can now be scheduled in addition to immediate execution. The billing routine behaves differently in that scheduling won't cause immediate billing effects like cancellations and automatic crediting.
* It is now possible to register configurations for the Default and Bankgirot External Invoice Identifier formats. Both configurations are always fixed, but this now allows the usage of these configuration for invoices.
* Fixed an issue where registering Avtale Giro agreements on a monthly subscription in late Feburary in a non-leap year would cause the agreement to not be toggled automatically.
* Fixed an issue in the reporting subsystem where product and tax details would not always be generated for demands.
* Fixed an issue where the wrong Vipps environment would be used during agreement creation **Preview**.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Multiple visual adjustments to Enterprise Plan configuration and current subscriptions.
* Changed how fees are displayed for specific demands.
* Removed deprecated default reports.
* Improvements to shared authorizations, specifically for handling more than 1000 authorizations on the same subscription.
* Improvements to the confirmation page when changing address and contact information in general.
* The Paid On date for Invoices now shows the organizations accounted time instead of the subscribers payment time.
* Multiple translation improvements

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Improved error handling for Invoice copy when external provider reports errors
* Fixed an issue with in the salesposter when the currency was something else than NOK.
* Additional translations.
* Added option for order confirmation and details information page in the salesposter.
