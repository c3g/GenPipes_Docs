.. _docs_faq_c3g_res:

C3G Resource Usage
------------------

.. contents::
  :local:
  :depth: 1

----

Where can I find more details on CCDB servers, file system, usage guidelines?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

You can visit `Compute Canada Wiki <https://docs.computecanada.ca/wiki/Compute_Canada_Documentation>`_ to learn more about the list of Compute Canada Servers, systems and services available, How-to guides and usage policy.

Is there a list of software installed on Compute Canada servers?
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

See list of `available software <https://docs.computecanada.ca/wiki/Available_software>`_ and globally deployed modules on Compute Canada servers.

What are modules and why do we need them for GenPipes?
++++++++++++++++++++++++++++++++++++++++++++++++++++++

GenPipes is developed in Python. Modules in Python are a way to load software or tools just in time, when a program needs them.

The modules that come along with GenPipes allow you to use bioinformatics tools like Samtools, Homer, MACS2, without installing them yourself.

For details on why we need modules for GenPipes and which ones are required, deployed and p
re-installed on Compute Canada Servers, see :ref:`docs_gp_modules`.

What are GenPipes genomes? Where can I access them from?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GenPipes pipelines are used for genomic analysis and they require reference genomes. C3G, in partnership with Compute Canada, maintains several genomes that are available on several HPC centres including Beluga, Cedar and others. In addition to the fasta sequence, many genomes include aligner indices and annotation files. 

To access these genomes, you need to add the following lines to your .bashrc file:

::

  ## GenPipes/MUGQIC genomes and modules
  export MUGQIC_INSTALL_HOME=/cvmfs/soft.mugqic/CentOS6

To explore the available genomes, you can type:

::

  ls $MUGQIC_INSTALL_HOME/genomes/species/

For a list of available genomes, visit `Bioinformatics resources - genomes <https://www.computationalgenomics.ca/cvmfs-genomes/>`_ and see `sources here <https://bitbucket.org/mugqic/genpipes/src/master/resources/genomes/>`_.

What is meant by test dataset? Where can I find available test datasets?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GenPipes pipelines can be run using your sequencing instruments generated, measured, sampled read datasets in respective formats as required by individual pipelines or test datasets.  Refer to :ref:`GenPipes Test Datasets<docs_testdatasets>` for various available test datasets that can be used to run various GenPipes pipelines, in case you don't have your own dataset to be processed.

----

~      
