.. _auth-product-in-depth:

*******************************
Product Authorization In Depth
*******************************
The following describes the relationship between users, subscribers, authentications and authorizations and how these concepts are treated by |projectName|.

Authentication and authorization is often mixed together, because they often follow right after each other.
For good measure the following is how the terms are defined throughout the documentation:

* Authentication is the process of identifying the user is who she says she is, typically handled by asking for a password and other credentials.
* Authorization is the process of determining what the user should have access to do. I.e `Is Jane Doe allowed to read the sports section?`

|projectName| does not make any assumptions, restrictions or requirements about how tenants want to Authenticate and Authorize.
Meaning each tenant is free to use their own IdP and roll their own custom authorization process.

Authorization Building Blocks 
=============================
The user authorization module provides building blocks which can be used in different ways to help achieve a simpler, faster and more robust authorization process.

There are several central parts

* Identity Providers
* Users
* Authorization Sources

The following goes into details about each area in turn, describing how they work, can be used by external parties, and how |projectName| use these for providing an out-of-the-box auhtorizaiton experience using |ADB2C|.

To create, update and otherwise manipulate these items look at the API Reference documentation, specifically anything under the `/authorization` path.

Identity Providers
=============================
In short: An identity provider represents a source of users.

An identity provider can be a database, an online service, a location or anything for that matter.
Each user can only exist in one provider at a time, though there is nothing that restricts you from having multiple providers and having the same user added multiple times, one for each.

The fact that an identity provider can be almost anything is used as the background for solving the special case of Site-Access Authorization.

There are two built-in identity provider types that |projectName| knows about and will offer to do some automation for, but even though you utilize one of these types, the automation is entirely optional.

* ADB2C
* Auth0

For both of these built in providers the support revolves around two things:

* Generating claims data in the `id_token` and `access_token`
* Managing users from the self-service and Merchant clients

Both cases needs to make SOME assumptions and requirements on how authorization works, but as mentioned, this part is optional to use.

Users
=====
A User resides with an Identity Provider and exists primarily as a mapping construct between Identity Providers, Subscribers and Products.

A user has the following primary properties:

* ``ExternalId`` - The Id as it is on the Identity Provider. Useful for quick look up after authentication.
* ``SubscriberId`` - An optional Id that maps the user to a specific subscriber.
* ``IdentityProviderId`` - The Id that shows which identity provider this belongs to. Only useful for multi-IdP scenarios.

Authorization Sources
=====================
Some businesses need little more than a `user` and an `identity provider` mapping the user to a subscriber to solve their needs.
Others require a bit more magic to make things working, this is where **Authorization Sources** come into play.
Authorization sources are the auto-magic of the user authorization that |projectName| offers.

.. important::

    An essential assumption is that an authorization is considered to be access to one or more products.
    If this is NOT true for your business, the automation offered is not suitable for your use case.

    It might still be the mapping support used to generate the product list is relevant, but not the end result.

An Authorization Source is a mapping between a user, and an entity that |projectName| knows about.

Each source grants access to one or more products depending on the source.

Whenever an authorization source is added or removed from a user |projectName| will attempt to resolve the list of products that the user has access to based on this source.

At the time of writing the following sources exists, each with its own logic for mapping products onto the users.

* Subscriber
* Subscriber Account
* External Static Sources

Adding an authorization source to a user will result in a list of products being built and associated with the given user.

Each addition, modification or removal will cause a rebuild of the entire list, so please allow a few seconds before the list is completely up to date.

Subscriber Authorization Source
-------------------------------
The subscriber authorization source can be added either directly, or by mapping the user to a subscriber. 
It is the only source that can be implicitly mapped.

The authorization source will enable all products for which the `subscriberId` owns a subscription that is currently valid.

A valid subscription in this context is a subscription that:

* Is started before now
* Is ending later than now
* Is not cancelled currently

Whenever a subscription is created, renewed or cancelled all users connected to a subscriber via the subscriber authorization source will have its product list updated.

This is the mapping type used by |projectName| for the main/primary user account on a subscriber.
The self-service uses this to implicitly indicate ownership.

Subscriber Account Authorization Source
---------------------------------------
Adding a Subscriber Account Id to a user will do something similar to to the Subscriber Authorization Source.

The source will enable all products for which the `subscriberAccountId` owns a subscription that is currently valid (using the same validity conditions as the subscriber source).

This is the mapping type used by |projectName| for adding shared and family users.

A user can be mapped to a subscriber and multiple subscriber accounts at the same time that have nothing to do with each other.

External Static Authorization Source
------------------------------------
In some scenarios it may be something external that grants access to a specific product.

Consider a case where a timed purchase in an external system should temporarily grant access to the same products as a subscription does.
It could be a timed coupon for instance.

You could either build your content system around being able to read these time based coupons or you could let some middleware inject the Product into the user and use the regular authorization routine.

An `External Static Authorization Source` is just that: Something external, and something static (from the point of view of |projectName|).

All products here are added/removed as is.
Only adding or removing a source will cause the product to be enabled or disabled. There is nothing inside |projectName| that will manipulate this list automatically.

Accessing Product Authorizations
================================
Based on the list of authorization sources, a list of products is built for the user.
That list is collapsed so duplicates are removed.

The list can then be access directly by the external user id provided upon registration using the endpoint ``/authorizations/identityprovider/{identityProviderId}/user/{externalId}``

Enriching Tokens During Sign-in
-------------------------------
Most online IdP solutions allows for some sort of external API connections during sign-in.
If mapping is done correctly, these sign-in procedures can use their own User Id to obtain a list of products and make decisions on what to put in the token.

For tenants running the |projectName| provisioned |ADB2C| the ``id_token`` is populated with subscriberId and products during sign-in as described in the quick start.

The same can be achieved if you are running your own |ADB2C| instance. In that case please :ref:`contact support <reporting-bugs>` as configuring it is a bit outside the scope of this documentation.

.. note::

    We are working on migrating our Auth0 based tenants to a solution where the tokens are enriched in the same manner, but it requires some work and most importantly coordination.
    
    If you are interested in transitioning to this new solution please reach out to :ref:`support <reporting-bugs>`.


.. include:: site-access.inc