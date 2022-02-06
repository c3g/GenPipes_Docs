:orphan:

.. _docs_pre_req_chklist:

Checklist of Pre-requisites for Running GenPipes
------------------------------------------------

**CHK1**:  Ensure you have the GenPipes runtime environment setup appropriately.  It may vary depending upon your GenPipes deployment type. For details on various deployment type options, see :ref:`docs_dep_options`.  The instructions below list key checklist items for various deployment types.

  **For using GenPipes pre-deployed on Compute Canada servers**

    * :ref:`Get a Compute Canada account<docs_access_gp_pre_installed>` if not deploying GenPipes locally or in the cloud. You can use GenPipes deployed by C3G on CC datacenter servers.  Once you have the account, make sure you have your software environment setup for requisite GenPipes modules. For details see :ref:`setting_up_gp_environment_modules` section in the :ref:`docs_access_gp_pre_installed` documentation.

  **For using GenPipes deployed locally on your server (bare metal or virtual) or in a container**

    * Hardware requirement 
  
      To run GenPipes locally in your server - it must have at least the following resources:

      - CPU
      - Cores
      - Memory
      - Disk speed / SSD capacity

    * Software requirements

      - Python  3.9.1
      - :ref:`Modules that are required<accessing_sw_mod_genomes_local_dp>`
      - :ref:`Genomes that need to be referenced<ref_installing_genomes>`

----

.. _software dependencies:

.. figure:: /img/sw-modules-dep.png
   :align: center
   :alt:  Software Modules required for running GenPipes

   Figure: Software Modules required for running GenPipes 

----

**CHK2**: Ensure that you can test run one of the GenPipes Pipeline.  Simply issue the help option instead of running any jobs.  This will confirm whether GenPipes can actually run and environment setup in terms of python modules is taken care of.

  * Check that GenPipes is deployed

    - For Compute Canada data centre users:

         *<pipeline_name>.py --help*


    - For local installation 

         *$MUGQIC_PIPELINES_HOME/pipelines/<pipeline_name>/<pipeline_name>.py --help*

  * Ensure CVMFS is mounted (??? Is this valid for non container too?)

**CHK3**: Verify if input file(s) can be accessed
 
  - ini or configuration files
  - Readset file
  - Design file
