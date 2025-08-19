.. _docs_dep_gp_cloud:


.. spelling:word-list::

   slurm
   yaml

Cloud Deployment
=================

This document describes how to deploy GenPipes in the cloud. Following are the supported cloud providers where you can deploy and run GenPipes:

.. contents:: :local:

----

For more details on non-cloud deployment options for GenPipes you may refer to :ref:`GenPipes Deployment Options Page<docs_dep_options>`.


GenPipes on Google Cloud Platform (GCP)
---------------------------------------
This section describes how to deploy and run GenPipes using GCP infrastructure.

.. image:: /img/gp_on_gcp_cloud.png
    :scale: 50%

**Pre-requisites for deploying GenPipes on GCP**

If you are a seasoned GCP user and familiar with Google Cloud shell, you can skip this step.  For first time GCP users – you may want to try GCP free tier for GenPipes deployment. Follow these steps to create and access GCP account:

- Create an account on GCP. For more instructions, `check out GCP console page <https://console.cloud.google.com/>`_.

- Get acquainted with Google Cloud Shell. For more instructions, `check out this page <https://cloud.google.com/shell/docs/quickstart>`_.

- Create a new project. For detailed instructions `see here <https://cloud.google.com/resource-manager/docs/creating-managing-projects>`_.

.. note::
      1. Enable Deployment Manager API for your project. For further details, `visit this page <https://support.google.com/cloud/answer/6158841?hl=en>`_.

      2. You also need to make sure that billing is enabled (even for a GCP free try option).

**Install GenPipes**

To install GenPipes on GCP, use Google Cloud Shell Session and download the following install scripts:

::

  git clone https://bitbucket.org/mugqic/cloud_deplyoment.git

GenPipes requires `Slurm <https://slurm.schedmd.com/>`_ for scheduling genomic analysis jobs on GCP compute servers. To setup Slurm on your GCP compute infrastructure, run the following commands in your Google Cloud Shell:

::
 
  cd cloud_deplyoment/gcp/
  gcloud deployment-manager deployments create slurm --config slurm-cluster.yaml

Once this command is done running, a configuration script is started to install SLURM on the cluster. It will take some time to complete the setup. You will be able to monitor the status of installation once you run the next command. The Cluster configuration is specified in slurm-cluster.yaml file. You can view it to see the controller and worker node setup. By default, only a single node is used for this GCP GenPipes deployment. See node_count value in slurm-cluster.yaml file.

.. warning::
   From here on, your GenPipes cloud is being deployed and your account is getting billed by Google.
   *Remember to shut down the cluster when the analysis is done.*

**Access GenPipes Slurm Cluster on GCP**

Use the following command to log into the login node of your GCP Slurm cluster:

::

  gcloud compute ssh login1 --zone=northamerica-northeast1-a

After running the command mentioned above, you are now on GenPipes cloud deployment login node.

**Monitoring GenPipes deployment in GCP**

The installation is still running and once you log into the login node of your GCP Slurm cluster, you will see the following welcome message:

::

  *** Slurm is currently being installed/configured in the background. ***
  A terminal broadcast will announce when installation and configuration is complete.

.. note::

   Wait for the terminal broadcast. This can take up to 10 minutes. Once you have received it or when you log to the GCP Slurm Cluster login node and there is no warning message displayed as you login, you can go to the next step. 

**Validate GenPipes on GCP cloud runtime environment**

Now that your GCP Slurm Cluster is up and running without any error or warning, you can launch any GenPipes pipeline using the command:

::

  genpipes <pipeline_name> –help

For example, to check the help information for GenPipes ChIP Sequencing pipelines, try:

::

  genpipes chipseq -h

**GenPipes Test Run in the cloud**

To run ChIP Sequencing pipeline using test dataset, use the login node on your GCP Slurm Cluster and issue the following commands in Google Cloud shell corresponding to each step below:

Step 1: Create a new test directory

::

  mkdir -p chipseq_test
  cd chipseq_test

Step 2: Download test dataset and unzip it as shown below:

::

  wget https://datahub-90-cw3.p.genap.ca/chipseq.chr19.new.tar.gz
  gzip -d chipsseq.chr19.new.tar.gz

Step 3: GenPipes ChIP Sequencing pipeline needs a configuration file to setup the parameters required by this pipeline. You can download it using the command:

::

  wget https://bitbucket.org/mugqic/cloud_deplyoment/raw/master/quick_start.ini

Step 4: Create ChIP Sequencing pipeline execution command script as shown below:

.. parsed-literal::

    bash # You do not need this line if you did a logout login cycle
    # The next line generates the pipeline script
    genpipes chipseq -c $GENPIPES_INIS/chipseq/chipseq.base.ini \
    $GNEPIPES_INIS/common_ini/chipseq.\ |key_ccdb_server_cmd_name|\.ini \
    quick_start.ini \
    -j slurm \
    -r readsets.chipseqTest.chr22.tsv \
    -d designfile_chipseq.chr22.txt \
    -s 1-18 > chipseqScript.sh

Step 5:  Now you can execute ChIP Sequencing pipeline using the following command:

::

  bash chipseqScript.sh

Step 6: View Progress of your pipeline and jobs by using squeue command. For more `Slurm commands <https://slurm.schedmd.com/quickstart.html>`_ and details on monitoring Slurm cluster, you can see `Slurm documentation <https://slurm.schedmd.com/>`_

There are several ways to check the status of your jobs in the queue.  Below are a few SLURM commands to make use of.  Use the Linux 'man' command to find loads of additional information about these commands as well.

::

  squeue <options>

where you can use the following options:

::

  -u username
  -j jobid
  -p partition
  -q qos

For example:

::

  [shalz@ubuntu_srv:/$ squeue -u shaloo
  JOBID PARTITION  NAME     	USER     ST       TIME  NODES NODELIST(REASON)
  92311  debug     test     	shaloo   R        0:06      2 e06ne9s0e,c17n09
  88915  xyz	   GPU_test     shaloo   PD       0:00      1 (Priority)
  91716  xyz       hell_te      shaloo   R        0:08      2 d19res0e,d16n08 
  91791  xyz 	   hello_te     shaloo   PD       0:00      2 (Priority)
  91792  xyz       hello_te     shaloo   PD       0:00      2 (Priority)

Step 7: Shutdown GCP compute resources (Very Important!!!)
You need to make sure that after your jobs are run, you need to shutdown your GenPipes Slurm Cluster on GCP otherwise you will continue to be billed for the same.  After all your jobs have run, use the following command to exit out of your login node Google Cloud shell session:

::

  exit

This command closes the Slurm Login node shell. You are now back on your cloud shell administrative server. You can shut down your GenPipes cloud cluster by running the following script:

::

  gcloud deployment-manager deployments delete slurm

**Further information**

If you run into any issues, please refer to :ref:`Troubleshooting runtime issues<docs_troubleshooting_rt_issues>` section of this documentation and visit :ref:`GenPipes Support<docs_how_to_get_support>` page.

For advanced GCP cloud setup scenarios and for the latest updates on deploying GenPipes in the cloud, details regarding Slurm stand alone cluster setup, or multi-cluster federation setup or to burst out of on-premise cluster to GCP while running GenPipes, refer to the `README.md file <https://bitbucket.org/mugqic/cloud_deplyoment/src/master/gcp/README.md>`_.
