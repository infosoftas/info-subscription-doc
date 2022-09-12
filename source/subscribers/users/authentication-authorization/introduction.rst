.. _subscriber-authentication-and-authorization:

********************************************
Subscriber Authenticating and Authorization
********************************************

For many subscription services, it is a requirement that subscribers can sign-in and access their subscription. 
Either to consume it or to manage it, and often both.

|projectName| provides optional, built-in, components to solve common authentication and authorization needs.
The components are built such that they can be used with any identity provider (IdP), but with a specific common authorization means.
For advanced authorization scenarios where multiple systems contribute to the authorization flow, the components may be used partially or skipped altogether depending on the requirements.

The following is a quick-start to help get you started if all you require is a simple option to authenticate and authorize subscribers to access one or more specific products.

Quick Start
===========

The default subscriber authentication and authorization component is built around Microsoft Azure ADB2C (henceforth just |ADB2C|). 
Its a long winded name, but it is basically just an Identity Provider for consumer/customer accounts, in this case |projectName| subscribers.

|ADB2C| is an Identiy Provider (IdP) and out of the box provides Authentication using OAuth2 and Open Id Connect (OIDC).
As part of the authentication flow |projectName| extends the identity with a set of attributes that may be used to Authorize the user for accessing a given product.

Since |ADB2C| uses OIDC protocol it is likely that the stack you are using has a component or library that can help you along.

The `official ADB2C documentation contains a guide <https://docs.microsoft.com/en-us/azure/active-directory-b2c/openid-connect>`_ on how to send authenticatation requests.

The guide will refer to variables to replace such as `tenant`, `appId`, `policy` and more.
Refer to the table below on how to obtain all of this information, when you don't have access to the desired information. 

.. table:: ADB2C References

    =============      =====
    tenant             Obtained when signing up an application. Typically the |projectName| tenant name appended with `S4Prod` (Example: `experimentationS4prod`)
    policy             Defaults to `B2C_1_SignIn`
    client_id          Obtained when signing up an application
    client_secret      Obtained when signing up an application
    redirect_uri       Configured when signing up an application, this is your application URL provided when you signed up the application.
    =============      =====

There are quite a few parameters in the table for the `auhtorize` endpoint, most of which is something you need to consider if hand building the request.
If you are using a component or library a lot of this is probably taken care of out of the box.

Example Requests for an authorization code flow
-----------------------------------------------
The following are sample requests for an authorization code flow, to get you started, but we recommend learning about Open Id Connect and specifically |ADB2C| to get the most out of your authentication and authorization process.

If you have a test account on the Experimentation tenant, the following should be reproducable using just your browser.

1. Obtaining the authorization code

.. tabs:: 

    .. code-tab:: http http

        GET https://experimentationS4prod.b2clogin.com/experimentationS4prod.onmicrosoft.com/b2c_1_signin/oauth2/v2.0/authorize?client_id=1b162230-180c-4648-9d0f-a313bb86510c&response_type=code+id_token&redirect_uri=https%3A%2F%2Fjwt.ms%2F&scope=openid%20offline_access&response_mode=fragment HTTP/1.1
        Host: experimentationS4prod.b2clogin.com
        Connection: keep-alive
        Accept: */*

.. code-block:: http
    :caption: Sample Response

    HTTP/1.1 302 Found
    Location: https://jwt.ms/callback?code=AUTHORIZATION_CODE&state=YOURSTATE

At this point the ID Token returned is enough to verify that the user exists.

2. Decoding the token

The ID Token 