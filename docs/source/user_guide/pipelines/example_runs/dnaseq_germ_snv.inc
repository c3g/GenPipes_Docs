::

  genpipes dnaseq_.py -t germline_snv -c $MUGQIC_PIPELINES_HOME/pipelines/dnaseq_high_coverage/dnaseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readset.dnaseq.txt -j slurm -s 1-15 -g dna_commands.sh

  bash dna_commands.sh

.. include:: /common/gp_cluster_ini.inc

