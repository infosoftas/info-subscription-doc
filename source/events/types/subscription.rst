.. _subscription-created-event:

Event: com.info-subscription.SubscriptionCreated
------------------------------------------------
All operations that results in a new subscription period will trigger a ``SubscriptionCreated`` event.

The typical sources of a new Subscription are

* Orders
* Subscription Renewal

Other operations may create new subscriptions such as Plan Changes, Pauses and Infosoft initiated migrations (this is not a complete list).

.. Important:: 

    The ``SubscriptionCreated`` event should not be confused with the ``OrderProcessed`` event. 
    Subscriptions are created on a recurring basis until a subscription is cancelled, while orders are only created at the beginning of a subscription.

Example Use Case
~~~~~~~~~~~~~~~~
The ``SubscriptionCreated`` event may be used to keep external systems up to date instead of doing bulk synchronizations, such as updating:

* External Entitlement/Authorizaitons
* Delivery Management
* Service Desks
* Cash Registers

It may be used to distribute out a monthly newsletter (if the subscription is monthly), or it may be used to notify subscribers that they have a subscription (for infrequent subscriptions).

.. _subscription-deactivated-event:

Event: com.info-subscription.SubscriptionDeactivated
----------------------------------------------------
When a subscription has been cancelled, and the cancellation time has been reached/passed, a ``SubscriptionDeactivated`` event will be fired.
For sources of subscription cancellations, please refer to the ``SubscriptionCancelled`` event below.

Example Use Case
~~~~~~~~~~~~~~~~
Some ideas on how to use the deactivation event.

* Revoking authorizations
* Starting data cleanup operations, like removing from mailing lists

.. _subscription-cancelled-event:

Event: com.info-subscription.SubscriptionCancelled
--------------------------------------------------
Operations that result in subscriptions being cancelled will lead to a ``SubscriptionCancelled`` event being fired.

Typical source of Subscription cancellations are

* User initiated cancellations (Merchant or Self-Service).
* Orders with an Automatic Cancellation marker.
* Subscription Pauses (which are implemented as Cancel followed by Create).
* Forced cancellations due to lack of payments (Payment Stop).

The ``SubscriptionCancelled`` event is fired at the registration time, NOT at the time of the cancellation taking effect.

.. note::
    When a subscription is cancelled, proration policies determine whether subscribers are credited for unused time or charged for invoiced periods. 
    See :ref:`Proration Policies for Cancellations <proration-policies>` for detailed information on how cancellation proration works.

Example Use Case
~~~~~~~~~~~~~~~~
Similar to ``SubscriptionCreated``, the ``SubscriptionCancelled`` event may be used to keep external system in sync.

* Automated 'Sorry to see you go' emails.
* Automated offers to save the customer.
* Automated transfer to external debt collection (Payment Stops).