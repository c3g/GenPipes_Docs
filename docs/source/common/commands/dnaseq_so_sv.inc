.. parsed-literal::

    genpipes dnaseq -t somatic_sv \\
    -c $GENPIPES_INIS/dnaseq/dnaseq.base.ini \\
    $GENPIPES_INIS/dnaseq/dnaseq.cancer.ini  \\
    $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
    -r readset.somatic_sv.txt \\
    -p pairs.somatic_sv.csv \\
    -s 1-38 -j slurm -g dnaseq_somatic_sv_cmd.sh

    bash dnaseq_somatic_sv_cmd.sh