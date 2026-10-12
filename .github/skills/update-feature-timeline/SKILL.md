---
name: update-feature-timeline
description: Add a new year or update an existing year's INFO-Subscription feature timeline from an evidence-backed yearly summary. Use when publishing selected features, refreshing yearly counts, or extending the innovation timeline and its release-note tables.
---

# Update the feature timeline

Use `.github/skills/summarize-feature-year/summaries/YYYY.md` as the reviewed
input. If the summary does not exist or lacks coverage for the requested
releases, use `summarize-feature-year` first. If the user supplies another
summary, check that it contains the same evidence and decisions.

The persistent public source is `source/changelog/feature-timeline.rst`.
Read and edit that file in the active worktree; do not depend on an earlier
Copilot session's generator, ledger, filesystem paths, or temporary artifacts.

## Check the input

1. Read the summary and current timeline, including earlier years for
   duplicates. Verify selected items against their cited release sections.
2. Publish only selected features, not unresolved borderline candidates.
   Preserve previously reviewed entries not explicitly superseded by the
   summary. Do not remove a feature simply because an incremental summary
   only lists new announcements; clarify proposed removals if needed.
3. Resolve cross-year duplicates using the first announcement rule. Publish
   later expansions only when their independently meaningful outcome is
   documented. Keep names and benefits consistent between summary and page.

## Update every representation

The page contains raw HTML for its visual timeline followed by RST yearly
tables. Update all of these together:

- **Summary tile:** an `<a href="#timeline-year-YYYY">` whose count matches
  the selected features for that year. Keep its accessible label accurate.
- **Year marker:** a `feature-history-year` element with
  `id="timeline-year-YYYY"`, followed by that year's feature list.
- **Feature cards:** alternate `feature-history-left` and
  `feature-history-right` within each year. Each card links to its table
  entry, using the same name displayed in that entry.
- **Yearly table:** use `.. _feature-timeline-YYYY:` above the year heading,
  with columns **Feature**, **What it enables**, and **Release notes**.
  Each feature's first cell contains its target, a blank line, and the name.
  Cite existing release labels with `:ref:` links. When a feature has no
  release-note announcement, cite its documentation page instead, for
  example :ref:`MCP Server <mcp-server>`.
- **Coverage text:** update the partial-year note below the year heading to
  the actual summary cutoff. The page has no introduction; do not add one.
  A previous year's partial coverage does not become
  complete merely because a new year is added. Remove a partial-year note
  only when a full review supports that change.

Keep years newest first in the tiles, timeline, and tables. Within each year,
keep features in first-announcement order. Do not display months, exact dates,
preview suffixes, or a preview column in the cards or tables. Coverage prose
can include an exact release date. Preserve the HTML/CSS alternating-card
design, mobile layout, keyboard focus styling, and scroll offsets. Do not
reintroduce Mermaid, circles, or connector dashes.

### Feature targets

For a new feature, use `feature-entry-YYYY-<slug>`, where the slug is the
lowercase feature name with each run of characters outside `a-z0-9` replaced
by one hyphen, and leading/trailing hyphens removed. Check uniqueness and
choose a stable distinguishing suffix if two names collide. Preserve existing
targets on intentional renames so incoming links continue to work.

Follow the existing list-table indentation:

```rst
   * - .. _feature-entry-YYYY-feature-name:

       Feature name
     - A concise explanation of the newly enabled customer outcome.
     - :ref:`rNNN <changelog-rNNN>`
```

The card's `href` must exactly match this target. Year tiles link to the
visual year markers, not to the table headings.

## Release-note reachability

Every cited release must be rendered by the current changelog or a reachable
archive wrapper. If a source `.inc` is omitted, include it in the appropriate
year wrapper; if that wrapper is new, add it to `archive.rst`'s toctree.
Follow existing include paths and avoid including the same release twice,
which produces duplicate reference labels. Do not reorganize unrelated
changelog content or alter release-note claims.

## Validate and finish

Run `make html` from the worktree using the repository's configured Sphinx
environment. If Sphinx or an extension is missing, use an available project
virtual environment or install `requirements.txt` into a project virtual
environment before retrying. Do not hardcode another checkout's environment.
Compare warnings with the baseline; fix warnings introduced by this update.

Inspect `build/html/changelog/feature-timeline.html` and confirm:

- Every tile and card fragment link resolves to exactly one target.
- Each year's tile count equals its card count and table-entry count, and
  feature names match between the cards and tables.
- Years and features have the required ordering; all release links resolve.
- Existing years and reviewed selections are preserved.

Check the rendered page at desktop and mobile widths when browser tooling is
available, including one tile-to-year and one card-to-table click, keyboard
focus, and horizontal overflow. If unavailable, state that limitation rather
than claiming a visual check. Stop any temporary server started for the check.

Keep the diff focused. Do not commit unless asked. Report the years updated,
resulting feature counts, and any unresolved evidence or coverage limitations.
