.. parsed-literal::

    genpipes covseq -c $GENPIPES_INIS/covseq/covseq.base.ini \\
      $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
      $GENPIPES_INIS/covseq/ARTIC_v4.1.ini \\
      -r readset.covseq.txt -g covseqCommands_mugqic.sh

    bash covseqCommands_mugqic.sh