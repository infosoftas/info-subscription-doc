.. _provider-efaktura:

eFaktura
=========
eFaktura is a Norwegian eInvoicing solution providing consumers with an electronic invoice directly within their online banking system. It is provided by Master Card Payment Services.

Unlike many of the other recurring payment systems, there is no automatic payment, the consumer still has to accept the Invoice, but doing so is almost trivial.

Consignment or Mandate Registration
----------------------------------

The terminology has historically been a bit confusing, but similar to |AvtaleGiro| an organization needs a consignment or agreement or mandate from the Subscriber to send him/her an efaktura Invoice.
eFaktura registration is an "out-of-band" process where the subscriber accepts eFaktura in general (not for the specific organization). 
Then it is up to the Organization to determine if the subscriber should have eFaktura or not.

|projectName| implements eFaktura with the following process

1. The subscriber registers for eFaktura 2.0 in their online bank (or a similar location).
2. An eFaktura Search is done on a regular basis by |projectName|.
3. New agreements are created (if not blocked).
4. Cancelled/Blocked agreements are removed.
5. Running subscriptions are automatically switched to new eFaktura agreements.
6. Recurring payments are invoiced using the new agreements.

Since all of this is "out-of-band", there is little developer integration here.

The requirements is that an account is setup for eFaktura, |projectName| automatically takes care of the rest.

The following sequence diagram illustrates the mandate registration and first invoice generation process:

.. mermaid::

   %%{init: { 'sequence': { 'mirrorActors': false } } }%%
   sequenceDiagram
      actor Subscriber
      participant OnlineBank
      participant INFO-Subscription
      participant MastercardPaymentServices
      
      Note over Subscriber,OnlineBank: Registration Phase
      Subscriber->>OnlineBank: Register for eFaktura 2.0
      activate OnlineBank
      OnlineBank->>MastercardPaymentServices: Register eFaktura consent
      MastercardPaymentServices-->>OnlineBank: Consent registered
      OnlineBank-->>Subscriber: eFaktura 2.0 activated
      deactivate OnlineBank
      
      Note over INFO-Subscription,MastercardPaymentServices: Agreement Discovery
      loop Periodic Search
          INFO-Subscription->>MastercardPaymentServices: Search for eFaktura agreements
          activate MastercardPaymentServices
          MastercardPaymentServices-->>INFO-Subscription: Return available agreements
          deactivate MastercardPaymentServices
          INFO-Subscription->>INFO-Subscription: Create new agreements (if not blocked)
          INFO-Subscription->>INFO-Subscription: Switch running subscriptions to eFaktura
      end
      
      Note over INFO-Subscription,Subscriber: Invoice Generation
      INFO-Subscription->>INFO-Subscription: Generate invoice for subscription
      INFO-Subscription->>MastercardPaymentServices: Submit eFaktura invoice
      activate MastercardPaymentServices
      MastercardPaymentServices->>OnlineBank: Deliver eFaktura invoice
      deactivate MastercardPaymentServices
      OnlineBank->>Subscriber: eFaktura invoice available
      Subscriber->>OnlineBank: Review and accept invoice
      OnlineBank->>Subscriber: Payment confirmed

Combining with AvtaleGiro
----------------------------------

Technically it is possible to combine eFaktura and AvtaleGiro into a common request, one that provides a visual representation of the Invoice (eFaktura), and one that takes care of the automated payment (AvtaleGiro).
At the current time of writing this is not provided by |projectName|.

Cancelling Agreements
---------------------------------------------------------

At any point in time, the consumer may block the issuer thus cancelling the agreement, in which case an alternate means should be used to get the payment.

|projectName| manages this scenario by:

* Disabling the agreement once a cancellation is discovered (regular scanning)
* Disabling the payment agreement and reverting to the default agreement (Invoice).
* Generating reminders on Invoice since no payment are going to be received with eFaktura.