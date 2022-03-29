.. _provider-avtalegiro:

AvtaleGiro
===========

AvtaleGiro is the local Norwegian Direct Debit solution for consumers, provided by Mastercard Payment Services (MPS), formerly NETS.

Mandate Registration
--------------------
In AvtaleGiro terminology an agreement is called a mandate. The following will use the term agreement and mandate interchangeably.

AvtaleGiro traditionally provides an "out-of-band" style agreement registration. 

1. The customer receives a physical invoice with a customer identifier (KID).
2. The customer registers this in the online banking solution (or some other means as described by MPS https://www.mastercardpaymentservices.com/norway\_/Pages/Dev/paymentmandates.aspx)
3. A mandate is sent to the merchant.
4. Recurring payments can be charged on the consumers account, associated with the specific mandate.

Since all of this is "out-of-band", there is little developer integration here.

The requirements is that an account is setup for AvtaleGiro (:api-ref:`Account endpoint<Account/post_avtalegiro_account>`) and that mandates are imported using the OCR Payment file from MasterCard payment services. 
|projectName| takes care of the rest.

Manually Registering Mandates
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
A mandate registration requeres the following

* A KID (an identifier)
* A SubscriberId
* An AccountId

The mandate is created by sending a POST request to the :api-ref:`mandate endpoint<Mandate/post_avtalegiro_mandate>`, an example request body might look like:

.. code-block:: json

    {
        "accountId" : "a28373e1-5733-4682-98f0-549cb59800f8",
        "subscriberId" : "acecdb1d-b78b-45bd-9374-4feee7edaf72",
        "kid" : "00000000000011",
        "notificationDisabled" : true
    }

The output of such a request is a new Id for the mandate, which can then be used to register a general payment agreement as described in the section for :ref:`managing agreements <manage-payment-agreement>`


Connected/Interactive Mandate Registration
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Mastercard Paymentservices provides an alternative solution to the out of band registration option, the branded name for this is Mastercard Payment Services' E-Agreement service.
Basically its a website that allows for the registration to happen in a connected/interactive manner without the need for the consumer to go to the online banking solution.

The process for such a registration is

1. Create/Get the Subscriber. The Subscriber Number is required.
2. Get the AvtaleGiro bank account number using the account endpoint :api-ref:`Account endpoint<Account/get_avtalegiro_account>`.
3. Calculate the KID using the External Identifier calculation endpoint.
4. POST the required information to the eAgreement service (refer to MPS Develop docs for the details - https://www.mastercardpaymentservices.com/norway/utvikler/pvugetstarted).
5. If an OK response is received from MPS the Mandate can be imported with the defined KID.
6. Create a general payment agreement with the mandate.
7. *(Optional)* Order a subscription with the agreement created in the previous step.

.. Note::

    This is NOT built into |projectName| at the time of writing, but we are looking into adding it as an option to our self-service and ordering process.
    This will need to be built by all parties not relying on the |projectName| ordering process and self-service solutions regardless.

Cancelling Mandates
-------------------
At any point in time, the consumer may cancel the mandate, in which case an alternate means should be used to get the payment.

|projectName| manages this scenario by:

* Disabling the mandate once a cancellation is received.
* Disabling the payment agreement and reverting to the default agreement (Invoice).
* Generating reminders on Invoice since no payment are going to be received with AvtaleGiro.

It is possible to cancel a mandate using :api-ref:`the mandate endpoint <Mandate/delete_avtalegiro_mandate__id_>`. 

At the time of writing, there are no common scenarios where this is needed, but the most likely would be some external lifecycle management of the mandates.

Creating Claims
----------------
A Claim is the AvtaleGiro terminology for doing a debit/charge on the consumers account.
Once submitted, if not cancelled by the merchant, will lead to an account transfer on the given due date.

Claims are automatically created and cancelled for subscriptions on an AvtaleGiro mandate. 
There should be minimal need for manually creating claims. 
Please let us know if you have specific scenarios that is not supported.

Claims can be created directly using the API if required, using :api-ref:`the claims endpoint <Claim/post_avtalegiro_claim>`.

.. Caution:: 

    All mandates are created with a maximum debit amount per month. 
    Using the subscription mandate for external charges runs the risk of exceeding this amount.
    This in turn leads to rejected claims and unpaid invoices.

    Use this feature with some caution.
