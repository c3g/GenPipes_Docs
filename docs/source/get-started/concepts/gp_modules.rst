:orphan:

.. _docs_gp_modules:

GenPipes Modules
================

GenPipes gives you access to hundreds of bioinformatics `tools and modules <https://www.computationalgenomics.ca/cvmfs-modules/>`_ pre-installed by our team. To explore the available tools, you can type the following command:

::

  module avail mugqic/

This will allow you to use bioinformatics tools like Samtools, Homer, MACS2, without installing them yourself.

You can load them as follows:

::

  # module add mugqic/<tool>/<version>
  module add mugqic/samtools/1.4.1
 
  # Now samtools 1.4.1 is available to use. To check:
  samtools

.. _gp_avl_modules:

To see what modules are available with pre-installed GenPipes, you can run the following command:

::
  
  module avail mugqic/

Or, you can visit `Bioinformatics Resources <https://www.computationalgenomics.ca/cvmfs-modules/>`_ site for a list of available GenPipes modules or see `sources here <https://bitbucket.org/mugqic/genpipes/src/master/resources/modules/>`_.

.. _gp_why_modules:

*Modules* are a way to load software or tools when we need them.

Every time a computer runs a command (example “ls”), it needs to find the instructions to do so. It looks for the instructions in places listed in a variable called the ”$PATH”. Every time you install a new tool, you need to add its location to your $PATH. Every time you issue a command (like ls), the computer will search through all the places listed in the $PATH to find the instructions on what to do.

Imagine, for servers that have thousands of users, each in need of several software, how long the PATH can get and how much that can slow down the system!
To avoid this, installed software is packaged in “modules” that you can be loaded when needed. The software is installed on the computer but the computer is not aware of it until you “load”” the module, which adds the software location to the $PATH.

To see what is in your $PATH, use the following command:


:: 

  echo $PATH

To see where the instructions of a command are stored, you can use which command as shown below:

::

   which ls

For ls, the instruction are usually stored in:
 
::

   /bin/ls
