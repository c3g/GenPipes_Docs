.. _docs_troubleshooting_rt_err_qsub_cmd:

Error: qsub command not found
------------------------------

While running a pipeline using specific configuration file, the command text file is generated successfully. However, when the user tries to run the commands using:

::

  bash <command-file.txt>

the following error shows up:

*qsub: command not found*

.. image:: /img/error/get_st_err1a.png

.. image:: /img/error/get_st_err1b.png

**Fix**

Check the kind of GenPipes deployment you are working with.  If it is a local deployment, on a bare metal server or a virtual server or in a container, you need to make sure you do not specify -j pbs or -j slurm option but -j daemon or -j batch mode.

In case you are using moab or torque scheduler, ensure that you use -j pbs option in the pipeline command. If you are using mp2b or cedar server, then you need to specify -j slurm as the scheduler option and use the correct configuration file (mp2b.ini or cedar.ini) depending upon which server you are using to run your pipeline jobs.
