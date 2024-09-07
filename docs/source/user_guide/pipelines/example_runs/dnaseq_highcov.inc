::

    genpipes dnaseq_high_coverage.py -c $MUGQIC_PIPELINES_HOME/pipelines/dnaseq_high_coverage/dnaseq_high_coverage.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -j slurm -s 1-15 -g dna_high_cov_commands.sh

    bash dna_high_cov_commands.sh

.. include:: /common/gp_cluster_ini.inc
