.. _subscription-orders:

***************************************
Creating New Subscriptions Using Orders
***************************************

This document describes the process of creating new subscriptions using "orders" in |projectName|. An **order** is a workflow that encapsulates the steps required to create a subscription in a semi-atomic transaction. Using orders helps ensure consistency, reduces manual follow-up, and simplifies error handling for clients.

Key Benefits of Using Orders
----------------------------

- No manual clean-up required if an order is not completed.
- No need for follow-up steps after order completion (e.g., invoice generation is automatic).
- Ensures a consistent, reliable subscription creation process.

While it is possible to create subscriptions without using an order, we recommend using orders for simplicity and reliability.

Order Workflow Overview
-----------------------
An order consists of several steps:

#. **Order Initialization** – Captures and calculates information such as the selected subscription plan, price, and payment agreement.
#. **Payment Agreement Registration** – Registers payment details, often via third-party providers (required for credit cards, mobile payments, etc.).
#. **Order Completion** – Finalizes and activates the subscription using information from previous steps.

.. mermaid:: order-sequence.mmd
    :align: center
    :alt: Order Sequence Flow

Clients may also prepare orders in advance, for example, to send pre-filled order details for customer acceptance.

.. note::
    There may be timeout/expiration issues with this approach if using online Payment Service Providers (PSPs) such as {payex}.
    For example, a payment session with {payex} is valid for two weeks at the time of writing.


Order Anatomy
=============

Orders are not persistent resources or entities; instead, they encapsulate the parameters and state of a subscription creation workflow. Once completed, an order is generally only useful for reporting or statistical purposes.

Key fields in an order include:

- **subscriberId**: Who/what is subscribing to an offering
- **templatePackageId**: The offering being subscribed to (see :ref:`plans <plans>`)
- **paymentAgreementId** or **paymentAgreementParameters**: How payment should be processed
- **organizationId**: Who is offering the subscription

Other fields may be relevant in specific scenarios.


Subscription Plan Choices and Overrides
---------------------------------------
A ``TemplatePackage`` acts as a template for the subscription plan to be created. Some plan parameters may require choices by the subscriber or sales process. These are often optional, but can be specified using ``templatePackageChoices``.

To determine which parameters are overridable, refer to the specific template plan documentation. Choices are validated both when creating and completing the order, ensuring that only valid orders are processed, even if the template changes.

Refer to the :ref:`template plans section <subscriptionplan-templates>` for more details.

.. note::
    There is some confusion about the terminology related to "packages" and "plans".
    The word "Package" is used in the API, while "Plan" is used in the self-service and Merchant UI. In general, they are synonymous.


Processing Payments
-------------------
Most orders require a payment process. If the payment method is set to ``SwedbankPay`` or similar, the order response will include a ``terminalRedirectUrl``.

This :abbr:`URL (Uniform Resource Locator)` is where the client should redirect the user to enter payment card details.

The parameters must include a return URL and a cancel URL (these can be the same). 
When the user completes or cancels the payment, they are returned to the appropriate page, with the order ID in the query string for identification..

Depending on the outcome, the client should update local systems and either :ref:`Cancel <cancel-order>` or :ref:`Complete <complete-order>` the order.


Alternate Invoice Contact/Address
---------------------------------
|projectName| manages invoice addresses by creating a separate subscriber contact (see: :ref:`Subscribers Section <subscribers>`) and associating it with the subscription.

You can either specify an existing contact ID in ``invoiceContactId`` or provide details for a new contact (to be associated with the ordering subscriber). 
The required details are the same as for a generic subscriber contact.

The end result is that the subscription will be billed on the subscriber, but invoices will be sent to the contact given.

This is typically used for gift style scenarios, and for subscriptions where a company is paying for a personal subscription.


Orders and Subscribers
======================
Subscribers can be created before an order, or as part of the order flow. If the client creates the subscriber, the ``subscriberId`` must be specified with the order.

If the subscriber should be created during the order flow, an ``externalSubscriberId`` and/or ``subscriberNumber`` must be provided.


Completing an Order
===================
.. _complete-order:

Completing an order may take some time, so we recommend providing users with processing feedback.

The completion process includes:

#. Building a custom plan for the subscription and verifying its validity.
#. Completing the transaction with the PSP (if applicable).
#. Creating a PaymentAgreement for the selected provider.
#. Creating a subscription with the defined PaymentAgreement as the payment method.
#. Scheduling a payment demand with the order amount and a due date matching the subscription start.

After these steps, the billing engine performs additional asynchronous tasks:

#. Creating and issuing an invoice for the payment demand (immediately or in the future, depending on the schedule).
#. On the due date, initializing a payment request for the demand.
#. Creating a payment representing the captured amount.
#. Creating a draft demand and invoice for the next period.
#. Scheduling a payment demand for the next period.

These additional steps happen asynchronously, so the user may not see the invoice or payment immediately. 
However, they will appear in the payment/invoice overview shortly after order completion.

.. note::

    Refer to the :ref:`billing overview <billing-cycle>` section for information on how recurring billing is handled.

Once the order is completed, the response contains an updated order view with the new status and various IDs indicating what was created.

While not always essential, the order will persist, allowing clients to display a list of historic purchases/orders if desired.

Subscriptions generated by recurring billing (i.e., not via orders) are not treated as orders and will not clutter the order history view.


Cancelling an Order
===================
.. _cancel-order:

If the user cancels the payment process or the order, we recommend that the client explicitly cancels the order.

While not strictly required, explicit cancellation provides several benefits:

- The order is marked as cancelled, preventing further processing attempts.
- Any payment process at the PSP is cancelled (if applicable).
- Statistics and reporting are more accurate.

Cancelled orders can be useful for business follow-up, such as during marketing or sales campaigns.


Automatic Cancellations and Completions
---------------------------------------
In some cases, |projectName| will automatically close open orders. Currently, this applies to orders with ``Vipps`` and ``MobilePay`` payment agreements.
Many consumers close the browser window after being redirected to the Vipps or MobilePay app, resulting in incomplete orders. 

If an order is not completed, the upstream agreement is automatically checked after a short period (about 5 minutes):

- If the agreement is approved, the order is automatically completed.
- If the agreement is rejected or expired, the order is automatically cancelled.

If the agreement expires, the order cannot be completed and is cancelled automatically.

This behaviour may be disabled by setting ``disableVippsCompletion`` to ``true`` in the order configuration.

Asynchronous Completion of Orders
---------------------------------
In some cases it is desirable to provide the user with immediate feedback once the order is completed.
It is possible to make the order completion fully asynchronous by setting the ``maxPollingTimeout`` to ``0`` during the Order Complete API request.
