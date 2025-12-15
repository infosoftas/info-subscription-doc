.. _provider-peppol:

PEPPOL BIS Billing (EHF/OIO)
=============================

PEPPOL (Pan-European Public Procurement OnLine) BIS Billing is an international standard for electronic invoicing that enables automatic end-to-end distribution of invoices and credit notes through the PEPPOL Network.

Similar to how |projectName| automatically delivers Norwegian eFaktura eInvoices to consumers, the platform has an integration that allows automatic distribution of invoices and credit notes through the PEPPOL Network to businesses and organizations.

Supported Countries
-------------------

|projectName| currently supports PEPPOL invoicing for the following countries:

* **Norway** - Uses EHF (Elektronisk Handelsformat) format
* **Denmark** - Uses OIO (Offentlig Information Online) format
* **Sweden** - Uses OIO format

.. Note::

    Although OIO is a Danish name, the same format is used for both Denmark and Sweden within the PEPPOL network.

Payment Provider Types
----------------------

The Payment Provider type varies by country:

EHF (Norway)
~~~~~~~~~~~~

* **Provider Type**: EHF
* **Required Identifier**: Norwegian Organization Number (9 digits)
* **Use Case**: Business-to-business and business-to-government invoicing in Norway

OIO (Denmark)
~~~~~~~~~~~~~

* **Provider Type**: OIO
* **Required Identifier**: CVR (Central Business Register number, 8 digits) or GLN (Global Location Number, 13 digits)
* **Use Case**: Business-to-business and business-to-government invoicing in Denmark

.. Note::

    For Danish organizations, CVR is the most commonly used identifier. GLN is typically used for larger organizations with multiple locations or specific supply chain requirements.

.. Note::

    GLN was previously communicated as EAN (European Article Number), so many people know OIO invoicing as "EAN invoicing". Both terms refer to the same identifier system.

OIO (Sweden)
~~~~~~~~~~~~

* **Provider Type**: OIO
* **Required Identifier**: GLN (Global Location Number)
* **Use Case**: Business-to-business and business-to-government invoicing in Sweden

Registration Process
--------------------

Unlike eFaktura, AvtaleGiro, or similar consumer-facing payment methods, there is **no automatic mandate registration or scanning** for PEPPOL invoicing. The subscriber or merchant needs to manually register the PEPPOL endpoint information.

The registration process follows these steps:

1. Verify that the recipient is registered in the PEPPOL network (using the lookup endpoint).
2. Create a provider agreement with the appropriate identifiers.
3. Create a payment agreement pointing to the provider agreement.
4. Register the payment agreement for the subscription.

PEPPOL Network Lookup
~~~~~~~~~~~~~~~~~~~~~~

Before creating a PEPPOL agreement, you can verify that the recipient exists in the PEPPOL network using the lookup endpoint:

**Endpoint**: :api-ref:`Invoice Document Network Lookup <Invoice/InvoiceDocumentNetworkLookup>`

.. Important::

    To use the lookup endpoint, you must know the **Document Network** (i.e., the target country) of the subscriber. It is the recipient's country that matters, **not** the selling organization's or merchant's country.

Example lookup request:

.. code-block:: json

    {
        "documentNetwork": "EHF",
        "recipientIdentifier": "999999999"
    }

Registration Workflow
~~~~~~~~~~~~~~~~~~~~~

The following sequence diagram illustrates the typical PEPPOL agreement registration process:

.. mermaid::

   %%{init: { 'sequence': { 'mirrorActors': false } } }%%
   sequenceDiagram
      actor Merchant
      participant API as INFO-Subscription API
      participant PEPPOL as PEPPOL Network

      Merchant->>API: Lookup recipient in PEPPOL network<br/>(POST /invoice/documentnetworklookup)
      API->>PEPPOL: Query recipient registration
      PEPPOL-->>API: Recipient found/not found
      API-->>Merchant: Lookup result

      alt Recipient is registered in PEPPOL
          Merchant->>API: Create subscriber<br/>(if not exists)
          API-->>Merchant: Subscriber ID
          
          Merchant->>API: Create provider agreement<br/>(POST /paymentagreement)
          Note right of API: Include:<br/>- ProviderType: EHF or OIO<br/>- Identifier (Org.nr, CVR, GLN)
          API-->>Merchant: Provider Agreement ID
          
          Merchant->>API: Register payment agreement<br/>for subscription<br/>(POST /subscription/{id}/changePaymentAgreement)
          API-->>Merchant: Payment agreement registered
          
          Note right of API: Future invoices will be<br/>sent via PEPPOL network
      else Recipient not in PEPPOL
          Merchant->>Merchant: Use alternative payment method
      end

