::

  genpipes chipseq -c $GENPIPES_INIS/pipelines/chipseq/chipseq.base.ini $GENPIPES_INIS/pipelines/common_ini/beluga.ini -r readset.chipseq.txt -d design.chipseq.txt -s 1-20 -g chipseqScript.sh

  bash chipseqScript.sh

.. include:: /common/gp_cluster_ini.inc
