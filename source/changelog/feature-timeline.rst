.. _feature-timeline:

################
Feature timeline
################

.. raw:: html

   <style>
   .feature-history-summary { display: grid; grid-template-columns: repeat(4, minmax(0, 1fr)); gap: .6rem; max-width: 960px; margin: 1.5rem auto 2.5rem; }
   .feature-history-summary a { padding: .7rem; text-align: center; background: #f1f5f9; border-radius: .45rem; color: #183b56; }
   .feature-history-summary strong { display: grid; grid-template-columns: minmax(0, 1fr) auto minmax(0, 1fr); align-items: baseline; font-size: 1.25rem; }
   .feature-history-summary strong span { grid-column: 2; }
   .feature-history-summary small { grid-column: 3; margin-left: .3rem; text-align: left; font-size: .75rem; font-weight: 400; color: #526575; }
   .feature-history { --history-line: #87a9c3; max-width: 960px; margin: 0 auto 3rem; position: relative; }
   .feature-history::before { content: ""; position: absolute; top: 1.2rem; bottom: 1.2rem; left: 50%; width: 3px; transform: translateX(-50%); background: var(--history-line); }
   .feature-history-year { position: relative; z-index: 1; display: flex; justify-content: center; margin: 2.3rem 0 1rem; }
   .feature-history-year span { padding: .45rem 1.2rem; color: #fff; background: #1f4e79; border-radius: 2rem; font-size: 1.2rem; font-weight: 700; }
   .feature-history-items { list-style: none; margin: 0; padding: 0; }
   .feature-history-item { display: grid; grid-template-columns: minmax(0, 1fr) 2.5rem minmax(0, 1fr); align-items: center; margin: .65rem 0; position: relative; }
   .feature-history-card { display: block; grid-row: 1; padding: .75rem 1rem; background: #fff; border: 1px solid #d4e0e8; border-radius: .55rem; box-shadow: 0 2px 8px rgba(24,59,86,.08); }
   .feature-history-card strong { color: #183b56; }
   .feature-history-summary a:hover, .feature-history-card:hover { background: #eaf2f8; }
   .feature-history-summary a:focus-visible, .feature-history-card:focus-visible { outline: 3px solid #1f4e79; outline-offset: 3px; }
   .feature-history-year, [id^="feature-entry-"] { scroll-margin-top: 4rem; }
   .feature-history-left .feature-history-card { grid-column: 1; text-align: right; margin-right: .8rem; }
   .feature-history-right .feature-history-card { grid-column: 3; margin-left: .8rem; }
   @media (max-width: 640px) {
     .feature-history-summary { grid-template-columns: repeat(2, minmax(0, 1fr)); }
     .feature-history::before { left: 1rem; }
     .feature-history-year { justify-content: flex-start; margin-left: 2.4rem; }
     .feature-history-item { grid-template-columns: 2rem minmax(0, 1fr); }
     .feature-history-left .feature-history-card, .feature-history-right .feature-history-card { grid-column: 2; text-align: left; margin: 0 0 0 .6rem; }
   }
   </style>

   <div class="feature-history-summary" aria-label="Significant features by year">
   
   <a href="#timeline-year-2026" aria-label="2026: 10 new features"><strong><span>+10</span> <small>features</small></strong>2026</a>
   <a href="#timeline-year-2025" aria-label="2025: 6 new features"><strong><span>+6</span> <small>features</small></strong>2025</a>
   <a href="#timeline-year-2024" aria-label="2024: 15 new features"><strong><span>+15</span> <small>features</small></strong>2024</a>
   <a href="#timeline-year-2023" aria-label="2023: 6 new features"><strong><span>+6</span> <small>features</small></strong>2023</a>
   <a href="#timeline-year-2022" aria-label="2022: 8 new features"><strong><span>+8</span> <small>features</small></strong>2022</a>
   <a href="#timeline-year-2021" aria-label="2021: 6 new features"><strong><span>+6</span> <small>features</small></strong>2021</a>
   <a href="#timeline-year-2020" aria-label="2020: 15 new features"><strong><span>+15</span> <small>features</small></strong>2020</a>
   <a href="#timeline-year-2019" aria-label="2019: 16 new features"><strong><span>+16</span> <small>features</small></strong>2019</a>
   </div>
   <div class="feature-history" aria-label="Significant INFO-Subscription features by year">
   
   <div class="feature-history-year" id="timeline-year-2026"><span>2026</span></div>
   <ol class="feature-history-items">
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2026-retention-offers"><strong>Retention offers</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2026-tailor-made-subscription-plans"><strong>Tailor-made subscription plans</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2026-external-dunning"><strong>External dunning</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2026-mcp-server"><strong>MCP server</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2026-automated-gdpr-data-retention"><strong>Automated GDPR data retention</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2026-trial-subscription-checkout"><strong>Trial subscription checkout</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2026-scheduled-cancellations"><strong>Scheduled cancellations</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2026-smartresponse-tracking"><strong>SmartResponse tracking</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2026-mollie-payments"><strong>Mollie payments</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2026-bad-debt-write-off"><strong>Bad debt write-off</strong></a></li>
   </ol>
   <div class="feature-history-year" id="timeline-year-2025"><span>2025</span></div>
   <ol class="feature-history-items">
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2025-hosted-checkout"><strong>Hosted Checkout</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2025-odata-analytics-api"><strong>OData analytics API</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2025-simplified-order-api-and-sdk"><strong>Simplified Order API and SDK</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2025-add-ons-on-running-subscriptions"><strong>Add-ons on running subscriptions</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2025-billing-transaction-log"><strong>Billing transaction log</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2025-refunds-through-payment-providers"><strong>Refunds through payment providers</strong></a></li>
   </ol>
   <div class="feature-history-year" id="timeline-year-2024"><span>2024</span></div>
   <ol class="feature-history-items">
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2024-betalingsservice-direct-debit"><strong>BetalingsService direct debit</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2024-edition-based-billing"><strong>Edition-based billing</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2024-mobilepay-in-denmark-and-finland"><strong>MobilePay in Denmark and Finland</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2024-oio-e-invoicing"><strong>OIO e-invoicing</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2024-automated-e-invoice-delivery"><strong>Automated e-invoice delivery</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2024-automatic-card-updates"><strong>Automatic card updates</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2024-prepaid-account-balance"><strong>Prepaid account balance</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2024-transactional-invoicing"><strong>Transactional invoicing</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2024-subscriber-audit-log"><strong>Subscriber audit log</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2024-one-off-vipps-mobilepay-payments"><strong>One-off Vipps MobilePay payments</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2024-one-off-card-payments"><strong>One-off card payments</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2024-profile-sharing-checkout"><strong>Profile-sharing checkout</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2024-repeat-offer-prevention"><strong>Repeat-offer prevention</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2024-revenue-and-user-kpis"><strong>Revenue and user KPIs</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2024-shared-subscriber-ownership"><strong>Shared subscriber ownership</strong></a></li>
   </ol>
   <div class="feature-history-year" id="timeline-year-2023"><span>2023</span></div>
   <ol class="feature-history-items">
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2023-detailed-churn-reporting"><strong>Detailed churn reporting</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2023-address-suggestions-while-typing"><strong>Address suggestions while typing</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2023-email-domain-based-access"><strong>Email-domain based access</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2023-automatic-settlement-of-reminders"><strong>Automatic settlement of reminders</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2023-bulk-enterprise-plan-registration"><strong>Bulk Enterprise Plan registration</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2023-balance-transfers-between-accounts"><strong>Balance transfers between accounts</strong></a></li>
   </ol>
   <div class="feature-history-year" id="timeline-year-2022"><span>2022</span></div>
   <ol class="feature-history-items">
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2022-permanent-discounts"><strong>Permanent discounts</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2022-automated-vipps-settlement"><strong>Automated Vipps settlement</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2022-saf-t-financial-export"><strong>SAF-T financial export</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2022-subscriber-access-service"><strong>Subscriber access service</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2022-gdpr-right-to-erasure"><strong>GDPR right to erasure</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2022-refund-registration"><strong>Refund registration</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2022-peppol-directory-lookup"><strong>Peppol directory lookup</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2022-avtalegiro-via-mastercard-api"><strong>AvtaleGiro via Mastercard API</strong></a></li>
   </ol>
   <div class="feature-history-year" id="timeline-year-2021"><span>2021</span></div>
   <ol class="feature-history-items">
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2021-avtalegiro-direct-debit"><strong>AvtaleGiro direct debit</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2021-scheduled-plan-changes"><strong>Scheduled plan changes</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2021-swedish-bankgirot-invoices"><strong>Swedish Bankgirot invoices</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2021-undo-and-resume-cancellations"><strong>Undo and resume cancellations</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2021-autogiro-direct-debit"><strong>AutoGiro direct debit</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2021-kilkaya-conversion-tracking"><strong>Kilkaya conversion tracking</strong></a></li>
   </ol>
   <div class="feature-history-year" id="timeline-year-2020"><span>2020</span></div>
   <ol class="feature-history-items">
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2020-switch-payment-method"><strong>Switch payment method</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2020-distribution-innovation-integration"><strong>Distribution Innovation integration</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2020-reporting-tags"><strong>Reporting tags</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2020-multiple-organizations"><strong>Multiple organizations</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2020-swedbank-pay-card-payments"><strong>Swedbank Pay card payments</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2020-standard-subscription-reports"><strong>Standard subscription reports</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2020-automatic-payment-retries"><strong>Automatic payment retries</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2020-additional-products"><strong>Additional products</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2020-binding-contracts"><strong>Binding contracts</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2020-shared-digital-access"><strong>Shared digital access</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2020-scheduled-address-changes"><strong>Scheduled address changes</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2020-one-off-charges"><strong>One-off charges</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2020-build-your-own-bundles"><strong>Build-your-own bundles</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2020-vipps-recurring-payments"><strong>Vipps recurring payments</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2020-subscriber-event-webhooks"><strong>Subscriber event webhooks</strong></a></li>
   </ol>
   <div class="feature-history-year" id="timeline-year-2019"><span>2019</span></div>
   <ol class="feature-history-items">
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2019-tenant-reporting-database"><strong>Tenant reporting database</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2019-arvato-invoice-factoring"><strong>Arvato invoice factoring</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2019-crediting-and-credit-notes"><strong>Crediting and credit notes</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2019-ehf-e-invoicing"><strong>EHF e-invoicing</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2019-fixed-term-subscriptions"><strong>Fixed-term subscriptions</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2019-automatic-stop-for-non-payment"><strong>Automatic stop for non-payment</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2019-enterprise-plans"><strong>Enterprise plans</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2019-subscription-pausing"><strong>Subscription pausing</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2019-custom-deal-pricing"><strong>Custom deal pricing</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2019-auth0-subscriber-login"><strong>Auth0 subscriber login</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2019-recurring-deliveries"><strong>Recurring deliveries</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2019-automatic-credit-control"><strong>Automatic credit control</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2019-kartverket-address-matching"><strong>Kartverket address matching</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2019-product-mix-reporting"><strong>Product-mix reporting</strong></a></li>
   <li class="feature-history-item feature-history-left"><a class="feature-history-card" href="#feature-entry-2019-google-tag-manager"><strong>Google Tag Manager</strong></a></li>
   <li class="feature-history-item feature-history-right"><a class="feature-history-card" href="#feature-entry-2019-plan-changes-with-proration"><strong>Plan changes with proration</strong></a></li>
   </ol>
   </div>
.. _feature-timeline-2026:

2026
====

Coverage for 2026 is partial: this year is shown up to the release on September 16, 2026.

.. list-table:: Features in 2026
   :header-rows: 1
   :widths: 32 52 16

   * - Feature
     - What it enables
     - Release notes
   * - .. _feature-entry-2026-retention-offers:

       Retention offers
     - Checkout can suggest an alternative offer when an order is blocked, and Self-Service can offer a downgrade instead of a cancellation.
     - :ref:`r142 <changelog-r142>`
   * - .. _feature-entry-2026-tailor-made-subscription-plans:

       Tailor-made subscription plans
     - Individual plans can be defined directly for a subscriber, for example for enterprise customers, without creating a reusable template.
     - :ref:`r142 <changelog-r142>`, :ref:`r143 <changelog-r143>`
   * - .. _feature-entry-2026-external-dunning:

       External dunning
     - Reminders can be created on demand when dunning is handled by debt collectors or manually.
     - :ref:`r142 <changelog-r142>`
   * - .. _feature-entry-2026-mcp-server:

       MCP server
     - AI assistants can work with subscription, billing, order, subscriber and catalogue data through the Model Context Protocol.
     - :ref:`MCP Server <mcp-server>`
   * - .. _feature-entry-2026-automated-gdpr-data-retention:

       Automated GDPR data retention
     - Historic data is cleaned up automatically to comply with data retention rules such as GDPR.
     - :ref:`r143 <changelog-r143>`
   * - .. _feature-entry-2026-trial-subscription-checkout:

       Trial subscription checkout
     - Free and trial subscriptions can be sold through a dedicated checkout journey with automatic cancellation.
     - :ref:`r144 <changelog-r144>`
   * - .. _feature-entry-2026-scheduled-cancellations:

       Scheduled cancellations
     - Merchants and subscribers can schedule a cancellation for a chosen future date, including beyond the current period.
     - :ref:`r144 <changelog-r144>`, :ref:`r145 <changelog-r145>`
   * - .. _feature-entry-2026-smartresponse-tracking:

       SmartResponse tracking
     - Checkout activity can be tracked in SmartResponse.
     - :ref:`r144 <changelog-r144>`
   * - .. _feature-entry-2026-mollie-payments:

       Mollie payments
     - One-off and recurring card, Apple Pay and Google Pay payments through Mollie, reaching more countries and currencies.
     - :ref:`r145 <changelog-r145>`
   * - .. _feature-entry-2026-bad-debt-write-off:

       Bad debt write-off
     - Unpaid invoices can be written off as bad debt without issuing a credit note.
     - :ref:`r145 <changelog-r145>`

.. _feature-timeline-2025:

2025
====

.. list-table:: Features in 2025
   :header-rows: 1
   :widths: 32 52 16

   * - Feature
     - What it enables
     - Release notes
   * - .. _feature-entry-2025-hosted-checkout:

       Hosted Checkout
     - A ready-made checkout for selling subscriptions without building your own order flow.
     - :ref:`r131 <changelog-r131>`
   * - .. _feature-entry-2025-odata-analytics-api:

       OData analytics API
     - Reporting and analytics data can be queried directly over the API using OData.
     - :ref:`r131 <changelog-r131>`
   * - .. _feature-entry-2025-simplified-order-api-and-sdk:

       Simplified Order API and SDK
     - A simplified Order API with a published JavaScript/TypeScript SDK, making it faster to build custom order flows.
     - :ref:`r131 <changelog-r131>`
   * - .. _feature-entry-2025-add-ons-on-running-subscriptions:

       Add-ons on running subscriptions
     - Additional products can be added to new and running subscriptions, with billing and proration.
     - :ref:`r132 <changelog-r132>`, :ref:`r134 <changelog-r134>`
   * - .. _feature-entry-2025-billing-transaction-log:

       Billing transaction log
     - A complete log of billing transactions for auditing and reporting.
     - :ref:`r135 <changelog-r135>`, :ref:`r136 <changelog-r136>`
   * - .. _feature-entry-2025-refunds-through-payment-providers:

       Refunds through payment providers
     - Vipps MobilePay charges can be refunded and Swedbank Pay transactions reversed directly from INFO-Subscription.
     - :ref:`r137 <changelog-r137>`, :ref:`r141 <changelog-r141>`

.. _feature-timeline-2024:

2024
====

.. list-table:: Features in 2024
   :header-rows: 1
   :widths: 32 52 16

   * - Feature
     - What it enables
     - Release notes
   * - .. _feature-entry-2024-betalingsservice-direct-debit:

       BetalingsService direct debit
     - Recurring payments in Denmark through BetalingsService direct debit.
     - :ref:`r121 <changelog-r121>`, :ref:`r122 <changelog-r122>`
   * - .. _feature-entry-2024-edition-based-billing:

       Edition-based billing
     - Subscriptions can be priced, sold and billed by a number of editions in a release calendar instead of by time.
     - :ref:`r121 <changelog-r121>`, :ref:`r122 <changelog-r122>`, :ref:`r126 <changelog-r126>`
   * - .. _feature-entry-2024-mobilepay-in-denmark-and-finland:

       MobilePay in Denmark and Finland
     - Subscribers in Denmark and Finland can order and pay recurring subscriptions with MobilePay.
     - :ref:`r123 <changelog-r123>`, :ref:`r124 <changelog-r124>`
   * - .. _feature-entry-2024-oio-e-invoicing:

       OIO e-invoicing
     - Danish business customers can be billed with OIO electronic invoices.
     - :ref:`r124 <changelog-r124>`
   * - .. _feature-entry-2024-automated-e-invoice-delivery:

       Automated e-invoice delivery
     - EHF and OIO e-invoices are delivered automatically through VaxTransfer, without manual file transfers.
     - :ref:`r124 <changelog-r124>`
   * - .. _feature-entry-2024-automatic-card-updates:

       Automatic card updates
     - Card details are refreshed automatically when a subscriber's card is replaced, reducing failed payments.
     - :ref:`r124 <changelog-r124>`
   * - .. _feature-entry-2024-prepaid-account-balance:

       Prepaid account balance
     - Payments can be placed on a subscriber's account and used for later billing.
     - :ref:`r124 <changelog-r124>`, :ref:`r125 <changelog-r125>`
   * - .. _feature-entry-2024-transactional-invoicing:

       Transactional invoicing
     - Non-recurring invoices can be created manually in an ERP-style view.
     - :ref:`r125 <changelog-r125>`
   * - .. _feature-entry-2024-subscriber-audit-log:

       Subscriber audit log
     - Merchants can see a log of important operations performed for each subscriber.
     - :ref:`r125 <changelog-r125>`
   * - .. _feature-entry-2024-one-off-vipps-mobilepay-payments:

       One-off Vipps MobilePay payments
     - Single invoices, reminders, prepaid top-ups and single items can be paid with Vipps or MobilePay.
     - :ref:`r126 <changelog-r126>`
   * - .. _feature-entry-2024-one-off-card-payments:

       One-off card payments
     - Single invoices and reminders can be paid by card through Swedbank Pay without a recurring agreement.
     - :ref:`r127 <changelog-r127>`
   * - .. _feature-entry-2024-profile-sharing-checkout:

       Profile-sharing checkout
     - Subscriber contact details are created automatically from the Vipps or MobilePay profile during checkout.
     - :ref:`r128 <changelog-r128>`
   * - .. _feature-entry-2024-repeat-offer-prevention:

       Repeat-offer prevention
     - Subscribers can be prevented from repeatedly switching between discounted offers.
     - :ref:`r128 <changelog-r128>`, :ref:`r130 <changelog-r130>`
   * - .. _feature-entry-2024-revenue-and-user-kpis:

       Revenue and user KPIs
     - Pre-calculated KPIs, including monthly recurring revenue, for reporting and the Merchant dashboard.
     - :ref:`r128 <changelog-r128>`, :ref:`r130 <changelog-r130>`
   * - .. _feature-entry-2024-shared-subscriber-ownership:

       Shared subscriber ownership
     - Several users can be mapped to the same subscriber as co-owners of its subscriptions.
     - :ref:`r128 <changelog-r128>`

.. _feature-timeline-2023:

2023
====

.. list-table:: Features in 2023
   :header-rows: 1
   :widths: 32 52 16

   * - Feature
     - What it enables
     - Release notes
   * - .. _feature-entry-2023-detailed-churn-reporting:

       Detailed churn reporting
     - Cancellations are classified by type, so churn reports can separate real churn from plan changes and other process-driven cancellations.
     - :ref:`r109 <changelog-r109>`
   * - .. _feature-entry-2023-address-suggestions-while-typing:

       Address suggestions while typing
     - Subscribers and merchant users get street, house and apartment suggestions from Distribution Innovation as they type.
     - :ref:`r109 <changelog-r109>`, :ref:`r114 <changelog-r114>`
   * - .. _feature-entry-2023-email-domain-based-access:

       Email-domain based access
     - Everyone who signs up with a given email domain, such as a company domain, automatically gets access to a subscription.
     - :ref:`r115 <changelog-r115>`, :ref:`r116 <changelog-r116>`
   * - .. _feature-entry-2023-automatic-settlement-of-reminders:

       Automatic settlement of reminders
     - When a subscriber pays the original amount, the demand is settled automatically and the reminder fee is credited.
     - :ref:`r116 <changelog-r116>`
   * - .. _feature-entry-2023-bulk-enterprise-plan-registration:

       Bulk Enterprise Plan registration
     - Many subscribers and subscriptions can be registered on an Enterprise Plan in one operation.
     - :ref:`r118 <changelog-r118>`
   * - .. _feature-entry-2023-balance-transfers-between-accounts:

       Balance transfers between accounts
     - Billing account transactions can be transferred between accounts and subscribers, with a transfer log for reporting.
     - :ref:`r119 <changelog-r119>`, :ref:`r120 <changelog-r120>`

.. _feature-timeline-2022:

2022
====

.. list-table:: Features in 2022
   :header-rows: 1
   :widths: 32 52 16

   * - Feature
     - What it enables
     - Release notes
   * - .. _feature-entry-2022-permanent-discounts:

       Permanent discounts
     - Long-running discounts for groups such as employees, applied to orders and subscriptions.
     - :ref:`r97 <changelog-r97>`, :ref:`r99 <changelog-r99>`, :ref:`r101 <changelog-r101>`
   * - .. _feature-entry-2022-automated-vipps-settlement:

       Automated Vipps settlement
     - Vipps payments are settled automatically, without importing settlement files.
     - :ref:`r98 <changelog-r98>`
   * - .. _feature-entry-2022-saf-t-financial-export:

       SAF-T financial export
     - SAF-T Financial files for subscription accounting, supporting Norwegian reporting to the authorities.
     - :ref:`r100 <changelog-r100>`
   * - .. _feature-entry-2022-subscriber-access-service:

       Subscriber access service
     - Users are mapped to subscribers and their active products, so websites can grant access from the sign-in token.
     - :ref:`r104 <changelog-r104>`
   * - .. _feature-entry-2022-gdpr-right-to-erasure:

       GDPR right to erasure
     - Personal data can be removed from subscribers, deliveries and invoices while legally required invoice data is kept.
     - :ref:`r105 <changelog-r105>`
   * - .. _feature-entry-2022-refund-registration:

       Refund registration
     - Refunds can be registered, either linked to a payment or standalone.
     - :ref:`r107 <changelog-r107>`
   * - .. _feature-entry-2022-peppol-directory-lookup:

       Peppol directory lookup
     - The Peppol directory is checked automatically, so EHF e-invoices are sent only to registered recipients.
     - :ref:`r107 <changelog-r107>`
   * - .. _feature-entry-2022-avtalegiro-via-mastercard-api:

       AvtaleGiro via Mastercard API
     - AvtaleGiro mandates can be managed through the Mastercard API instead of file transfers.
     - :ref:`r108 <changelog-r108>`

.. _feature-timeline-2021:

2021
====

.. list-table:: Features in 2021
   :header-rows: 1
   :widths: 32 52 16

   * - Feature
     - What it enables
     - Release notes
   * - .. _feature-entry-2021-avtalegiro-direct-debit:

       AvtaleGiro direct debit
     - Norwegian subscribers can pay by AvtaleGiro bank mandates.
     - :ref:`r84 <changelog-r84>`, :ref:`r100 <changelog-r100>`
   * - .. _feature-entry-2021-scheduled-plan-changes:

       Scheduled plan changes
     - Plan changes can be scheduled for a later date instead of taking effect immediately.
     - :ref:`r86 <changelog-r86>`, :ref:`r87 <changelog-r87>`
   * - .. _feature-entry-2021-swedish-bankgirot-invoices:

       Swedish Bankgirot invoices
     - Invoices can carry Bankgirot payment references, so Swedish subscribers can pay by invoice.
     - :ref:`r86 <changelog-r86>`, :ref:`r87 <changelog-r87>`
   * - .. _feature-entry-2021-undo-and-resume-cancellations:

       Undo and resume cancellations
     - Scheduled cancellations can be undone, and cancelled subscriptions can be resumed.
     - :ref:`r92 <changelog-r92>`, :ref:`r95 <changelog-r95>`
   * - .. _feature-entry-2021-autogiro-direct-debit:

       AutoGiro direct debit
     - Swedish subscribers can pay by AutoGiro mandates through Bankgirot.
     - :ref:`r89 <changelog-r89>`, :ref:`r95 <changelog-r95>`
   * - .. _feature-entry-2021-kilkaya-conversion-tracking:

       Kilkaya conversion tracking
     - Orders can be tracked in Kilkaya to identify the content that drives conversions.
     - :ref:`r96 <changelog-r96>`

.. _feature-timeline-2020:

2020
====

.. list-table:: Features in 2020
   :header-rows: 1
   :widths: 32 52 16

   * - Feature
     - What it enables
     - Release notes
   * - .. _feature-entry-2020-switch-payment-method:

       Switch payment method
     - A running subscription can be moved to another payment method, including by subscribers in Self-Service.
     - :ref:`r69 <changelog-r69>`, :ref:`r70 <changelog-r70>`, :ref:`r72 <changelog-r72>`
   * - .. _feature-entry-2020-distribution-innovation-integration:

       Distribution Innovation integration
     - Recurring deliveries can be exported to Distribution Innovation for physical distribution.
     - :ref:`r72 <changelog-r72>`, :ref:`r76 <changelog-r76>`
   * - .. _feature-entry-2020-reporting-tags:

       Reporting tags
     - Tags such as a store or campaign can be attached to orders for attribution reporting.
     - :ref:`r73 <changelog-r73>`, :ref:`r81 <changelog-r81>`
   * - .. _feature-entry-2020-multiple-organizations:

       Multiple organizations
     - One tenant can sell under several organizations, with order pages targeting a specific organization.
     - :ref:`r73 <changelog-r73>`, :ref:`r74 <changelog-r74>`
   * - .. _feature-entry-2020-swedbank-pay-card-payments:

       Swedbank Pay card payments
     - Card payments through Swedbank Pay's eCommerce gateway.
     - :ref:`r74 <changelog-r74>`, :ref:`r76 <changelog-r76>`
   * - .. _feature-entry-2020-standard-subscription-reports:

       Standard subscription reports
     - Merchants get ready-made subscription reports without building their own.
     - :ref:`r76 <changelog-r76>`
   * - .. _feature-entry-2020-automatic-payment-retries:

       Automatic payment retries
     - Failed payment requests, such as card captures, are retried automatically according to configurable rules.
     - :ref:`r77 <changelog-r77>`, :ref:`r79 <changelog-r79>`
   * - .. _feature-entry-2020-additional-products:

       Additional products
     - Subscribers can add extra products to a subscription.
     - :ref:`r77 <changelog-r77>`
   * - .. _feature-entry-2020-binding-contracts:

       Binding contracts
     - Subscribers can be bound to contract terms, with a fee for early cancellation or change.
     - :ref:`r77 <changelog-r77>`, :ref:`r89 <changelog-r89>`
   * - .. _feature-entry-2020-shared-digital-access:

       Shared digital access
     - Subscribers can give several users access to one subscription and manage them themselves.
     - :ref:`r77 <changelog-r77>`
   * - .. _feature-entry-2020-scheduled-address-changes:

       Scheduled address changes
     - Address changes, such as temporary holiday addresses, can be scheduled in advance.
     - :ref:`r77 <changelog-r77>`
   * - .. _feature-entry-2020-one-off-charges:

       One-off charges
     - One-off items and balance-settling invoices can be billed outside the regular billing cycle.
     - :ref:`r79 <changelog-r79>`, :ref:`r82 <changelog-r82>`
   * - .. _feature-entry-2020-build-your-own-bundles:

       Build-your-own bundles
     - A plan can let customers choose any number of the available products.
     - :ref:`r80 <changelog-r80>`
   * - .. _feature-entry-2020-vipps-recurring-payments:

       Vipps recurring payments
     - Subscribers can pay recurring subscriptions with Vipps.
     - :ref:`r83 <changelog-r83>`
   * - .. _feature-entry-2020-subscriber-event-webhooks:

       Subscriber event webhooks
     - Integrations can react automatically to changes to subscribers and their contacts.
     - :ref:`r83 <changelog-r83>`

.. _feature-timeline-2019:

2019
====

Coverage for 2019 is partial: the release-note record starts on March 15, 2019.

.. list-table:: Features in 2019
   :header-rows: 1
   :widths: 32 52 16

   * - Feature
     - What it enables
     - Release notes
   * - .. _feature-entry-2019-tenant-reporting-database:

       Tenant reporting database
     - Each tenant gets a separate reporting database for its own BI and analysis.
     - :ref:`r54 <changelog-r54>`
   * - .. _feature-entry-2019-arvato-invoice-factoring:

       Arvato invoice factoring
     - Invoices can be sent to Arvato so that invoicing and collection go through factoring.
     - :ref:`r54 <changelog-r54>`
   * - .. _feature-entry-2019-crediting-and-credit-notes:

       Crediting and credit notes
     - Invoices and payment demands can be credited, with credit notes issued.
     - :ref:`r54 <changelog-r54>`, :ref:`r65 <changelog-r65>`
   * - .. _feature-entry-2019-ehf-e-invoicing:

       EHF e-invoicing
     - Business subscribers with an organization number can receive EHF e-invoices.
     - :ref:`r55 <changelog-r55>`, :ref:`r56 <changelog-r56>`
   * - .. _feature-entry-2019-fixed-term-subscriptions:

       Fixed-term subscriptions
     - Subscriptions can stop automatically after the initial or a later period instead of renewing.
     - :ref:`r55 <changelog-r55>`, :ref:`r56 <changelog-r56>`
   * - .. _feature-entry-2019-automatic-stop-for-non-payment:

       Automatic stop for non-payment
     - Subscriptions are stopped automatically when payment is not received.
     - :ref:`r56 <changelog-r56>`
   * - .. _feature-entry-2019-enterprise-plans:

       Enterprise plans
     - Organizations can hold many subscriptions under one plan with consolidated billing.
     - :ref:`r59 <changelog-r59>`
   * - .. _feature-entry-2019-subscription-pausing:

       Subscription pausing
     - Subscriptions can be paused temporarily instead of cancelled.
     - :ref:`r59 <changelog-r59>`
   * - .. _feature-entry-2019-custom-deal-pricing:

       Custom deal pricing
     - Orders can carry negotiated prices and a future start date, supporting custom sales deals and pre-sold subscriptions.
     - :ref:`r61 <changelog-r61>`, :ref:`r63 <changelog-r63>`, :ref:`r66 <changelog-r66>`
   * - .. _feature-entry-2019-auth0-subscriber-login:

       Auth0 subscriber login
     - Subscribers sign in through Auth0, with subscriber information attached to their user and logins restricted to actual subscribers.
     - :ref:`r61 <changelog-r61>`, :ref:`r67 <changelog-r67>`
   * - .. _feature-entry-2019-recurring-deliveries:

       Recurring deliveries
     - Physical deliveries are scheduled automatically from delivery calendars on products.
     - :ref:`r63 <changelog-r63>`
   * - .. _feature-entry-2019-automatic-credit-control:

       Automatic credit control
     - New orders are denied automatically for subscribers whose account balance exceeds a configured limit.
     - :ref:`r63 <changelog-r63>`, :ref:`r64 <changelog-r64>`
   * - .. _feature-entry-2019-kartverket-address-matching:

       Kartverket address matching
     - Norwegian delivery addresses are matched automatically against Kartverket, the Norwegian mapping authority.
     - :ref:`r65 <changelog-r65>`
   * - .. _feature-entry-2019-product-mix-reporting:

       Product-mix reporting
     - Products can be grouped, for example as Digital or Freemium, so reports show performance by product type.
     - :ref:`r65 <changelog-r65>`, :ref:`r66 <changelog-r66>`
   * - .. _feature-entry-2019-google-tag-manager:

       Google Tag Manager
     - Order and Self-Service pages can send events, such as completed orders, to Google Tag Manager for marketing analytics.
     - :ref:`r66 <changelog-r66>`, :ref:`r85 <changelog-r85>`, :ref:`r145 <changelog-r145>`
   * - .. _feature-entry-2019-plan-changes-with-proration:

       Plan changes with proration
     - Subscribers can upgrade or downgrade during a period, with consumed and remaining time prorated.
     - :ref:`r67 <changelog-r67>`
