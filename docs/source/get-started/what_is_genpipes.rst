.. _docs_what_is_genpipes:
  
Introducing GenPipes
=====================

GenPipes is a workflow management system (WMS) that facilitates building robust genomic workflows. It is a unique solution that combines both a framework for development and end-to-end analysis pipelines, covering a large scope of genomic applications and research domains. It offers researchers a simple method to analyze different types of data, customizable to their needs and resources. In addition, it provides flexibility to create customized workflows besides the ones that are already implemented and validated by GenPipes.

What is GenPipes?
-----------------

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

Each Job object is submitted to the GenPipes workflow management system using a specific “Scheduler” object. The Scheduler object creates execution commands that are compatible with the user's computing system. Four different Scheduler objects have already been implemented (PBS, SLURM, Batch, and Daemon).

How GenPipes works?
--------------------

GenPipes is a Python based object-oriented framework that is available to users as a command line tool. Figure below shows the general workflow of GenPipes. 

.. image:: /img/gp_working.png

When the GenPipes command is launched, required modules and files will be searched for and validated. If all required modules and files are found, the analysis commands will be produced. GenPipes will create a directed acyclic graph that defines job dependency based on input and output of each step.

Once launched, the jobs are sent to the scheduler and queued. As jobs complete successfully, their dependent jobs are released by the scheduler to run. If a job fails, all its dependent jobs are terminated and an email notification is sent to the user. When GenPipes is re-run, it will detect which steps have successfully completed, as described in section “Smart relaunch features,” and skip them but will create the command script for the jobs that were not completed successfully. To force the entire command generation, despite successful completion, the “-f” option should be added.  

For details on GenPipes usage and various bioinformatics pipelines see :ref:`GenPipes User Guide<docs_user_guide>`.
