.. _wordpress-access:

************************
WordPress Paywall Plugin
************************

The WordPress Paywall Plugin builds on INFO-Subscription's :ref:`managed subscriber
experience <managed-experience>` and identity provider. It lets visitors sign in with
their INFO-Subscription account and restricts individual WordPress articles to the
appropriate audience. Visitors do not need WordPress accounts.

For installation, application registration, configuration, and updates, follow the
`plugin README <https://github.com/infosoftas/info-subscription-wordpress#readme>`_.
Download the installable ``infosub.zip`` from the
`GitHub releases <https://github.com/infosoftas/info-subscription-wordpress/releases>`_.
The README also lists the plugin requirements and the two application-registration
callbacks. The repository is private, so contact INFO-Subscription support if you need
access to the downloads or the registrations.

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

Visitors without access can be shown a teaser and sign-in or subscription prompt, or be
redirected to sign in or continue to checkout, depending on the site's configured
behavior. Login-only articles use a sign-in prompt or redirect rather than a
subscription prompt.

Selecting products
==================

The article editor can load the tenant's products with the product picker. An
administrator signs in interactively using authorization code with PKCE; no client
secret is used, and tokens are used once to load products and are never stored. The
picker retrieves products through ``GET /product``. Editors can also enter product IDs
manually, for example when the product list has not been loaded.

Troubleshooting
===============

Start with the diagnostics on the plugin's settings page. They help identify
application-registration and API access problems. Common causes include a callback URI
registered on the wrong application or platform, or an API application without access
to the tenant. The
`README troubleshooting guidance <https://github.com/infosoftas/info-subscription-wordpress#diagnosing-api-authentication-failures>`_
covers common sign-in errors and their causes.
