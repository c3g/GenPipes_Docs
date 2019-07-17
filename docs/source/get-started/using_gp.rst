.. _docs_using_gp:

.. spelling::

   userID
   
Using GenPipes for genomic analysis
====================================

.. note::

	* What is available in a typical deployment and how to access it
	* Required Software & Environment configurations
	* Inputs
	  - Generic stuff for running any supported pipeline
	  - Deployment Specific Configurations
	  - Design File
	* Pipeline specific Configurations
	* Example – Running HicSeq pipeline (or any other common one)

GenPipes framework can be used to perform various genomic analysis corresponding to the available pipelines.  GenPipes is a command line tool. The underlying object-oriented framework is developed in Python. It simplifies the development of new features and its adaptation to new systems; new workflows can be created by implementing a Pipeline object that inherits features and steps from other existing Pipeline objects. Similarly, deploying GenPipes on a new system may only require the development of the corresponding Scheduler object along with specific :ref:`configuration files<docs_config_ini_file>`. GenPipes’ command execution details have been implemented using a shared library system, which allows the modification of tasks by simply adjusting input parameters. This simplifies code maintenance and makes changes in software versions consistent across all pipelines.

Running GenPipes
-----------------

Before running GenPipes, you may want to visit the :ref:`checklist of pre-requisites for GenPipes<docs_pre_req_chklist>`.

Here is how you can launch GenPipes. Following is the generic command to run GenPipes:

.. code-block:: bash

   <pipeline-name>.py -c config -r readset-file -s 1-n > list-of-commands.txt
   bash list-of-commands.txt
       

where <pipeline-name> refers to one of the :ref:`available  GenPipes Pipelines<docs_available_pipelines>` and step-range-number-1-n refers to the specific steps in the pipeline that need to be executed. 

To launch GenPipes, the following is needed:

1. Name of the pipeline corresponding to one of the :ref:`available  GenPipes Pipelines<docs_available_pipelines>`.

2. A :ref:`readset file<docs_readset_file>` that contains information about the samples, indicated using the flag “-r”. GenPipes can aggregate and merge samples as indicated by the readset file.

3. Configuration/ini files that contain parameters related to the cluster and the third-party tools, indicated using the flag “-c”. Configuration files are customizable, allowing users to adjust different parameters.

4. The specific steps to be executed, indicated by the flag “-s”. 

In addition to the :ref:`configuration files<docs_config_ini_file>` and the input :ref:`readset file<docs_readset_file>`, certain pipelines such as ChIP-Seq and RNA sequencing (RNA-Seq), require a :ref:`design file<docs_design_file>` that describes each contrast. Custom sample groupings can be defined in the design file. :ref:`Design files<docs_design_file>` are indicated by the flag “-d”. The tumor_pair pipeline requires normal−tumor pairing information provided in a standard comma-separated values file using the “-p” option. More information on the design file and the content of each file type can be found in the :ref:`GenPipes User Guide<docs_user_guide>`. 

Example Run
-----------
The following example shows how you can run Hi-C sequencing pipeline using GenPipes installed on Compute Canada data centres. Please ensure you have login access to GenPipes servers.  Refer to :ref:`checklist of pre-requisites for GenPipes<docs_pre_req_chklist>` before you run this example.

We will now run the pipeline using a test dataset. We will use the first 2 million reads from HIC010 from Rao et al. 2014 (SRR1658581.sra). This is an in-situ Hi-C experiment of GM12878 using MboI restriction enzyme.

You need to first download the test dataset by visiting this link: 

`Hi-C Sequencing Test Dataset <http://www.computationalgenomics.ca/tutorial/hicseq.zip>`_

In the downloaded zip file, you will find the two fastq read files in folder “rawData” and will find the readset file (readsets.HiC010.tsv) that describes that dataset.

Please ensure you have access to "guillimin" server in Compute Canada data centre. We will run this analysis on guillimin as follows:

::

  hicseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.guillimin.ini -r readsets.HiC010.tsv -s 1-15 -e MboI > hicseqScript_SRR1658581.txt

To understand what $MUGQIC_PIPELINES_HOME refers to, please see instructions on how to :ref:`access GenPipes on Compute Canada servers<docs_access_gp_pre_installed>`.

In the command above, 

-c defines the ini configuration files

-r defines the readset file

-s defines the steps of the pipeline to execute. To check pipeline steps use hicseq -h

-e defines the restriction enzyme used in the HiC library

By default, on Compute Canada servers such as "Cedar", "Graham" or "Mammouth", SLURM scheduler is used. On guillimin server, you need to use PBS scheduler. For that you need to specify "-j pbs" option as shown below:

::

  hicseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.guillimn.ini -r readsets.HiC010.tsv -s 1-15 -e MboI -j pbs > hicseqScript_SRR1658581.txt

The above command generates a list of instructions that need to be executed to run Hi-C sequencing pipeline.  These instructions are stored in the file:

::

 hicseqScript_SRR1658581.txt

To execute these instructions, use:

:: 

  bash hicseqScript_SRR1658581.txt

.. warning::

         You will not see anything happen, but the commands will be sent to the server job queue. So do not run this more than once per job.

To confirm that the commands have been submitted, wait a minute or two depending on the server and type:

::

  showq -u <userID>

where, <userID> is your login id for accessing Compute Canada infrastructure.

In case you ran it several times and launched too many commands you do not want, you can use the following line of code to cancel ALL commands:

::

  showq -u <userID> | tr "|" " "| awk '{print $1}' | xargs -n1 canceljob

.. note::

	Congratulations!
        You just successfully issued the Hi-C sequencing analysis pipeline commands!!!

After the processing is complete, you can access quality control plots in the homer_tag_directory/HomerQcPlots. You can find the compartment data in the compartments folder, TADs in the TADs folder and significant interactions in the peaks folder.

For more information about output formats please consult the webpage of the third party tool used.

.. note::

         The Hi-C sequencing pipeline also analyzes capture hic data if the “-t capture” flag is used. For more information on the available steps in that pipeline use: 

::

  hicseq -h

To see examples of running other pipelines and also for figuring out how to run pipelines locally or in the cloud on your own GenPipes deployment, refer to :ref:`GenPipes Tutorials<doc_list_tutorials>`.
