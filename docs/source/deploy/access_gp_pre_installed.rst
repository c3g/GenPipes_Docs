.. _docs_access_gp_pre_installed:


.. spelling:word-list::

         abc
         123
         01
         puTTY
         Ctrl
         cvmfs
         CentOS
         DRAC

DRAC Deployment
===============

In this guide you will learn how to access GenPipes deployed on the servers hosted by the `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_, *formerly Compute Canada (CCDB)*. Once you have access to these servers you can begin using GenPipes for genomic analysis.


.. _get_ccdb_account:

.. contents:: :local:

Once you have access to these servers you can begin using GenPipes for genomic analysis.

1. Register for DRAC Account
-----------------------------

a. Go to the DRAC website. Click `Register <https://ccdb.alliancecan.ca/security/login>`_ to initiate a new account.

b. Agree with the policy and submit your acceptance. 

c. Fill in the required fields of the form and submit it.

.. admonition:: Students / Post-Doc / Other Sponsored Users
   :class: note

   * To be eligible for accessing the resources offered by the DRAC, the Principle Investigator (PI) of your laboratory must also have an account. 
   
   * You will need to provide the *Compute Canada Role Identifier (CCRI)* of your sponsor or PI. The CCRI value is of the form: ``abc-123-01``. 
  
   * Canadian academics have free access to the DRAC resources. 
   
   **It may take a couple of days to process your account registration request.**

.. admonition:: DRAC Account
   :class: warning

   The latest DRAC server access requires multi-factor authentication (MFA). Also, once your account is enabled, you may be required to request access to specific servers that deploy GenPipes.

   Visit https://ccdb.alliancecan.ca/me/access_systems for details.

   * Verify that your access is enabled (green check mark) for each HPC and cloud system you plan to use.
   * Verify that your access is disabled for each HPC and cloud system you don’t plan to use.

   For questions and concerns about the DRAC servers, please email support@tech.alliancecan.ca to reach the alliance tech support.

2. Connect to DRAC Servers
---------------------------

.. tabs::

   .. tab:: Unix / Linux / Mac or Windows (bash)


      a. Open a bash shell or terminal on your local system and type the following command:

      .. parsed-literal:: 

          ssh myaccount@\ |key_ccdb_server_cmd_name|\.alliancecan.ca


      b. Enter your DRAC account password. Follow the latest instructions on using MFA for DRAC server access. See https://ccdb.alliancecan.ca/me/access_systems for details.

   .. tab:: Windows (PuTTY)

      a. Open puTTY.

      b. Select **"Session"** on the left hand side panel

      c. Select **"SSH"** and fill the *"Host Name"* entry with the following:

      .. parsed-literal::

          \ |key_ccdb_server_cmd_name|\.alliancecan.ca

      d. Click **"Open"**

         A terminal will open and ask you to connect using your CC account credentials. Follow the latest instructions on using MFA for DRAC server access. See https://ccdb.alliancecan.ca/me/access_systems for details.

.. admonition:: DRAC Server Name
   :class: note
          
   Replace the server name, \ |key_ccdb_server_cmd_name|\, in the command above with the one you are connected to. 

.. admonition:: DRAC server |key_ccdb_server_cmd_name|
   :class: note
          
   Replace the server name, \ |key_ccdb_server_cmd_name|\, in the command above with the desired cluster name. 

*Voila!!!*

Once connected to the DRAC server, you are all set to use GenPipes.

.. admonition:: Available Software at DRAC
   :class: hint

         Canadian Centre for Computational Genomics (C3G), in partnership with DRAC, offers and maintains a large set of bioinformatics resources for the community. 
         
         For a complete list of software currently deployed DRAC servers (\ |key_ccdb_server_name|, \ |other_ccdb_server_names|\) see `Bioinformatics Resources <https://computationalgenomics.ca/cvmfs-genome/>`_ and `Available Software <https://docs.alliancecan.ca/wiki/Available_software>`_. 
         
         You can refer to several `reference genomes <https://github.com/c3g/GenPipes/tree/main/resources/genomes/>`_ as well. Make sure you have the environment setup.

.. _setting_up_gp_environment_modules:

3. GenPipes Environment Setup 
-----------------------------

