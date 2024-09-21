.. _docs_methylation:

.. spelling::

     epigenetic
     methylome
     Cytosine
     cytosines
     CpG
     mappability 

Methylation Sequencing Pipeline
===============================

:bdg-primary:`Version` |genpipes_version|

.. tab-set:: 

      .. tab-item:: Usage

         .. dropdown:: Command
            :open:

            .. code::

               genpipes methylseq [options] [--genpipes_file GENPIPES_FILE.sh]
               bash GENPIPES_FILE.sh

         .. dropdown:: Options

            .. The design option in methylseq is not supported hence not included below

            .. include:: opt_methylseq.inc
            .. include:: /common/gp_readset_opt.inc
            .. include:: /common/gp_common_opt.inc

         .. dropdown:: Example

            .. include::  /user_guide/pipelines/example_runs/methylseq.inc

            .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

            .. card:: Test Dataset
               :link: docs_testdatasets
               :link-type: ref

               You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

      .. tab-item:: Schema
         :name: methschema    

         .. dropdown:: Bismark

            .. figure:: /img/pipelines/mmd/methylseq.mmd.png
               :align: center
               :alt: methylation_seq 
               :width: 100%
               :figwidth: 95%

               Figure: Methylation Sequencing (Bismark)

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: legend
               :width: 100%
               :figwidth: 75%

         .. dropdown:: Gembs

            .. figure:: /img/pipelines/mmd/methylseq.gembs.mmd.png
               :align: center
               :alt: methylation_seq 
               :width: 100%
               :figwidth: 95%

               Figure: Methylation Sequencing (GemBS)

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: legend
               :width: 100%
               :figwidth: 75%

         .. dropdown:: Hybrid

            .. figure:: /img/pipelines/mmd/methylseq.hybrid.mmd.png
               :align: center
               :alt: methylation_seq hybrid 
               :width: 100%
               :figwidth: 95%

               Figure: Methylation Sequencing (Hybrid)

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: legend
               :width: 100%
               :figwidth: 75%           

            .. include:: opt_methylseq_dragen_warning.inc    

         .. dropdown:: Dragen

            .. figure:: /img/pipelines/mmd/methylseq.dragen.mmd.png
               :align: center
               :alt: methylation_seq dragen 
               :width: 100%
               :figwidth: 95%

               Figure: Methylation Sequencing (Dragen)

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: legend
               :width: 100%
               :figwidth: 75%           

            .. include:: opt_methylseq_dragen_warning.inc 

      .. tab-item:: Steps

         .. include:: opt_methylseq_dragen_warning.inc    

         .. dropdown:: Bismark
            
            +----+---------------------------------+
            |    |  *Bismark*                      |
            +====+=================================+
            | 1. | |picard_sam_to_fastq|           |
            +----+---------------------------------+
            | 2. | |trimmomatic|                   |
            +----+---------------------------------+
            | 3. | |merge_trimmomatic_stats|       |
            +----+---------------------------------+
            | 4. | |bismark_align|                 |
            +----+---------------------------------+
            | 5. | |add_bam_umi|                   |
            +----+---------------------------------+
            | 6. | |sambamba_merge_sam_files|      |
            +----+---------------------------------+
            | 7. | |picard_remove_duplicates|      |
            +----+---------------------------------+
            | 8. | |metrics|                       |
            +----+---------------------------------+
            | 9. | |methylation_call|              |
            +----+---------------------------------+
            | 10.| |wiggle_tracks|                 |
            +----+---------------------------------+
            | 11.| |methylation_profile|           |
            +----+---------------------------------+
            | 12.| |ihec_sample_metrics_report|    |
            +----+---------------------------------+
            | 13.| |bis_snp|                       |
            +----+---------------------------------+
            | 14.| |filter_snp_cpg|                |
            +----+---------------------------------+
            | 15.| |prepare_methylkit|             |
            +----+---------------------------------+
            | 16.| |methylkit_diff_analysis|       |
            +----+---------------------------------+
            | 17.| |multi_QC|                      |
            +----+---------------------------------+
            | 18.| |cram_output|                   |
            +----+---------------------------------+

         .. dropdown:: Gembs

            +----+---------------------------------+
            |    |  *Gembs*                        |
            +====+=================================+
            | 1. | |picard_sam_to_fastq|           |
            +----+---------------------------------+
            | 2. | |trimmomatic|                   |
            +----+---------------------------------+
            | 3. | |merge_trimmomatic_stats|       |
            +----+---------------------------------+
            | 4. | |gembs_prepare|                 |
            +----+---------------------------------+
            | 5. | |gembs_map|                     |
            +----+---------------------------------+
            | 6. | |picard_remove_duplicates|      |
            +----+---------------------------------+
            | 7. | |metrics|                       |
            +----+---------------------------------+
            | 8. | |gembs_call|                    |
            +----+---------------------------------+
            | 9. | |gembs_bcf_to_vcf|              |
            +----+---------------------------------+
            | 10. | |gembs_format_cpg_report|      |
            +----+---------------------------------+
            | 11.| |methylation_profile|           |
            +----+---------------------------------+
            | 12. | |dragen_bedgraph|              |
            +----+---------------------------------+
            | 13.| |wiggle_tracks|                 |
            +----+---------------------------------+
            | 14.| |ihec_sample_metrics_report|    |
            +----+---------------------------------+
            | 15.| |gembs_report|                  |
            +----+---------------------------------+
            | 16.| |filter_snp_cpg|                |
            +----+---------------------------------+
            | 17.| |prepare_methylkit|             |
            +----+---------------------------------+
            | 18.| |methylkit_diff_analysis|       |
            +----+---------------------------------+
            | 19.| |multi_QC|                      |
            +----+---------------------------------+
            | 20.| |cram_output|                   |
            +----+---------------------------------+

         .. dropdown:: Hybrid

            +----+----------------------------------+
            |    |            *Hybrid*              |         
            +====+==================================+
            | 1. | |picard_sam_to_fastq|            |           
            +----+----------------------------------+
            | 2. | |trimmomatic|                    |      
            +----+----------------------------------+
            | 3. | |merge_trimmomatic_stats|        | 
            +----+----------------------------------+
            | 4. | |dragen_align|                   |
            +----+----------------------------------+
            | 5. | |add_bam_umi|                    |
            +----+----------------------------------+
            | 6. | |sambamba_merge_sam_files|       |
            +----+----------------------------------+
            | 7. | |picard_remove_duplicates|       |
            +----+----------------------------------+
            | 8. | |metrics|                        |
            +----+----------------------------------+
            | 9. | |methylation_call|               |
            +----+----------------------------------+
            | 10.| |wiggle_tracks|                  |
            +----+----------------------------------+
            | 11.| |methylation_profile|            |
            +----+----------------------------------+
            | 12.| |ihec_sample_metrics_report|     |
            +----+----------------------------------+
            | 13.| |bis_snp|                        |
            +----+----------------------------------+
            | 14.| |filter_snp_cpg|                 |
            +----+----------------------------------+
            | 15.| |prepare_methylkit|              |
            +----+----------------------------------+
            | 16.| |methylkit_diff_analysis|        |
            +----+----------------------------------+
            | 17.| |multi_QC|                       |
            +----+----------------------------------+
            | 18.| |cram_output|                    |
            +----+----------------------------------+
         
         .. dropdown:: Dragen

            +----+-----------------------------------+
            |    |              *Dragen*             |         
            +====+===================================+
            | 1. | |picard_sam_to_fastq|             |           
            +----+-----------------------------------+
            | 2. | |trimmomatic|                     |      
            +----+-----------------------------------+
            | 3. | |merge_trimmomatic_stats|         | 
            +----+-----------------------------------+
            | 4. | |dragen_align|                    |
            +----+-----------------------------------+
            | 5. | |add_bam_umi|                     |
            +----+-----------------------------------+
            | 6. | |sambamba_merge_sam_files|        |
            +----+-----------------------------------+
            | 7. | |sort_dragen_sam|                 |
            +----+-----------------------------------+
            | 8. | |metrics|                         |
            +----+-----------------------------------+
            | 9. | |dragen_methylation_call|         |
            +----+-----------------------------------+
            | 10.| |split_dragen_methylation_report| |
            +----+-----------------------------------+
            | 11.| |methylation_profile|             |
            +----+-----------------------------------+
            | 12.| |dragen_bedgraph|                 |
            +----+-----------------------------------+
            | 13.| |wiggle_tracks|                   |
            +----+-----------------------------------+
            | 14.| |ihec_sample_metrics_report|      |
            +----+-----------------------------------+
            | 15.| |bis_snp|                         |
            +----+-----------------------------------+
            | 16.| |filter_snp_cpg|                  |
            +----+-----------------------------------+
            | 17.| |prepare_methylkit|               |
            +----+-----------------------------------+
            | 18.| |methylkit_diff_analysis|         |
            +----+-----------------------------------+
            | 19.| |multi_QC|                        |
            +----+-----------------------------------+
            | 20.| |cram_output|                     |
            +----+-----------------------------------+

         .. card::

            .. include:: steps_methylseq.inc

      .. tab-item:: About

         .. card::

            `DNA Methylation`_ is an important epigenetic system related to gene expression. It is involved in embryonic development, genomic imprinting, X chromosome inactivation and cell differentiation. Since methylation takes part in many normal cellular functions, aberrant methylation of DNA may be associated with a wide spectrum of human diseases, including cancer. Bisulfite sequencing approaches are currently considered a “gold standard” allowing comprehensive understanding of the methylome landscape. Whole-genome bisulfite sequencing (WGBS), provides single-base resolution of methylated cytosines across the entire genome.

            GenPipes methylation sequencing workflow is adapted from the `Bismark pipeline`_. It aligns paired-end reads with `Bowtie 2`_ default mode. Duplicates are removed with `Picard`_, and methylation calls are extracted using Bismark. `Wiggle`_ tracks for both read coverage and methylation profile are generated for visualization. Variant calls can be extracted from the whole-genome bisulfite sequencing (WGBS) data directly using `Bis-SNP caller`_. Bisulfite conversion rates are estimated with lambda genome or from human non-CpG methylation directly. Several metrics based on IHEC requirements are also calculated. Methylation sequencing can also process capture data if provided with a capture `BED file`_. 

            Both paired-end reads as well as single-end reads are supported by this pipeline. Paired-end reading improves the ability to identify the relative positions of various reads in the genome making it much more effective than single-end reading for resolving structural rearrangements such as gene insertions, deletions or inversions and assembly of repetitive regions.  Single-end reads are much less expensive in terms of resource consumption and time needed for analysis and can be used for experiments that do not require higher degrees of accuracy offered by paired-reads.

            The standard MUGQIC Methyl-Seq pipeline uses Bismark to align reads to the reference genome. Treatment and filtering of mapped reads approaches as mark duplicate reads, recalibration and sort are executed using `Picard`_ and GATK. Samtools MPILEUP and `BCFtool`_ are used to produce the standard SNP and indels variants file (VCF). Additional SVN annotations mostly applicable to human samples include mappability flags, `dbSNP annotation`_ and extra information about SVN by using published databases. The `SNPeff tool`_ is used to annotate variants using an integrated database of functional predictions from multiple algorithms (`SIFT`_, `Polyphen 2`_, `LRT`_ and `MutationTaster`_, `PhyloP`_ and `GERP++`, etc.) and to calculate the effects they produce on known genes.

            A summary html report is automatically generated by the pipeline. This report contains description of the sequencing experiment as well as a detailed presentation of the pipeline steps and results. Various Quality Control (QC) summary statistics are included in the report and additional QC analysis is accessible for download directly through the report. The report includes also the main references of the software and methods used during the analysis, together with the full list of parameters that have been passed to the pipeline main script.

            See :ref:`methschema` tab for the pipeline workflow. For the latest implementation and usage details refer to WGS or Methylation Sequencing implementation `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/methylseq/README.md>`_.

            **References**

            * `DNA Methylation Detection: Bisulphite genomic sequencing analysis <https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3233226/>`_.
            * `Strategies for analyzing bisulfite sequencing data <https://www.sciencedirect.com/science/article/pii/S0168165617315936>`_.
            * `Analysis and Visualization Tool for Targeted Amplicon Bisulfite Sequencing on Ion Torrent Sequencers <https://journals.plos.org/plosone/article?id=10.1371/journal.pone.0160227>`_.
            * Cytosine and Guanine - `CpGs`_.

