.. _on-demand-reminder:

*************************************
Creating Reminders On Demand
*************************************

The standard dunning flow in |projectName| issues reminders automatically according to a configured schedule. There are scenarios where that schedule-driven flow is not appropriate — most commonly when an external party, such as a debt collection agency, is running the collections process. This page describes how to create a reminder directly via the API, bypassing the dunning schedule.

When to Use This
================

Use the on-demand reminder endpoint when:

- An external party controls the reminder and collections timeline, and you need the corresponding ledger entries and invoice document to appear in |projectName|.
- You require precise control over reminder timing, fee amounts, and sequence numbering rather than relying on a preconfigured dunning schedule.
- The dunning schedule is not configured, or its timing does not align with an externally driven collections process.

How It Differs from Scheduled Reminders
========================================

The :ref:`Repeated Reminder Flow <Repeated_Reminder_Flow>` section of the billing overview describes how reminders are normally generated: a dunning process configuration drives a scheduler that creates reminders at defined intervals relative to the original invoice due date.

The on-demand endpoint produces the same end result — a reminder invoice document is generated in the document service and ledger entries are created — but the trigger is a direct API call rather than the scheduler. The dunning process configuration on the billing plan is not consulted for timing or fee values; the caller supplies those values in the request body.

Step-by-Step Example: External Debt Collector
==============================================

A subscriber has an overdue invoice. The organisation has handed the debt to an external collection agency. The agency has its own fee schedule and issues reminders on its own timeline. The organisation needs each reminder to appear in |projectName| with the correct fee and due date.

**Step 1: Find the payment demand id**

Query the payment demand endpoint for the subscriber's open demands:

.. code-block:: http
    :name: Find Payment Demand

    GET https://api.info-subscription.com/paymentdemand?subscriberId=0c8f576a-6308-4598-a255-52080fbf5f71 HTTP/1.1
    Host: api.info-subscription.com
    S4-TenantId: 3fce3f93-97a7-4045-952d-f8af685a47cb
    Authorization: Bearer <TOKENHERE>

Locate the overdue demand in the response and note its ``id``.

**Step 2: Create the reminder**

POST to the reminder sub-resource of the payment demand, providing the fee and due date that the collector has determined:

.. code-block:: http
    :name: Create On-Demand Reminder

    POST https://api.info-subscription.com/paymentdemand/3fa85f64-5717-4562-b3fc-2c963f66afa6/reminder HTTP/1.1
    Host: api.info-subscription.com
    S4-TenantId: 3fce3f93-97a7-4045-952d-f8af685a47cb
    Authorization: Bearer <TOKENHERE>
    Content-Type: application/json

    {
        "dueDate": "2025-03-15T00:00:00Z",
        "fee": 35.00,
        "counter": 1,
        "reminderPolicy": {
            "disableAccountPaymentConsumption": true
        }
    }

A ``202 Accepted`` response indicates the reminder has been accepted for asynchronous processing.

``reminderPolicy`` — Controlling Payment Consumption
=====================================================

By default, |projectName| reduces the reminder amount by any partial payments the subscriber has already made against the original invoice. This is the appropriate behaviour for most scenarios: the subscriber should not be asked to pay an amount they have already partially covered.

In external-collector scenarios this default may not be correct. The collector may have already accounted for partial payments in its own system and is supplying the exact amount to charge. To generate the reminder for the supplied amount without deducting prior partial payments, set ``reminderPolicy.disableAccountPaymentConsumption`` to ``true``.

.. note::

    When ``disableAccountPaymentConsumption`` is ``true``, the full ``fee`` value (plus the outstanding principal on the demand) is used as the reminder amount regardless of any payments recorded in |projectName|. Only use this setting when the caller has independently accounted for partial payments.

When ``reminderPolicy`` is omitted entirely, the default behaviour (deduct partial payments) applies.

``counter`` — Reminder Sequence Number
=======================================

The ``counter`` field identifies the position of this reminder in the series for the payment demand. The first reminder has counter ``1``, the second ``2``, and so on.

When ``counter`` is omitted, |projectName| looks up the existing reminders for the demand and assigns the next available sequence number automatically. This is convenient but involves an extra lookup and can produce incorrect ordering if two reminders are created concurrently for the same demand.

.. tip::

    Supply ``counter`` explicitly whenever you know the intended position in the sequence. This avoids the extra lookup and ensures correct ordering even under concurrent requests.

Events
======

A successfully processed on-demand reminder emits the same events as a schedule-driven reminder. Listen for the :ref:`ReminderIssued <reminder-issued-event>` event to react to the reminder in downstream systems (for example, to trigger notifications or update an external ledger).
