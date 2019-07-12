.. _docs_gs_intro:

Introduction
==============
Genomic sequencing has become an indispensable tool for modern bioinformatics researchers in their quest to understand biological processes. Next generation sequencing (NGS) is not only complex but is also compute and data intensive. It requires efficient handling of high performance computing infrastructure, managing scalability, flexibility and capability to handle massive amounts of genome reference data while managing intermediate results and inter-dependency between several serial and parallel analysis processes.

GenPipes is a python based bioinformatics tool comprising of several pre-built pipelines. It is available for public use as open source software. GenPipes was developed at the Canadian Centre for Computational Genomics (C3G). It offers a wide array of genomic sequencing pipelines including RNA-Seq, ChIP-Seq, Whole Genome Sequencing (WGS), Exome sequencing, Bisulfite sequencing, Hi-C, capture Hi-C, metagenomics and long read PacBio assembly. 

Key Differentiators
-------------------

GenPipes is different from other analysis platforms, workbenches and workflow management systems (WMS) in terms of the following capabilities:

1. **Flexibility:** Easy to modify and configure, multiple type of deployments available – local (containerized), cloud (GCP) and hosted on Compute Canada data centre, support for multiple job schedulers
2. **Scalability:** Optimized for large scale data analysis, simple to scale up or down in terms of processing and data access needs.
3. **Built-in Pipelines:** Pre-built, tested on multiple computing infrastructures, robust industry standard benchmark driven and production quality genomic analysis pipelines for various bioinformatics analyses.

.. image:: /img/gp_components.png

Basic Concepts
--------------

GenPipes is a Python based object oriented workflow management system that comes pre-built with several genomic analysis pipelines. A  typical analysis workflow comprises of several complex actions that are interdependent and need to be managed in terms of input, output, process configuration and pipeline tuning.  

GenPipes refer to four kinds of objects that are used to manage different components of a typical analysis workflow. These are:

- Pipeline
- Step
- Job
- Scheduler 

Pipeline
.........

It is the main object that controls the overall genomic analysis workflow. For each type of analysis, a specific Pipeline object is defined. Pipeline objects can inherit from one another. 

Step
....

Each Pipeline object uses Step objects to define the flow of the analysis. It provides flexibility in choosing which steps are called during a pipeline execution. Pipeline instance calls all steps implemented in a pipeline or only a set of steps selected by the user. Each step of a pipeline is a unit of execution block that encapsulates a part of the analysis (e.g., trimming or alignment). The Step object is a central unit object that corresponds to a specific analysis task. The execution of the task is directly managed by the code defined in each Step instance; some steps may execute their task on each sample individually while other steps execute their task using all the samples collectively. 

Job
....

The key purpose of each Step object is to generate a list of “Job” objects, which correspond to the consecutive execution of single tasks. The Job object defines the commands that will be submitted to the system. It contains all the elements needed to execute the commands, such as input files, modules to be loaded, as well as job dependencies and temporary files. Jobs are submitted in a workflow management system which uses various algorithms to schedule various types of jobs and optimizes time to result and resource usage.

Scheduler
.........

Each Job object is submitted to the GenPipes workflow management system using a specific “Scheduler” object. The Scheduler object creates execution commands that are compatible with the user's computing system. Four different Scheduler objects have already been implemented (PBS, SLURM, Batch, and Daemon)

