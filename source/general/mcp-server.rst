.. _mcp-server:

**********
MCP Server
**********

This page explains what MCP is in the context of INFO-Subscription and how to connect your AI tools quickly.

What is the INFO-Subscription MCP?
==================================

The `Model Context Protocol (MCP) <https://modelcontextprotocol.io>`_ is a standard for connecting AI assistants to external tools and data sources.
The INFO-Subscription MCP gives MCP-compatible assistants access to subscription, billing, order, subscriber, and catalogue data in your tenant.

The INFO-Subscription MCP server is available in two flavours:

.. list-table::
   :header-rows: 1

   * - Flavour
     - How it runs
     - Intended audience
   * - Remote server
     - Hosted HTTP endpoint, secured with Azure AD B2C JWT bearer auth
     - Teams and organisations wanting a shared, always-on connection (**preferred**)
   * - Local tool (``s4mcp``)
     - Installed as a .NET global tool, runs as a child process over stdio
     - Individual developers and power users on their own machine

What can you do with it?
========================

When connected, the AI assistant can query INFO-Subscription data on your behalf.

Supported capability areas:

* **Subscribers**: search subscribers, look up by GUID or subscriber number, and retrieve subscriber contacts
* **Subscriptions**: search subscription periods, get full period detail, and retrieve grouped lifetime history with renewals
* **Billing**: search invoices, get full invoice detail, get reminders and credit notes, and look up by invoice number
* **Orders**: search orders and retrieve full order detail including payment and transaction IDs
* **Catalogue**: list and search packages, products, organizations, and billing frequencies

Example prompts:

* ``Show me all active subscriptions for subscriber 10042``
* ``Find the invoice with number 88321 and summarise what was billed``
* ``Which subscribers have cancelled in the last 30 days?``
* ``List all packages available for organization X``
* ``What is the full renewal history for subscriber 10042?``

Prerequisites
=============

* .NET 10 runtime (for the local tool)
* An INFO-Subscription tenant ID (GUID)
* A B2C client ID (provided by Infosoft; the production default is pre-configured in the tool)

Getting started — Remote server (preferred)
===========================================

A hosted HTTP endpoint is available for teams who want a shared, always-on connection without installing the local tool.

Production endpoint:

.. code-block:: text

   https://mcp.info-subscription.com

Tenant-specific endpoint (recommended for users with access to multiple tenants):

.. code-block:: text

   https://mcp.info-subscription.com/<YOUR_TENANT_ID>

The server is also published in the main MCP registry for tools that support direct discovery:
`MCP Registry <https://registry.modelcontextprotocol.io/>`_.

Point your MCP client to the server URL and use ``http`` transport. Example:

.. code-block:: json

   {
     "mcpServers": {
       "s4": {
         "url": "https://mcp.info-subscription.com",
         "transport": "http"
       }
     }
   }

.. note::

   The remote server requires a valid Azure AD B2C access token.
   You can use the public client_id ``09ddd06c-dd1b-4782-8716-820ce6077e41``.
   If your client is not pre-configured, contact Infosoft to configure redirect URLs.
   You can also request a private client_id.
   A client_secret is not required; if a tool requires one, it is not supported at this time.
   MCP clients that support OAuth 2.0 Protected Resource Metadata can discover the authorization server automatically from ``https://mcp.info-subscription.com/.well-known/oauth-protected-resource``.
   Contact Infosoft to obtain the required scope and client registration details.

Getting started — Claude Desktop (remote MCP)
=============================================

Claude Desktop setup is UI-driven (not config-file-driven).
Use the connector flow in Claude Desktop to add a remote MCP server URL.
For current step-by-step instructions, see the official Claude guide:
`Get started with custom connectors using remote MCP <https://support.claude.com/en/articles/11175166-get-started-with-custom-connectors-using-remote-mcp>`_.

Getting started — Local tool (optional)
=======================================

Install the tool from NuGet.org:

.. code-block:: powershell

   dotnet tool install --global Infosoft.Info.Subscription.Mcp.LocalServer

Add to VS Code ``settings.json`` (user-level, all workspaces):

.. code-block:: json

   {
     "github.copilot.chat.mcp.servers": {
       "s4": {
         "command": "s4mcp",
         "args": ["--tenant", "<YOUR_TENANT_ID>"],
         "transport": "stdio"
       }
     }
   }

Or add a workspace-level ``.vscode/mcp.json``:

.. code-block:: json

   {
     "servers": {
       "s4": {
         "command": "s4mcp",
         "args": ["--tenant", "<YOUR_TENANT_ID>"],
         "type": "stdio"
       }
     }
   }

Replace ``<YOUR_TENANT_ID>`` with your INFO-Subscription tenant GUID.

Authentication note
===================

On first use, the local tool opens a browser window for sign-in via Azure AD B2C (PKCE flow).
After successful sign-in, the token is cached in the platform config folder.
Subsequent invocations are silent until the token expires, so no manual token management is required.
