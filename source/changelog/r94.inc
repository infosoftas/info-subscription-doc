.. _changelog-r94:

****************************
Release October 13th 2021
****************************
The following changes started rolling out on October 13th.
The API and backend are being rolled out to all tenants at the same time, and the client will be propagated over the next couple of days.


API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added an option that allows defining an alternate billing plan for contract surcharge billing.
* Introduced an option to allow for multiple charge attempts on Swedbank pay agreement in case the initial charge fails to produce a payment.
* It is now possible to some updates on Dunning Processes. As always these will only take effect on subscriptions renewed/created AFTER the update, not on an already planned dunning actions.
* Added policy support contract surchages calculations, either based on entire frequency or number of remaining/consumed days. The default remains number of remaining/consumed days.
* Fixed an issue where failed Swedbank pay transactions would be marked as Captured even though they were actually failed (just a display error).
* Fixed an issue for BgMax payment imports where grosly invalid identifiers would cause the payment import process to stop for the entire file.
* Fixed an issue in the reporting subsystem where the KPI for daily paid amounts would not handle multiple payments registered with the same timestamp.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Allow sorting of Subscriber Notes.
* Filtering is now available for recurring deliveries **Preview**
* Fixed an issue where the wrong credit time was shown in the invoice view.


Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Fixed an issue where it was not possible to switch back to Swedish.
* Additional translations for Swedish related payment methods.