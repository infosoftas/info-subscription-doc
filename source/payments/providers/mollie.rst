.. _provider-mollie:

Mollie (Card, Wallets, and Mandates)
====================================

Mollie is a Payment Service Provider (PSP) that |projectName| uses primarily for card-based payments, with additional hosted-checkout support for Apple Pay, Google Pay, and SEPA Direct Debit where Mollie, the subscriber's device/browser, and the issuing bank support them.

For provider-side concepts and checkout behavior, see the official `Mollie API documentation <https://docs.mollie.com/>`_.

Requirements for using Mollie
-----------------------------

In order to use Mollie, at least one Mollie account must be configured in |projectName|. Before onboarding that account, you must already have a working agreement with Mollie and a Mollie profile.

Account onboarding is only required once per Mollie account, and it can be completed from the Merchant application.

The public API exposes the account lifecycle under ``/mollie/account``:

* ``POST /mollie/account`` creates an account record with fields such as ``name``, ``profileId``, ``refreshToken``, and ``testMode``.
* ``GET /mollie/account/{id}/connect`` starts the hosted Mollie Connect flow and returns an ``authorizationUrl`` and ``state``.
* ``POST /mollie/account/{id}/connect/token`` completes the connect flow by exchanging the returned authorization ``code``.

Please :ref:`contact support <reporting-bugs>` if you need help with onboarding or account setup.

Mandates, Payment Agreements, and Mollie Payments
-------------------------------------------------

Mollie uses slightly different terminology than |projectName|:

* A provider-side agreement is called a ``Mandate`` in Mollie.
* A provider-side transaction is called a ``Payment`` in Mollie.

To avoid confusion, this page uses *mandate* for the Mollie resource and *payment agreement* for the |projectName| abstraction described in :ref:`payment-agreements`.

Agreement Registration During Orders
------------------------------------

Mollie supports the same type of interactive hosted-checkout registration flow as Swedbank Pay. During order registration, set ``paymentMethod`` to ``Mollie`` and populate ``mollieParameters``:

.. code-block:: json

    {
      "paymentMethod": "Mollie",
      "mollieParameters": {
        "accountId": "945a996e-ac8b-4a96-96c3-deb136dc2830",
        "returnUrl": "https://yourdomain.com/order/complete",
        "cancelUrl": "https://yourdomain.com/order/cancel",
        "culture": "nl-NL"
      }
    }

The ``mollieParameters`` object is defined in the public API as:

* ``accountId`` (required) – which configured Mollie account to use.
* ``returnUrl`` (required) – where the subscriber is returned after completing the Mollie checkout.
* ``cancelUrl`` (optional) – where the subscriber is returned if the checkout is cancelled.
* ``culture`` (optional) – a Mollie-compatible culture code for the hosted checkout.

Agreement Registration Without Orders
-------------------------------------

For existing subscribers, card renewals, or self-service payment-method changes, you can start mandate registration directly with ``POST /mollie/mandate``.

The request body in the public API contains fields such as:

.. code-block:: json

    {
      "accountId": "945a996e-ac8b-4a96-96c3-deb136dc2830",
      "subscriberId": "3fa85f64-5717-4562-b3fc-2c963f66afa6",
      "methods": [
        "Card"
      ],
      "amount": 0.0,
      "currency": "EUR",
      "description": "Register subscription payment method",
      "redirectUrl": "https://yourdomain.com/payment/mollie/complete",
      "cancelUrl": "https://yourdomain.com/payment/mollie/cancel",
      "customerProfile": {
        "name": "Jane Doe",
        "email": "jane@example.com",
        "locale": "en_GB"
      }
    }

Notes on the request:

* ``methods`` uses the Swagger-defined Mollie mandate methods: ``Card``, ``Ideal``, and ``DirectDebit``.
* ``amount`` may be ``0`` or higher. The published schema notes that zero-amount first payments are only accepted by Mollie for card and direct-debit mandate setups.
* ``accounting`` may also be supplied when you need to attach invoice, payment-demand, or payment identifiers to the Mollie-side request.

The API responds with the platform mandate ID and the hosted checkout URL:

.. code-block:: json

    {
      "mandateId": "6fd12fb4-fb29-4713-a248-a63f4909627e",
      "checkoutUrl": "https://www.mollie.com/checkout/select/abcdef",
      "initialPaymentId": "d2c649a7-76d3-47da-b548-b279efcfd4f4"
    }

After the subscriber completes checkout, confirm the registration with ``POST /mollie/mandate/{id}/complete`` and retrieve the stored mandate details with ``GET /mollie/mandate/{id}``.

The public API also exposes ``GET /mollie/mandate/{id}/remote`` when you need the live Mollie-side state, including fields such as ``status``, ``method``, ``cardLabel``, ``cardLastFour``, ``consumerName``, and ``consumerAccount``.

Recurring / Mandate Payments
----------------------------

Once the mandate is active, recurring charges are created with ``POST /mollie/mandate/{id}/payment``.

The request body contains:

.. code-block:: json

    {
      "mandateId": "6fd12fb4-fb29-4713-a248-a63f4909627e",
      "accountId": "945a996e-ac8b-4a96-96c3-deb136dc2830",
      "subscriberId": "3fa85f64-5717-4562-b3fc-2c963f66afa6",
      "amount": 149.0,
      "currency": "EUR",
      "description": "Subscription renewal INV-100245",
      "paymentId": "25c4d62e-c284-46eb-9f8f-a6e215b094b1"
    }

The response contains both the |projectName| payment identifier and the Mollie payment identifier:

.. code-block:: json

    {
      "paymentId": "25c4d62e-c284-46eb-9f8f-a6e215b094b1",
      "molliePaymentId": "tr_7UhSN1zuXS"
    }

In Mollie terminology this creates a *payment*. In |projectName| terms it is the provider-side transaction created for the existing payment agreement / mandate.

One-off Payments
----------------

Mollie can also be used for one-off hosted-checkout payments through ``POST /mollie/payment``.

The published request body supports fields such as ``accountId``, ``amount``, ``currency``, ``description``, ``redirectUrl``, ``cancelUrl``, ``methods``, ``captureMode``, and ``accounting``. The response returns the platform payment ``id`` together with a Mollie ``checkoutUrl`` for redirecting the subscriber.

The public API also exposes:

* ``GET /mollie/payment/{id}`` for the stored payment record in |projectName|.
* ``GET /mollie/payment/{id}/remote`` for the live Mollie-side state.
* ``POST /mollie/payment/{id}/cancel`` to cancel a payment.
* ``POST /mollie/payment/{id}/refund`` to refund a full or partial amount.
* ``POST /mollie/payment/{id}/capture`` for capture scenarios when the payment was created with manual capture.

Feature Notes
-------------

* Card is the primary recurring-payment method in this integration.
* Apple Pay and Google Pay are exposed indirectly through Mollie's hosted checkout rather than as separate |projectName| API resources.
* SEPA Direct Debit is exposed through the same Mollie integration and can be used when the subscriber and market support it.
