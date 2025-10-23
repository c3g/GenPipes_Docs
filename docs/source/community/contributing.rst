.. _docs_contributing:

.. spelling:word-list::

     metagenomics

Contribution
=============

The GenPipes team at C3G welcomes all contributions from the open source community!

GenPipes bioinformatics pipelines were originally developed at the Canadian Centre for Computational Genomics (C3G), as part of the GenAP project. These, are now open source and available for public use. 

The :ref:`pipelines<docs_pipeline_ref>` can be used for DNA, RNA-Seq, ChIP-Seq, WGS, long-read DNA sequencing, metagenomics and SARS-CoV-2 genomic analysis.

Your Contributions
-------------------

**We love your input!**

Do share your feedback related to GenPipes usage, documentation or code changes and feature requests.

You can contribute by:

#. Reporting a bug or issue
#. Submitting a fix
#. Proposing new features
#. Discussing code optimizations
#. Becoming a maintainer

GenPipes Source Repository
---------------------------

Earlier, GenPipes pipeline sources were hosted at `Bitbucket <https://bitbucket.org/mugqic/genpipes/src/master/>`_. Starting GenPipes v6.0.0, GitHub is our preferred source code repository and used for tracking issues and feature requests. 

* `Pipeline Repository <https://github.com/c3g/GenPipes>`_
* `Documentation Repository <https://github.com/c3g/GenPipes_Docs>`_ 

You can submit issues and pull requests and get involved.

When issuing a GitHub pull request, follow these guidelines:

* Fork the repo and create your branch from master.
* If you have added code that should be tested, add relevant tests.
* If applicable, update the documentation sources for the changes in usage, if any.
* Ensure the test suite passes.
* Make sure your code lints.
* Issue a pull request!

.. admonition:: "Test your fixes"
   :class: note

   Before submitting your code changes for GenPipes or the documentation, please validate the fixes. For GenPipes pipeline code changes, you may need to validate using one of the supported :ref:`deployment options<docs_access_gp_pre_installed>`. For documentation code changes, simply follow the instructions in the ``README`` file in the `GenPipes Documentation repository <https://github.com/c3g/GenPipes_Docs>`_ to build and deploy docs locally to validate the fixes.

License
--------

GenPipes is available under the LGPL `license <https://github.com/c3g/GenPipes/blob/main/COPYING.LESSER>`_. Any contributions you make will be under the LGPLv3 license.

Reporting Issues
-----------------

We recommend the `FaceBook Draft.js Guide <https://github.com/facebook/draft-js/blob/main/CONTRIBUTING.md>`_ when
reporting a bug or an issue related to GenPipes or its documentation.

Please provide the following information when you open a bug or an issue with GenPipes:

* Single line summary with key words about the issue
* Steps to reproduce the issue
  - Specific instructions
  - If required, provided commands and code that caused the issue
  - Make sure you specify GenPipes version number, deployment type
* What was expected and what actually happened
* Other insights or logs that can help debug the issue.