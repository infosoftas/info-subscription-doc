.. _provider-autogiro:

Autogiro
========

Autogiro is the primary Swedish Direct Debit solution for both B2C and B2B, provided by Bankgirot. It allows recurring payments to be collected from customers' accounts with minimal customer interaction after the initial setup.

Mandate Registration
--------------------
In Autogiro terminology, an agreement is called a mandate. The following will use the term agreement and mandate interchangeably.

Autogiro traditionally provides an "out-of-band" style agreement registration.

1. The customer receives a physical invoice or notification with identifiers (Payer Number, Bankgiro Number).
2. The customer registers this in the online banking solution or through other means provided by their bank.
3. A mandate is sent to the merchant via file transfers from Bankgirot.
4. Recurring payments can be charged on the consumer's account, associated with the specific mandate.

Since all of this is "out-of-band", there is little developer integration here.

The requirement is that an account is set up for Autogiro (:api-ref:`Account endpoint<Autogiro/AutogiroCreateAccount>`) and that mandates and payments are imported using the files from Bankgirot.
|projectName| takes care of this for you, if configured during onboarding. Reach out to support to get help with this.

The rest is taken care of by |projectName| in terms of billing, claims generation etc.

Manually Registering Mandates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A mandate registration requires the following:

* A payerNumber (an identifier from Bankgirot)
* A SubscriberId
* An AccountId

The mandate is created by sending a POST request to the :api-ref:`mandate endpoint<Autogiro/AutogiroCreateMandate>`, an example request body might look like:

.. code-block:: json

    {
        "accountId" : "a28373e1-5733-4682-98f0-549cb59800f8",
        "subscriberId" : "acecdb1d-b78b-45bd-9374-4feee7edaf72",
        "payerNumber" : "1234567890",
    }

The output of such a request is a new Id for the mandate, which can then be used to register a general payment agreement as described in the section for :ref:`managing agreements <manage-payment-agreement>`.

Connected/Interactive Mandate Registration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Bankgirot provides alternative solutions to the out-of-band registration option. These include digital signing services that allow for the registration to happen in a connected/interactive manner without the need for the consumer to go to the online banking solution.

Registration can be integrated with Bankgirot's digital services, which allow customers to sign up for Autogiro agreements online.

.. Note::

    This is not automatically built into |projectName| at the time of writing. 
    Integrations requiring interactive mandate registration will need to be built by parties not relying on the |projectName| standard ordering process.
    Contact support for guidance on implementing interactive mandate registration.

Cancelling Mandates
-------------------
At any point in time, the consumer may cancel the mandate, in which case an alternate means should be used to get the payment.

|projectName| manages this scenario by:

* Disabling the mandate once a cancellation is received.
* Disabling the payment agreement and reverting to the default agreement (Invoice or Email).
* Generating reminders on Invoice since no payment is going to be received with Autogiro.

It is possible to cancel a mandate using :api-ref:`the mandate endpoint <Autogiro/AutogiroDeleteMandate>`.

At the time of writing, there are no common scenarios where this is needed, but the most likely would be some external lifecycle management of the mandates.

Creating Payments (Transactions)
---------------------------------
A Transaction is the Autogiro terminology for doing a debit/charge on the consumer's account.
Once submitted, if not cancelled by the merchant, it will lead to an account transfer on the given due date.

Transactions are automatically created and cancelled for subscriptions on an Autogiro mandate.
There should be minimal need for manually creating transactions.
Please let us know if you have specific scenarios that are not supported.

Transactions can be created directly using the API if required, using :api-ref:`the transaction endpoint <Autogiro/post_autogiro_transaction>`.

.. Caution::

    A mandate can have a maximum of one transaction per day.
    Using the subscription mandate for external charges runs the risk of conflicting with existing transactions.
    This in turn leads to unpaid invoices or other discrepancies.

    Use this feature with some caution, or make sure you have separate Mandates.