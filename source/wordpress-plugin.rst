.. _wordpress-access:

************************
WordPress Paywall Plugin
************************

The WordPress Paywall Plugin lets visitors sign in with their subscriber account and restricts articles to signed-in subscribers or subscribers with selected products.
Subscribers do not need WordPress accounts.

The plugin is installed from `GitHub releases <https://github.com/infosoftas/info-subscription-wordpress/releases>`_ and is not yet listed in the WordPress.org plugin directory.
Installation, configuration, troubleshooting and updates are described in the `plugin README <https://github.com/infosoftas/info-subscription-wordpress#readme>`_.

Prerequisites
=============

The plugin relies on the |projectName| managed sign-in, so the tenant needs:

* The |projectName| provisioned |ADB2C|, as described in the :ref:`authentication quick start <auth-quick-start>`.
  Tenants using their own identity provider do not get the product claims the plugin requires.
* Products granted to users through :ref:`authorization sources <auth-product-in-depth>`.
  A subscriber without a mapped product authorization can sign in but does not get access to product-restricted articles.
* Two application registrations, requested from |projectName| support:

  * one in the tenant's sign-in instance, for subscriber sign-in on the site;
  * one in the main |projectName| instance with access to the tenant, used by editors to load the product list.

  The plugin settings page shows the redirect URIs to include in the request.

Article access
==============

Each article has one of the following access modes:

* **AllAccess** — anyone can read the article.
* **UserLoggedIn** — the visitor must be signed in with |projectName|. No product is required.
* **SelectedProducts** — the visitor must have a valid authorization for at least one of the selected products.

Product authorizations are read from the sign-in token, so changes such as a new purchase take effect the next time the subscriber signs in.
See :ref:`Accessing Product Authorizations <auth-product-in-depth>` for how authorizations end up in the token.

Visitors without access see a teaser with sign-in and subscribe links, or are redirected to a configurable page such as a :ref:`managed checkout <checkout>`.

Support
=======

Report plugin issues in the `plugin repository <https://github.com/infosoftas/info-subscription-wordpress/issues>`_.
For questions about application registrations, products or authorization sources, see :ref:`Support and Reporting Bugs <reporting-bugs>`.
