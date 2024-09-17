::

  genpipes dnaseq -t somatic_fastpass -c $MUGQIC_PIPELINES_HOME/pipelines/dnaseq/dnaseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/dnaseq/dnaseq.cancer.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readset.somatic_fastpass.txt -p pairs.somatic_fastpass.csv -j slurm -s 1-15 -g dna_commands.sh

  bash dna_commands.sh

.. include:: /common/gp_cluster_ini.inc
