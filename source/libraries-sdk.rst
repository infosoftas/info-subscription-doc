.. _libraries-sdk:

***************************
Client Libraries and SDKs
***************************

Currently we do not provide any official client libraries or SDKs for |projectName|. 
There are options for generating SDKs using community tools and libraries, as well as other solutions to quickly integrate with |projectName|.

We encourage the community to contribute by creating and maintaining libraries in various programming languages.
Refer to our `GitHub repository <https://www.github.com/infosoftas/info-subscription/>`_  if you are interested in contributing.

Autogenerate SDKs with tooling
==============================

The OpenAPI specification for |projectName| is generated in a way that makes it suitable for automatic SDK generation using various tools. 
This allows developers to quickly create client libraries in their preferred programming languages.

.. tip:: 
    
    If possible, developers should restrict their tooling to only generate for the API surface they intend to use, rather than the entire API. 
    This helps reduce the size of the generated SDK and makes it easier to work with.

Examples of tools that can be used for SDK generation include:

* `OpenAPI Generator <https://openapi-generator.tech/`
* `Swagger Codegen <https://swagger.io/tools/swagger-codegen/`
* `Postman Code Generators <https://learning.postman.com/docs/developer/code-generators/`
* `Microsoft Kiota <https://github.com/microsoft/kiota>`_

.. note:: 

    Internally at Infosoft we utilize Kiota to generate dotnet and TypeScript SDKs for various externally deployed services that builds on top of the API.

Integration Platforms
=====================

Many low-code and no-code integration platforms support OpenAPI specifications.
Examples of such platforms include:

* Polly.ai
* Zapier
* Make.com
* Microsoft Power Automate
* Tray.io

There are many more out there, use the platform that suits your needs best.