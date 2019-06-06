.. _subscriber-authorization:

************************
Authorizing Subscribers
************************

Since the business defines the auhtorization procedure, this documentation will not provide a definitive authorization procedure.
This is an outline of an authorization procedure which will fit many businesses, and it assumes the use of the user model provided with INFO-Subscription.

The process is outlined here:

1. Determine which organization(s) the application is authorizing for (typically determined by the site/context)
2. Start an interactive login flow with Auth0 and let the user login.
3. Obtain the `SubscriberId` from the the id token.
4. :api-ref:`Get all subscriptions <Subscription/SubscriptionGet>` for the obtained `SubscriberId` and `OrganizationId` from the first step
5. If one or more subscriptions covers the current date (between starttime and endtime), the subscriber has access.

.. Important::
    Remember to check that the subscription covering the current date is indeed still valid, i.e. when was it cancelled if it was cancelled.

Expanding Authorization
=======================
There are a slew of options for authorization, the following outlines some approaches to obtain more information for a subscription which may help in granting or denying access.

Authorizing by plan or products
-------------------------------
Each subscription is associated with a plan (package in the API), each plan contains one or more products.
It is possible for the application which is authorizing to have a list of Plans or Products which grants access to various items.

Plans are typically used for bundling things together and special offers, and as such products typically have a closer relation with authorization needs, but it depends on the business what is most appropriate.

The basic flow would then be adapted with steps:

1. Let some administrative user map products by presenting them with :api-ref:`the products list <Product/ProductGet>` and keep the mapped list of product ids.
2. For all subscriptions thats cover the current date, verify that one/all products in the defined list is included in the subscription.

.. Note::
    In case of multiple subscriptions decide if a multi-product requirement can be met from different subscriptions or not.

Authorizing by Enterprise Plan
------------------------------
In some cases the application might not be authorizing for product access, but instead a report/dashboard view of an enterprise agreement.
For this scenario, adapt the login flow to determine if the Enterprise Plan of the subscription matches with the plan(s) for which information is required.

Authorizing historically
------------------------
Some businesses may require historic accuracy when authorizing. Typically that would be the case when granting access to an archieve or similar.

Modifying the basic flow as follows:

1. Determine the date or date-range of the archive item.
2. Determine if the subscription should fully cover the range, or just overlap partially 
3. When filtering for subscriptions don't use current time but use the time of the archive item.

