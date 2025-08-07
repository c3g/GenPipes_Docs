.. parsed-literal::

    genpipes nanopore_covseq -c $GENPIPES_INIS/nanopore/nanopore.base.ini \\
        $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
        $GENPIPES_INIS/nanopore_covseq/ARTIC_v4.1.ini \\
        -r readset.default.nanopore_covseq.txt -g nanopore_covseq_cmd.sh

    bash nanopore_covseq_cmd