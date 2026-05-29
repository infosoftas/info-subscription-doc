.. _mcp-server:

*****************************************
INFO-Subscription MCP for AI Assistants
*****************************************

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
   * - Local tool (``s4mcp``)
     - Installed as a .NET global tool, runs as a child process over stdio
     - Individual developers and power users on their own machine
   * - Remote server
     - Hosted HTTP endpoint, secured with Azure AD B2C JWT bearer auth
     - Teams and organisations wanting a shared, always-on connection

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
* ``Which subscribers in Oslo have cancelled in the last 30 days?``
* ``List all packages available for organization X``
* ``What is the full renewal history for subscriber 10042?``

Prerequisites
=============

* .NET 10 runtime (for the local tool)
* An INFO-Subscription tenant ID (GUID)
* A B2C client ID (provided by Infosoft; the production default is pre-configured in the tool)

Getting started — VS Code (GitHub Copilot)
===========================================

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

Getting started — Claude Desktop
================================

Install the tool (same command as above), then edit the Claude Desktop config file:

* **macOS:** ``~/Library/Application Support/Claude/claude_desktop_config.json``
* **Windows:** ``%APPDATA%\\Claude\\claude_desktop_config.json``

.. code-block:: json

   {
     "mcpServers": {
       "s4": {
         "command": "s4mcp",
         "args": ["--tenant", "<YOUR_TENANT_ID>"]
       }
     }
   }

Authentication note
===================

On first use, the local tool opens a browser window for sign-in via Azure AD B2C (PKCE flow).
After successful sign-in, the token is cached in the platform config folder.
Subsequent invocations are silent until the token expires, so no manual token management is required.

Remote server (optional / advanced)
===================================

A hosted HTTP endpoint is available for teams who want a shared, always-on connection without installing the local tool.

Production endpoint:

.. code-block:: text

   https://mcp.info-subscription.com

Tenant-specific endpoint (recommended for users with access to multiple tenants):

.. code-block:: text

   https://mcp.info-subscription.com/<YOUR_TENANT_ID>

Example Claude Desktop configuration using HTTP transport:

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
   MCP clients that support OAuth 2.0 Protected Resource Metadata can discover the authorization server automatically from ``https://mcp.info-subscription.com/.well-known/oauth-protected-resource``.
   Contact Infosoft to obtain the required scope and client registration details.
