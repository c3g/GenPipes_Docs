.. parsed-literal::

  genpipes dnaseq -t germline_snv -c $GENPIPES_INIS/dnaseq/dnaseq.base.ini \\
    $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
    -r readset.dnaseq.txt \\
    -s 1-27 -j slurm -g dnaseq_germline_snv_cmd.sh

  bash dnaseq_germline_snv_cmd.sh