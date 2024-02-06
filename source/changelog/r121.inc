.. _changelog-r121:

**************************
Release Feburary 6th 2024
**************************

We are back with another release.

This time around we have started work on a new setup for billing based on Editions or Issues, or more specifically based on a set of dates in a calendar.
Underneath the covers it is still mainly based on time.
The feature is not complete, but the changelog will start to reflect that we are introducing parts for this new billing concept.

As usual we have a bunch of minor adjustments and bug fixes to make your recurring billing experience smoother.

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* It is now possible to define a Period on Account Demand transactions (lines), these are optional and the Start time will still be derived from the issue time in case they are not given.
* **[Preview]** Support for creating |BetalingsService| payment agreements and mandates. 
  |BetalingsService| is the Danish Direct Debit solution similar to the Norwegian |AvtaleGiro| and Swedish |AutoGiro|.
  Just like AvtaleGiro, it is mostly an out-of-band solution that requires little in terms of direct interaction.
* **[Preview]** Support for adding product pricing based on a number of editions.

Changed
-------

* Added new CancellationType for cancellations related to deletions (i.e. subscription that start in the future and are deleted and not just cancelled). 
  This allows clients to do special logic already at the time of cancellation, and most importantly allows them to skip a lookup step which is going to fail since the subscription is now gone (deleted).
* Getting an existing subscription or calculating the next subscription period will now include `Product Name` and `Product Description` for each product in the Subscription Plan.
* Credit Note Id is now forwarded to the Ledger Entries when generating Credit records via Billing, ie. when crediting a payment demand or during automatic crediting for cancelled subscriptions.
* Original AccountTime is now available on Charges and Allowances even when they have been included on a Payment Demand.

Fixed
-----

* **[Hotfix]** An issue where Zip Code would be set with an invalid value during |eFaktura| agreement scanning.
* **[Hotfix]** An issue where |eFaktura| agreements would be re-created even though they existed in cases where there was also an |AvtaleGiro| mandate.
* **[Hotfix]** An issue in the reporting subsystem where replacement Payment Demands would not be generated in the reporting model due to an invalid configured constraint.
* An issue with Account PaymentDemands where the `ProductId` would not be populated all the way through reporting and in the API on the TaxDetails collection.
* An issue where Account PaymentDemands with a Payable Amount of 0 would not be automatically settled.
* An issue where Enterprise Plan Payment Demands would not carry over Product Name and Description for TaxDetails in reporting.
* An issue where adjusting the Billing Plan Minimum Due Days would not affect existing Enterprise Plans. **Note** By design it still does not reschedule anything, only affects new billing cycles and orders.
* An issue where crediting with a replacement payment demand on Enterprise Plans would lead to the subsequent reminder would never be generated. 
* A decimal rounding issue on EHF when utilizing multiple non-zero VAT products on a single transaction.
* An issue with failed Template Plan validation where Product, Price and Plan had a start time in the future, causing the plan creation to fail.

Removed
-------

* Invalid Calendar endpoints that were not in use.

Deprecated
----------
We call out the following deprecations, the endpoints/field will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* We are deprecating the endpoints ``/paymentdemand/{id}/credit/completely`` and ``/paymentdemand/{id}/credit/partially`` in favor of ``/paymentdemand/{id}/credit`` endpoint.
* We are deprecating the field ``TaxPercentage`` on the endpoint for creating Account Payment Demand transaction ``POST /paymentdemand/``, in favour of specifying a list of Tax Details.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* **[Preview]** New dashboard/overview visuals to replace the current numbers based overview.
* Organizations can now be configured with Identifications such as Organization Number and other external unique Ids. This was previously removed, but has now been brought back in an updated version.

Changed
-------

* HPR Number can now be configured on a Tenant by Tenant basis, and its toggled off by default.
* Removed Distribution Innovation Endpoint references since they are now determined by the backend.
* Scheduled Plan changes are not shown on cancelled subscriptions, as they are never going to take effect.

Fixed
-----

* An issue where Email Domain users would be listed with the previous period for Subscription Plan access instead of the current period.
* An issue where the Payment Import log would display the Amount for parsed transactions in the processed transactions Amount. Leading to some confusion on OCR files with multiple assignments.
* An issue where displaying an old invoice with a deleted Invoice Contact would lead to an error message.

Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self-service client

Changed
-------

* **[Hotfix]** Salesposter order process URLs are now significantly shorter.