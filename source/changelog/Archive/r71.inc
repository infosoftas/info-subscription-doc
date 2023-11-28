.. _changelog-r71:

**************************
Release March 12th 2020
**************************
The following changes were rolled out to production on March 12th 2020.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* General support for Care Of.
* New API endpoints for view demand and reminder schedules.
* Added support for generating PayEx payment agreements for both POPS and eCommerce without the need for going through a new order.
* Changed input validation for changing a package and stopping a subscription, the changes revolves around which date is allowed as the change date (allowing earlier dates than before).
* Fixed an issue where calculating the next subscription would not populate all properties correctly.
* Fixed an issue where getting registered WebHooks would list registered events without the namespace prefix.
* Any reminder fees are now included in the total on Invoices where appropriate (i.e. all other places than the line total).
* Reporting now populates payment agreement information correctly for all subscriptions.
* Fixed an issue with initial term offers that would cause the follow-up period to not be billed correctly (only occured for perpeptual free invoices so not very critical).

Client
======
The following new features and improvements are now available in the web client

* Added new view for Subscriber Payment Agreements
* Added option for generating copy of credit notes
* General support for Care Of in merchant and self-service
* Adjustments to the view for credit notes in merchant
* Menu adjustments to simplify navigation a bit
* Fixed an issue related to displaying of dates when viewing stopped/changed subscription

Care Of
=======
This release sees the inclusion of a new field in subscriber contact details called Care Of.
It is a minor feature but the value is carried throughout the system in different manners.

The field itself is just a new optional text field for Subscriber Contacts.
Its purpose is to provide a Name for a person/entity that is the target receiver of the mail delivery (whether this may be an Invoice, a package or something else).

Recurring deliveries and the subscriber details have a new field called Care Of and this field is exposed in the Salesposter and in the merchant.

For Invoices the field is mapped to the `Recipient->Contact->Name` and similarly to other instances of participant.
In case there is no Care Of the Contact Name is left equal to the Subscriber name.

EHF maps fields from the Invoice, so naturally the `AccountingCustomerParty->Contact->Name` contains the value from the Recpient on the Invoice.