.. dropdown:: :material-outlined:`notifications;2em` Additional Requirements for `dragen` and `hybrid`
   :color: warning

      .. include:: opt_methylseq_dragen_warning.inc    

.. The following are html links used in this text

.. _DNA Methylation: https://genestack-user-tutorials.readthedocs.io/tutorials/Methylation_profiling/
.. _Bismark pipeline: https://www.ncbi.nlm.nih.gov/pubmed/21493656
.. _Bis-SNP caller: https://www.ncbi.nlm.nih.gov/pubmed/22784381
.. _BED file: https://asia.ensembl.org/info/website/upload/bed.html
.. _CpGs: https://en.wikipedia.org/wiki/CpG_site
.. _Bowtie 2: http://bowtie-bio.sourceforge.net/bowtie2/index.shtml
.. _BCFtool: https://samtools.github.io/bcftools/bcftools.html
.. _dbSNP annotation: https://www.ncbi.nlm.nih.gov/books/NBK44455/
.. _Polyphen 2: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4480630/
.. _PhyloP: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2798823/
.. _Picard: https://www.broadinstitute.org/files/shared/mpg/plathumgen/plathumgen_fennell.pdf
.. _Wiggle: https://genome.ucsc.edu/goldenPath/help/wiggle.html
.. _SNPeff tool: http://snpeff.sourceforge.net/SnpEff.html
.. _SIFT: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC168916/
.. _LRT: https://en.wikipedia.org/wiki/Likelihood-ratio_test
.. _MutationTaster: https://en.wikipedia.org/wiki/MutationTaster
.. _GERP++: http://mendel.stanford.edu/sidowlab/downloads/gerp/index.html

