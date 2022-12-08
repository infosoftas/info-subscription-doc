.. _changelog-r108:

****************************
Release December 6th 2022
****************************

Deck the halls with boughs of holly Fa-la-la-la-la, la-la-la-la.
December marks that christmas is soon upon us, and also that we have the last release of the year. 
All API/Backend instances have been upgraded as well as the Merchant UI. The various self-service instances will be upgraded over the next few days.

This year we have managed to send out 12 releases, roughly one each month - presumably we are going to continue with the same pace as we move forward.
The next one is likely to hit late January 2023.

Merry Cristmas and a Happy New Year to everyone.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Added a requirement to supply OrganizationId on refunds NOT based on payments.
* Included additional properties for Invoice, CreditNote and Reminders.
* Introduced an option to have AvtaleGiro mandates managed by the Mastercard API instead of file based management.
* Adjusted the Open API Specification for Settlement Policy and Reminder Settings on the Dunning Process to make it more discoverable.
* Fixed an issue with Settlement Policy where supplied values would ignored during configuration.
* Fixed an issue with the newly introduced EHF Organization validation where validation errors were not queryable using the API.
* Added field for Floor, Floor Type and Apartment Number for delivery addresses (recurring deliveries).
* Adjusted the behaviour such that payments on outstanding Invoices will mark any related EHF invoices as already exported.
* Reminder Documents can now be produced with a list of allowances to reduce the payable amount on reminder generation (to allow partial payments).
* Vipps Campaign properties are now set whenever there is a price on the initial period that differs from the full price.
* Fixed an issue where rounding amounts would produce invalid EHF files. The rounding amount is now supplied to the rounding total in the EHF header.
* Fixed an issue where new tenants would not be able to use Power BI reporting capabilities due to a change in the underlying Azure Power BI service.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Introduced option to configure Distribution Innovation export file basename.
* Spelling correction of organization number.
* Remove the possibility to add multiple delivery changes on the same date.
* Fixed an issue where adding multiple delivery changes at the same time would generate an invalid series of changes.
* The option to generate Credit Note copies has been re-introduced for Enterprise Plans.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Support for the Distribution Innovation interactive address helper. **Preview**
* Updated texts and translations for delivery address changes.
* Removed the possibility to add additional delivery stops if the latest change is already a delivery stop.
* Added configuration to allow cancellation in subscription period. The default is still cancel at the end of the current period.
* Sales Poster Nothern Sami translations.
* Fixed an issue where order on existing subscribers would generate a gibberish Organization Number instead of a blank one.