.. _order-processed-event:

Event: com.info-subscription.OrderProcessed
-------------------------------------------
Once an order is completed and processed an event is triggered called ``OrderProcessed``. 
This indicates that the platform has accepted the order and the Subscription should start as expected.

Orders can be registered via the Salesposter, the Merchant UI or a custom solution using the Orders endpoint in the API.

The event contains a few minimal key points about the order, as well as an indicator about whether the system has finished creating the first subscription period at the time of the event triggering.


Example Use Case
~~~~~~~~~~~~~~~~
The ``OrderProcessed`` event may be used to start up dialog with the Subscriber in a Welcome email, or to build up real time statistics of sales.

Other uses cases includes handing off initial distribution information such as a startup one-off delivery, typical for ISPs and Cable operators where some hardware is required to get started.