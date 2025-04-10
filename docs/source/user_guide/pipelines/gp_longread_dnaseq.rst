.. _docs_gp_longread_dnaseq:

.. spelling:word-list:: 
 
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

Long Read DNA Sequencing Pipeline
==================================

:bdg-primary:`Version` |genpipes_version|

.. dropdown:: :material-outlined:`notifications_active;2em` v6.0.0 Update! 
   :color: success
   :open:

   The **GenPipes v6.x** release introduces the new Long Read DNA Sequencing Pipeline. It supports two protocols, Nanopore and Revio. 

.. _ref_docs_gp_nanopore:

   .. note::
      
      The Nanopore protocol offers the same sequencing pipeline that was earlier available as the Nanopore sequencing pipeline in the previous GenPipes releases (v5.x or older).

.. tab-set:: 

      .. tab-item:: Usage

         .. dropdown:: Command
            :open:

            .. code::

                 genpipes longread_dnaseq [-options ] [--genpipes_file GENPIPES_FILE.sh]
                 bash GENPIPES_FILE.sh

         .. dropdown:: Options

            .. include:: opt_longread_dnaseq.inc
            .. include:: /common/gp_readset_opt.inc
            .. include:: /common/gp_common_opt.inc

         .. dropdown:: Example

            .. dropdown:: Nanopore

               .. include::  /user_guide/pipelines/example_runs/lr_nanopore.inc

            .. dropdown:: Revio

               .. include::  /user_guide/pipelines/example_runs/lr_revio.inc

            .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

            .. card:: Test Dataset
               :link: docs_testdatasets
               :link-type: ref

               Use the :ref:`Long Read DNA sequencing test dataset <docs_testdatasets>` for this pipeline.

      .. tab-item:: Schema
         :name: lrdnaschema  

         .. dropdown:: Nanopore 
            
            The following figure shows the schema for Nanopore sequencing pipeline:

            .. figure:: /img/pipelines/mmd/nanopore.mmd.png
               :align: center
               :alt: nanopore schema 
               :width: 80%
               :figwidth: 95%

               Figure: Schema of Nanopore Long Read DNA Sequencing Protocol

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: dada2 ampseq
               :width: 100%
               :figwidth: 75%

         .. dropdown:: Revio 
            
            The following figure shows the schema for Revio Long Read DNA Sequencing Protocol:

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

         +----+------------------------------------+-------------------------------+
         |    | Nanopore                           | Revio                         |
         +====+====================================+===============================+
         | 1. | |blastqc|                          | |metrics_nanoplot|            |
         +----+------------------------------------+-------------------------------+
         | 2. | |minimap2_align|                   | |pbmm2_align|                 |
         +----+------------------------------------+-------------------------------+
         | 3. | |pycoqc|                           | |picard_merge_sam_files|      |
         +----+------------------------------------+-------------------------------+
         | 4. | |picard_merge_sam_files|           | |metrics_mosdepth|            |
         +----+------------------------------------+-------------------------------+
         | 5. | |svim|                             | |set_deepvariant_regions|     |
         +----+------------------------------------+-------------------------------+
         | 6. |                                    | |deepvariant_vc|              |
         +----+                                    +-------------------------------+
         | 7. |                                    | |merge_filter_deepvariant|    |
         +----+                                    +-------------------------------+
         | 8. |                                    | |hificnv|                     |
         +----+                                    +-------------------------------+
         | 9. |                                    | |trgt_genotyping|             |
         +----+                                    +-------------------------------+
         | 10.|                                    | |sawfish|                     |
         +----+                                    +-------------------------------+
         | 11.|                                    | |annotSV|                     |
         +----+                                    +-------------------------------+
         | 12.|                                    | |hiphase|                     |
         +----+                                    +-------------------------------+
         | 13.|                                    | |report_cpsr|                 |
         +----+                                    +-------------------------------+
         | 14.|                                    | |multiqc|                     |
         +----+------------------------------------+-------------------------------+
  
         .. card::

            .. include:: steps_longread_dnaseq.inc

      .. tab-item:: About

         .. card::

            Over the past decade, `long-read`, single-molecule DNA sequencing technologies have emerged as powerful players in genomics. With the ability to generate reads tens to thousands of kilobases in length with an accuracy approaching that of short-read sequencing technologies, these platforms have proven their ability to resolve some of the most challenging regions of the human genome, detect previously inaccessible structural variants, and generate some of the first telomere-to-telomere assemblies of whole chromosomes.
                        
            The LongRead Pipeline is used to analyse long reads produced by the Oxford Nanopore Technologies (ONT) and PacBio Revio sequencers. It supports the following protocols:
            
            * Nanopore
            * Revio
            
            Both protocols require a :ref:`readset file as input <docs_readset_file>`. The :ref:`readset file for the Long Read DNA Seq pipeline<ref_example_longread_dnaseq_readset_file>` has a specific structure and format containing the sample metadata and paths to input data (FASTQ, FAST5 or BAM).

            **Nanopore**

            The Nanopore protocol of the pipeline uses minimap2 to align reads to the reference genome. Additionally, it produces a QC report that includes an interactive dashboard with data from the basecalling summary file as well as the alignment. A step aligning random reads to the NCBI nt database and reporting the species of the highest hits is also done as QC.

            Once the QC and alignments have been produced, Picard is used to merge readsets coming from the same
            sample. Finally, SVIM is used to detect Structural Variants (SV) including deletions, insertions and
            translocations. 
            
            For a full summary of the types of SVs detected, refer to this `site <https://github.com/eldariont/svim#background-on-structural-variants-and-long-reads>`_.

            The SV calls produced by SVIM are saved as VCFs for each sample, which can then be used in downstream
            analyses. No filtering is performed on the SV calls.

            This pipeline currently does not perform base calling and requires both FASTQ and a sequencing_summary
            file produced by a ONT supported basecaller (we recommend Guppy). Additionally, the testing and
            development of the pipeline were focused on genomics applications, and functionality has not been tested
            for transcriptomics or epigenomics datasets.

            For more information on using ONT data for structural variant detection, as well as an alternative
            approach, refer to `Structural Variant Pipeline GitHub repository <https://github.com/nanoporetech/pipeline-structural-variation>`_.

            **Revio**

            The Revio protocol uses `pbmm2`_ to align reads to the reference genome, followed by variant calling with DeepVariant
            and structural variant calling with HiFiCNV, TRGT, and Sawfish. Variants are annotated with AnnotSV and phased
            with HiPhase. A CPSR report can be produced from the phased variants. Metrics on the raw and mapped reads are
            collected with NanoPlot and mosdepth, respectively. 

            See :ref:`lrdnaschema` tab for the pipeline workflow. For the latest implementation and usage details refer to the Long Read DNA Sequencing implementation `README.md <https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/longread_dnaseq/README.md>`_ file.

            **References**

            * `Evaluating nanopore sequencing data processing pipelines for structural variation identification <https://genomebiology.biomedcentral.com/articles/10.1186/s13059-019-1858-1>`_.
            * `Minimap2`_: Pairwise alignment for nucleotide sequences.
            * `Basecalling using Guppy <https://timkahlke.github.io/LongRead_tutorials/BS_G.html>`_.

