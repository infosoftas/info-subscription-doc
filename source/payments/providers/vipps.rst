.. _provider-vipps:

Vipps Recurring And MobilePay Recurring
=======================================

Vipps and MobilePay Recurring is a product provided by |VippsMobilePay| that allows organization operating in Norway, Denmark and Finland to offer mobile/app based recurring payment, for subscribers with a valid account.
It is backed by a credit card, debit card or bank account managed by |VippsMobilePay|.

In the following the product name `Vipps Recurring` is used, but it refers to both Vipps and MobilePay.

Requirements for Vipps Recurring
--------------------------------
The requirements is that an account is setup for Vipps (:api-ref:`Account endpoint<Account/post_vipps_account>`).
Infosoft is a Vipps partner and we can facilitate the Vipps onboarding process if required, please :ref:`contact support <reporting-bugs>` for details.

Agreement Registration
----------------------
.. _agreement-registration:
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

Handling Terminal/Landing Page Cancellations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
When subscribers are redirected to the VippsMobilePay terminal or landing page to confirm an agreement, they may cancel the process or simply close the browser/app without completing the registration. Since VippsMobilePay does not provide immediate feedback in the response when this occurs, there are two primary methods for handling these cancellations:

1. **Error/Validation Handling During Complete Order**
   
   When attempting to complete an order using the :api-ref:`Complete Order endpoint <Orders/CompleteOrder>`, the system will validate the agreement status with VippsMobilePay. If the subscriber has cancelled or not completed the agreement registration, the Complete Order request will fail with an appropriate error response indicating the agreement was not approved.

   This approach is suitable when you control the order completion flow and can handle validation errors gracefully in your application.

2. **Polling the Agreement Status**
   
   You can also check the agreement status directly using the ``GET vippsmobilepay/agreement/{id}/remote`` endpoint. This endpoint retrieves the current state of the agreement directly from VippsMobilePay, allowing you to determine if the subscriber has:
   
   - Approved the agreement (``ACTIVE`` or ``PENDING`` status)
   - Rejected/cancelled the agreement (``STOPPED`` or ``EXPIRED`` status)
   - Not yet responded to the agreement request
   
   This approach is useful for scenarios where you need to check agreement status independently of order completion, such as displaying real-time status updates to users or implementing retry logic.

.. note::
   The agreement state returned by the remote endpoint is directly transferred from VippsMobilePay's upstream API. For detailed information about agreement states and status values, please refer to the official `VippsMobilePay Recurring API Documentation <https://developer.vippsmobilepay.com/docs/APIs/recurring-api/>`_.

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

The agreement is created by sending a POST request to the :api-ref:`agreement endpoint <MobilePay/CreateVippsMobilePayAgreement>`, an example request body might look like:

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

Single Payments
---------------
|VippsMobilePay| also offers a product that does not require an agreement, transactions/payments using this API are denoted `epayment`. Typically used for single purchases in retail scenarios or similar.

|projectName| offers an integration with `epayment`, that can be used for instance to pay for a single invoice, prepaying to a billing account, or any other thing you may want to use it for..

The flow for creating a new `epayment` resembles :ref:`agreement registration <agreement-registration>`, with one notable exception being the final capture.

1. The subscriber selects something to pay for.
2. An `epayment` authorization process is started with Vipps.
3. The subscriber is redirected to a website (or App) to confirm the information (Managed by Vipps).
4. The subscriber confirms the purchase in the Vipps Mobile App (Managed by Vipps).
5. A capture request is sent to Vipps once the product is shipped/delivered.

Scheduled Captures
------------------
Since Vipps Epayments acts as a two phased transaction, the client must issue a capture request when shipping goods (or delivery products or whatever).

When using an `epayment` to pay invoices a due date is known at the purchase time and a scheduled capture time can be set using :api-ref:`the epayment endpoint <MobilePay/CreatePayment>`.

If set, a capture attempt will be automatically executed around the time specified (within an hour typically).

Automatic Accounting/Settlement
-------------------------------
It is possible to have |projectName| handle settlement and accounting for an `epayment`. 

All that is required is to fill out the required `Accounting` properties when :api-ref:`creating the epayment <VippsMobilePay/CreatePayment>`.

An example request with accounting data that automagically settles an Invoice may look like:

.. code-block:: json

    {
        "accountId": "3fa85f64-5717-4562-b3fc-2c963f66afa6",
        "reference": "a28373e1-5733-4682-98f0-549cb59800f8",
        "amount": 1000, // The amount is taken from the Invoice or the Reminder payable amount.
        "currency": "NOK",
        "description": "Paying Invoice 1234",
        "returnUrl": "https://merchantstore.example.com/order/",
        "userFlow": "WEB_REDIRECT",
        "captureTime": "2024-08-12T08:20:01.261Z", // When automatic capture should kick in (can be omitted)
        "accounting": {
            "subscriberId": "3fa85f64-5717-4562-b3fc-2c963f66afa6",
            "externalInvoiceIdentifier": "10012347207834", // Indicates that we want to settle this invoice with this epayment.
        }
    }
}