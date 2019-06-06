.. _authorization:

************************************
API Authentication and Authorization
************************************

|projectName| APIs uses OAuth2 for Authorization.

The service is provided by {AUTH0}, and thus the gory details may be found at the {AUTH0} website, but the following should get you started.

Short Version
=============
The quick'n'dirty details for those already familiar with OAuth2 flows.

* Token URL: at |tokenUrl|
* Grant Type: Typically ``client_credentials`` or ``implicit`` but any of the grant types works
* Audience: |auth0audience|

Authorization in detail
=======================

If you are somewhat familiar with OAuth2 terminology we rely on {AUTH0} as the *Authorization server*.
If you have no clue what an authorization server is, it is basically the thing that identifies the application for the user and the API.

To access the API you should obtain a token using for instance the ``client_credentials`` grant type.

Obtaining A Token
-----------------
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

.. code::
    
    Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6Ik1FVTJOa1pEUWpCRVFUWkNRamxCTTBaRFJUZ3pRVEZHUXpaQ09VVTRNa0k0TURBMlJEVkZNdyJ9.eyJpc3MiOiJodHRwczovL2luZm9zdWJzY3JpcHRpb24uZXUuYXV0aDAuY29tLyIsInN1YiI6Ik5Cc2gyalFVbTE2NXNBWTVmZWQzRThaTnppQkF6MGE0QGNsaWVudHMiLCJhdWQiOiJodHRwczovL2FwaS5pbmZvLXN1YnNjcmlwdGlvbi5jb20vIiwiaWF0IjoxNTI0MTQ2NjE4LCJleHAiOjE1MjQyMzMwMTgsImF6cCI6Ik5Cc2gyalFVbTE2NXNBWTVmZWQzRThaTnppQkF6MGE0IiwiZ3R5IjoiY2xpZW50LWNyZWRlbnRpYWxzIn0.fLiToHzpMzcDkBarLu9MYR-LTYR4V0MCeoG4_sEhoH4ykDu0lhp-cgloJnYR6jEFNcK6u8difFViVSrrAnM7QPCp2eqptZQxkqjX0ZNdNUbkvSnpL7iFHKkEvy7DdRLjHkX6oJq_Le9ww6fKmdhVqvEnbu8h39mMWQPHGk0dh0mketr6tZRxu0WGBYusbeZOH9lkn3mQhAFl1nzqE3sePjTkwe1rah8FKHQhI2xYfd-dwMWAiPiXLRS_H5l9NyjtdcIvtXLnfWTM_eo0qAHPh1Q_4TlEPFptLk37Bx3NE6U5UM9EiQLUP0jdxOr9_2mPST70bIKQxh60YRgOWd8Jug

If the client that obatined the token is allowed to communicate with the API, the request will go through, and otherwise you will get an ``403 Forbidden`` error.
Requests with invalid tokens, or without tokens will be presented with a ``HTTP 401`` error.

Authorization Flows or Grant Types
----------------------------------
There are multiple ways to authorize an application to work with an API, in OAuth2 lingo these different flows are called grant types.
Depending on your use case, you may use the flow you are most comfortable with, but for machine to machine interaction, with no end-users involved, we recommend using `client_credentials` grant type.



.. Which authentication flow should I choose?
   ------------------------------------------

    This depends on a few things. If you want to act on behalf of a user, you should use the ``implicit``. 
    This makes sure that the application you are building will have the same rights as the user who is logged in.

    If you just want access to the API as an application (i.e. no user interaction) you should use the ``client_credentials`` grant. 
    This way anyone using your application will have the same rights as your application and no user context will be available to the API.