.. _auth-quick-start:

****************************************************
Authentication and Authorization Quick Start
****************************************************

For many subscription services, it is a requirement that subscribers can sign-in and access their subscription. 
Either to consume it or to manage it, and often both.

|projectName| provides optional, built-in, components to solve common authentication and authorization needs.
The components are built such that they can be used with any identity provider (IdP), but with a specific common authorization means.
For advanced authorization scenarios where multiple systems contribute to the authorization flow, the components may be used partially or skipped altogether depending on the requirements.

The following is a quick-start to help get you started if all you require is a simple option to authenticate and authorize subscribers to access one or more specific products.

The default subscriber authentication and authorization component is built around Microsoft Azure ADB2C (henceforth just |ADB2C|). 
Its a long winded name, but it is basically just an Identity Provider for consumer/customer accounts, in this case |projectName| subscribers.

|ADB2C| is an Identiy Provider (IdP) and out of the box provides Authentication using OAuth2 and Open Id Connect (OIDC).
As part of the authentication flow |projectName| extends the identity with a set of attributes that may be used to Authorize the user for accessing a given product.

Since |ADB2C| uses OIDC protocol it is likely that the stack you are using has a component or library that can help you along.

The `official ADB2C documentation contains a guide <https://docs.microsoft.com/en-us/azure/active-directory-b2c/openid-connect>`_ on how to send authenticatation requests.

The guide will refer to variables to replace such as `tenant`, `appId`, `policy` and more.
Refer to the table below on how to obtain all of this information, when you don't have access to the desired information. 

.. table:: ADB2C Reference variables

    =============      =====
    tenant             Obtained when signing up an application. Typically the |projectName| tenant name appended with `S4Prod` (Example: `experimentationS4prod`)
    policy             Defaults to `B2C_1_SignIn`
    client_id          Obtained when signing up an application
    client_secret      Obtained when signing up an application
    redirect_uri       Configured when signing up an application, this is your application URL provided when you signed up the application.
    =============      =====

There are quite a few parameters in the table for the `auhtorize` endpoint, most of which is something you need to consider if hand building the request.
If you are using a component or library a lot of this is probably taken care of out of the box.

Example Authorization Code Flow
===============================
The following are exsamples of an authorization code flow, to get you started, but we recommend learning about Open Id Connect and specifically |ADB2C| to get the most out of your authentication and authorization process.

.. note:: 

    If you have a test account on the Experimentation tenant, the following should be reproducable using just your browser.

Obtaining the authorization code and id token
---------------------------------------------

.. code-block:: http

    GET https://experimentationS4prod.b2clogin.com/experimentationS4prod.onmicrosoft.com/b2c_1_signin/oauth2/v2.0/authorize?client_id=1b162230-180c-4648-9d0f-a313bb86510c&response_type=code+id_token&redirect_uri=https%3A%2F%2Fjwt.ms%2F&scope=openid%20offline_access&response_mode=fragment HTTP/1.1
    Host: experimentationS4prod.b2clogin.com
    Connection: keep-alive
    Accept: */*

Once the login prompt has been taken care of, a redirect should occur to something like

.. code-block:: http
    :caption: Sample Redirect/Response 

    GET https://jwt.ms#id_token=eyJ0XAi...4faeEoQ&code=XfTTAAAvPM1KaPlrEqdFSB..&state=the_state_you_sent_in_during_step_one HTTP/1.1
    Host: jwt.ms
    Connection: keep-alive
    Accept: */*

At this point you can either use the `code` to obtain an `access_token` or you can verify and decode the `id_token`

Verifying and Decoding the token
--------------------------------

The ID Token provided is a ``JWT`` token, encoded and signed by the IdP. The signature can be verified by using the key provided in the OIDC Metadata endpoint.
Verification is outside the scope of this documentation, we recommend you entrust that to someone who knows cryptography (i.e. a library/component).

Once decoded the ``id_token`` contains the identification of the user as well as his/her `SubscriberId` and any `Products` that are accessible currently.

The two claims containing the identification:

    * ``extension_SubscriberId`` - A SubscriberId representing a specific subscriber.
    * ``extension_Products`` - A JSON string containing an array of products and the users current validity of those products.


