::

  genpipes ampliconseq \
          -c $GENPIPES_INIS/ampliconseq/ampliconseq.base.ini $GENPIPES_INIS/common_ini/beluga.ini \
          -r readset.ampliconseq.txt \
          -s 1-5 \
          -g ampliconseqCommands.sh 

  bash ampliconseqCommands.sh

.. include:: /common/gp_cluster_ini.inc
