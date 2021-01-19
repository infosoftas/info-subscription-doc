ReportingService: Documentation of tables
=========================================
Documentation of existing tables per. 20 November 2020. Number of tables / columns documented: 30/446 (see Appendix for further details).

[billing].[PaymentWithdrawals]
----------------------------
PaymentWithdrawals includes credit card debit attempts.

[dbo].[Organizations]
---------------------
Information about organizations such as organization name, e-mail , phone and address.

In order for the various tables to be as easy to read as possible, parts of this information are also found in many of the tables in the report layer . Here some may have many titles / organizations. The main point of this is to be able to structure different titles separately, but with different offers, invoice runs and subscription plans.

[dbo].[ProductReportingGroups]
------------------------------
ProductReportingGroups are used to put products into different groups. For example, it can be used to make it clear that products A and B belong to report group 1, while products C, D and E belong to report group 2.


[dbo].[Products]
----------------
Products provides an overview of all products that are available, and has a more detailed description of these.

Special fields in Products:
~~~~~~~~~~~~~~~~~~~~~~~~~~~
**Productcategory**: This is a grouping table for the report layer, which can be used to split the reporting into groups. You create a group, and then link products to the groups.

 

[dbo].[ReportingGroups]
-----------------------
Report groups are defined to distinguish between different product types. Examples of this could be that one product is digital, another is on paper (physical), while a third is a combination of both digital and paper.
 

[dbo].[SubscriberContacts]
------------------------
All contact addresses: Main addresses, billing addresses and temporary addresses.

Special fields in SubscriberContacts:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**IsPrimary**: Value 1 means the address is home address, 0 is billing address or temporary address.

**Identification**: May contain information about organization number, customer reference and more. JSON functions must be used to retrieve each individual value in this type of field.
 

[dbo].[Subscribers]
-------------------
Subscriber is a register of all subscribers and contains all contact information. This information is used for deliveries and invoicing. Examples of use are sending a PDF invoice to an e-mail address or sending a physical invoice to a postal address.

Special fields in Subscribers:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**ContactId**: This is a reference to the subscriber contact from which the contact information is retrieved.

**ExternalId**: External customer number of a third party system.

 
[DBO].[Tag]
---------
Free text that can be sent with an order, but this is used differently from customer to customer. The idea is to be able to connect to other tables to be able to retrieve information. Information in Tags can also be created manually.

When you send a tag with an order, two tags are currently created in the report layer. One with type Subscriber and one with type SubscriberAccount. Referenceid then correspond henholdsvi s SubscriberId and SubscriberAccount . Thus you can search for all subscribers who have a relationship with for example ShopID = 458. The vast majority of tables in the report layer have a connection to subscriberide and can then be grouped / filtered in relation to Tag.
 

[economy].[AccountTransaction]
----------------------------
Saldo transactions can, among other things, be used for purchases from agreements. For example, if you agree on a payment claim, which you will later buy out of, then this table will be used.
 

[economy].[Invoices]
------------------
Invoice details.

 
[economy].[PaymentDemandAllowances]
---------------------------------
Contains adjustments that occur when you pay too much or too little.
 

[economy].[PaymentDemandCharges]
------------------------------
Balance sheet transactions that are included in payment claims.
 

[economy].[PaymentDemandDetails]
--------------------------------
Information about payment requirements, connected to the subscription (Subscription) and what is the next subscriptionId.

Payment claims are formed before the subscription is formed. Therefore, subscriptionid is for the previous subscription, while NextsubscriptionId is the subscription in question. When a subscription is renewed, NextSubscriptionId is applied to the correct payment claim.
 
[economy].[PaymentDemandFees]
---------------------------
Invoice fee.


[economy].[PaymentDemands]
--------------------------
Invoicing of customers produces a demand for payment, and PaymentDemands contains customers' invoices, with amounts, time for when they were issued and when the demand is due. Link to ledger is displayed.

Payment Demand is the basis for payment claims that the system generates, and it is on the basis of these that an invoice is formed. Examples of using payment requirements k an be reporting outstanding guilty amount or income broken down by month of the year. Each claim points to the subscription period that is the basis for the claim. It is important here to keep in mind that the requirement is formed before the period is formed, so the pointer is therefore always backwards in time.  

For orders, there will be a pointer to the order that led to the claim.
 

[economy].[SubscriberAmounts]
-----------------------------
Information on all amounts paid for a subscriber, divided into different subscriptions.

 

[economy].[SubscriberLedgers]
-----------------------------
Displays the customer ledger and the types of financial transactions that have been performed for the subscriber.

