.. _end-user-authentication:

***************************
Authenticating Subscribers
***************************

|projectName| utilizes {AUTH0} for managing subscriber users, as such developers familiar with {AUTH0} can use what they know of {AUTH0} out of the box, and may refer to their documentation for details.

In order to authenticate users, a regular Open Id Connect (OIDC) login flow may be used.

For most scenarios we recommend using the {AUTH0} Universal Login for authentication, {AUTH0} provides a series of Quick Start guides for different application types at https://auth0.com/docs/quickstarts.

The {AUTH0} guides will refer to the admin section for various details such as `domain`, `connection`, `client_id`, `client_secret` and more.
Refer to the table below on how to obtain all of this information, since you do not have access to the Auth0 admin section. 

.. table:: Auth0 References

    =============      =====
    Connection         <Your Tenant Name>
    Domain             |auth0domain|
    Client_Id          Obtained when signing up, or by contacting infosoft
    Client_Secret      Obtained when signing up, or by contacting infosoft
    Callback           Configured by infosoft upon request
    Logout URL         Configured by infosoft upon request
    =============      =====

.. Note::
    It is on our backlog to allow for more administrative control of these settings, but currently settings like these needs to be coordinated with Infosoft.

.. Tip::
    You may also refer to the :ref:`authorization` section, but keep in mind you need to use an interactive/on-behalf-of grant type 
    and not the `client_credentials` grant type.

    Keep in mind that these are two independent sections of the application with different sets of users, you should treat the authentication as two separate things as well (i.e. one for admins/machines and another for subscribers).

There are a few customizable options for the Login Page, refer to the section :ref:`Login Page Customization` for details.

Example Requests for an authorization code flow
-----------------------------------------------
The following are sample requests for an authorization code flow, this can get you started, but we recommend learning about Open Id Connect and specifically {AUTH0} to get the most out of your authentication and authorization.

1. Obtaining the authorization code

.. tabs:: 

    .. code-tab:: http http

        GET https://{AUTH0DOMAIN}/authorize?response_type=code&client_id=YOUR_CLIENT_ID&connection=CONNECTION&scope=openid&redirect_uri=https://YOUR_APP/callback&state=YOURSTATE HTTP/1.1
        Host: {AUTH0DOMAIN}
        Connection: keep-alive
        Accept: */*

.. code-block:: HTTP
    :caption: Sample Response

    HTTP/1.1 302 Found
    Location: https://YOUR_APP/callback?code=AUTHORIZATION_CODE&state=YOURSTATE

2. Exchanging the code with a token

.. tabs::

   .. code-tab:: bash curl

    curl --request POST \
        --url 'https://{AUTH0DOMAIN}/oauth/token' \
        --header 'content-type: application/x-www-form-urlencoded' \
        --data 'grant_type=authorization_code&client_id=YOUR_CLIENT_ID&client_secret=YOUR_CLIENT_SECRET&code=AUTHORIZATION_CODE&redirect_uri=https://YOUR_APP/callback'

   .. code-tab:: http http

        POST https://{AUTH0DOMAIN}/oauth/token HTTP/1.1
        Host: {AUTH0DOMAIN}
        Content-Type: application/x-www-form-urlencoded
        Accept: application/json

        grant_type=authorization_code&client_id=YOUR_CLIENT_ID&client_secret=YOUR_CLIENT_SECRET&code=AUTHORIZATION_CODE&redirect_uri=https://YOUR_APP/callback

.. code-block:: http
    :caption: Sample Response

    HTTP/1.1 200 OK
    Content-Type: application/json

    {
        "access_token":"eyJz93a...k4laUWw",
        "id_token":"eyJ0XAi...4faeEoQ",
        "token_type":"Bearer",
        "expires_in":86400
    }

Obtaining the Subscriber Id from the token
------------------------------------------
During the OIDC flow, the client may request an `access_token <http://https://auth0.com/docs/tokens/overview-access-tokens>`_  or an `id_token <https://auth0.com/docs/tokens/guides/id-token/get-id-tokens>`_.

When users are managed using the |projectName| Sales Poster and self-service client, both of these tokens should a custom claim for the subscriber id, similar to the listing below:

.. code-block:: json
    :caption: Sample Id Token content

    {
        "https://info-subscription.com/subscriberId": "a9c6b736-dac0-4805-93a2-934ce049551d",
        "https://info-subscription.com/tenantId": "abb7c92e-b8f2-4ae5-fef0-08d69bbc8a54",
        "iss": "https://infosubscription.eu.auth0.com/",
        "sub": "google-oauth2|111745085132080132986",
        "aud": "https://api.info-subscription.com/",
        "iat": 1559798200,
        "exp": 1559805400,
        "azp": "zMOPVqHu29qTWkzqJ6Ybh3Eudohz45v8",
        "scope": ""
    }

This basically identifies the logged in user as a specific subscriber.
It is the subscriber that owns a subscription, not a user.
In practical terms this means that multiple users can be related to the same subscriber.

.. Important::

    Not all users have subscribers!

When you have obtained a `SubscriberId`, head on to the :ref:`subscriber-authorization` section for details on how to determine if you should let the subscriber access a given resource.

Login Page Customization
========================
The Login page that the uses lands on when starting the Authorization flow currently allows for a few customizations that should be added as extra parameters in the query string.

The parameters that you can set are described in the table below together with the effect it creates in the login page.

.. table:: Login Page customizations

    =============      =========================================================================    ==============================================
    **PARAMETER**      **DESCRIPTION**                                                              **EFFECT**
    orgname            The name of the organization as defined in INFO-Subscription                 Customized Window Title and Logo on Login Page
    language            Auth0 language code (https://github.com/auth0/lock/tree/master/src/i18n)    Displays the login page in the specified language
    =============      =========================================================================    ==============================================

An example for setting the Organization to *Demo* and the Language to *Swedish*:

``https://{AUTH0DOMAIN}/authorize?response_type=code&client_id=YOUR_CLIENT_ID&connection=CONNECTION&scope=openid&redirect_uri=https://YOUR_APP/callback&state=YOURSTATE&language=sv&orgname=demo``

Advanced Scenarios
------------------
There are several advanced scenarios such as

* Keeping a user signed in using refresh tokens
* Not prompting for login if already logged in elsewhere
* Passwordless signin
* Probably more!

All of these scenarios are described in detail in the Auth0 documentation, so we recommend you head over to https://auth0.com/docs/ for these advanced scenarios.