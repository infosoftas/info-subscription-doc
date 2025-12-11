.. _api-based-user-claims:

*************************************
API-Based User Claims Retrieval
*************************************

While the token-based authorization flow described in the :ref:`quick start <auth-quick-start>` is the most common approach, there are scenarios where obtaining user claims directly via an API call is more suitable.

This alternative approach allows you to retrieve user authorization information without relying on the token login flow, making it particularly useful for:

* Server-to-server integrations
* Custom authorization processes
* Direct ADB2C integrations
* Scenarios where token-based flows are not practical

API Endpoint Overview
====================

The endpoint ``/authorizations/identityprovider/{tenantId}/userclaims`` returns user claims data that includes subscriber and product information. 

While this endpoint is designed to be consumed directly by ADB2C during custom policy execution, it can also be used by other authorization processes that need to retrieve user claims programmatically.

Authentication Requirements
==========================

.. important::

    This endpoint requires special authentication as it is built to support ADB2C direct integrations and server-to-server scenarios.

The authentication method uses HTTP Basic Authentication with a username and password obtained from your Identity Provider setup in |projectName|.

Obtaining Credentials
--------------------

Username and password credentials for this endpoint can be obtained in one of two ways:

1. Directly from the IdP setup in |projectName|
2. From your support contact

Please :ref:`contact support <reporting-bugs>` if you need assistance obtaining these credentials.

Authentication Header
--------------------

To authenticate with the endpoint:

1. Concatenate the username and password separated by a colon (``:``)
2. Base64 encode the concatenated string
3. Include the encoded string in the ``Authorization`` header

.. code-block:: text
    :caption: Authentication Format

    Authorization: Basic {base64encode("{username}:{password}")}

Example
-------

.. code-block:: python
    :caption: Python Example - Building the Authorization Header

    import base64

    username = "your_username"
    password = "your_password"
    
    # Concatenate username and password with a colon
    credentials = f"{username}:{password}"
    
    # Base64 encode the credentials
    encoded_credentials = base64.b64encode(credentials.encode()).decode()
    
    # Build the Authorization header
    auth_header = f"Basic {encoded_credentials}"

.. code-block:: javascript
    :caption: JavaScript Example - Building the Authorization Header

    const username = "your_username";
    const password = "your_password";
    
    // Concatenate username and password with a colon
    const credentials = `${username}:${password}`;
    
    // Base64 encode the credentials
    const encodedCredentials = Buffer.from(credentials).toString('base64');
    
    // Build the Authorization header
    const authHeader = `Basic ${encodedCredentials}`;

.. code-block:: csharp
    :caption: C# Example - Building the Authorization Header

    using System;
    using System.Text;

    string username = "your_username";
    string password = "your_password";
    
    // Concatenate username and password with a colon
    string credentials = $"{username}:{password}";
    
    // Base64 encode the credentials
    string encodedCredentials = Convert.ToBase64String(
        Encoding.UTF8.GetBytes(credentials)
    );
    
    // Build the Authorization header
    string authHeader = $"Basic {encodedCredentials}";

Making the API Request
======================

Once you have constructed the authentication header, you can make a request to the endpoint.

Request Format
-------------

.. code-block:: http
    :caption: HTTP Request

    GET /authorizations/identityprovider/{tenantId}/userclaims?externalId={externalUserId} HTTP/1.1
    Host: api.info-subscription.com
    Authorization: Basic {encodedCredentials}

Parameters
----------

.. table:: Request Parameters

    =============  ========  ====================================================================
    Parameter      Location  Description
    =============  ========  ====================================================================
    tenantId       Path      The Identity Provider tenant ID from |projectName|
    externalId     Query     The external user ID as it exists in the Identity Provider
    =============  ========  ====================================================================

Response Format
--------------

The endpoint returns user claims in a format suitable for ADB2C consumption, including subscriber and product information.

.. code-block:: json
    :caption: Sample Response

    {
        "subscriberId": "73265483-0a64-4acc-9ccf-11359ef5ce9f",
        "products": [
            {
                "id": "70e75bc0-6c3d-4934-a2e8-08d80b92b721",
                "validFrom": "2022-06-29T05:37:25.8669071+00:00",
                "validTo": "2023-06-29T05:37:24.8669071+00:00"
            }
        ]
    }

.. note::

    The ``subscriberId`` may be empty for family members and other shared users.
    
    The ``products`` array can be empty whenever no mapping exists that grants product access.

Complete Example
===============

.. code-block:: python
    :caption: Python Complete Example

    import base64
    import requests

    # Configuration
    api_base_url = "https://api.info-subscription.com"
    username = "your_username"
    password = "your_password"
    tenant_id = "your_tenant_id"
    external_user_id = "user@example.com"

    # Build authentication header
    credentials = f"{username}:{password}"
    encoded_credentials = base64.b64encode(credentials.encode()).decode()
    auth_header = f"Basic {encoded_credentials}"

    # Make the request
    url = f"{api_base_url}/authorizations/identityprovider/{tenant_id}/userclaims"
    headers = {
        "Authorization": auth_header
    }
    params = {
        "externalId": external_user_id
    }

    response = requests.get(url, headers=headers, params=params)

    if response.status_code == 200:
        user_claims = response.json()
        print(f"Subscriber ID: {user_claims.get('subscriberId')}")
        print(f"Products: {user_claims.get('products')}")
    else:
        print(f"Error: {response.status_code} - {response.text}")

