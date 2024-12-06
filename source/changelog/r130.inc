.. _changelog-r130:

*********************
Release December 11th
*********************

As we reach the end of the year, and the holiday seasons for many, we roll out a new release.
This time around the changelog is rather long, with lots of minor improvements and especially UI changes building upon work done in previous releases.
We would like to call out the new KPIs in the dashboard, a small change that everyone will notice immediately, and hopefully find useful.

Until next time: Merry Christmas and a Happy New Year from the INFO-Subscription dev team. We hope to bring you more feature packed releases next year!

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Reporting for the recently introduced revenue KPIs now include a timestamp for the last update, similar to other KPI records.

Changed
-------

* Subscriptions created due to a plan change will now have its `SourceType` set to `ChangePackage`. In addition we now set the `PreviousSubscription` to the subscription that was changed from.
* Handling of |AvtaleGiro| mandates during automatic change import so that changes in non-operation fields will not cause an update to the underlying mandate and payment agreement.
* Webhooks for new tenants will now only support TLS1.2 or newer. We have yet to decide on a forced migration/upgrade of existing registrations.
* Seeding of SubscriberNumber Sequence configuration will no longer reset manually configured sequences during scaling operations.
* It is no longer possible to switch a subscription to an inactive payment agreement. This will cause a validation error.

Fixed
-----

* An issue where it was not possible to order with |Vipps| and |MobilePay| for subscriptions based on Editions.
* Multiple issues related to converting Editions to periods based on calendars. Mostly related to edge cases where changes happened on the same date as a release on the calendar.
* An issue where updating `PaymentRequest` retry handling on an existing dunning process would not be processed.
* OpenAPI schema definition for `SettlementPolicy` for multiple dunning process related operations. It will now correctly specify `OneOf` with the correct structure instead of just specifying the `PolicyType`.
* An issue where importing existing |SwedbankPay| agreements would fail due to missing token references.
* An issue during |VippsMobilePay| agreement import where campaign types with missing information would lead to import failures. They are now correctly changed to a different campaign type internally to allow the agreement import.
* Warnings and Errors are now correctly shown when importing payment files with non-structural errors. For instance when no matching organization setup is found.
* **Hotfix** An issue when handling |VippsMobilePay| user profile information during orders, with automatic profile gathering, that would cause the order to fail in some scenarios.

Deprecated
----------

We call out the following deprecations, the endpoints/field will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* VippsParameters should no longer be used for new Orders, instead use the similarly named property VippsMobilePayParameters which also contains new optional fields for profile sharing.
* We are deprecating the field ``TaxPercentage`` on the endpoint for creating Account Payment Demand transaction ``POST /paymentdemand/``, in favour of specifying a list of Tax Details.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* Option to configure SettlementPolicy in the DunningProcess configuration.
* Possibility to configure ReminderPolicy in the DunningProcess configuration. Specifically this allows toggling on/off whether to automatically write off reminder fees for payments matching the original payable amount.
* Support for selecting a new Payment Agreement during credit and re-issue. Useful for cases where the Subscription the demand is based on is already started.
* Subscription Plans can now be configured to participate in Order Denials evaluation for Offers. A mechanism to avoid repeat subscriptions on offers.
* Support for viewing and modifying typed Order Denial entries for subscribers. Previously there was only one type, so it was impossible to note the difference between them.
* Renewal name and description for subscription plans to use after the initial period. If left blank the behaviour will be to use the default text and description.
* New KPIs in the dashboard for Users and MRR (Monthly Recurring Revenue), including a change relative to 30 days ago.

Changed
-------

* Filtering deliveries now allows for selecting calendar release dates instead of just regular dates for products with editions.
* Order Denials are now highlighted during orders registered from merchant in cases where it is relevant.
* When maintaining release calendars an edition number is now shown with the calendar.
* Sanitized the subscription view related to information from the original order, among others removed one of the Order dates.
* General cleanup of the subscription view to streamline placement of information and buttons.

Fixed
-----

* An issue where EHF would not be available when changing/adding Invoice Contact.
* An issue where changing from using CVR/Organization Number to GLN would demand a new PaymentAgreement, even though its not required.
* An issue where switching from Email or Invoice to a new EHF Agreement would instead generate an OIO based PaymentAgreement.
* An issue where main users deleted in the source directory would lead to the users page not being rendered.


Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self service and sales poster.

Fixed
-----

* An issue where it was not possible to add a new scheduled address change.
* An issue where configured cancellation reasons would not be shown if cancellation was only allowed at the end of the active subscription period.

Changed
-------

* After self-service logout user is now automatically redirected to the tenant home page (if configured) after a short period of time.