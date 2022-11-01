.. _auth-site-access:

Scenario: Site Access
=====================

For some business scenarios, it is common to provide access to a product for a given site or location.

A common example is scientific journals, a university buys access and all employees and students are granted access whenever they are on campus.

There are many solutions for this problem, but a common solution is to somehow map the IP Address of the campus, and all requests originating from that IP will be allowed access.

The model provided by |projectName| can help automate a solution for this scenario, but some custom authorization logic is still required to make it work.

The scenario assumes the following:

* A subscription for a given product is required to access content.
* A campus/site/location can be associated with one or more public IP Addresses.
* The content management system can identify the accessing IP.

To achieve such a site access authorisation a few things should be done.

Using |projectName| do the following:

1. Create a Subscription Plan with the required product(s)
2. Create a Subscriber and a Subscription on the new plan. If you do this via the API, the Sales Poster or the Merchant is not important.
3. Record the Subscriber Account Id.
4. Create an Identity Provider and call it ``Site Access`` or something similar.
5. Add a new user for the ``Site Access`` provider, in the ``ExternalId`` note the IP Address of the site.
6. Create a ``SubscriberAccountSource`` using the just created ``userId`` and the ``subscriberAccountId``.
7. Test it by providing the IP Address to the endpoint ``/authorizations/identityprovider/{identityProviderId}/user/127.0.0.1``

In the CMS do the following:

1. Before Authentication obtain the IP address and look it up using the endpoint from above.
2. If a valid/success response is given grant access, otherwise start the regular authentication and authorisation process for users.

Now everyone on campus has access without authenticating and without an individual subscription.

If the subscription is upgraded, everyone gets access to the upgrade.
Should the subscription be cancelled, everyone looses their access.
