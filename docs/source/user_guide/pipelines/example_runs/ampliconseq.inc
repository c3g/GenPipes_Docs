::

  genpipes ampliconseq \
          -c $MUGQIC_PIPELINES_HOME/pipelines/ampliconseq/ampliconseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini \
          -r readset.ampliconseq.txt \
          -s 1-5 \
          -g ampliconseqCommands.sh 

  bash ampliconseqCommands.sh

.. include:: /common/gp_cluster_ini.inc
