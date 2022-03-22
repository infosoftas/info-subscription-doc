.. _changelog-r100:

***********************
Release March 28th 2022
***********************
Another release, this one marks our 100th anniversary for releases, since we started numbering our releases at least.
This release has lots of minor changes, a few new features, and we are making a few things generally available as well (ie. they are out of preview).

As always the backend has been rolled out entirely, while the frontend/UI clients will roll out over the next couple of days.

Avtalegiro Generally Available
==============================
With this release the Avtalegiro integration is now generally available for everyone to use.

Simply put this feature allows subscribers to register AvtaleGiro mandates in with their bank (or using an online form if the tenant provides on), and mandates can be imported into INFO-Subscription for recurring charges.

There is some setup required to get this up and running, with the Bank, with Mastercard Payment Services and of course with INFO-Subscription.
Please refer to our documentation or reach out to support to get further information.


Vipps Generally Available
=========================
With this release the Vipps Recurring (Faste betalinger) integration is now generally available for everyone to use.

The Vipps Recurring integration allows subscribers to use Vipps for payment of their recurring subscriptions, and manage their preferred payment means in the Vipps App.
Vipps takes care of notifying the subscriber about expired credit cards or failed payments etc, while INFO-Subscription takes care of generating the underlying payment demand/invoice that defines what needs to be charged.

There is some setup required to get this up and running, with Vipps and with INFO-Subscription.
Please refer to our documentation or reach out to support to get further information.

Quick Retry of failed Payment Requests with Swedbank Generally Available
============================================================================
With this release Swedbank Payment Request retry handling is now generally available.

When using the Swedbank PSP for card processing, it sometimes happens that there are intermediate issues with the card handling. Typically due to a lack of funds on the card.
It is now possible to configure INFO-Subscription to automatically retry those failed requests after a period of time, and only failing back to regular reminders in case the retries have failed to achieve the desired result.

There is some setup required to get this up and running, please refer to our documentation or reach out to support to get further information.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* When configuring reminders of a dunning process, each configuration is now ranked/numbered such the order is deterministic. See separate section for details.
* The reporting subsystem now supports generation of partial SAF-T compatible files specifically designed for Norway. See the separate section for the details. **Preview**
* Significant changes in the inner handling of ledger record generation that fixes a series of stability issues, which would typically manifest as duplicate ledger entries.
* Fixed an issue where generating payment demands with lots of entries, typically for enterprise plans, would lead to invalid invoices being generated (lines would be skipped).
* When trying to issue an invoice with no lines, the operation will be denied as the invoice is essentially invalid. As a minimum a 0 valued line should be added.
* The End time on an invoice line period is now optional, meaning its possible to represent "point in time" charges without specifying the same time twice.
* Removed the restriction that a subscriber external identifier should be historically unique. The idea originally was to make sure the old subscriber was revived but it turns out to be impractical for third parties.
* Added a restriction that prevents removing future cancellations on subscriptions that were created as automatically cancelled as it breaks the automation flows. If continuation is required a new order needs to be placed or a new subscription created manually.
* Previously when cancelling or otherwise amending subscriptions at a future date, the ledger entries generated would be added with the future date. This has now been changed so that all ledger entries are generated with a time corresponding to when the action was carried out.
* Fixed an issue where manually processing scheduled payment demands for Enterprise Plans would lead to a future issue time being set instead of the current time (only occurred when Infosoft does manual error correction).
* Fixed an issue with download/export of EHF files where the file would not be generated and exported but instead an empty storage reference would be generated to the caller. **Hotfixed**
* Subscriber and Plan information should now be included on all EHF files, including enterprise plan invoices.
* Extended the EHF handling to generalize Fee handling so it now converts to charges the same way that regular charge/invoice lines does.
* Invoices with allowances will now be materialized with Allowances in the EHF lines.
* Fixed an issue in the order flow, where multiple simultaneous complete requests on the same order would lead to multiple subscriptions being created with the same information.
* Importing AvtaleGiro mandates using the OCR file would cause a complete abort in case the file included a cancellation of a mandate that was not already present. This has now been fixed and replaced with a warning.
* AvtaleGiro and Vipps integration is now consider to be generally available. See separate section for details.


Ranked/Numbered Reminder Settings
---------------------------------
Reminder Settings for the dunning process now contains a rank/numbering for ordering reminder production.

Previously the order would be based on the creation time, thus the oldest would always be first, and deleting it and adding a new would be evaluated second regardless of the delay count.
The rank can be specified during creation and updates, if not specified the next available rank will be taken automatically (temporary compatibility thing).

If the number series has holes in it, it is effectively a broken sequence and it will only work up until the hole is encountered.

The introduction of this ordering represents a breaking change in the API, but our telemetry tells us that no-one but we are using that API.

The UI has not yet been updated to acknowledge the new numbering, so expect some issues when managing multiple reminder setups at the same time.

Partial SAFT-T File generation
------------------------------
BLAH WE NOW HAVE SAFT SUPPORT!

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added option to download invoice PDFs for enterprise plans.
* Added support for name changes for temporary address changes.
* Fixed a timezone issue with search on Payments, Invoices, Corrections and CreditNotes **Hotfixed**.
* Adjustments and fixes to Recurring Deliveries and related Distribution Innovation integration **Preview**.
* Configuration of Payment Request retries (Swedbank) is now generally available. See separate section for details.