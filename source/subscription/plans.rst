.. _plans:

************************
Plans and Template Plans
************************

An important concept for all subscriptions is the notion of a subscription plan.
At its core, the subscription plan is the content of the contract between the subscriber and the organization, while the subscription is the timeline.
The subscription plan encapsulates things such as the agreed price, the products that are included, and the billing frequency.

.. Note::

    For historical reasons, there is some terminology confusion regarding plans. 
    The API uses the terms ``package`` and ``template package`` to denote plans and template plans. 
    All places where the API mentions a package, it is in fact a reference to a subscription plan.


The following is a `simplified` class diagram that illustrates the relationships between the various components of a subscription plan:

.. mermaid:: subscriptionpackage-class.mmd
    :align: center
    :alt: Class diagram of SubscriptionPlan (SubscriptionPackageView)

Permanent Discount
------------------
The ``permanentDiscount`` property allows you to define a discount that is always applied to the subscription plan. 
This is currently defined as a a percentage.
This is currently defined as a percentage.
Permanent discounts are useful for loyalty programs, negotiated rates, or long-term customer incentives. 
The discount is automatically factored into the price calculation for the subscription based on the full price.

Automatic Stop
--------------
The ``automaticStop`` property is a boolean flag that, when set to true, causes the subscription to automatically end (stop) after the current term or period completes. 
This is useful for limited-time offers, trial periods, or subscriptions that should not auto-renew. 
When enabled, the system will not renew the subscription beyond the defined term, and the subscriber will need to take action to continue the service.


.. _subscriptionplan-templates:

Templates, Choices and Subscription Plans (Instances)
=====================================================

All subscriptions needs to be assigned a plan that determines its contract/rules. 
To help alleviate some of the construction pains of building plans, |projectName| has a concept of :api-ref:`template plans <Package>`

As the name suggests, the template plan is a template with a series of predefined settings that a subscription will use for its plan.
When placing a new :ref:`order <subscription-orders>` a template is referred for the various defaults, and possibly some choices that override those defaults or specify a selection.

The template and the choices together form a plan instance, a Subscription Plan, which is associated with the created subscription.
When created the subscription plan does not refer back to the template and the template can be changed at will without affecting the instance on the subscription.


The following diagram attempts to visualize how the order, template package, and choices are combined into a single subscription package.

.. mermaid:: subscriptionplan-merge.mmd
    :align: center
    :alt: Diagram showing how order, template package, and choices merge into a subscription package

1. **OrderCreate**: The client sends an order request, specifying which template package to use and providing any choices (such as selected products, billing frequency, or other allowed customizations).
2. **TemplatePackage**: The template package defines the available options and default configuration for the subscription plan.
3. **Choices (TemplatePackageChoices)**: The order may include choices that override or specify options within the template package (e.g., which products to include, billing plan, number of units, etc.).
4. **Merge**: All inputs are merged together, combining their data and rules.
5. **SubscriptionPackage**: The result is a concrete subscription package instance, ready for use in the new subscription.

The same principles apply when changing subscription plans on a running subscription (upgrades and downgrades).

.. _subscription-plan-changes:

Subscription Plan Changes (Upgrades and Downgrades)
===================================================
Most subscription business models contains the option to switch between plans, either as an upgrade (typically a more costly product), or as a downgrade (a less costly product).

|projectName| supports upgrades and downgrades through Subscription Plan changes, and handles proration automatically.

.. note:: 
    
    There is no logical concept of an upgrade or a downgrade, the definition of whether a change is an upgrade or a downgrade is left to the client.

Doing a plan change is simple as:

1. Determine the `SubscriptionId` to change.
2. Determine/Build the SubscriptionPlan to change into (refer to Orders for details on Plan Choices)
3. :api-ref:`Schedule the change </Subscription/post_Subscription__subscriptionId__scheduledchange>` 

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

.. _subscription-plan-chaining:

Subscription Plan Chaining (Package Chains)
===========================================
Some subscription scenarios require a sequence of planned changes to the subscription plan over time. This is often used for introductory offers, stepwise price increases, or staged product upgrades. In |projectName|, this is handled through **chaining** (also known as package chains).

What is Chaining?
-----------------
A package chain is a predefined sequence of subscription plans (packages) that a subscription will follow over its lifecycle. Each step in the chain defines the plan (and price, products, or rules) that will be active for a given period. When the current step ends (typically at renewal), the subscription automatically advances to the next step in the chain.

**Common use cases:**

- Introductory pricing (e.g., 1 month at 99, then 3 months at 149, then 199/month)
- Stepwise upgrades or downgrades
- Promotional periods followed by regular pricing

