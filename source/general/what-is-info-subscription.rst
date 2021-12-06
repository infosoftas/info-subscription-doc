.. _what-is-it:

*********************
What is |projectName|
*********************

|projectName| is a service that provides subscription billing and management, in simple terms it creates invoices, manages payments and maintains subscriptions based on these invoices and payments.

What is it not?
===============
Depending on your point of view it might be easier to understand what it is by describing what it isn't 

CRM
---
INFO-Subscription contains a small customer management module, that will allow you to manage simple information about a customer. 
It is not a fully fledged CRM system, neither is it going to attempt to fulfil that role. We do however plan to provide options for integrating with third party CRMs so you can bring your own.

.. Note::
    
    Currently external CRMs are not directly supported, but we are actively working on it! 
    In the mean time, the existing Customer backend is rather simple and there are no obvious issues with making it a slave to an external sync process.

Delivery, Distribution and Packaging
------------------------------------
Many subscriptions requires some sort of physical distribution of products. 
While |projectName| is somewhat capable of producing information to distribution and packaging systems, it is not capable of generating package slips, driver routes etc.

Magic
-----
No, unfortunately it is not powered by magic just yet, but we have contacted Dr Strange in an attempt to get a Powered By Magic integration.

What |projectName| does
========================
So that was a list of things |projectName| does not do, now then what does it actually do.
While not a complete feature list it gives you an overview of what you can expect. For feature information refer to the {PRODUCTWEBSITE}

Subscription Management and Billing 
-----------------------------------
|projectName| provides capabilities to create, cancel and upgrade/downgrade subscriptions, in relation to custom configured plans which helps drive billing.

In this case billing is the process of figuring out when and which subscribers should receive an invoice, and produce said invoices based on the details of the plan.
Additionally billing refers to handling of payments and making sure that subscriptions are cancelled on missing payments etc.

Automatic Payments
^^^^^^^^^^^^^^^^^^
Part of the billing engine also manages automatic payments with cards, direct debit and similar, making sure that most subscribers pay the right amount at the right time.

