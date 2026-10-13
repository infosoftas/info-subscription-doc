.. _libraries-sdk:

***************************
Client Libraries and SDKs
***************************

SDK packages are available for .NET and TypeScript. They are generated from the OpenAPI specification using Microsoft Kiota and include only a subset of the API.

* **.NET**: `Infosoft.Info.Subscription.Dotnet on NuGet.org <https://www.nuget.org/packages/Infosoft.Info.Subscription.Dotnet>`_ (`.NET source code <https://github.com/infosoftas/info-subscription-sdk/tree/main/dotnet-sdk>`_)
* **TypeScript**: `@infosoftas/info-subscription-ts on npmjs.org <https://www.npmjs.com/package/@infosoftas/info-subscription-ts>`_ (`TypeScript source code <https://github.com/infosoftas/info-subscription-sdk/tree/main/typescript-sdk>`_)

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

* `OpenAPI Generator <https://openapi-generator.tech/docs/>`_
* `Swagger Codegen <https://swagger.io/docs/open-source-tools/swagger-codegen/>`_
* `Postman SDK Generator <https://learning.postman.com/docs/sdk-generator/overview>`_
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