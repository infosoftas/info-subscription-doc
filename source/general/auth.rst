.. _authorization:

************************************
API Authentication and Authorization
************************************

|projectName| APIs uses OAuth2 and OIDC for API Authentication. 
OAuth2 knowledge on its own is sufficient but the metadata discovery of OIDC makes the process simpler for most libraries.

The underlying authentication service is provided by |ADB2C| the following should get you started, if you have questions reach out to support.

.. important::
    
    This sections describes authentication for the API, look to the :ref:`User Authorisation Quick Start <auth-quick-start>` for details on end-user/subscriber authentication and authorisation.

Minimum Required Details
========================
The quick'n'dirty details for those already familiar with OAuth2 or OIDC flows who just wants to get started.

* Token URL: at |adb2cTokenUrl|
* Grant Type: Typically ``client_credentials``
* Audience: |adb2cAudience|
* Metadata Url: |adb2cMetadataUrl|
* Scope: |adb2cscope|

Remember to `Reuse the Token`_ until it expires!

Token Acquisition
=================

If you are somewhat familiar with OAuth2 and OIDC terminology we rely on |ADB2C| as the *Authorization server*.
If you have no clue what an authorisation server is, it is basically the thing that identifies the application for the user and the API.

To access the API you should obtain a token using for instance the ``client_credentials`` grant type.

To obtain a token ``POST`` a request to |adb2cTokenUrl| with a body containing your chosen flow type, client credentials and the audience.

.. tabs::

   .. code-tab:: bash curl

    curl --request POST \
        --url 'https://prodlogins4.b2clogin.com/prodlogins4.onmicrosoft.com/B2C_1A_V2SIGNIN/oauth2/v2.0/token' \
        --header 'content-type: application/x-www-form-urlencoded' \
        --data 'grant_type=client_credentials&client_id=YOUR_CLIENT_ID&client_secret=YOUR_CLIENT_SECRET&scope=ADB2CAPISCOPE'

   .. code-tab:: http http

        POST https://prodlogins4.b2clogin.com/prodlogins4.onmicrosoft.com/B2C_1A_V2SIGNIN/oauth2/v2.0/token HTTP/1.1
        Host: prodlogins4.b2clogin.com
        Content-Type: application/x-www-form-urlencoded
        Accept: application/json

        grant_type=client_credentials&client_id=YOUR_CLIENT_ID&client_secret=YOUR_CLIENT_SECRET&scope=ADB2CAPISCOPE

The response comes in the form of a JWT token, a type, and an expiration time relative to the issue time.

.. code-block:: json

    {
        "access_token": "eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6Imhxb2k2Z19yanhEdmtuWmVKNDVIWk9UbnhkeHNrSnVldTRCdE04ajRQTFUifQ.eyJpc3MiOiJodHRwczovL3FhbG9naW5zNC5iMmNsb2dpbi5jb20vZDgxODM4NGEtZjZjZS00ZDJhLWIwNWEtMjI5NTUxZjY4YTJhL3YyLjAvIiwiZXhwIjoxNjY0MjkyOTg2LCJuYmYiOjE2NjQyODkzODYsImF1ZCI6IjcyNjM4OWJiLTVmODAtNDdlOC1hMTE1LTk0MjcxMTlmOTI5OSIsInRpZCI6ImQ4MTgzODRhLWY2Y2UtNGQyYS1iMDVhLTIyOTU1MWY2OGEyYSIsImNvcnJlbGF0aW9uSWQiOiIzZDM2NjAzNi1kMWYzLTQyYjctOGMzMC1lNWI2ZDAzZGIzMTEiLCJzY3AiOiJhcGlhZG1pbiIsImF6cGFjciI6IjEiLCJzdWIiOiI3MWQ3ZTNhMS0yMTA3LTQ5ZmUtOTZiMy00ZGFiM2JhYmM4NDgiLCJvaWQiOiI3MWQ3ZTNhMS0yMTA3LTQ5ZmUtOTZiMy00ZGFiM2JhYmM4NDgiLCJ2ZXIiOiIyLjAiLCJhenAiOiJmNmY4OWQ5Ni02N2VjLTQ1ZWQtYmJjOS0xMTExMmE0OTUxZDAiLCJpYXQiOjE2NjQyODkzODZ9.Y2syarjQxh1Bxc6W9vsnXo6TvOgFZZGb4cy21wZNzHy6s3lXmmuUtQ-Aae7CODXYhgLtE5PEmcgGzBSlxVbW_MM937e1yx6y0fDgr9wONcFc5RRxjYZctXVOH38TMWj2p-LSOSGZPgVH_CD1vEsA05urszP4QllkQwhHY5RN7Y-1PI-KupPkIocddJchl3jw_HB8_iIP9IjUhxptH6bAXjDwnzoVbMVVfCy4qMpf4EpxsbOP9nUdyhDJBHnTmYamnOKEk6JfDMJ1Y_f2seLK9HZ7GVT2RL7hn1X7zgL474LgOVOwOk8VolTzHOxV2kmacAVUlL0X6x0mfpAEEh9j8Q",
        "token_type": "Bearer",
        "not_before": 1664289386,
        "expires_in": 3600,
        "expires_on": 1664292986,
        "resource": "726389bb-5f80-47e8-a115-9427119f9299"
    }

