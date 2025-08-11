.. _docs_using_gp:

.. spelling:word-list::

   userID
   txt
   genpipes
   atacseq
   ATAC-Seq
   
Using GenPipes for genomic analysis
====================================

This document describes the GenPipes execution environment and how to use various genomic analysis pipelines.  It assumes you already have access to GenPipes through one of the available :ref:`GenPipes Deployment Options<docs_dep_options>`.

.. note::
   **Have you tried the GenPipes Wizard?**
      We've developed a helpful tool: the :ref:`GenPipes Wizard <docs_gp_wizard>`. It guides users through selecting the appropriate deployment method, pipeline, and protocol, and helps construct the full command to run GenPipes.


Topics covered in this document includes information regarding what is available in a typical GenPipes deployment and how to access it. Besides that it covers details on required software and environment configurations, various kinds of inputs required to run genomic analysis such as command options, configuration details, readset file and design file. There are example runs highlighting how to issue the pipeline commands with requisite inputs and pipeline specific configurations.

.. contents:: :local:


GenPipes Executable
--------------------
The GenPipes framework can be used to perform various genomic analyses corresponding to the available pipelines.  GenPipes is a command line tool. The underlying object-oriented framework is developed in Python. It simplifies the development of new features and its adaptation to new systems; new workflows can be created by implementing a Pipeline object that inherits features and steps from other existing Pipeline objects. 

Similarly, deploying GenPipes on a new system may only require the development of the corresponding Scheduler object along with specific :ref:`configuration files<docs_config_ini_file>`. GenPipes’ command execution details have been implemented using a shared library system, which allows the modification of tasks by simply adjusting input parameters. This simplifies code maintenance and makes changes in software versions consistent across all pipelines.

Running GenPipes
-----------------

**Pre-Requisites**

Before running GenPipes, you may want to visit the :ref:`checklist of pre-requisites for GenPipes<docs_pre_req_chklist>`.

**Usage**

Here is how you can launch GenPipes. Following is the generic command to run GenPipes:

.. code-block:: bash

   genpipes <pipeline-name> -c config -r readset-file -s 1-n -g list-of-commands.txt
   bash list-of-commands.txt
       

where:

- **<pipeline-name>** refers to one of the :ref:`available  GenPipes Pipelines<docs_available_pipelines>`
- **-s** <step-range-number-1-n> refers to the specific steps in the pipeline that need to be executed
- **-c** refers to the configuration file, multiple files can be specified, say one for cluster specific configuration and another that is pipeline specific configuration settings
- **-r** readset file, an input file required by the pipeline
- **-g** the commands for running the pipeline are output to this file.

.. _gp_terminology:

**Terminology**

In the context of GenPipes, you need to be familiar with the following terms.  These constitute inputs and configuration required before you can launch the pipelines.

* :ref:`Readset File<docs_readset_file>`
* :ref:`Configuration files<docs_config_ini_file>`
* :ref:`Design files<docs_design_file>`
* :ref:`Test Datasets<docs_testdatasets>` 

**Launching GenPipes**

To launch GenPipes, the following is needed:

1. Name of the pipeline corresponding to one of the :ref:`available  GenPipes Pipelines<docs_available_pipelines>`.

2. A :ref:`readset file<docs_readset_file>` that contains information about the samples, indicated using the flag “-r”. GenPipes can aggregate and merge samples as indicated by the readset file.

3. Configuration/ini files that contain parameters related to the cluster and the third-party tools, indicated using the flag “-c”. Configuration files are customizable, allowing users to adjust different parameters.

4. The specific steps to be executed, indicated by the flag “-s”. 

In addition to the :ref:`configuration files<docs_config_ini_file>` and the input :ref:`readset file<docs_readset_file>`, certain pipelines such as ChIP-Seq and RNA sequencing (RNA-Seq), require a :ref:`design file<docs_design_file>` that describes each contrast. Custom sample groupings can be defined in the design file. :ref:`Design files<docs_design_file>` are indicated by the flag “-d”. More information on the design file and the content of each file type can be found in the :ref:`GenPipes User Guide<docs_user_guide>`. 

