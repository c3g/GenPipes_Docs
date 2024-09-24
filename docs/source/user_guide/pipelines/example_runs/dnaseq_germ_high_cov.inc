::

    genpipes dnaseq -t germline_high_cov -c $GENPIPES_INIS/dnaseq_high_coverage/dnaseq.base.ini $GENPIPES_INIS/common_ini/beluga.ini -j slurm -s 1-15 -g dna_commands.sh

    bash dna_commands.sh

.. include:: /common/gp_cluster_ini.inc
