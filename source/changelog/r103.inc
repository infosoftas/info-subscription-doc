.. _changelog-r103:

***********************
Release June 22nd 2022
***********************
Another month, another release. This will be the last release before the summer period. Expect the next release to be sometime during August.
The API and backend has been rolled out entirely, and the frontend/UI will be rolled out over the next couple of days, some UI instances have already been deployed.

This release contains a lot of internal changes, most notably across the board upgrade to .NET 6 (where .NET is applicable of course). 
The main takeaway is an increase in performance on the API level.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added support for automatically generating replacement Account Demands when crediting. Previously this would have to be done manually in all cases. Manual intervention is still required when changing parameters of the demand (i.e. changing Payment Agreement for instance).
* Fixed an issue that would cause demands to be automatically creditted during subscription cancellation, if the cancellation time was within the same second as the end time but not EXACTLY at the end time.
* Introduced a restriction to prevent removal of cancellations when a Subscription Contract is in place.
* Removed date specification for invoice lines where no date is specified to avoid displaying "0001-01-01" in the generated Invoice.
* Added reminder number to the ledger specification together with the reminder fee. Previously only the fee was included making it difficult to track where they came from.
* Changed handling of AvtaleGiro mandate deletions so that Payment Agreements are now deactivated instead of deleted.
* Fixed an issue in reporting where querying for Subscriber tags would cause a failure if no tags were present.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added option to update products on existing subscription plans (not templates).
* Fixed a series of issues related to Enterprise Plan management.
* Fixed an issue that would cause the Invoice Amount total to be incorrect when tax is included in the Payment Method fee.
* Adjusted how Currency is displayed during plan changes.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Additional and adjusted translations for Northern Sami.