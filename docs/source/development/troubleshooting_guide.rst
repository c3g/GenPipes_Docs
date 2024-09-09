.. _docs_troubleshooting_guide:

Troubleshooting Guide
======================


This document contains most frequently encountered issues faced by developers and their fixes.

.. dropdown:: :material-outlined:`help;2em` No jobs are submitted after running `genpipes` command. Why?

   The `genpipes` command simply spits out the list of jobs that will be submitted subsequently. These commands are stored in the `genpipes_cmd.sh` script. It does not run the jobs on its own, users must run this script to ensure jobs are submitted.
   
   New users sometimes don't realize that it is not sufficient to issue the `genpipes <pipeline.py> [options] -g genpipes_cmd.sh` command. You must also run `bash genpipes_cmd.sh`` after running the `genpipes`` command. Jobs are submitted **only** when you execute the `bash genpipes_cmd.sh`.

.. dropdown:: :material-outlined:`help;2em` Issues while running `genpipes` command.
    
   Often pipeline users encounter issues are due to the readset and/or design file not being formatted correctly. Make sure you use the correct format for the readset and the design file as mentioned in the pipeline user guide. For example, ChIP sequencing protocol uses a different file format than the DNA sequencing pipeline. Learn more about the different :ref:`design file<docs_design_file>` and :ref:`readset file<docs_readset_file>` formats.