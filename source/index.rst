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

This is the home of the API documentation for |projectName|.

If you came here looking for the user documentation you are in the wrong place. This is the developer documentation.

If you have no idea what |projectName| is, then head over to the `product website <https://www.infosoft.as/solutions/info-subscription/>`_ and have a look.

If you just want the gory details you can browse `the Swagger UI <https://api.info-subscription.com/swagger/>`_ or `get the OpenAPI/Swagger definition file <https://api.info-subscription.com/swagger/v1/swagger.json>`_.

Otherwise head over to the :ref:`Getting Started <getting-started>` section

Contact Information and Support
-------------------------------
Please refer to the section on :ref:`Support and Reporting Bugs <reporting-bugs>` for details on how to contact Infosoft.

:ref:`genindex`

.. The following TOC tree directives are here to make sure the side-bar looks like we want it to.
   If a toc tree does not have a :hidden: tag it will be shown on the index page!

.. toctree::
   :includehidden:

   self
   general/getting-started
   general/auth
   general/what-is-info-subscription
   general/terminology.rst

.. toctree::
    :caption: Subscribers
    :hidden:

    subscribers/users/usermodel
    subscribers/users/authentication
    subscribers/users/authorization

.. toctree::
    :caption: Subscriptions
    :glob:
    :hidden:

    subscription/orders/orders
    subscription/*

.. toctree::
    :caption: Events and Webhooks
    :hidden:

    events/events-introduction

.. toctree::
    :caption: Payments and Agreements
    :glob:
    :hidden:

    payments/agreements
    payments/providers/*

.. toctree::
    :caption: Reporting and Analytics
    :hidden:

    Reporting Datamodel <reporting/Report database>

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