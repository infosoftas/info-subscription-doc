.. _user-authorization-granted-event:

Event: com.info-subscription.UserAuthorizationGranted
-----------------------------------------------------
When a user is granted authorization to one or more products, a ``UserAuthorizationGranted`` event is triggered.

User authorization in |projectName| is built from authorization sources, such as subscriptions, subscriber accounts, or external static grants.
Whenever a change to these sources results in a user gaining access to a product, this event is fired.

Typical sources of this event are:

* A new subscription being created for a subscriber the user is connected to.
* A subscription renewal that extends an existing authorization.
* An external static authorization source being added for the user.
* An email domain authorization source being associated with the user's email domain.

Example Use Case
~~~~~~~~~~~~~~~~
The ``UserAuthorizationGranted`` event is well suited for keeping external authorization and entitlement systems in sync without polling:

* Granting access to digital content platforms (websites, apps, streaming services).
* Provisioning accounts or entitlements in third-party systems.
* Sending a welcome or access confirmation message to the user.

Related events:

* ``com.info-subscription.UserAuthorizationRevoked``
* ``com.info-subscription.EmailDomainAuthorizationGranted``

.. _user-authorization-revoked-event:

Event: com.info-subscription.UserAuthorizationRevoked
-----------------------------------------------------
When a user's authorization to one or more products is revoked, a ``UserAuthorizationRevoked`` event is triggered.

This is the counterpart to ``UserAuthorizationGranted`` and is fired whenever a change in authorization sources results in a user losing access to a product.

Typical sources of this event are:

* A subscription being cancelled or deactivated.
* An external static authorization source being removed.
* An email domain authorization source being revoked.

Example Use Case
~~~~~~~~~~~~~~~~
The ``UserAuthorizationRevoked`` event can be used to:

* Revoke access to digital content or services in external systems.
* Trigger win-back or re-engagement campaigns when access is lost.
* Clean up user accounts or entitlements in downstream systems.

Related events:

* ``com.info-subscription.UserAuthorizationGranted``
* ``com.info-subscription.EmailDomainAuthorizationRevoked``

.. _email-domain-authorization-granted-event:

Event: com.info-subscription.EmailDomainAuthorizationGranted
------------------------------------------------------------
When an email domain is granted authorization, an ``EmailDomainAuthorizationGranted`` event is triggered.

Email domain authorization allows all users whose email address belongs to a specific domain to be automatically authorized to access one or more products.
This is typically used in institutional or corporate scenarios where access is granted based on an email domain rather than individual subscriber accounts.

When such an authorization is configured for a domain, this event is triggered, which may in turn lead to ``UserAuthorizationGranted`` events for all affected users.

Related events:

* ``com.info-subscription.EmailDomainAuthorizationRevoked``
* ``com.info-subscription.UserAuthorizationGranted``

.. _email-domain-authorization-revoked-event:

Event: com.info-subscription.EmailDomainAuthorizationRevoked
------------------------------------------------------------
When an email domain's authorization is revoked, an ``EmailDomainAuthorizationRevoked`` event is triggered.

This is the counterpart to ``EmailDomainAuthorizationGranted`` and is fired when an email domain authorization is removed, which may result in ``UserAuthorizationRevoked`` events for all users affected by that domain authorization.

Related events:

* ``com.info-subscription.EmailDomainAuthorizationGranted``
* ``com.info-subscription.UserAuthorizationRevoked``
