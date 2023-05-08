.. _changelog-r113:

************************
Release May 15th 2023
************************
Another month has gone by and it is time for a new release. 
This release mostly contains under the cover improvements and upgrade of various components, with a few visual improvements and of course some bug fixes.


API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

* Added an option to write-off billing account transactions. 
  
  * Depending on the state of the transactions, they will either generate a balancing transaction to the subscriber ledger, or just be removed from the subscriber account so it is not included on the next invoice.
  * The transactions that are posted on the subscriber ledger are also available in a new table in the reporting sub-system.

* Included Currency on billing account transactions. This is solely a query/response simplification since the Currency is already accesible multiple other places in the hierarchy of the transaction.
* Fixed an issue where consuming allowances during reminder generation would consume the entire allowance, even when only a partial consumption was allowed.
* Adjusted payment demand generation so that due now includes time, and not always defaults to midnight. This alleviates an issue where payment provider integrations such as Swedbank Pay, could end up charging for the next subscription several hours before it was actually due.


Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Added support for writing off account transactions.
* Added Payment Amount for demands settle by an excessive payment. Now the behaviour is similar to inadequate payments.
* The behaviour for showing reports have changed so that reports are now refreshed on demand if expired. Previously they would just be dormant, now a waiting message is shown so the merchant can come back after a few minutes.
* Fixed an issue where it was possible to cancel an enterprise plan related subscription outside its current period.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Fixed an issue where the Distribution Innovation Address helper would choose the wrong Delivery Point Id in case where apartments had its own Id.