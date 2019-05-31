.. _end-user-subscriber:

*********************
Subscriber User Model
*********************

|projectName| provides an out-of-the-box solution for managing users for subscribers.
The model is optional, but at the time of writing, is required when using the built in subscriber self-service client.

It is important to note that there are in principal two types of users. 
Those related to subscribers, and those related to administrative users of a tenant.
This section concerns itself about the subscriber users, i.e. the people buying subscriptions.

A user may or may not be connected to a customer, which in turn might be connected to a subscriber.
This model allows anyone to plug in their own user system or use the one provided by |projectName|.

When ordering subscriptions using the |projectName| Sales Poster, Users and Customers are automatically created and connected to each other.
It is also possible to connect an existing user to a customer using the :api-ref:`API <Customer/CustomerByIdConnectByIdentityProviderIdPost>`.

Having users, customers and subscribers connected is important to provide a streamlined authentication and authorization experience.

.. include:: authentication.rst

.. include:: authorization.rst

