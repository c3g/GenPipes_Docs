.. _docs_troubleshooting_gp:

.. spelling::

    qsub
    slurm
    moab

Troubleshooting GenPipes
=========================
This document lists some commonly faced issues related to GenPipes deployment and usage.

.. note::
	* Deployment issues

          - Container (local deployment)
	  - Cloud deployment
	  - Accessing C3G pre-installed GenPipes

	* Usage issues

	  - Input parameters
	  - Design file
	  - Pre-requisites not taken care of – SW/ Input / File format
	  - Scheduler related usage issues

**Contents**

.. contents:: :local:

----

Error: qsub command not found
------------------------------

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

Error: RAP_ID  not set error message
-------------------------------------
To be updated once there is more data available regarding error text

----

Error: Other commonly faced errors for new users
------------------------------------------------

TBD
