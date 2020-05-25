.. _subscription-payment-agreements:

***************************
Payment Agreements
***************************
A payment agreement is essentially a record of details on how a subscription should be paid, or more specifically an agreement between the subscriber and the organization on how the organization should charge for the subscription.

In terms of the API, a Payment Agreement is an abstraction for various providers, and thus the most important information on a payment agreement is the Id, the Provider Reference and the Provider Type.
The provider type specifies which actual provider is used, while the reference is the key for that provider.

So for instance if the Provider Type is `PayEx` and the provider reference is `123456`, then essentially the PayEx Agreement Id is `123456`.

A subscriber may have more than one agreement at any time, but will always have at least one agreement as a fallback which is used for general invoicing.

****************************************
Creating and Changing Payment Agreements
****************************************

The process of creating and changing payment agreement is as follows:

1. Create Provider Agreement.
2. Create Payment Agreement.
3. Switch Agreement on current subscription.

For details on creating a new provider agreement, refer to the individual payment provider for details.

The following outlines a few more details, on the switching process.

Creating a new payment agreement is pretty simple using :api-ref:`the API </PaymentAgreement/AddAsync>`. Provide the `SubscriberId`, `ProviderType` and `ProviderReference`, and the agreement is created. Everything else is optional.

Switching payment agreements on a subscription requires invoking the action for :api-ref`switching agreements </Subscription/ChangePaymentAgreementForSubscription>`.

This will change the active agreement, and in case there is an outstanding payment request, the old one will be removed and a new one generated, and future payment requests will use the provided agreement.

It is possible to propagate changes through the various levels of the subscription chain if desired, this is typically useful for changing a payment agreement on a subscription that has already been renewed, but has not yet been paid.