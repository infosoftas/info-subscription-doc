.. _api-based-user-claims:

*************************************
API-Based User Claims Retrieval
*************************************

While the token-based authorization flow described in the :ref:`quick start <auth-quick-start>` is the most common approach, there are scenarios where obtaining user claims directly via an API call is more suitable.

This alternative approach allows you to retrieve user authorization information without relying on the token login flow, making it particularly useful for:

* Server-to-server integrations
* Custom authorization processes
* Token enrichment with self-managed ADB2C instances or other IdP solutions
* Scenarios where token-based flows are not practical

API Endpoint Overview
=====================

The endpoint ``/authorizations/identityprovider/{tenantId}/userclaims`` returns a dictionary of user claim names and string values.

While this endpoint is designed to be consumed directly by ADB2C during custom policy execution, it can also be used by other authorization processes that need to retrieve user claims programmatically.

This claims endpoint is distinct from the OAuth-authenticated product lookup ``GET /authorizations/identityprovider/{identityProviderId}/user/{externalId}``, which returns product IDs rather than claims.

Authentication Requirements
===========================

.. important::

    This endpoint requires special authentication as it is built to support ADB2C direct integrations and server-to-server scenarios.

The authentication method uses HTTP Basic Authentication with a username and password obtained from your Identity Provider setup in |projectName|.

Obtaining Credentials
----------------------

Username and password credentials for this endpoint can be obtained in one of two ways:

1. Directly from the IdP setup in |projectName|
2. From your support contact

Please :ref:`contact support <reporting-bugs>` if you need assistance obtaining these credentials.

Authentication Header
----------------------

To authenticate with the endpoint:

1. Concatenate the username and password separated by a colon (``:``)
2. Base64 encode the concatenated string
3. Include the encoded string in the ``Authorization`` header

.. code-block:: text
    :caption: Authentication Format

    Authorization: Basic {base64encode("{username}:{password}")}

Example
-------

.. tabs::

   .. code-tab:: python Python

        import base64

        username = "your_username"
        password = "your_password"
        
        # Concatenate username and password with a colon
        credentials = f"{username}:{password}"
        
        # Base64 encode the credentials
        encoded_credentials = base64.b64encode(credentials.encode()).decode()
        
        # Build the Authorization header
        auth_header = f"Basic {encoded_credentials}"

   .. code-tab:: javascript JavaScript

        const username = "your_username";
        const password = "your_password";
        
        // Concatenate username and password with a colon
        const credentials = `${username}:${password}`;
        
        // Base64 encode the credentials
        const encodedCredentials = Buffer.from(credentials).toString('base64');
        
        // Build the Authorization header
        const authHeader = `Basic ${encodedCredentials}`;

   .. code-tab:: csharp C#

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

   .. code-tab:: php PHP

        <?php
        $username = "your_username";
        $password = "your_password";
        
        // Concatenate username and password with a colon
        $credentials = $username . ":" . $password;
        
        // Base64 encode the credentials
        $encodedCredentials = base64_encode($credentials);
        
        // Build the Authorization header
        $authHeader = "Basic " . $encodedCredentials;
        ?>

Making the API Request
======================

Once you have constructed the authentication header, you can make a request to the endpoint.

Request Format
--------------

.. code-block:: http
    :caption: HTTP Request

    POST /authorizations/identityprovider/{tenantId}/userclaims HTTP/1.1
    Host: api.info-subscription.com
    S4-TenantId: {tenantId}
    Authorization: Basic {encodedCredentials}
    Content-Type: application/json

    {"objectId":"{externalUserId}"}

Parameters
----------

.. table:: Request Parameters

    =============  ========  ====================================================================
    Parameter      Location  Description
    =============  ========  ====================================================================
    tenantId       Path and  The |projectName| tenant ID, supplied in both the URL path and the
                   Header    ``S4-TenantId`` header
    objectId       JSON body The user's identifier in the Identity Provider
    =============  ========  ====================================================================

Response Format
---------------

The endpoint returns the claims configured for the user in the Identity Provider, as a dictionary of claim names to string values.

.. code-block:: json
    :caption: Sample Response

    {
        "claimName": "string value"
    }

.. note::

    This is an illustrative example only.

Complete Example
================

.. tabs::

   .. code-tab:: python Python

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
            "Authorization": auth_header,
            "S4-TenantId": tenant_id,
            "Content-Type": "application/json"
        }

        response = requests.post(url, headers=headers, json={"objectId": external_user_id})

        if response.status_code == 200:
            user_claims = response.json()
            print(user_claims)
        else:
            print(f"Error: {response.status_code} - {response.text}")

   .. code-tab:: javascript JavaScript

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

        axios.post(url, {
            objectId: externalUserId
        }, {
            headers: {
                'Authorization': authHeader,
                'S4-TenantId': tenantId,
                'Content-Type': 'application/json'
            }
        })
        .then(response => {
            const userClaims = response.data;
            console.log(userClaims);
        })
        .catch(error => {
            console.error(`Error: ${error.response?.status} - ${error.message}`);
        });

   .. code-tab:: csharp C#

        using System;
        using System.Collections.Generic;
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

            public async Task<Dictionary<string, string>> GetUserClaimsAsync(
                string tenantId, 
                string externalUserId)
            {
                var url = $"{_apiBaseUrl}/authorizations/identityprovider/{tenantId}/userclaims";
                var requestBody = JsonConvert.SerializeObject(new { objectId = externalUserId });
                using var content = new StringContent(requestBody, Encoding.UTF8, "application/json");
                using var request = new HttpRequestMessage(HttpMethod.Post, url)
                {
                    Content = content
                };
                request.Headers.Add("S4-TenantId", tenantId);

                var response = await _httpClient.SendAsync(request);
                response.EnsureSuccessStatusCode();

                var json = await response.Content.ReadAsStringAsync();
                return JsonConvert.DeserializeObject<Dictionary<string, string>>(json);
            }
        }

   .. code-tab:: php PHP

        <?php
        // Configuration
        $apiBaseUrl = "https://api.info-subscription.com";
        $username = "your_username";
        $password = "your_password";
        $tenantId = "your_tenant_id";
        $externalUserId = "user@example.com";

        // Build authentication header
        $credentials = $username . ":" . $password;
        $encodedCredentials = base64_encode($credentials);
        $authHeader = "Basic " . $encodedCredentials;

        // Make the request
        $url = $apiBaseUrl . "/authorizations/identityprovider/" . $tenantId . "/userclaims";

        $options = [
            'http' => [
                'header'  => "Authorization: " . $authHeader . "\r\n" .
                    "S4-TenantId: " . $tenantId . "\r\n" .
                    "Content-Type: application/json\r\n",
                'method'  => 'POST',
                'content' => json_encode(['objectId' => $externalUserId]),
            ]
        ];

        $context  = stream_context_create($options);
        $result = file_get_contents($url, false, $context);

        if ($result !== false) {
            $userClaims = json_decode($result, true);
            print_r($userClaims);
        } else {
            echo "Error fetching user claims\n";
        }
        ?>

Use Cases
=========

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
=====================

* :ref:`Authentication and Authorization Quick Start <auth-quick-start>` - Token-based authorization flow
* :ref:`Product Authorization In Depth <auth-product-in-depth>` - Understanding authorization concepts
* :ref:`Microsoft ADB2C <adb2c-forgot-password>` - ADB2C-specific integration details
