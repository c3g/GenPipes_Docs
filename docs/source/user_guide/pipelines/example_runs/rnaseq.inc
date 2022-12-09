::

  rnaseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/rnaseq/rnaseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini workshop.ini -r readset.rnaseq.txt -d design.rnaseq.txt -s 1-24 -j slurm -g commands.txt

  bash commands.txt

.. include:: /common/gp_cluster_ini.inc
