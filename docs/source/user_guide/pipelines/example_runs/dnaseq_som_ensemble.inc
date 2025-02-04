::

  genpipes dnaseq -t somatic_ensemble -p patientname_file, normal_sample_file, tumor_sample_file -c $GENPIPES_INIS/dnaseq/dnaseq.base.ini $GENPIPES_INIS/dnaseq/dnaseq.cancer.ini $GENPIPES_INIS/common_ini/beluga.ini -r readset.somatic_ensemble.txt -p pairs.somatic_ensemble.csv -j slurm -s 1-15 -g dna_commands.sh

  bash dna_commands.sh

.. include:: /common/gp_cluster_ini.inc
