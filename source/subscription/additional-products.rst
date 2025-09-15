.. _additional-products:

*********************************
Addons or Additional Products
*********************************

In |projectName|, **additional products** (also called "addons") are items or services that are attached to a subscription and follow its lifetime. 

This section explains the concept, rules, and best practices for working with additional products as a developer.

What Are Additional Products?
-----------------------------

Additional products are optional items or services that can be:

- Included as part of the subscription plan (automatically provisioned when the subscription is created)
- Purchased by the subscriber during the initial order
- Purchased at any time during the lifetime of the subscription (subject to business rules)

They are always associated with a specific subscription and exist only for the duration of that subscription. 

Examples use cases include:

- Extra storage or bandwidth
- Premium support
- Device insurance
- IoT sensor devices
- Family Access


.. note::

	Throughout this documentation, the term **additional products** is used as the primary term, but it is synonymous with **addons**. 
	Both refer to the same concept and may be used interchangeably in the documentation. 


Key Rules and Behaviors
-----------------------

- **Lifecycle:** Additional products are bound to the subscription's lifetime. When the subscription is cancelled, all associated additional products are also terminated.
- **No Proration or Mid-Period Cancellation:** Once purchased, additional products cannot be cancelled or refunded during the active subscription period. They remain active until the subscription ends or is cancelled.
- **Pricing:** Additional products do not follow the price rules or discounts defined on subscription plans. Their prices are set independently and are not affected by plan-level promotions or changes.
- **Purchase Timing:** Additional products can typically be added at the time of subscription purchase or during the subscription's lifetime (subject to business rules).

API Usage
---------
The API provides endpoints for managing additional products. See the  `API reference <https://api.info-subscription.com/swagger/>`_ for details.

Typical API operations include:

- Listing available additional products for a subscription plan or a specific subscription instance.
- Adding an additional product to a subscription.
- Retrieving additional products associated with a subscription.


Upgrades and Downgrades with Additional Products
------------------------------------------------

When a subscription is upgraded or downgraded to a different plan, the handling of additional products depends on what is included in the new plan and what the subscriber has already purchased:

- **Upgrade to a Plan with Included Addons:**
	- If the new plan includes additional products that the subscriber has already purchased, the included amount replaces the purchased amount. For example, if a subscriber purchased one IoT sensor device as an addon and upgrades to a plan that includes one device, the included device takes precedence and the purchased addon is removed.
	- If the subscriber needs more than what is included in the new plan, they must purchase the extra quantity as additional products.
	- Purchases do not stack with included products; only the higher of the included or purchased quantity is retained.

- **Downgrade to a Plan with Fewer or No Included Addons:**
	- If the new plan includes fewer or no additional products, only the difference (if any) between what was previously included and what is now included will remain as a separate purchase.
	- For example, if a subscriber had a plan with two Family Access licenses included and downgrades to a plan with one included, the subscriber will retain one included license. If they need more, they must purchase the additional licenses as addons.
	- If the new plan includes none, the subscriber may need to purchase all additional products again if they wish to keep them.

This logic ensures that subscribers always receive the correct entitlements based on their current plan, and that additional product purchases are not duplicated or stacked with included quantities.

Developer Suggestions
---------------------
- Clearly communicate to users that additional products cannot be cancelled or refunded mid-period.
- When displaying subscription details, show all active additional products and their terms.
- Use the API to validate which additional products are available for a given plan or subscription.