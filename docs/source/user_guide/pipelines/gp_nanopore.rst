.. _docs_gp_nanopore:

.. spelling::

     Nanopore
     phenotypic
     basecalling
     translocations
     basecaller
     bp
     mRNA
     Minimap
     minimap
     transcriptomic
     epigenomic

Nanopore Pipeline
==================

:bdg-primary:`Version` |genpipes_version|

.. tab-set:: 

      .. tab-item:: Usage

         .. dropdown:: Command
            :open:

            .. code::

               genpipes nanopore [options] [--genpipes_file GENPIPES_FILE.sh]
               bash GENPIPES_FILE.sh

         .. dropdown:: Options

            .. include:: /common/gp_readset_opt.inc
            .. include:: /common/gp_common_opt.inc

         .. dropdown:: Example

            .. include::  /user_guide/pipelines/example_runs/nanopore.inc
            .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

            .. card:: Test Dataset
               :link: docs_testdatasets
               :link-type: ref

               You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.


      .. tab-item:: Schema
         :name: nanoschema  

         The following figure shows the schema for Nanopore sequencing pipeline:

          .. figure:: /img/pipelines/mmd/nanopore.mmd.png
             :align: center
             :alt: nanopore schema 
             :width: 80%
             :figwidth: 95%

             Figure: Schema of Nanopore Sequencing protocol

          .. figure:: /img/pipelines/mmd/legend.mmd.png
             :align: center
             :alt: dada2 ampseq
             :width: 100%
             :figwidth: 75%

      .. tab-item:: Steps

         +----+-------------------------------------------+
         |    |  *Nanopore Sequencing Steps*              |
         +====+===========================================+
         | 1. | |blastqc|                                 |
         +----+-------------------------------------------+
         | 2. | |minimap2_align|                          |
         +----+-------------------------------------------+
         | 3. | |pycoqc|                                  |
         +----+-------------------------------------------+
         | 4. | |picard_merge_sam_files|                  |
         +----+-------------------------------------------+
         | 5. | |svim|                                    |
         +----+-------------------------------------------+

         .. card::

            .. include:: steps_nanopore.inc

      .. tab-item:: About

         .. card::

            Structural Variations (SV) are genomic alterations including insertions, deletions, duplications, inversions, and translocation. They account for approximately 1% of the differences among human genomes and play a significant role in phenotypic variation and disease susceptibility.

            Nanopore sequencing technology can generate long sequence reads and provides more accurate SV identification in terms of both sequencing and data analysis. For SV analysis, several new aligners and SV callers have been developed to leverage the long-read sequencing data. Assembly based approaches can also be used for SV identification. `Minimap2`_ aligner offers high speed and relatively balanced performance for calling both insertions as well as deletions.

            The Nanopore is used to analyze long reads produced by the `Oxford Nanopore Technologies (ONT)`_ sequencers. Currently, the pipeline uses `Minimap2`_ to align reads to the reference genome. Additionally, it produces a QC report that includes an interactive dashboard for each readset with data from the basecalling summary file as well as the alignment. A step aligning random reads to the `NCBI nucleotide`_ database and reporting the species of the highest hits is also done as QC.

            Once the QC and alignments have been produced, Picard is used to merge readsets coming from the same sample. Finally, SVIM is used to detect Structural Variants (SV) including deletions, insertions and translocations. For a full summary of the types of SVs detected, please consult the following `site <https://github.com/eldariont/svim#background-on-structural-variants-and-long-reads>`_.

            The SV calls produced by SVIM are saved as VCFs for each sample, which can then be used in downstream analyses. No filtering is performed on the SV calls.

            This pipeline currently does not perform base calling and requires both FASTQ and a sequencing_summary file produced by a ONT supported basecaller (we recommend `Guppy`_). Additionally, the testing and development of the pipeline were focused on genomics applications, and functionality has not been tested for transcriptomic or epigenomic datasets. Beyond the QC dashboards for each readset, there is currently no implemented reporting step in this pipeline.

            For more information on using ONT data for structural variant detection, as well as an alternative approach, please consult `Oxford Nanopore Technologies SV Pipeline GitHub repository <https://github.com/nanoporetech/pipeline-structural-variation>`_.

            **References**

            * `Evaluating nanopore sequencing data processing pipelines for structural variation identification <https://genomebiology.biomedcentral.com/articles/10.1186/s13059-019-1858-1>`_.
            * `Minimap2`_: Pairwise alignment for nucleotide sequences.
            * `Basecalling using Guppy <https://timkahlke.github.io/LongRead_tutorials/BS_G.html>`_.

.. include::  /user_guide/pipelines/example_runs/nanopore-readset.inc

.. Following are the replacement texts used in the content above

.. |blastqc| replace:: `BlastQC`_
.. |minimap2_align| replace:: `Minimap2 Align`_
.. |pycoqc| replace:: `pycoQC`_
.. |picard_merge_sam_files| replace:: `Picard Merge SAM Files`_
.. |svim| replace:: `Structural Variant Identification using Mapped Long Reads`_

.. Following are the html links used in this text

.. _Oxford Nanopore Technologies (ONT): https://academic.oup.com/clinchem/article/61/1/25/5611478 
.. _Minimap2 aligner: https://github.com/lh3/minimap2
.. _Minimap2: https://academic.oup.com/bioinformatics/article/34/18/3094/4994778
.. _NCBI nucleotide: https://www.ncbi.nlm.nih.gov/nucleotide/
.. _Guppy: https://bio.tools/guppy
