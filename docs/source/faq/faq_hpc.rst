.. _docs_faq_hpc:

.. spelling::

     genpipes

GenPipes HPC Jobs
-------------------

How do I run GenPipes pipelines when the number of steps or jobs exceeds HPC site queue limit?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Most HPC sites impose resource sharing constraints. One such constraint is limiting the number of jobs submitted to the scheduler wait queue. In such environments user can overcome the queue limits and continue to run GenPipes Pipelines even if the job has more steps than the limit.

**Response**

GenPipes provides utilities such as ```chunk_genpipes.sh``` that can takes pipeline commands as input and chunks them so that each chunk comprises of jobs which are within the specified queue limits for a given HPC environment.

For example, hicseq.py pipeline commands can be chunked as follows:

::

  M_FOLDER=path_to_folder

  hicseq.py <options> --genpipes_file hicseq_script.sh

  $MUGQIC_PIPELINES_HOME/utils/chunk_genpipes.sh hicseq_script.sh $M_FOLDER -n 15

Here, ```-n 15``` input specifies that the maximum number of jobs in a chunk is 15.  This is an optional parameter.  By default, the chunk size is 20.

You can use the ```watchdog.sh``` GenPipes utility to monitor the status of these job `chunks`.

For details, refer to :ref:`Monitoring GenPipes Pipeline runs<ref_monitoring_gp>` and see genpipes/utils in the source tree.

.. warning::

     ```chunk_genpipes.sh``` script should be invoked **only once** for a pipeline run whereas the ```watchdog.sh``` script can be run multiple times during a pipeline run for checking the job status.

----

In case of an error or job timeout, do I need to re-run the entire GenPipes Pipeline script over again or is there a smarter way to submit only the failed jobs?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

When there is an error or timeout with the scheduler, user can avoid canceling all GenPipes jobs and re-submit the entire pipeline script again.

**Response**

GenPipes utilities such as ```chunk_genpipes.sh``` and ```watchdog.sh``` can be used to smartly chunk pipeline command script and submit these chunks to the HPC scheduler queue instead of the full pipeline run script at once.The ```watchdog.sh``` script can be used to monitor status of job runs. Only the job chunks that timeout or encounter error can be re-submitted to the scheduling queue. 

For details, refer to :ref:`Monitoring GenPipes Pipeline runs<ref_monitoring_gp>` and see genpipes/utils in the source tree.
