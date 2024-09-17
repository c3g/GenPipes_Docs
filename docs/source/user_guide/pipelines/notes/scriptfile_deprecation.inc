.. caution::

     It is recommended that you use the ``-g GENPIPES_CMD.sh`` option instead of redirecting the output of the pipeline command to a file via ``> GENPIPES_CMD.sh``.

     |:white_check_mark:|  

     ::

       genpipes [pipeline] [options] -g genpipes_cmd.sh

       bash genpipes_cmd.sh

     |:stop_sign:|  

     :: 

       genpipes [pipeline] [options] > genpipes_cmd.sh 

       bash genpies_cmd.sh

     The ``> scriptfile`` method is supported but **will be deprecated** in a future GenPipes release.
       

.. This is a comment - Issue #206 fix removing duplicate beluga tip
.. ..include:: /common/gp_cluster_ini.inc