.. image:: /img/gp_command_profile.png

Example Run
^^^^^^^^^^^^

The following example shows how you can run the ChIP Sequencing pipeline using GenPipes installed on Compute Canada data centres. Please ensure you have login access to GenPipes servers.  Refer to :ref:`checklist of pre-requisites for GenPipes<docs_pre_req_chklist>` before you run this example.

We will now run the pipeline using a test dataset. 

You need to first download the test dataset by visiting this link: 

`ChiP Sequencing Test Dataset <https://datahub-90-cw3.p.genap.ca/chipseq.chr19.new.tar.gz>`_

In the downloaded tar file, you will find the fastq read files in folder “rawData” and will find the readset file (readset.chipseq.txt) that describes that dataset.

Please ensure you have access to the "\ |key_ccdb_server_name|\" server in `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_, formerly Compute Canada, data centre. We will run this analysis on |key_ccdb_server_name| as follows:

::

  genpipes chipseq -c $GENPIPES_INIS/chipseq/chipseq.base.ini $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini -r readset.chipseq.txt -s 1-15 -g chipseq_cmd.sh

To understand what $GENPIPES_INIS refers to, please see instructions on how to :ref:`access GenPipes on Compute Canada servers<docs_access_gp_pre_installed>`.

In the command above, 

-c defines the ini configuration files

-r defines the readset file

-s defines the steps of the pipeline to execute, use `genpipes chipseq -h` to check steps

By default, Slurm scheduler is used when using the GenPipes deployment on the `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_, formerly Compute Canada, servers such as |key_ccdb_server_name|, |other_ccdb_server_names|. On the abacus server, you need to use PBS scheduler. For that you need to specify "-j pbs" option as shown below:

::

  genpipes chipseq -c $GENPIPES_INIS/chipseq/chiseq.base.ini $GENPIPES_INIS/common_ini/abacus.ini -r readset.chipseq.txt -s 1-15 -j pbs -g chipseq_cmd.sh

The above command generates a list of instructions that need to be executed to run the ChIP sequencing pipeline. These instructions are stored in the file:

::

  chipseq_cmd.sh

To execute these instructions, use:

:: 

  bash chipseq_cmd.sh

.. warning::

         You will not see anything happen, but the commands will be sent to the server job queue. So do not run this more than once per job.

To confirm that the commands have been submitted, wait a minute or two depending on the server and type:

::

  squeue -u <userID>

where, <userID> is your login id for accessing the DRAC infrastructure.

On abacus, the equivalent command is:
::

  showq -u <userID>

In case you ran the command to submit the jobs several times and launched too many commands you do not want, you can use the following line of code to cancel ALL commands:
::

  scancel -u <userID>


Or on abacus:
::

  showq -u <userID> | tr "|" " "| awk '{print $1}' | xargs -n1 canceljob

.. note::

	Congratulations!
        You just successfully issued the ChIP sequencing analysis pipeline commands!!!

After the processing is complete, you can access quality control plots in the report/ directory and you can find peak data in the peak_call/ directory.

For more information about output formats please consult the webpage of the third party tool used.

.. note::

         The ChIP sequencing pipeline also analyzes ATAC-Seq data if the “-t atacseq” flag is used. For more information on the available steps in that pipeline use: 

::

  genpipes chipseq -h

Example Run with Design File
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Certain pipelines that involve comparing and contrasting samples, need a :ref:`Design File<docs_design_file>`. The design file can contain more than one way to contrast and compare samples.  To see how this works with GenPipes pipelines, lets run a RNA-Sequencing experiment.

**RNA-Sequencing Test Dataset**

First, you need to download the test dataset from `here <https://datahub-90-cw3.p.genap.ca/rnaseq.chr19.tar.gz>`_.

In the downloaded tar file, you will find the fastq read files in folder rawData and will find the readset file (readset.rnaseq.txt) that describes that dataset. You will also find the design file (design.rnaseq.txt) that contains the contrast of interest.

Following is the content of the Readset file (readset.rnaseq.txt):

