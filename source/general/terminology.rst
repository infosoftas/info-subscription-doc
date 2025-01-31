.. _terminology:

***************************
Terminology and Definitions
***************************

.. glossary::

    Subscriber
    Account Owner
        An entity who owns a given subscription is considered to be legally responsible for the subscription.
        All financial transactions for a subscription is associated with the subscriber (in the general case).

    End User
    User
        A person/entity who interacts with |projectName| either as a tenant/merchant or as a potential subscriber.

    Subscription
        An agreement for an organization to provide/deliver a service or product to a subscriber in a given period of time.
        A subscription is typically associated with a specific set of rules, called a plan, which describes the particular terms of the subscription.
        See :term:`plan` for details.

    Subscription Plan
    Package
        A set of rules that governs the details of a subscription, such as the duration, continuation, billing and fees.

    Template Subscription Plan
    Template Package
        A template to simplify the creation of new subscription plans. The template is used to create a new plan with a specific set of rules during order registrations.

    Organization
        A legal entity, company or similar who offers one or more products as a subscription.

    Payment
        A Payment

    Subscriber Account
        An account within an organization that belongs to a subscriber
    
    Product
        A product is something that is sold/purchased either as a service, benefit or a physical wares that can be subscribed to

    Payment Agreement
        An agreement on a means of payment/billing between an organization, a subscriber and optionally a third party that allows the organization to obtain payments from the subscriber.

    Payment Service Provider
    PSP
        From `wikipedia <https://en.wikipedia.org/wiki/Payment_service_provider>`_ : A payment service provider, offers sellers and merchants, services for accepting electronic payments by a variety of payment methods including credit card, bank-based payments such as direct debit, bank transfer, and real-time bank transfer based on online banking. 
        Typically, they use a software as a service model and form a single payment gateway for their clients (merchants) to multiple payment methods.

    NETS
    Mastercard Payment Solutions
    Bankgirot
    SwedbankPay
    VippsMobilePay
        A specific PSP - see :term:`PSP`

    eFaktura
        |eFaktura| is a Norwegian electronic invoicing method for invoicng through most Norwegian online banking solutions provided by :term:`astercard Payment Solutions`. May be combined with AvtaleGiro :term:`AvtaleGiro`

    Vipps
    MobilePay
        |Vipps| and |MobilePay| is a scandinavian App for payments managed by mobile phone, either through payment cards or direct bank account transfers behind the scenes. It is currently available in Norway, Denmark and Finland merchant payments.
    
    AvtaleGiro
        |AvtaleGiro| is the direct debit solution in Norway, handling recurring payments with little customer interaction after setup. It is provided by Mastercard Payment Solutions. May be combined with :term:`eFaktura`.

    Autogiro
        |Autogiro| is the B2C and B2B direct debit solution in Sweden, handling recurring payments with little customer interaction after setup. It is provided by :term:`Bankgirot`.

    BetalingsService
        |BetalingsService| is the B2C direct debit solution in Denmark, handling recurring payments with little customer interaction after setup. It is provided by :term:`Mastercard Payment Solutions`.

    Autogiro Norway
        Autogiro in Norway is a special direct debit solution for B2B payments, it should NOT be confused with the Swedish Autogiro variant. It is provided by :term:`Mastercard Payment Solutions`.


.. _conceptual_relationship:

*******************************
Conceptual Relationship Model
*******************************

The following diagram illustrates the conceptual relationships between the some of the entities and terms defined in this document.


.. figure:: /_images/relationship-model.png
    :alt: Conceptual Relationship Diagram
    :align: center
    :scale: 80%

    Simplified relationship between selected central entities.


.. note::

    Please note that the diagram is a simplification and does not cover all possible relationships between the entities.