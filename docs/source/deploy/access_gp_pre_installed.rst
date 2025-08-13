.. _docs_access_gp_pre_installed:


.. spelling:word-list::

         abc
         123
         01
         puTTY
         Ctrl
         cvmfs
         CentOS

DRAC Deployment
===============

This document explains how you can access GenPipes deployed on `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_, formerly Compute Canada, servers and start using it for genomic analysis.

.. _get_ccdb_account:

Step 1: Get a DRAC Data Base (CCDB) account
---------------------------------------------

a. Go to the website: `https://ccdb.alliancecan.ca/account_application <https://ccdb.alliancecan.ca/account_application>`_

b. Agree with the policy and submit your acceptance 

c. Fill the form and submit it.

.. note::

        If you are a student or a post-doc (or any other kind of Sponsored User), to be eligible to apply to `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_, formerly Compute Canada, the Principle Investigator (PI) of your laboratory must also have an account. You will need the Compute Canada Role Identifier (CCRI) of your sponsor/PI. The CCRI has the abc-123-01 form. It is free for Canadian academics to use the DRAC servers.

        **It will take one or two days before your account request is processed.**

Step 2: Connect to DRAC servers
--------------------------------

**Unix / Linux / Mac or Windows (bash)**

a. Open a shell or terminal (bash preferably) and type the following command:

.. parsed-literal:: 

     ssh myaccount@\ |key_ccdb_server_cmd_name|\.alliancecan.ca

.. tip::
     
       Replace the server name |key_ccdb_server_cmd_name| in the command above with the desired cluster name. 

b. Enter your `Digital Research Alliance of Canada <https://alliancecan.ca/en>`_, formerly Compute Canada, account password.

**Windows (PuTTY)**

a. Open puTTY.

b. Select **"Session"** on the left hand side panel

c. Select **"SSH"** and fill the *"Host Name"* entry with the following:

.. parsed-literal::

    \ |key_ccdb_server_cmd_name|\.alliancecan.ca

.. tip::
     
       Replace the server name |key_ccdb_server_cmd_name| in the command above with the desired cluster name. 

d. Click **"Open"**

A terminal will open and ask you to connect using your CC account credentials.

Voila!!!

You are all set to use GenPipes deployed on the `Digital Research Alliance of Canada <https://alliancecan.ca/en>`_, formerly Compute Canada, data centre.

.. note::

         Canadian Centre for Computational Genomics (C3G), in partnership with `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_, formerly Compute Canada, offers and maintains a large set of bioinformatics resources for the community. For a complete list of software currently deployed on several HPC centres, including |key_ccdb_server_name|, |other_ccdb_server_names| , refer to `Bioinformatics Resources <https://computationalgenomics.ca/cvmfs-genome/>`_ and `available software <https://docs.alliancecan.ca/wiki/Available_software>`_. Several reference genomes are also available. You can refer to the `available genomes <https://github.com/c3g/GenPipes/tree/main/resources/genomes/>`_ and the environment setup to access these genomes.


.. _setting_up_gp_environment_modules:

Step 3: Setting up your user environment for GenPipes access
------------------------------------------------------------

**For Abacus, DRAC Users only**

All of the software and scripts used by GenPipes are already installed on several DRAC servers including |key_ccdb_server_name|, |other_ccdb_server_names|. To access the tools, you will need to add the tool path to your bash_profile. The bash profile is a hidden file in your home directory that sets up your environment every time you log in. You can also use your bashrc file.

Genomes and modules used by the pipelines are already installed on a CVMFS partition mounted on all those clusters in /cvmfs/soft.mugqic/CentOS6

.. note::

        For more information on the differences between the .bash_profile and the .bashrc profile, consult `this page <http://www.joshstaiger.org/archives/2005/07/bash_profile_vs.html>`_.

::

   ## open bash_profile
   nano $HOME/.bash_profile

.. note::

      GenPipes 5.x release onward has been verified for Python version 3.11.1 or higher. It no longer supports Python 2.7 version. 

Next, you need to load the `software modules <https://docs.python.org/3/tutorial/modules.html>`_ in your shell environment that are required to run GenPipes. You can refer to the full list of modules available on the `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_, formerly Compute Canada, servers at the :ref:`module page<doc_cvmfs_modules>`.

To load the GenPipes modules, paste the following lines of code and save the file, then exit (Ctrl-X):

:: 

   umask 0006
   
   ## GenPipes/MUGQIC genomes and modules
   export MUGQIC_INSTALL_HOME=/cvmfs/soft.mugqic/CentOS6
   module use $MUGQIC_INSTALL_HOME/modulefiles
   module load mugqic/genpipes/<latest_version>
   export JOB_MAIL=<my.name@my.email.ca>
   export RAP_ID=<my-rap-id>

You will need to replace the text in "<>" with your account and GenPipes software version specific information.

**JOB_MAIL** is the environment variable that needs to be set to the email ID on which GenPipes job status notifications are sent corresponding to each job initiated by your account. It is advised that you create a separate email for jobs since you can receive hundreds of emails per pipeline. You can also de-activate the email sending option by removing the “-M $JOB_MAIL” option from the .ini files.

**RAP_ID** is the Resource Allocation Project ID from DRAC. It is usually in the format: rrg-lab-xy OR def-lab.

**Environment settings for MUGQIC analysts**

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

::

  export JOB_MAIL=<my.name@my.email.ca>

**How to check the version of GenPipes deployed**

To find out the latest GenPipes version available, once you have connected to your CC account, use the following command:

::

  module avail 2>&1 | grep mugqic/genpipes

.. note::

       Previous version of GenPipes were named mugqic_pipelines and are still available for use.

**How to ensure bash_profile changes take effect in the environment variables?**

When you make changes to your bash_profile, you will need to log out and then login again for these changes to take effect. Alternatively, you can run the following command in bash shell:

::

  source $HOME/.bash_profile

By adding the lines related to module load and environment variable setting via export, you have set up the pipeline environment and are ready to use GenPipes!

This also gives you access to hundreds of bioinformatics tools pre-installed by our team. To explore the available tools, you can type the following command:

::

  module avail mugqic/

For a full list of all available software on DRAC servers, visit `module page <https://docs.alliancecan.ca/wiki/Available_software>`_.

To load a tool available on DRAC servers, for example - samtools, use the following command:

:: 

  # module add mugqic/<tool><version>
  module add mugqic/samtools/1.4.1

  # Now samtools 1.4.1 is available for use in your account environment. To check, run the following command:
  samtools

Several of the GenPipes pipelines may require referencing genomes. To access these pre-installed genomes available in:

::

  $MUGQIC_INSTALL_HOME/genomes/species/

use the following command to check all available genome species:

::

  ls $MUGQIC_INSTALL_HOME/genomes/species

All genome-related files, including indices for different aligners and annotation files can be found in:

::

  $MUGQIC_INSTALL_HOME/genomes/species/<species_scientific_name>.<assembly>/
  ## so for Homo Sapiens hg19 assembly, that would be:
  ls $MUGQIC_INSTALL_HOME/genomes/species/Homo_sapiens.hg19/

For a complete list of all available reference genomes, visit `genome page <https://computationalgenomics.ca/cvmfs-genome/>`_.

Step 4: Running GenPipes pipelines
----------------------------------
Now you are all set to run GenPipes analysis pipelines. Refer to instructions in :ref:`Using GenPipes for genomic analysis<docs_using_gp>` for example runs.  For specific pipelines supported by GenPipes, their command options refer to GenPipes :ref:`User Guide<docs_user_guide>`.
