.. _order-example-override-price:


Example: Overriding Pre-Defined Prices
--------------------------------------
Typically a template plan is setup with a specific set of products.

The price is either defined directly on the template plan, or as a function of the list price on the products.

In some scenarios it is desirable to override this price when creating the order.

For instance where an extra-ordinary discount should be given to a subscriber (for whatever reason), or in cases where each subscription is negotiated by a salesperson, which is typically for high-value enterprise and B2B susbscriptions.

It is possible to override the price during the order like the following

.. code-block:: json
    :caption: Price Override

    {
        "subscriberId": "11111111-2222-3333-4444-000000000000",
        "templatePackageId": "10000000-0000-0000-0000-000000000000",
        "paymentAgreementId" : "44444444-5555-6666-7777-000000000000",
        "organizationId" : "20000000-0000-0000-0000-000000000000",
        "templatePackageChoices": 
        {
            "priceOveride": 2000,
        }
    }

.. IMPORTANT::

    It is important to note that this is only possible if the template is configured to allow price overrides!