.. _payment-agreements:

********************
Payment Agreements
********************

|projectName| attempts to manage all parts of the billing lifecycle in an automated fashion.
When a payment demand is generated, and an invoice issued, |projectName| refers to the current payment agreement, in order to determine how to get money from the subscriber.

A payment agreement is a reference between the subscriber and the tenant which allows the tenant to claim payments directly from the subscriber.

Different agreement types provides different capabilities and routines.

All subscribers can have a payment agreement called `None` or `InvoiceOnly`. 
This basically means there is no way to claim the amount so the system does no attempts at generating a payment.

For details on adding a custom/external payment provider integration refer to :doc:`external-provider-integration`.

Properties of a Payment Agreement
=================================
All payment agreements have a few important properties

* A `PaymentType`: What sort of payment mechanism is this: DirectDebit, Mobile App, Payment Card (VISA/Mastercard etc.), eInvoice.
* A `PaymentProviderType`: Which provider is used for the underlying payment mechanism.
* A reference for more provider specific details.

The `PaymentType` is mostly a cosmetic/informational property, especially for tenants with only a few integrations or operating countries.

The `Payment Provider Type` indicates the service provider that |projectName| uses to facilitate the given claims.
At the time of writing the following providers are currently supported:

* AvtaleGiro, DirectDebit by Mastercard Payment Services.
* Card Payments, by Swedbank Pay (formerly PayEx eCommerce).
* Vipps Recurring, Mobile Payments by Vipps.
* eFaktura, eInvoicing by Mastercard Payment Services.
* Autogiro, DirectDebit by Bankgirot.
* EHF, Norwegian version of EUs PEPPOL BIS Billing Standard.
* Email, As the name says it handles Email. Can be used to filter Invoice for e-mails but there is no built in Email sending.
* InvoiceOnly/None - the default payment type that does "nothing".

Managing Payment Agreements
============================
.. _manage-payment-agreement:

There are multiple ways to create a payment agreement for a subscriber.

* Created during the order registration.
* Created as a self-service action (initiated via a website or target email campaigns etc).
* Initiated out-of-band.

All of the approaches share the same organization/abstraction model in |projectName| and follow the same flow in terms of the integration/API.

1. A Provider Agreement is created (the details vary by provider).
2. A Payment Agreement is created pointing to the provider agreement.
3. The Payment Agreement is registered for a subscription (sometimes this happens automatically).

The idea here is that each Payment Provider, such as Vipps, SwedbankPay or AvtaleGiro, have their own percular details on how to register an agreement, and they have different terminology and different properties availble on the agreements.
To abstract away some of these details most of the time, the subscription points to a payment agreement, which in turn points to the provider.

This allows most integrations to just query for the Subscription and Payment Agreement information without worrying too much about the various providers.
When a new provider is added, no adjustments are needed to provide general information about these new agreements, only in-depth information requires additional integration.

For details on how to register new provider agreements, refer to the individual provider sections.

A request to create a new payment agreement might look like:

.. code-block:: json
    :name: Sample Payment Agreement
    
    {
        "subscriberId": "3fa85f64-5717-4562-b3fc-2c963f66afa6",
        "providerType": "AvtaleGiro",
        "providerAgreementReference": "00000000000011",
        "paymentMethod": "DirectDebit",
        "providerAgreementId": "945a996e-ac8b-4a96-96c3-deb136dc2830"
    }
    

Switching Agreements Manually
-----------------------------

Once a Payment Agreement has been created, switching to this agreement is a simple as :api-ref:`assigning it to the subscription <Subscription/post_Subscription__id__changePaymentAgreement>`.

.. Note::

    Agreement management is also built into the Self-Service client and to some degree into the Merchant client.

Out Of Band Agreements and Automatic Agreement Registration
-----------------------------------------------------------
Some payment providers are typically registered in a process not connected to the merchant, and by extension not in their systems.
At the current time of writing, this is relevant for the following providers:

* AvtaleGiro (Norway)
* eFaktura (Norway)
* Autogiro (Sweden)
* BetalingsService (Denmark)

For all of the above, the registration will happen, or may happen, in the subscribers online banking solution.

There are different details to be aware of, but in general terms the following process is enacted.

1. The Subscriber registers an agrement in his/her bank.
2. A notification is generated to the merchant.
3. |projectName| registers a `ProviderAgreement` and a `PaymentAgreement`.
4. Once the `PaymentAgreement` is generated |projectName| will attempt to automatically switch to the created agreement.

At the current time, only subscribers on InvoiceOnly/None agreements are automatically switched.
It is assumed that whatever process they entered into is preferable from their point of view untill otherwise dictated. 
At the current time there is no way for a merchant to define a preferred order of payment methods.

Importing Agreements
----------------------

Sometimes it is necessary to import payment agreements from external sources.

There are several use cases for importing agreements, but the two main scenarios are:

1. When migrating existing agreements from another billing/subscription system.
2. Integrating with ecommerce platforms that generates the agreemt during the initial sale.

Each provider integration exposes its own endpoint for importing existing agreements. 
There are some variations, so look to the provider descriptions for the details.

Common for all the scenarios is that once an agreement has been imported for the provider, it should be added as a general agreement, and handled the same way as with new orders or during self-service registrations, as :ref:`described above <manage-payment-agreement>`.

************************
Payment Providers (PSPs) 
************************

.. toctree::
    :glob:
    :maxdepth: 1
    
    providers/avtalegiro
    providers/eFaktura
    providers/vipps
    providers/swedbank
    providers/betalingsservice
    providers/autogiro
    external-provider-integration