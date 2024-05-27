.. _changelog-r124:

***********************
Release May 28th 2024
***********************

Sunshine reggae is a thing, perhaps sunshine coding is a thing as well. It sure has felt like it for this sprint with the summer heat hitting early here in Oslo.

We are ready with a new release, with a lot of minor improvements spread throughout different areas of the platform. 

While mostly ironing out issues with features related to tenants operating in Denmark, we are also hard at work making things more flexible and easier for all other tenants.

A concrete example of this includes a new integration to allow automated distribution of EHF invoices, without having to bother about pesky file transfers.

There is one more release before the summer, so stay tuned, it will most likely land in your lap in late June.


API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

Added
-----

* Support for rescheduling reminder generation. Opens up the possibility of postponing a reminder or pushing it forward if desired.
* Enterprise Plans can now be assigned a Payment Agreement for billing purposes.
* OIO is now a supported Payment Method, it behaves similar to EHF, but is only valid for Danish invoice recipients.

    * Orders can be generated with OIO.
    * New payment agreements can be created using OIO and switching to/from OIO is also allowed.

* Refreshing of card metadata (Mask and Expiry time) for Swedbank Pay card payments where cards have been replaced with Network Token support. Enabling automated card updates. Read more about Network Tokenization on https://developer.swedbankpay.com/checkout-v3/features/optional/network-tokenization/
* Payments can now be matched directly to a Subscriber Account via a new Matching Type. This will bypass regular invoice matching and trigger an account update instead (with related automated settlement as a consequence).
* Billing can now do accounting and settlement of payments that are associated with a Billing Account post-completion.
* **[Preview]** |MobilePay| agreements are now deactivated automatically on subscription expiration, similar to how Vipps agreements are deactivated.
* **[Preview]** Account configuration for MySupply VaxTransfer for live EHF and OIO invoice distribution.
* **[Preview]** Automatic invoice distribution of EHF and OIO via VaxTransfer.

Changed
-------

* Introduced a new summary field for the total number of additional products based on the number of unit ordered for subscription plans (Units times count of additional products).
* SubscriptionCancelled notifications are now less likely to be sent before the cancellation has been propagated throughout the system.
* Improved on the resolution of results from Kart Verket to give a more accurate number of found results in case of multiple results.


Fixed
-----

* AccountId path parameter is now fixed so account transfers works as intended.
* |eFaktura| Allowances will now be generated with a static system text if no description is present to avoid failures.
* An issue where Preliminary Payment Demands on Enterprise Plan would exclude the subscription price in the total Amount calculation and only contain subscription 2 to _n_.
* A case where charges would have invalid ledger marker, causing subsequent issues during write-off.
* Allowance ledger marker would be ignored during write off.
* A race condition causing significant delays when creating initial subscriptions without going through the order process.
* **[Hotfix]** An issue where additional products would not be populated for subsequent steps in chained subscription plans from the order process.
* **[Preview]** API route for exporting |BetalingsService| files has been changed so the path is unique in the API description.
* **[Preview]** |MobilePay| is now correctly set as the source on payments when automatic payment generation occurs.

Deprecated
----------
We call out the following deprecations, the endpoints/field will be removed in a future version, the exact timing depending on existing use and adoption of replacements.

* We are deprecating the endpoints ``/paymentdemand/{id}/credit/completely`` and ``/paymentdemand/{id}/credit/partially`` in favor of ``/paymentdemand/{id}/credit`` endpoint.
* We are deprecating the field ``TaxPercentage`` on the endpoint for creating Account Payment Demand transaction ``POST /paymentdemand/``, in favour of specifying a list of Tax Details.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

Added
-----

* Option to select Subscriber Account when creating payments manually.
* Support for connecting payments to subscriber accounts if not matched automatically.
* Option of assigning a `Name` to shared users instead of just displaying the email.
* **[Preview]** OIO is now supported as a payment method for new agreements, similar to EHF.
* **[Preview]** |MobilePay| support.

    * Payments with source MobilePay gets a customized branding logo.
    * MobilePay Agreements can be viewed with transactions.


Changed
-------

* Additional validations for switching payment agreement on existing subscriptions, handling requirements for Organization Number if switching to `EHF` for instance.
* Option to reset product selection during creation of a new subscription.
* The |Vipps| Account Configuration via now also enables configuration of |MobilePay|, determined by the chosen country.
* Tooltip shown for Organization Number to clarify different meanings depending on country of operation.
* Number of available shared users now calculated using backend provided summary field on the subscription plan.

Fixed
-----

* An issue where the username/principal name was shown for a user instead of the assigned Display Name.
* An issue where searching for users would target the wrong underlying field.
* Handling of missing responses from remote source on payment provider transactions (when viewing payment agreement details), causing an information message to be displayed instead of just a blank view.

Self-Service and Sales Poster
=============================
The following new features and improvements are now available in the self service and sales poster.

Added
-----

* Support for multiple new payment methods during order registration via the sales poster: `EHF`, `MobilePay`, `OIO` and `Email`.
* Danish as a possible language for sales poster and self-service.
* Option of assigning Name to shared users instead of just the Email address.

Changed
-----

* Validations for contact updates related to requirements for the current active payment agreements.
* Adjusted payment method selection for orders via the sales poster when adding invoice contacts, based on the available information on the subscriber.

Fixed
-----

* An issue where it was possible to switch to an expired Payment Agreement.