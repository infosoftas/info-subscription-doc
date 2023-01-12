.. _changelog-r109:

***************************
Release January 17th 2023
***************************

Aaaand we are at it again. A new year a new release. 
This release contains a slew of adjustments on bug fixes on features still in private-preview (early beta), so they are not called out in the release notes. But most of them are related to handling of deliveries and temporary adjustments to deliveries.

API and Backend
===============
The following new fixes, features and improvements are now available in the API and the backend.

* Added a new Payment Method Email (refer to separate section for more details).
* Added primary contact indicator when getting subscriber contacts (the primary contact is the one implictly returned when getting a subscriber).
* Added new endpoint to lookup an address in Distribution Innovation based on the Delivery Point Id.
* Fixed an issue with serialization for the recently introduced Settlement Policy configuration causing missing values for some response types.
* SourceId is now included in the Subscriber Contact to determine what is the source of the subscribers information (the value here is currently the Delivery Point Id from Distribution Innovation).
* It is now possible to add a cancellation type when cancelling a subscription to indicate why the cancellation is done. 
    
    * The idea is to differentiate between changes in the subscription and actual cancellation.
    * The cancellation type is available in the reporting subsystem (meaning churn reports can exclude certain types of cancellations).

* Changed the behaviour of automatic agreement switching for AvtaleGiro to consider subscriptions with a length down to 7 days. Previously it would only switch for subscriptions of 30 days or more, due to deadline rules defined by AvtaleGiro. The rules are now different when bank notification is disabled and thus 7 days can be allowed as the minimum subscription length.
* Billing Accounts now require OrganizationId and Currency to be defined upon creation. Automatically created accounts will be generated based on the Order that generates them.
* Added a new Description field for Account Payment Demands. Currently optional but will be changed to required in the future.
* Improved the stability of the EHF Peppol validation to reduce the number of false negatives due to Peppol being slow or down.
* Fixed an issue where EHF would be generated wrong if there were multiple transactions on the same non-zero tax group.
* Added rounding information to EHF invoice header information (hotfixed).
* Introduced validation to prevent configuration for ExternalInvoiceIdentifiers using some with prefix and some without. Mixing the two types on the same account WILL cause invalid overlaps.
* Fixed an issue where orders on Swedbank Pay and Vipps would not consider invoice fees and produce an invalid initial transaction (without the fee).
* Fixed an issue during value conversion that caused Vipps transactions to ignore decimal amounts (i.e 102,02 NOK would be charged as 102).
* Fixed an issue where orders with Initial Term with a fixed end date crossing DST would calculate an invalid end time (off by 1 hour).

Email as Payment Method/Type
-----------------------------
This release includes a new Payment Method: Email.
This does not do anything on its own, the integration type is still `InvoiceOnly`, so nothing special is done by INFO-Subscription, but the type is useful for separating fees and flows between printed/mailed invoices and Email distributed invoices.

New Payment Agreements can be created with this type, either directly through the Payment Agreement endpoint, alternatively during order creation with a set of parameters.

A future release will provide UI in self-service and merchant for switching to/from an Email agreement as well as sales support for email invoicing.

Merchant Client
===============
The following new features and improvements are now available in the merchant client.

* Improved view for Charges and ALlowances on invoices.
* Adjustments to the view for registering ledger/billing corrections, hopefully clarifying the consequences of the various actions.
* Fixed an issue that would cause duplicates when creating and updating Dunning Process and Billing Plan.
* Fixed an issue where shared users could not be added if a future cancellation time was registered on the current subscription.
* Fixed an issue with registering new refunds.

Self-Service and Salesposter
============================
The following new features and improvements are now available in the self-service client

* Fixed an issue where resetting password would not pass due to wrong client side validations.