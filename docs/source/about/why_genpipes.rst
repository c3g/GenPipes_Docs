.. _docs_gp_why:

.. spelling::

     metagen
     precipitomics

Why GenPipes?
==============

Genomic sequencing has become an indispensable tool for modern bioinformatics researchers in their quest to understand biological processes. Next-generation sequencing (NGS) is computationally complex, requiring efficient use of high-performance computing infrastructure, scalability, and flexibility. It also demands managing large genome reference data, intermediate results, and dependencies in serial and parallel processes.

GenPipes is a Python-based bioinformatics tool that offers a wide range of NGS genomic sequencing :ref:`pipelines for bioinformatics researchers<docs_available_pipelines>`. 

Developed at the Canadian Centre for Computational Genomics (C3G), GenPipes is available as open-source software offering a wide array of genomic sequencing pipelines. For example, RNA-Seq, ChIP-Seq, Whole Genome Sequencing (WGS), Exome sequencing, long-read DNA sequencing, metagen precipitomics and SARS-CoV-2 genome sequencing pipeline.


.. image:: /img/genpipes_hld.png

Features
---------

#. Supports Multiple Schedulers
  
   - Slurm 
   - PBS/Torque 
   - Batch
   - Daemon

#. Optimal Job Execution Time

   GenPipes reduces job analysis time using a dependency model that enables parallelism. This allows jobs to execute immediately once the dependencies are met.

#. Smart Job Relaunching

   By tracking job progress, GenPipes identifies failed jobs and the exact steps that failed. It restarts jobs from the failure point automatically.

#. Parameter Encapsulation

   GenPipes is a flexible framework that supports user customization. Its layered configuration system simplifies setting or modifying analysis parameters.

#. Supports Multiple Inputs

   GenPipes supports multiple input file options for analysis. It allows users to skip pipeline steps if deemed unnecessary.

#. Customizable Workflows

   GenPipes saves high-performance computing (HPC) resources and time with customizable pipeline steps, allowing users to configure workflows.


Key Differentiators
-------------------

Since the release of version 2.0.0 in 2014, a community of users has run GenPipes to conduct approximately 3,000 analyses processing ∼100,000 samples.

The following are GenPipes’s key capabilities that distinguish it from other analysis platforms, workbenches, and workflow management systems (WMS):  

#. **Flexibility:** GenPipes can be easily modified and configured. It has a workflow manager that can be adapted to new systems quickly. It supports multiple job schedulers and several deployment types, such as local (containerized, VM, server), cloud (GCP), and hosted on `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_ servers. It provides job status tracking through JSON files that can then be displayed on a web portal (*an official portal for GenPipes will be released soon*). 
#. **Scalability:** GenPipes is optimized for large-scale data analysis. It scales easily for processing and data access needs.  
#. **Built-in Pipelines:** GenPipes provides diverse, pre-built, tested, robust, industry-standard, production-quality pipelines for
   bioinformatics analysis. GenPipes pipelines cover diverse sequencing applications, performing full bioinformatics analysis. Unlike other pipeline solutions that end with a BAM file or include limited post-BAM steps, GenPipes pipelines are extensive, with up to 40 steps for comprehensive post-BAM processing. GenPipes’ :ref:`available pipelines<docs_available_pipelines>` facilitate bioinformatics processing, while the framework makes it flexible for modifications and new implementations.

For details on how GenPipes compares with other NGS solutions, refer to a `tabular comparison of available NGS solutions <https://onlinelibrary.wiley.com/doi/10.1155/2012/251364>`_.