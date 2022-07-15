.. _provider-swedbank:

Swedbank Pay
=============

Swedbank Pay is a Payment Service Provider (PSP), formerly PayEx. 
Swedbank Pay provides a series of different payment services, among these are handling of credit/debit card payments.

.. Note:: 

    Throughout the API and the documentation/description of it, 
    the integration is denoted as "PayEx". PayEx was acquired by Swedbank and the solution was re-branded.
    In order to not break the API we have kept the naming as-is.

Requirements for using Swedbank Pay
-----------------------------------
In order to use Swedbank Pay as a card provider, at least one Swedbank Pay account must be configured in |projectName|.
This can be acquired either by contacting Swedbank directly, alternatively Infosoft can facilitate the onboarding process if required. 
Please :ref:`contact support <reporting-bugs>` for details.

Agreement Registration
----------------------
In Swedbank terminology an agreement is basically the same as an agreement in |projectName|.
It is an agreement between the Merchant (a |projectName| tenant) and the subscriber, that allows the Merchant to make payment transactions on the subscribers payment card.

Like most other PSP, Swedbank Pay requires an integrated interactive process for registering new agreements. 
Typically in conjunction with an order.

1. The potential subscriber selects a Subscription Plan to purchase.
2. A payment transaction is started at Swedbank.
3. The subscriber is redirected to a website to card details (Managed by Swedbank Pay).
4. The order and agreement is finalized and the initial payment associated with the order.
5. Recurring payments can be charged on the subscribers card.

Since all of this is an interactive process, some integration is required for it to be available in the order process.
|projectName| provides a turn key sales and ordering process that is capable of handling Swedbank Pay Agreements.

If the caller utilizes the ordering API provided by |projectName| some of the above is handled, but the initial parameters and the redirection needs to be managed by the client.

Agreement Registration Without Orders
-------------------------------------
For existing subscribers on a different payment agreement, or for switching to a newer payment card. 
It is possible to register agreements WITHOUT an order.

The process is very similar to registrations with an order:

1. The potential subscriber chooses to create a new agreement.
2. A payment transaction is started at Swedbank, with a special indicator that its for agreement creation purposes.
3. The subscriber is redirected to a website to card details (Managed by Swedbank Pay).
4. The agreement is finalized and the initial payment associated with the order.


Prepared Transactions
---------------------
It is possible to prepare agreement transactions and send them to potential subscribers as direct URLs to the agreement terminal.
For more info check the Swedbank website, or contact support.


Manually Registering Agreements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
It is possible to register/import agreements registered outside of |projectName|.
This is typically useful when importing accounts from other sources such as an e-commerce solution.

An agreement registration requires the following

* A Swedbank Pay Recurrence Token
* An AccountId

The agreement is created by sending a POST request to the :api-ref:`agreement endpoint<PayEx/post_payex_agreement>`, an example request body might look like:

.. code-block:: json

    {
        "accountId" : "a28373e1-5733-4682-98f0-549cb59800f8",
        "recurrenceToken" : "acecdb1d-b78b-45bd-9374-4feee7edaf72",
    }

The output of such a request is a new Id for the agreement, which can then be used to register a general payment agreement as described in the section for :ref:`managing agreements <manage-payment-agreement>`.

|projectName| will only accept the agreement if the given `recurrenceToken` is valid on the Swedbank Pay account.
Details about the card such as the `expiration` and the `cardMask` may be given during import, but they will be pulled from Swedbank directly if missing.

Creating Payments
-----------------
A payment or transaction is the Swedbank Pay terminology for doing a debit/charge on the subscribers payment card.
Once submitted, if not cancelled by the merchant, will lead to an account transfer on the given due date.

Payments are automatically created and cancelled for subscriptions on a Swedbank Pay agreement. 
There should be minimal need for manually creating payments. 
Please let us know if you have specific scenarios that is not supported.

Payments can be created directly using the API if required, using :api-ref:`the transaction endpoint <PayEx/eCommerceTransactions/post_transaction>`.
