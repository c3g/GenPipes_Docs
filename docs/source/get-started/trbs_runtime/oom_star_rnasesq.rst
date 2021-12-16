.. _docs_troubleshooting_rt_oom_star_rnaseq:

Error: RNA Sequencing Star alignment - Out of Memory
-----------------------------------------------------

For first time users, it has been observed (see example in `Google GenPipes Forum <https://groups.google.com/forum/#!topic/GenPipes/EC2VeLz3i0Y>`_) that the RNA Sequencing pipeline command execution stops after STAR alignment 1.  

**Fix**

try to change the STAR parameters in your ini files to something like in the .ini files of the master branch:

::

  https://bitbucket.org/mugqic/mugqic_pipelines/src/master

The problem should be solved by setting io_buffer to a higher value like 1G or 4G. The command you show indicates you are using 8M.

At some point io_buffer was decreased in the template .ini but this exposed a bug in STAR where a negative memory allocation is attempted.
