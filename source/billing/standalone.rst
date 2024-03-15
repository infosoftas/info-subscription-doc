.. _standalone-paymentdemands:

*************************************
Transaction (Non-Recurring) Invoices
*************************************

|projectName| is designed to take care of most recurring billing needs. 
However in some cases it might be desirable to create an additional invoice that is not recurring, but still using the existing information from the subscription platform.

A few xxamples where such invoices may be beneficial:

- Single/One-off product sales using existing agreements
- Special initial transactional costs (delivery of hardware for instance)
- Finalizing a subscription lifecycle with a buyout of the subscribed product (often used with binding contracts for instance).

Such transactional invoices can be created as Account Payment Demands.

Creating an Account Payment Demand
===================================
A few input values are required to create an Account Demand.

#. Organization - The issuer of the invoice.
#. Subscriber - The receiver of the invoice.
#. Subscriber Account - The billing account where charges should be deducted.
#. BillingPlan - How should billing and subsequent dunning behave.
#. Payment Agreement - How should automatic payments be requested and processed.

Since the details of each of these items are present in the system, all that is required is to determine which ones to use, and define the correct Ids.

Consider an example where the subscriber wants to buy a coffee using his/her credit card agreement.
For simplicity we assume that some of the parameters are static.

1. Get the card agreement id

.. code-block:: http
    :name: Get Card Agreement

        GET https://api.info-subscription.com/paymentagreement?providerType=SwedbankPay&subscriberId=0c8f576a-6308-4598-a255-52080fbf5f71 HTTP/1.1
        Host: api.info-subscription.com
        S4-TenantId: 3fce3f93-97a7-4045-952d-f8af685a47cb
        Authorization: Bearer <TOKENHERE>

2. Create an account demand

.. code-block:: http
    :name: Create Account Payment Demand

        POST https://api.info-subscription.com/paymentdemand HTTP/1.1
        Host: api.info-subscription.com
        S4-TenantId: 3fce3f93-97a7-4045-952d-f8af685a47cb
        Authorization: Bearer <TOKENHERE>
        Content-Type: application/json

        {
            "type": "Account",
            "accountDemand": 
            {
                "organizationId": "3fa85f64-5717-4562-b3fc-2c963f66afa6",
                "subscriberAccountId": "ac31e29f-2675-4328-b62c-d1ac79294487",
                "subscriberId": "0c8f576a-6308-4598-a255-52080fbf5f71",
                "paymentAgreementId": "5b5b779d-ef0b-49ef-a976-9dfaafdfade0",
                "billingPlanId": "b5136018-2801-41da-9c03-62783cb03977",
                "transactions": [
                {
                    "description": "Extra Large Deluxe Coffee (Roomservice)",
                    "price": 220,
                    "currency": "USD",
                    "taxDetails": [
                    {
                        "description": "Coffee",
                        "taxPercent": 25,
                        "amount": 200
                    },
                    {
                        "description": "Roomservice Fee",
                        "taxPercent": 25,
                        "amount": 20
                    }]
                }]
            }
        }


Settling Outstanding Account Balance
------------------------------------
Depending on the scenario, the subscriber may want to settle any outstanding transactions on the account.

This is easily achievable by setting the parameter `SettleAccountBalance` to `true`


.. code-block:: json

    {
            "type": "Account",
            "accountDemand": 
            {
                // .. Properties omitted for brevity
                "SettleAccountBalance" : true,
                // .. Properties omitted for brevity
            }
    }

This will generate a new payment demand with account charges and allowances included.

Refer to the API specification to lookup details on which transactions are available on the account prior to generating the demand.