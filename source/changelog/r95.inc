.. _changelog-r95:

****************************
Release November 11th 2021
****************************
The following changes started rolling out on November 11th.
The API and backend are being rolled out to all tenants at the same time, and the client will be propagated over the next couple of days.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Introduced support for resuming an old cancelled subscription. This will generate a new subscription plan based on the old one. **Preview**
* Fixed an issue where the Vipps Account setup would return the create Id in the wrong format.
* Removed API for generating orders with PayEx POPS parameters. POPS has been offline for more than a year now.
* Added support for generating Tax on Fees based on the included products. **Preview**
* Payment Agreements are can now be deactivated instead of just deleted.
* Subscription Plans with multiple products now generates a single line with multiple details on the Invoice, previously multiple lines would be generated which was not the intention.
* Introduced additional validation for Vipps related parameters in the Order flow to prevent invalid orders getting accepted but failing half-way through.
* Added the possibility to re-use existing Swedbank Payment Agreements on new orders.
* Fixed an issue with querying for Payment Requests where specifying the InvoiceId did nothing for the filtering.
* Fixed an issue that would in some cases cause double crediting entries in the Subscriber Ledger.
* Fixed an issue where Subscription Plans with multiple products would cause Vipps Orders to fail.
* Fixed an issue where template packages with more than one chain step ending in an automatic stop, would not cause the automatic stop to be picked up.
* Fixed an issue where Denial Orders were added multiple times for the same violation/criteria.

AutoGiro in Preview
-------------------
This release includes a preview for the Swedish Direct Debit solution known as AutoGiro, provided by BankGirot (BGC).
The various APIs and services has been extended so it is now possible to create AutoGiro accounts and import mandates.
Similar to AvtaleGiro the process is mostly automated, so imported mandates will automatically switch payment agreement for the next payment demand where possible.

There are still some limitations in that AutoGiro is entirely file based, so files needs to be exported and imported manually and shipped to BGC. 
We are looking in to a solution where we take care of the SFTP transfer for all tenants, but today it needs to be done by the individual tenant.

Interested in participating in the preview? Contact support, find the details on {SUPPORTPAGE}.


Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added configuration option to define default Country Code (only for the merchant).
* Added option to select AutoGiro import files.
* Top-level menu texts have been slightly adjusted.
* Additional translation for shared users.
* Subscriber notes can now be sorted.


Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Adjustments to the visuals for the order flow, included a message on the Vipps Landing page not to close the browser.
* Fixed a visual issue where the Invoice Contact dropdown would be shown below the browser auto-fill suggestions. The auto-fill suggestions are now disabled for that field.