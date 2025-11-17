.. _changelog-r138:

**********************
Release November 17th
**********************

We are ready with the november release. This time around we have quite a few UI adjustments and fixes. 
Most of the work done in the API and Backend is under the hood and won't be directly visible. 
We are in general focusing our efforts on improved performance and building the foundation for future features.


API and Backend
===============

Breaking Changes
----------------

In this release we have tightened the serializer behaviour when handling JSON data. 
This means that in some cases clients may have sent invalid JSON, which has been handled regardless because the serializer was lenient.

With the change, the schema-valid JSON will be handled as before, but invalid JSON will now be rejected with an error.

This is strictly speaking a breaking change, but we expect that very few clients will be affected, and additionally it is just an enforcement of the existing schema.

Added
-----

* Support for new Billing Frequencies, 3, 4 and 6 weeks.

Changed
-------

* Creating scheduled subscription changes no longer waits for the processing to complete before returning. This improves responsiveness of the API.
* An empty body is permitted on subscription cancellations, previously a body was required, even if it was empty.
* Added Organization Number in the eFaktura requests to adhere to new requirements from Mastercard Payment Services and the norwegian banks.
* The OpenAPI schema now references a shared header parameter for the `S4-TenantId` header. This reduces the size of the schema significantly.
* The OpenAPI schema no longer includes all possible input formats acceptable by the runtime, so for the most part `application/json` is the only documented type. If you previously used `text/json` or  `application/json-patch` these will continue to work for the foreseeable future, but we recommend switching to `application/json`. Some generator may have had issues with multiple content types, so this change should help with that as well.

Fixed
-----

* An issue where Template Plan validation passed, even if some of the products did not have a valid price.
* An issue where no validation information was returned when creating the same sequence multiple times.
* An issue where some transactions on Account Demands would be created without Currency information if the Account Demand was generated due to a previous payment related cancellation.
* An issue where deliveries would not be handled correctly in case of a subscription plan change, leading to missing delivery notifications.
* An issue with missing contact information in reporting when automatically retrieving subscriber contact details from |VippsMobilePay|.
* An issue in the order API where Order Reference was not forwarded properly.
* OpenAPI schema no longer contains an invalid definition for optional types. Instead the types renders as `OptionalOf`.


Merchant Client
===============

Added
-----

* **[Preview]** Support for including existing balance on an account when creating a new order.
* **[Preview]** New KPI for tracking scheduled near-future payment cancellations.
* **[Preview]** Support for configuring multiple list prices in bulk/batches.
* Support for adding reporting tags to a subscriber.
* Support for sending e-mail notifications to users when a shared user is added to their account.
* Indication of how invoices have been settled, showing the transactions and payment(s) that was used.
* Users that have been deleted from the IdP, but where the mapping has not been removed, are now indicated in the user grids.
* Ledger entries created by a reminder, typically fees, are now linked to the reminder that created them.

Changed
-------

* Automatic refresh of payments view after re-matching.
* The payment and invoices overview so that deviating payments is put on the invoice they belong to if associated to one.
* The detail view for invoices now include more information and the layout has been slightly changed.
* Products list now includes a master/detail view for products with multiple billing frequency prices.
* Exporting the products to excel now includes the ProductId in addition to the existing columns.
* Styling improvement to the ledger view.
* The organizations view has been replaced with a new grid type with filtering and sorting aligned with the other replaced grids.

Fixed
-----

* Prevented the use of identical start and end dates when creating a temporary address change.
* An issue where the contract surcharge would always show NOK as the currency regardless of the actual currency used.
* An issue where adding a pause would allow switching to an inactive subscription plan.
* An issue where the current state of temporary address change or delivery stop would not be shown correctly.
* An issue where the selected payment file format would not be persisted in the session after importing a file.
* Prevented OIO to be shown as a invoicing method if not configured.
* An issue where it was not possible to fill out all required fields for manually created Account Invoices if OIO was selected as the payment method.
* An issue where a temporary delivery address change would be cut short with 1 hour if registered exactly during daylight saving times.
* An issue where registering a subscription plan change would show an incorrect price if the new plan had a reduced price.
* Fixed an issue where changing payment agreement to an e-mail agreement the e-mail would not be displayed.
* Fixed an issue for the users KPI, the changed users count was summarized incorrectly.
* Fixed an issue where assigning Email as a valid payment agreement type would not work.

Self-Service, Sales Poster and Checkout
========================================

Changed
-------

* The checkout business flow now displays prices without VAT/TAX.
* Improved handling of whitespace chars in all input fields for checkout.
* Prevented the use of identical start and end dates when creating a temporary address change.
* Aligned product sort or of temporary changes to match the sort order in the merchant.

Fixed
-----

* A few Danish translation issues in checkout.