.. code-block:: javascript
    :caption: JavaScript/Node.js Complete Example

    const axios = require('axios');

    // Configuration
    const apiBaseUrl = "https://api.info-subscription.com";
    const username = "your_username";
    const password = "your_password";
    const tenantId = "your_tenant_id";
    const externalUserId = "user@example.com";

    // Build authentication header
    const credentials = `${username}:${password}`;
    const encodedCredentials = Buffer.from(credentials).toString('base64');
    const authHeader = `Basic ${encodedCredentials}`;

    // Make the request
    const url = `${apiBaseUrl}/authorizations/identityprovider/${tenantId}/userclaims`;

    axios.get(url, {
        headers: {
            'Authorization': authHeader
        },
        params: {
            externalId: externalUserId
        }
    })
    .then(response => {
        const userClaims = response.data;
        console.log(`Subscriber ID: ${userClaims.subscriberId}`);
        console.log(`Products:`, userClaims.products);
    })
    .catch(error => {
        console.error(`Error: ${error.response?.status} - ${error.message}`);
    });

.. code-block:: csharp
    :caption: C# Complete Example

    using System;
    using System.Net.Http;
    using System.Net.Http.Headers;
    using System.Text;
    using System.Threading.Tasks;
    using Newtonsoft.Json;

    public class UserClaimsClient
    {
        private readonly HttpClient _httpClient;
        private readonly string _apiBaseUrl = "https://api.info-subscription.com";

        public UserClaimsClient(string username, string password)
        {
            _httpClient = new HttpClient();
            
            // Build authentication header
            var credentials = $"{username}:{password}";
            var encodedCredentials = Convert.ToBase64String(
                Encoding.UTF8.GetBytes(credentials)
            );
            
            _httpClient.DefaultRequestHeaders.Authorization = 
                new AuthenticationHeaderValue("Basic", encodedCredentials);
        }

        public async Task<UserClaims> GetUserClaimsAsync(
            string tenantId, 
            string externalUserId)
        {
            var url = $"{_apiBaseUrl}/authorizations/identityprovider/{tenantId}/userclaims";
            url += $"?externalId={Uri.EscapeDataString(externalUserId)}";

            var response = await _httpClient.GetAsync(url);
            response.EnsureSuccessStatusCode();

            var json = await response.Content.ReadAsStringAsync();
            return JsonConvert.DeserializeObject<UserClaims>(json);
        }
    }

    public class UserClaims
    {
        public string SubscriberId { get; set; }
        public Product[] Products { get; set; }
    }

    public class Product
    {
        public string Id { get; set; }
        public DateTime ValidFrom { get; set; }
        public DateTime ValidTo { get; set; }
    }

Use Cases
=========

ADB2C Custom Policies
---------------------

This endpoint is specifically designed to be called from ADB2C custom policies during the sign-in flow. The claims returned can be directly injected into the user's token.

Server-Side Authorization
-------------------------

For applications that perform authorization checks server-side, this endpoint provides a direct way to verify user access without parsing tokens.

Custom Identity Providers
-------------------------

If you're using a custom IdP other than ADB2C, this endpoint allows you to retrieve |projectName| authorization data and integrate it into your own authorization flow.

Comparison with Token-Based Flow
================================

.. table:: Token-Based vs API-Based Claims Retrieval

    ===========================  ======================================  ====================================
    Aspect                       Token-Based Flow                        API-Based Flow
    ===========================  ======================================  ====================================
    Use Case                     Client applications, SPAs                Server-to-server, custom policies
    Authentication               OIDC/OAuth2 user login                   HTTP Basic Auth (service account)
    Claims Location              Within JWT token                         API response
    User Interaction             Requires user login                      No user interaction
    Suitable For                 End-user authentication                  Backend integrations
    Documentation Reference      :ref:`auth-quick-start`                  This page
    ===========================  ======================================  ====================================

Security Considerations
=======================

.. warning::

    The credentials used for this endpoint provide access to user authorization data. Store them securely:
    
    * Never commit credentials to source control
    * Use environment variables or secure configuration management
    * Rotate credentials periodically
    * Restrict access to systems that need it

.. important::

    This endpoint should only be called from server-side code, not from client-side applications where credentials could be exposed.

Related Documentation
====================

* :ref:`Authentication and Authorization Quick Start <auth-quick-start>` - Token-based authorization flow
* :ref:`Product Authorization In Depth <auth-product-in-depth>` - Understanding authorization concepts
* :ref:`Microsoft ADB2C <adb2c-forgot-password>` - ADB2C-specific integration details
