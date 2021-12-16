.. _docs_troubleshooting_rt_fatal_err_star_rnaseq_option:

Fatal Limit Error: Star RNA Sequencing
---------------------------------------

When you issue the RNA sequencing GenPipes pipeline with Star option commands, the jobs fails with the fatal limit error:

::

  Fatal LIMIT error: the number of junctions to be inserted on the fly =2663181 is larger than the limitSjdbInsertNsj=1000000
  Fatal LIMIT error: the number of junctions to be inserted on the fly =2663181 is larger than the limitSjdbInsertNsj=1000000
  SOLUTION: re-run with at least --limitSjdbInsertNsj 2663181

  Nov 29 14:10:58 ...... FATAL ERROR, exiting
  MUGQICexitStatus:104

It is not clear from the error message where this solution configuration option needs to be specified.

Typically, the Star index options in the ```.ini``` file supplied for RNA sequencing protocol do not show ```--limitSjdbInsertNsj``` option.

::

  [star_index]

  ram = 191000M
  io_buffer = 1G
  threads = 20
  cluster_cpu = -N 1 -c 40
  cluster_walltime = --time=15:00:0
  cluster_queue = --mem-per-cpu=4775M
  star_cycle_number = 99

**Fix**

The correct way to specify this option is using ```--other-option``` flag as shown in the snippet from ```.ini``` file below:

::

    [star_index]

    ram = 191000M
    io_buffer = 1G
    threads = 20
    cluster_cpu = -N 1 -c 40
    cluster_walltime = --time=15:00:0
    cluster_queue = --mem-per-cpu=4775M
    star_cycle_number = 99
    other_options =--limitSjdbInsertNsj  2500000
