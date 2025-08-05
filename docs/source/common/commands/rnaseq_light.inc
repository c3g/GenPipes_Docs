.. parsed-literal::

    genpipes rnaseq_light -c $GENPIPES_INIS/rnaseq_light/rnaseq_light.base.ini \\
        $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
        -r readset.rnaseq.txt -d design.rnaseq.txt \\
        -s 1-8 -g rnaseq_light_cmd.sh

    bash rnaseq_light_cmd.sh