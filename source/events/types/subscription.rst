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
For sources of subscription cancellations, please refer to :ref:`SubscriptionCancelled <subscription-cancelled-event>`.

Example Use Case
~~~~~~~~~~~~~~~~
Some ideas on how to use the deactivation event.

* Revoking authorizations
* Starting data cleanup operations, like removing from mailing lists

.. _subscription-cancelled-event:

Event: com.info-subscription.SubscriptionCancelled
--------------------------------------------------
The external ``SubscriptionCancelled`` event signals that a cancellation has been registered. It does not mean that the subscription has ended or that access has stopped.

This event covers both ordinary and scheduled cancellations. Scheduled cancellations are reported when registered, not when they later take effect. When a scheduled cancellation takes effect, no second ``SubscriptionCancelled`` event is sent. Use :ref:`SubscriptionDeactivated <subscription-deactivated-event>` to detect when cancellation has taken effect.

For ordinary cancellations, use :api-ref:`Cancel Subscription </Subscription/post_subscription__id__cancel>` (``POST /subscription/{id}/cancel``). For scheduled cancellations, use :api-ref:`Create Scheduled Cancellation </Subscription/post_subscription__subscriptionId__scheduledcancellation>` (``POST /subscription/{subscriptionId}/scheduledcancellation``); you can view them via :api-ref:`List Scheduled Cancellations </Subscription/get_subscription_scheduledcancellation>` (``GET /subscription/scheduledcancellation``).

Typical source of Subscription cancellations are

* User initiated cancellations (Merchant or Self-Service).
* Orders with an Automatic Cancellation marker.
* Forced cancellations due to lack of payments (Payment Stop).

Cancellation Details
~~~~~~~~~~~~~~~~~~~~

The event includes the following consumer-visible cancellation details:

* ``CancellationType`` – The type of cancellation registered.
* ``CancellationCause`` – A text field describing the reason for cancellation. In some cases, this text is user-provided.
* ``CancellationTime`` – The time at which the cancellation takes effect. For cancellation at renewal, this is the subscription end time.

.. note::
    When a subscription is cancelled, proration policies determine whether subscribers are credited for unused time or charged for invoiced periods. 
    See :ref:`Proration Policies for Cancellations <proration-policies>` for detailed information on how cancellation proration works.

Example Use Case
~~~~~~~~~~~~~~~~
Similar to ``SubscriptionCreated``, the ``SubscriptionCancelled`` event may be used to keep external system in sync.

* Automated 'Sorry to see you go' emails.
* Automated offers to save the customer.
* Automated transfer to external debt collection (Payment Stops).

.. _subscription-cancellation-removed-event:

Event: com.info-subscription.SubscriptionCancellationRemoved
------------------------------------------------------------
The external ``SubscriptionCancellationRemoved`` event signals that a registered cancellation has been removed. It applies to both ordinary and scheduled cancellations.

Subscription Identifiers
~~~~~~~~~~~~~~~~~~~~~~~~

* ``SubscriberId`` – Identifies the subscriber.
* ``SubscriptionId`` – Identifies the subscription whose cancellation was removed.
* ``OrganizationId`` – Identifies the organization.

Example Use Case
~~~~~~~~~~~~~~~~
Use this event to clear cancellation indicators in external systems or stop cancellation-related communications. It is not a subscription activation event.