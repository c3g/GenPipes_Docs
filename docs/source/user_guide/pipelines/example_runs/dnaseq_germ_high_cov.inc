::

    genpipes dnaseq -t germline_high_cov -c $MUGQIC_PIPELINES_HOME/pipelines/dnaseq_high_coverage/dnaseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -j slurm -s 1-15 -g dna_commands.sh

    bash dna_commands.sh

.. include:: /common/gp_cluster_ini.inc
