.. _authorization:

************************************
API Authentication and Authorization
************************************

|projectName| APIs uses OAuth2 for API Authentication.

The service is provided by {AUTH0}, and thus the gory details may be found at the {AUTH0} website, but the following should get you started.

.. important::
    
    This sections is describes authentication for the API, look :ref:`here for details on end-user/subscriber authentication and authorization for subscribers <end-user-authentication>`.

Short Version
=============
The quick'n'dirty details for those already familiar with OAuth2 flows.

* Token URL: at |tokenUrl|
* Grant Type: Typically ``client_credentials`` but any of the common grant types works. Contact support for specific grant types.
* Audience: |auth0audience|

Remember to re-use the token untill it expires.

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

Reuse/Cache the Token
---------------------
All API tokens contains information about when they expire relative to the issuing time. That means a token can be re-used for all machine to machine requests in the timeframe for the given client/audience/tenant pair.
For most integrations that means only one token is needed at a time. For some integrations it may require a few more, but a limited set of tokens needs to be generated and they can be kept untill they expire.

While obtaining a new token is a relatively quick action, the token should be re-used until it expires for two primary reasons:

1. It improves the performance/experience for the integration i.e. not every API call needs a new token authorization, but just once every hour/day the overhead is paid.
2. Costs, there is an indirect cost associated with API Authentications, in case of repeated misuse extra charges may be added to the tenant.