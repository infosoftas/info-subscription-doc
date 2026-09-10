.. _payment-methods-overview:

***********************
Payment Methods
***********************

*Nordic payment methods for recurring businesses.*

|projectName| supports recurring payments and invoicing with support for nordic payment methods through a range of integrations with Payment Providers.
Infosoft has partnered with multiple different service providers to bring you the best possible results for your recurring payments.

.. list-table::
   :header-rows: 1
   :widths: 18 8 8 8 8 8 10 9 17

   * - Payment method
     - Norway 🇳🇴
     - Sweden 🇸🇪
     - Denmark 🇩🇰
     - Finland 🇫🇮
     - Europe 🇪🇺
     - Recurring
     - One-off
     - Provider
   * - :ref:`Vipps <provider-vipps>`
     - ✅
     - —
     - —
     - ✅
     - —
     - ✅
     - ✅
     - |VippsMobilePay|
   * - :ref:`MobilePay <provider-vipps>`
     - —
     - —
     - ✅
     - ✅
     - —
     - ✅
     - ✅
     - |VippsMobilePay|
   * - :ref:`Card <provider-swedbank>`
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - |SwedbankPay| / |Mollie|
   * - :ref:`AvtaleGiro <provider-avtalegiro>`
     - ✅
     - —
     - —
     - —
     - —
     - ✅
     - —
     - Mastercard Payment Services
   * - :ref:`Autogiro <provider-autogiro>`
     - —
     - ✅
     - —
     - —
     - —
     - ✅
     - —
     - Bankgirot
   * - :ref:`BetalingsService <provider-betalingsservice>`
     - —
     - —
     - ✅
     - —
     - —
     - ✅
     - —
     - Mastercard Payment Services
   * - :ref:`eFaktura <provider-efaktura>`
     - ✅
     - —
     - —
     - —
     - —
     - ✅
     - ✅
     - Mastercard Payment Services
   * - Google Pay
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - |Mollie|
   * - Apple Pay
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - |Mollie|
   * - SEPA Direct
     - —
     - —
     - —
     - ✅
     - ✅
     - ✅
     - —
     - |Mollie|
   * - :ref:`EHF (PEPPOL) <provider-peppol>`
     - ✅
     - —
     - —
     - —
     - —
     - ✅
     - ✅
     - Native
   * - :ref:`OIO/EAN (PEPPOL) <provider-peppol>`
     - —
     - —
     - ✅
     - —
     - —
     - ✅
     - ✅
     - Native
   * - :ref:`PEPPOL Sweden <provider-peppol>`
     - —
     - ✅
     - —
     - —
     - —
     - ✅
     - ✅
     - Native
   * - Invoice
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - Native
   * - Email
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - ✅
     - Native
   * - :ref:`BYO <external_payment_provider_integration>`
     - —
     - —
     - —
     - —
     - —
     - —
     - —
     - Bring your own

✅ indicates the method is available in that country/region, or supports that capability. — means it isn't.
*Europe* covers the wider set of European countries reachable through the card and wallet rails, beyond the four Nordic countries broken out individually.
*Recurring* means the method can be charged automatically on a schedule without subscriber interaction; *One-off* means it also supports collecting a single payment outside of a running agreement.

As a rule of thumb:

* Use :ref:`Vipps <provider-vipps>` or :ref:`MobilePay <provider-vipps>` for mobile-first consumer checkouts in Norway, Denmark, and Finland.
* Use :ref:`Card <provider-swedbank>` for the widest country coverage, spanning the Nordics and most of Europe, with both recurring and one-off charges; Google Pay, Apple Pay, and SEPA Direct extend the same |Mollie| coverage, subject to the subscriber's device, browser, or bank support.
* Use :ref:`AvtaleGiro <provider-avtalegiro>`, :ref:`Autogiro <provider-autogiro>`, or :ref:`BetalingsService <provider-betalingsservice>` for bank-mandated direct debit in Norway, Sweden, and Denmark respectively.
* Use :ref:`eFaktura <provider-efaktura>` or :ref:`EHF/OIO (PEPPOL) <provider-peppol>` for consumer or business eInvoicing where a direct charge isn't possible or desired.
* Use plain Invoice or Email when no automated collection is needed, or as the default fallback until a subscriber sets up another method.
* Use :ref:`BYO <external_payment_provider_integration>` to plug in a payment provider that |projectName| doesn't natively support.

