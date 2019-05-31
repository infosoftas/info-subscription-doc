.. _end-user-authentication:

***************************
Authenticating Subscribers
***************************

|projectName| utilizes Auth0 for managing subscriber users, as such developers familiar with Auth0 can use what they know of Auth0 out of the box, and may even refer to their documentation for details.

In order to authenticate users, a regular OAuth2/Open Id Connect (OIDC) login flow may be used.

For most scenarios we recommend using the Auth0 Universal Login for authentication, Auth0 provides a series of Quick Start guides for different application types at https://auth0.com/docs/quickstarts.
The guides will refer to the Auth0 admin section for various details such as `domain`, `connection`, `client_id`, `client_secret` and more.
Refer to the table below on how to obtain all of this information, since you do not have access to the Auth0 admin section. 

==========      =====
Connection      <Your Tenant Name>
Domain          infosubscription.eu.auth0.com
Client_Id       Obtained when signing up, or by contacting infosoft
Client_Secret   Obtained when signing up, or by contacting infosoft
Callback        Configured by infosoft upon request
Logout URL      Configured by infosoft upon request
==========      =====

.. Note::
    It is on our backlog to allow for more administrative control of these settings, but currently settings like these needs to be coordinated with infosoft.

You may also refer to our guide on authorization for the API ref:`_authorization`, but keep in mind you need to use an interactive/on-behalf-of grant type and not the `client_credentials` grant type.
Also keep in mind that these are two independent sections of the application, and you should treat the authentication as two separate things as well (i.e. one for admins/machines and another for subscribers).