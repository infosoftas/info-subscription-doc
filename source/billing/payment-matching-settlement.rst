.. _payment-matching-settlement:

****************************************************************
Payment Matching, Settlement, and Billing Account Reconciliation
****************************************************************

When a payment is received, |projectName| handles more than just registering the incoming amount. The platform first identifies which subscriber and invoice the payment belongs to, then decides whether the payment settles an outstanding demand, and finally updates the subscriber's billing account with any remaining credit or debt.

For most integrations, this flow is fully automated and event-driven:

1. The payment service identifies the payment and auto-completes it
2. ``PaymentCompleted`` is emitted
3. The billing service matches the payment to an unsettled demand
4. The demand is settled if the settlement policy is met
5. The settled demand records the result in ``settlementTransactions``
6. ``InvoicePaid`` is emitted if the invoice becomes paid

.. important::

    For ERP, accounting, and bank-reconciliation integrations, the primary billing-side hook is the settled demand's ``settlementTransactions`` payload. It records which payments, billing account allowances, and residual charges were involved in settlement.

Payment Identification Before Billing Settlement
================================================

Before the billing service can settle anything, the payment service must identify the payment. In practice, the effective payment lifecycle is:

.. mermaid::

    flowchart LR
        A[AwaitingIdentification] --> B[Completed]
        B --> C[PaymentCompleted event]
        C --> D[Billing service: demand matching and settlement]

Automatic approval is always enabled in practice, so ``AwaitingApproval`` is not relevant for normal integrations. If identification fails, the payment remains in ``AwaitingIdentification`` until it is corrected through the API.

Payments in this state:

* do not emit ``PaymentCompleted``
* do not emit :ref:`InvoicePaid <invoice-paid-event>`
* do not trigger billing settlement

Matching Types
--------------

When a payment is registered, the caller chooses a matching type that tells the payment service how to identify the subscriber and invoice.

.. list-table::
   :header-rows: 1
   :widths: 28 42 30

   * - Matching type
     - How it works
     - Requires
   * - ``UseSubscriberAndInvoice``
     - Matches directly by internal ``subscriberId`` and ``invoiceId``
     - Both ids
   * - ``UseExternalIdentifier``
     - Resolves the invoice through ``externalInvoiceIdentifier`` such as the invoice number shown to the payer
     - ``externalInvoiceIdentifier``
   * - ``UseSubscriberFromExternalIdentifier``
     - Resolves only the subscriber from ``externalInvoiceIdentifier``. The payment is not matched to the invoice automatically.
     - ``externalInvoiceIdentifier``
   * - ``NoInvoiceMatch``
     - Attaches the payment to a subscriber or billing account only. No invoice match is attempted during identification. This matching type is on a deprecation path.
     - ``subscriberId``
   * - ``UseBillingAccount``
     - Identifies the payment through a specific billing account and uses the most recent issued invoice on that account
     - ``subscriberAccountId``

Integrated payment providers and billing-driven payment creation typically use ``UseSubscriberAndInvoice``. Bank reconciliation and OCR import scenarios more often use ``UseExternalIdentifier`` or ``UseBillingAccount``.

Matching Policy
---------------

Matching Policy controls which invoice states are eligible for automatic completion after identification. It is configured per organization in the payment service.

By default, only invoices in ``Issued`` state can be auto-completed. This covers the normal path where an issued invoice is paid and then settled by billing.

Some organizations need to complete payments against other invoice states as well, for example late bank payments that arrive after an invoice has already been credited. For that purpose, a Matching Policy exposes ``AllowedInvoiceStatesForAutoCompletion`` as a flags value of ``InvoiceState``.

.. mermaid::

    flowchart TD
        A[Payment registered] --> B[Look up invoice]
        B --> C{Invoice state allowed by Matching Policy?}
        C -->|Yes| D[Identification succeeds]
        D --> E[Completed]
        E --> F[PaymentCompleted]
        C -->|No| G[Stay in AwaitingIdentification]

Matching Policy applies when a registration flow identifies a concrete invoice, such as ``UseSubscriberAndInvoice`` or ``UseExternalIdentifier``. It does not apply to ``NoInvoiceMatch`` and ``UseBillingAccount`` flows.

Matching policies are managed through the Payment API:

* ``POST /matchingpolicy`` creates a policy
* ``PUT /matchingpolicy/{id}`` updates a policy
* ``POST /matchingpolicy/{id}/organizations/{organizationId}`` assigns a policy to an organization

Payment Matching in Billing
===========================

Once ``PaymentCompleted`` arrives in the billing service, the system attempts to match the payment to an outstanding demand. The primary matching identifiers are ``invoiceId`` and ``subscriberId``.

A demand is eligible only when:

* there is no settle date (``settleDate == null``)
* the demand is not credited (``isCredited == false``)

.. mermaid::

    flowchart TD
        A[PaymentCompleted] --> B{InvoiceId + SubscriberId match to unsettled, non-credited demand?}
        B -->|Yes| C[Go to settlement]
        B -->|No| D{Exactly one outstanding demand with matching amount and billing account?}
        D -->|Yes| C
        D -->|No| E[Store payment as allowance on billing account]

Fallback Matching
-----------------

If direct ``invoiceId`` matching fails, billing applies a fallback rule:

