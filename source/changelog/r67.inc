.. _changelog-r67:

**************************
Release December 17th 2019
**************************
The following changes were rolled out to production on December 17th 2019

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added support for cancelling subscriptions on running Enterprise Plans with automatic crediting of the subscriptions if the demand is issued.
* Added support for crediting subscriptions on an Enterprise Plan demand.
* Added option to do a plan change during a period, causing a proration for the consumed and remaining period calculated in entire days.
* Improved internal validation for creating enterprise plans, in cases where the client is not entirely "compliant".
* Populated additional fields for EHF adding support for seller bank account number and adjusted Organization Numbers to be populated correctly for tax groups.
* Fixed an issue that made it possible to import the same Payments file multiple times.
* Extended the reporting datamodel with support for enterprise plan demands.

Client
======
The following new features and improvements are now available in the web client

* Added option to choose between generating a new followup demand when crediting a demand, or just creditting.
* Added quick link to go directly to Subscriber from the Payment Management view.
* Adjusted Payment Management view to better highlight the state of the Payment.
* Minor adjustments to Enterprise Plans related to activation and de-activation.
* Multiple language adjustments
* Added salesposter support for Auth0 login procedure that makes non-subscriber logins invalid.
* Fixed a bug in self-service where Phone number could not be updated.
* Fixed a reporting issue causing Enterprise Plan payments to not be listed.
* Adjusted date fields to be locked to the datepicker.
* Template Plans can no longer use multiple Billing Plans (temporary UI simplification)
* Added support for plan change during running subscription period (with proration as described above).

.. Important::

    We have rolled out an optional change to the authorisation mechanism in Auth0 so that users without Subscriber associations cannot log in.
    This change is currently an opt-in feature (contact us!) but we are working on making it mandatory for all tenants, but it requires more testing.
    This change is not directly related to the release, but requires changes to the ordering process as denoted above.


Known Issues
============

* When demands and invoices with reminders (that has fees) are paid, it is not obvious from the API and the client whether the fee on the demand has been settled or not.
* External Invoice Identifiers may be generated in a way that exceeds the allowed length when Subscriber Number and Invoice Number lengths exceeds the max length.