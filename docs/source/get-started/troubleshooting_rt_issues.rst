.. _docs_troubleshooting_rt_issues:

.. spelling::

    qsub
    slurm
    moab

Troubleshooting Runtime issues 
===============================
This document lists some commonly faced issues related to GenPipes deployment and usage.  These could be related to GenPipes deployment, software dependencies, environment setup or usage options.

The objective here is to list some commonly encountered issues and their fixes so that new users can benefit and focus more on using GenPipes.  These are mostly run-time issues that a new user may face. If you are looking at troubleshooting GenPipes as part of feature development or contributing to GenPipes code, please refer to the :ref:'Development` section of this documentation and refer to :ref:`Developer Guide<docs_dev_guide>` and :ref:`Troubleshooting Guide<docs_troubleshooting_guide>`.

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

Other issues need to be listed here along with their workaround and fix (if any). The following note is a placeholder to identify GenPipes troubleshooting issues related to the topics listed below:

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

