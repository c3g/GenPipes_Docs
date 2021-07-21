# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'GenPipes Mermaid Workflow Diagrams'
copyright = '2021, Shaloo Shalini'
author = 'Shaloo Shalini'

# The full version, including alpha/beta/rc tags
release = 'July 20,2021'

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
        'sphinxcontrib.spelling',
        'sphinxcontrib.mermaid',
]

#mermaid_params = ['--theme', 'forest', '--width', '600', '--backgroundColor', 'transparent']
# The resolution is not great
#mermaid_output_format = 'png'
# The generated svg is not readable 
#mermaid_output_format = 'svg'

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'alabaster'
html_show_authors = True
html_show_copyright = False
html_sidebars = { '**': [] }
html_theme_options = {
        #alabaster
        'sidebar_collapse': 'True',
        'show_powered_by': 'False',
}

html_show_sourcelink = False

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']
