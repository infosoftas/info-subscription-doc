.. _provider-betalingsservice:

BetalingsService
================

BetalingsService is the primary Danish Direct Debit solution for consumers, provided by the Danish banks and driven by Mastercard Payment Services (MPS), formerly NETS.

Mandate Registration
--------------------
In BetalingsService terminology, an agreement is called a mandate. The following will use the term agreement and mandate interchangeably.

BetalingsService traditionally provides an "out-of-band" style agreement registration.

1. |projectName| generates a Debtor Number for each subscriber and sends a physical invoice with identifiers (Debtor Number, Creditor Number, Creditor Group Number). The Creditor Number and Creditor Group Number are configured in the BetalingsService account within |projectName|.
2. The customer registers this in the online banking solution (or some other means as described by MPS https://www.betalingsservice.dk)
3. A mandate file is sent by MPS to |projectName| via SFTP, where it is automatically processed.
4. Recurring payments can be charged on the consumer's account, associated with the specific mandate.

The following sequence diagram illustrates the mandate registration and first claim processing flow:

.. mermaid:: betalingsservice-mandate-flow.mmd
    :align: center
    :alt: BetalingsService Mandate Registration and First Claim Flow

Since all of this is "out-of-band", there is little developer integration here.

The requirement is that an account is set up for BetalingsService (:api-ref:`Account endpoint<BetalingsService/BetalingsServiceCreateAccount>`) and that mandates and payments are imported using the files from MPS. 
|projectName| takes care of this for you, if configured during onboarding. Reach out to support to get help with this.

The rest is taken care of by |projectName| in terms of billing, claims generation etc.

Manually Registering Mandates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A mandate registration requires the following:

* A mandateNumber (an identifier from MPS)
* A SubscriberId
* An AccountId
* A SubscriberNumber

The mandate is created by sending a POST request to the :api-ref:`mandate endpoint<BetalingsService/BetalingsServiceCreateMandate>`, an example request body might look like:

.. code-block:: json

    {
        "accountId" : "a28373e1-5733-4682-98f0-549cb59800f8",
        "subscriberId" : "acecdb1d-b78b-45bd-9374-4feee7edaf72",
        "mandateNumber" : "123451",
        "subscriberNumber" : "2255412586",
    }

The output of such a request is a new Id for the mandate, which can then be used to register a general payment agreement as described in the section for :ref:`managing agreements <manage-payment-agreement>`.

Connected/Interactive Mandate Registration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MPS provides an alternative solution to the out-of-band registration option, the branded name for this is MPS' E-Agreement service.
Basically, it's a website that allows for the registration to happen in a connected/interactive manner without the need for the consumer to go to the online banking solution.

Registration goes via BetalingService "Tilmeldingslink", which is documented here: https://www.betalingsservice.dk/erhverv/l%C3%B8sninger/bs-tilmeldingslink
Alternatively via file transfers, which is not currently included with |projectName|.

Cancelling Mandates
-------------------
At any point in time, the consumer may cancel the mandate, in which case an alternate means should be used to get the payment.

|projectName| manages this scenario by:

* Disabling the mandate once a cancellation is received.
* Disabling the payment agreement and reverting to the default agreement (Invoice or Email).
* Generating reminders on Invoice since no payment is going to be received with BetalingsService.

It is possible to cancel a mandate using :api-ref:`the mandate endpoint <BetalingsService/BetalingsServiceDeleteMandate>`.

At the time of writing, there are no common scenarios where this is needed, but the most likely would be some external lifecycle management of the mandates.

Creating Payments (Transactions)
---------------
A Transaction is the BetalingsService terminology for doing a debit/charge on the consumer's account.
Once submitted, if not cancelled by the merchant, will lead to an account transfer on the given due date.

Transactions are automatically created and cancelled for subscriptions on a BetalingsService mandate. 
There should be minimal need for manually creating transactions. 
Please let us know if you have specific scenarios that are not supported.

Transactions can be created directly using the API if required, using :api-ref:`the transaction endpoint <BetalingsService/post_betalingsservice_transaction>`.

.. Caution:: 

    A mandate can have a maximum of one transaction per day. 
    Using the subscription mandate for external charges runs the risk of conflicting with existing transactions.
    This in turn leads to unpaid invoices or other discrepancies.

    Use this feature with some caution, or make sure you have separate Mandates.
