.. _testing-experimenting:

*****************************
Testing and Experimentation
*****************************

To simplify testing and experimentation with |projectName|, we provide a dedicated tenant environment called `Experimentation`.

This environment is pre-configured with some settings and data to facilitate testing without impacting production tenants.

Developers can use this environment to experiment with the platform (trial runs), new features and test API integrations.
For continuous integration testing we recommend contacting support for a dedicated CI environment suited to your specific needs.

Test Data and Routines
======================

The `Experimentation` tenant is pre-configured with some data, such as:

* An organization.
* A few products with list prices.
* At least one Template Subscription Plan.
* A test account to support testing with |Vipps| and |MobilePay|.
* A test account to support testing with |SwedbankPay|.
* A test account to support submitting PEPPOL Invoices (EHF and OIO) as well as interactive lookups for organization identifiers.

The test environment is configured to run on low-priority resources, so performance may vary.

Developers should not rely on this environment for performance testing or benchmarking.

Do not submit sensitive data here, as it is a shared environment accessible by multiple parties.

.. important:: 

    The `Experimentation` environment includes a set of pre-defined test data and routines to help you get started quickly. 
    The environment is reset quarterly, so your data will be removed after the reset.
    
    At the current time these resets occur the first work day in September, December, March and June.
    We may do additional resets depending on the actual use.

Tenant Information
------------------

The `Experimentation` tenant is pre-configured with the following information:

* Tenant Id: `e02d3360-8a5f-4115-fef1-08d69bbc8a54` - Include this in the |tenantHeader| header as described in the `OpenAPI/Swagger definition <https://api.info-subscription.com/swagger/v1/swagger.json>`_
* Client Id: `1b162230-180c-4648-9d0f-a313bb86510c`

Contact :ref:`support <reporting-bugs>` for a `client_secret` to authenticate with the API and/or a set of management credentials to the `merchant client <https://merchant.info-subscription.com>`_.

Payment Provider Test Data
---------------------------

The pre-configured test accounts are linked to the respective integration/testing environments for |VippsMobilePay|, |SwedbankPay| and our PEPPOL access point.

The details of these environments is beyond the scope of this documentation, but you can find more information in the respective payment provider's documentation.

* Developer Documentation for `Vipps and MobilePay <https://developer.vippsmobilepay.com/>`_
* Developer Documentation and Test Data for `SwedbankPay <https://developer.swedbankpay.com/checkout-v3/test-data/>`_

.. note:: 

    Unfortunately, we cannot provide a meaningful test setup for |AvtaleGiro|, |eFaktura|, |BetalingsService| and |AutoGiro| at the current time.
    Each of these are out-of-band integrations, and as such rarely requires custom integration to function.