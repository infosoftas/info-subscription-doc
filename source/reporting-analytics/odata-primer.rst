Querying with OData on INFO-Subscription
========================================

This section introduces OData querying for the Info Subscription Analytics API. 
It is intended for developers who want to efficiently retrieve data from the OData-compliant endpoint at https://analytics.info-subscription.com in a read-only fashion.

Use Cases for the Analytics OData API
-------------------------------------
The Analytics OData API is a powerful tool for accessing and analyzing your subscription and reporting data. Some common use cases include:

- Building custom dashboards and reports tailored to your business needs
- Integrating analytics data into your own BI tools (such as Power BI, Tableau, or Excel)
- Automating data extraction for scheduled reporting or data warehousing
- Enabling advanced filtering, aggregation, and exploration of your subscription data

.. note::
    The dashboards provided in the merchant UI are themselves built on top of this API. This means you have access to the same rich data and capabilities as the built-in analytics tools, allowing you to extend or customize your analytics experience as needed.

What is OData?
--------------
OData (Open Data Protocol) is a standardized REST API protocol for querying and updating data. OData services expose their data in a discoverable way, allowing you to explore available entities and properties via metadata.

.. important:: 
    
    Understanding the underlying data model will help you write more effective OData queries and interpret the results returned by the API.
    The Analytics OData API provides access to data that is structured according to the reporting and analytics data model.
    Refer to :doc:`reporting-analytics/intro` for more information.

Exploring the API
-----------------
The Info Subscription Analytics API is OData-compliant. You can discover available entities, properties, and relationships by accessing the metadata document::

    https://analytics.info-subscription.com/$metadata

This document describes the structure of the data and is useful for understanding what you can query.

Basic OData Query Structure
---------------------------
OData queries are simple HTTP requests. For example, to list all subscribers::

    GET https://analytics.info-subscription.com/Subscribers

Filtering Results
-----------------
Use the ``$filter`` parameter to restrict results. For example, to find subscribers in Sweden::

    GET https://analytics.info-subscription.com/Subscribers?$filter=Country eq 'Sweden'

You can combine filters::

    GET https://analytics.info-subscription.com/Subscribers?$filter=Country eq 'Sweden' and City eq 'Stockholm'

Sorting Results
---------------
Use the ``$orderby`` parameter to sort::

    GET https://analytics.info-subscription.com/Subscribers?$orderby=Name asc

Paging Results
--------------
Use ``$top`` and ``$skip`` for paging::

    GET https://analytics.info-subscription.com/Subscribers?$top=10&$skip=10

Selecting Fields
----------------
Use ``$select`` to return only specific fields::

    GET https://analytics.info-subscription.com/Subscribers?$select=Name,Email,Country


Expanding Navigation Properties
-------------------------------
If the metadata defines navigation properties (e.g., related entities), use ``$expand``. For example::

    GET https://analytics.info-subscription.com/Payment?$expand=Subscriber


Discovering Entities and Properties
------------------------------------
The actual entity and property names available for querying can be found by inspecting the OData $metadata endpoint:

    https://analytics.info-subscription.com/$metadata

This XML document describes all available entities, properties, and relationships. Use it to inform your queries and to discover new data you can access.


Example: Combined Query
-----------------------
A query to get the first 5 Swedish subscribers in Stockholm, showing only their name and email, sorted by name::


    GET https://analytics.info-subscription.com/Subscribers?
        $filter=Country eq 'Sweden' and City eq 'Stockholm'&
        $select=Name,Email&
        $orderby=Name asc&
        $top=5


Authentication
--------------
All requests to the Analytics OData API require authentication using an ``access token``, following the same mechanisms as the main API. 
You must obtain an access token as described in :doc:`general/auth` and include it in the ``Authorization`` header as a Bearer token.

In addition, every request must include the ``S4-TenantId`` header, just like with the regular API. For example:

.. code-block:: http

    GET /Subscribers HTTP/1.1
    Host: analytics.info-subscription.com
    Authorization: Bearer <your-access-token>
    S4-TenantId: <your-tenant-id>

For detailed instructions on obtaining tokens, supported grant types, and example requests, see :doc:`general/auth`.

Supported Query Operations
--------------------------
The Analytics OData API is **read-only**. You can use the following standard OData query operations:

- Filter data (``$filter``)
- Sort results (``$orderby``)
- Select specific fields (``$select``)
- Page through large result sets (``$top``, ``$skip``)
- Expand related entities (``$expand``)
- Retrieve metadata about available entities and properties (``$metadata``)

Creating, updating, or deleting data is not supported through this API.

Tips
----

- Always consult the OData metadata for available entities and properties (see the $metadata endpoint).
- Use tools like Postman or curl to experiment with queries.
- OData supports more advanced features like functions, batch requests, and more. See the OData documentation for details.

References
----------
- OData Protocol: https://www.odata.org/documentation/
- OData Metadata: https://analytics.info-subscription.com/$metadata
- API Endpoint: https://analytics.info-subscription.com
