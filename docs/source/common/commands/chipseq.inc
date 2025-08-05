.. parsed-literal::

    genpipes chipseq -c $GENPIPES_INIS/chipseq/chipseq.base.ini \\
        $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
        -r readsets.chipseq.txt -d design.chipseq.txt \\
        -s 1-19 -g chipseqCommands.sh
    
    bash chipseqCommands.sh