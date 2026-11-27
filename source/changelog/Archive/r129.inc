.. _changelog-r129:

*********************
Release November 5th
*********************

We march onwards with a new release. This time around we offer a slew of bug fixes and a few general purpose quality of life enhancements.

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Support for selecting a different Payment Agreement when Crediting and Re-issuing a Payment Demand. If a new agreement is selected no lookups will be done to determine which agreement to use. This essentially allows for changing the Payment Method of a single Payment Demand/Invoice when the source subscription has been renewed (after Due Time).
* During orders for Subscription Plans with Editions, an additional validation will be done to ensure that there are enough available Editions in the calendar to cover the subscription.

Changed
-------

* Handling of exporting files for BetalingsService and Autogiro so that the files come pre-generated with a name and extension that is acceptable by the provider.
* The use of VippsParameters in orders routes to the newer VippsMobilePayParameters property without optional profile properties.
* |VippsMobilePay| ePayments are now marked as failed in case the capture operation fails for some reason.
* The internal OData component setup to improve serialization performance from the Reporting subsystem.

Fixed
-----

* A series of validation errors during orders where the validation routine would reject some valid orders, and NOT reject some invalid orders.
* A few issues related to subscription revenue statistics calculation, mostly to not calculate revenue as lost or gained in edge case scenarios and a lack of unit handling.
* An issue where plan changes (downgrades) on subscription with an not settled payment demand with a large allowance could lead to negative nonpayable payment demands.
* An issue where automatic re-generation of a settled Payment Demands after removal of a future subscription cancellation would lead to an extra Allowance in the billing account.
* An issue where proration would calculate an entire extra day in cases where cancellation is done with a millisecond variation. Specifically billing now resolves to entire seconds and discards any smaller time units.
* An issue where the Edition calendar would not reset the numbering when starting a new calendar year.
* During export of recurring deliveries that would not account for time zone differences.
* Missing OrganizationId on CreditNoteIssued events.
* Invalid SubscriberId on some cases for InvoiceIssued and CreditNoteIssued events.
* An issue where Subscriber Account would not be reset when updating a not identified payment with a new matching type (without Subscriber Account).
* An issue where calculating the next subscription period would not handle scheduled plan changes with a price different from the full price.

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

* Support for managing a fixed set of Cancellation Causes causes available in self-service.
* UI for subscribing to the event type `InvoicePaid`.
* Option for deleting/anonymising Subscribers to easily comply with GDPR requests. Read more about this feature in the user documentation.

Changed
-------

* Waiting/Handling during export of Distribution Innovation files to avoid error messages and duplicate exports.

Fixed
-----

* Some edge case issue with Edition Calendar editing/maintenance.


Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self service and sales poster.

Added
-----

* Support for restricting Cancellation Causes to a configured set of values.

Changed
-------

* From/To Edition Numbers will be shown on Invoice Lines instead of From/To Date information for Edition based subscriptions.
* Default country is now derived from Country of the Organization instead the globally configured default country during new orders.
* Changed to use VippsMobilePayParameters for orders to keep in line with latest API contract.