::

  Sample	Readset	Library	RunType	Run	Lane	Adapter1	Adapter2	QualityOffset	BED	FASTQ1	FASTQ2	BAM
  GM12878_Rep1	GM12878_Rep1	myLibrary	PAIRED_END	1	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/rnaseq_GM12878_chr19_Rep1_R1.fastq.gz	raw_data/rnaseq_GM12878_chr19_Rep1_R2.fastq.gz	
  GM12878_Rep2	GM12878_Rep2	myLibrary	PAIRED_END	1	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/rnaseq_GM12878_chr19_Rep2_R1.fastq.gz	raw_data/rnaseq_GM12878_chr19_Rep2_R2.fastq.gz	
  H1ESC_Rep1	H1ESC_Rep1	myLibrary2	PAIRED_END	1	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/rnaseq_H1ESC_chr19_Rep1_R1.fastq.gz	raw_data/rnaseq_H1ESC_chr19_Rep1_R2.fastq.gz	
  H1ESC_Rep2	H1ESC_Rep2	myLibrary2	PAIRED_END	1	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/rnaseq_H1ESC_chr19_Rep2_R1.fastq.gz	raw_data/rnaseq_H1ESC_chr19_Rep2_R2.fastq.gz	


This analysis contains 4 samples with a single readset each. They are all PAIRED_END runs and have a pair of fastq files in the “rawData” folder.

Following is the content of the Design file (design.rnaseq.txt):

::

  Sample	H1ESC_GM12787
  H1ESC_Rep1	1
  H1ESC_Rep2	1
  GM12878_Rep1	2
  GM12878_Rep2	2

We see a single analysis that compares two replicates of `H1ESC` to two replicates of group `GM12878`.

