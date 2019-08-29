# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#

import os
#import sys
#sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'gpdocs'
author = u'Shaloo Shalini (GenPipes GSoD 2019)' 
copyright = author 

# The full version, including alpha/beta/rc tags

versionfile=open('../VERSION', 'r')
vstr1=versionfile.read()
versionfile.close()

version = u'Version '+vstr1
release = u' '+vstr1+u'( 0.9 draft )' 

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [ 'sphinxcontrib.spelling',
               'recommonmark',
               'sphinx_markdown_tables',
               'sphinx_git',
               'sphinx_tabs.tabs'
]

# Spelling language.
spelling_lang = 'en_UK'

# Location of word list.
spelling_word_list_filename = 'spelling_wordlist'

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
#

#source_suffix = ['.rst', '.md']
source_suffix = {
                 '.rst': 'restructuredtext',
                 '.md': 'markdown',
}
#source_suffix = '.rst'

product_version = vstr1 

rst_epilog = """
.. |genpipes_version| replace:: %(product_version)s
""" % { "product_version": product_version ,
}

master_doc = 'index'

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
#html_theme = 'alabaster'
#html_theme = 'nature'

on_rtd = os.environ.get('READTHEDOCS') == 'True'
if on_rtd:
    html_theme = 'default'
else:
    html_theme = 'sphinx_rtd_theme'

html_logo = 'img/genpipes_doc_img.png'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']

html_static_path = ['_static']

html_last_updated_fmt = '\n %c'
#html_last_updated_fmt = '%b %d, %Y at %H:%M'

html_context = {
#    'css_files': [
#        '_static/theme_overrides.css',  # override wide tables in RTD theme
#        ],
#     'commit': os.getenv('TRAVIS_COMMIT', '')[:7],
#     'commit': '3.1.4'
     }