.. The following are replacement texts used in this file

.. |picard_sam_to_fastq| replace:: `Picard SAM to FastQ`_
.. |trimmomatic| replace:: `Trimmomatic`_
.. |merge_trimmomatic_stats| replace:: `Merge Trimmomatic Statistics`_
.. |bismark_align| replace:: `Bismark Aligner Step`_
.. |add_bam_umi| replace:: `UMI BAM Tag Processing`_
.. |sambamba_merge_sam_files| replace:: `Sambamba Merge SAM Files`_
.. |picard_remove_duplicates| replace:: `Picard remove duplicates`_
.. |metrics| replace:: `Compute Metrics`_
.. |methylation_call| replace:: `Methylation Call`_
.. |wiggle_tracks| replace:: `Wiggle Tracks`_
.. |methylation_profile| replace:: `Methylation Profile`_
.. |ihec_sample_metrics_report| replace:: `IHEC Sample Metrics Report`_
.. |bis_snp| replace:: `Bis SNP Processing`_
.. |filter_snp_cpg| replace:: `Filter SNP CpGs`_
.. |prepare_methylkit| replace:: `Prepare for MethylKit Differential Analysis`_
.. |methylkit_diff_analysis| replace:: `MethylKit Differential Analysis`_
.. |dragen_align| replace:: `Dragen Align`_
.. |sort_dragen_sam| replace:: `Sort Dragen SAM`_
.. |dragen_methylation_call| replace:: `Dragen Methylation Call`_
.. |split_dragen_methylation_report| replace:: `Split Dragen Methylation Report`_
.. |dragen_bedgraph| replace:: `Dragen BED Graph`_
.. |gembs_prepare| replace:: `GemBS Prepare`_
.. |gembs_map| replace:: `GemBS Map`_
.. |gembs_call| replace:: `GemBS Call`_
.. |gembs_bcf_to_vcf| replace:: `GemBS BCF to VCF`_
.. |gembs_format_cpg_report| replace:: `GemBS Format CPG Report`_
.. |gembs_report| replace:: `GemBS Report`_
.. |multi_QC| replace:: `Multi QC`_
.. include:: repl_cram_op.inc
