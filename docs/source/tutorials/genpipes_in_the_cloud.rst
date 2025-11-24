.. _genpipes_in_the_cloud:

Tutorial: GenPipes in the Cloud (GCP)
=====================================

.. include:: /common/test_datasets.txt

.. dropdown:: :material-outlined:`bolt;2em` Usage Change Effective v5.x onward
   :color: success

    .. include:: /gp5_0.inc

.. include:: /common/new_wizard_dropdown.txt  

.. admonition:: v6.x Support for Cloud
    :class: danger

    We have not yet verified / released GenPipes support for GCP / Cloud in version 6.x release. The following tutorial works for GenPipes v5.x only.

GenPipes bioinformatics :ref:`pipelines<docs_available_pipelines>` are developed as part of the GenAP project at the Canadian Centre for Computational Genomics (C3G).

This tutorial shows you how to run GenPipes in Google Cloud (GCP). It uses the **“Try GCP for free”** account to run a pipeline in the cloud.

.. contents:: 
    :local:
    :depth: 2
 
----

Prerequisites
-------------

#. Create an account on GCP. `Learn more... <https://console.cloud.google.com/>`__.
#. Get acquainted with using the Google Cloud Shell. `Learn more... <https://cloud.google.com/shell/docs/quickstart>`__.
#. Create a new project. `Learn how to create a cloud project... <https://cloud.google.com/resource-manager/docs/creating-managing-projects>`__.

:bdg-primary:`Step 1:` Deploy GenPipes in GCP cloud
----------------------------------------------------

Set up GenPipes in your cloud server instance. Run in the Google shell:

.. code-block:: bash

    user@machine:~$ git clone https://bitbucket.org/mugqic/cloud_deplyoment.git

    user@machine:~$ cd cloud_deplyoment/gcp/

    user@machine:~$ gcloud deployment-manager deployments create slurm --config slurm-cluster.yaml

For more details on how to set up GenPipes in the cloud, see :ref:`GenPipes Cloud Deployment Guide<docs_dep_gp_cloud>`.

.. admonition:: Cloud billing
    :class: warning
    
    Please note that from here on, your GenPipes cloud deployment is being deployed and your account is getting billed by Google. Remember to shut down the cloud server cluster when the analysis is done if you do not wish to be billed unintentionally.

:bdg-primary:`Step 2:` Verify Slurm Deployment
------------------------------------------------

Once the ``gcloud`` command is done running, a configuration script is started to install SLURM on the cluster running in the cloud. You will be able to monitor the installation after you run the next command.

Use the Google shell to log into the login node of the Slurm cluster:

.. code-block:: bash

    user@machine:~$ gcloud compute ssh login1 --zone=northamerica-northeast1-a

You are now on your cloud deployment login node.

The installation may still be running. Once it is done, you will see a welcome 
message:

.. code-block:: bash

    Slurm is currently being installed/configured in the background.

    A terminal broadcast will announce when installation and configuration is
    complete.

Wait for the terminal broadcast. It can take up to 10 minutes. 


:bdg-primary:`Step 3:` Run GenPipes Pipeline
-----------------------------------------------

In this tutorial, we will run the ``chipseq`` pipeline in the cloud.

First, create a test folder as shown below:

.. code-block:: bash

    user@machine:~$ mkdir -p chipseq_test
    user@machine:~$ cd chipseq_test

Then, download the `Chip Sequencing Test Dataset`_ and unzip it:

.. parsed-literal::

    user@machine:~$ wget  \ |test_dataset_download_url|\/chipseq.chr19.new.tar.gz
    user@machine:~$ gzip -d chipseq.chr19.new.tar.gz


Next, download the ``chipseq`` configuration file for use in the cloud:

.. code-block:: bash

    user@machine:~$ wget https://bitbucket.org/mugqic/cloud_deplyoment/raw/master/quick_start.ini


Then construct the ``chipseq`` pipeline launch command:

.. parsed-literal::

    user@machine:~$ genpipes chipseq -c $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini \\
                        $MUGQIC_PIPELINES_HOME/pipelines/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
                        quick_start.ini \\
                    -j slurm \\
                    -r readsets.chipseqTest.chr22.tsv \\
                    -d designfile_chipseq.chr22.txt \\
                    -s 1-18 \\
                    -g chipseqScript.sh

Finally, launch the pipeline using the command:

.. code-block:: bash

    user@machine:~$ bash chipseqScript.sh

:bdg-primary:`Step 4:` Monitor Pipeline Status
-----------------------------------------------

Use the ``squeue`` command to monitor the GenPipes analysis run through the `Slurm <https://slurm.schedmd.com/>`_ scheduler. For details on how to monitor scheduler jobs, refer to the job monitoring step in the tutorial :ref:`GenPipes on DRAC <doc_genpipes_tutorial>`.

For more details on viewing log files and generating reports, refer to the section *Monitor Job Status* in the Tutorial: :ref:`GenPipes on DRAC servers<doc_genpipes_tutorial>`.

.. note:: 
    
    Shut down your GenPipes Cloud setup once you are done to ensure you are not
    billed for unintentional cloud usage.

After the jobs have run, you can exit the login node:

.. code-block:: bash

    user@machine:~$ exit

You, are now in back on your cloud shell administrative machine. You can shut down your GenPipes cloud cluster.

.. code-block:: bash

    user@machine:~$ gcloud deployment-manager deployments delete slurm

You are not being billed anymore.

.. note::

    You need to enable the “deployment manager” API on your project. See `this page <https://support.google.com/cloud/answer/6158841?hl=en>`__.
    You also need to make sure that billing is enabled (even for a free try).
    For more detailed information, check out our `Bitbucket repo <https://bitbucket.org/mugqic/cloud_deplyoment/src/master/gcp/>`_

