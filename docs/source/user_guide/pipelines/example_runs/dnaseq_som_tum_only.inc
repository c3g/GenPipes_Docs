::

  genpipes dnaseq -t somatic_tumor_only -c $MUGQIC_PIPELINES_HOME/pipelines/dnaseq/dnaseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readset.somatic_tumor_only.txt -j slurm -s 1-15 -g dna_commands.sh

  bash dna_commands.sh

.. include:: /common/gp_cluster_ini.inc
