.. _requests-responses:

Building Requests
=================

In general requests are build such that a `HTTP Method/Verb <https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods>`_ corresponds to a specific type of action.

* ``GET`` Requests data from a resource
* ``POST`` Creates a resource or starts a process
* ``PUT`` Replaces/Completely Updates an existing resource
* ``DELETE`` Deletes a resource or cancels a process
* ``PATCH`` Partially updates a resource or state of a process

The APIs expect ``JSON`` as input and outputs ``JSON`` unless otherwise noted in the `reference documentation <https://api.info-subscription.com/swagger/>`_.

.. Tip::
    Even though the APIs Accept ``application/json`` as input and responds with ``application/json`` by default, it is recommended that you set the ``Accept``  and ``Content-Type`` headers
    so there is no doubt for client and server what is requested.

If for some reason you *really really* like XML, Protobuf, Thrift, MessagePack or your own custom content type, then let us know and we might consider implementing it.

Handling Responses
==================

Just as requests are build around the common HTTP Methods, the API responses are constructed around common `HTTP Status Codes <https://developer.mozilla.org/en-US/docs/Web/HTTP/Status>`_.
Each response contains a code and optionally a body. 
We strive to follow the same convention throughout the API which should hopefully provide consumers a streamlined experience. 
Let us know if you discover inconsistencies!

Successful Responses
--------------------

For succesful requests we generally map the status codes as follows:

* ``GET`` Returns ``HTTP 200 OK`` with a body.
* ``POST`` (i.e. create a new resouce) Returns ``HTTP 201 Created`` with a body of the created resource.
* ``PUT`` Returns ``HTTP 204 No Content`` with no body
* ``DELETE`` Returns ``HTTP 204 No Content`` with no body

You can consider this as a general rule, but to be certain please refer to the `reference docs <https://api.info-subscription.com/swagger/>`_ for your particular action.

Error Conditions
----------------
There are two categories of errors.

#.  Errors that the client can do something about, typically input format or unmet requirements. 
    These produces status codes in the **400-499** range.

#.  Errors that is entirely the fault of the server, typically environment errors or implementation errors or other similar unexpected conditions.
    These produces status codes in the **500-599** range.

Client Errors
~~~~~~~~~~~~~
As described above these are Errors that the client should handle, typically by displaying some sort of feedback to the user.

Typically client errors are validation/format related and generates a ``HTTP 400 Bad Request`` response with a `validation error instance <https://api.info-subscription.com/swagger/#model-ValidationResultModel>`_

Whenever possible multiple validations will be included in a single response, but since some validations are dependant on existance of a given resource this is not always achievable.

The following is an example of a ``BadRequest`` response with multiple validation failures. 

.. code-block:: http
    :caption: Headers
    :name: bad-request-example-headers

    HTTP/1.1 400 Bad Request
    Transfer-Encoding: chunked
    Content-Type: application/json; charset=utf-8
    Server: Kestrel
    Request-Context: appId=cid-v1:ae92dc8e-a862-4e47-92f2-cc707892f433
    X-Powered-By: ASP.NET
    Date: Mon, 01 Jan 2042 00:13:37 GMT

.. code-block:: json
    :caption: Body
    :name: bad-request-example-body

    {
        "message": "Validation Failed",
        "errors": [
            {
                "field": "Currency",
                "message": "The Currency field is required."
            },
            {
                "field": "ValueDate",
                "message": "Date is out of Range"
            },
            {
                "field": "PaidAmount",
                "message": "The amount is out of Range"
            },
            {
                "field": "PaymentDate",
                "message": "Date is out of Range"
            }
        ]
    }

Authentication and Authorization errors are strictly speaking also client errors, but the response and the meaning are covered in the :ref:`authentication section <requests-responses-auth>`

Server Errors
~~~~~~~~~~~~~
Generally speaking the APIs responds with either ``HTTP 500 Internal Server Error`` or ``HTTP 503 Service Unavailable``.

There might be cases where you get other ``5xx`` series status codes, but those are always from the hosting environment and thus it is a bit hard to reason about their content in all cases.

HTTP 500 Internal Server Error
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

These errors should always include a body of the following format

.. code-block:: json

    {
        "Code": "SOME HTTP StatusCode",
        "Message": "An error message of sorts",
    }


While the message itself is usually not that informative, we recommend that you log any such errors and open a :ref:`bug report <reporting-bugs>` so that we might solve the issue.

HTTP 503 Service Unavailable
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Typically waiting a few minutes and trying again should work, if not please open a :ref:`bug report <reporting-bugs>` so we can investigate.

Authentication and Authorization Responses
------------------------------------------
.. _requests-responses-auth:

There are currently two auth related responses you can expect and should handle.

* ``HTTP 401 Not Authenticated`` - Indicates that no authorization information was found, typically because there is no Authorization header or the content of the header was mal-formed.
* ``HTTP 403 Forbidden`` - Indicates the there was some authorization information, but the resource/action requests requires permissions that the authorized party does not have.

There is currently no body associated with either response, but in case of a ``HTTP 401`` code a response header ``WWW-Authenticate`` should be included.
An example `401` response:

.. code-block:: http

    HTTP/1.1 401 Unauthorized
    Server: Kestrel
    WWW-Authenticate: Bearer error="invalid_token", error_description="The token is expired"
    Request-Context: appId=cid-v1:ae92dc8e-a862-4e47-92f2-cc707892f433
    X-Powered-By: ASP.NET
    Date: Mon, 01 Jan 2042 00:13:37 GMT
    Content-Length: 0

.. Tip::
    While you are most likely to receive these types of responses during development and testing, we recommend you at least handle and log such errors so you have something to debug.