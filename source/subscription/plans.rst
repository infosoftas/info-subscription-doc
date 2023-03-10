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
To help alleviate some of the construction pains of building plans, |projectName| has a concept of :api-ref:`template plans <Package>`

As the name suggests, the template plan is a template with a series of predefined settings that a subscription will use for its plan.
When placing a new :ref:`order <subscription-orders>` a template is referred for the various defaults, and possibly some choices that override those defaults or specify a selection.

The template and the choices together form a plan instance, a Subscription Plan, which is associated with the created subscription.
When created the subscription plan does not refer back to the template and the template can be changed at will without affecting the instance on the subscription.

For more details on choices during orders refer to the  :ref:`order section <subscription-orders>`.

.. _subscription-plan-changes:

Subscription Plan Changes (Upgrades and Downgrades)
===================================================
Most subscription business models contains the option to switch between plans, either as an upgrade (typically a more costly product), or as a downgrade (a less costly product).

|projectName| supports upgrades and downgrades through Subscription Plan changes. 

.. note:: 
    
    There is no logical concept of an upgrade or a downgrade, the definition of whether a change is an upgrade or a downgrade is left to the client.

Doing a plan change is simple as:

1. Determine the `SubscriptionId` to change.
2. Determine/Build the SubscriptionPlan to change into (refer to Orders for details on Plan Choices)
3. :api-ref:`Schedule the change <post_Subscription__subscriptionId__scheduledchange>` 

A change is defined with a pocessing type, denoting when the change should be carried out.

#. Immediately - Process now
#. OnScheduledTime - Process at the defined time
#. OnRenewal - Process when the subscription is renewed next

Immediate Changes
-----------------
Immediate changes are carried out at once, with no options for regret other than somehow creating compensating transactions.

Essentially an Immediate change means the current subscription is cancelled now, and a new one is generated with the new parameters.
Outstanding allowances or charges are transferred to the new subscription and the current time period is prorated according to the billing configuration.

Changes On Scheduled Time
-------------------------
Scheduled changes are carried out around the time supplied with the change request. Very similar to Immediate changes.

Any proration happens at the time of the execution of the schedule, and not at the time of registration.

Mostly useful for scenarios where the is a fixed delay related to the desired change. That might be a planned summertime product downgrade for instance.

Scheduled changes can be revoked by deleting them before they are executed.

On Renewal Changes
------------------
Changes scheduled for the renewal are a bit different from the other two types.

When a subscription is billed, changes registered for renewal are planned into the billing flow entirely, and the running subscription is never cancelled, nor does any proration occur.

Changes are effective on the next subscription and automatically associated with the renewal process.

This is useful for business models operating with entire periods for downgrades and other similar non-cost related changes.
