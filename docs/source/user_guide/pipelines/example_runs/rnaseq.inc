::

  genpipes rnaseq -c $GENPIPES_INIS/rnaseq/rnaseq.base.ini $GENPIPES_INIS/common_ini/beluga.ini -r readset.rnaseq.txt -d design.rnaseq.txt -s 1-24 -j slurm -g commands.txt

  bash commands.txt

.. include:: /common/gp_cluster_ini.inc
