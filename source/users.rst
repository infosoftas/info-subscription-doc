.. _users:

*****
Users
*****

The client may rely on the user and customer model provide by |projectName| or its own model.
This article describes the basics of using the |projectName| provided model.

.. Note::

    At the current time of writing, using the built-in subscriber self-service application and the administrative application
    requires the use of the |projectName| user model to function.

    If you do not plan to write your own administrative client and you have your own user model, don't worry about the details here!

The user model is based entirely on top of {AUTH0}, meaning that whenever a reference exists to any form of User Id, this is in fact the {AUTH0} representation of said user.

Simple model
=================
For simple use cases, |projectName| provides a wrapper API for managing users.

It is provided as a simple alternative which only satisfies basic requirements.
We refer to this model as the simple model. 
For more advanced scenarios we recommend that client implements using the direct model (i.e. using {AUTH0} directly).

.. Note::

    There is nothing that prevents starting with the simple model and progressing to the direct model. 
    The backend is the same, the difference is only in the complexity of getting started and the number of features exposed.

    It is also possible to combine the different approaches, in fact this is how the |projectName| self-service application does it.

The simple model assumes a username/password creation flow and is not concerned about external identity providers such as Google, Facebook, LinkedIn or others.

Domain and connection
---------------------
The various API methods refer to authentication domain and authentication connection.
These values relate to the {AUTH0} communication. 

Typically these values are fixed and you won't have to worry about them other than obtaining the from Infosoft.

==========  =====
Connection  <Your Tenant Name>
Domain      infosubscription.eu.auth0.com
==========  =====

Creating a User
---------------

Creating a new user is straight forward and requires only a few things

* An Email
* A Name
* A Password

These are typically provide by the user in some sort of signup page.

Adding a user will create a new user at {AUTH0} and anyone with those credentials can now log in.

User Login
----------
We recommend the client follows the ``implicit`` credentials grant type as described in the :ref:`authorization` section if all that is needed is a verification of the users credentials.

Alternatively the client can make use of the :api-ref:`GetAccessToken <User/UserGetAccessTokenPost>` method to obtain an access token, and if granted use that for API communicaiton. 
This might be preferable in signup/order flows where requiring a signin by the user after a purchase is too cumbersome.

Connecting with a customer
--------------------------
Please refer to :ref:`customers` for details on how to connect users and customers.


Direct Model
============

When communicating with {AUTH0} directly, the client can make use of most of the features as described in the `Auth 0 Documentation <https://auth0.com/docs>`_ note however that you do not have management capabilities.

Given a ``client_id`` , ``client_secret`` and the ``Auth0 domain``, most of the sign-in/login options provided on the Auth0 site should be available. For assistance please :ref:`contact us <reporting-bugs>`.