.. The following are replacement texts used in this file

.. |blastqc| replace:: `BlastQC`_
.. |minimap2_align| replace:: `Minimap2 Align`_
.. |pycoqc| replace:: `pycoQC`_
.. |picard_merge_sam_files| replace:: `Picard Merge SAM Files`_
.. |svim| replace:: `Structural Variant Identification using Mapped Long Reads`_
.. |metrics_nanoplot| replace:: `Metrics Nanoplot`_
.. |pbmm2_align| replace:: `pbmm2 Align`_
.. |metrics_mosdepth| replace:: `Metrics Mosdepth`_
.. |set_deepvariant_regions| replace:: `Set DeepVariant Regions`_
.. |deepvariant_vc| replace:: `DeepVariant Germline VC`_
.. |merge_filter_deepvariant| replace:: `Merge Filter Deepvariant`_
.. |hificnv| replace:: `HiFi CNV`_
.. |trgt_genotyping| replace:: `Target Genotyping`_
.. |sawfish| replace:: `Sawfish`_
.. |annotSV| replace:: `Annotate SV`_
.. |hiphase| replace:: `Hi Phase`_
.. |report_cpsr| replace:: `Report CPSR`_
.. |multiqc| replace:: `MultiQC`_

.. The following are html links used in this text

.. _Oxford Nanopore Technologies (ONT): https://academic.oup.com/clinchem/article/61/1/25/5611478 
.. _Minimap2 aligner: https://github.com/lh3/minimap2
.. _Minimap2: https://academic.oup.com/bioinformatics/article/34/18/3094/4994778
.. _NCBI nucleotide: https://www.ncbi.nlm.nih.gov/nucleotide/
.. _Guppy: https://bio.tools/guppy
.. _pbmm2: https://github.com/PacificBiosciences/pbmm2
