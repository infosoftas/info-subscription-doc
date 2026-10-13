---
name: summarize-feature-year
description: Generate or update an evidence-backed yearly summary of significant INFO-Subscription features from the public changelog, including archived releases. Use when reviewing a new year, refreshing a year's feature selection, or preparing features for the innovation timeline.
---

# Summarize a feature year

Produce a reusable research summary, not a public documentation page. Do not
change the timeline unless the user also requests that step; use the
`update-feature-timeline` skill for publishing.

## Find and review the evidence

1. Work in the user's active checkout or worktree. If the year is unspecified
   and cannot be inferred from the request, ask which year to review.
2. Read `source/changelog/feature-timeline.rst` and any existing summary at
   `.github/skills/summarize-feature-year/summaries/YYYY.md`. Preserve previously
   reviewed selections unless new evidence or the user justifies a change.
3. Inventory the public release notes using `source/changelog/changelog.rst`,
   `source/changelog/archive.rst`, and its yearly wrappers. Also inspect
   `source/changelog/*.inc` and `source/changelog/Archive/*.inc` for release
   notes omitted from those wrappers. Do not assume one file equals one year:
   a file can contain multiple dated release sections, and a year can be split
   between the current changelog and archive.
4. Read every release section for the requested year in full, including
   introductions, nested bullets, and all client/backend sections. Do not
   search only for "Added", or classify items solely by their heading.
5. Record the actual release date and exact reference label of each release
   section. Every dated section must have its own label: `changelog-rNNN` for
   the main release in `rNNN.inc`, and `changelog-rNNN-hotfix` for an
   additional hotfix section in the same file (add a stable distinguishing
   suffix if a file has more than one). If a section lacks a label, add one
   using this convention rather than citing a label that points to a
   different section. Explain inferred dates and unresolved ambiguities.
   Establish the earliest and latest covered releases; do not claim a complete
   year if the evidence only covers part of it.
6. Some launches, such as new APIs or developer tools, are documented without
   a release-note announcement. Check documentation pages added or changed
   during the year (`git log --diff-filter=A --since=YYYY-01-01
   --until=YYYY-12-31 -- source`) and ask the user about known launches that
   the evidence does not cover. Date such features from the user or the page's
   git history, and cite the page's reference label.

## Select significant capabilities

Include new capabilities and substantial expansions that enable a materially
new customer workflow, business model, integration, market/payment reach,
automation, checkout/self-service experience, or reporting outcome.

Always include the first announcement of a new third-party integration (for
example payment, distribution, identity, e-invoicing, address, analytics or
tracking services), even when its scope is narrow. Later changes to an existing
integration follow the normal rules.

Exclude bug fixes, maintenance, styling/translations, performance/resilience
without a new capability, removals, routine validation, and minor conveniences.
A field, toggle, filter, or reporting addition is not automatically significant:
evaluate the business outcome it enables. For example, cancellation
classification can enable **Detailed churn reporting**, rather than merely
"cancellation types".

Count a capability once at its first publicly announced availability, including
announcements made before general availability. Do not add it again for later
general availability or exposure in another client. A later independently
meaningful expansion can qualify, but explain what is new. Compare related
announcements across earlier years and the existing timeline to avoid
cross-year duplicates.

Use concise, customer-facing feature names and a one-sentence explanation of
what each enables. Avoid endpoint names, hype, and unsupported claims. Do not
append "(preview)" or add a preview column to the selected features.

Do not pad sparse years or target a feature count. Record borderline candidates
with their business outcome and inclusion/exclusion rationale. Ask the user to
resolve genuinely ambiguous candidates when needed, without blocking clearly
supported selections.

## Persist the summary

Create or update
`.github/skills/summarize-feature-year/summaries/YYYY.md`. This is internal
review evidence; it is not included in Sphinx navigation. Use this structure:

```markdown
# Significant features: YYYY

## Scope
Year: YYYY
Coverage: YYYY-MM-DD through YYYY-MM-DD
Completeness: partial or complete, with the evidence supporting that claim

## Coverage
| Source file | Release section/date(s) reviewed | Reference label(s) |
|-------------|----------------------------------|--------------------|

## Selected features
| First announcement | Feature | What it enables | Source file and section | Release reference(s) | Selection rationale |
|--------------------|---------|-----------------|-------------------------|----------------------|---------------------|

## Borderline candidates
| Candidate | What it enables | Evidence | Decision and rationale |
|-----------|-----------------|----------|------------------------|

## Notable exclusions and duplicates
| Candidate | Evidence | Reason or existing timeline feature/year |
|-----------|----------|------------------------------------------|

## Changes since the previous summary
Describe additions, revised evidence, and any proposed removals or renames.
```

Sort selected features by first announcement within the year. Retain useful
prior decisions, incorporate newly reviewed releases, and deduplicate when
updating. If a selected feature is already in the timeline, use its existing
name unless a rename is intentional; record that rename explicitly.

Before finishing, check that every inventoried release section for the year is
in the coverage table, every selected feature has source evidence and a real
reference label, and no unresolved candidate has silently become selected.
Flag any evidence not currently rendered by a changelog/archive wrapper so the
publishing skill can make its reference available. Report the selection count,
coverage cutoff, and outstanding decisions without modifying public release
notes or automatically publishing the summary.