Creating a PEPPOL Agreement
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

To create a PEPPOL payment agreement, you need to:

1. **Determine the appropriate provider type** based on the recipient's country:
   
   * Norway → ``EHF``
   * Denmark → ``OIO``
   * Sweden → ``OIO``

2. **Gather the required identifier**:
   
   * For EHF (Norway): Norwegian Organization Number
   * For OIO (Denmark): CVR or GLN
   * For OIO (Sweden): GLN

3. **Create the payment agreement** using the :api-ref:`Payment Agreement endpoint <PaymentAgreement>`:

Example request for EHF (Norway):

.. code-block:: json

    {
        "subscriberId": "3fa85f64-5717-4562-b3fc-2c963f66afa6",
        "providerType": "EHF",
        "providerAgreementReference": "999999999",
        "paymentMethod": "eInvoice"
    }

Example request for OIO (Denmark with CVR):

.. code-block:: json

    {
        "subscriberId": "3fa85f64-5717-4562-b3fc-2c963f66afa6",
        "providerType": "OIO",
        "providerAgreementReference": "10150817",
        "paymentMethod": "eInvoice"
    }

Example request for OIO (Sweden with GLN):

.. code-block:: json

    {
        "subscriberId": "3fa85f64-5717-4562-b3fc-2c963f66afa6",
        "providerType": "OIO",
        "providerAgreementReference": "7312345678901",
        "paymentMethod": "eInvoice"
    }

4. **Assign the agreement to the subscription** using :api-ref:`the change payment agreement endpoint <Subscription/post_Subscription__id__changePaymentAgreement>`.

Invoice and Credit Note Distribution
-------------------------------------

Once a PEPPOL agreement is registered and active:

* **Invoices** generated for the subscription will automatically be sent through the PEPPOL network to the recipient's endpoint.
* **Credit Notes** will also be distributed through the PEPPOL network.
* The recipient will receive the documents in their accounting system or PEPPOL access point.

The distribution is fully automated once the agreement is in place.

Differences from Consumer eInvoicing
-------------------------------------

PEPPOL invoicing differs from consumer-focused solutions like eFaktura in several key ways:

==================== =============================== ===================================
Feature              Consumer eInvoicing (eFaktura)  PEPPOL (EHF/OIO)
==================== =============================== ===================================
Target Audience      Consumers (B2C)                 Businesses/Organizations (B2B/B2G)
Registration         Automatic scanning available    Manual registration required
Mandate Discovery    System can scan for mandates    Lookup endpoint must be used
Network Type         National (Norway)               International (PEPPOL)
Payment Type         Direct from consumer            Invoice-based (no direct payment)
==================== =============================== ===================================

Troubleshooting
---------------

Recipient Not Found
~~~~~~~~~~~~~~~~~~~

If the lookup endpoint returns that a recipient is not found in the PEPPOL network:

* Verify the identifier format is correct for the country.
* Confirm the recipient has registered with a PEPPOL access point.
* Check that you're using the correct Document Network for the recipient's country.
* Consider using an alternative payment method.

Agreement Creation Fails
~~~~~~~~~~~~~~~~~~~~~~~~~

If creating a PEPPOL agreement fails:

* Ensure the subscriber exists in |projectName|.
* Verify the provider type matches the recipient's country.
* Confirm the identifier is valid and correctly formatted.
* Check that the subscriber doesn't already have an active PEPPOL agreement.

Invoices Not Being Delivered
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If invoices are not being delivered through PEPPOL:

* Verify the payment agreement is active and assigned to the subscription.
* Confirm the recipient's PEPPOL endpoint is still active.
* Check for any error events or notifications in |projectName|.
* Re-run the network lookup to ensure the recipient is still registered.

See Also
--------

* :ref:`payment-agreements` - General information about payment agreements
* :ref:`provider-efaktura` - Norwegian consumer eInvoicing
* :api-ref:`Invoice API <Invoice>` - Invoice management endpoints
* :api-ref:`Payment Agreement API <PaymentAgreement>` - Payment agreement endpoints