.. tabs::
   
   .. tab:: Abacus, DRAC Users 

      The required software modules and scripts used by GenPipes are pre-deployed on DRAC servers (\ |key_ccdb_server_name|, |other_ccdb_server_names|\). 
      
      To access them, add the tool path to your ``.bash_profile``. 
      
      .. dropdown:: What is `.bash_profile`?
         
         The ``.bash_profile`` is a hidden file in your home directory that sets up your environment every time you log in. You can also use your ``.bashrc`` file.

         For more information on the differences between the ``.bash_profile`` and the ``.bashrc profile``, consult `this page <http://www.joshstaiger.org/archives/2005/07/bash_profile_vs.html>`_.

      Genomes and modules used by the pipelines are pre-installed on a CVMFS partition mounted on all the DRAC server clusters in the path ``/cvmfs/soft.mugqic/CentOS6``.

      .. code::

         ## open bash_profile
         nano $HOME/.bash_profile

      Next, you need to load the `software modules <https://docs.python.org/3/tutorial/modules.html>`_ in your shell environment. These are required to run GenPipes. Paste the following lines of code into the ``.bash_profile``, save it, then exit (Ctrl-X). Start a new shell to source these environment variables:

      .. code:: 


         umask 0006
          
         ## GenPipes/MUGQIC genomes and modules
         export MUGQIC_INSTALL_HOME=/cvmfs/soft.mugqic/CentOS6
         module use $MUGQIC_INSTALL_HOME/modulefiles
         module load mugqic/genpipes/<latest_version>
         export JOB_MAIL=<my.name@my.email.ca>
         export RAP_ID=<my-rap-id>

      The full list of modules available on the DRAC servers can be accessed via the :ref:`module page<doc_cvmfs_modules>`.

      .. admonition:: JOB_MAIL and RAP_ID
         :class: note
         
         Replace the text in "<>" with your DRAC account specific information.

         **JOB_MAIL** is the environment variable that needs to be set to the email ID on which GenPipes job status notifications are sent corresponding to each job initiated by your account. It is advised that you create a separate email for jobs since you can receive hundreds of emails per pipeline. You can also de-activate the email sending option by removing the “-M $JOB_MAIL” option from the .ini files.

         **RAP_ID** is the Resource Allocation Project ID from DRAC. It is usually in the format: rrg-lab-xy OR def-lab.

   .. tab:: MUGQIC Analysts

      For MUGQIC analysts, add the following lines to your $HOME/.bash_profile:

      .. parsed-literal::

          umask 0006
            
          ## MUGQIC genomes and modules for MUGQIC analysts
          
          HOST=`hostname`;
          
          DNSDOMAIN=`dnsdomainname`;
          
          export MUGQIC_INSTALL_HOME=/cvmfs/soft.mugqic/CentOS6
          
          if [[ $HOST == abacus* || $DNSDOMAIN == ferrier.genome.mcgill.ca ]]; then
          
            export MUGQIC_INSTALL_HOME_DEV=/lb/project/mugqic/analyste_dev
          
          elif [[ $HOST == ip* || $DNSDOMAIN == m  ]]; then
          
            export MUGQIC_INSTALL_HOME_DEV=/project/6007512/C3G/analyste_dev
          
          elif [[ $HOST == fir* || $DNSDOMAIN == fir.alliancecan.ca ]]; then
          
            export MUGQIC_INSTALL_HOME_DEV=/project/6007512/C3G/analyste_dev
          
          
          elif [[ $HOST == \ |key_ccdb_server_cmd_name|\* || $DNSDOMAIN == \ |key_ccdb_server_cmd_name|\.alliancecan.ca ]]; then
          
            export MUGQIC_INSTALL_HOME_DEV=/project/6007512/C3G/analyste_dev
          
          fi

          module use $MUGQIC_INSTALL_HOME/modulefiles $MUGQIC_INSTALL_HOME_DEV/modulefiles
          module load mugqic/genpipes/<latest_version>
        
            export RAP_ID=<my-rap-id>

          Also, set JOB_MAIL in your $HOME/.bash_profile to receive PBS/SLURM job logs:

      .. code::

         export JOB_MAIL=<my.name@my.email.ca>

.. admonition:: Python Version
    :class: warning

    GenPipes 5.x release onward has been verified for Python version 3.11.1 or higher. It no longer supports Python 2.7 version. 

Verify Version
+++++++++++++++

Run the following command to verify the available GenPipes version: 

.. code::

    module avail 2>&1 | grep mugqic/genpipes

.. dropdown:: What is `mugqic`?

    Previous version of GenPipes were named `mugqic_pipelines` and are still available for use.

Verify Environment
+++++++++++++++++++

You must ensure that your ``.bash_profile`` changes have taken effect before running ``genpipes`` command.

When you make changes to your ``.bash_profile`` file, you will need to log out and then login again for these changes to take effect. Alternatively, you can run the following command in bash shell:

.. code::

   source $HOME/.bash_profile

Check your access to the bioinformatics tools pre-installed for GenPipes usage with the command:

.. code::

   module avail mugqic/

Check Tools Availability
+++++++++++++++++++++++++

Check Tools Availability
+++++++++++++++++++++++++

To load a tool available on DRAC servers, for example - samtools, use the following command:

:: 

  # module add mugqic/<tool><version>
  module add mugqic/samtools/1.4.1

  # Now samtools 1.4.1 is available for use in your account environment. To check, run the following command:
  samtools

Several of the GenPipes pipelines may reference genomes. Check whether you can access these pre-installed genomes available:

::

  ls $MUGQIC_INSTALL_HOME/genomes/species

All genome-related files, including indices for different aligners and annotation files can be found in:

::

  $MUGQIC_INSTALL_HOME/genomes/species/<species_scientific_name>.<assembly>/
  ## so for Homo Sapiens hg19 assembly, that would be:
  ls $MUGQIC_INSTALL_HOME/genomes/species/Homo_sapiens.hg19/

For a complete list of all available reference genomes, visit `genome page <https://computationalgenomics.ca/cvmfs-genome/>`_.

4. Run ``genpipes`` Command
-----------------------------

That's all. You are now set up to run GenPipes pipelines for genomic analysis. 

For example runs, refer to instructions in :ref:`Using GenPipes<docs_using_gp>` section. Each pipelines supported by GenPipes requires a different command syntax.  See GenPipes :ref:`User Guide: Pipelines Reference<docs_user_guide>`  section for details.
