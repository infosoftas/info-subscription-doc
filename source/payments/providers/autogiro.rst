.. _provider-autogiro:

Autogiro
========

Autogiro is the primary Swedish Direct Debit solution for both B2C and B2B, provided by Bankgirot. It allows recurring payments to be collected from customers' accounts with minimal customer interaction after the initial setup.

Mandate Registration
--------------------
In Autogiro terminology, an agreement is called a mandate. The following will use the term agreement and mandate interchangeably.

Autogiro provides an "out-of-band" style agreement registration, similar to :ref:`BetalingsService <provider-betalingsservice>`.

1. The customer receives a physical invoice or notification with identifiers (Payer Number, Bankgiro Number).
2. The customer registers this in their online banking solution.
3. A mandate is sent to the merchant via file transfers from Bankgirot.
4. Recurring payments can be charged on the consumer's account, associated with the specific mandate.

Since all of this is "out-of-band", there is little developer integration here.

The requirement is that an account is set up for Autogiro and that mandates and payments are imported using the files from Bankgirot.
|projectName| takes care of this for you, if configured during onboarding. Reach out to support to get help with this.

The rest is taken care of by |projectName| in terms of billing, payment generation etc.

Mandate Registration to First Payment Flow
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The following sequence diagram illustrates the complete flow from mandate registration through to the first payment claim:

.. mermaid::

   %%{init: { 'sequence': { 'mirrorActors': false } } }%%
   sequenceDiagram
      actor Customer
      participant Bank as Customer's Bank
      participant Bankgirot
      participant INFO-Subscription
      participant Merchant

      Note over Customer,Merchant: Mandate Registration Phase
      
      Merchant->>Customer: Send invoice with Payer Number & Bankgiro Number
      Customer->>Bank: Register Autogiro mandate in online banking
      Bank->>Bankgirot: Submit mandate registration
      
      Bankgirot->>INFO-Subscription: Send mandate file (approval)
      activate INFO-Subscription
      INFO-Subscription->>INFO-Subscription: Import and activate mandate
      INFO-Subscription->>INFO-Subscription: Create payment agreement
      deactivate INFO-Subscription
      
      Note over Customer,Merchant: Billing & Payment Phase
      
      INFO-Subscription->>INFO-Subscription: Generate invoice (billing cycle)
      INFO-Subscription->>INFO-Subscription: Create payment claim
      INFO-Subscription->>Bankgirot: Send payment file with claim
      
      Bankgirot->>Bank: Process payment request
      Bank->>Bank: Debit customer account
      Bank->>Bankgirot: Payment confirmation
      
      Bankgirot->>INFO-Subscription: Send payment confirmation file
      INFO-Subscription->>INFO-Subscription: Update payment status
      INFO-Subscription->>Merchant: Payment completed notification

Cancelling Mandates
-------------------
At any point in time, the consumer may cancel the mandate via their bank, in which case an alternate means should be used to get the payment.

|projectName| manages this scenario by:

* Disabling the mandate once a cancellation is received.
* Disabling the payment agreement and reverting to the default agreement (Invoice or Email).
* Generating reminders on Invoice since no payment is going to be received with Autogiro.