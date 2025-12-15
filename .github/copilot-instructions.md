# GitHub Copilot Instructions for INFO-Subscription Documentation

## Repository Overview

This repository contains the developer and technical documentation for INFO-Subscription, built using Sphinx and reStructuredText (RST). The documentation covers:

- API workflows and usage patterns
- Data model for reporting purposes
- Integration with external providers
- Detailed conceptual explanations beyond the Swagger API reference

## Technology Stack

- **Documentation Generator**: Sphinx
- **Markup Language**: reStructuredText (.rst files)
- **Theme**: sphinx_rtd_theme (Read the Docs theme)
- **Extensions**:
  - sphinxcontrib-mermaid (for diagrams)
  - sphinx-tabs (for tabbed content)
  - sphinxcontrib-contentui (for content UI components)
  - sphinx-copybutton (for code block copy buttons)
- **Build System**: Make (Makefile for Unix/Linux, make.bat for Windows)
- **Hosting**: Read the Docs (see readthedocs.yml)

## Project Structure

```
.
├── source/              # Main documentation source files
│   ├── index.rst       # Documentation homepage
│   ├── conf.py         # Sphinx configuration
│   ├── billing/        # Billing-related docs
│   ├── events/         # Event system docs
│   ├── payments/       # Payment processing docs
│   ├── subscribers/    # Subscriber management docs
│   ├── subscription/   # Subscription lifecycle docs
│   └── ...            # Other topic directories
├── diagramsource/      # Source files for diagrams
├── requirements.txt    # Python dependencies
├── Makefile           # Build commands for Unix/Linux
├── make.bat           # Build commands for Windows
└── readthedocs.yml    # Read the Docs configuration
```

## Building the Documentation

### Prerequisites
```bash
pip install -r requirements.txt
```

### Build Commands
```bash
# Build HTML documentation
make html

# Build and view locally
make html && open build/html/index.html  # macOS
make html && xdg-open build/html/index.html  # Linux
```

The built documentation will be in `build/html/`.

## Documentation Standards

### File Format
- Use `.rst` (reStructuredText) for all documentation files
- Follow existing file naming conventions (lowercase with hyphens)
- Place files in appropriate topic directories under `source/`

### Writing Style
- Write clear, concise, and technical documentation
- Use second person ("you") when addressing developers
- Include code examples where relevant
- Use proper RST syntax for headers, links, code blocks, and lists

### RST Syntax Guidelines
- **Headers**: Use consistent underline styles (= for h1, - for h2, ~ for h3, ^ for h4)
- **Code blocks**: Use `.. code-block:: language` directive
- **Links**: Use proper RST link syntax
- **Lists**: Use consistent bullet or numbered list formatting
- **Notes/Warnings**: Use `.. note::`, `.. warning::`, `.. important::` directives

### Content Organization
- Keep related content together in topic directories
- Update `index.rst` or relevant index files when adding new pages
- Maintain the table of contents (toctree) structure
- Ensure cross-references work correctly

## Making Changes

### Typical Workflow
1. Identify the relevant `.rst` file(s) in the `source/` directory
2. Make minimal, focused changes to address the issue
3. Build the documentation locally to verify changes
4. Check for Sphinx warnings or errors in the build output
5. Review the HTML output to ensure proper rendering
6. Commit changes with clear, descriptive messages

### Testing Changes
Always build the documentation after making changes:
```bash
make html
```

Check the build output for:
- Warnings about broken links or references
- Syntax errors in RST files
- Missing files or toctree issues

### Common Tasks

#### Adding a New Documentation Page
1. Create a new `.rst` file in the appropriate directory
2. Add proper RST header structure
3. Include the new file in a `toctree` directive in the parent index
4. Build and verify the page appears in navigation

#### Updating Existing Content
1. Locate the relevant `.rst` file
2. Make focused changes preserving existing formatting
3. Ensure cross-references remain valid
4. Build to verify no warnings introduced

#### Adding Code Examples
Use the code-block directive with appropriate language:
```rst
.. code-block:: python

   # Your code example here
   def example():
       pass
```

## Contributing Guidelines

- Follow the contribution guidelines in README.md
- Keep PRs focused on specific documentation improvements
- Ensure all Sphinx builds complete without errors
- Maintain consistency with existing documentation style
- Test that all internal links work correctly

## Things to Avoid

- Don't modify the `conf.py` file unless specifically working on Sphinx configuration
- Don't change the theme or major structural elements without discussion
- Don't add dependencies to `requirements.txt` without necessity
- Avoid restructuring the entire documentation tree in a single PR
- Don't remove or significantly alter existing content without understanding its purpose

## Best Practices for Copilot

- **Scope**: Focus on documentation content improvements, not infrastructure changes
- **Style**: Match the existing tone and formatting of surrounding documentation
- **Testing**: Always build the documentation to verify changes render correctly
- **Minimal Changes**: Make the smallest changes necessary to address the issue
- **Context**: Consider how changes fit into the overall documentation structure
- **Links**: Verify that all cross-references and external links remain valid

## Read the Docs Integration

This repository is configured for Read the Docs hosting via `readthedocs.yml`. Changes to the main branch are automatically built and deployed. Ensure:
- All builds complete successfully
- No warnings are introduced
- The documentation structure remains compatible with Read the Docs
