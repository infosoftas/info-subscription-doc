.. _changelog-r139:

**********************
Release December 10th
**********************

Last release of 2025, this is a minor release with a mix of fixes and small improvements.

Happy holidays to everyone, we will be back with a new release in January.

API and Backend
===============



Added
-----

* Validation for templates with chains, making sure the chain is valid for the choices/selections also after the first period. This prevent invalid orders from being created, and ensures that renewals will work as expected (the chain will still be terminated on renewal if invalid). This change is relevant for both Order creation and Subscription Plan pre-validation.
* Accounting transaction information for |SwedbankPay| when the transactions are managed by a payment request in the billing system.
* Support for mapping Additional Products to User Authorization information immediately when adding them to a running subscription.


Changed
-------

* The generation of final/account-balance demands have been changed so it now consumes account balance directly, as charges and allowances, where it would previously attempt generate details as if they where products. This brings the behavior in line with how other demand types handle account balances.
* Adjusted text for handling Charges and Claims on |eFaktura| demands (only relevant for Norwegian recipients).
* Extended the |SwedbankPay| transaction response to include Currency and newly added accounting information.
* Retrieving remote |VippsMobilePay| agreement information now also includes campaign details.


Fixed
-----

* An issue where Tax Details were not generated correctly for demands where allowances was split. This could lead to negative total amount on invoices, and incorrect tax reporting.
* An issue where the selected Payment Method and Provider would not be stored correctly on orders. The billing would be correct, affecting mostly the reporting experience.
* Two related issues in reporting where AccountTransactionHistory entries would not be re-opened correctly after being reverted to the billing account during crediting.
* An issue where subscription periods would be negative in some edge cases when using "remainder of year" or "remainder of month" as the initial period length (term).
* An issue introduced in the previous change in serialization rules, where updating an issue invoice with new header information was not accepted even if modelled correctly.


Merchant Client
===============

Added
-----

* **[Preview]** New tool for bulk crediting and write-off of outstanding demands and transactions on accounts. Allows merchants to "reset" a subscribers account to zero balance in a controlled manner.
* Support for directly refunding |VippsMobilePay| charges from the Merchant Client. Avoids the need to context-switch to the Vipps or MobilePay portal for refunds.
* Support for directly refunding |SwedbankPay| transactions from the Merchant Client. Avoids the need to context-switch to the SwedbankPay portal for refunds.


Changed
-------

* Extended the economic overview with additional information for each transaction.
* A few minor translation adjustments to some grid columns and filter labels.

Fixed
-----

* An issue where it was not possible to update a temporary delivery address change.
* A performance issue for the Subscription Plan view which would sometimes hang and abort after 30 seconds.

Self-Service, Sales Poster and Checkout
========================================

Added
-----

* **[Preview]** Support for an alternative `client_id` during checkout. This allows merchants to use different client applications for Self service and ordering. Possibly streamlining the user experience with other front systems, such as the CMS. Essentially it is possible for checkout and CMS to shared a client.
* Checkout will now attempt to determine the default country based on the OrganizationId defined in the selected subscription plan. Prefilling the Country field where possible. If undefined will fallback to a blank field.

Changed
-------

* For existing subscriber checkout should now update contact information with the latest provided information. Previously it would not update anything on existing subscribers. This uses a new callback feature in the Orders SDK.

Fixed
-----

* An issue in checkout making it possible to order on an expired Subscription Plan.
* An issue in checkout where it was not possible to start a payment flow on one provider type and then switch to another provider type without loosing information on the subscriber in the process.