If you want to look at whats inside the token go to https://jwt.io or https://jwt.ms and copy/paste the token to have a look.

Using the token
================

Once you have a token, it should be included in the ``Authorization`` header as a ``Bearer`` token. It should look something like the following

.. code::
    
    Authorization: Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJSUzI1NiIsImtpZCI6Imhxb2k2Z19yanhEdmtuWmVKNDVIWk9UbnhkeHNrSnVldTRCdE04ajRQTFUifQ.eyJpc3MiOiJodHRwczovL3FhbG9naW5zNC5iMmNsb2dpbi5jb20vZDgxODM4NGEtZjZjZS00ZDJhLWIwNWEtMjI5NTUxZjY4YTJhL3YyLjAvIiwiZXhwIjoxNjY0MjkyOTg2LCJuYmYiOjE2NjQyODkzODYsImF1ZCI6IjcyNjM4OWJiLTVmODAtNDdlOC1hMTE1LTk0MjcxMTlmOTI5OSIsInRpZCI6ImQ4MTgzODRhLWY2Y2UtNGQyYS1iMDVhLTIyOTU1MWY2OGEyYSIsImNvcnJlbGF0aW9uSWQiOiIzZDM2NjAzNi1kMWYzLTQyYjctOGMzMC1lNWI2ZDAzZGIzMTEiLCJzY3AiOiJhcGlhZG1pbiIsImF6cGFjciI6IjEiLCJzdWIiOiI3MWQ3ZTNhMS0yMTA3LTQ5ZmUtOTZiMy00ZGFiM2JhYmM4NDgiLCJvaWQiOiI3MWQ3ZTNhMS0yMTA3LTQ5ZmUtOTZiMy00ZGFiM2JhYmM4NDgiLCJ2ZXIiOiIyLjAiLCJhenAiOiJmNmY4OWQ5Ni02N2VjLTQ1ZWQtYmJjOS0xMTExMmE0OTUxZDAiLCJpYXQiOjE2NjQyODkzODZ9.Y2syarjQxh1Bxc6W9vsnXo6TvOgFZZGb4cy21wZNzHy6s3lXmmuUtQ-Aae7CODXYhgLtE5PEmcgGzBSlxVbW_MM937e1yx6y0fDgr9wONcFc5RRxjYZctXVOH38TMWj2p-LSOSGZPgVH_CD1vEsA05urszP4QllkQwhHY5RN7Y-1PI-KupPkIocddJchl3jw_HB8_iIP9IjUhxptH6bAXjDwnzoVbMVVfCy4qMpf4EpxsbOP9nUdyhDJBHnTmYamnOKEk6JfDMJ1Y_f2seLK9HZ7GVT2RL7hn1X7zgL474LgOVOwOk8VolTzHOxV2kmacAVUlL0X6x0mfpAEEh9j8Q

If the client that obtained the token is allowed to communicate with the API, the request will go through, and otherwise you will get an ``403 Forbidden`` error.
Requests with invalid tokens, or without tokens will be presented with a ``HTTP 401`` error.

Authorisation Flows or Grant Types
==================================
There are multiple ways to authorise an application to work with an API, in OAuth2 lingo these different flows are called grant types.
Depending on your use case, you may use the flow you are most comfortable with.

For machine to machine interaction, with no end-users involved, the recommended option is to use `client_credentials` grant type.

For cases with interactive administrative/merchant users, the recommended option is to use `implicit` or `authorization_code` grant types.

Reuse the Token
===============
All API tokens contains information about when they expire relative to the issuing time. That means a token can be re-used for all machine to machine requests in the timeframe for the given client/audience/tenant pair.
For most integrations that means only one token is needed at a time. For some integrations it may require a few more, but a limited set of tokens needs to be generated and they can be kept untill they expire.

While obtaining a new token is a relatively quick action, the token should be re-used until it expires for two primary reasons:

1. It improves the performance/experience for the integration i.e. not every API call needs a new token authorization, but just once every hour/day the overhead is paid.
2. Costs, there is an indirect cost associated with API Authentications, in case of repeated misuse extra charges may be added to the tenant.

Authentication Libaries and SDKs
================================

Most OIDC/OAuth2 conformant libraries and SDKs can be used to obtain tokens.

Our recommendation is to use a library if at all possible instead of relying on a hand rolled solution.

Most libaries will do, but since we have used Microsoft ADB2C and Auth0 as the token providers those are the libraries we have tested to some degree.

Microsoft Authentication Library - MSAL
---------------------------------------

Microsoft provides a range of `client SDKs <https://learn.microsoft.com/en-us/azure/active-directory/develop/msal-overview#languages-and-frameworks>`__ that are designed to work with the Microsoft Identity Platform on a wide array of languages and platforms.

It supports the various quirks of ADB2C, but should work for most OIDC providers.

Most of the SDKs includes transparent in-memory caching of tokens, and in some cases extension libraries for serialized token caches exists as well.

Auth0 Authentication and Management Libraries
---------------------------------------------

Similar Auth0 provides a wide range of `client SDKs <https://auth0.com/docs/libraries>`__  that are easily consumed and supports the various Auth0 quirks.

There are event more languages and frameworks supported for Auth0 than MSAL. 
Similar to the Microsoft libraries, some of these provides in-memory caching as well as serialized token caches.
