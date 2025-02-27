.. _getting-started:

****************************
Getting Started with the API
****************************

The |projectName| APIs are HTTP-based and designed to somewhat conform to the REST ideology.
Purists will note that there are no Hypermedia links, this will may change in the future.

The entire management capability of the platform is exposed in the API, meaning that whatever you see in our supplied management and self-service solution you should be able to do with the API.
Meaning you can do things such as:

    * Integrate with existing web-shops or frontends
    * Provide tailored self-service for subscribers matching your brand and workflows
    * Integrate management capability in a custom business portal, CRM System or similar

.. IMPORTANT::
    Please read the introduction about the terminology before you start banging your head against the wall, it might actually contain a pointer or two that will help you.

In order to actually use the API you will need a couple of things

* A set of client credentials
* A TenantId

The client credentials are used for authentication and authorization to the API which is :ref:`described separately <authorization>`

While the TenantId is used to ascertain which tenant your application is trying to access.

Once you have authenticated, try retrieving a subscriber or all subscriptions to get some instant gratification.

Obtaining Client Credentials 
============================

At the current time there is no registration process, so you have to :ref:`contact Infosoft <reporting-bugs>` to obtain a set of credentials.

Client Credentials comes in the form of a *client_id* and *client_secret* are used to authenticate (identify) and authorize an application in the API.
Together with the |tenantHeader| (see below), the API will determine if the client should be granted access or not.

.. Important::

    The `client_secret` is actually secret. You should keep this safe, and not disclose it to others.

.. TIP::
    You should consider obtaining separate credentials for separate applications/solutions.

    This way it is easier for you to keep track of the source when investigating issues, errors or peculiar behavior.


Obtaining a Tenant Id
=====================

Infosoft should have given you a Tenant Id when you signed up for using |projectName|. If you are a third party, contact the tenant/customer and have them provide you with a Tenant Id.
If not please :ref:`contact support <reporting-bugs>` for the Tenant Id

Using the Tenant Id
-------------------

The TenantId is in the form of a UUIDv4/GUID such as ``fe923cfe-2e67-4f7a-960a-d4c36fce22c4`` and at the current time is required in the |tenantHeader| header for all requests to the API.

Endpoint(s)
===========

The |projectName| APIs are accessed using https://api.info-subscription.com/ as the base url. 
All paths, names etc that is referenced here will be relative to that base URL.

.. include:: requests-responses.inc