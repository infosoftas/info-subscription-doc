
.. image:: _images/slogan.png
    :scale: 50 %
    :align: center
    :alt: Infosoft Logo With Slogan Software for subscription businesses
    :target: https://www.infosoft.as

*****************************************************
Welcome to the |projectName| Developer Documentation
*****************************************************

This documentation is designed for third-party developers and API consumers who want to integrate with the |projectName| platform. Here you'll find comprehensive guides, API references, and practical examples to help you build, extend, and connect your solutions to |projectName| .

**What is INFO-Subscription?**

|projectName| is a flexible platform for managing subscription-based businesses, offering robust APIs and managed experiences for seamless integration and automation. 
If you are new to the platform, visit the `product website <https://www.infosoft.as/info-subscription/>`_ for an overview.

**Who Should Use This Documentation?**

- Developers building integrations with |projectName| APIs
- Partners and customers automating subscription workflows
- Anyone seeking to extend or embed |projectName| capabilities in their own systems

If you are looking for end-user documentation, please visit the `user documentation <https://docs.infosoft.no/>`_.

Integration Options
===================
|projectName| provides a powerful API available to all tenants. You can:

- Explore the full API in the `Swagger UI <https://api.info-subscription.com/swagger/>`_
- Download the `OpenAPI/Swagger definition <https://api.info-subscription.com/swagger/v1/swagger.json>`_
- Start with our :ref:`Getting Started with the API <getting-started>` guide for a step-by-step introduction on how to authenticate and make your first API calls
- Review :ref:`integration guides <common-scenarios>` for common use cases and advanced scenarios.

|projectName|  also offers a :ref:`managed subscriber experience <managed-experience>`, including:

* A self-service portal for subscribers to manage their subscriptions
* An ordering and registration process for new subscribers
* An integrated Identity Provider (IdP) for authentication and authorization

To integrate with the managed subscriber experience, see our :ref:`introduction to the managed experience <managed-experience>`.

Quick Start
===========
1. Read :ref:`Getting Started <getting-started>` for API onboarding
2. Review API :ref:`Authentication <authorization>`, :ref:`Versioning <api-versioning>`, and perhaps the :ref:`Terminology <terminology>`
3. Try out the API using the Swagger UI or your favorite API client
4. Explore :ref:`common scenarios <common-scenarios>` and code samples

Beyond The Basics
=================
Already familiar with the basics? Explore these advanced topics to get the most out of |projectName|:

* :ref:`Common Integration Scenarios <common-scenarios>` – Real-world use cases
* :ref:`Webhooks and Event Handling <events>` – Automate workflows with event-driven integrations
* :ref:`Reporting and Analytics <reporting-intro>` – Access and analyze subscription data
* :doc:`OData Querying <reporting-analytics/odata-primer>` – Advanced querying techniques for analytics data
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
   general/scenarios

.. toctree::
    :caption: Subscribers
    :hidden:

    subscribers/subscribers

.. toctree::
    :caption: Subscriptions
    :hidden:

    subscription/plans
    subscription/orders/orders
    subscription/orders/examples/examples
    subscription/additional-products

.. toctree::
    :caption: Billing and Invoicing
    :hidden:

    billing/billingcycle
    billing/proration-policies
    billing/standalone

.. toctree::
    :caption: Payments and Agreements
    :glob:
    :hidden:

    payments/index

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