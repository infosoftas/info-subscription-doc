Managed Subcriber Experience
============================
The managed subscriber experience is a turn key solution for tenants that do not want to build their own customer facing solutions.

It consists of three parts which works in tandeem to provide a complete solution for end users (subscribers).

* An Identity Provider (IdP) utilized for user authentication (username/password, social accounts etc).
* A salesprocess that takes care of registering new users, subscribers and subscriptions complete with payment agreements, invoice contact details.
* A self-service management site where users can see and manage their subscriptions, change payment agreements and get an overview of their invoices.

While the components provided are enough to get most business going, there is typically some requirement to make them interact with an external web-site.
Either to funnel users into different sales processes (different plans, campaigns, products etc), or to authenticate and authorize users for consuming their content.

For further information head on over to our :ref:`authentication and authorization <auth-quick-start>` section or the :ref:`ordering/sales <salesposter>` quick start section.

Accessing Self-Service/Subscription Management
----------------------------------------------
Once an end-user/subscriber has made a purchase and created a user, regardless of how that was achieved, the user may need to manage the subscription or just see the latest invoice.

The self-service management solution can be access by navigating to https://{tenantName}-s4.azurewebsites.net where *tenantName* is the name of the tenant.

If the tenant is configured with a :ref:`custom domain <selfservice-custom-domain>` that domain may be used instead.