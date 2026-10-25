.. _changelog-r147:

**********************************
2026 Release (Upcoming) - Draft
**********************************

.. note::

   These release notes are a draft and still in progress. The release date and the remaining items for this release will be added before the release.

.. TODO: Set the release date in the heading above, remove the draft note and add the remaining r147 items
   (API and Backend, Merchant Client, Self-Service, Sales Poster and Checkout) following the structure of earlier releases.

This release introduces a WordPress plugin, making it easy to put WordPress content behind your |ProjectName| subscriptions.

Hope you enjoy the new features! As always, we welcome your feedback and suggestions.


INFO-Subscription Access WordPress Plugin
=========================================

We are launching the first version (v0.1.0) of the "INFO-Subscription Access" WordPress plugin, allowing you to restrict access to articles on your WordPress site based on your subscribers' |ProjectName| subscriptions.

Visitors sign in with their |ProjectName| account through your tenant's Azure AD B2C sign-in using OpenID Connect, so no WordPress user accounts are needed for your subscribers. The plugin uses the id_token form_post flow and does not require a client secret.

Each article can be configured with one of the following access modes:

* **AllAccess** - the article is available to everyone.
* **UserLoggedIn** - the article is available to all signed-in users.
* **SelectedProducts** - the article is available to signed-in users with access to any one of the selected products, based on the ``extension_Products`` claim.

Visitors without access are shown a teaser with links to sign in or subscribe, or are redirected to a subscribe page.

Editors pick the products for an article from a list loaded from the |ProjectName| API. To load the list, an administrator signs in interactively using the authorization code flow with PKCE. Tokens are never stored by the plugin, and product IDs can also be entered manually.

The plugin requires WordPress 5.6 or newer, PHP 8.0 or newer and HTTPS. It is not yet available in the WordPress.org plugin directory; instead, an installable ``infosub.zip`` is attached to the v0.1.0 release on GitHub at https://github.com/infosoftas/info-subscription-wordpress. The plugin is licensed under the MIT licence.
