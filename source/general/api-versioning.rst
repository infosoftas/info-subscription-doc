.. _api-versioning:

**************
API Versioning
**************

This document describes how |projectName| versions its API, manages changes, and handles deprecations to ensure stability and predictability for API consumers.

Versioning Approach
===================

Path-Based Versioning
---------------------

|projectName| uses **path-based versioning** where the version number is part of the URL path for each endpoint. This means that different endpoints can have different versions, and there is no strict version relationship between endpoints.

For example:

.. code-block:: text

    https://api.info-subscription.com/v1/subscribers
    https://api.info-subscription.com/v2/subscriptions
    https://api.info-subscription.com/v1/invoices

In this example, the ``subscribers`` and ``invoices`` endpoints are at version 1, while the ``subscriptions`` endpoint is at version 2. Each endpoint evolves independently based on its own requirements.

Independent Endpoint Versioning
-------------------------------

Each API endpoint is versioned independently. This means:

* There is **no version relationship** between different endpoints
* Upgrading one endpoint to a new version does not require upgrading others
* You can use ``v1`` of one endpoint and ``v2`` of another in the same integration
* Each endpoint version remains stable and backward-compatible within its version

This approach provides maximum flexibility for both API providers and consumers, allowing incremental adoption of new features without forcing wholesale API version upgrades.

API Documentation and OpenAPI Specification
-------------------------------------------

The OpenAPI (Swagger) specification available at https://api.info-subscription.com/swagger/ contains **all currently available API versions**, including deprecated versions that are still supported. 

* **Active versions**: Endpoints that are current and fully supported
* **Deprecated versions**: Endpoints marked as deprecated are clearly indicated in the Swagger documentation with deprecation notices
* **Removed versions**: Once an endpoint version is sunset and removed, it will no longer appear in the OpenAPI specification

In the Swagger UI, deprecated endpoints are visually marked to alert you that they should be migrated to newer versions. This allows you to explore both current and deprecated versions while planning your migration strategy.

Breaking vs Non-Breaking Changes
=================================

Understanding the difference between breaking and non-breaking changes is crucial for maintaining stable integrations.

Breaking Changes
----------------

A **breaking change** is any modification that could cause existing client implementations to fail or behave incorrectly. Breaking changes require a new version of the endpoint.

Examples of breaking changes include:

* **Removing or renaming** existing fields in request or response payloads
* **Changing the data type** of an existing field (e.g., from string to integer)
* **Modifying the meaning or behavior** of an existing field
* **Removing or renaming** an endpoint
* **Changing endpoint paths** or HTTP methods (e.g., from POST to PUT)
* **Adding required fields** to request payloads
* **Removing support** for previously accepted values
* **Changing error codes or responses** in a way that affects error handling
* **Modifying authentication or authorization** requirements
* **Changing default values** in a way that alters behavior

When we introduce a breaking change, we will:

1. Create a new version of the affected endpoint (e.g., ``/v2/resource``)
2. Maintain the old version (e.g., ``/v1/resource``) for a deprecation period
3. Clearly document the changes and migration path
4. Communicate the deprecation timeline to all API consumers

Non-Breaking Changes
--------------------

A **non-breaking change** (also called a backward-compatible change) is a modification that does not affect existing client implementations when properly designed.

Examples of non-breaking changes include:

* **Adding new optional fields** to request payloads
* **Adding new fields** to response payloads
* **Adding new endpoints** or resources
* **Adding new optional query parameters**
* **Adding new HTTP methods** to existing endpoints (if not previously used)
* **Adding new values** to enums or choice fields (with appropriate handling)
* **Fixing bugs** that align behavior with documented specifications
* **Performance improvements** that don't change functionality
* **Adding more detailed error messages** without changing error codes

Non-breaking changes are introduced to the current version of an endpoint without creating a new version.

Client Expectations for Handling Changes
=========================================

To ensure your integration remains stable across non-breaking changes, your client implementation should follow these best practices:

Ignore Unknown Fields
---------------------

Your client should **gracefully ignore** any fields in API responses that it doesn't recognize. This allows us to add new optional fields to responses without breaking your integration.

.. code-block:: javascript

    // Good: Only extract known fields
    const { id, name, email } = response.data;
    // Any additional fields in response.data are safely ignored

Do Not Rely on Field Ordering
-----------------------------

JSON objects are unordered collections. Never assume that fields in a response will appear in a specific order.

Handle New Enum Values Gracefully
---------------------------------

When working with enumerated values (e.g., status codes), implement a default case for unknown values:

