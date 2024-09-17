.. _docs_gp_job_results:

.. spelling::

        walltime

Viewing and Analyzing GenPipes Results
=======================================

This document contains generic insights related to viewing and analyzing results obtained after running GenPipes Pipelines.  It assumes that you are familiar with :ref:`GenPipes Basics<docs_what_is_genpipes>` and have used one of the pipelines already as demonstrated in :ref:`Using GenPipes<docs_using_gp>`.

.. contents:: :local:

----

Overview
--------

If you are a new user of GenPipes and have successfully run it for the first time, you are likely to wonder, what is next?  How can you determine whether all the jobs that were part of one of the :ref:`GenPipes Pipelines<docs_pipeline_ref>` were executed successfully? Where are the results located once the pipelines are run and what is the best way to view and analyze GenPipes results in general. 

You can find answers to such questions here.

GenPipes Results
-----------------

When a pipeline is run successfully, by default, the output is saved to the same location the pipeline was launched in the first place. This behavior can be changed by modifying the output directory when launching the pipeline using -o or --output-dir, for example:

::

   genpipes rnaseq -o /PATH/TO/OUTPUT ... (other options) -g genpipes_cmd_list.sh
   
   bash genpipes_cmd_list.sh

For most pipelines, GenPipes creates an html report with most of the results in the pipeline. To create the report, you need to rerun the same command you ran to create the GenPipes commands, but add --report to it.

Refer to the 'job_output' directory. In that directory, you can find subdirectories that roughly correspond to each step in the pipeline, inside those are the log files. At the top, of the directory, there is a file that is named with the following convention:

::

  job_output/PIPELINE_job_list_YEAR-MM-DDTHH.MM.SS

where, PIPELINE corresponds to the pipeline name and YEAR-MM-DDTHH.MM.SS to the date and time the pipeline was launched. This job list file in the job_output folder that can help you determine the status of each job and sub-jobs as well.

.. note::

       This job_list file can be used to check the status of only those jobs that are scheduled using PBS and Slurm schedulers.  Also, this feature is not supported when you run :ref:`GenPipes in a container<docs_dep_gp_container>`.


Abacus Reports (PBS Scheduler)
++++++++++++++++++++++++++++++

Use the `log_report.pl` script to generate the tab-delimited report for Abacus as shown in the command below:

::

  log_report.pl job_output/{PIPELINE}_job_list_{DATE}T{TIME}

For example:

::

  log_report.pl job_output/RnaSeq_job_list_2018-06-26T12.54.27

This command shown above returns the status of each job. In addition to the detailed report, it also outputs a summary file that includes the number of jobs that completed successfully, those that failed, and those that are still active/inactive.

Compute Canada Reports (Slurm Scheduler)
+++++++++++++++++++++++++++++++++++++++++

Use the `log_report.py` script to generate the html report for Compute Canada Clusters running Slurm Scheduler:

::

 log_report.py job_output/{PIPELINE}_job_list_{DATE}T{TIME} --tsv log.out 
 
.. note::
  
     By default, unlike the `log_report.pl` script, the script `log_report.py` does not provide detailed output.  Use the --tsv option to get a detailed output.

You can save the reports as .csv or .tsv files and open them in Excel on your laptop.  For each job, there is an exit code that indicates job status.  

Exit Codes
++++++++++

Following are some of the common job exit codes:

* 0 - Exit code of 0 means that the pipeline ran without any issues
* 271 - This exit code typically means that there was insufficient RAM allocated and hence the job did not run successfully.
* -11 - Exit code -11 indicates that the job was prematurely killed as it exceeded the allocated walltime - basically insufficient compute resources were assigned for the job.

.. note::

      For every GenPipes Pipeline run, output is created in the default or specified location. However, please note that what is actually written in the output location varies significantly between each pipeline.  Refer to GenPipes User Guide, :ref:`Pipelines Reference<docs_pipeline_ref>` section for details regarding the processing performed by different pipelines.

GenPipes Errors & Log Files
----------------------------

When launched, GenPipes creates a job_output folder where it stores the logs and errors from all the jobs. If errors occur, you need to look into the job_output folder for the log of the step that failed to see what it last printed before it shut down. This usually helps to understand what potentially happened. When a job finishes successfully, it will create a file with the extension .done.

GenPipes Logs are stored in the job_output folder under the appropriate folder for each step. For more details see :download:`GenPipes Error Logs </ref/C3GAW_practical_7_GenpipeProgress.pdf>`.

Visualization and Analysis
--------------------------

GenPipes output results vary a lot depending upon each specific pipeline and the way it is configured to run. Also, the way results are analyzed is also dependent on the final objective of the analysis. For example, in case of visualizations, the results have to be imported to R or Python or some alternative visualization package. 

Tools such as Integrative Genomics Viewer (`IGV`_ - Integrative Genomics Viewer), `Genome Browser Gateway <https://genome.ucsc.edu/cgi-bin/hgGateway>`_ and several others are utilized for visualization of results. **These tools vary from pipeline to pipeline.** 

Figure below demonstrates one such tool used for RNA Sequencing Analysis.

.. figure:: /img/genome_brow_gway.png
   :align: center
   :alt: gnome-browser 

   Figure: Genome Browser Gateway

The best way for new users and beginners to begin to explore the results is to look at the interactive MultiQC reports.  Most pipelines support this and generate an html report that is saved under the report directory. 

The MultiQC report that is automatically generated when running the pipeline summarizes the most important results in the pipeline, while providing tables or plots per sample. More advanced users can use the output files used as input to MultiQC to generate their own visualizations or further analyze results using their own methods.

As mentioned earlier, visualization of results varies from pipeline to pipeline. As a reference, you can see :download:`RNA Sequencing Analysis Visualization of results </ref/C3GAW_practical_6_visualization.pdf>`.

Figure below shows how the data is displayed once the alignment files are opened on IGV.

.. figure:: /img/alignment_vis.png
   :align: center
   :alt: data alignment vis

   Figure: Data Alignment visualizer using IGV Tool

GenPipes Relaunch
-----------------

If GenPipes fails, for any reason, you can recreate the commands and relaunch them.
When recreating the commands, GenPipes can detect jobs that have completed successfully and will not rerun them.  That being said, unless you understand why a job failed and fix it, relaunched jobs might fail with the same error.

GenPipes Clean
--------------

GenPipes stores some temporary files that are useful to shorten potential reruns. To delete all these files, you can run the GenPipes command with --clean. This will delete a lot of files that were marked by GenPipe developers as “removable”. If you are interested in temporary files, avoid the –clean command.

Tracking GenPipes Environment Parameters for quoting in Publications
---------------------------------------------------------------------

In order to keep track of all parameters used, GenPipes creates a final .config.trace.ini file each time it is run. It is a good idea to keep a copy of that file in order to keep track of software versions used when publishing your paper or publication.

.. _IGV: http://software.broadinstitute.org/software/igv/
