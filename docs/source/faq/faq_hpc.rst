.. _docs_faq_hpc:

.. spelling:word-list::

     genpipes

GenPipes HPC Jobs
-------------------

.. contents::
  :local:
  :depth: 1

----

How do I run GenPipes pipelines when the number of steps or jobs exceeds HPC site queue limit?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Most HPC sites impose resource sharing constraints. One such constraint is limiting the number of jobs submitted to the scheduler wait queue. In such environments user can overcome the queue limits and continue to run GenPipes Pipelines even if the job has more steps than the limit.

**Response**

GenPipes provides utilities such as ```chunk_genpipes.sh``` that can take pipeline commands as input and chunks them so that each chunk consists of jobs which are within the specified queue limits for a given HPC environment.

For example, the chipseq pipeline commands can be chunked as follows:

::

  M_FOLDER=path_to_folder

  genpipes chipseq <options> --genpipes_file chipseq_script.sh

  chunk_genpipes.sh chipseq_script.sh $M_FOLDER -n 15

Here, ```-n 15``` input specifies that the maximum number of jobs in a chunk is 15.  This is an optional parameter.  By default, the chunk size is 20.

You can use the ```submit_genpipes``` GenPipes utility to submit jobs smartly to the scheduler and use scheduler ```watch``` command to monitor the status of these job `chunks`.
::

  submit_genpipes $M_FOLDER

For details, refer to :ref:`Submitting GenPipes Pipeline runs<ref_submitting_gp>` and see genpipes/utils in the source tree.

.. warning::

     ```chunk_genpipes.sh``` script should be invoked **only once** for a pipeline run whereas the ```submit_genpipes``` script can be run multiple times during a pipeline run for checking the job status.

----

In case of an error or job timeout, do I need to re-run the entire GenPipes Pipeline script over again or is there a smarter way to submit only the failed jobs?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

When there is an error or timeout with the scheduler, the user can avoid canceling all GenPipes jobs and re-submit the entire pipeline script again.

**Response**

GenPipes utilities such as ```chunk_genpipes.sh``` and ```submit_genpipes``` can be used to smartly chunk pipeline command script and submit these chunks to the HPC scheduler queue instead of the full pipeline run script at once.The ```submit_genpipes``` script can be used to smartly submit jobs to the scheduler and then use the scheduler's ```watch``` command to monitor status of job runs. Only the job chunks that timeout or encounter error can be re-submitted to the scheduling queue. 
For details, refer to :ref:`Submitting GenPipes Pipeline runs<ref_submitting_gp>` and see genpipes/utils in the source tree.
