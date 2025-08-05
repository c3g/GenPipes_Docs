.. parsed-literal::

    genpipes rnaseq_denovo_assembly \\
        -c $GENPIPES_INIS/rnaseq_denovo_assembly/rnaseq_denovo_assembly.base.ini \\
        $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
        -r readset.rnaseq.txt -d design.rnaseq.txt \\
        -s 1-24 -g rnaseq_denovo_cmd.sh

    bash rnaseq_denovo_cmd.sh