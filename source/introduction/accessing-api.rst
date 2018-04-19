Accessing the API
=================

The |projectName| API is accessed using https://api.info-subscription.com/ as the base url. 
All paths, names etc that is referenced here will be relative to that base URL.

In order to actually use the API you will need a couple of things

* A set of client credentials
* A TenantId

Obtaining Client Credentials 
----------------------------

At the current time there is no registration process, so you have to contact Infosoft to obtain a set of credentials.
If you are a third party, please contact your client directly.

Client Credentials comes in the form of a *client_id* and *client_secret* are used to authenticate (identify) and authorize an application in the API.
Together with the |tenantHeader| (see below), the API will determine if the client should be granted access or not.

.. TIP::
    You should consider obtaining separate credentials for separate applications/solutions.

    This way it is easier for you to keep track of the source when investigating issues, errors or perculiar behavior.


Using the Client Credentials
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Authentication flow details here? Or maybe in a separate document?



Obtaining a Tenant Id
--------------------

Infosoft should have given you a Tenant Id when you signed up for using |projectName|. 
If not please contact support for the Tenant Id, or in case you are a third party, please contact your client directly.

Using the Tenant Id
~~~~~~~~~~~~~~~~~~~

The TenantId is in the form of a UUID/GUID such as ``fe923cfe-2e67-4f7a-960a-d4c36fce22c4`` and at the current time is required in the |tenantHeader| header for all requests to the API.