Special fields in SubscriberLedgers:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**SubscriberAccount**: When you create a new subscription, then assigned this one SubscriberAccount. This is retained when the subscription is renewed. But if you have two parallel subscriptions, these will each have their own subscriber account .

**LedgerType** - some examples of values:

+---------+------------------------------+
| Type    | Description                  |
+=========+==============================+
| Charge  | Payment requirements         |
+---------+------------------------------+
| Payment | Payment                      |
+---------+------------------------------+
| Balance | Balance / balance adjustment |
+---------+------------------------------+
| Credit  | Credit                       |
+---------+------------------------------+



[Order].[OrderAmounts]
------------------------
Displays all orders in total (created, canceled and executed) and the value of these. Formed when an order is created and updated when it is completed or canceled.

 

[Order].[OrderCompletedAmounts]
-------------------------------
Displays the total number of orders executed and the total value of these. The TemplatePackageName field shows which package template was used .

 

[Order].[Orders]
----------------
All orders, including information about the date when the order was created / executed / canceled and the order status:

+--------+-------------+
| Status | Description |
+========+=============+
|  0     | InProgress  |
+--------+-------------+
|  1     | Completed   |
+--------+-------------+
|  2     | Cancelled   |
+--------+-------------+

 

[Order].[Products]
------------------
Displays all products ordered.

 
[payment].[DailyPaidAmounts]
----------------------------
Total amount of what is paid for each date, for each organization.
 

[payment].[Payments]
-----------------------------------
All payments for each individual subscriber. The most common source values are OCR, PayEx , Manual, Import and MI (migrated).
 
[subscription].[CanceledSubscriptions]
--------------------------------------
All canceled subscriptions, including reason for cancellation.

[subscription].[Contracts]
--------------------------
Information on binding time, whether the function is activated for use.

[subscription].[EnterprisePlans]
--------------------------------
General information about framework agreements.

[subscription].[SubscriberAccounts]
---------------------------------
Contains the first date for when a SubscriberAccount was used. This is used for financial reporting.

[subscription].[SubscriptionPackageProducts]
--------------------------------------------
All subscription packages related to product.

[subscription].[SubscriptionPackages]
--------------------------------------------
All personal subscription packages for a subscriber. Can be used on several subsequent subscriptions. Is basically a calculated copy of the template package.

Special fields in SubscriptionPackages:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
**BillingFrequencyId**: Example of values 1001 = Month, 1003 = Quarter, 1012 = Full year.

**BillingPlanId**: Each term can be linked to several payment plans . A payment plan controls, for example, how early payment claims are to be formed and when they are to be reminded. For example , you may want a 30-day payment deadline for companies, but three weeks for regular subscribers.

**SubscriptionPackageChainId**: This is used if you create package links. That is, you must first pay 99 kroner the first month, then 149 and maybe 199 before you go over to full price 249.

**InitialTermType**: This is used if the first period is to have a different length. 10 = «Until date », 20 = «Number of days», 100 = «Out the month», 200 = «Out the year» .  

**InitialTermValue**: This will then have slightly different values ​​depending on the type. For the value «10», then there will be a date. For "20" it will be a number of days ". For "100" and "200", it is not used.

**AutomaticStop**: This means that the subscription will be automatically stopped after the period.

 
[subscription].[Subscriptions]
------------------------------
All subscriptions registered in the system, with comprehensive information about, among other things, start and end time, details such as price, tax ( VAT ) , units, IsCancelled (0 = No), IsRenewed (0 = no) and reason for cancellation.

 





Appendix
========

To get a better overview of the tables in the reporting database, you can use the SQLs below as an aid.
 

Count the number of columns in all tables
-----------------------------------------

select count ( COLUMN_NAME ) CountColumns from INFORMATION_SCHEMA . COLUMNS where TABLE_NAME not in ( '__EFMigrationsHistory' , 'Snapshots' , 'PowerBiConfigurations' , 'Commits' ) and TABLE_SCHEMA <> 'Sys'


Output per. 20 November 2020: 446

Lists all columns in all tables
-------------------------------

select TABLE_SCHEMA + '.' + TABLE_NAME as ' TableSchema.Table_Name ' , max ( ORDINAL_POSITION ) as ColumnsCount
from INFORMATION_SCHEMA . COLUMNS where   TABLE _NAME not in ( '__EFMigrationsHistory' , 'Snapshots' , 'PowerBiConfigurations' , 'Commits' ) and TABLE_SCHEMA <> 'Sys'
group by TABLE_SCHEMA + '.' + TABLE_NAME order by TABLE_SCHEMA + '.' + TABLE_NAME

.. image:: Tables.png
  :width: 400
  :alt: Alternative text