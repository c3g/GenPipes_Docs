.. _docs_genpipes_container_tutorial:

.. spelling::

       qsub
       sbatch

Running GenPipes in a local Containerized Infrastructure
=========================================================

.. note::

     The following is work in progress.

This tutorial is TBD. For now here is the information we have regarding how to run GenPipes locally within your infrastructure in a containerized environment.

GenPipes pipelines use scheduler's calls (qsub, sbatch) for submitting genomic analysis compute jobs. If you plan to use GenPipes locally using your infrastructure, inside a container, you need to run the GenPipes pipeline python scripts using the "batch mode" option.  For local containerized versions of GenPipes, this is the preferred way of running the pipelines, if you don't have access to a scheduler locally such as SLURM or PBS.  

This is how you can run GenPipes pipelines such as :ref:`DNA Sequencing Pipeline<docs_gp_dnaseq>`, refer to the command below:

::

  dnaseq.py -c dnaseq.base.ini dnaseq.batch.ini -j batch -r your-readsets.tsv -d your-design.tsv -s 1-34 -t mugqic > run-in-container-dnaseq-script.sh
   
  bash run-in-container-dnaseq-script.sh

Please note, there is a disadvantage to running GenPipes Pipelines without a scheduler.  In the batch mode, which is configured using the "-j batch" option, all the jobs would run as a batch, one after another, on a single node.  If your server is powerful enough, this might be your preferable option.  Otherwise, if you would like to take advantage of GenPipes' job scheduling capabilities, you need to install a job scheduler locally in your infrastructure so that GenPipes can work effectively.  We recommend SLURM scheduler for GenPipes.

