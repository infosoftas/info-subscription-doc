.. _users:

*****
Users
*****

The client may rely on the user and customer model provide by |projectName| or its own model.
This article describes the basics of using the |projectName| provided model.

.. Note::

    At the current time of writing, using the built-in subscriber self-service application 
    requires the use of the |projectName| user model to function.

The user model is based entirely on top of {AUTH0}


AddUser is a simple wrapper for creating new users with username/password without worrying about Auth0.