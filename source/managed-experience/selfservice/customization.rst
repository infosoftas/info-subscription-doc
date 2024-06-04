.. _salesposter:

Orders and User Registration
============================

|projectName| contains a turnkey Salesposter/Ordering solution that can get organizations up and running in no time.

For tenants where the managed subscriber experience is enabled, the salesposter is available on a URL following the template: https://{tenantName}-s4.azurewebsites.net/salesposter, where *tenantName* is the name of the tenant.

If the tenant is configured with a :ref:`custom domain <selfservice-custom-domain>` that domain may be used instead of the azurewebsites subdomain, such as https://subscription.example.com/salesposter

Creating new subscriptions is as simple as providing the user with a link to the salesposter. 
Afterwards a user will exist that can be :ref:`authenticated and authorized <auth-quick-start>` by external parties, and recurring billing will follow automatically until the subscription is cancelled.

Try it out using our experimentation site https://experimentation-s4.azurewebsites.net/salesposter

Configuration Parameters for the ordering process
-------------------------------------------------
There are two levels/areas of configuration for the salesposter.

A set of configuration options are static i.e. it does not vary from sale to sale or subscriber to subscriber, and is configured during onboarding and in some cases via the Merchant interface of |projectName|.
These are things covered by the user documentation and as such are not relevant from a technical/integration standpoint.

Another set of configurations are dynamic and varies from process to process. These options can be changed from session to session at will.

The Salesposter primarily uses URL query parameters to control presentation and validation logic.

Once a user follows the link with query parameters, they are copied to an encrypted cookie and stored throughout the ordering process.
To change these params, simply make a new URL with different values.

The following table outlines the various parameters, some have a set of fixed possible values.

+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| Parameter Name    | Description                                                  | Default Value      | Possible values                                    |
+===================+==============================================================+====================+====================================================+
| lang              | Defines the display language                                 | nor (Norwegian)    | :ref:`Available Languages <languages>`             |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| redirect          | A redirection location for when the order has completed      |                    | Any URL                                            |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| pty               | A list of available payment types                            | 1 (Swedbank Pay)   | :ref:`Payment Types <paymenttypes>`                |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| loginWith         | Defines which user credential providers to expose            | internal           | :ref:`Credential Providers <credentialproviders>`  |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| sourceUrl         | An encoded URL that will be sent to **Kilkaya** for tracking | Off                | Any encoded string                                 |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| templatepackageid | Subscription Plan Id being ordered                           | Custom             | Any valid Template Plan                            |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| organization_id   | The Organization the order should be placed on               | Custom             | Any valid organization                             |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| adr               | Controls the address section                                 | On                 | :ref:`Mandatory Toggle Options <mandatorytoggle>`  |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| tel               | Controls the phone section                                   | On                 | :ref:`Mandatory Toggle Options <mandatorytoggle>`  |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| org               | Controls the organization number section                     | On                 | :ref:`Mandatory Toggle Options <mandatorytoggle>`  |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| inv               | Controls the invoice Contact section                         | Off                | :ref:`Mandatory Toggle Options <mandatorytoggle>`  |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| invtext           | Header text for invoice contact section                      | Language dependent |                                                    |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| orginv            | Controls additional organizaiton number section              | Off                | :ref:`Mandatory Toggle Options <mandatorytoggle>`  |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| co                | Controls the co section                                      | Off                | :ref:`Mandatory Toggle Options <mandatorytoggle>`  |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| invref            | Controls primary contact buyer reference section             | Off                | :ref:`Mandatory Toggle Options <mandatorytoggle>`  |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+
| invpayref         | Controls invoice contact buyer reference section             | Off                | :ref:`Mandatory Toggle Options <mandatorytoggle>`  |
+-------------------+--------------------------------------------------------------+--------------------+----------------------------------------------------+

The following is a series of options tables (referenced by each parameter above).

.. _languages:

.. list-table:: Language Options
   :header-rows: 1

   * - Value
     - Description
   * - eng
     - English
   * - nor
     - Norwegian
   * - swe
     - Swedish
   * - sam
     - Northern Sami

.. _paymenttypes:

.. list-table:: Payment Type Options
   :header-rows: 1

   * - Value
     - Description
   * - 1
     - {payex}
   * - 2
     - {vipps}
   * - 3
     - Email
   * - 4
     - EHF
   * - 5
     - {mobilePay}
   * - 7
     - OIO
   * - 9
     - Invoice


.. _credentialproviders:

.. list-table:: Credential Providers
   :header-rows: 1

   * - Value
     - Description
   * - Internal
     - Uses internal login mechanism ("local" users)
   * - Google
     - Google accounts
   * - Facebook
     - Facebook accounts

.. _mandatorytoggle:

.. list-table:: Optional/Mandatory Toggling Options
   :header-rows: 1

   * - Value
     - Description
   * - On
     - Shows the section
   * - Off
     - Disables/Hides the section
   * - Required
     - Shows the section and makes it mandatory to fill

.. admonition:: Simple Example

    The following is an example of how the Salesposter may be configured to do a specific thing.
    In this case the configuration does the following:

    * Restricts the Payment Type to be Swedbank Pay
    * Overrides the default Subscription Plan
    * Uses a :ref:`custom domain <selfservice-custom-domain>` (not really salesposter specific).

    Example Url
    
    https://experimentation.minside.info-subscription.com/salesposter?pty=1&templatepackageid=14714f54-dbf4-4899-a9c7-51763d536568
