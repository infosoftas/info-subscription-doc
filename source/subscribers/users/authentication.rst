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
    It is on our backlog to allow for more administrative control of these settings, but currently settings like these needs to be coordinated with infosoft.

You may also refer to the :ref:`authorization` section, but keep in mind you need to use an interactive/on-behalf-of grant type 
and not the `client_credentials` grant type.

Also keep in mind that these are two independent sections of the application, 
and you should treat the authentication as two separate things as well (i.e. one for admins/machines and another for subscribers).

Obtaining the Subscriber Id from the token
------------------------------------------
During the OIDC flow, the client may request an `access_token <http://https://auth0.com/docs/tokens/overview-access-tokens>`_  or an `id_token <https://auth0.com/docs/tokens/guides/id-token/get-id-tokens>`_.

When users are managed using the |projectName| Sales Poster and self-service client, both of these tokens should a custom claim for the subscriber id, similar to the listing below:

.. code-block:: json

    {
        "aud" : "asdasd",
        "https://api.info-subscription.com/subsriberId" : "12345-12345-12345",
        "https://api.info-subscription.com/tenantId" : "12345-12345-12345"
    }