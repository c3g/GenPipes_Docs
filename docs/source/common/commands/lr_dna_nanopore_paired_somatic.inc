.. parsed-literal::

    genpipes longread_dnaseq -t nanopore_paired_somatic \\
    -c $GENPIPES_INIS/longread/longread.base.ini \\
       $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini \\
       $GENPIPES_INIS/longread/longread_dnaseq.cancer.ini \\
    -r /cvmfs/soft.mugqic/root/testdata/nanopore/readset.nanopore.txt \\
    -o nanopore -g longread_nanopore_cmd.sh

    bash longread_nanopore_cmd.sh