.. _subscription-orders:

***************************************
Creating new subscriptions using orders
***************************************

An order is an encapsulation of a series of steps/stages to help create new subscriptions and keeping the flow in a semi-atomic transaction, meaning that if an order fails to complete (or is never completed by the user)
there is no clean-up duty for the client, and when an order completes there should be no series of followup steps such as making sure the first invoice is generated etc.

While it is possible to create subscriptions without using an order, we recommend that clients use orders to simplify the process.

An order is split into several steps, primarily to ensure consistensy between the various things that an order covers.

#. Order Initialization - Captures and calculate information such as price and which agreement to use
#. Payment Agreement Registration - Typically defers to third parties for payment processing
#. Order Completion - Gathers information from the previous steps and finalizes/activates the subscription

Secondly applications/clients might want to prepare orders, for instance to send out pre-filled order details for acceptance by customers or other similar scenarios.

.. image:: /_images/order-sequence.svg
    :align: center
    :alt: Order Sequence Flow

.. Note::

    There might be timeout/expiration issues with this approach if using online Payment Service Prodivers (PSPs) such as {payex}.
    because the order initialises the payment (at the time of writing the session is valid for two weeks using PayEx for instance)

The anatomy of an Order
=======================

The main thing to remember about orders, is that they are not actually resources/entities as such, 
but rather encapsulates parameters of a workflow.

An order contains information about a few things

* Who/What is subscribing to an offering - the ``subscriberId``
* What offering are they subscribing to - the ``templatePackageId`` (see :ref:`plans <plans>`)
* How should payment be processed, specified by either of the following:

    * The ``paymentAgreementId``
    * The ``paymentAgreementParameters``
* Who is offering this subscription - the ``organizationId``

The are other fields, all of which come into play in various scenarios.

Package Choices/Overrides
-------------------------
As the name implies a ``TemplatePackage`` is a template for the package/plan that will be created for a given subscription.

Some of the parameters of a package may require choices by the subscriber (or the sales process), these choices are often optional, but can be defined using the ``templatePackageChoices``.

To figure out which things are overridable by the user, have a look at the specific template package as it defines the flexibility.

The choices are validated when creating the order, and again when completing it, so it should not be possible to define an illegal order if for some reason the template is changed.

.. Note ::

    There is some confusion about the terminology related to packages. 
    The word Package is used in the API while the term Plan is used for the self-service and Merchant UI.

Processing Payments
-------------------
Most of the time, there is a need to enact some sort of payment process.

When an order is created, if the paymentMethod is set to ``PayEx`` or similar, the response will contain a ``terminalRedirectUrl``.

This :abbr:`URL (Uniform Resource Locator)` indicates where the client should send the user so he/she can input the payment card details.

The parameters must contain a return url and a cancel url (they can be the same).
When the user completes or cancels the payment process, he/she is returned to either of these pages, with an Id in the querystring representing the order.

Depending on where the user was redirected the client can do whatever is needed to update local systems and either :ref:`Cancel <cancel-order>` or :ref:`Complete <complete-order>` the order.

.. Note: 

 Currently the payment process must always be {payex} processed card payments, but we are working actively on more alternatives.

 Invoice Contact/Address
 -----------------------
 |projectName| manages invoice addresses by creating a separate subscriber contact (see: :ref:`Subscribers Section <subscribers>`) and associating it with the subscription.
 
 It is possible to either define an existing contact id in the `invoiceContactId` or by defining details for a new contact (to be associated with the ordering subscriber).
 The details to provide are the same as for a generic subscriber contact.

Orders and Subscribers
======================
Subscribers can either be created before an order, or during the order flow, if the client creates subscribers the `subscriberId` must be specified with the order.

In case the subscriber should be created with the flow, an `externalSubscriberId` and/or `subscriberNumber` must be provided.

Completing an Order
===================
.. _complete-order:

Completing an order takes a bit of time, so we suggest the client presents the user with some sort of processing feedback.

Completing the order currently executes a few different tasks such as

#. Builds a custom package for the subscription and verifies the result is valid
#. Complete the transaction at the PSP to ensure that the agreement can be used
#. Creates a PaymentAgreement for the given payment card
#. Creates a subscription with the created PaymentAgreement as the payment method
#. Create a payment demand with the amount from the order and a due date which is the same as the subscription start

Following these steps another series of steps will be enacted by the billing engine

#. Create and Issue an Invoice for the Payment Demand
#. On the due date, initialize a payment/capture of the demand
#. Captures the demand amount on the payment card
#. Creates a payment representing the captured amount
#. Create a draft for the next period 

These additional things happens asynchronous, so don't expect it all to be completed the second the order response is generated. 
But it basically means you can direct the user to a payment/invoice overview and within a short time they will see their invoice and/or payment.

Once completed the response contains an updated order view with the new status and various Id's that informs the client of what was created.

While not immensely useful the order will persist so you could choose to have a list of *purchases/orders* or some such in the client to show historic orders.

Subscriptions generated by the passing of time (i.e. recurring subscriptions) are not treated as orders and won't mess up the view.

Cancelling an Order
===================
.. _cancel-order:

If for some reason the user opts to cancel the payment process or the order, we recommend that the client explicitly cancels the order.

While not strictly necessary it helps with a few things

* The order is set as cancelled and no further attempts to process it can occur
* If applicable, any payment process at the PSP is cancelled

The fact that an order was cancelled might be useful to business people to follow up during various marketing/sales campaigns or similar activities.

PSP Callbacks
==================
.. _psp-Callbacks:

Many PSPs have a concept of a `callback` used for ensuring that payments are processed correctly in the event of a client failure. 
Typically failures are things such as loosing internet connectivity, user closes browser session, browser/machine crashes, appliction errors and the list goes on.

The idea is that the PSP will do a `callback` to a registered URL out-of-band from the browser.

We recommend that the client implements some sort of callback handling that will either :ref:`Cancel <cancel-order>` or :ref:`Complete <complete-order>` the order.

.. Important::

    |projectName| currently has no built in callback handling that can be utilized but it is on the roadmap.
