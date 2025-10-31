.. _docs_genpipes_container_tutorial:

.. spelling:word-list::

       qsub
       sbatch

Tutorial: GenPipes in a Local Container
========================================

.. include:: /common/new_gp_wizard.txt

GenPipes bioinformatics :ref:`pipelines<docs_available_pipelines>` are developed as part of the GenAP project at the Canadian Centre for Computational Genomics (C3G).

This tutorial shows you how to download, setup and run GenPipes locally within a containerized environment.

.. contents:: 
    :local:
    :depth: 2
 
----

Prerequisites
-------------

#. Download the latest version of GenPipes and 
   :ref:`deploy it in a container<docs_dep_gp_container>`. 

#. The available :ref:`GenPipes pipelines<docs_available_pipelines>` utilize the job
   scheduler's calls (``qsub``, ``sbatch``) for submitting genomic analysis compute jobs. You must have Slurm or PBS job scheduler available in your infrastructure to submit GenPipes pipeline job submissions.

#. If you want to deploy and use GenPipes in a local container but do not have access
   to Slurm or PBS scheduler in your local infrastructure, then it is recommended that you run the GenPipes pipeline launch scripts using the ``batch`` option.  

.. note:: 

    GenPipes is pre-installed on DRAC servers. These servers are set up to utilize Slurm job scheduler (PBS is available on C3G Abacus server). 
    
    If you are resource constrained, you may want to explore using GenPipes on DRAC servers instead of running the pipelines in your local environment. :ref:`Learn more...<doc_genpipes_tutorial>`.

:bdg-primary:`Step 1:` Check local GenPipes deployment
------------------------------------------------------

Make sure the container is up and running. Use the command to see if ``genpipes`` is available locally within the container:

.. code:: 

     user@machine:~$ genpipes -h

:bdg-primary:`Step 2:` Construct pipeline launch command
---------------------------------------------------------

In this tutorial, we will use the :ref:`DNA Sequencing Pipeline<docs_gp_dnaseq>`.
To create the pipeline command, use the following code in the terminal:

.. code::

     user@machine:~$ genpipes dnaseq -c dnaseq.base.ini dnaseq.batch.ini \\
                     -j batch \\
                     -r your-readsets.tsv \\
                     -d your-design.tsv \\
                     -s 1-34 \\
                     -t mugqic \\
                     -g run-in-container-dnaseq-script.sh

Each GenPipes pipeline requires some configuration settings and inputs such as parameters used for various genomic analysis tools invoked in different pipeline steps, design file (optional), and the readset file. Refer to the details in the :ref:`GenPipes Tutorial (DRAC Server)<doc_genpipes_tutorial>` to learn more about these input files, their formats and how to specify them when constructing the pipeline launch command. 

:bdg-primary:`Step 3:` Launch pipeline run
-------------------------------------------
   
.. code:: 

    user@machine:~$ bash run-in-container-dnaseq-script.sh

When running the ``dnaseq`` pipeline within a container, without any job scheduler, please note that the jobs run as a batch, one after another and not in parallel.

.. admonition:: Limitations
     :class: warning

      There is a disadvantage in running GenPipes Pipelines without a scheduler.
      
      When a pipeline is run in the batch mode using the ``-j batch`` flag, all the pipeline jobs are run as a batch, one after another, on a single node.  This requires a powerful server, otherwise it could be pretty slow and tedious.
      
      To take advantage of the job scheduling capabilities available in GenPipes pipelines, we recommend that you install a job scheduler (Slurm) locally in your infrastructure so that GenPipes can work effectively.

:bdg-primary:`Step 4:` Monitor Job Status
-------------------------------------------

Once the pipeline run is over, you can verify the exit status of each job with the GenPipes log_report tool:

::

	user@machine:~$ log_report.py --tsv log.out job_output/RnaSeq.stringtie.job_list.<TIMESTAMP>

Take a look at the output with:

::

	user@machine:~$ less -S log.out

and check that all jobs finished successfully. 

If you find that any jobs failed, look at the outputs in the ``job_output`` directory to identify the reason for the failure. 

If everything ran successfully, you will find an interactive html report under ``report/RnaSeq.stringtie.multiqc.html`` and the results of the differential expression analysis under the folder ``DGE``.

After the processing is complete, you can access quality control plots in the report/ directory and find peak data in the peak_call/ directory.

For more information about output formats please consult the webpage of the third party tools used by the pipeline.

.. note:: 

    If you are using Slurm scheduler deployed locally when running GenPipes in a container, you can use the commands ``squeue`` and ``showq`` to monitor job status. See :ref:`GenPipes Tutorial (DRAC Server)<doc_genpipes_tutorial>` for details on how to monitor pipeline job status.

Getting Help
-------------

GenPipes pipelines are built around third party tools used by the genomic research community in specific fields. To understand the output of each pipeline, refer to the  documentation for these specific tools used in pipeline steps to understand the produced output. 

For more information on contacting the GenPipes team or get help, click :ref:`support<docs_how_to_get_support>`.