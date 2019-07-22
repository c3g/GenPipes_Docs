:orphan:

.. _docs_pre_req_chklist:

Checklist of Pre-requisites for Running GenPipes
------------------------------------------------

* :ref:`Get a Compute Canada account<docs_access_gp_pre_installed>` if not deploying GenPipes locally or in the cloud

* Hardware requirement (for local installation and setup)

* Software requirement

  - Python 2.7
  - Modules that are required
  - Genomes that need to be referenced

* Check that GenPipes is deployed

  - For Compute Canada data centre users:

::
 
  <pipeline_name>.py --help

  - For local installation 

::
  
  $MUGQIC_PIPELINES_HOME/pipelines/<pipeline_name>/<pipeline_name>.py --help

* Ensure CVMFS is mounted (??? Is this valid for non container too?)

* Verify if input file(s) can be accessed
 
  - ini or configuration files
  - Readset file
  - Design file

* Other items in GenPipes checklist that must be addressed before pipeline can be run for genomic analysis 
