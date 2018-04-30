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

.. ATTENTION::
    This documentation and the API it describes is still very much in a pilot phase and is thus subject to change.

    It is likely that there are discrepancies between the actual implementation and the documentation.
    Either in the form of concepts documented that does not exist or concepts that have been changed since the documentation was written.
    We are trying to bring everything up to speed, but as mentioned above this is still a beta/pilot thing. 
    Let us know by contacting support or creating issues.
    
    We welcome any and all feedback you have on the API, and in the pilot phase the barrier for including changes
    is somewhat smaller than normal (since we don't need to version the API).

This is the home of the API documentation for |projectName|.

If you came here looking for the user documentation please head over to http://www.hereissomedocuemtnation.no

If you have no idea what |projectName| is, then head over to the `product website <https://www.infosoft.as/solutions/info-subscription/>`_ and have a look.

If you just want the gory details you can browse `the Swagger UI <https://api.info-subscription.com/swagger/>`_ or `get the OpenAPI/Swagger definition file <https://api.info-subscription.com/swagger/v1/swagger.json>`_.

Otherwise head over to the :ref:`Getting Started <getting-started>` section

Contact Information and Support
-------------------------------
Please refer to the section on :ref:`Support and Reporting Bugs <reporting-bugs>` for details on how to contact Infosoft.

.. The following TOC tree directives are here to make sure the side-bar looks like we want it to.
   If a toc tree does not have a :hidden: tag it will be shown on the index page!

.. toctree::
   :hidden:

   self
   general/getting-started
   general/auth
   general/what-is-info-subscription

.. toctree::
    :caption: Subscriptions
    :hidden:

    subscription/orders/orders

.. toctree::
    :caption: Misc
    :hidden:
   
    reporting-bugs
    API Reference/Swagger <https://api.info-subscription.com/swagger/>
    doc-contribution