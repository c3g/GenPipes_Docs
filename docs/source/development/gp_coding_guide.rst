:orphan:

.. _docs_gp_coding_guide:

.. spelling::

       bfx
       dnaseq

GenPipes Coding Guidelines
==========================

.. note::

       The following document is based on basic information available in the GenPipes source file `coding standards.txt <https://bitbucket.org/mugqic/genpipes/src/master/README-GenAP_coding_standards.txt>`_.  In future, this may be updated to help open source community to contribute to GenPipes sources.

.. contents:: :local:

General
-------

Any code that is added or modified in GenPipes sources must be clear, readable and well documented with meaningful comments.

Indentation
------------

Use 4 space indentation instead of tabs.

Wrappers vs. Command Line
--------------------------

Useful methods should be written in common script files (e.g. as a python script within the bfx/ folder, or as a new method within pipeline/common.py) : no command-line should be hard-coded within a pipeline python wrapper (e.g. within dnaseq.py).  When a command has to be implemented, the developer has to wrap it as a method in a python script (e.g. pipelines/common.py or bfx/picard.py). Methods should be made as general as possible with the possibility of adding command line options, with the uses of the configuration .ini files, in order to make them usable across pipelines.

Command Line format
-------------------

When coding commands, a single command should be divided across different lines (\) with every parameter on a line to enhance code readability. Also, each line should be preceded by 2 space characters, except for the first line of the command.

For example,

::

  motifMaker.sh find \\
    -f {fasta_consensus} \\
    -g {output_gff} \\
    -o {output}

Use of modules
---------------

All software calls should be done using the module system. Modules should be specified within the .ini file(s). Preferably use the mugqic modules which hare distributed among the `Digital Research Alliance of Canada <https://alliancecan.ca/en>`_ (formerly Compute Canada) HPC clusters, this ensures stability of the analysis and reproducibility of the results. If using a non-mugqic module, ensure that the module is available on all the cluster. Avoid system modules which are not be transferable across different platforms.

Pipeline Development
---------------------

Bitbucket tickets are usually created for each pipeline development, where benchmarking parameters and other decisions made can be logged for later reference.
Code is always developed on a branch, i.e. try as much as possible to not edit the master branch directly. Once code is ready to be merged, a pull request is created. After being reviewed by at least two developers on the team (if possible, developers have to be uninvolved in the reviewed project), and after all the reviewer comments and inquiries have been addressed and accepted, the development branch can then be merged to master.

Transferability
---------------

Pipelines should be transferable to a host of other clusters; so keep that in mind as you write your code.
