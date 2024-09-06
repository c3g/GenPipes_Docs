::

  genpipes ampliconseq.py \
          -c $MUGQIC_PIPELINES_HOME/pipelines/ampliconseq/ampliconseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini \
          -r readset.ampliconseq.txt \
          -t dada2 \
          -s 1-5 \
          -g ampliconseqCommands.sh 

  bash ampliconseqCommands.sh

.. include:: /common/gp_cluster_ini.inc
