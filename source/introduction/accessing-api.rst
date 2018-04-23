.. _accessing-api:
*****************
Accessing the API
*****************

The |projectName| APIs are HTTP-based and designed to somewhat conform to the REST ideology.
Purists will note that there are no Hypermedia links, this will hopefully change in the future.

The entire management capability of the platform is exposed in the API, meaning that whatever you see in our supplied management client and subscriber client you should be able to do with the API.
Meaning you can do things such as:

    * Integrate with existing web-shops or frontends
    * Provide tailormade self-service for subscribers matching your brand and workflows
    * Integrate management capability in a custom business portal, CRM System or similar

The |projectName| APIs are accessed using https://api.info-subscription.com/ as the base url. 
All paths, names etc that is referenced here will be relative to that base URL.

In order to actually use the API you will need a couple of things

* A set of client credentials
* A TenantId


Authorization
=============
|projectName| APIs uses OAuth2 for authorization.

Short Version
-------------
The quick'n'dirty details for those already familiar with OAuth2 flows.

* Token URL: at |tokenUrl|
* Grant Type: ``client_credentials`` or ``implicit``
* Audience: |auth0audience|

Authorization in detail
-----------------------

If you are familiar with OAuth terminology we rely on {AUTH0} as the *Authorization server*.
If you have no clue what an authorization server is, it is basically the thing that identifies the application for the user and the API.

To access the API you should obtain a token using either the ``client_credentials`` or ``implicit`` grant types.

Obtaining A Token
~~~~~~~~~~~~~~~~~
To obtain a token ``POST`` a request to  |tokenUrl|
with a body containing your chosen flow type, client credentials and the audience

.. code-block:: json
    :linenos:

    {
        "client_id" : "{{client_id}}",
        "client_secret":"{{client_secret}}",
        "audience":"https://api.info-subscription.com/",
        "grant_type":"client_credentials"
    }


The response comes in the form of a JWT token, a type, and an expiration time relative to the issue time.

.. code-block:: json

    {
        "access_token": "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6Ik1FVTJOa1pEUWpCRVFUWkNRamxCTTBaRFJUZ3pRVEZHUXpaQ09VVTRNa0k0TURBMlJEVkZNdyJ9.eyJpc3MiOiJodHRwczovL2luZm9zdWJzY3JpcHRpb24uZXUuYXV0aDAuY29tLyIsInN1YiI6Ik5Cc2gyalFVbTE2NXNBWTVmZWQzRThaTnppQkF6MGE0QGNsaWVudHMiLCJhdWQiOiJodHRwczovL2FwaS5pbmZvLXN1YnNjcmlwdGlvbi5jb20vIiwiaWF0IjoxNTI0MTQ2NjE4LCJleHAiOjE1MjQyMzMwMTgsImF6cCI6Ik5Cc2gyalFVbTE2NXNBWTVmZWQzRThaTnppQkF6MGE0IiwiZ3R5IjoiY2xpZW50LWNyZWRlbnRpYWxzIn0.fLiToHzpMzcDkBarLu9MYR-LTYR4V0MCeoG4_sEhoH4ykDu0lhp-cgloJnYR6jEFNcK6u8difFViVSrrAnM7QPCp2eqptZQxkqjX0ZNdNUbkvSnpL7iFHKkEvy7DdRLjHkX6oJq_Le9ww6fKmdhVqvEnbu8h39mMWQPHGk0dh0mketr6tZRxu0WGBYusbeZOH9lkn3mQhAFl1nzqE3sePjTkwe1rah8FKHQhI2xYfd-dwMWAiPiXLRS_H5l9NyjtdcIvtXLnfWTM_eo0qAHPh1Q_4TlEPFptLk37Bx3NE6U5UM9EiQLUP0jdxOr9_2mPST70bIKQxh60YRgOWd8Jug",
        "expires_in": 86400,
        "token_type": "Bearer"
    }

If you want to look at whats inside the token go to https://jwt.io and have a look.

Once you have a token, it should be included in the ``Authorization`` header as a ``Bearer`` token. It should look something like the following

.. code-block:: http
    
    Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6Ik1FVTJOa1pEUWpCRVFUWkNRamxCTTBaRFJUZ3pRVEZHUXpaQ09VVTRNa0k0TURBMlJEVkZNdyJ9.eyJpc3MiOiJodHRwczovL2luZm9zdWJzY3JpcHRpb24uZXUuYXV0aDAuY29tLyIsInN1YiI6Ik5Cc2gyalFVbTE2NXNBWTVmZWQzRThaTnppQkF6MGE0QGNsaWVudHMiLCJhdWQiOiJodHRwczovL2FwaS5pbmZvLXN1YnNjcmlwdGlvbi5jb20vIiwiaWF0IjoxNTI0MTQ2NjE4LCJleHAiOjE1MjQyMzMwMTgsImF6cCI6Ik5Cc2gyalFVbTE2NXNBWTVmZWQzRThaTnppQkF6MGE0IiwiZ3R5IjoiY2xpZW50LWNyZWRlbnRpYWxzIn0.fLiToHzpMzcDkBarLu9MYR-LTYR4V0MCeoG4_sEhoH4ykDu0lhp-cgloJnYR6jEFNcK6u8difFViVSrrAnM7QPCp2eqptZQxkqjX0ZNdNUbkvSnpL7iFHKkEvy7DdRLjHkX6oJq_Le9ww6fKmdhVqvEnbu8h39mMWQPHGk0dh0mketr6tZRxu0WGBYusbeZOH9lkn3mQhAFl1nzqE3sePjTkwe1rah8FKHQhI2xYfd-dwMWAiPiXLRS_H5l9NyjtdcIvtXLnfWTM_eo0qAHPh1Q_4TlEPFptLk37Bx3NE6U5UM9EiQLUP0jdxOr9_2mPST70bIKQxh60YRgOWd8Jug


.. Which authentication flow should I choose?
   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    This depends on a few things. If you want to act on behalf of a user, you should use the ``implicit``. 
    This makes sure that the application you are building will have the same rights as the user who is logged in.

    If you just want access to the API as an application (i.e. no user interaction) you should use the ``client_credentials`` grant. 
    This way anyone using your application will have the same rights as your application and no user context will be available to the API.


Obtaining Client Credentials 
============================

At the current time there is no registration process, so you have to :ref:`contact Infosoft <reporting-bugs>` to obtain a set of credentials.

Client Credentials comes in the form of a *client_id* and *client_secret* are used to authenticate (identify) and authorize an application in the API.
Together with the |tenantHeader| (see below), the API will determine if the client should be granted access or not.

.. TIP::
    You should consider obtaining separate credentials for separate applications/solutions.

    This way it is easier for you to keep track of the source when investigating issues, errors or perculiar behavior.


Obtaining a Tenant Id
=====================

Infosoft should have given you a Tenant Id when you signed up for using |projectName|. 
If not please :ref:`contact support <reporting-bugs>` for the Tenant Id

Using the Tenant Id
-------------------

The TenantId is in the form of a UUID/GUID such as ``fe923cfe-2e67-4f7a-960a-d4c36fce22c4`` and at the current time is required in the |tenantHeader| header for all requests to the API.

Endpoint(s)
===========

The |projectName| APIs are accessed using https://api.info-subscription.com/ as the base url. 
All paths, names etc that is referenced here will be relative to that base URL.

