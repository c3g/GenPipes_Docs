.. parsed-literal::

    user@machine:~$ genpipes ampliconseq -c $GENPIPES_INIS/ampliconseq/ampliconseq.base.ini \\
                                            $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
                                            -r readset.ampliconseq.txt \\
                                            -s 1-8 \\
                                            -g ampliconseqCommands.sh
    
    user@machine:~$ bash ampliconseqCommands.sh