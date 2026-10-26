.. _wordpress-access:

************************
WordPress Paywall Plugin
************************

The WordPress Paywall Plugin builds on
INFO-Subscription's :ref:`managed subscriber experience <managed-experience>` and
identity provider. It puts articles behind an INFO-Subscription paywall without
requiring you to write integration code.

Visitors sign in with their INFO-Subscription account through your tenant's Azure AD B2C
identity provider. Sign-in uses OpenID Connect's ``id_token`` flow and does not require a
client secret. Subscribers do not need WordPress accounts.

For installation, configuration, and updates, follow the
`plugin README <https://github.com/infosoftas/info-subscription-wordpress#readme>`_.
There you can also read about the plugin requirements and application registrations,
including the redirect URIs for subscriber sign-in and API product lookup.
Contact INFO-Subscription support to request the application registrations.

Article access
==============

Choose an access mode for each article:

* **AllAccess** — anyone can read the article.
* **UserLoggedIn** — the visitor must have an active INFO-Subscription sign-in session.
  A WordPress login alone does not grant access, and the subscriber does not need a
  selected product.
* **SelectedProducts** — the visitor must have at least one of the article's selected
  products. The plugin checks the subscriber's ``extension_Products`` claim; matching
  any one selected product is sufficient.

Visitors without access can see a teaser with sign-in and subscribe links, or be
redirected to a configurable subscribe page. Login-only articles show a sign-in prompt
or redirect to sign-in rather than a subscription prompt.

Editors and administrators who can edit an article can always preview it, including
protected content.

Selecting products
==================

The article editor can load the tenant's products with the product picker. An
administrator signs in interactively using authorization code with PKCE; no client
secret is used, and tokens are used once to load products and are never stored. The
picker retrieves products through ``GET /product``. Editors can also enter product IDs
manually, for example when the product list has not been loaded.

Settings can be locked by defining the plugin's constants in ``wp-config.php``. See the
`plugin README <https://github.com/infosoftas/info-subscription-wordpress#readme>`_ for
the available constants and configuration details.

Troubleshooting
===============

Start with the diagnostics on the plugin's settings page. They help identify
application-registration and API access problems. Common causes include a callback URI
registered on the wrong application or platform, or an API application without access
to the tenant. The
`README troubleshooting guidance <https://github.com/infosoftas/info-subscription-wordpress#diagnosing-api-authentication-failures>`_
covers common sign-in errors and their causes.
