.. You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. image:: _images/slogan.png
    :scale: 50 %
    :align: center
    :alt: Infosoft Logo With Slogan Software for subscription businesses
    :target: https://www.infosoft.as

************
Introduction
************

This is the home of the developer documentation for |projectName|.
If you came here looking for the user documentation you are in the `wrong place <https://docs.infosoft.no/>`_.

If you have no idea what |projectName| is, then head over to the `product website <https://www.infosoft.as/solutions/info-subscription/>`_ and have a look.

Integration Options
===================
|projectName| is backed by an API that all tenants can make use of. 

If you just want the gory details for the API you can browse `the Swagger UI <https://api.info-subscription.com/swagger/>`_ or `get the OpenAPI/Swagger definition file <https://api.info-subscription.com/swagger/v1/swagger.json>`_.

Alternatively, head over to the :ref:`Getting Started with the API <getting-started>` section for a more gentle API introduction, or look at our list of :ref:`common scenarios <common-scenarios>`.

Some tenants prefer to use our :ref:`managed subscriber experience <managed-experience>` which includes

 * A self-service portal/web site where subscribers can manage their subscriptions.
 * An ordering and user registration site/process where new subscribers can order subscriptions and register a new user.
 * An Identity Provider (IdP) solution that contains user credentials and some authorization information for letting users consume their purchased content.

For integrating with the managed subcriber experience header over to our :ref:`introduction to the managed experience <managed-experience>` .


Contact Information and Support
=================================
Please refer to the section on :ref:`Support and Reporting Bugs <reporting-bugs>` for details on how to contact Infosoft.

:ref:`genindex`

.. The following TOC tree directives are here to make sure the side-bar looks like we want it to.
   If a toc tree does not have a :hidden: tag it will be shown at the bottom on the index page!

.. toctree::
   :hidden:

   self
   general/getting-started
   general/what-is-info-subscription
   general/terminology
   general/auth
   general/scenarios

.. toctree::
    :caption: Managed Subscriber Experience (Self-Service)
    :hidden:

    managed-experience/managed-introduction
    managed-experience/selfservice/customization
    managed-experience/authentication-authorization/quick-start
    managed-experience/authentication-authorization/user-management-authentication
    managed-experience/selfservice/custom-domain
    managed-experience/authentication-authorization/adb2c/index

.. toctree::
    :caption: Events and Webhooks
    :hidden:

    events/events-introduction

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

.. toctree::
    :caption: Payments and Agreements
    :glob:
    :hidden:

    payments/index
    payments/requests

.. toctree::
    :caption: Reporting and Analytics
    :hidden:

    Introduction <reporting-analytics/intro>
    Datamodel <reporting-analytics/datamodel>


.. toctree::
    :caption: Misc
    :hidden:
   
    reporting-bugs
    API Reference/Swagger <https://api.info-subscription.com/swagger/>
    doc-contribution

.. toctree::
    :caption: Changelog
    :hidden:

    changelog/changelog