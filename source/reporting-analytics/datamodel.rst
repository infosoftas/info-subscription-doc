.. _reporting-datamodel:

*******************
Reporting Datamodel
*******************
The following contains a description of the various tables in the reporting database.
Each section of the model is organized into seperate areas/silos mostly to indicate their usage area. 
Though its up to you to be creative.

The datamodel documentation is divided into a section for each of the various areas, as well as sub-sections for each table.

Some of the tables have noteworthy columns that are called out separately, in their respective sections.

General Purpose
===============
The main area is an catch-all where things that are not naturally in one area or another is created.
This contains reporting management data, as well as cross cutting data such as Organizations and Subscribers.

**Schema Name** : dbo

Available Tables 

 * Organizations
 * Products
 * Subscribers
 * SubscriberContacts
 * Tag
 * ReportingGroups
 * ProductReportingGroups

Organizations
-------------
Information about organizations such as organization name, e-mail, phone and address.
Organization data is commonly denormalized.

Products
--------
Contains information about all available products.

Noteworthy columns
~~~~~~~~~~~~~~~~~~
**ProductCategory**: This is a grouping field only for reporting and analytics purposes, can be used to split the reports into groups. 
You create a group, and then link products to the groups via the API.

Subscribers
-----------
The main list of all subscribers in the system as well as the details of the primary contact.
This information is mainly used for invocing, reporting and deliveries.

Noteworthy columns
~~~~~~~~~~~~~~~~~~
**ContactId**: This is a reference to the subscriber contact from which the contact information is retrieved.

**ExternalId**: External reference as defined by a third party. Typically CRM or a master data system of sorts.
 
SubscriberContacts
------------------
All contact information for all subscribers, such as the primary contact address, billing addresses and delivery addresses.

Noteworthy columns
~~~~~~~~~~~~~~~~~~
**IsPrimary**: Indicates the contact information is the default that will be used for billing, deliveries etc if not overridden by a specific selection of another contact.
**Identification**: May contain information about organization number, customer references and more. Data is stored as a JSON array, and T-SQL JSON Functions can be used to parse the data.

Tag
---
Tags are text fields that can be associated with different entities, used for grouping and reporting purposes.
They carry no value and are only represented in the reporting datamodel.

The idea is to let third parties tag on information as appropriate for their specific use case.

At the current time its possible to provide tags for:

- Subscriptions
- Subscribers
- Subscriber Accounts
- Payments
- Payment Demands

At the current time the API endpoint for creating a new Order contains a tag value that will be assigned to the first subscription, the subscriber and the subscriber account.
It is designed as a list of tags where all tags will be added.

The `ReferenceId` will then correspond to `Subscriber`, `SubscriberAccount` and `Subscription`, respectively. 

An example is to tag all orders with a "Sales Unit" or "Store" Id, allowing to report and analyze sales by physical department or store. 

The vast majority of the entities in the reporting model have a connection to `SubscriberId` and can then be grouped / filtered in relation to the `Tag` given.

ReportingGroups
---------------
Reporting groups, as the name suggests, a way to group things for reporting purposes. Specifically Products and permanent discounts.
For instance you may want to group all products of a specific type as "Cosmetics" and another as "Foodstuffs". 
You can do this in each and every report you generate, or you can setup the group in the reporting model, and just group and filter on the reporting group.

Items can be included in multiple groups.

Economy and Billing 
===================
The economy and billing area/silo, contains data related to the recurring billing of the subscriptions.
Anything you need to know about your billing is collected here such as Invoices and their state, outstanding transtractions and fees.

**Schema Name** : economy

Available Tables 

* AccountTransaction
* Invoices
* PaymentDemands
* PaymentDemandFees
* PaymentDemandDetails
* PaymentDemandAllowances
* PaymentDemandCharges
* SubscriberLedgers
* SubscriberAmounts

AccountTransaction
------------------
Outstanding account transactions.
This contains the current list of transaction that has yet to be billed (put on an Invoice).
These are generated as payments are processed, subscriptions are cancelled and related.


Invoices
----------
Summary data about the various invoices produced, such as state and issue date.
Does not include the entire invoice, just summary data.


PaymentDemands
----------------
Invoicing of subscribers produces a "Demand for Payment", and PaymentDemand, along with its related entities, contains details about what is billed such as:

- Reference to the subscription period(s) billed and the amount.
- Any transactions caused by metered billing or manual corrections.
- Time of issuing.
- Reference to the resulting Invoice Document.
- Reference to the Order/first period and the amount.
- State of settlment.

Payment Demand is the basis for payment claims that the system generates, and it is on the basis of these that an invoice is formed. 

Example reporting/analysis use cases include:

- Total outstanding dept amount.
- Billed Amount by month or even by product.
- Degree of payment by area, organization or payment method.

