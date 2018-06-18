.. _events:

*******************
Events and Webhooks
*******************

Events describe things that has occured inside |projectName| and can be used by a client to react to these changes.

Webhooks are the mechanism used for notifying clients about the various events and at its simplest 
it is just a ``POST`` request with a payload.

When an event is triggered the system will send an event to all registered webhooks with a payload describing the event.

.. Note::

    Typically when an endpoint is configured to receive events, the terminology used would be that the endpoint *subscribes* to the event and that configuration would be denoted a *subscription*.

    In an attempt to avoid confusion with the subscriptions provided by |projectName|, the documentation will use a slightly different terminology, replacing *subscribe* with **receive**, and *subscription* with **registration** or **webhook**.

Enabling Webhook Event Notifications
====================================
Since not everyone needs event notifications the infrastructure required is not enabled by default on a tenant.

Enabling notifications is a one time operation, and there is currently no way to disable it (don't worry its not dangerous :))

There are two ways to enable event notifications:

1. Press a button in the Administrative UI
2. Use the Notifications API with an empty ``POST`` request

Deploying the infrastructure takes a few minutes, so go ahead and grab a cup of coffee and it will probably be done by the time you get back.

Registering webhooks
====================
A client may receive events by registering one or more endpoints with the tenant.
Each endpoint must specify one or more events to be received.

You can create as many registrations as you want, and one event can go to multiple registrations.

It is recommended that you have one registration per endpoint.
In case you want multiple events for a given endpoint, just specify multiple events - it is possible to update them later on.

.. Important::

    Webhooks requires ``HTTPS`` endpoints. 
    
    `Let's Encrypt <https://letsencrypt.org/>`_ makes certificate handling easy, so there are no excuses!

Webhook Validation Handshake
----------------------------
Behind the scenes |projectName| use Azure Event Grid for the actual event delivery, which requires a validation procedure.
This validation procedure is to make sure you actually own the endpoint you are registering.

If you are familiar with `Azure Event Grid and its validations <https://aka.ms/esvalidation>`_, just do what you normally do, otherwise read on.

At the time of registration as special "validation event" is sent to the endpoint. It looks like any other event, but the content contains a ``validationCode`` property.

The application should verify that this is indeed something it wants to handle and respond with a simple json object containing the validationCode in the ``validationResponse`` property.

The following is a complete example of the validation event, note the ``eventType`` and the content of the ``data`` property.

.. code-block:: json
    :caption: Validation Event
    :name: Validation Event Example

    [{
    "id": "2d1781af-3a4c-4d7c-bd0c-e34b19da4e66",
    "topic": "/subscriptions/xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx",
    "subject": "",
    "data": {
        "validationCode": "512d38b6-c7b8-40c8-89fe-f46f9e9622b6",
        "validationUrl": "https://rp-eastus2.eventgrid.azure.net:553/eventsubscriptions/estest/validate?id=B2E34264-7D71-453A-B5FB-B62D0FDC85EE&t=2018-04-26T20:30:54.4538837Z&apiVersion=2018-05-01-preview&token=1BNqCxBBSSE9OnNSfZM4%2b5H9zDegKMY6uJ%2fO2DFRkwQ%3d"
    },
    "eventType": "Microsoft.EventGrid.SubscriptionValidationEvent",
    "eventTime": "2018-01-25T22:12:19.4556811Z",
    "metadataVersion": "1",
    "dataVersion": "1"
    }]


The following is an example of an "approved" response to the above validation event

.. code-block:: json
    :caption: Validation Response
    :name: Validation Response Example

    {
        "validationResponse": "512d38b6-c7b8-40c8-89fe-f46f9e9622b6"
    }

Manual Handshake
~~~~~~~~~~~~~~~~
If you do not have total control over the webhook, validation using the handshake may be hard or imposible,
typically the case when you use a third party integration service such as Zapier, IFTTT or even Microsoft's own Flow.

For these scenarios you can configure the webhook such that you get the event data, and a ``validationUrl`` is included. 
A manual ``GET`` request (i.e. copy/paste to your favorite browser) will then approve the endpoint.

The URL is valid for 10 minutes after registration has started.

Direct Event Grid integration
-----------------------------
If you are using Azure services or use products with some sort of event grid integration built in, things are a lot easier with direct access to the event grid resources.

While not an out-of-the-box experience, we might be able to work something out for your particular needs, so please contact support and we will have a look.


Events Schema and Payload
=========================
All events follow a common schema with some "global" properties.

The following is the json schema for an event

.. code-block:: json
    :name: Event Schema

    [{
        "topic": string,
        "subject": string,
        "id": string,
        "eventType": string,
        "eventTime": string,
        "data":{
        object-unique-to-each-publisher
        },
        "dataVersion": string,
        "metadataVersion": string
    }]

The table is a short description of each property.

+-----------------+--------+------------------------------------------------------+
| Property        | Type   | Description                                          |
+-----------------+--------+------------------------------------------------------+
| topic           | string | Full resource path to the event source.              |
+-----------------+--------+------------------------------------------------------+
| subject         | string | Publisher-defined path to the event subject.         |
|                 |        | Subject means what the event concerns not the title. |
+-----------------+--------+------------------------------------------------------+
| eventType       | string | Defines the type of the data                         |
+-----------------+--------+------------------------------------------------------+
| eventTime       | string | The time the event is generated in UTC               |
+-----------------+--------+------------------------------------------------------+
| id              | string |                                                      |
|                 |        | Unique identifier for the event                      |
+-----------------+--------+------------------------------------------------------+
| data            | object | Event data specific for the given eventType          |
+-----------------+--------+------------------------------------------------------+
| dataVersion     | string | The schema version of the data object                |
+-----------------+--------+------------------------------------------------------+
| metadataVersion | string | The schema version of the event metadata.            |
|                 |        | Event metadata being the properties described here   |
+-----------------+--------+------------------------------------------------------+

Event Data
----------
Each event contains a property ``data`` this data property is essentially the event content that is interesting.
It is a ``JSON`` object, and the ``eventType`` property describes which object instance it is.

To learn more about the available events and what data they contain see the `API Reference <https://api.info-subscription.com/swagger/#/>`_ in the Models section.

Each event has a typename in the following format ``com.info-subscription.{eventName}``, so the ``SubscriptionCancelled`` event would be ``com.info-subscription.SubscriptionCancelled``.

Events Philosophy
=================
There are a few different approaches to take when designing events. This section attempts to clarify some of our reasoning, you might not agree, but atleast you will know why. 

Lightweight Payload
-------------------
We strive to follow a philosophy of lightweight event payload with only the minimum of information needed to make the event sensible, while also providing key information to query for details.

The reasoning behind this is that event occurrence in itself, together with the subject, is often enough to react to a given event without any futher information.
For instance the ``SubscriptionCancelled`` event contains the ``SubscriptionId`` and the ``SubscriberId``, the first being the subject of the event, i.e. which subscription was cancelled.
The later is such a common additional piece of information that describes the owner, so it is included as well.

The fact that a subscription was cancelled, and which one it was, is enough to remove access to a web page, or send an "Sorry to see you go" email, or any other number of actions.

In some cases the receiving application might want more data, in which case the API can be queried using the ``SubscriptionId`` or the ``SubscriberId``.

Keeping the events lightweight, makes it simpler for us to deliver the events as fast as possible.

Registration for specific events
--------------------------------
Often a receiving application will only care about a handful of events, and it will have to discard the rest.

Since events which are just discarded is a waste of bandwidth and processing time, each webhook registration must specify which events it wants.

For the few applications that handles many events in a single endpoint, there is a performance consideration to make. 
Perhaps the endpoint is perfectly capable of handling todays events, but then we add another event to |projectName| and all of a sudden no events are properly handled because the endpoint it overwhelmed.
By not allowing for wildcard/all type event registrations, we help alleviate that problem and reduce stress on your application as well as on the |projectName| infrastructure.

By no means are these considerations enough to handle all issues, but it helps - and it is not immensly annoying or troublesome for any of the involved parties.

Event Delivery
==============
Since |projectName| relies on Azure Event Grid for event delivery, the delivery rules/details are defined by Event Grid.
The following is a short summary of those details, for the full information please refer to https://docs.microsoft.com/en-us/azure/event-grid/delivery-and-retry

Event Grid provides durable delivery, which basically means it will retry if it did not get a proper response from the endpoint.

Success Codes are defined as

* 200 OK
* 202 Accepted

Failure to respond within 50 seconds will be counted as a delivery failure, and typical HTTP error codes such as 400, 404, 500 and 503 will also mark the delivery as failed.

If a delivery has failed it will be retried according to the following "timetable"

#. 10 seconds
#. 30 seconds
#. 1 minute
#. 5 minutes
#. 10 minutes
#. 30 minutes
#. 1 hour
#. Every hour untill 24 hours

After 24 hours, the event is considered lost and no futher attempts are made.

Security/Authentication
-----------------------
Once a registration has been created, there is currently no built security mechanism such as an API key or HMAC to verify the validity of the content.

You can append a secret as a query parameter when creating the webhook registration which will then be sent with every request if the event originates from |projectName|.