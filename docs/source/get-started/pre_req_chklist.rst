:orphan:

.. _docs_pre_req_chklist:

Before Running GenPipes
-----------------------

We highly recommend that new users go through these checklists and address all the pre-requisites for running GenPipes successfully.

1. Check Environment & Setup
=============================

Ensure you have the GenPipes runtime environment setup appropriately.  It may vary depending upon your GenPipes deployment type. For details on various deployment type options, see :ref:`docs_dep_options`.  The instructions below list key checklist items for various deployment types.

Compute Canada Deployment
+++++++++++++++++++++++++

:ref:`Get a Compute Canada account<docs_access_gp_pre_installed>` if not deploying GenPipes locally or in the cloud. You can use GenPipes deployed by C3G on CC datacenter servers.  Once you have the account, make sure you have your software environment setup for requisite GenPipes modules. 

For details see :ref:`setting_up_gp_environment_modules` section in the :ref:`docs_access_gp_pre_installed` documentation.

Local Deployment
++++++++++++++++

For using GenPipes deployed locally on your servers, whether bare-metal or virtual servers, or in a container, ensure that the sufficient compute resources are available:

**Hardware requirements** 

- CPU
- Cores
- Memory
- Disk speed / SSD capacity

**Software requirements**

- Python  3.11.1
- :ref:`Modules that are required<accessing_sw_mod_genomes_local_dp>`
- :ref:`Genomes that need to be referenced<ref_installing_genomes>`

----

.. _software dependencies:

.. figure:: /img/sw-modules-dep.png
   :align: center
   :alt:  Software Modules required for running GenPipes

   Figure: Software Modules required for running GenPipes 

----

2. Validate Deployment
=======================

Ensure that you can test run one of the GenPipes Pipeline.  Simply issue the help option instead of running any jobs.  This will confirm whether GenPipes can actually run and environment setup in terms of python modules is taken care of.

* Check that GenPipes is deployed

  - For Compute Canada data centre users:

        *genpipes <pipeline_name> --help*

* Ensure CVMFS is mounted

3. Check Input Files 
=====================

Verify if the required input file(s) for the pipeline run can be accessed:
 
  - ini or configuration files
  - Readset file
  - Design file