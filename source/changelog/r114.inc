.. _changelog-r114:

************************
Release June 13th 2023
************************

Time flies when you are having fun developing subscription software.
It's time for another release, the last one before the summer holidays kicks in.
That means the next release will not follow our regular monthly cadence - we will be back with another release some time in August most likely.

We will try with a new format for the changelog, it will still be divided into three main parts, but we will also attempt to follow a type of change convention outlined on https://keepachangelog.com/

This release is a mix of bug fixes and some minor new features, the most interesting being a new behaviour for cancelling subscription based on their lack of payments.

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Subscription Payment Demands and Order Payment Demands can now be credited via the POST /paymentdemand/{id}/credit endpoint.
* Support for bulk replacing all Reminder Settings on a Dunning Process via the Dunning Process update endpoint.
* Support for adding/replacing Payment Request Settings on a Dunning Process via the Dunning Process update endpoint.
* **[Preview]** New logic for evaluating automatic cancellation due to missing payments (Payment Stop).

Fixed
-----

* Billing Account transactions would not always apply currency to the data model, causing it to be unavailable in the API and reporting/analytics solution.
* Fixed an issue where removing a future cancellation would lead to invalid accounting and ledger information because any prorated charges would be invoiced again and any allowances would be written off/credited.
* Fixed an issue where it was impossible to credit an Order Payment Demand for a future subscription that had been deleted.
* If a billing account had an outstanding Payment Demand with an allowance in excess of the total payment demand amount, and a new payment was registered, the excess allowance would disappear from the account. This issue has now been fixed.
* All Payment Demands are now correctly assigned a time component of the payment due, this fixes an issue where Payment Requests would be captured slightly before the actual due time (Mostly relevant for |SwedbankPay|).
* |SwedbankPay| agreements are now stored without time component for the expiration to prevent undefined adjustments of the timezone (the timezone is unknown and depends on the card issuer).

Changed
-------

* Payment Requests for |VippsRecurring| are now offset by 1 entire day, to alleviate a problem where Vipps captures money earlier than the actual due time (Vipps operates in entire days, while INFO-Subscription operates with a time component).
* Adjusted/Improved the Billing Account selection process When generating new orders, specifically start of a new subscription after a cancellation time has been surpassed but before the original period expired will now reuse the account in case its the only one available. Previously a new one would be generated.
* **[Preview]** eFaktura agreements will no longer be automatically applied to subscriptions with a length of less than 5 days. To avoid them always being paid late.

Deprecated
----------
We call out the following deprecations, the endpoints will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* We are deprecating the endpoints /paymentdemand/{id}/credit/completely and /paymentdemand/{id}/credit/partially in favor of the afore mentioned /paymentdemand/{id}/credit endpoint.

Security
--------

* Fixed an issue where a compromised upstream service for EHF receiver validation or Azure Event Grid could lead to our services being used for a DoS attack.

[Preview] New behavior: Automatic cancellation for missing payments (Payment Stop)
-----------------------------------------------------------------------------------

We have introduced an alternative behaviour to automatically cancel subscription with a lack of payments.
With the modified behaviour all payment demands that are due before the threshold will be evaluated and the amount evaluated is the sum of these demands.
In addition any outstanding billing account Allowances will be subtracted from the amount.

Only if the final amount is above the balance threshold will the subscription be cancelled.

Interested in participating in the preview? Contact support, find the details on {SUPPORTPAGE}.


Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* **[Preview]** Support for Interactive Distribution Innovation Address Lookup (Address Helper) during address registration.
* Aggregated total of outstanding account transactions from the billing account are now shown in the Subscriber Ledger.

Fixed
-----

* An issue with the total amount on Subscriber Ledger for Enterprise Plans.
* An issue where adding a Vipps configuration would present an error message even though the configuration was created.
* Updating an Organizations main identifier (Organization Number) would reset other identifications configured, this has now been corrected.
* An issue where crediting an Invoice for an Enterprise Plan, with a replacement, would lead to an error when generating the replacement Invoice.
* Contract time was shown incorrectly when changing Subscription Plan.
* An issue where it was not possible to remove a future cancellation.

Changed
-------

* Minor visual improvements to outstanding billing account transactions.
* Multiple improvements and adjustments to the deliveries view.


Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self-service client

Added
-----

* **[Preview]** Support for Interactive Distribution Innovation Address Lookup (Address Helper) during address registration.

Fixed
-----

* When no sales terms are configured, an error message will be displayed instead of causing an internal server error.
* An issue with Orders using Vipps would keep on displaying the message to not close the window after completing the Vipps interaction.

[Preview] Interactive Distribution Innovation Address Lookup (Address Helper)
-----------------------------------------------------------------------------------

With the Interactive DI Address Lookup Merchants and Subscribers will be presented with address suggestions based on information from the DI Address Helper API.
As the user enters street information, and selects a street additional suggestions will be provided for house, apartments etc.

The end result is a high quality address that is directly transferred to DI when generating Distribution and Delivery information.

Interested in participating in the preview? Contact support, find the details on {SUPPORTPAGE}.