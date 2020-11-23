.. _changelog-r82:

***************************
Release November 25th 2020
***************************
The following changes started rolling out on November 25th. 
As usual the API and backend changes have already rolled out to everyone, while the client roll out will happen gradually during the next couple of days.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added type declarations to Payment Demands.
* Expanded the properties of Payment Demands to include additional details on the state.
* Added support for querying on the state of payment import processing.
* Extended transaction state information for Swedbank Pay / PayEx eCommerce transactions.
* Replaced Swedbank Pay, Payee Reference with a proper tracable reference Id.
* Extended the reporting subsystem with reminders and tax breakdowns on demands.
* Fixed an issue where demands for Enterprise Plans would not include all details in the reporting subsystem.
* Fixed multiple issues related to how billing handles switching of Payment Agreements on a running subscription.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Introduced support for displaying Balance/Account Demands (Preview).
* Invoice and Reminder fees are now displayed separately.
* Multiple adjustments on how fees are displayed for Invoices and Demands.
* Added processing log view for imported payments.
* Additional translations for product details on subscription plans.
* Invoice and Creditnote search views now includes filters for organizations.
* Added additional fields for searching on Invoice Contacts.
* Adjustments to how alternative organization number is displayed.
* Fixed multiple issues with grid/list virtualizations causing a scrollbar to be displayed even when there is sufficient screen real-estate.
* Fixed isse where new list prices would not be reflected for orders on old/existing template plans.