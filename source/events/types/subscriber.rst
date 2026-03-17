.. _subscriber-created-event:

Event: com.info-subscription.SubscriberCreated
----------------------------------------------
Not suprisingly, whenever a new Subscriber is created, it triggers an event ``SubscriberCreated``.

There are multiple sources for new Subscribers, but most typically it is done during registration of new Orders.

The event contains the SubscriberId an optional ExternalId and the Subscriber Number (whether its generated or externally defined).

Example Use cases
~~~~~~~~~~~~~~~~~

The related events for Subscriber and Subscriber Contact may typically be used to synchronize with external CRM, Datalakes, Datawarehouses or similar.
Mapping and correlation with other sources may be done via the External Id or via the Subscriber Number depending on the design.

If done properly, such a synchronization opens up multiple use cases such as, customer segmentation, marketing/campaign analysis, reporting, visualization, customer communication etc.

.. _subscriber-deleted-event:

Event: com.info-subscription.SubscriberDeleted
----------------------------------------------
When a Subscriber is deleted from the system, a ``SubscriberDeleted`` event is triggered.

The event contains the SubscriberId of the deleted subscriber.

.. _subscriber-contact-created-event:

Event: com.info-subscription.SubscriberContactCreated
-----------------------------------------------------
Whenever a new contact is added to a Subscriber, a ``SubscriberContactCreated`` event is triggered.

Subscriber contacts represent the contact information tied to a subscriber, such as a postal or email address.
The event includes both the SubscriberId and the ContactId, as well as whether it is the primary contact and the source of the contact information.

.. _subscriber-contact-updated-event:

Event: com.info-subscription.SubscriberContactUpdated
-----------------------------------------------------
When the details of a Subscriber contact are changed, a ``SubscriberContactUpdated`` event is triggered.

Similar to ``SubscriberContactCreated``, the event includes the SubscriberId, the ContactId, whether it is the primary contact, and the source.

.. _subscriber-contact-deleted-event:

Event: com.info-subscription.SubscriberContactDeleted
-----------------------------------------------------
When a contact is removed from a Subscriber, a ``SubscriberContactDeleted`` event is triggered.

The event contains the SubscriberId and the ContactId of the removed contact.
