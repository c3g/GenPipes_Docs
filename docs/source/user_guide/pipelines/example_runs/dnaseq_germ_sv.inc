::

  genpipes dnaseq -t germline_sv -c $GENPIPES_INIS/dnaseq/dnaseq.base.ini $GENPIPES_INIS/dnaseq/dnaseq.sv.ini $GENPIPES_INIS/common_ini/beluga.ini -r readset.dnaseq.txt -j slurm -s 1-15 -g dna_commands.sh

  bash dna_commands.sh

.. include:: /common/gp_cluster_ini.inc
