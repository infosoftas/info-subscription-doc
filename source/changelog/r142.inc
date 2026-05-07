.. _changelog-r142:

**********************
Release May 13th
**********************

We are back with another release, it has been almost two months since the last one. 
The release includes a mix of new features, improvements to existing functionality, and bug fixes across the API, Backend, Merchant Client, Self-Service, Sales Poster and Checkout.
Notable features in terms of the business impact include the support for preventing churn and presenting next-best-offers in checkout and self-service.

In addition to the public facing changes listed below, there are also a number of internal improvements and optimizations that have been made to enhance the overall performance and reliability of the system, as well as paving the way for future features.


API and Backend
===============

Added
-----

* **[Preview]** Introduced configuration options to allow Payment matching on paid and credited demands and invoices. This might be useful when consumers have configured fixed bank transfers instead of relying on the invoice and the associated ExternalInvoiceIdentifier.
* **[Preview]** A configuration option has been added so merchants and restrict Billing Account generation during the order process to only ever allow one Billing Account per customer. This is useful for merchants who want to ensure all orders from a customer are consolidated under a single Billing Account. It is not a system wide setting, and is only meant to steer orders so that integrations does not make mistakes.
* **[Preview]** Support for defining subscription plans directly, instead of relying on preconfigured Template Plans and the available override parameters. This allows more control in case where individual subscription plans are needed. Especially useful for merchant with primarily enterprise customers.
  The feature consists of multiple parts:

    * New API endpoint to create and get subscription plans directly.
    * Modified endpoint for creating subscriptions to allow associating with a directly created subscription plan.
    * Modified order endpoint for referencing existing subscription plans when creating orders.
    * Modified endpoints for scheduling subscription changes to allow referencing existing subscription plans.

* Option to directly create Demand Reminders. Useful when dunning is driven by external parties such as debt collection agencies, or when the merchant wants to have more control over the timing and content of reminders manually.
  Refer to :ref:`Creating Reminders On Demand <on-demand-reminder>` for more details.

* Support for updating some credit note header information and re-submitting it to the :ref:`PEPPOL <provider-peppol>` network. Brings feature parity with the same functionality for invoices, and allows merchants to correct mistakes in credit notes without having to cancel and re-issue them.
* The feature for automatically waiving reminder fees on payments, now support all increments of reminder fees instead of just the original Invoice amount. In essence if a subscriber pays the exact amount on any reminder or invoice, the remaining fees will be waived. 
* The reporting subsystem now includes Tax Details for reminder fees. Previously this was generalized to a single percentage.
* Reporting now includes the transaction type for Allowances and Charges, enabling better reporting and analysis of the different types of fees and allowances that are applied to payment demands and billing accounts.


Changed
-------

* Removed restriction on overriding Due Date when crediting and re-issuing account payment demands. It now follows the payment agreement rules for due date calculations similar to how Subscription and Order demands work.
* Removed properties from reminder schedules that were never populated (Payment Provider and Payment Method) to avoid confusion.
* Cancellations triggered due to missing payments (debt cancellation), will now update the subscription cancellation time if the subscription was already cancelled. This ensures that subscribers cannot circumvent the early cancellation by pre-emptively cancel at the end of the current period.
* The logic for decoding ExternalInvoiceIdentifiers (KID or OCR Reference), has been updated to allow decoding of "filler" characters in a sensible way, instead of responding with an error.
* Reminder Document states will now be updated when the underlying Invoice is marked as paid to ensure the state of the reminder follows the invoice. There is still no separate state on the reminder, i.e. it cannot be marked as paid directly.
* When creating an order, where a Denial Orders blocks the registration, the validation error will now include the type of Denial Order that caused the block. This allows applications to better understand why an order was blocked and take appropriate actions or display relevant information to the user.
* Changed Payment Registrations so it is no longer possible to approve/complete a payment without a valid Subscriber Account. This prevents payments from being ending in a orphaned completed state without any actionable billing relationship.


Fixed
-----

* An issue where products and organization data would not be automatically synchronized to the reporting sub system, causing reports to be missing data until a manual sync was triggered.
* An issue where crediting already settled payment demands, did not handle reminder fees correctly. Allowances are now added to cover the reminder fee when crediting, and the credit note issued on shows the original invoice amount to avoid drift with recipients.
* An issue where transferring a Charge or an Allowance from Subscriber A to Subscriber B and BACK AGAIN would fail.
* An issue where changing the payment agreement on a running subscription with an existing payment demand, would not update the agreement on the demand. This affected only changes to/from CreditCard agreements, as most other switches would not require an update of the demand.
* The |Vipps| and |MobilePay| refund wrapper now returns the right refunded amount, previously it always returned 0.

Deprecated
----------

These items will be removed in a future release.

* The Map User API endpoint in the simplified Order API is now deprecated, and removed from the reference documentation. This endpoint was used to map user identities during subscriber creation and order completion. The functionality has been replaced with a more streamlined approach.
* Purchased Additional Products in the SubscriptionPlan object will be removed in a future release (Products with IncludedInPlan = false). They can be accessed via the `PurchasedAdditionalProducts` property on the Subscription object instead. This change was made to better separate the concept of products included in the plan and products that were added on top of the plan.


Merchant Client
===============

Added
-----

* **[Preview]** Option to configure 'next-best-offer' for checkout (see checkout section below for details).
* Support to configure terms acceptance for checkout (see checkout section below for details).
* Option to sending reminder copy (PDF) for Enterprise Plan Payment Demands, this works the same way as for the other demand types that already has the option.
* The possibility to filter expired plans in the Enterprise Plan overview.


Changed
-------

* Removed menu items for now data dumps and invoice production. These have been replaced with more focused features in the UI.
* Handling of manually creating and updating payments so Subscriber Billing Account is enforced in the UI as well as in the API. This prevents payments from being ending in a orphaned completed state without any actionable billing relationship.
* Improved the performance for the Dashboard.

Fixed
-----

* An issue where timezone would be ignored, leading to inaccurate data in the dashboard.
* An issue where the language element would not reflect the chosen language.

Self-Service, Sales Poster and Checkout
========================================

Added
-----

* **[Preview]** Checkout: Support for 'next-best-offer' style offer selection in checkout in case of Denial Orders blocking the order. This needs to be configured to a fixed offer in Merchant.
* Checkout: Support for toggling if terms should be accepted by explicitly (checkbox) or implicitly. This varies by market and payment provider requirements and is now configurable in Merchant.
* Self-Service: Support for displaying a fixed offer, similar to the 'next-best-offer' in checkout, in the self-service portal when subscribers wants to cancel their running subscription. This effectively results in a subscription "downgrade" (change of plan) instead of a churned subscriber.

Changed
--------

* Internal handling of |SwedbankPay|, |Vipps| and |MobilePay| accounts to make account selection explicit so invalid account setup is easier to detect and handle when setting up checkout journeys  (a configuration error will be presented).
* Styling differences between the various checkout views.


Fixed
-----

* An issue where the language element would not reflect the chosen language.
* Another issue where subscriber information was missing due to multiple navigation actions by the user during the checkout process.
* An issue where some query parameters were case sensitive in checkout.
* Checkout now supports templatePlanId again (in addition to the obsolete templatePackageId).
* An issue where using the back button during checkout would cause payment providers selection to revert to the default instead of the configured providers.