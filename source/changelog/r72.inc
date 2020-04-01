.. _changelog-r72:

**************************
Release April 1st 2020
**************************
The following changes rolled out to production on April 1st 2020.

API and Backend
===============
The following new features and improvements are now available in the API and the backend.

* Fixed an issue that would sometimes cause Invoice query models to not be generated resulting in a bad filtering/querying experience.
* Recurring Deliveries integration for Distribution Innovation (preview).
* Behaviour change: When matching payments to payment demands and invoices, the payment service now considers the state of the demand. If a demand is already paid or credited the payment will not be considered a match as it is most likely a duplicate payment and should be assigned the subscriber account or removed.

Client
======
The following new features and improvements are now available in the self-service and merchant client.

* Added "Number of copies" in the subscriptions list for the merchant.
* Fixed an error where the amount was not included when exporting invoice lists.
* Multiple navigational adjustments in the merchant system menu.
* List of payments is now limited to displaying 2 months of data for the merchant.
* For invoices with an Invoice Contact there are now additional details included about the Invoice Contact for both merchant and subscriber.
* Payment Agreement Management and Switching Added (preview).
* Recurring Deliveries integration for Distribution Innovation (preview).


Managing Payment Agreements (Preview)
-------------------------------------
This release includes a feature for managing payment agreements, both as a subscriber (self-service) and as the merchant (admin).
At the current point in time this feature only makes sense for organizations with a configured Payment Service Provider, but in the future it will be expanded to include additional payment agreement types.

From the self-service pages, it is now possible to add a new Credit Card agreement. 
Adding a new agreement will prompt the user to change his/her agreement on any running subscriptions.

It is also possible to have multiple agreements and switch between them at a later time.

From the merchant pages, it is possible to switch a subscribers agreement, it is however not possible to add new credit card agreements at this time.
We mayt look into a hand-of process, where the registration is started by the merchant and completed by the subscriber, at a later date - but it is currently not in the pipeline.

See the user documentation for more details.

*Contact our support for inclusion in the preview*

Recurring Deliveries - Distribution Innovation (Preview)
--------------------------------------------------------
This release also feature the preview of an integration with Distribution Innovation.
It is already possible to configure (map) products for recurring delivery.
All subscriptions with products thus configured will have a recurring delivery generated when a subscription is created or renewed.

Further mapping of products into Distribution Innovation terms will generate records to be sent to Distribution Innovation for actual physical distribution.
Unfortunately there is no API for doing live/online integrations on the fly, so files will still need to be exported and shipped to DI.

*Contact our support for further details and possible inclusion in the preview*