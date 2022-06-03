.. _order-examples:

Order Examples
==============

The following contains a few common scenarios/examples for the ordering process.
Unless otherwise stated, each of them presents the body for creating a new order using an order request like the following.

.. code-block:: http
    :caption: Create a new order
    :name: create-new-order

    POST /Order/ HTTP/1.1
    Host: https://api.info-subscription.com
    Content-Type: application/json
    S4-TenantId: SOMETENTANT
    Authorization: Bearer RANDOMTOKEN
    Content-Length: 10
    

Each example typically only shows properties relevant to the example and omits required elements for brevity.

It is possible to combine many of the examples, though not necessarily all of them.


.. include:: choosing-products.rst

.. include:: override-price.rst