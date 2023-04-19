.. _changelog-r112:

************************
Release April 18th 2023
************************

Happy easter everyone! We are back with another release, following the easter holidays it is a bit delayed but not by much.
This release contains a slew of bug fixes and some new features of varying importance.

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

* Preliminary Payment Demands and Payment Demands now include an InvoiceContactId that was inferred from the Subscription or Order generating the Payment Demand.
* The OAS Spec now includes Transactions for Account Payment Demands. 
* Transactions are included when querying/retrieving Account Payment Demands.
* Added E-mail as a separate Payment Provider type to allow separate billing fees to be configured.
* Removed deprecated PayEx POPS API Endpoints. The POPS platform has been shutdown for some time.
* Added support for bulk deletion of future subscriptions related to Enterprise Plans and prevented individual cancellations for the same subscription types.
* Added support for consuming Account Transactions for Subscription Plan changes (automatic proration on changes).
* Extra ordinary payments now has the option of settling old outstanding payment demands.
* ReminderId is registered for Subscriber Ledger Charges generated for reminders.
* The reporting sub-system now updates materialized subscriber contact information on current/active subscriptions when subscriber contact information is changed.
* When generating account charges for partially settled payment demands, the charges are now split by Product and Tax causing multiple charges to be generated and tracked separately.
* Fixed an issue where an invalid credit ledger transaction was created when amending/removing a future cancellation.
* Fixed an issue where Invoice Fees on Enterprise Plans did not include VAT.
* Fixed an issue where an Invoice Line would be generated with Start and End on the same time for Account Demands without a period. It now only generates a Start and leaves the End empty.
* Fixed an issue where updating Reminder Policy on a dunning process would not actually update the policy.
* Fixed an issue where subscriber name and number would be stripped after crediting and re-issuing an Enterprise Plan Payment Demand.
* Credit Time on subscriber Ledger transactions now use the time of registration instead of the cancellation time when a subscription cancellation leads to an automatic crediting.
* Fixed an issue with recurring deliveries related to deleting future subscriptions.
* Fixed an issue where EHF would be generated in a way that was invalid for receiving subscriber contact did not have an email address.
* Fixed an issue where subscription with an Initial Term for the current month would generate an invalid timestamp when observing DST.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* For users with multiple available tenants, the last used tenant is now persisted across sessions.
* Added support for exporting subscriber ledger entries.
* Added configuration that will allow tenants to hide irrelevant Payment Import formats based on country.
* Added/Moved settings for final/balance invoice that supports the changed backend processing.
* New subscriber contact identification HPR (Norwegian Health Personell Registration Number).
* Multiple adjustments for Billing Plan and Dunning Process setup.
* Zip and City/Area has switched placed in contact overview.
* When creating new subscription orders, a small polling delay has been introduced, in order to display the newly generated invoice and payment demand in most cases without requiring a manual refresh.
* Chain Steps are now sorted by the step order when editing existing chains.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* New subscriber contact identification HPR (Norwegian Health Personell Registration Number) can now be toggled in the Salesposter.