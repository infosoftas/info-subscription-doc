.. _auth-quick-start:

***********
Quick Start
***********
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
    * ``extension_Products`` - A comma separated list of products the user is somehow mapped to currently.


.. code-block::
    :caption: Sample Id Token

    eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6Ilg1ZVhrNHh5b2pORnVtMWtsMll0djhkbE5QNC1jNTdkTzZRR1RWQndhTmsifQ.eyJleHAiOjE2NjMwNjQ5MjAsIm5iZiI6MTY2MzA2MTMyMCwidmVyIjoiMS4wIiwiaXNzIjoiaHR0cHM6Ly9zdHJpa2tlZGFtZW5zNHFhLmIyY2xvZ2luLmNvbS80NmJlNmVjOC1iNzRhLTQ0YTAtYWFkNi0wZjRhMzA0YjU5ZTcvdjIuMC8iLCJzdWIiOiI3NGEyOTRjMy03NmQxLTQwMjktOWJjMC0zNTAyMmJkN2E2MWUiLCJhdWQiOiI5NmMwNzczNS0wZTk3LTQ3YTAtYmI0MC0yOTk3MjZmMWM3YjUiLCJub25jZSI6ImRlZmF1bHROb25jZSIsImlhdCI6MTY2MzA2MTMyMCwiYXV0aF90aW1lIjoxNjYzMDYxMzIwLCJuYW1lIjoiRXNiZW4iLCJnaXZlbl9uYW1lIjoiRXNiZW4iLCJlbWFpbHMiOlsiZXNiYmFjaEBpbmZvc29mdC5ubyJdLCJleHRlbnNpb25fU3Vic2NyaWJlcklkIjoiN2U0MTE2NWQtOTA5OS00Y2MwLTllOWItYzk3YjkzODgzY2QwIiwiZXh0ZW5zaW9uX1Byb2R1Y3RzIjoiNTQ5NzJjODctY2JhMy00YWY5LTMwODYtMDhkYTBiZDI0MDhjLDdmNWY3OGE1LWM4NDItNDI5Ny0zMDg3LTA4ZGEwYmQyNDA4Yyw5MGZhYzMyMi02ZDA2LTQyZTItMzA4OC0wOGRhMGJkMjQwOGMiLCJ0ZnAiOiJCMkNfMV9TaWduSW4ifQ.CctTVjBKw1SilfWOu2XStR6V6idzQNfxPrEnG-wU-B61_c8wbV4sqrM4JZpNmaCSJIqWUY2Le7ZXEz-kgenAzaKJ-s79xiU19G_G23yMeJh-MJJ2llasNLI9Lw57fRS032oswZj_pAr7qYx1xf5BX6cwV2YqU2zmwXsSYr4SVwAgs-CeB26HMB075cQSZ0bTXqWi78i7-4MLBAd44o-xrETxp5ZAmXr8BKifQe3tKdkD90onrlJQUVgQ0al9Ih5nC58GIcUwfghSFeuh8ZkG9Mx8Pjw2kYqDT70m2IHHVqFyG55YREDTz2MkD-oxEac7cfH2vNEbt7sHlHxVE3kseA


.. code-block:: json
    :caption: Sample Id Token Decoded

    {
        "exp": 1663064920,
        "nbf": 1663061320,
        "ver": "1.0",
        "iss": "https://strikkedamens4qa.b2clogin.com/46be6ec8-b74a-44a0-aad6-0f4a304b59e7/v2.0/",
        "sub": "74a294c3-76d1-4029-9bc0-35022bd7a61e",
        "aud": "96c07735-0e97-47a0-bb40-299726f1c7b5",
        "nonce": "defaultNonce",
        "iat": 1663061320,
        "auth_time": 1663061320,
        "name": "Esben",
        "given_name": "Esben",
        "emails": [
            "esbbach@infosoft.no"
        ],
        "extension_SubscriberId": "7e41165d-9099-4cc0-9e9b-c97b93883cd0",
        "extension_Products": "54972c87-cba3-4af9-3086-08da0bd2408c,7f5f78a5-c842-4297-3087-08da0bd2408c,90fac322-6d06-42e2-3088-08da0bd2408c", 
        "tfp": "B2C_1_SignIn"
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
