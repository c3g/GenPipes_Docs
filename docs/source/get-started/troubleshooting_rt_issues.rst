.. _docs_troubleshooting_rt_issues:

.. spelling::

    qsub
    slurm
    moab
    Runtime
    Ehresmann
    io

Troubleshooting Runtime Issues 
===============================
This document lists some commonly faced issues related to GenPipes deployment and usage.  These could be related to GenPipes deployment, software dependencies, environment setup or usage options.

The objective here is to list some commonly encountered issues and their fixes so that new users can benefit and focus more on using GenPipes.  These are mostly run-time issues that a new user may face. If you are looking at troubleshooting GenPipes as part of feature development or contributing to GenPipes code, please refer to the :ref:`Developer Guide<docs_dev_guide>` and :ref:`Troubleshooting Guide<docs_troubleshooting_guide>`.

**Contents**

.. contents:: :local:

----

1. Error: qsub command not found
----------------------------------

While running a pipeline using specific configuration file, the command text file is generated successfully. However, when the user tries to run the commands using:

::

  bash <command-file.txt>

the following error shows up:

*qsub: command not found*

.. image:: /img/error/get_st_err1a.png

.. image:: /img/error/get_st_err1b.png

**Fix**

Check the kind of GenPipes deployment you are working with.  If it is a local deployment, on a bare metal server or a virtual server or in a container, you need to make sure you do not specify -j pbs or -j slurm option but -j daemon or -j batch mode.

In case you are using moab or torque scheduler, ensure that you use -j pbs option in the pipeline command. If you are using mp2b or cedar server, then you need to specify -j slurm as the scheduler option and use the correct configuration file (mp2b.ini or cedar.ini) depending upon which server you are using to run your pipeline jobs.

----

2. Runtime Failure: Job fails on worker nodes
----------------------------------------------
When you issue the pipeline commands, the jobs fail to run on worker nodes.

**Fix**

The most common reason for this failure is not setting up the .bashrc with mugqic modules. See details on accessing GenPipes on Compute Canada servers - :ref:`setting_up_gp_environment_modules`. For other GenPipes :ref:`docs_dep_options`, make sure you have closely followed the :ref:`docs_pre_req_chklist` before actually issuing GenPipes pipeline run commands.

----

3. Error: RAP_ID not set
-------------------------
If you try to run GenPipes deployed by C3G on Compute Canada servers, the initial run shows error related to RAP_ID not set. Sometimes, this same issue manifests in the form of timing error as shown in figure below:

.. figure:: /img/error/rap_id_error.png
   :align: center
   :alt: rap_id error 

   Figure:  Error encountered if RAP_ID not set or set incorrectly

**Fix**

Make sure you have updated your .bashrc file as directed in :ref:`setting_up_gp_environment_modules`.  Once you set up the correct RAP_ID when you run the bash commands for your pipeline, they all go through and get scheduled depending on the scheduler (default or as as specified by -j option in pipeline command)

----

4. Error: Missing Genomes and Annotations
-----------------------------------------
Several users have encountered this issue.

**Fix**

Most of the GenPipes pipeline commands require you to supply input data in the form of readsets, design files and configuration.  If a specific genome that you need to provide to the pipeline is not available in the pre-installed GenPipes setup deployed on Compute Canada servers as listed in test `datasets <https://www.computationalgenomics.ca/test-dataset/>`_and available `genomes <https://genpipes.readthedocs.io/en/latest/c3gres/cvmfs_genomes.html>`_.

----

5. Error: While using STAR option in RNA Sequencing Pipeline
-------------------------------------------------------------
Users have reported issues while running RNA Sequencing Pipeline. One such issue is as listed by Sophie Ehresmann `here <https://groups.google.com/forum/#!searchin/genpipes/star%7Csort:date/genpipes/GzK3RZ5WZt4/3G8FEa_yAwAJ>`_.

**Fix**

TBD-GenPipes-Dev 

----

6. Error: Newbie issue - the pipeline does not execute at all!
--------------------------------------------------------------
First time users may issue the pipeline command and assume it will generate jobs on worker nodes automatically.  However, after multiple runs, no execution happens if the pipeline command is executed.  For example see Han's issue in `GenPipes Google Group <https://groups.google.com/forum/#!msg/genpipes/4jxFWDC_Otw/K0ULgt7-AQAJ;context-place=forum/genpipes>`_.

**Fix**

This is a very common issue.  GenPipes pipeline command does NOT issue the commands on its own.  When you run the pipeline, it simply generates a bunch of commands to execute but does not execute them.  You need to redirect the output of pipeline command into a file and then bash execute that file containing all the commands corresponding to a genomic analysis.  See GenPipes Google Group discussions and Mathieu Bourgey's `response for details <https://groups.google.com/forum/#!msg/genpipes/4jxFWDC_Otw/K0ULgt7-AQAJ;context-place=forum/genpipes>`_.

----

7. Error: RNA Sequencing Star alignment - Out of Memory
--------------------------------------------------------
For first time users, it has been observed (see example in `Google GenPipes Forum <https://groups.google.com/forum/#!topic/GenPipes/EC2VeLz3i0Y>`_) that the RNA Sequencing pipeline command execution stops after STAR alignment 1.  

**Fix**

try to change the STAR parameters in your ini files to something like in the .ini files of the master branch:

::

  https://bitbucket.org/mugqic/mugqic_pipelines/src/master

The problem should be solved by setting io_buffer to a higher value like 1G or 4G. The command you show indicates you are using 8M.

At some point io_buffer was decreased in the template .ini but this exposed a bug in STAR where a negative memory allocation is attempted.
