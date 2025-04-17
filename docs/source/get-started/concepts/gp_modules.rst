:orphan:

.. _docs_gp_modules:

GenPipes Modules
================

The `Canadian Centre for Computational Genomics <https://www.computationalgenomics.ca>`_ (C3G) in partnership with the `Alliance Canada <https://docs.alliancecan.ca/wiki/Technical_documentation>`_, allows researchers to access hundreds of bioinformatics `tools and modules <https://docs.alliancecan.ca/wiki/Available_software#List_of_globally-installed_modules/>`_ pre-installed on several HPC centres including Beluga, Niagara, Cedar and Graham. 

.. _gp_avl_modules:

Use the following command to explore the available tools:

::

  module avail mugqic/

Use the following command to load any of the available tools:

::

  # module add mugqic/<tool>/<version>
  module add mugqic/samtools/1.4.1
 
  # Now samtools 1.4.1 is available to use. To check:
  samtools

Use the following command to check available GenPipes versions pre-installed on the server:

:: 

  module avail genpipes

.. _gp_avl_genomes:

To see what genomes are available with pre-installed GenPipes, you can run the following command:

::
  
  ls $MUGQIC_INSTALL_HOME/genomes/species/

Or, you can visit `Bioinformatics Resources <https://computationalgenomics.ca/cvmfs-genome/>`_ site for a list of available genomes. The genome list is also available at `GenPipes GitHub repository <https://github.com/c3g/GenPipes/tree/main/resources/genomes>`_.
