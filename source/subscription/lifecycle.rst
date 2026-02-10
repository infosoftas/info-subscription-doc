.. _subscription-lifecycle:

**************************
Subscription Lifecycle
**************************

Understanding the subscription lifecycle is essential for integrators working with |projectName|. This guide explains how subscriptions are created, renewed, and eventually terminated, clarifying the relationships between key entities and the recurring nature of subscription-based billing.

Overview
========

A **subscription** represents an ongoing agreement between a subscriber and an organization to deliver products or services over time. Unlike a one-time purchase, a subscription consists of multiple sequential **subscription periods**, each representing a distinct time interval during which the service is provided.

Most subscriptions in |projectName| follow this lifecycle:

1. **Creation** – A subscription begins, typically through an :ref:`order <subscription-orders>`
2. **Active Periods** – The subscription generates recurring subscription periods (renewals) at regular intervals
3. **Billing** – Each subscription period triggers a :ref:`billing cycle <billing-cycle>`
4. **Termination** – Eventually, the subscription is cancelled and no further periods are created

.. important::
    A critical concept in |projectName| is that **each subscription period is technically a separate subscription entity** in the system. When we talk about "subscription renewal," we're actually creating a new subscription record that continues from where the previous one ended. This design allows for precise tracking of billing, service delivery, and state changes over time.


Key Terminology
===============

Before diving into the lifecycle details, it's important to understand the key entities and their relationships:

**Subscriber**
    The entity (person or organization) who owns and is financially responsible for subscriptions. For the complete definition, see the :ref:`terminology <terminology>` section.

**Subscriber Contact**
    Contact information associated with a subscriber, such as billing addresses, delivery addresses, or alternate contacts. A subscriber may have multiple contacts. See ``SubscriberContacts`` in :ref:`reporting datamodel <reporting-datamodel>`.

**Subscriber Account** (also **Subscriber Billing Account**)
    The financial account under which a subscriber's transactions, charges, and payments are tracked. See :term:`Subscriber Account` in :ref:`terminology <terminology>`.

**Order**
    A workflow that encapsulates the steps required to create a new subscription, including payment registration, plan selection, and subscription activation. See :ref:`Creating New Subscriptions Using Orders <subscription-orders>`.

**Subscription**
    A time-bound agreement to provide products/services. In |projectName|, each billing period creates a new subscription record that is part of a logical subscription chain. See the :ref:`terminology <terminology>` section for the formal definition.

**Subscription Plan** (also **Package**)
    The set of rules governing a subscription, including pricing, products included, billing frequency, and renewal terms. Created from a Template Subscription Plan during order processing. See :ref:`Plans and Template Plans <plans>` and the :ref:`terminology <terminology>` section.

**Template Subscription Plan** (also **Template Package**)
    A reusable template that defines the default configuration for subscription plans, used during order creation to generate concrete subscription plans. See :ref:`subscriptionplan-templates <subscriptionplan-templates>` and the :ref:`terminology <terminology>` section.

**Subscription Period**
    A specific time interval within the subscription lifecycle (e.g., one month, one year). Each period is represented as a separate subscription entity in the system.


The Subscription Lifecycle Timeline
====================================

The following diagram illustrates a typical subscription lifecycle spanning multiple periods. This example shows:

- **Initial creation** via an order
- **Five subscription periods** (representing renewals)
- **Key billing events** for each period
- **Final cancellation** of the subscription

