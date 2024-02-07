.. _adb2c-sso:

Single Sign On
==============
By default all |projectName| provisioned |ADB2C| tenants are configured with SSO being enabled across the tenant.

In essence that means, that if a user is signed in to one application, for instance self-service, and have "Keep Me Signed In" toggled on, there should be no login prompt but instead he/she should be automatically signed in.

There is one requirement in that the login request should NOT include the query parameter `prompt=login`, as soon as that is included the SSO session is terminated.