PaymentDemandFees
-----------------
Fees related to payment demands and reminders for the given payment demand.

PaymentDemandDetails
--------------------
Details refers to the Subscriptions, Orders and external one-time transactions associated with a payment demand.

Keep in mind that Subscriptions are always billed in advance, but the subscription that is referred here is the past one (the one deciding how the next bill is going to be basically).

Noteworthy columns
~~~~~~~~~~~~~~~~~~
**NextSubscriptionId**: This column is populated once the subscription is renewed/extended. Thus at the time when the NextSubscriptionId is populated the demand now covers and existing 

 
PaymentDemandAllowances
-----------------------
Any allowances consumed from the Billing Account (`AccountTransaction`) are presented here. Allowances reduce the total amount to be claimed.
 

PaymentDemandCharges
--------------------
Any extra charges/debits from the Billing Account (`AccountTransaction`) are presented here.
Charges increase the total amount to be claimed.

Typically these would be metered charges, or left overs from previously settled demands with a missing amount.


SubscriberLedgers
-----------------
The entity contains all ledger entries/transactions regardless of organization or state.

Represents the current total state of a subscribers accounts.


KPI: SubscriberAmounts
----------------------
This is the sum of subscriberledgers grouped by subscriberid, organizationid and currency at any given time.

Can be used to give a "snapshot" insight into how much is billed or owed across all organizations. It is designed as a pre-calculated KPI.


Orders
======
The orders area/silo, contains data related to incoming orders, and basically should be your goto area for sales performance data.

**Schema Name** : order

Available Tables 

* OrderAmounts
* OrderCompletedAmounts
* Orders
* Products


KPI: OrderAmounts and OrderCompletedAmounts



One table includes all orders that have been started (and later cancelled), while the other only summarises orders that have been completed.

Example use cases involves a running dashboard of the value of your orders over time.
 

Orders (and Products)
---------------------
Summary data about all orders started, cancelled and completed.

It includes information such as the price/value, when it was created and completed, as well as when it was abandonned/cancelled if that was the cause.

It refers to a Products table so its possible to group Orders and Products and analyze sales behaviour using this data.


Subscriptions 
=============

The subscription area/silo, is similar to the Orders silo, except it related to data about the recurring business, it should be your goto area for reucrring performance data.

**Schema Name**: subscription

Avtailble Tables

* Subscriptions
* CanceledSubscriptions
* Contracts
* Enterprise Plans
* SubscriptionPackages
* SubscriptionPacakgeProducts

Subscriptions
-------------
All subscriptions registered in the system, with comprehensive information about, start and end time, details such as price, tax ( VAT ), number of units, cancellation status and reason for cancellation as well as renewal status.
 
CanceledSubscriptions
---------------------
All canceled subscriptions, including reason for cancellation.

Contracts
---------
Information on subscriptions with fixed contracts, and how long those contracts are defined to last.

EnterprisePlans
---------------
General information about agreements for enterprises used for common billing and rules for selling to these enterprises.

SubscriptionPackages and  SubscriptionPacakgeProducts
-----------------------------------------------------
Contains instance level details about a given subscription, detailing the specific for that subscription.
More commonly known as a Subscription Plan.

Noteworthy columns
~~~~~~~~~~~~~~~~~~
**BillingFrequencyId**: The frequency at which the Subscription is billed/renewed
    * 1001 - Month
    * 1003 - Quarter
    * 1012 - Full year.

**SubscriptionPackageChainId**: Defines the package chain for stepping/changing packages during renewal. I.e. first pay 99 kroner the first month, then 149 for the second, 199 for the third before finally changing to the full price of 249.

**InitialTermType**: This is used if the first period is to have a different length. 10 - «Until date », 20 - «Number of days», 100 - «Out the month», 200 - «Out the year» .  

**InitialTermValue**: This will then have slightly different values ​​depending on the type. For the value «10», then there will be a date. For "20" it will be a number of days ". For "100" and "200", it is not used.

**AutomaticStop**: This means that the subscription will be automatically stopped after the period.

Payments
========
**Schema Name**: payment

Avtailble Tables

* DailyPaidAmounts
* Payments

KPI: DailyPaidAmounts
---------------------

KPI style table with total amount of what is paid for any given date, for each organization.

This only includes payments that have been approved and complete, payments yet to be identified are not included in the summary.

Payments
--------
All payments for each individual subscriber, regardless of source. 
The most common source values are OCR, PayEx , Manual, Import and MI (migrated).


Entity Relationship Diagram
===========================

The following is an ER diagram of the reporting data model serving as a visual reference.

.. mermaid:: datamodel-er.mmd
    :align: center
    :alt: Entity Relationship Diagram for Reporting Model