.. mermaid::

    gantt
        title Subscription Lifecycle with Multiple Periods
        dateFormat  YYYY-MM-DD
        
        section Order & Creation
            Order Placed & Completed   :milestone, order, 2025-01-15, 0d
            
        section Period 1
            Subscription Period 1   :active, period1, 2025-01-15, 15d
            Invoice Issued (Period 1)   :milestone, inv1, 2025-01-15, 0d
            Payment Due (Period 1)   :crit, due1, 2025-01-15, 1d
            
        section Period 2
            Subscription Period 2 (Renewal)   :active, period2, 2025-01-30, 30d
            Invoice Issued (Period 2)   :milestone, inv2, 2025-01-15, 0d
            Payment Due (Period 2)   :crit, due2, 2025-01-30, 1d
            
        section Period 3
            Subscription Period 3 (Renewal)   :active, period3, 2025-03-01, 30d
            Invoice Issued (Period 3)   :milestone, inv3, 2025-02-14, 0d
            Payment Due (Period 3)   :crit, due3, 2025-03-01, 1d
            
        section Period 4
            Subscription Period 4 (Renewal)   :active, period4, 2025-03-31, 30d
            Invoice Issued (Period 4)   :milestone, inv4, 2025-03-16, 0d
            Payment Due (Period 4)   :crit, due4, 2025-03-31, 1d
            
        section Period 5
            Subscription Period 5 (Renewal)   :active, period5, 2025-04-30, 30d
            Invoice Issued (Period 5)   :milestone, inv5, 2025-04-15, 0d
            Payment Due (Period 5)   :crit, due5, 2025-04-30, 1d
            
        section Period 6
            Subscription Period 6 (Renewal)   :active, period6, 2025-05-30, 15d
            Invoice Issued (Period 6)   :milestone, inv6, 2025-05-15, 0d
            Payment Due (Period 6)   :crit, due6, 2025-05-30, 1d
            Subscription Cancelled   :milestone, cancel, 2025-06-14, 0d

.. note::
    This is a simplified timeline. The first subscription period is often invoiced at order completion, which may coincide with the period start date in the diagram. For **renewal** periods, billing events typically occur **before** the subscription period starts due to the :ref:`in-advance billing model <in-advance-billing>`. Invoices are usually issued 15-30 days before the period begins, depending on the billing plan's "minimum due days" configuration.


Detailed Lifecycle Stages
==========================

1. Subscription Creation via Order
-----------------------------------

Most subscriptions begin with an :ref:`order <subscription-orders>`. The order workflow handles:

- **Subscriber identification or creation** – Establishing who is subscribing
- **Plan selection** – Choosing a :ref:`Template Subscription Plan <subscriptionplan-templates>` and any customizations
- **Payment agreement registration** – Setting up payment methods (credit card, direct debit, invoice, etc.)
- **Subscription activation** – Creating the first subscription period

**Key API Interactions:**

- :api-ref:`Create Order </Order/post_Order>` – Initialize the order
- :api-ref:`Complete Order </Order/post_Order__orderId__complete>` – Finalize and activate the subscription

**Events Triggered:**

- ``OrderProcessed`` – Fired when an order is completed
- :ref:`SubscriptionCreated <subscription-created-event>` – Fired when the first subscription period is created

The completed order produces:

