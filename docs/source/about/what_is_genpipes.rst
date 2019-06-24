.. _docs_what_is_genpipes:
  
What is GenPipes?
=================

.. image:: /img/genpipes_hld.png

GenPipes is a workflow management system (WMS) that facilitates building robust genomic workflows. It is a unique solution that combines both a framework for development and end-to-end analysis pipelines, covering a large scope of genomic applications and research domains. It offers researchers a simple method to analyze different types of data, customizable to their needs and resources. In addition, it provides flexibility to create customized workflows besides the ones that are already implemented and validated by GenPipes.

GenPipes is an open source, flexible, scalable Python-based framework that facilitates
the development and deployment of multi-step computational workflows. These workflows
are optimized for High-Performance Computing (HPC) clusters and the cloud.

Following genomics application pipelines are already implemented and validated through GenPipes:

* ChIP-Seq
* De-Novo RNA Sequencing
* Deep Whole Genome Sequencing
* Exome Sequencing
* Hi-C / Capture Hi-Ca
* Illumina raw data processing
* Metagenomics
* PacBio De novo Assembly
* RNA Sequencing / Unmapped RNA Quality Control
* Transcriptonomics Assembly
* Tumour Analysis
* Whole Exome Sequencing (WES)
* Whole Genome Bisulphate Sequencing (WGBS)/ Reduced Representation Bisulphate Sequencing (RRBS)
* Whole Genome Sequencing (WGS)

GenPipes software is available under a GPLv3 open source license and is continuously updated to follow recent advances in genomics and bioinformatics. The framework can be accessed through multiple deployment mechanisms. It has already been configured on several servers at C3G HPC computing facility. Its also supports Cloud deployment through GCP. Besides this,  a Docker image is also available to facilitate additional installations on local / individual machines for small dataset analysis.

GenPipes Features
-----------------
* Multiple Schedulers
  - GenPipes is optimized for HPC processing. Currently, it supports 4 schedulers - Slurm, PBS/Torque, Batch, Daemon.

* Optimal Job Execution Time
  - GenPipes minimizes overall job analysis time by job dependency model that leverages job parallelism. This enables jobs to become active and executed as soon as the dependencies are met.

* Smart Relaunching of Jobs
  - Through smart tracking of job progress, GenPipes can determine which jobs failed and at which steps. This helps to relaunch the jobs at the exact point in time, just before the last failure, automatically.
  
* Parameter Encapsulation
  - GenPipes is a flexible framework that allows user adjustments. It implements a superposed configuration system to reduce the time required to set-up or modify parameters needed during the analysis.

* Diverse Inputs
  - GenPipes is flexible in terms of multiple choice of input files for the analysis. It allows users to skip specific steps in the pipeline if they consider them unnecessary.

* Customizable Workflows
  - GenPipes limits wastage of expensive HPC resources and time as it allows customizable steps in different pipelines enabling users to plug and play with customized pipeline steps. 

About the documentation
-----------------------

This documentation is continuously written, corrected, edited, and revamped by
members of the GenPipes community. It is edited via text files in the
`reStructuredText <http://www.sphinx-doc.org/en/stable/rest.html>`_ markup
language and then compiled into a static website/offline document using the
open source `Sphinx <http://www.sphinx-doc.org>`_ and `ReadTheDocs
<https://readthedocs.org/>`_ tools.

.. note:: You can contribute to Godot's documentation by
          GENPIPES_DOCS_TBD - We need to describe the GenPipes documentation contribution policy here.
