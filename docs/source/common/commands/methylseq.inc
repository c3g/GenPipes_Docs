.. parsed-literal::

    genpipes methylseq -c $GENPIPES_INIS/methylseq/methylseq.base.ini \\
        $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
        -r readset.methylseq.txt \\
        -s 1-15,17-18 > methylseq.sh

    bash methylseq.sh 