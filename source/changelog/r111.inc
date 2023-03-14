.. _changelog-r111:

***********************
Release March 14th 2023
***********************
This is a smaller release with primarily bug fixes and minor adjustments.
The client has been rolled out, as well as the first batch of self-service instances. The next batch will follow during the next couple of days.

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

* Added additional source/related properties to ledger transactions enabling easier source correlation (Invoices, Reminders, CreditNotes etc).
* Cached the OAS3.0/Swagger JSON generation for the API significantly improving load times.
* Added Invoice Contact Id in the API for Payment Demands and Preliminary Demands.
* Fixed an issue with eFaktura where Susbcribers would be assigned an eFaktura agreement even when the issuer was blocked by the consignment.
* Fixed an issue where allowance consumption of reminders would not settle the underlying demand if consuming all allowances would bring the payable amount down to 0.
* Preliminary Demands are now automatically removed when future subscriptions are deleted.
* Fixed an issue where Fees would not be reflected on the Invoice for new orders on existing SwedbankPay Card agreements.
* Adjusted Due Date handling for eFaktura during credit and re-issuing.
* Deliveries now handles subscription with an automatic cancellation, such that the delivery is marked as ended on the subscription end time immediately.
* Fixed an issue that would prevent new Subscription Orders with a start time exactly at the same time as a new price should take effect.
* Fixed an issue where it was not possible to upload Power Bi reports.
* Refunds based on Payments now sets the OrganizationId automatically based on the input payment.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Support for handling refunds. **Preview**

    * A view for listing and registering new refunds.
    * A search/grid view of all registered refunds including an export to CSV.
    
* Some improvements for searching by Invoice Number.
* Registering a new subscription will now automatically refresh the overview to provide up to date information.
* Fixed an issue where Vipps Recurring fees would be added using the wrong underlying type, essentially having no effect on the billing.
* Fixed an issue where adjusting any Organization parameters would essentially reset the configured time zone.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Translations and text improvements for Norwegian, Swedish and Northern Sami.
* Sales/Subscription terms can now be reference by a link instead of being embedded within INFO-Subscription, allowing out-of-band updates.
* Country for Invoice Contacts are now created in the same manner as the Subscribers country information.