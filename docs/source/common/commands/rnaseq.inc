.. parsed-literal::
    
    user@machine:~$ genpipes rnaseq -c $GENPIPES_INIS/rnaseq/rnaseq.base.ini \\
                                        $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
                                    -r readset.rnaseq.txt \\
                                    -d design.rnaseq.txt \\
                                    -s 1-21 \\
                                    -g rnaseqCommands.sh

    user@machine:~$ bash rnaseqCommands.sh