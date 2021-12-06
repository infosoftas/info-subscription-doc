URL parameters
=========================================
Salesposter uses URL query string to control presentation and business logic. Once a user follows the link with query parameters, they are copied to an encrypted cookie. To change these params, simply make a new URL with different values.

Salesposter location follows the following template: https://{tenantName}-s4.azurewebsites.net/salesposter, where *tenantName* - name of the tenant Salesposter is deployed on.

Query string parameters are:

* **sourceurl** - (optional) URL Salesposter was accessed from. Used to track traffic using **Kilkaya**
* **lang** - (optional, default value - **nor**) Site language. Possible values:

+--------+-------------+
|  Value | Description |
+========+=============+
|  eng   |   English   |
+--------+-------------+
|  nor   |  Norwegian  |
+--------+-------------+
|  swe   |   Swedish   |
+--------+-------------+

* **templatepackageid** - (optional) Subscription plan identifier
* **organization_id** - (optional) Organization identifier
* **account_id** - (optional) PayEx account identifier
* **pty** - (optional, default value - **PayEx**) Available payment types, separated by **","**. Possible values:

+----------+--------------+
|  Value   | Description  |
+==========+==============+
|   PayEx  |   English    |
+----------+--------------+
|   Vipps  |  Norwegian   |
+----------+--------------+
|  Invoice |   Swedish    |
+----------+--------------+

* **order** - (optional, default value - **On**) Controls "Subscription Plan" section on login. Possible values:

+----------+--------------------+
|  Value   |     Description    |
+==========+====================+
|   On     |    Shows section   |
+----------+--------------------+
|   Off    |    Hides section   |
+----------+--------------------+

* **tax** - (optional, default value - **On**) Controls whether subscription plan has tax or not. Possible values:
  
+----------+--------------------+
|  Value   |     Description    |
+==========+====================+
|   On     |    Enables tax     |
+----------+--------------------+
|   Off    |    Disables tax    |
+----------+--------------------+

* **loginwith** - (optional, default value - **Internal,Google,Facebook**) Available login types, separated by **","**. Possible values:

+---------------+----------------------------------------+
|    Value      |            Description                 |
+===============+========================================+
|   Internal    |    Uses internal login mechanism       |
+---------------+----------------------------------------+
|    Google     |    Google account                      |
+---------------+----------------------------------------+
|   Facebook    |    Facebook account                    |
+---------------+----------------------------------------+

* **adr** - (optional, default value - **On**) Controls address section during order creation. Possible values:

+--------------+--------------------------------------+
|  Value       |     Description                      |
+==============+======================================+
|   On         |    Shows section                     |
+--------------+--------------------------------------+
|   Off        |    Hides section                     |
+--------------+--------------------------------------+
|  Required    |    Makes section mandatory to fill   |
+--------------+--------------------------------------+

* **tel** - (optional, default value - **On**) Controls phone section during order creation. Possible values:

+--------------+--------------------------------------+
|  Value       |     Description                      |
+==============+======================================+
|   On         |    Shows section                     |
+--------------+--------------------------------------+
|   Off        |    Hides section                     |
+--------------+--------------------------------------+
|  Required    |    Makes section mandatory to fill   |
+--------------+--------------------------------------+

* **inv** - (optional, default value - **Off**) Controls additional contact section during order creation. Possible values:

+--------------+--------------------------------------+
|  Value       |     Description                      |
+==============+======================================+
|   On         |    Shows section                     |
+--------------+--------------------------------------+
|   Off        |    Hides section                     |
+--------------+--------------------------------------+
|  Required    |    Makes section mandatory to fill   |
+--------------+--------------------------------------+

* **invtext** - (optional, default value - **Invoicepayer**) Header text for additional contact section during order creation
* **orginv** - (optional, default value - **Off**) - Controls additional contact organization number section during order creation. Possible values:

+--------------+--------------------------------------+
|  Value       |     Description                      |
+==============+======================================+
|   On         |    Shows section                     |
+--------------+--------------------------------------+
|   Off        |    Hides section                     |
+--------------+--------------------------------------+
|  Required    |    Makes section mandatory to fill   |
+--------------+--------------------------------------+

* **co** - (optional, default value - **Off**) - Controls CO section during order creation. Possible values:

+--------------+--------------------------------------+
|  Value       |     Description                      |
+==============+======================================+
|   On         |    Shows section                     |
+--------------+--------------------------------------+
|   Off        |    Hides section                     |
+--------------+--------------------------------------+
|  Required    |    Makes section mandatory to fill   |
+--------------+--------------------------------------+

* **org** - (optional, default value - **On**) - Controls organization number section during order creation. Possible values:

+--------------+--------------------------------------+
|  Value       |     Description                      |
+==============+======================================+
|   On         |    Shows section                     |
+--------------+--------------------------------------+
|   Off        |    Hides section                     |
+--------------+--------------------------------------+
|  Required    |    Makes section mandatory to fill   |
+--------------+--------------------------------------+

* **redirect** - (optional) - includes 2 parameters separated by **",**. Must be exactly in this order:
    1. URL to redirect to after order has been completed
    2. (optional, default value - 3) Delay (in seconds) before the redirect

* **invref** - (optional, default value - **Off**) - Controls primary contact buyer reference section. Possible values:

+--------------+--------------------------------------+
|  Value       |     Description                      |
+==============+======================================+
|   On         |    Shows section                     |
+--------------+--------------------------------------+
|   Off        |    Hides section                     |
+--------------+--------------------------------------+
|  Required    |    Makes section mandatory to fill   |
+--------------+--------------------------------------+

* **invpayref** - (optional, default value - **Off**) - Controls additional contact invoice reference section. Possible values:

+--------------+--------------------------------------+
|  Value       |     Description                      |
+==============+======================================+
|   On         |    Shows section                     |
+--------------+--------------------------------------+
|   Off        |    Hides section                     |
+--------------+--------------------------------------+
|  Required    |    Makes section mandatory to fill   |
+--------------+--------------------------------------+

Example
-----------------------------------
Here is an example on how to order a specific subscription plan with PayEx payment only using Salesposter deployed on *experimentation* tenant.

https://experimentation-s4.azurewebsites.net/salesposter?pty=PayEx&templatepackageid={some-template-package-id}