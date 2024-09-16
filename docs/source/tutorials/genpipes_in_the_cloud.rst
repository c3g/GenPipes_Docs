.. _genpipes_in_the_cloud:

Running GenPipes on Google Cloud Platform (GCP)
===============================================
Quickstart
----------

The Quickstart uses a **“Try GCP for free”** session.
If you already have basic knowledge of GCP, and its shell, you can jump directly to step 4.

1. Create an account on GCP. For more instructions, check out `this page <https://console.cloud.google.com/>`__.
2. Get acquainted with Google Cloud Shell. For more instructions, check out `this page <https://cloud.google.com/shell/docs/quickstart>`__.
3. Create a new project. For more instructions, check out `this page <https://cloud.google.com/resource-manager/docs/creating-managing-projects>`__.
4. Install GenPipes, as follows:

In your google shell session, run:

.. code-block:: bash

    git clone https://bitbucket.org/mugqic/cloud_deplyoment.git
    cd cloud_deplyoment/gcp/
    gcloud deployment-manager deployments create slurm --config slurm-cluster.yaml

From here on, your GenPipes cloud is being deployed and your account is getting billed by Google.
Remember to shut down the cluster when the analysis is done.
Once this command is done running, a configuration script is started to install SLURM on the cluster. You will be able to monitor the installation after you run the next command.

Run one of the GenPipes test sets on GCP:
-----------------------------------------
In the Google shell run the following command to log into the login node of the Slurm cluster:

.. code-block:: bash

    gcloud compute ssh login1 --zone=northamerica-northeast1-a


You are now on your cloud deployment login node.

The installation is still running and you where welcome by the following message:

.. note::

    ** Slurm is currently being installed/configured in the background. **
    A terminal broadcast will announce when installation and configuration is
    complete.

Wait for the terminal broadcast this can take up to 10 minutes. Once you have received it or one you log to this node
without seeing the warning, you can go to the next step. You can run the GenPipes :ref:`tutorial <doc_genpipes_tutorial>` from
that location.

Let’s use ChIPSeq as an example:

**1- Make a folder for the test:**

.. code-block:: bash

    mkdir -p chipseq_test
    cd chipseq_test

**2- Download dataset and unzip it:**

.. code-block:: bash

    wget https://datahub-90-cw3.p.genap.ca/chipseq.chr19.new.tar.gz
    gzip -d chipseq.chr19.new.tar.gz


**3- Download the config file for this Quickstart:**

.. code-block:: bash

    wget https://bitbucket.org/mugqic/cloud_deplyoment/raw/master/quick_start.ini


**4- Create chipseq pipeline script:**

.. code-block:: bash

    bash # You do not need this line if you did a logout login cycle
    # The next line generates the pipeline script
    genpipes chipseq -c $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini \
    $MUGQIC_PIPELINES_HOME/pipelines/common_ini/cedar.ini \
    quick_start.ini \
    -j slurm \
    -r readsets.chipseqTest.chr22.tsv \
    -d designfile_chipseq.chr22.txt \
    -s 1-18 > chipseqScript.sh

**5- Run chipseq pipeline:**

.. code-block:: bash

    bash chipseqScript.sh

**6- Look at your pipeline progression: .**
Use squeue command. Your GenPipes analysis is `being run on Slurm <https://slurm.schedmd.com/>`_

**7- Shut down your Genpipes Cloud installation (and stop being billed): .**
After the jobs have run, you can exit the login node:

.. code-block:: bash

    exit

You, are now in back on your cloud shell administrative machine. You can shut down your GenPipes cloud cluster.

.. code-block:: bash

    gcloud deployment-manager deployments delete slurm

You are not being billed anymore.

.. note::

    You need to enable the “deployment manager” API on your project. See `this page <https://support.google.com/cloud/answer/6158841?hl=en>`__.
    You also need to make sure that billing is enabled (even for a free try).
    For more detailed information, check out our `bitbucket repo <https://bitbucket.org/mugqic/cloud_deplyoment/src/master/gcp/>`_
