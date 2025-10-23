.. _docs_quickstart_gp:

Quick Start
============

Follow these steps to get started with GenPipes. 

.. note:: 

    .. include:: /common/new_gp_wizard.txt
    
    If you are new to GenPipes, we recommend trying the GenPipes Wizard tool. It offers step by step instructions on how to select an appropriate deployment type, select a pipeline, construct the pipeline command and run genomic analysis.


* :bdg-dark-line:`Step 1: Identify prerequisites`

   Review the :ref:`GenPipes Checklist<docs_checklist>` before you run GenPipes. Make sure you have the required software, hardware, log-in accounts, and other resources required to run GenPipes.

* :bdg-dark-line:`Step 2: Understand GenPipes basics`

   Learn GenPipes basics, concepts, and functionality to apply it to your genomic analysis. Refer to the :ref:`Introduction to GenPipes<docs_what_is_genpipes>` and :ref:`Why GenPipes<docs_gp_why>` sections for details.

* :bdg-dark-line:`Step 3: Select GenPipes deployment`

   Explore :ref:`GenPipes deployment options<docs_dep_options>` and select an appropriate one applicable to your use case.
   
   * GenPipes deployed on the Digital Research Alliance of Canada,  :ref:`DRAC servers<docs_access_gp_pre_installed>`, formerly Compute Canada, `CCDB servers <https://alliancecan.ca/en>`_ (*This option requires log in and* `server access  <https://ccdb.alliancecan.ca/me/access_systems>`_. No local software download or deployment required.)
   * GenPipes installed locally on a :ref:`server, virtual machine<docs_dep_gp_local>`, or :ref:`container<docs_dep_gp_container>`   :bdg-info:`*`
   * :ref:`GenPipes deployed in the cloud<docs_dep_gp_cloud>`  :bdg-info:`*`

   .. admonition:: GenPipes Package for Local Deployment
      
      *Options marked* :bdg-info:`*` *require you to use one of these options for local deployment:*

      * Download the pre-built, packaged GenPipes via the `GenPipes Download Page`_
      * Get the `GenPipes Source Code`_, use the :ref:`GenPipes Developer Guide<docs_dev_guide>` and build, deploy it locally.

* :bdg-dark-line:`Step 4: Review pipeline options`

   Check out the :ref:`available pipelines<docs_available_pipelines>`, use the :ref:`Pipeline Reference<docs_pipeline_ref>` and select an appropriate protocol for genomic analysis. Try the :ref:`GenPipes Wizard <docs_gp_wizard>` tool to select a GenPipes deployment type, pipeline, and protocol, and construct the full GenPipes command to run the analysis.

* :bdg-dark-line:`Step 5: Run GenPipes`

   Once you have the pipeline command ready with required protocol options, :ref:`run GenPipes<docs_using_gp>` and :ref:`analyze the results<docs_gp_job_results>`. Check out the :ref:`GenPipes Tutorials<doc_list_tutorials>` for details.   

.. dropdown:: :material-outlined:`bolt;2em` Usage Change Effective v5.x onward
   :color: success

   .. include:: /gp5_0.inc 

.. _GenPipes Download Page: https://bitbucket.org/mugqic/genpipes/downloads/
.. _GenPipes Source Code: https://github.com/c3g/GenPipes