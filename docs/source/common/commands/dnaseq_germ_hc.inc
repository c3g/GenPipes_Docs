.. parsed-literal::

    genpipes dnaseq -t germline_high_cov \\
        -c $GENPIPES_INIS/dnaseq/dnaseq.base.ini \\
        $GENPIPES_INIS/dnaseq/dnaseq.high_cov.ini  \\
        $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
        -r readset.dnaseq.txt \\
        -s 1-15 -g dnaseq_germ_high_cov_cmd.sh

    bash dnaseq_germ_high_cov_cmd.sh