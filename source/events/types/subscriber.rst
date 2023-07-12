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

Related events: 

 * ``com.info-subscription.SubscriberDeleted``
 * ``com.info-subscription.SubscriberContactCreated``
 * ``com.info-subscription.SubscriberContactUpdated``
 * ``com.info-subscription.SubscriberContactDeleted``
