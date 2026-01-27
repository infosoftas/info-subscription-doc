.. _auth-sessions:

Understanding Sessions and Session Management
=============================================

Understanding sessions and their scope, and the applications' roles, is important to understand how to implement a good user experience.

When using the managed experience provided with |projectName|, there are essentially two types of sessions to be aware of.

1. The IdP/Login session (managed by the |projectName| ADB2C tenant instance)
2. The Application/Local sessions (managed by you/your application), typically the session in a content management system, a self-service portal or similar.

.. Note::

    In case of multiple applications, there may very well be multiple application sessions, and multiple login sessions at the same time.

IdP/Login session
------------------
When a user is authenticated, a session is created in ADB2C for that user on that device/browser/app, which is the login session. 
The user is kept logged in until the user signs out, or until the session expires (whichever happens first). After the session is terminated, subsequent login requests will prompt the user to enter his/her credentials anew.

ADB2C provides IdP/Login session management via browser cookies only.

Persistent or Non-Persistent Sessions (Keep Me Signed In)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sessions may be persistent or non-persistent, meaning the IdP/Login session may be kept even if the browser is closed.
This is a persistent session, also known as "Keep Me Signed In".
For non-persistent sessions, the session is terminated when the browser is closed.

In ADB2C, the user is required to consider if the session should be persistent or not during sign-in.

.. Note::

    An explicit application sign-out will always terminate the sessions regardless of the persistence setup.

Application/Local Session
--------------------------
The application creates the application session after the user has been authenticated. 
For browser-based applications, this is typically stored in a cookie, but the details may vary depending on the technology.

The application session timeframe is determined by the application developer.
Typically, there are two ways to group applications and determine their session handling:

- Non-privileged access: Long sessions, typically measured in days, weeks and months. 
  The application allows access to less sensitive data. 
  Content consumption apps such as CMSs and streaming services fall into this category. 
  Sessions may be kept alive for some time even if the browser is closed.
- Privileged access: Short sessions, typically measured in minutes or hours. 
  The application allows access to sensitive data or restricted actions (payments, password changes, etc).
  Management applications such as self-service or e-commerce fall into this category.
  Sessions are typically terminated when browsers are closed.

User Experience
---------------
It is important to understand sessions when designing the optimal user experience for any given scenario.

In many cases, this design is a balance between multiple things such as:

- User convenience/ease of use
- Security
- Business needs

.. TIP::

    For non-privileged access scenarios such as content protection sites, we recommend starting with short-lived sessions, and no longer than 1 day before requiring an interaction with the IdP.
    
    Consider letting the access token expiry time define the application session to begin with.

    Understand the consequences to the authorisation flow if you change the application/local session lifetime.

Terminating Sessions/Logout
---------------------------

Application/Local logout is managed by the application. As with the creation of the session, the details are up to the application developer and technology, but typically it involves removing a cookie.
If the user wants to log in again, the application initiates a new authentication with ADB2C. Provided nothing has terminated the IdP/session, the user should be automatically authenticated and an application session can be created.

An application may initiate a logout with ADB2C to terminate the IdP/Login session; a subsequent login request will then prompt for credentials.

.. Note:: 
    
    ADB2C may be configured with front-channel logout to handle application logout when an IdP session is terminated.
    This is an advanced scenario and is rarely needed for low/non-privileged applications.


Default |projectName| IdP Session Behaviour
-------------------------------------------

For tenants with an ADB2C instance provisioned by Infosoft, there is a default behaviour setup which determines how the IdP/Login session works.
The following table describes the default behaviour of the ADB2C instances.

.. Table:: ADB2C Default Session Properties

    +--------------------------+-----------------------------------------------------------------------------------------------+
    | Property                 | Behaviour Description                                                                         |
    +==========================+===============================================================================================+
    | Persistence              | Users can choose whether to have persistent sessions or not.                                  |
    |                          | The default is persistent sessions if supported by the browser.                               |
    +--------------------------+-----------------------------------------------------------------------------------------------+
    | Persistence Lifetime     | 30 days (sliding, so if it is used repeatedly it lasts forever).                              |
    +--------------------------+-----------------------------------------------------------------------------------------------+
    | Non-Persistent Lifetime  | 24 hours                                                                                      |
    +--------------------------+-----------------------------------------------------------------------------------------------+
    | Access Token Lifetime    | 1 hour                                                                                        |
    +--------------------------+-----------------------------------------------------------------------------------------------+
    | Termination              | Sign-out only terminates the calling application's IdP/Login session.                         |
    +--------------------------+-----------------------------------------------------------------------------------------------+


Advanced Scenarios
==================
There are several advanced scenarios such as

* Keeping a user signed in using refresh tokens (breaks the automatic authorisation described in the quick start)
* Not prompting for login if already logged in elsewhere (prompt=none)
* Passwordless sign-in (requires ADB2C re-configuration and is a priced service add-on)

All of these scenarios are described in detail in the ADB2C documentation, so head over there for more details.

.. Note::

    While the official documentation describes a lot of options, not all of them are readily accessible using the managed experience due to cost optimisations and streamlining between tenants.
    Reach out to support if you want to know the costs.