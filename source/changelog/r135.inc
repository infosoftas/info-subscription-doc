.. _changelog-r135:

******************
Release June 16th
******************

The 5th release of INFO-Subscription in 2025 is here, it also marks the last release before the summer holidays.

This release contains a mixed bag of things, such as more improvements to the newly introduced additional products and additional details on billing transactions to facilitate better reporting and auditing of billing transactions. 
It also contains a number of improvements to the checkout to improve the conversion rate.


API and Backend
===============

Added
-----

* **[Preview]** Added validation to prevent a plan change to a different billing frequency when an existing subscription has an additional product with a price override.
* **[Preview]** Support for updating some header level information on already issued invoices.
* Added property to Allowance and Charge account transaction creation that indicates if the registered transaction is adjustment is included in the ledger (and thus needs to be reversed when billing the transaction).
* Added support for resubmitting an existing invoice to the PEPPOL Network.
* Subscriber Contacts can now be queried directly via the OData reporting API. Previously they were only available via the owning subscriber.
* `POST /order/{id}/complete` now contains an optional parameter to control wait time (or disabling waiting entirely), before returning a result. This is useful if your workflow has an upper bound on the processing.
* A new complete transaction log for all billing related transactions is available in the reporting subsystem.

Changed
-------

* Allowances now contains TaxDetails when generated based on transactions with TaxDetails (Split and Proration for Paid periods).
* Added support for retrieving upstream/remote status of Vipps MobilePay ePayments.
* Final/Balance Demands with allowances from the billing account will now map these as allowances on the Invoice. Previously they were mapped as negative charges.


Fixed
-----

* **[Preview]** An issue where scheduled plan changes would not properly merge included additional products with identical purchased additions products.
* **[Preview]** An issue where scheduled removals of additional products would not work when the product was present as both an included product and a purchased product.
* An issue in the reporting subsystem where subscriber contact information was not always correctly set when retrieving details from Vipps MobilePay.
* An issue where the proration calculation for paid periods would be off by one day. Resulting in invalid amounts being calculated for allowances. The allowance was more than owed to the subscriber, so the negative effects was to the seller.


Merchant Client
===============

Added
-----

* Option to search for subscribers based on their Organization Number identification (Organization Number and CVR Norway, Sweden and Denmark).
* New possibility to disable eFaktura agreements manually as a fallback when the subscriber is unable to cancel it upstream.


Changed
-------

* Price display to ensure prices/amounts are always shown in an identical manner.
* Reintroduced option do searches without an organization filter for a number of search views.
* Option to filter on organization number for invoice searches.
* General styling improvements to some of the grid views to make them more consistent with the rest of the application.


Fixed
-----

* **[Preview]** An issue where transactional/account invoices could not be created if no default Currency was configured.
* An issue preventing activation of Enterprise Plans if not activated during creation.
* An issue where subscription plans without an organization restriction could not be used when bulk creating subscriptions on enterprise plans.
* A minor performance issue where payment agreements were sent during credit and re-issue even if the same agreement should be reused.



Self-Service, Sales Poster and Checkout
========================================

Added
-----
* Option to regret a subscription cancellation if it is in the future.
* Support for journey specific text for checkout.
* Support for displaying plan information on checkout for journeys related to ordering a subscription.


Changed
-------

* Sorting of subscription periods so active subscriptions are always shown first.
* Price display to ensure prices/amounts are always shown in an identical manner.