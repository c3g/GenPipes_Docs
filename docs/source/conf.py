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
import sphinx_rtd_theme
#import sys
#sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'GenPipes'
author = u'Shaloo Shalini (GSoD 2019) GenPipes' 
show_authors = False
#copyright =  author

copyright = u'GenPipes (GSoD 2019)'

# The full version, including alpha/beta/rc tags

versionfile=open('../VERSION', 'r')
vstr1=versionfile.read()
versionfile.close()

version = u'Version '+vstr1
#release = u' '+vstr1+u'( 0.9 draft )' 
release = u' '+vstr1 

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [ 'sphinxcontrib.spelling',
               'recommonmark',
               'sphinx_markdown_tables',
               'sphinx_git',
               'sphinx_rtd_theme',
               'sphinx.ext.autosectionlabel',
               'sphinx.ext.imgmath',
               'sphinx_tabs.tabs',
]

# Configure autosectionlabel extension
autosectionlabel_prefix_document = True
autosectionlabel_maxdepth = 3

# Spelling language.
spelling_lang = 'en_US'

# Location of word list.
spelling_word_list_filename = 'spelling_wordlist.txt'
spelling_show_suggestions=True

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

html_last_updated_fmt = '\n %c'
#html_last_updated_fmt = '%b %d, %Y at %H:%M'

html_context = {
#    'css_files': [
#        '_static/theme_overrides.css',  # override wide tables in RTD theme
#        ],
#     'commit': os.getenv('TRAVIS_COMMIT', '')[:7],
#     'commit': '3.1.4'
     }

html_theme_options = {
	'display_version': True,
#        'style_nav_header_background': '#1d75c8',
}

#linkcheck configuration settings

user_agent = 'Mozilla/5.0 (X11; Linux x86_64; rv:25.0) Gecko/20100101 Firefox/25.0'

#linkcheck_timeout = 10 
#linkcheck_workers = 10
#linkcheck_retries = 3
linkcheck_ignore = [ 
        r'https://www.computationalgenomics.ca/*.gz$',
        r'https://datahub-90-cw3.p.genap.ca/*',
        r'https://www.computationalgenomics.ca/tutorial/*',
        r'https://bitbucket.org/mugqic/genpipes/downloads/*',
        ]

# -- Options for LaTeX output ------------------------------------------------

latex_logo = 'img/genpipe_logo.png'
latex_additional_files = ['gp_pdf.txt']
latex_toplevel_sectioning = 'section'
latex_engine = 'xelatex'
latex_use_xindy = False
latex_appendices = []
latex_show_urls = 'no'
latex_show_pagerefs = True

latex_elements = {
        # -- The paper size ('letterpaper' or 'a4paper').  ---------------------
        # 'papersize': 'letterpaper',

        #'fncychap': r'',
        'fncychap': r'\usepackage[Lenny]{fncychap}',
        #'fncychap': r'\usepackage[Bjornstrup]{fncychap}',
        #'fncychap': r'\usepackage[Rejne]{fncychap}',

        'printindex': r'\footnotesize\raggedright\printindex',
        'extraclassoptions': 'openany',

        # -- The font size ('10pt', '11pt' or '12pt'). -------------------------
        'pointsize': '11pt',

        #'pxunit': '0.6bp',


        # -- Additional stuff for the LaTeX preamble. --------------------------
        'preamble': r'''
                        \makeatletter
                        \input{gp_pdf.txt}
                        \makeatother
                    ''',

        # -- Latex figure (float) alignment ------------------------------------
        #'figure_align': 'htbp',
        'figure_align': 'H',

        'sphinxsetup': \
                      'InnerLinkColor={rgb}{0.2,0.51,0.96}, \
                       OuterLinkColor={rgb}{0.2,0.51,0.96}, \
                       shadowsep={0pt}, \
                       shadowsize={0pt}, \
                       shadowrule={0pt}',
    }

#numfig = True
numfig_format = {'figure': 'Fig. %s'}
numfig_secnum_depth = 1

# -- Grouping the document tree into LaTeX files.  -----------------------------
# List of tuples (source start file, target name, title, author,
# documentclass [howto, manual, or own class]).

latex_documents = [
        (master_doc, 'index.tex', u'GenPipes Documentation', '', 'manual', False),
]

