:orphan:

.. _docs_available_pipelines:

.. spelling:word-list::

   SARS-COV-2
   COV
   fastpass
   germline_high_cov
   germline
   cov

Available Pipelines
===================

.. list-table:: 
   :header-rows: 1
   :widths: auto
   :class: table-responsive

   * - Genomic Analysis
     - ``genpipes <command_name>``
     - Protocol Options
   * - ChIP Sequencing
     - :ref:`chipseq <docs_gp_chipseq>`
     -  *None*
   * - RNA Sequencing
     - :ref:`rnaseq <docs_gp_rnaseq>`
     - | ``-t chipseq (default)`` or
       | ``-t atacseq``
   * - | RNA Sequencing 
       | Light
     - :ref:`rnaseq_light <docs_gp_rnaseqlight>`
     -  *None*
   * - | Denovo RNA 
       | Sequencing
     - :ref:`rnaseq_denovo_assembly <docs_gp_rnaseq_denovo>`
     - | ``-t trinity (default)`` or
       | ``-t seq2fun``
   * - | Whole Genome 
       | Sequencing
     - :ref:`dnaseq <docs_gp_dnaseq>`
     - | :code:`-t germline_snv` (default) or
       | ``-t germline_sv``
   * - Exome Sequencing
     - :ref:`dnaseq <docs_gp_dnaseq>`
     - |capture|
   * - | Deep Whole Genome
       | Sequencing
     - :ref:`dnaseq <docs_gp_dnaseq>`
     - | |ini_file|
       | |germline_option|
   * - | Deep Exome 
       | Sequencing
     - :ref:`dnaseq <docs_gp_dnaseq>`
     - |capture|
   * - | Whole Genome 
       | Methyl Sequencing
     - :ref:`methylseq <docs_methylation>`
     - | :code:`bismark` (default) or
       | ``-t gembs`` or
       | ``-t hybrid`` or
       | ``-t dragen`` or
   * - | Capture Methyl 
       | Sequencing
     - :ref:`methylseq <docs_methylation>`
     - |capture| 
   * - Cancer Analysis
     - :ref:`dnaseq <docs_gp_dnaseq>`
     - | |somatic1|
       | |somatic2|
       | |somatic3|
       | |somatic4|
   * - | Long-Reads Whole
       | Genome Sequencing
     - :ref:`longread_dnaseq <docs_gp_longread_dnaseq>`
     - | |lr_flags1|
       | |lr_flags2|
       | |lr_flags3|
       | 
       | (**Note** ``-t nanopore_paired_somatic`` option 
       | also requires -p *pair_file_name*)
   * - Meta Genomics
     - :ref:`ampliconseq  <docs_gp_ampliconseq>`
     -  *None*
   * - | SARS-COV-2
       | Analysis
     - :ref:`covseq <docs_gp_covseq>`
     -  *None* 

.. |capture| replace:: capture :ref:`BED file<docs_bed_file>` in Readset file or ``ini`` file 
.. |ini_file| replace:: use relevant ``ini`` file
.. |germline_option| replace:: and ``-t germline_high_cov``
.. |somatic1| replace:: ``-t somatic_ensemble`` or  
.. |somatic2| replace:: ``-t somatic_sv`` or
.. |somatic3| replace:: ``-t somatic_fastpass`` or
.. |somatic4| replace:: ``-t somatic_tumor_only`` 
.. |lr_flags1| replace:: ``-t nanopore`` or  
.. |lr_flags2| replace:: ``-t nanopore_paired_somatic`` or 
.. |lr_flags3| replace:: ``-t revio`` 