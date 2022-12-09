::

  python tumor_pair.py -c $MUGQIC_PIPELINES_HOME/pipelines/tumor_pair/tumor_pair.base.ini $MUGQIC_PIPELINES_HOME/pipelines/tumor_pair/tumor_pair.extra.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readset.tumorPair.txt -p pairs.csv -s 1-44 -g tumor_pairCommands.sh

  bash tumor_pairCommands.sh

.. include:: /common/gp_cluster_ini.inc
