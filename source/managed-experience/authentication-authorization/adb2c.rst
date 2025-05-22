*****************
Microsoft |ADB2C|
*****************

The following contains a few pointers related specifically to interactions with |ADB2C| that integrations should consider in the interaction. 
For other customisation and interaction options refer to the official ADB2C product documentation.

.. _adb2c-forgot-password:

Handling Forgotten Password
===========================

With the |projectName| provisioned/managed |ADB2C| instance configuration, some care is required for handling session that starts by the user resetting the password.

The scenario/flow is roughly as follows:

1. The user is presented with a login prompt.
2. The users clicks "Forgot Password".
3. User goes through email verification and enters new password (and a confirmation).
4. The user is logged in without having to enter his/her credentials after the change.

The issue is that during step 4, the regular server side login process is NOT executed.

The end result is that the id_token generated does not include the `extension_SubscriberId` nor `extesion_Products`.

Recommend Workaround
---------------------
The recommended workaround for this scenario is for the integration application to handle the password journey by forcing a new login.

1. Detect that token contains the property `isForgotPassword` with a value `true`.
2. Clear local session cookies.
3. Re-run login flow.

The result will be that the user needs to enter his/her credentials again, and the resulting token will be populated with the correct information.

The above approach is implemented in the |projectName| self-service application.

.. code-block:: json
    :caption: Sample Decoded Id Token for the Forgotten Password Journey

    {
        "ver": "1.0",
        "iss": "https://experimentations4prod.b2clogin.com/b2f8feca-1a5c-4090-ab41-9013d3420118/v2.0/",
        "sub": "62a786d2-5cd2-4a26-9cb0-18b056b9562f",
        "aud": "1b162230-180c-4648-9d0f-a313bb86510c",
        "exp": 1707321390,
        "nonce": "defaultNonce",
        "iat": 1707317790,
        "auth_time": 1707317790,
        "isForgotPassword": true,
        "name": "esbbach+testuser1@infosoft.no",
        "emails": [
        "esbbach+testuser1@infosoft.no"
        ],
        "oid": "62a786d2-5cd2-4a26-9cb0-18b056b9562f",
        "tfp": "B2C_1_Signin",
        "nbf": 1707317790
    }


.. _adb2c-sso:

Single Sign-On
==============
To implement single sign-on properly, please refer to the section about session management.

Sign-out details
-----------------

For applications to terminate the IdP/Login session, the `client_id` needs to be sent in the sign-out request.
Refer to additional details of the sign-out process at the `official web site <https://learn.microsoft.com/en-us/azure/active-directory-b2c/openid-connect#send-a-sign-out-request>`_

Forced Sign-In
==============
To force a sign-in and ignore any IdP/Login Sessions, include the query parameter `prompt=login` in the authorisation request. This will forcefully terminate the IdP/Login sessions for the given `client_id`.