Your subscription logic doesn't need to be rebuilt for every payment method: all our integrations support recurring subscription payments/invoicing, and some of them can also be used for one-off purchases without a running agreement.

All of this happens through the use of payment agreements, which serve as an abstraction.
|projectName| manages the integrations so you don't have to.

.. _payment-agreements:

Payment Agreements
===================

|projectName| attempts to manage all parts of the billing lifecycle in an automated fashion.
When a payment demand is generated, and an invoice issued, |projectName| refers to the current payment agreement, in order to determine how to get money from the subscriber.

A payment agreement is a reference between the subscriber and the tenant which allows the tenant to claim payments directly from the subscriber.

Different agreement types provide different capabilities and routines.

All subscribers can have a payment agreement called `Invoice`. 
This basically means there is no way to claim the amount so the system does no attempts at generating a payment.

Concretely, this affects one stage of the :ref:`billing cycle <billing-cycle>`: with an `Invoice` agreement, no payment request is scheduled after the invoice is issued, so the invoice moves straight to *Wait For Payment*. From there it follows the normal invoice-based flow — the subscriber pays manually, and if they don't, the usual reminder/dunning process applies exactly as it would for any unpaid invoice. `Invoice` (along with `Email`) is also the fallback agreement subscribers revert to when no other payment method is active.

Properties of a Payment Agreement
=================================
All payment agreements have a few important properties

* A `PaymentType`: What sort of payment mechanism is this: DirectDebit, Mobile App, Payment Card (VISA/Mastercard etc.), eInvoice.
* A `PaymentProviderType`: Which provider is used for the underlying payment mechanism.
* A reference for more provider specific details.

The `PaymentType` is mostly a cosmetic/informational property, especially for tenants with only a few integrations or operating countries.

The `Payment Provider Type` indicates the service provider that |projectName| uses to facilitate the given claims.
See the :ref:`payment methods overview <payment-methods-overview>` above for the currently supported providers, including country coverage and recurring/one-off support.

For details on adding a custom/external payment provider integration refer to :doc:`external-provider-integration`.

Managing Payment Agreements
============================
.. _manage-payment-agreement:

There are multiple ways to create a payment agreement for a subscriber.

* Created during the order registration.
* Created as a self-service action (initiated via a website or target email campaigns etc).
* Initiated out-of-band.

Choosing the Right Flow
------------------------

.. list-table::
   :header-rows: 1
   :widths: 30 70

   * - Scenario
     - Use this flow
   * - A new subscriber is signing up and choosing a payment method as part of checkout
     - Create during checkout via :ref:`order registration <subscription-orders>` — pass ``paymentAgreementParameters`` with the order
   * - An existing subscriber wants to add or change their payment method themselves
     - A self-service action, via the managed :ref:`self-service client <auth-quick-start>` or your own site calling the API directly
   * - The provider registers the agreement in the subscriber's online bank, outside of your control
     - `Out of Band Agreements and Automatic Agreement Registration`_ (below) — applies to AvtaleGiro, eFaktura, Autogiro, and BetalingsService
   * - You already have agreements in another billing system or an ecommerce platform
     - `Importing Agreements`_ (below)
   * - You need a provider |projectName| doesn't natively support
     - Use a custom PSP integration: :doc:`Bring your own PSP <external-provider-integration>`

All of the approaches share the same organization/abstraction model in |projectName| and follow the same flow in terms of the integration/API.

1. A Provider Agreement is created (the details vary by provider).
2. A Payment Agreement is created pointing to the provider agreement.
3. The Payment Agreement is registered for a subscription (sometimes this happens automatically).

The idea here is that each Payment Provider, such as :ref:`Vipps <provider-vipps>`, :ref:`SwedbankPay <provider-swedbank>` or :ref:`AvtaleGiro <provider-avtalegiro>`, have their own peculiar details on how to register an agreement, and they have different terminology and different properties available on the agreements.
To abstract away some of these details most of the time, the subscription points to a payment agreement, which in turn points to the provider.

This allows most integrations to just query for the Subscription and Payment Agreement information without worrying too much about the various providers.
When a new provider is added, no adjustments are needed to provide general information about these new agreements, only in-depth information requires additional integration.

For details on how to register new provider agreements, refer to the individual provider sections.

A request to create a new payment agreement, sent to the :api-ref:`Payment Agreement endpoint <PaymentAgreement>`, might look like:

