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
INFO-Subscription contains a small ammount personal data, that will allow you to manage simple information about a subscriber. 
It is not a fully fledged CRM system, neither is it going to attempt to fulfil that role. 

However, it is possible to integrate with third party CRMs to synchronize data in a reactive manner, so everyone can bring their own CRM.

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
|projectName| provides capabilities to:

 * Create new subscriptions.
 * Handle cancelations and upgrades/downgrades subscriptions (both planned and immediate adjustments).
 * Customize billing cycles to suit various business needs.
 * Automatic proration for upgrades/downgrades.

In this case billing is the process of figuring out when and which subscribers should receive an invoice, and produce said invoices based on the details of the purchased plan/product.
Additionally billing refers to handling of payments and making sure that subscriptions are cancelled on missing payments etc.

Automatic Payments
^^^^^^^^^^^^^^^^^^
Part of the billing engine also manages automatic payments with cards, direct debit and similar, making sure that most subscribers pay the right amount at the right time.

Automated Dunning
^^^^^^^^^^^^^^^^^
Sometimes subscribers neglects to pay their invoices, in these cases |projectName| makes it possible to automate dunning procedure to generate reminders, and adding handling fees etc.