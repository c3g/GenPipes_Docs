.. parsed-literal::

    genpipes dnaseq -t somatic_tumor_only \\
    -c $GENPIPES_INIS/dnaseq/dnaseq.base.ini \\
    $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
    -r readset.somatic_tumor_only.txt \\
    -s 1-38 -j slurm -g dnaseq_somatic_tumor_cmd.sh

    bash dnaseq_somatic_tumor_cmd.sh