.. code-block:: json
    :name: Sample Payment Agreement
    
    {
        "subscriberId": "3fa85f64-5717-4562-b3fc-2c963f66afa6",
        "providerType": "AvtaleGiro",
        "providerAgreementReference": "00000000000011",
        "paymentMethod": "DirectDebit",
        "providerAgreementId": "945a996e-ac8b-4a96-96c3-deb136dc2830"
    }

* ``subscriberId`` – the subscriber the agreement belongs to.
* ``providerType`` – which :ref:`provider <payment-methods-overview>` handles the agreement, for example ``AvtaleGiro``, ``Vipps``, or ``EHF``.
* ``providerAgreementReference`` and ``providerAgreementId`` – identifiers for the underlying provider agreement; which of the two is required, and their exact format, varies by provider, so check the individual provider section for the fields it expects.
* ``paymentMethod`` – the informational `PaymentType` described above (DirectDebit, Mobile App, Payment Card, eInvoice, etc.); it doesn't affect how the agreement is processed.

The API returns the created agreement record; use its identifier in the next step, registering the agreement for the subscription, as described in `Switching Agreements Manually`_ below.

Switching Agreements Manually
-----------------------------

Once a Payment Agreement has been created, switching to this agreement is a simple as :api-ref:`assigning it to the subscription <Subscription/post_Subscription__id__changePaymentAgreement>`.

.. Note::

    Agreement management is also built into the Self-Service client and to some degree into the Merchant client.

Out Of Band Agreements and Automatic Agreement Registration
-----------------------------------------------------------
Some payment providers are typically registered in a process not connected to the merchant, and by extension not in their systems.
At the current time of writing, this is relevant for the following providers:

* :ref:`AvtaleGiro <provider-avtalegiro>` (Norway)
* :ref:`eFaktura <provider-efaktura>` (Norway)
* :ref:`Autogiro <provider-autogiro>` (Sweden)
* :ref:`BetalingsService <provider-betalingsservice>` (Denmark)

For all of the above, the registration will happen, or may happen, in the subscribers online banking solution.

There are different details to be aware of, but in general terms the following process is enacted.

1. The Subscriber registers an agreement in his/her bank.
2. A notification is generated to the merchant.
3. |projectName| registers a `ProviderAgreement` and a `PaymentAgreement`.
4. Once the `PaymentAgreement` is generated |projectName| will attempt to automatically switch to the created agreement.

At the current time, only subscribers with the `Invoice` payment agreement are automatically switched.
It is assumed that whatever process they entered into is preferable from their point of view until otherwise dictated. 
At the current time there is no way for a merchant to define a preferred order of payment methods.

Importing Agreements
----------------------

Sometimes it is necessary to import payment agreements from external sources.

There are several use cases for importing agreements, but the two main scenarios are:

1. When migrating existing agreements from another billing/subscription system.
2. Integrating with ecommerce platforms that generate the agreement during the initial sale.

Each provider integration exposes its own endpoint for importing existing agreements. 
There are some variations, so look to the provider descriptions for the details.

Common for all the scenarios is that once an agreement has been imported for the provider, it should be added as a general agreement, and handled the same way as with new orders or during self-service registrations, as :ref:`described above <manage-payment-agreement>`.

************************
Payment Providers (PSPs) 
************************

* :doc:`AvtaleGiro <providers/avtalegiro>` – Norwegian Direct Debit via Mastercard Payment Services (formerly NETS).
* :doc:`eFaktura <providers/eFaktura>` – Norwegian consumer eInvoicing delivered directly in online banking.
* :doc:`PEPPOL BIS Billing (EHF/OIO) <providers/peppol>` – business-to-business/government eInvoicing for Norway, Denmark, and Sweden.
* :doc:`Vipps / MobilePay Recurring <providers/vipps>` – mobile app-based recurring payments for Norway, Denmark, and Finland.
* :doc:`Swedbank Pay (Card Payments) <providers/swedbank>` – credit/debit card processing via Swedbank Pay.
* :doc:`Autogiro <providers/autogiro>` – Swedish Direct Debit via Bankgirot.
* :doc:`BetalingsService <providers/betalingsservice>` – Danish Direct Debit via Mastercard Payment Services.
* :doc:`Bring Your Own PSP <external-provider-integration>` – integrate a payment provider |projectName| doesn't natively support, using the public API and webhooks.

.. toctree::
    :glob:
    :maxdepth: 1
    :hidden:
    
    providers/avtalegiro
    providers/eFaktura
    providers/peppol
    providers/vipps
    providers/swedbank
    providers/autogiro
    providers/betalingsservice
    external-provider-integration