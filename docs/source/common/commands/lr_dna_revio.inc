.. parsed-literal::

    genpipes longread_dnaseq -t revio \\
        -c $GENPIPES_INIS/longread/longread.base.ini \\
        $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
        -r /cvmfs/soft.mugqic/root/testdata/longread_dnaseq/readset.revio.txt \\
        -o revio -g longread_revio_cmd.sh

    bash longread_revio_cmd.sh