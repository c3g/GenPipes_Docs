The `Canadian Centre for Computational Genomics <https://www.computationalgenomics.ca>`_ (C3G) in partnership with the `Alliance Canada <https://docs.alliancecan.ca/wiki/Technical_documentation>`_, allows researchers to access hundreds of bioinformatics :ref:`tools and modules<doc_cvmfs_modules>` pre-installed on several HPC centres including Beluga, Niagara, Cedar and Graham. 

.. _gp_avl_modules:

Use the following command to explore the available tools:

::

  module avail mugqic/

.. dropdown:: Available Modules

  .. include:: /common/gp_avl_module_current_ver.inc

Use the following command to load any of the available tools:

::

  # module add mugqic/<tool>/<version>
  module add mugqic/samtools/1.4.1
 
  # Now samtools 1.4.1 is available to use. To check:
  samtools

Use the following command to check available GenPipes versions pre-installed on the server:

:: 

  module avail genpipes