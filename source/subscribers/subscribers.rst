.. _subscribers:

***********
Subscribers
***********

In |projectName| subscribers serves as the entity which own subscriptions. They are abstract entities, where the only purpose is a unified identification mechanism.
A subscriber may be a person, a company, a government, a computer, a pidgeon or whatever else you can imagine, as long as you can imagine that it can subscribe to one of the configured subscription plans.

Subscriber Identity (Identifiers)
=================================
Subscribers have two identifiers, one internal UUID/GUID and one external human-readable running number called the subscriber number. 

Optionally a subscriber may have an external Id, this is useful to map between |projectName| and external systems.

Unlike a subscription, a customer is never associated with an :term:`organization` and is considered global. 
Keep this in mind if you have to decide on having one or multiple tenants.

Subscriber Contacts
===================
While subscribers may be anything, contacts are considered entities with a name and an address. Typically a private customer would have a single primary contact, which is him/herself.
A company will have one or more contacts responsible for managing and/or paying for subscriptions.

The contact information is used when issuing Invoices, and in some cases as the basis of delivery information for distribution of physical goods.

Customizable Subscriber Number
==============================
By default the subscriber number is generated from an internal sequence provided by |projectName|.

In some cases it may be desirable to use externally assigned numbers, typically the case where external CRM systems have numeric identifiers, or multiple subscription systems are in use.

Internal subscriber number generation can be toggled off, see to the :api-ref:`refence docs </SubscriberConfiguration/SubscriberConfigurationPost>` for details.

.. Note ::

    Toggling off the number generation requires that an external system provides the subscriber number, as this is a required field.

.. Warning ::

    Switching back and forth between internal and external subscriber number configuration 
    may lead to weird issues as the internal number generator only knows the numbers it has generated.