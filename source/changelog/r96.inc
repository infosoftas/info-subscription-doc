.. _changelog-r96:

****************************
Release December 12th 2021
****************************
The last release of the year 2021. This brings us to a total of 13 release for 2021.
The release was rolled out entirely on the 12th of December, all API, backend and tenant clients have been rolled out at roughly the same time.
Without further ado, lets head on to the interesting bits.


API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added support for importing existing Vipps Recurring agreements.
* Added support for getting the remote Vipps Agreement details based on an existing agreement.
* Added support for skipping the Vipps Recrruing Landing page (requires approval/setting by Vipps).
* Minor documentation adjustments.
* When Subscriber Contacts are deleted, the subscription using the contact (Invoice Address) will automatically revert to the subscribers primary contact.
* Scheduled Plan Changes `At Renewal` will now override any existing changes of the same type and return the correct change id.
* Fixed an issue where AvtaleGiro Payment Demands would be calculated with a wrong Due Date due to an offset between the UTC core and the Norwegian timezone deadlines of Mastercard Payment Services.
* It is now possible to cancel outstanding claims when the AvtaleGiro mandate has been cancelled/deleted.
* Fixed an issue where trying to export EHF Invoices would also export EHF Credit Notes.
* Support for import AvtaleGiro mandates as a total/initial file using the OCR import routine.


Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Replace the generic money logo with the official Vipps logo for Vipps agreements.
* Minor visual adjustments to Invoices, Credit Notes and Orders.
* Fixed some issues related to calendar/date time pickers not being shown correctly.
* Removed option to credit standalone/account demands.
* It is now possible to select a separate billing plan and dunning process for Subscription Contract Surcharge handling.
* Improved the Guide/Wizard when configuring subscription plans for multiple offer steps (chaining).
* Notification settings on AvtaleGiro accounts are now displayed correctly (previously it would not show your existing setting).


Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Added option to toggle displaying prices in the sales poster.
* Added Kilkaya purchase/convertion tracking **Preview**.
* SalesPoster customization options are now documented with the API/Developer docs (this site).

Preview support for Kilkaya Order Tracking
------------------------------------------
This release includes preview support for tracking orders directly in Kilkaya when using the |projectName| salesposter.

Kilkaya provides dashboard for operational intelligence, and tracking orders allows for promoting content that drives convertions.

If you are interested in using this please reach out to our support and of course Kilkaya to get started.