
.. image:: _images/slogan.png
    :scale: 50 %
    :align: center
    :alt: Infosoft Logo With Slogan Software for subscription businesses
    :target: https://www.infosoft.as

*****************************************************
Welcome to the |projectName| Developer Documentation
*****************************************************

This documentation is designed for third-party developers and API consumers who want to integrate with the |projectName| platform. 
Here you'll find comprehensive guides, API references, and practical examples to help you build, extend, and connect your solutions to |projectName| .

Building Subscription Businesses with |projectName|
====================================================

|projectName| is a flexible platform for managing subscription-based businesses, offering robust APIs and managed experiences for seamless integration and automation. 
If you are new to the platform, visit the `product website <https://www.infosoft.as/info-subscription/>`_ for an overview.

**Who Should Use This Documentation?**

- Developers building integrations with |projectName| APIs
- Partners and customers automating subscription workflows
- Anyone seeking to extend or embed |projectName| capabilities in their own systems

If you are looking for end-user documentation, please visit the `user documentation <https://docs.infosoft.no/>`_.

.. note::

    New to the domain? The docs use terms like *subscriber*, *subscription*, and *payment agreement* throughout. See :ref:`Terminology <terminology>` before continuing if anything is unclear.

Quick Start
===========

1. Read :ref:`Getting Started <getting-started>` for API onboarding
2. Review API :ref:`Authentication <authorization>`, :ref:`Versioning <api-versioning>`, and perhaps the :ref:`Terminology <terminology>`
3. Try out the API in our :ref:`testing and experimentation tenant <testing-experimenting>`, using the Swagger UI or your favorite API client
4. Explore :ref:`common scenarios <common-scenarios>` and code samples


Integration Options
===================

|projectName| gives you two building blocks that can be combined as needed:

.. list-table::
   :header-rows: 1
   :widths: 25 40 35

   * - Path
     - Choose this if
     - Start here
   * - Build your own
     - You want full control over checkout, self-service, and authentication in your own frontend
     - :ref:`Getting Started with the API <getting-started>`
   * - Use the managed experience
     - You want a turnkey ordering and self-service portal without building your own frontend
     - :ref:`Introduction to the managed experience <managed-experience>`

Most tenants mix the two: for example, using the managed self-service portal while still calling the API directly for custom reporting or ERP integration.

**Building your own?** The full API is available to every tenant:

- Explore it in the `Swagger UI <https://api.info-subscription.com/swagger/>`_
- Download the `OpenAPI/Swagger definition <https://api.info-subscription.com/swagger/latest/swagger.json>`_
- Review :ref:`integration guides <common-scenarios>` for common use cases and advanced scenarios.

**Using the managed experience?** It includes:

* A self-service portal for subscribers to manage their subscriptions
* An ordering and registration process for new subscribers
* An integrated Identity Provider (IdP) for authentication and authorization

To integrate with the managed subscriber experience, see our :ref:`introduction to the managed experience <managed-experience>`.

Explore Further
===============

Ready to go deeper? Start with a goal below, or browse the reference material: 

I want to build...
-------------------

Custom integrations against the raw API, for teams building their own checkout, portal, or workflows.

* 🛒 :ref:`A custom subscription checkout <subscription-orders>`
* 🔌 :ref:`My own content into a CMS or portal <auth-quick-start>`
* 💳 :ref:`Recurring payments into my own flow <payment-methods-overview>`
* 📱 :ref:`A Vipps or MobilePay integration <provider-vipps>`
* 🔄 :ref:`Subscription change handling (upgrades/downgrades) <subscription-plan-changes>`
* 🧾 :ref:`Billing and invoice handling <billing-cycle>`
* ⚡ :ref:`Event-driven subscriptions <events>`
* 📊 :ref:`Subscription analytics into my own tools <reporting-intro>`

I want to set up...
--------------------

|projectName|'s turnkey, managed experiences — configured, not built from scratch.

* 🛒 :ref:`A managed subscription checkout <checkout>`
* 👤 :ref:`A self-service portal for subscribers <managed-experience>`

