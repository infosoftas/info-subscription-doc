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

1. An eFaktura Search is done on a regular basis.
2. New agreements are created (if not blocked).
3. Cancelled/Blocked agreements are removed.
4. Running subscriptions are automatically switched to new eFaktura agreements.
5. Recurring payments are invoiced using the new agreements.

Since all of this is "out-of-band", there is little developer integration here.

The requirements is that an account is setup for eFaktura, |projectName| automatically takes care of the rest.

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