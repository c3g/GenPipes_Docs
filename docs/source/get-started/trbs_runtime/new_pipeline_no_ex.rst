.. _docs_troubleshooting_rt_new_pipeline_no_exec:

Error: Newbie issue - the pipeline does not execute at all!
-------------------------------------------------------------

First time users may issue the pipeline command and assume it will generate jobs on worker nodes automatically.  However, after multiple runs, no execution happens if the pipeline command is executed.  For example see Han's issue in `GenPipes Google Group <https://groups.google.com/forum/#!msg/genpipes/4jxFWDC_Otw/K0ULgt7-AQAJ;context-place=forum/genpipes>`_.

**Fix**

This is a very common issue.  GenPipes pipeline command does NOT issue the commands on its own.  When you run the pipeline, it simply generates a bunch of commands to execute but does not execute them.  You need to redirect the output of pipeline command into a file and then bash execute that file containing all the commands corresponding to a genomic analysis.  See GenPipes Google Group discussions and Mathieu Bourgey's `response for details <https://groups.google.com/forum/#!msg/genpipes/4jxFWDC_Otw/K0ULgt7-AQAJ;context-place=forum/genpipes>`_.