* The subscriber must have exactly one outstanding demand
* The payment amount must equal that demand amount
* The billing account must match when a billing account is present

When those conditions are met, the payment is matched and can proceed to settlement even without an explicit invoice reference.

Unmatched Payments
------------------

If billing cannot match the completed payment to any demand, the amount is stored as an allowance on the subscriber's billing account. That allowance can then reduce a future invoice automatically.

Settlement
==========

After a demand is matched, billing evaluates whether the payment settles the demand according to the active settlement policy configured through the billing plan's dunning process.

Settlement Policies
-------------------

Two settlement policy types exist:

.. list-table::
   :header-rows: 1
   :widths: 35 65

   * - Policy
     - Description
   * - Percent of demand
     - The payment must cover at least a configured percentage of the outstanding demand amount. The default is 100 percent.
   * - Fixed amount tolerance
     - The payment may settle the demand when the remaining difference is within a configured fixed amount, for example 5 NOK.

If the payment alone does not meet the threshold, billing checks the subscriber's current billing account balance next.

Settlement then follows one of these paths:

* If the payment alone meets the policy, the demand settles from the payment
* If payment plus available allowances meets the policy, the demand settles using both the payment and the consumed allowance balance
* If neither threshold is met, the demand remains open

.. mermaid::

    flowchart TD
        A[Demand matched] --> B[Credit reminder fees if configured]
        B --> C{Payment alone meets policy?}
        C -->|Yes| D[Settle using payment]
        C -->|No| E{Payment + allowances meets policy?}
        E -->|Yes| F[Settle using payment and allowances]
        E -->|No| G[No settlement; demand stays open]
        D --> H[Create settlementTransactions]
        F --> H

Settlement Outcomes
-------------------

.. list-table::
   :header-rows: 1
   :widths: 35 65

   * - Scenario
     - What happens
   * - Payment equals demand
     - Demand is settled with no residual account movement
   * - Payment settles the demand on its own
     - Demand is settled from the payment. Any excess becomes an allowance on the billing account.
   * - Payment plus billing account allowance settles the demand
     - Demand is settled, and the used allowances are recorded in ``settlementTransactions.consumedAllowances``
   * - Payment stays below the settlement threshold
     - No settlement occurs and the demand remains open
   * - Demand is settled even though payment is below the full amount
     - The unpaid remainder becomes a charge on the billing account and is recorded in ``settlementTransactions.generatedCharges``

Reminder Fees and Auto-Crediting
--------------------------------

If a demand includes reminder fees and the payment covers the original demand amount plus only part of the reminder fees, the remaining reminder fees can be credited automatically. This behavior is configurable per billing plan.

Settlement Transactions
-----------------------

Every settled demand carries a ``settlementTransactions`` object describing how settlement happened:

* ``payments`` lists the payment or payments used
* ``consumedAllowances`` lists billing account credits applied during settlement
* ``generatedCharges`` lists any residual debt moved to the billing account

This is the primary record for external accounting, ERP reconciliation, and custom billing dashboards.

.. important::

    If you need a definitive settlement audit trail, use ``settlementTransactions`` rather than inferring settlement from invoice totals alone.

.. _billing-account-role:

Billing Account Role
====================

The billing account is the running ledger for a subscriber within an organization and currency. It stores the financial carry-over that links one invoice period to the next.

* **Allowances** are credits added when payments exceed what was owed, when demands are credited or refunded, or when an unmatched payment is received
* **Charges** are debts added when a settled demand still has a residual unpaid amount, or when usage-based or other account transactions are posted

The balance is effectively:

.. code-block:: text

    sum(allowances) - sum(charges)

When a new account demand is created with ``SettleAccountBalance: true``, outstanding account transactions can be included in the new demand total. This is how the hybrid model described in :ref:`Billing Overview <billing-cycle>` works in practice.

Enterprise Plan Behavior
========================

.. warning::

    Enterprise Plan settlement behaves differently from standard subscription billing and should be treated as a separate integration model.

An Enterprise Plan groups multiple subscriptions into one billing arrangement for an organization. Settlement is handled for the plan invoice as a whole rather than through per-subscription billing account carry-over.

.. list-table::
   :header-rows: 1
   :widths: 30 35 35

   * - Aspect
     - Standard subscriptions
     - Enterprise Plan
   * - Demand scope
     - Per subscription
     - All subscriptions in the plan for the billing period
   * - Billing account charges and allowances
     - Yes. Partial payments can create charges and overpayments can create allowances.
     - No carry-over billing account behavior
   * - Proration
     - Yes. Changes and cancellations can generate prorated charges or allowances.
     - No proration. The plan fee is fixed for the period.
   * - Reminder auto-crediting
     - Supported
     - Not applicable
   * - Settlement policy
     - Configurable per billing plan
     - Requires full payment of the invoice amount

For Enterprise Plan customers, the invoice is settled atomically: either the full invoice amount is paid, or it is not. Integrations should not expect billing account allowances or charges to top up or carry forward Enterprise Plan settlement.

Related Documentation
=====================

* :ref:`Billing Overview <billing-cycle>`
* :ref:`Transaction (Non-Recurring) Invoices <standalone-paymentdemands>`
* :ref:`Proration Policies for Cancellations <proration-policies>`
* :ref:`InvoicePaid <invoice-paid-event>`