.. code-block:: javascript

    switch (subscription.status) {
        case 'active':
            handleActive();
            break;
        case 'cancelled':
            handleCancelled();
            break;
        case 'suspended':
            handleSuspended();
            break;
        default:
            // Handle unknown statuses gracefully
            handleUnknownStatus();
    }

Use Semantic Versioning for Dependencies
----------------------------------------

If you're using an SDK or client library for |projectName|, follow semantic versioning principles:

* **Patch updates** (e.g., 1.0.0 → 1.0.1): Bug fixes, safe to upgrade
* **Minor updates** (e.g., 1.0.0 → 1.1.0): New features, backward-compatible
* **Major updates** (e.g., 1.0.0 → 2.0.0): Breaking changes, review before upgrading

Be Flexible with Response Validation
------------------------------------

Avoid strict validation that requires an exact schema match. Instead, validate only the fields your application needs:

.. code-block:: python

    # Good: Validate only what you need
    def validate_subscriber(subscriber):
        assert 'id' in subscriber
        assert 'email' in subscriber
        # Don't fail if extra fields exist

Deprecation and Sunset Policy
==============================

When we need to introduce breaking changes, we follow a structured deprecation process to give you ample time to migrate.

Deprecation Timeline
--------------------

When an API endpoint version is deprecated:

1. **Announcement**: We announce the deprecation with at least **18 months** advance notice
2. **Deprecation Period**: The endpoint continues to function normally with deprecation warnings
3. **Migration Support**: We provide migration guides and support during the transition
4. **Sunset Date**: After 18 months, the endpoint version is removed

During the deprecation period:

* The deprecated endpoint **remains fully functional**
* Responses include deprecation headers (``Sunset`` and ``Deprecation``)
* Documentation clearly marks the endpoint as deprecated
* The new version is available for migration

Deprecation Notice Example
--------------------------

When an endpoint is deprecated, API responses will include HTTP headers following the ASP.NET Core API Versioning conventions:

.. code-block:: http

    HTTP/1.1 200 OK
    api-supported-versions: 2.0, 3.0
    api-deprecated-versions: 1.0
    sunset: Wed, 01 Jun 2026 00:00:00 GMT
    
These headers indicate:

* ``api-supported-versions`` - Lists all currently supported versions of this endpoint
* ``api-deprecated-versions`` - Lists versions that are deprecated but still functional
* ``sunset`` - The date when the deprecated version(s) will be removed

For example, if you call a ``v1`` endpoint that has been deprecated in favor of ``v2`` and ``v3``, the response headers will show that ``v1`` is deprecated, while ``v2`` and ``v3`` are the supported versions you should migrate to.

Migration Path
--------------

When migrating from a deprecated version:

1. **Review the changelog** for differences between versions
2. **Test with the new version** in a non-production environment
3. **Update your code** to use the new endpoint path
4. **Deploy incrementally** and monitor for issues
5. **Verify functionality** matches expected behavior

Monitoring Deprecations
-----------------------

To stay informed about deprecations:

* Monitor the :ref:`changelog <changelog>` for deprecation announcements
* Check response headers from API calls for deprecation warnings
* Subscribe to our API updates mailing list (contact :ref:`support <reporting-bugs>`)
* Review the `API Reference <https://api.info-subscription.com/swagger/>`_ regularly

Best Practices
==============

To build resilient integrations with |projectName| APIs:

1. **Build for change**: Design your client to handle non-breaking changes gracefully
2. **Monitor deprecation warnings**: Regularly check for deprecation headers in responses
3. **Test early**: When a new version is released, test it in your development environment
4. **Stay informed**: Follow our :ref:`changelog <changelog>` and documentation updates
5. **Use versioned endpoints explicitly**: Always specify the version in your API calls
6. **Document your dependencies**: Keep track of which API versions your application uses
7. **Plan for migrations**: Budget time for API version upgrades in your development cycle
8. **Use SDKs when available**: Official :ref:`SDKs and libraries <libraries-sdk>` handle version management automatically

Summary
=======

* |projectName| uses **path-based versioning** with independent endpoint versions
* Each endpoint version is **stable and backward-compatible**
* We distinguish between **breaking** and **non-breaking** changes
* Clients should be designed to **gracefully handle** non-breaking changes
* Deprecated endpoints remain available for **at least 18 months** after deprecation
* Migration guidance and support are provided during deprecation periods

By following these guidelines and best practices, you can build robust integrations that remain stable as the API evolves.