- A **Subscriber** (if one didn't already exist)
- A **Subscription** entity representing the first period
- A **Subscription Plan** instance derived from the template
- A **Billing cycle** that begins immediately (see next section)

.. tip::
    While it's possible to create subscriptions without using orders, we strongly recommend using the order workflow for consistency, error handling, and automatic invoice generation.


2. Billing Cycle Initiation
----------------------------

As soon as a subscription period is created (whether the initial period or a renewal), a :ref:`billing cycle <billing-cycle>` is automatically triggered. The billing system:

1. **Schedules the payment demand** – Determines when to issue the invoice based on the :ref:`in-advance billing model <in-advance-billing>`
2. **Issues the invoice** – Generates an invoice for the subscription period, typically 15-30 days before the period starts
3. **Processes payment requests** – For integrated payment providers (e.g., AvtaleGiro, SwedbankPay), payment collection is initiated
4. **Handles payment outcomes** – Records successful payments or initiates dunning processes (reminders, cancellations) for failed payments

**Key Point:** Each subscription period has its own independent billing cycle. Multiple billing cycles often overlap because payments may not settle immediately.

For complete details on billing stages, payment processing, and dunning, see the :ref:`Billing Overview <billing-cycle>`.


3. Subscription Renewals
-------------------------

At the end of each subscription period, |projectName| automatically generates a new subscription period (a "renewal") based on the subscription plan's renewal rules. This renewal is **not** a modification of the existing subscription—it's the creation of a **new subscription entity** that continues the logical subscription chain.

**Renewal Process:**

1. The current subscription period reaches its end date
2. |projectName| creates a new subscription with:

   - The same subscriber
   - The same (or updated) subscription plan
   - A new start date (typically the day after the previous period ended)
   - A new billing cycle

3. A :ref:`SubscriptionCreated <subscription-created-event>` event is fired
4. The billing cycle for the new period begins immediately

**Subscription Plan Changes:**

Renewals can also incorporate :ref:`plan changes <subscription-plan-changes>` (upgrades or downgrades) scheduled to take effect at renewal time. When a plan change occurs:

- The new subscription period uses the updated plan
- Proration adjustments are applied as needed
- Outstanding charges/allowances are transferred to the new subscription

**API Reference:**

While renewals typically happen automatically, you can also:

- :api-ref:`View upcoming renewals </Subscription/get_Subscription_scheduled>` – See scheduled subscription periods
- :api-ref:`Schedule plan changes </Subscription/post_Subscription__subscriptionId__scheduledchange>` – Modify the plan for the next renewal


4. Active Subscription Management
----------------------------------

While a subscription is active, various management operations are available:

**Plan Changes (Upgrades/Downgrades)**

Change the subscription plan either immediately or at the next renewal. See :ref:`Subscription Plan Changes <subscription-plan-changes>`.

- **Immediate changes** – Cancel the current period and create a new one with the updated plan
- **Scheduled changes** – Apply the change at the next renewal

**Pausing Subscriptions**

Temporarily halt service delivery and billing. Implemented as a cancellation followed by a scheduled reactivation.

**Adding Products**

Dynamically add one-time or recurring products to a subscription. See :ref:`Additional Products <additional-products>`.

**Payment Method Updates**

Update payment agreements or switch payment providers without cancelling the subscription.


5. Subscription Cancellation
----------------------------

Subscriptions can be cancelled for several reasons:

- **User-initiated** – Subscriber or merchant cancels via API or self-service portal
- **Payment failure** – Automatic cancellation after dunning processes exhaust all reminders
- **Plan rules** – Subscription plans with ``automaticStop`` set to true cancel after the current period
- **System events** – Administrative actions or plan changes

**Cancellation Timing:**

Cancellations can be:

- **Immediate** – The subscription ends right away, and proration may apply
- **End of period** – The subscription continues until the current period ends, then stops

**API Reference:**

- :api-ref:`Cancel Subscription </Subscription/post_Subscription__subscriptionId__cancel>` – End a subscription

**Events Triggered:**

- :ref:`SubscriptionCancelled <subscription-cancelled-event>` – Fired when cancellation is registered
- :ref:`SubscriptionDeactivated <subscription-deactivated-event>` – Fired when the cancellation takes effect

**What Happens After Cancellation:**

- No further subscription periods (renewals) are created
- Any outstanding payment demands remain in the billing system
- Proration policies determine whether subscribers receive credits for unused time (see :ref:`Proration Policies <proration-policies>`)


Subscription States and Transitions
====================================

Each subscription period has a lifecycle state that tracks its current status:

- **Active** – The subscription period is currently in effect and service is being delivered
- **Pending** – The subscription period is scheduled but hasn't started yet
- **Cancelled** – The subscription has been cancelled and will not renew
- **Completed** – The subscription period has ended and a renewal was created (or the subscription was cancelled)

The following state diagram illustrates the possible transitions:

.. mermaid::

    stateDiagram-v2
        [*] --> Pending: Subscription Created
        Pending --> Active: Period Start Time Reached
        Active --> Completed: Period Ends + Renewal Created
        Active --> Cancelled: Cancellation Requested
        Pending --> Cancelled: Cancellation Before Start
        Cancelled --> [*]
        Completed --> [*]

.. note::
    This is a simplified view. The actual subscription lifecycle may include additional states and transitions depending on plan changes, pauses, and other operations.


Integration Points for Developers
==================================

When building integrations with |projectName|, consider these key touchpoints in the subscription lifecycle:

Webhooks and Events
-------------------

Subscribe to relevant events to stay synchronized with subscription state changes:

- :ref:`SubscriptionCreated <subscription-created-event>` – Monitor new periods and renewals
- :ref:`SubscriptionCancelled <subscription-cancelled-event>` – Handle cancellation registration
- :ref:`SubscriptionDeactivated <subscription-deactivated-event>` – React when cancellation takes effect
- ``OrderProcessed`` – Track initial subscription creation from orders

See the :ref:`Events and Webhooks <events>` section for implementation details.

Reporting and Analytics
-----------------------

The :ref:`reporting datamodel <reporting-datamodel>` provides comprehensive access to subscription and billing data:

- **Subscriptions** – View all subscription periods and their relationships
- **PaymentDemands** – Track billing for each subscription period
- **Invoices** – Monitor invoice state and settlement
- **Subscribers** – Access subscriber and contact information

Use :doc:`OData querying <../reporting-analytics/odata-primer>` to build custom reports and dashboards.

API Endpoints
-------------

Key API endpoints for subscription lifecycle management:

- :api-ref:`List Subscriptions </Subscription/get_Subscription>` – Retrieve active and historical subscriptions
- :api-ref:`Get Subscription Details </Subscription/get_Subscription__subscriptionId_>` – View a specific subscription period
- :api-ref:`View Scheduled Subscriptions </Subscription/get_Subscription_scheduled>` – See upcoming renewals
- :api-ref:`Cancel Subscription </Subscription/post_Subscription__subscriptionId__cancel>` – End a subscription
- :api-ref:`Schedule Plan Change </Subscription/post_Subscription__subscriptionId__scheduledchange>` – Modify future renewals

For a complete API reference, visit the `Swagger UI <https://api.info-subscription.com/swagger/>`_.


Common Scenarios and Best Practices
====================================

Tracking a Subscriber's Full Subscription History
--------------------------------------------------

To view all subscription periods for a given subscriber (across renewals):

1. Query the :api-ref:`Subscriptions endpoint </Subscription/get_Subscription>` filtering by ``subscriberId``
2. Use the ``startTime`` and ``endTime`` fields to reconstruct the timeline
3. Link subscription periods using the ``subscriberAccountId`` to track the logical subscription chain

Handling Payment Failures
--------------------------

When payment processing fails:

1. The billing cycle enters the :ref:`dunning process <billing-cycle>`, issuing reminders
2. Subscribe to billing and payment events to stay informed of payment status
3. After exhausting reminders, the system may automatically cancel the subscription
4. Use the :ref:`SubscriptionCancelled <subscription-cancelled-event>` event to trigger follow-up actions (e.g., service revocation)

Offering Upgrades and Downgrades
---------------------------------

Allow subscribers to change their plan:

1. Present available plans to the subscriber (e.g., via self-service portal)
2. Use :api-ref:`Schedule Plan Change </Subscription/post_Subscription__subscriptionId__scheduledchange>` to apply the change immediately or at renewal
3. |projectName| handles proration, billing adjustments, and subscription period creation automatically

Preventing Automatic Renewals
------------------------------

For limited-time subscriptions (e.g., trial periods, seasonal offers):

- Set ``automaticStop`` to ``true`` in the subscription plan
- The subscription will not renew after the current period ends
- Subscribers can manually renew or resubscribe if desired


Summary
=======

The subscription lifecycle in |projectName| is designed around the concept of **recurring subscription periods**, with each period represented as a separate subscription entity. Understanding this model is key to successful integration:

- **Subscriptions start** with an :ref:`order <subscription-orders>` that creates the first period
- **Renewals create new subscription periods** automatically at regular intervals
- **Each period triggers its own billing cycle**, operating independently but overlapping with others
- **Cancellations stop renewals**, but existing periods and billing cycles continue until resolved
- **Events and APIs** provide rich integration points for tracking and managing the lifecycle

By leveraging the order workflow, subscription events, and billing automation, you can build robust integrations that seamlessly handle the full subscription lifecycle from creation to cancellation.

**Next Steps:**

- Learn how to create subscriptions: :ref:`Creating New Subscriptions Using Orders <subscription-orders>`
- Understand billing automation: :ref:`Billing Overview <billing-cycle>`
- Explore plan management: :ref:`Plans and Template Plans <plans>`
- Implement event-driven integrations: :ref:`Events and Webhooks <events>`
- Access subscription data: :ref:`Reporting and Analytics <reporting-intro>`