Additional Resources
--------------------

**Billing & Subscription Lifecycle** – in-depth guides for how the platform manages recurring billing:

* :ref:`Subscription Lifecycle <subscription-lifecycle>` – How subscriptions are created, renewed, upgraded, and terminated
* :ref:`Billing Cycle In Depth <billing-cycle>` – Payment demands, invoices, reminders, and dunning, stage by stage
* :ref:`Proration Policies <proration-policies>` – How cancellations and mid-period plan changes are prorated
* :ref:`Payment Matching, Settlement & Reconciliation <payment-matching-settlement>` – How incoming payments are matched to invoices and billing accounts reconciled
* :ref:`Standalone Payment Demands <standalone-paymentdemands>` – Issuing one-off charges outside the regular billing cycle
* :ref:`On-Demand Reminders <on-demand-reminder>` – Issuing reminders when an external collection agency controls the timeline

**General**

* :ref:`Common Integration Scenarios <common-scenarios>` – Real-world use cases
* :ref:`Webhooks and Event Handling <events>` – Automate workflows with event-driven integrations
* :ref:`Reporting and Analytics <reporting-intro>` – Access and analyze subscription data
* :doc:`OData Querying <reporting-analytics/odata-primer>` – Advanced querying techniques for analytics data
* :doc:`MCP Server <general/mcp-server>` – Connect AI assistants to live tenant data
* `API Reference <https://api.info-subscription.com/swagger/>`_ – Full technical details for all endpoints
* :ref:`Follow the changelog <changelog>` – Stay up to date with the latest changes
* :ref:`Testing <testing-experimenting>` – Use our testing and experimentation tenant for testing your integration and getting to know the platform.

For more, see the sidebar or use the search to find specific guides and references.

Contact & Support
=================
For help, feedback, or to report issues, see :ref:`Support and Reporting Bugs <reporting-bugs>` for contact details.

.. The following TOC tree directives are here to make sure the side-bar looks like we want it to.
   If a toc tree does not have a :hidden: tag it will be shown at the bottom on the index page!

.. toctree::
   :hidden:

   self
   general/getting-started
   general/what-is-info-subscription
   general/terminology
   general/auth
   general/api-versioning
   general/mcp-server
   general/scenarios

.. toctree::
    :caption: Subscribers
    :hidden:

    subscribers/subscribers

.. toctree::
    :caption: Subscriptions
    :hidden:

    subscription/lifecycle
    subscription/plans
    subscription/orders/orders
    subscription/orders/examples/examples
    subscription/additional-products

.. toctree::
    :caption: Billing and Invoicing
    :hidden:

    billing/billingcycle
    billing/payment-matching-settlement
    billing/proration-policies
    billing/standalone
    billing/on-demand-reminder

.. toctree::
    :caption: Payments and Agreements
    :glob:
    :hidden:

    payments/payment-agreements

.. toctree::
    :caption: Events and Webhooks
    :hidden:

    events/events-introduction

.. toctree::
    :caption: Managed Subscriber Experience (Self-Service)
    :hidden:
    :glob:

    managed-experience/managed-introduction
    managed-experience/selfservice/checkout
    managed-experience/authentication-authorization/quick-start
    managed-experience/authentication-authorization/api-based-claims
    managed-experience/authentication-authorization/adb2c
    managed-experience/authentication-authorization/sessions
    managed-experience/authentication-authorization/user-management-authentication
    managed-experience/selfservice/custom-domain
    
.. toctree::
    :caption: Reporting and Analytics
    :hidden:

    Introduction <reporting-analytics/intro>
    Datamodel <reporting-analytics/datamodel>
    OData Querying <reporting-analytics/odata-primer>


.. toctree::
    :caption: Misc
    :hidden:

    testing-experimenting
    libraries-sdk
    reporting-bugs
    API Reference/Swagger <https://api.info-subscription.com/swagger/>
    doc-contribution

.. toctree::
    :caption: Changelog
    :hidden:

    changelog/changelog

:ref:`genindex`