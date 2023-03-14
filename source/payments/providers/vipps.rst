.. _provider-vipps:

Vipps Recurring
================

Vipps Recurring allows organization operating in Norway to offer mobile/app based recurring payment, for subscribers with a Vipps account.
It is backed by a credit card, debit card or bank account managed by Vipps.

Requirements for Vipps Recurring
--------------------------------
The requirements is that an account is setup for Vipps (:api-ref:`Account endpoint<Account/post_vipps_account>`).
Infosoft is a Vipps partner and we can facilitate the Vipps onboarding process if required, please :ref:`contact support <reporting-bugs>` for details.

Agreement Registration
----------------------
In Vipps terminology an agreement is almost like a subscription. 
It is an agreement between the Merchant (a |projectName| tenant) and the subscriber to pay for a given product, at a recurring interval.
If the subscription plan changes, the agreement should change with it.

Vipps requires an integrated interactive process for registering new agreements. Typically in conjunction with an order.

1. The potential subscriber selects a Subscription Plan to purchase.
2. A draft agreement is generated on Vipps using the subscribers mobile number.
3. The subscriber is redirected to a website to confirm the information (Managed by Vipps).
4. The subscriber confirms the purchase in the Vipps Mobile App (Managed by Vipps).
5. The order and agreement is finalized and the initial payment associated with the order.
6. Recurring payments can be charged on the subscribers account/card, associated with the specific Vipps Agreement.

Since all of this is an interactive process, some integration is required for it to be available in the order process.
|projectName| provides a turn key sales and ordering process that is capable of handling Vipps Agreements.

If the caller utilizes the ordering API provided by |projectName| some of the above is handled, but the initial parameters and the redirection needs to be managed by the client.

In-Shop/Non-Browser Agreement Registration (Merchant Initiated)
---------------------------------------------------------------
Vipps allows a special type of agreement registration where everything is managed by the merchant, and the only thing the subscriber has to do is accept the agreement in the mobile app.
This process is almost identical to the above, except the browser redirect part can be headless and without user interaction.

The purpose of this registration process is to provide "in-shop" purchases of subscriptions without requiring the buyer to interact with a browser.

This alternate registration process requires:

1. A special agreement with Vipps that allows merchant initiated agreements.
2. An extra parameter to the order process that indicates the process should be used with Vipps.

Payment Type Management
-----------------------
Since Vipps Recurring is backed by bank accounts and potentially card agreements, there is a need to manage the card agreements upon expiration.
All of this is managed by Vipps, refer to the official Vipps documentation for what this entails.

Manually Registering Agreements
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
It is possible to register/import agreements registered outside of |projectName|.

An agreement registration requires the following

* A Vipps Agreement Id
* A SubscriberId
* An AccountId

The agreement is created by sending a POST request to the :api-ref:`agreement endpoint<VippsAgreement/post_vipps_agreement>`, an example request body might look like:

.. code-block:: json

    {
        "accountId" : "a28373e1-5733-4682-98f0-549cb59800f8",
        "subscriberId" : "acecdb1d-b78b-45bd-9374-4feee7edaf72",
        "vippsAgreementId" : "agr_123456",
    }

The output of such a request is a new Id for the agreement, which can then be used to register a general payment agreement as described in the section for :ref:`managing agreements <manage-payment-agreement>`

Creating Charges
----------------
A charge is the Vipps Recurring terminology for doing a debit/charge transaction on the subscribers account.
Once submitted, if not cancelled by the merchant, will lead to an account transfer on the given due date.

Charges are automatically created and cancelled for subscriptions on a Vipps Recurring agreement. 
There should be minimal need for manually creating charges. 
Please let us know if you have specific scenarios that is not supported.

Charges can be created directly using the API if required, using :api-ref:`the charges endpoint <Charges/post_vipps_charges>`.

.. Caution:: 

    Depending on the registration process, new agreements may be created with a maximum debit amount per month. 
    Using the subscription agreement for external charges runs the risk of exceeding this amount.
    This in turn leads to rejected charges and unpaid invoices for the regular subscription.

    Use this feature with some caution if the agreement is used by a subscription.