How It Works
------------
1. **Template Package Chain Definition:**
    - In the API, a template package (plan) can define a `PackageChain` (see the ``packageChainId`` or ``subscriptionPackageChainId`` fields in the API schema).
    - The chain consists of one or more steps, each referencing a template package and a duration (based on the billing plan).
    - Example: Step 1: "Intro Offer" (1 month), Step 2: "Standard" (11 months), Step 3: "Full Price" (indefinite).

2. **Order Placement:**
    - When an order is placed referencing a template package with a chain, the resulting subscription is initialized at the first step of the chain.
    - The subscription plan instance records the current step and the chain it belongs to.

3. **Automatic Advancement:**
    - On each renewal, the system checks if the current step has completed its duration.
    - If so, the subscription advances to the next step in the chain, updating the plan, price, and other parameters as defined.
    - This process is automatic and does not require user or client intervention.

4. **Chain Completion:**
    - When the last step in the chain is reached, the subscription remains on that plan until changed or cancelled.

API Reference
-------------
- The API exposes chain-related fields on both template packages and subscription packages:
  - `packageChainId` (on template packages): Links to the chain definition.
  - `subscriptionPackageChainId` (on subscription packages): Indicates the chain instance the subscription is following.
  - `chainStepOrder` or similar fields: Indicate the current step.
- Chains and their steps can be managed via the API endpoints for packages and package chains. See the OpenAPI/Swagger documentation for details.

.. note::
    Chaining is especially useful for business models that require time-limited offers, staged onboarding, or complex upgrade/downgrade flows. It ensures that subscribers are automatically transitioned through the intended sequence of plans without manual intervention.

.. tip::
    When designing chains, consider how proration, billing frequency, and product entitlements should behave at each step. Test chain transitions in a non-production environment to ensure the desired customer experience.


Example of a Subscription Plan Chain
------------------------------------

The following diagram illustrates a typical introductory pricing chain:

.. mermaid:: subscriptionplan-chain-example.mmd
    :align: center
    :alt: Example of a subscription plan chain with introductory, standard, and full price steps

In this example:

- **Step 1:** Intro Offer (e.g., 1 month at 99)
- **Step 2:** Standard (e.g., 3 months at 149 per month)
- **Step 3:** Full Price (e.g., 199 per month until cancelled)

The subscription automatically advances through each step as periods renew, applying the defined plan and price for each stage.

Setting up such a chain involves creating the individual template packages and then defining the chain package that references them. 
Below is a simplified example of a Template SubscriptionPlan that defines a chain similar to the visualized chain.

.. code-block:: json
        :caption: Example: Creating Packages and a Chain Package

        // Step 1: Intro Offer Template Plan
        // POST /package
        {
            "id": "10000000-0000-0000-0000-000000000101", // Just here for reference, not actually part of the request.
            "name": "Intro Offer",
            "products": [
                { "productId": "prod-intro" }
            ],
            "price" : 99,
            "currency" : "NOK",
            "BillingPlans": ["12340000-0000-0000-0000-000000004321"] // Monthly
        }

        // Step 2: Reduced Price Template Plan
        {
            "id": "10000000-0000-0000-0000-000000000102", // Just here for reference, not actually part of the request.
            "name": "Standard",
            "products": [
                { "productId": "prod-standard" }
            ],
            "price" : 149,
            "currency" : "NOK",
            "BillingPlans": ["12340000-0000-0000-0000-000000004321"] // Monthly
        }

        // Step 3: Full Price Template Plan
        {
            "id": "10000000-0000-0000-0000-000000000103", // Just here for reference, not actually part of the request.
            "name": "Full Price",
            "products": [
                { "productId": "prod-full" }
            ],
            "price" : 199,
            "currency" : "NOK",
            "BillingPlans": ["12340000-0000-0000-0000-000000004321"] // Monthly
        }

        // Step 4: Chain Template Package referencing the above as steps
        // POST /packagechain
        {
            "name": "Intro+Standard+Full Chain",
            "description": "A subscription plan chain from Intro to Standard to Full Price",
            "packageChain": {
                "steps": [
                    { 
                        "step" : 1, 
                        "nextPackageId": "10000000-0000-0000-0000-000000000101" 
                    },
                    { 
                        "step": 2,
                        "nextPackageId": "10000000-0000-0000-0000-000000000102" 
                    },
                    { 
                        "step" : 3,
                        "nextPackageId": "10000000-0000-0000-0000-000000000103" 
                    }
                ]
            }
        }