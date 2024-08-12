# -*- coding: utf-8 -*-
#
# Configuration file for the Sphinx documentation builder.
#
# This file does only contain a selection of the most common options. For a
# full list see the documentation:
# http://www.sphinx-doc.org/en/stable/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'INFO-Subscription'
copyright = 'Infosoft AS'
author = 'Infosoft AS'

# The short X.Y version
version = ''
# The full version, including alpha/beta/rc tags
release = ''


# -- General configuration ---------------------------------------------------

# If your documentation needs a minimal Sphinx version, state it here.
#
# needs_sphinx = '1.0'

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.todo',
    'sphinx.ext.imgmath',
    'sphinx.ext.extlinks',
    'sphinx_tabs.tabs',
    'sphinxcontrib.contentui',
    'sphinx_rtd_theme',
    'sphinx_copybutton'
    ]
# extensions = ['sphinx_tabs.tabs']

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
#
# source_suffix = ['.rst', '.md']
source_suffix = '.rst'

# The master toctree document.
master_doc = 'index'

# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#
# This is also used if you do content translation via gettext catalogs.
# Usually you set "language" from the command line for these cases.
language = 'en'

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path .
exclude_patterns = []

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = 'sphinx'


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'

# Theme options are theme-specific and customize the look and feel of a theme
# further.  For a list of options available for each theme, see the
# documentation.
#
html_theme_options = {
    'navigation_depth' : 4,
    'collapse_navigation' : False,
    'sticky_navigation' : False
}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

# Custom sidebar templates, must be a dictionary that maps document names
# to template names.
#
# The default sidebars (for documents that don't match any pattern) are
# defined by theme itself.  Builtin themes are using these templates by
# default: ``['localtoc.html', 'relations.html', 'sourcelink.html',
# 'searchbox.html']``.
#
# html_sidebars = {}

html_logo = '_images/icon.png'
html_favicon = '_images/favicon.ico'
html_show_copyright = False
html_use_opensearch = 'http//docs.info-subscription.com'
html_show_sphinx = False
html_experimental_html5_writer = True

html_context = {
    "display_github": True, # Add 'Edit on Github' link instead of 'View page source'
    "last_updated": False,
    "commit": False,
    "readthedocs" : os.environ.get("READTHEDOCS", ""),
}

# Define the canonical URL if using a custom domain on Read the Docs
html_baseurl = os.environ.get("READTHEDOCS_CANONICAL_URL", "")

# -- Options for HTMLHelp output ---------------------------------------------

# Output file base name for HTML help builder.
htmlhelp_basename = 'INFO-Subscriptiondoc'


# -- Options for LaTeX output ------------------------------------------------

latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',

    # The font size ('10pt', '11pt' or '12pt').
    #
    # 'pointsize': '10pt',

    # Additional stuff for the LaTeX preamble.
    #
    # 'preamble': '',

    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
latex_documents = [
    (master_doc, 'INFO-Subscription.tex', 'INFO-Subscription Documentation',
     'Infosoft AS', 'manual'),
]


# -- Options for manual page output ------------------------------------------

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [
    (master_doc, 'info-subscription', 'INFO-Subscription Documentation',
     [author], 1)
]


# -- Options for Texinfo output ----------------------------------------------

# Grouping the document tree into Texinfo files. List of tuples
# (source start file, target name, title, author,
#  dir menu entry, description, category)
texinfo_documents = [
    (master_doc, 'INFO-Subscription', 'INFO-Subscription Documentation',
     author, 'INFO-Subscription', 'One line description of project.',
     'Miscellaneous'),
]


# -- Options for Epub output -------------------------------------------------

# Bibliographic Dublin Core info.
epub_title = project
epub_author = author
epub_publisher = author
epub_copyright = copyright

# The unique identifier of the text. This can be a ISBN number
# or the project homepage.
#
# epub_identifier = ''

# A unique identification for the text.
#
# epub_uid = ''

# A list of files that should not be packed into the epub file.
epub_exclude_files = ['search.html']


# -- Extension configuration -------------------------------------------------

# -- Options for todo extension ----------------------------------------------

# If true, `todo` and `todoList` produce output, else they produce nothing.
todo_include_todos = True


rst_prolog = """
.. |projectName| replace:: INFO-Subscription
.. |tenantHeader| replace:: ``S4-TenantId``
.. |auth0audience| replace:: https://api.info-subscription.com/
.. |tokenUrl| replace:: https://infosubscription.eu.auth0.com/oauth/token
.. |auth0domain| replace:: infosubscription.eu.auth0.com
.. |ADB2C| replace:: `ADB2C <https://docs.microsoft.com/en-us/azure/active-directory-b2c/overview/>`__
.. |Swedbank| replace:: `Swedbank Pay <https://www.swedbankpay.com/>`__
.. |SwedbankPay| replace:: `Swedbank Pay <https://www.swedbankpay.com/>`__
.. |eFaktura| replace:: `eFaktura <https://www.efaktura.no/>`__
.. |AvtaleGiro| replace:: `AvtaleGiro <https://www.avtalegiro.no/>`__
.. |BetalingsService| replace:: `BetalingsService <https://www.betalingsservice.dk/erhverv/>`__
.. |Vipps| replace:: `Vipps <https://www.vipps.no/>`__
.. |VippsRecurring| replace:: `Vipps Recurring <https://www.vipps.no/>`__
.. |MobilePay| replace:: `MobilePay <https://www.vippsmobilepay.com/>`__
.. |VippsMobilePay| replace:: `VippsMobilePay <https://www.vippsmobilepay.com/>`__
.. |AutoGiro| replace:: `AutoGiro <https://www.autogiro.se/>`__
.. |adb2cAudience| replace:: 7bdcdd56-3ba6-4e6d-a841-db4816d7909d
.. |adb2cMetadataUrl| replace:: https://prodlogins4.b2clogin.com/prodlogins4.onmicrosoft.com/B2C_1A_V2SIGNIN/v2.0/.well-known/openid-configuration
.. |adb2cTokenUrl| replace:: https://prodlogins4.b2clogin.com/prodlogins4.onmicrosoft.com/B2C_1A_V2SIGNIN/oauth2/v2.0/token
.. |adb2cScope| replace:: https://prodlogins4.onmicrosoft.com/api/.default
"""

def replacements(app, docname, source):
    result = source[0]
    for key in app.config.replacementsTags:
        result = result.replace(key, app.config.replacementsTags[key])
    source[0] = result

replacementsTags = {
    "{PRODUCTWEBSITE}" : "`product website <https://www.infosoft.as/solutions/info-subscription/>`_",
    "{AUTH0}" : "`Auth0 <https://www.auth0.com/>`_",
    "{AUTH0DOMAIN}" : "infosubscription.eu.auth0.com",
    "{SUPPORTPAGE}" : "https://www.infosoft.as/contact-us/",
    "{payex}" : "`Swedbank Pay <https://www.swedbankpay.com/>`_",
    "{vipps}" : "`Vipps <https://www.vipps.no/>`_",
    "{mobilePay}" : "`MobilePay <https://www.vippsmobilepay.com/>`_"
}

def setup(app):
   app.add_config_value('replacementsTags', {}, True)
   app.connect('source-read', replacements)

extlinks = {
    'github-issues': ('https://www.github.com/infosoftas/info-subscription/issues/%s', 'Github Issue %s '),
    'api-ref': ('https://api.info-subscription.com/swagger/#/%s', 'API Reference %s'),
}

