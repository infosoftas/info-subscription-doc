.. _order-example-products-on-plan:

Example: Choosing Products On A Plan
====================================

For organizations with many products to sell, it is often required to have the option to construct any product combination the subscriber desires.
Consider an traditional cable TV provider, many of them offer extra channels, and even serves as an Internet Service Provider.

Instead of creating every combination of product selects as template plans, it is possible to provide one or two template plans that allows choosing between products.
Continuing the example of a TV/ISP company, they may have the following products

* Basic TV ``00000000-0000-0000-0000-000000000001``
* Premium TV ``00000000-0000-0000-0000-000000000002``
* Sports Channel ``00000000-0000-0000-0000-000000000003``
* Movie Channel ``00000000-0000-0000-0000-000000000004``
* Random Channel ``00000000-0000-0000-0000-000000000005``
* Slow Internet ``00000000-0000-0000-0000-000000000006``
* Fast Internet ``00000000-0000-0000-0000-000000000007``
* Ultra Internet ``00000000-0000-0000-0000-000000000008``

An example template would look something like the following:

.. code-block:: http
    :caption: Template Plan/Package Headers
    

    POST /Order/ HTTP/1.1
    Host: https://api.info-subscription.com
    Content-Type: application/json
    S4-TenantId: SOMETENTANT
    Authorization: Bearer RANDOMTOKEN

.. code-block:: javascript
    :caption: Template Plan/Package Body

    {
        "id": "10000000-0000-0000-0000-000000000000",
        "products": [
            {
                "productId": "00000000-0000-0000-0000-000000000001",
                "fullPrice": 1000,
                "taxPercent": 25
            },
            {
                "productId": "00000000-0000-0000-0000-000000000002",
                "fullPrice": 2000,
                "taxPercent": 25
            },
            /* Omitted for brevity  */
            {
                "productId": "00000000-0000-0000-0000-000000000008",
                "fullPrice": 8000,
                "taxPercent": 25
            }
        ],
        "name": "TV and Internet",
        "description": "Internet and TV For All Yo!"
        /* Rest omitted for brevity */
    }

If one were to subscribe to the above *TV and Internet* package, with no choices, it would contain 8 Products.

However, using choices, it is possible to construct and order for *Basic TV* and *Slow Internet* like the following

.. code-block:: json
    :caption: Order of Basic TV and Slow Internet using choices

    {
        "subscriberId": "11111111-2222-3333-4444-000000000000",
        "templatePackageId": "10000000-0000-0000-0000-000000000000",
        "paymentAgreementId" : "44444444-5555-6666-7777-000000000000",
        "organizationId" : "20000000-0000-0000-0000-000000000000",
        "templatePackageChoices": 
        {
            "products": ["00000000-0000-0000-0000-000000000001", "00000000-0000-0000-0000-000000000006"],
        }
    }
