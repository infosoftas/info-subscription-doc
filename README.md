# INFO-Subscription Developer Documentation

This repo contains the source/markup for the developer/technical documentation for INFO-Subscription.

This covers areas such as

* Typical workflows using the API.
* Understanding the datamodel for reporting purposes.
* Understanding the integration with external providers.
* Detailed/Conceptual explainations for the API where the reference documentation (Swagger) is insufficient.

## Contributing

* Feel free to create PRs if you feel like you know something that should be included in the documentation.
* Create issues for documentation that you think is missing, remember to be precise in your issue description.

### Maintaining the feature timeline with Copilot

Two repository skills support the yearly update workflow:

* `summarize-feature-year` reviews current and archived public release notes and saves an evidence-backed selection in `.github/skills/summarize-feature-year/summaries/YYYY.md`.
* `update-feature-timeline` uses that summary to update the year tiles, feature cards, yearly tables, release links, and coverage notes in `source/changelog/feature-timeline.rst`.

For example, ask Copilot to "Use summarize-feature-year to review 2027", then
"Use update-feature-timeline to publish the 2027 summary". You can also request
both steps together. The summary step does not publish changes by itself.

In an existing Copilot CLI session, run `/skills reload` after adding these skills.
