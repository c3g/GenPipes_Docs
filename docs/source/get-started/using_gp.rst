.. _docs_using_gp:


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

GenPipes framework can be used to perform various genomic analysis corresponding to the available pipelines.  GenPipes is a command line tool. The underlying object-oriented framework is developed in Python. It simplifies the development of new features and its adaptation to new systems; new workflows can be created by implementing a Pipeline object that inherits features and steps from other existing Pipeline objects. Similarly, deploying GenPipes on a new system may only require the development of the corresponding Scheduler object along with specific configuration files. GenPipes’ command execution details have been implemented using a shared library system, which allows the modification of tasks by simply adjusting input parameters. This simplifies code maintenance and makes changes in software versions consistent across all pipelines.

Running GenPipes
-----------------

Here is how you can launch GenPipes. Following is the generic command to run GenPipes:

.. code-block:: bash

   <pipeline-name>.py -c your-configuration-file -r input-readset-file -s step-range-number-1-n > list-of-commands.txt
   bash list-of-commands.txt
       

where <pipeline-name> refers to one of the supported GenPipes Pipelines and step-range-number-1-n refers to the specific steps in the pipeline that need to be executed. In addition to the configuration file and the input readset file, certain pipelines such as ChIP-Seq and RNA sequencing (RNA-Seq), require a design file that describes each contrast. Custom sample groupings can be defined in the design file. Design files are indicated by the flag “-d”. The tumor_pair pipeline requires normal−tumor pairing information provided in a standard comma-separated values file using the “-p” option. More information on the design file and the content of each file type can be found in the :ref:`GenPipes User Guide<docs_user_guide>`. 
