.. _customers:

*********
Customers
*********

|projectName| provides a simple model for adminstering customers, a customer is a person, company or other legal entity which can be identified by a name and an address.
A customer can serve as a :term:`subscriber` if there is no external customer management system (cypically a CRM).

Unlike a subscription, a customer is never associated with an :term:`organization` and is considered global. 
Keep this in mind if you have to decide on having one or multiple tenants.

.. Note::

    At the current time of writing, using the built-in subscriber self-service application 
    requires the use of the |projectName| customer model to function.
    Work is in progress to move towards a pure subscriber related model.

Creating A New Customer
=======================

There are two paths to creating a customer

#. By providing a user identity and details in one stage
#. By providing personal details and user identity separately

As detailed in the :api-ref:`refence docs </Customer/CustomerPost>`, there is an option for providing an ``identityProviderId``. 
If given the customer is automatically associated with the given user, if not the association will need to be created later to allow a customer to log in.

Refer to the :ref:`users` section for notes on how to create users.