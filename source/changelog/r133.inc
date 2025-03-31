.. _changelog-r133:

******************
Release April 1st
******************

INFO-Subscription has closed shop - no further release will be made - ever.

As aprils fools go that one is pretty lame, but anyway, here is the real changelog for this release.

We only have a few new items for you this time, but behind the scenes we have been busy with a lot of scaling testing and adjustments as well as preparations for planned features.


API and Backend
===============

Added
-----

* **[Preview]** Multiple purchases of additional products of the same type are now merged during renewals.
* **[Preview]** Support for updated list prices during renewals for additional products.

Changed
-------

* WriteOffs now include a source accounting time for the original transaction for reporting purposes.
* WriteOffs that leads to deletions, due to the transaction never having been accounted, will now also be tracked for reporting purposes.

Fixed
-----

* **[Hotfix]** An issue where allowance was added as charges on the final demands
* **[Hotfix]** An issue where Balance/Final demand generation would filter out Allowances, causing demands to be produced even when the subscriber account was below the defined limit.
* An issue with full-synchronization of |AvtaleGiro| mandates, where processing would never complete and in some cases lead to multiple PaymentAgreements.
* Handling of the SwedbankPay operation failure event so it produces an external notification for failed payment processing.
* An issue where a scheduled subscription plan change would lead to a subscription being slightly longer than it should.

Merchant Client
===============

Added
-----

* **[Preview]** The possibility to delete users, and not just disconnect them from the subscriber.
* A new option for creating users directly when creating new Susbcribers.
* Support for showing/querying Distribution Innovation for address information in case DeliveryPointId is present on the contact.
* UI actions for generating Reminder copies similar to the existing Invoice copy feature.
* Adjusted the subscription view for Additional Products to include price information.

Changed
-------

* Improved the user experience when supplying a long query in the subscriber search field.

Fixed
-----

* A paging issue on the subscriber list view where switching pages would not reset the view position.
* An issue where it was not possible to add/edit contact information on a subscriber with no contact info present.
* An issue where switching tabs/subviews for payments would not work properly for multiple organizations under some circumstances.


Self-Service, Sales Poster and Checkout
========================================

Added
-----

* Support for showing/querying Distribution Innovation for address information in case DeliveryPointId is present on the contact.
* Added support for sending the client_id in the request to signout of ADB2C. Making sure SSO works for Application scoped sessions.
* Checkout: Added support for defining an OrganizationId in the url for template plans without a fixed organization.