Let us now run this RNA-Sequencing analysis on the |key_ccdb_server_name| server at `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_, formerly Compute Canada. Use the following command:

::

  genpipes rnaseq -c $GENPIPES_INIS/rnaseq/rnaseq.base.ini $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini -r readset.rnaseq.txt -d design.rnaseq.txt -g rnaseqScript.txt
  bash rnaseqScript.txt

The commands will be sent to the job queue and you will be notified once each step is done. If everything runs smoothly, you should get **MUGQICexitStatus:0** or **Exit_status=0.** If that is not the case, then an error has occurred after which the pipeline usually aborts. To examine the errors, check the content of the **job_output** folder.

.. _ref_submitting_gp:

Submitting GenPipes Pipeline Runs
----------------------------------

HPC site policies typically limit the number of jobs that a user can submit in a queue. These sites deploy resource schedulers such as Slurm, or PBS/Torque for scheduling and sharing of HPC resources. Integrating with the resource schedulers and dealing with resource constraints are critical to ensuring productivity of HPC users. GenPipes caters to these user pain points through intelligent utilities that help in smartly chunking and submitting pipeline runs, resubmitting the jobs and ensuring that there are no errors in scheduler calls.

GenPipes offers a utility scripts namely, ```chunk_genpipes.sh``` and ```submit_genpipes``` to enable better integration with resource schedulers (Slurm, PBS/Torque) deployed on HPC clusters. 

The usage model is as follows. First, you need to issue GenPipes pipeline command with -g GENPIPES_FILE option to store all pipeline commands in a bash script.  Next, you need to use the utility called ```chunk_genpipes.sh``` that takes as input this bash script file GENPIPES_FILE and chunks scheduler jobs into a folder ```job_chunks``` (default) or the one you specify. Note that chunk_genpipes.sh utility is supposed to be run for a pipeline bash script  **only once**. After successful chunking, user can use the ```submit_genpipes``` utility to smartly submit the pipeline jobs to the scheduler without having to worry about scheduler integration and exceeding queue limits as these utilities take care of that.  Better HPC integration is offered by ```submit_genpipes``` as it looks for any error in the calls made to the scheduler and makes sure to auto-correct them based on chunking limits specified through ```chunk_genpipes.sh``` earlier.

The ```submit_genpipes``` script lets GenPipes users manage resource constraints in a flexible and robust manner. GenPipes user can delegate job submission to this script and use ```watch``` command to monitor the submitted jobs. At any time,  GenPipes users can stop monitoring the submitted jobs by issuing ```Ctrl-C``` to a running ```watch``` command in the terminal. After a clean ```ctrl-C``` stop of or if the watch command was killed in another manner, for example when a session is killed after ssh disconnection, users can restart monitoring GenPipes jobs to the queuing system by simply invoking the ```watch``` command again.

The ```submit_genpipes``` script comes with a fail safe mechanism that will resubmit jobs that failed to be sent to the scheduler up to 10 times (default). 

Example: Submitting ChipSeq jobs
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here is an example of how to use the ```submit_genpipes``` script with the :ref:`Chip Sequencing Pipeline<docs_gp_chipseq>`:

::

  M_FOLDER=path_to_folder

  genpipes chipseq <options> --genpipes_file chipseq_script.sh

  chunk_genpipes.sh chipseq_script.sh $M_FOLDER

  submit_genpipes $M_FOLDER

The ```chunk_genpipes.sh``` script is used to create job chunks of specified size that are submitted at a time. Please note that this script should be executed **only once** before using ```submit_genpipes``` to submit jobs.  

.. note::

     * The ```submit_genpipes``` script can be run for multiple GenPipes pipelines simultaneously, to ```submit jobs``` belonging to respective pipelines. You need to ensure that each submit_genpipes script invocation refers to a different job_chunks folder corresponding to the pipeline.

     * ```submit_genpipes``` script runs can be *stopped* by ```Ctrl-C``` keystroke and restarted at will. 

     * ```submit_genpipes``` script has intelligent lock mechanism that *prevents invoking two simultaneous runs* of ```submit_genpipes``` in parallel, on the on the same job chunking folder or GenPipes pipeline run.

The figure below demonstrates how the ```submit_genpipes``` utility works. The pipeline command file output is fed into ```chunk_genpipes.sh``` script which creates the chunks folder as a one time activity. This chunk folder is monitored by the ```submit_genpipes``` script.

.. figure:: /img/submit_genpipes_utility.png
   :align: center
   :width: 90%
   :figwidth: 90%
   :alt: submit_genpipes util

For a complete list of available GenPipes utilities, refer to the ```genpipes/util``` folder in the source tree.

Sample Output
^^^^^^^^^^^^^^

This section demonstrates how a GenPipes user can chunk job submission and submit job, monitor their status using ```chunk_genpipes.sh``` and ```submit_genpipes``` utilities  and ```watch``` command.

After generating GenPipes command file, say for GenPipes DNASeq Pipeline, 'dnaseq.sh`, follow these two steps:

**Step 1: Use chunk size 20 to chunk command submission to the scheduler**

::

  chunk_genpipes.sh dnaseq.sh job_chunks 20

.. note::

     In the command above, 20 specifies the number of jobs in a chunk

Figure below shows the output of the command above:

.. figure:: /img/chunk_genpipes_output.png
   :align: center
   :width: 60%
   :figwidth: 60%
   :alt: chunk_gp output

   Output of chunk_genpipes command

**Step 2: Invoke submit_genpipes script to monitor the submitted GenPipes jobs**

:: 

  submit_genpipes job_chunks -n 800

.. note::

     In the command above, 800 refers to the total number of jobs that can be submitted simultaneously at a time to the scheduler.

Figure below shows the output of the submit_genpipes command:

.. figure:: /img/monitorsh_output.png
   :align: center
   :width: 60%
   :figwidth: 60%
   :alt: chunk_gp output

   Output of submit_genpipes command

Further Information
-------------------

GenPipes pipelines are built around third party tools that the community uses in particular fields. To understand the output of each pipeline, please read the documentation pertaining to the tools that produced the output. 

You can see all :ref:`available GenPipes pipelines<docs_available_pipelines>` for a complete listing of all supported pipelines. To see examples of running other pipelines and also for figuring out how to run pipelines locally or in the cloud on your own GenPipes deployment, refer to :ref:`GenPipes Tutorials<doc_list_tutorials>`.

For further information or help with particular pipelines, you can send us an email to:

info@computationalgenomics.ca
