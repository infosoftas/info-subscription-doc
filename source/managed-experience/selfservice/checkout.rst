.. _checkout:

Checkout
========

|projectName| contains a checkout solution to streamline the purchase and onboarding process for both digital services and physically distributed products. 
It is an out-of-the-box web app that enables end users to complete subscription purchases with minimal effort, requiring no special setup from tenants.

Key features include:

* **Comprehensive Purchase Journeys**: Prebuilt workflows for:
    * Simple, low-friction orders for digital/non-physical services.
    * Orders requiring customer details (e.g., name, phone, and address).
    * **B2B orders**, including advanced invoicing options.
* **Payment Options**: Built-in support for payment methods such as Vipps, MobilePay, CreditCard, EHF, OIO, Email invoicing as well as traditional invoicing.
.. * **Customizable Invoice Address collection**: Optional configurations for invoice address collection. (COMMENTED OUT UNTIL WE HAVE OPTION TO TOGGLE THIS!)

Checkout allows developers to configure, extend, and customize it to meet specific business requirements to some degree.

The following documentation will guide you through the customisation to suit your specific requirements.

Journey Types in |projectName| Checkout
---------------------------------------
The journey query parameter allows you to specify the type of journey to be invoked during the checkout process. 

Each journey is pre-configured to meet different use cases, providing flexibility for digital services, physically distributed products, and B2B transactions.

Available Journey Types
~~~~~~~~~~~~~~~~~~~~~~~

The following as quick list of the journeys, details are available in the following sections.

* Order
* Order with Address and Personal Information
* B2B 

#. Order (``order``)

    * **Description**: A minimal-friction journey designed for orders that do not require personal information like an address or phone number.
    * **Use Case**: Ideal for digital services or products where only basic payment and subscription details are needed.
    * **How to use**:
    
        .. code-block:: bash

            https://{tenantName}-s4.azurewebsites.net/checkout?journey=order

    **Screenshot:**
    
    .. image:: /_images/checkout/order_journey.png
        :align: center
        :alt: Minimal-friction order journey interface
        :scale: 60%

#. Order with Address and Personal Information (``order-address``)

    * **Description**: A journey that requires users to provide additional details, such as their name, address, and telephone number.
    * **Use Case**: Suitable for physically distributed products or services requiring accurate delivery and contact details.
    * **How to use**:

        .. code-block:: bash

            https://{tenantName}-s4.azurewebsites.net/checkout?journey=order-address
    
    **Screenshot:**

    .. image:: /_images/checkout/order-address_journey.png
        :align: center
        :alt: Personal Info and Address order journey interface
        :scale: 60%

#. B2B (``order-business``)

    * **Description**: A journey tailored for business-to-business transactions. This includes options for e-invoicing and company-specific information.
    * **Use Case**: Ideal for businesses subscribing on behalf of an organization, where advanced invoicing and organizational data are necessary.
    * **How to use**:

        .. code-block:: bash

            https://{tenantName}-s4.azurewebsites.net/checkout?journey=order-business

    **Screenshot:**

        .. image:: /_images/checkout/order-businesss_journey_combined.jpeg
            :align: center
            :alt: Business to Business order journey interface, with step 2 showing the follow up window after selecting EHF as the payment method.
            :scale: 60%

The journey parameter ensures the correct workflow is invoked, streamlining the process to match the needs of your specific subscription model.

By specifying the journey type, you can provide users with a customized and optimized checkout experience that aligns with their unique requirements.

Configuration Options
---------------------
The checkout configuration can be adjusted in two primary ways: via query parameters and more statically defined options in the Merchant UI.

1. Configuration via Query Parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following query parameters can be used to customize the checkout process dynamically at runtime:

* ``returnUrl``: Specifies the URL to which the user will be redirected after completing the order. If not provided, the platform uses the merchant-configured Tenant Home Page configuration value.
* ``source``: Tracks the source of the order for analytics and reporting (e.g., Kilkaya, Google Tag Manager).
* ``templatePlanId``: Overrides the default subscription plan, allowing you to dynamically specify a different plan for the user.
* ``organizationId``: Specifies the organization ID for the order, allowing you to dynamically set the organization for the subscription plan if not provided in the plan directly.
* ``journey``: Sets the journey type to invoke, this is a required parameter.

These query parameters can be appended to the checkout URL to tailor behaviour for specific use cases.

For example:

.. code-block:: bash

    https://{tenantName}-s4.azurewebsites.net/checkout?journey=order&returnUrl=https://example.com/thank-you&source=google&templatePlanId=1234567


2. Configuration and Default via Merchant Options
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Tenants can define settings in the Merchant UI that control the default behaviour and appearance of the checkout process.


These options include:

**Global Settings**

* ``Tenant Home Page``: Default returnUrl if none is provided in the query parameters.
* ``Kilkaya Installation``: Specifies the integration setup for Kilkaya order tracking and the endpoint where orders should be registered.
* ``GoogleTagManager Id``: Defines the GTM setup for order tracking and registration.
* ``Self Service Url``: A reference URL for payment providers that require a self-service management page for users.
* ``Custom Css Url``: Points to a custom CSS file that will be applied during the checkout process, allowing complete visual customisation.

**Per-Journey Settings**
Each journey can be further customized with the following settings:

* ``IngressHeader`` and ``IngressText``: Control the introduction header and text displayed at the start of the checkout process.

**Screenshot:**

.. image:: /_images/checkout/ingress_example.png
    :align: center
    :alt: Customizable introduction header and text example (Monthly Subscription of Coffee)
    :scale: 60%

* ``PaymentMethods``: Specifies the payment methods available to users during the checkout process (e.g., CreditCard, Vipps, Invoice and Email).

**Screenshot:**

.. image:: /_images/checkout/paymentmethod_example.png
    :align: center
    :alt: Display the payment selection step of a checkout journey, showing multiple payment methods (e.g., CreditCard, Vipps, Email etc.).
    :scale: 60%

* ``TermsUrl``: The URL pointing to the terms and conditions for the subscription.
* ``OrganizationId``: Specifies the default organization ID used for the order if not provided with the Subscription Plan Id.
* ``DefaultSubscriptionPlanId``: The default subscription plan for new orders if not overridden by a query parameter.

These options acts as defaults, and some are required for the best user experience, but all of them are essentially optional.

Advanced customisation with the |projectName| Orders SDK
--------------------------------------------------------

If the out-of-the-box solution does not fully meet your requirements, we offer an SDK that provides deeper customisation options and flexibility. 
The SDK exposes the underlying functionality of the checkout application, allowing you to build tailored solutions and integrate seamlessly with your own web application.

The SDK is available as:

* An NPM package, making it easy to integrate directly into your JavaScript/TypeScript projects.
* A GitHub repository, where you can review the source code, contribute, or explore detailed examples.

Visit the SDK resources here:

* **GitHub Repository**: https://github.com/infosoftas/s4-orders-js-sdk
* **NPM Package**: https://www.npmjs.com/package/@infosoftas/s4-orders-js-sdk

For advanced use cases, the SDK offers full control over workflows, payment integrations, and customisation of the purchase process, empowering developers to create a solution that perfectly aligns with their needs.