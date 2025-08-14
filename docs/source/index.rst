.. .. codeauthor:: Shaloo Shalini <shaloo_shalini@yahoo.com>

GenPipes v\ |genpipes_version|\  Documentation
==============================================

.. dropdown:: :material-outlined:`bolt;2em` Usage Change Effective v5.x onward
   :color: success

   .. include:: gp5_0.inc

.. dropdown:: :material-outlined:`handshake;2em` Sponsors
   :color: info

   GenPipes is an open-source genomics workflow and next generation gene sequencing pipeline platform. It is developed and financed by the `Canadian Centre for Computational Genomics <https://www.computationalgenomics.ca>`_ (C3G).

   C3G, a core platform affiliated with `McGill University <https://www.mcgill.ca>`_, provides bioinformatics analysis and HPC services for life sciences research. 

   These services include:
   
   * Bespoke pipeline development
   * Fee-based analyses
   * Other suite of software solutions genomics  

.. dropdown::  :material-outlined:`coronavirus;2em` Fighting COVID-19
   :color: secondary

   GenPipes offers two pipelines: :ref:`CoVSeq<docs_gp_covseq>` for short-read sequencing (e.g., Illumina) and :ref:`Nanopore_CoVSeq<docs_gp_nanopore_cov>` for long-read sequencing. These pipelines help researchers analyze viral sequences and detect mutations quickly, preventing the spread of new strains.

Welcome
--------

GenPipes is a flexible Python-based framework to facilitates the development and deployment of multi-step genomic workflows, optimized for High-Performance Computing (HPC) clusters and the cloud. It offers open-source, validated and scalable :ref:`gene sequencing pipelines<docs_pipeline_ref>` for various :ref:`genomics applications<docs_gp_usecases>`.

Audience
+++++++++

This documentation is meant for new genomics users as well as seasoned ones. We welcome all :ref:`contributions<docs_contributing>` to pipelines and its documentation from the open source community. To learn more about how this documentation is organized, see :ref:`Documentation Map<docs_genpipes_archmap>`.

----

**Table of Contents** 

----

.. toctree::
   :maxdepth: 1
   :caption: GenPipes 
   :name: sec-general

   about/index
   get-started/gp_usecases
   faq/gp_faq

.. toctree::
   :maxdepth: 1
   :caption: Get Started
   :name: sec-learn

   deploy/how_to_deploy_genpipes
   get-started/index
   user_guide/user_guide
   tutorials/list_tutorials

.. toctree::
   :maxdepth: 1
   :caption: Support
   :name: sec-support

   support/how_to_get_support

.. toctree::
   :maxdepth: 1
   :caption: Community
   :name: sec-community

   community/channels
   community/contributing

.. toctree::
   :maxdepth: 1
   :caption: Resources
   :name: sec-resources

   resources/citation
   resources/publications
   resources/workshops
   resources/testdataset
   resources/compute_resources

.. toctree::
   :maxdepth: 1
   :caption: Development
   :name: sec-devel

   development/release_notes
   development/gp_release_instructions
   development/dev_guide
   development/troubleshooting_guide

.. toctree::
   :maxdepth: 1
   :caption: Documentation
   :name: sec-documentation

   documentation/about
   documentation/genpipes_doc_archmap
   documentation/docs_changelog

.. Indices and tables
.. ------------------
..
.. * :ref:`genindex`
.. * :ref:`modindex`
.. * :ref:`search`

.. _GitHub Issue 110: https://github.com/c3g/GenPipes/issues/110
