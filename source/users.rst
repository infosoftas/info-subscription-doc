.. _users:

*****
Users
*****

The client may rely on the user and customer model provide by |projectName| or its own model.
This article describes the basics of using the |projectName| provided model.

.. Note::

    At the current time of writing, using the built-in subscriber self-service application 
    requires the use of the |projectName| user model to function.

The user model is based entirely on top of {AUTH0}, meaning that whenever a reference exists to any form of User Id, this is in fact the {AUTH0} representation of said user.

Lightweight model
=================
For simple use cases, |projectName| provides a wrapper API for managing users.

It is provided as a simple alternative which only satisfies basic requirements.
We refer to this model as the lightweight model. 
For more advanced scenarios we recommend that client implements using the Direct model (i.e. using {AUTH0} directly).

The lightweight model assumes a username/password creation flow and is not concerned about external identity providers such as Google, Facebook, LinkedIn or others.

Creating a User
---------------

Creating a new user requires a few things

* An Email
* A Name
* A Password
* A connection
* A domain

The first three are typically provided by the user. 

The connection and domain are 

AddUser is a simple wrapper for creating new users with username/password without worrying about Auth0.