.. code-block::
    :caption: Sample Id Token

    eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6Ilg1ZVhrNHh5b2pORnVtMWtsMll0djhkbE5QNC1jNTdkTzZRR1RWQndhTmsifQ.eyJleHAiOjE2Njk5NzcwOTgsIm5iZiI6MTY2OTk3MzQ5OCwidmVyIjoiMS4wIiwiaXNzIjoiaHR0cHM6Ly9leHBlcmltZW50YXRpb25zNHByb2QuYjJjbG9naW4uY29tL2IyZjhmZWNhLTFhNWMtNDA5MC1hYjQxLTkwMTNkMzQyMDExOC92Mi4wLyIsInN1YiI6IjYyYTc4NmQyLTVjZDItNGEyNi05Y2IwLTE4YjA1NmI5NTYyZiIsImF1ZCI6IjFiMTYyMjMwLTE4MGMtNDY0OC05ZDBmLWEzMTNiYjg2NTEwYyIsImlhdCI6MTY2OTk3MzQ5OCwiYXV0aF90aW1lIjoxNjY5OTczNDk4LCJuYW1lIjoiZXNiYmFjaCt0ZXN0dXNlcjFAaW5mb3NvZnQubm8iLCJlbWFpbHMiOlsiZXNiYmFjaCt0ZXN0dXNlcjFAaW5mb3NvZnQubm8iXSwiZXh0ZW5zaW9uX1N1YnNjcmliZXJJZCI6IjczMjY1NDgzLTBhNjQtNGFjYy05Y2NmLTExMzU5ZWY1Y2U5ZiIsImV4dGVuc2lvbl9Qcm9kdWN0cyI6Ilt7XCJJZFwiOlwiNzBlNzViYzAtNmMzZC00OTM0LWEyZTgtMDhkODBiOTJiNzIxXCIsXCJWYWxpZEZyb21cIjpcIjIwMjItMDYtMjlUMDU6Mzc6MjUuODY2OTA3MSswMDowMFwiLFwiVmFsaWRUb1wiOlwiMjAyMy0wNi0yOVQwNTozNzoyNC44NjY5MDcxKzAwOjAwXCJ9XSIsInRmcCI6IkIyQ18xX1NpZ25pbiIsImNfaGFzaCI6ImZscHdQdXRyMHpfaXVPVHd3N3pKZEEifQ.ADc-WY-w0CH3yY6Ch97vox2F-xEIQOsb3jKb45VJjfwKNuWWGauO5zsdwLyBQk0w_HVU1738SsFYfO0Iwe4cXM6gpf5LVwc8vjugD6pBZLN6SLPEnSCoMdDwRGT_hN_qaotZD7mKTXV3H0io98-btGWs9zjkzLX3APteDih7P8Kn-AjZPVxwnVgkRI0w3-SjkU1fiAtlRYYueFA_0pIEHeLfF9TcvknPvFQry8gvJZbm5-QRgP2z4n6_Hvh9prPDtot2BKahKkgCV877K4U5cYJkWWO8a0LVgKXbx0-7uI9YnjdKU1Hmloh7H70GpaxTfOoxzJxcs3Q9x5MafJvMdg


.. code-block:: json
    :caption: Sample Id Token Decoded

    {
        "exp": 1669977098,
        "nbf": 1669973498,
        "ver": "1.0",
        "iss": "https://experimentations4prod.b2clogin.com/b2f8feca-1a5c-4090-ab41-9013d3420118/v2.0/",
        "sub": "62a786d2-5cd2-4a26-9cb0-18b056b9562f",
        "aud": "1b162230-180c-4648-9d0f-a313bb86510c",
        "iat": 1669973498,
        "auth_time": 1669973498,
        "name": "esbbach+testuser1@infosoft.no",
        "emails": [
            "esbbach+testuser1@infosoft.no"
        ],
        "extension_SubscriberId": "73265483-0a64-4acc-9ccf-11359ef5ce9f",
        "extension_Products": "[{\"Id\":\"70e75bc0-6c3d-4934-a2e8-08d80b92b721\",\"ValidFrom\":\"2022-06-29T05:37:25.8669071+00:00\",\"ValidTo\":\"2023-06-29T05:37:24.8669071+00:00\"}]",
        "tfp": "B2C_1_Signin",
        "c_hash": "flpwPutr0z_iuOTww7zJdA"
    }

The above JWT is a sample, not all fields will always be available or have values.

``extension_SubscriberId`` may be empty for family members and other shared users. 

``extension_Products`` can be empty whenever no mapping exists that grants product access.

Authorization Alternatives
==========================

Now that a token has been retrieved and decoded, the next step is to do the actual authorization.

Depending on your need there are two simple alternatives that may be used, either:

1. Verify that there is something in the ``extensions_Products`` list.
2. Verify that the product requested is available in the ``extensions_Products`` list.

.. note:: 

    ``extensions_SubscriberId`` is not part of the suggested auhtorization process, as in most general cases it is not needed.


.. important::
    
    The two authorization/verification alternatives are suggestions, verify with the business requirements that they will suffice for your case.
