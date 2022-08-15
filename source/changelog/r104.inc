.. _changelog-r104:

************************
Release August 16th 2022
************************
We are back after the summer! It has been a long time since the last release, everyone has been on vacation so the release size does not reflect the length directly (it is quite large regardless).

As always the API and backend has been rolled out entirely, and the frontend/UI will be rolled out over the next couple of days, some UI instances have already been deployed.

We are slowly migrating to a new deployment type for the administrative merchant UI, which should lead to simplified access and increased performance for most tenants.
Each tenant will be contacted directly to arrange for the details on when to make the switch.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* New option for defining a reason when switching subscription plans. Useful to see why a Subscription was cancelled.
* New API and Backend support for simplified handling of end-user authorizations. *Preview*
* Fixed an issue where getting Invoice and Credit Note files would fail to output the file stream.
* Expanded Subscription and Demand Detail query support to filter on next subscription (if set).
* Getting Payment Demand Details now include the Next Subscription Id if set
* Demand total amounts are now rounded to two-decimals using `Round half to even` (also known as `Bankers rounding`).
* Fixed an issue that prevented AvtaleGiro claims to be generated for new orders (initial period) on existing mandates.
* Fixed an issue where Vipps charges would not be generated in a timely manner if the Billing Plan minimum due days was set to 2 and the subscription renewed around midnight UTC.
* The event for Invoice Issued would sometimes be triggered before the Invoice was available for querying. This has been fixed.
* It is now possible to set the intial Invoice and Subscriber sequence number to 0, making it possible to have the first Invoice Number have a value of 1.
* Fixed an issue causing the OCR payment import to fail if an AvtaleGiro mandatecancellation was registered for a subscriber with multiple active AvtaleGiro mandates.
* The reporting service now reflects Standalone Account Payment Demands entirely.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Support for ADB2C as an end-user backend. *Preview*
* UI changes related to Enterprise Plan to make it more streamlined and simpler to use.
* Changed the sub-menu tab order for the Subscriber View.
* Removed the possibility to update a temporary change AFTER it has been started.
* Fixed an issue where entering a future date would use UTC midnight as the starting time instead of local midnight.
* Reminder settings now displays the delay as integers instead of decimals.
* Multiple visual adjustments for subscriberview and for the plan change view.
* Temporary changes are now out of preview.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Support for ADB2C as an end-user backend *Preview*

End-User Authorization Preview
===============================

This release includes a new backend feature intended to simplify the end-user authorization process.
Today all authorization logic is handled at the resource level, typically the CMS/Website that the subscriber accesses or some other middleware authorization service deployed by the tenant.
INFO-Subscription implements its own authorization logic for the self-service client, similar to the one deployed at the resource level.

Multiple tenants have similar requirements for authorization, and while not all tenants have the same requirements, we have decided to implement a common authorization service that can be used if desired.

This release includes the first preview of this service, where users are mapped to either a subscriber or a subscriber account, and depending on the mapping, a list of products is mapped to the user based on the current active susbcriptions.
The end result is that authorization can look at the product list for the user and determine access/authorization this way.

Additionally, we have added Authentication Provider support for Active Directory B2C (ADB2C), so that the list of products is injected directly into the `access_token` during signin.
Using the `access_token` product list should alleviate the need to query the API during most sign-in operations.

We are still maturing this service, and the existing Auth0 setup that you know will continue to function.

Going forward the backend will add support for Auth0 as an authentication provider, providing a list of products injected into the `access_token` similar to what is done in the ADB2C integration.

It should also be possible to use the mapping service with an external authentication provider, but the injection needs to be handled on the outside, as there is no standard way to handle management actions like this.

Please contact support for access to the preview.