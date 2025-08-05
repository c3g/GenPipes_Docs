.. parsed-literal::

    genpipes dnaseq -t germline_sv -c $GENPIPES_INIS/dnaseq/dnaseq.base.ini \\
        $GENPIPES_INIS/dnaseq/dnaseq.sv.ini \\
        $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
        -r readset.dnaseq.txt \\
        -s 1-25 -g dnaseq_germ_sv_cmd.sh
        
    bash dnaseq_germ_sv_cmd.sh