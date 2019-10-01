.. _plans:

************************
Plans and Template Plans
************************
An important concept for all subscriptions are the notion of a plan.
At its core, the plan is the content of the contract between the subscriber and the organization, while the subscription is the timeline.
The plan encapsulates things such as the agreed price, the products that are included, and the billing frequency.

.. Note::

    For historical reasons there are some terminology confusion regarding plans. 
    The API use the terms ``package`` and ``template package`` to denote plans and template plans. 
    All places where the API mentions a package, it is in fact a reference to a plan.


Templates, Choices and Subscription Plans (Instances)
=====================================================
All subscriptions needs to be assigned a plan that determines its contract/rules. 
To help alleviate some of the construction pains of building plans, |projectName| has a concept of :api-ref:`template plans </Package>`

As the name suggests, the template plan is a template with a series of predefined settings that a subscription will use for its plan.
When placing a new :ref:`order <subscription-orders>` a template is referred for the various defaults, and possibly some choices that override those defaults or specify a selection.

The template and the choices together form a plan instance, a Subscription Plan, which is associated with the created subscription.
When created the subscription plan does not refer back to the template and the template can be changed at will without affecting the instance on the subscription.

For more details on choices during orders refer to the  :ref:`order section <subscription-orders>`.