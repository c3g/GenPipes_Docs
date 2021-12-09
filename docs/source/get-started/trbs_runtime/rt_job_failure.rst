.. _docs_troubleshooting_rt_job_failure:


Runtime Failure: Job fails on worker nodes
-------------------------------------------

When you issue the pipeline commands, the jobs fail to run on worker nodes.

**Fix**

The most common reason for this failure is not setting up the .bashrc with mugqic modules. See details on accessing GenPipes on Compute Canada servers - :ref:`setting_up_gp_environment_modules`. For other GenPipes :ref:`docs_dep_options`, make sure you have closely followed the :ref:`docs_pre_req_chklist` before actually issuing GenPipes pipeline run commands.
