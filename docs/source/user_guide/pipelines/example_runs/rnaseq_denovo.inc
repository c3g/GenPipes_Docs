::

  genpipes rnaseq_denovo_assembly -c $GENPIPES_INIS/rnaseq_denovo_assembly/rnaseq_denovo_assembly.base.ini $GENPIPES_INIS/common_ini/beluga.ini -r readset.rnaseq.txt -d design.rnaseq.txt -s 1-23 -g rnaseqDeNovoCommands.sh

  bash rnaseqDeNovoCommands.sh

.. include:: /common/gp_cluster_ini.inc
