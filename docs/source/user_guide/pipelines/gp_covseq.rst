.. _docs_gp_covseq:

.. spelling:word-list::

     des
     du
     sociaux
     santé
     Ministere
     quast
     covseq

CoV Sequencing Pipeline
========================

:bdg-primary:`Version` |genpipes_version|

.. tab-set:: 

      .. tab-item:: Usage

         .. dropdown:: Command
            :open:

            .. code::

               genpipes covseq [options] [--genpipes_file GENPIPES_FILE.sh]
               bash GENPIPES_FILE.sh

         .. dropdown:: Options

            .. include:: /common/gp_design_opt.inc 
            .. include:: /common/gp_readset_opt.inc
            .. include:: /common/gp_common_opt.inc

         .. dropdown:: Example

            .. include::  /user_guide/pipelines/example_runs/covseq.inc

            .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

            .. card:: Test Dataset
               :link: docs_testdatasets
               :link-type: ref

               .. include::  /resources/cov-seq-testdataset-note.inc

      .. tab-item:: Schema
         :name: covschema

         .. dropdown:: CovSeq
            :open:

            .. figure:: /img/pipelines/mmd/covseq.mmd.png
               :align: center
               :alt: covseq schema
               :width: 100%
               :figwidth: 95%

               Figure: Schema of CoVSeq Sequencing protocol

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: legend
               :width: 100%
               :figwidth: 75%

      .. tab-item:: Steps

         +----+--------------------------------+
         |    |  *SARS-CoV-2 Sequencing Steps* |
         +====+================================+
         | 1. | |host_reads_removal|           |
         +----+--------------------------------+
         | 2. | |kraken_analysis|              |
         +----+--------------------------------+
         | 3. | |cutadapt|                     |
         +----+--------------------------------+
         | 4. | |mapping_bwa_mem_sambamba|     |
         +----+--------------------------------+
         | 5. | |sambamba_merge_sam_files|     |
         +----+--------------------------------+
         | 6. | |sambamba_filtering|           |
         +----+--------------------------------+
         | 7. | |ivar_trim_primers|            |
         +----+--------------------------------+
         | 8. | |covseq_metrics|               |
         +----+--------------------------------+
         | 9. | |freebayes_calling|            |
         +----+--------------------------------+
         | 10.| |ivar_calling|                 |
         +----+--------------------------------+
         | 11.| |snpeff_annotate|              |
         +----+--------------------------------+
         | 12.| |ivar_create_consensus|        |
         +----+--------------------------------+
         | 13.| |bcftools_create_consensus|    |
         +----+--------------------------------+
         | 14.| |quast_consensus_metrics|      |
         +----+--------------------------------+
         | 15.| |rename_consensus_header_ivar| |
         +----+--------------------------------+
         | 16.| |rename_consensus_h_freebayes| |
         +----+--------------------------------+
         | 17.| |ncovtools_quickalign|         |
         +----+--------------------------------+
         | 18.| |prepare_table|                |
         +----+--------------------------------+
         | 19.| |prepare_report_ivar|          |
         +----+--------------------------------+
         | 20.| |prepare_report_freebayes|     |
         +----+--------------------------------+
         | 21.| |multiqc_report|               |
         +----+--------------------------------+

         .. card::

            .. include:: steps_covseq.inc

      .. tab-item:: About

         .. card::

            CoVSeQ pipeline is designed as part of the `partnership for Québec SARS-CoV-2`_ sequencing. It is funded by the CanCOGeN initiative through Genome Canada and from the Ministere de la santé et des services sociaux du Québec. For more details, see `CoVSeQ website`_.

            The COVID-19 pandemic required surveillance of the SARS-CoV-2 variants and fast spreading mutants through rapid and near real-time sequencing of the viral genome.  This is critical for effective health policy decision making. Gene sequencing pipelines require to be focused on specific characteristics of the COVID genome such as spike protein. To that effect, SARS-CoV-2 sequencing has been standardized through initiatives such as the Advancing Real-Time Infection Control Network (ARTIC) international initiative in which Illumina or Oxford Nanopore sequencing is carried out prior to whole viral genome amplification by tiling PCR or metagenomic approaches. 

            SARS-CoV-2 whole genome sequencing data can help researchers in the following ways:

            * characterize viral variants that occur within a given host
            * understand variant fixation in a given population
            * understand how the virus changes over time.

            GenPipes offers CoVSeQ Pipeline, a bioinformatics workflow that incorporates Illumina and ONT sequence. This pipeline is intended to address both short as well as long reads and input data obtained from Illumina as well as ONT Nanopore instruments.
            
            CoVSeQ pipeline helps in the genomic epidemiology of SARS-CoV-2 that output sequence alignment analysis and/or variants in various formats. It uses `Kraken2`_, `FreeBayes`_, `SnpEff`_ for genomic processing and `bcftools`_, `QUAST`_ for consensus. The latest version of the pipeline uses ncov-tools v1.8 for alignment and quality control. SAM Tools are used for sorting and indexing BAM files. It performs variant calling on every sorted BAM file, obtaining major frequency viral variants per genome in VCF format using the Freebayes variant calling program, as frequency-based pooled caller. Merged variants are annotated using SnpEff.  

            It can be used for SARS-CoV-2 whole genome sequencing as per `ARTIC`_ protocol `V4`_ or `V4.1`_ by specifying appropriate .ini file as described below in usage and example sections. 

            See :ref:`covschema` tab for the pipeline workflow. Refer to CoVSeq Pipeline implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/covseq/README.md>`_ for details.

            **References**

            * `CoVSeq Cost Effective Workflow`_
            * `CoVSeq Genome Analysis and Visualization`_

.. include:: /user_guide/pipelines/notes/artic_version.inc

.. The following are replacement texts used in this file

.. |host_reads_removal| replace:: `Host Reads Removal`_
.. |kraken_analysis| replace:: `Kraken Analysis`_
.. |cutadapt| replace:: `Cutadapt`_
.. |mapping_bwa_mem_sambamba| replace:: `Mapping BWA Mem Sambamba`_
.. |sambamba_merge_sam_files| replace:: `Sambamba Merge SAM Files`_
.. |sambamba_filtering| replace:: `Sambamba Filtering`_
.. |ivar_trim_primers| replace:: `iVar Trim Primers`_
.. |covseq_metrics| replace:: `CoVSeq Metrics`_
.. |freebayes_calling| replace:: `Freebayes Calling`_
.. |ivar_calling| replace:: `iVar Calling`_
.. |snpeff_annotate| replace:: `SNPEff Annotate`_
.. |ivar_create_consensus| replace:: `iVar Create Consensus`_
.. |bcftools_create_consensus| replace:: `BCFTools Create Consensus`_
.. |quast_consensus_metrics| replace:: `QUAST Consensus Metrics`_
.. |rename_consensus_header_ivar| replace:: `Rename Consensus Header ivar`_
.. |rename_consensus_h_freebayes| replace:: `Rename Consensus Header freebayes`_
.. |ncovtools_quickalign| replace:: `ncovtools Quickalign`_
.. |prepare_table| replace:: `Prepare Table`_
.. |prepare_report_ivar| replace:: `Prepare Report ivar`_
.. |prepare_report_freebayes| replace:: `Prepare Report Freebayes`_
.. |multiqc_report| replace:: `MultiQC Report`_

.. The following are links and references used in this file

.. _CoVSeQ website: https://covseq.ca
.. _partnership for Québec SARS-CoV-2: https://c3g.github.io/covseq_McGill/SARS_CoV2_Sequencing/about.html
.. _Paragon CleanPlex Product Documents: https://www.paragongenomics.com/customer-support/product_documents/ 
.. _CoVSeq Cost Effective Workflow: https://www.researchgate.net/publication/348593724_COVseq_is_a_cost-effective_workflow_for_mass-scale_SARS-CoV-2_genomic_surveillance
.. _CoVSeq Genome Analysis and Visualization: https://www.researchgate.net/publication/341117511_CoV-Seq_SARS-CoV-2_Genome_Analysis_and_Visualization
.. _FreeBayes: https://github.com/freebayes/freebayes
.. _ARTIC: https://github.com/artic-network
.. _V4: https://github.com/replikation/poreCov/tree/master/data/external_primer_schemes/nCoV-2019/V4
.. _V4.1: https://github.com/replikation/poreCov/tree/master/data/external_primer_schemes/nCoV-2019/V4.1
.. _Kraken2: https://github.com/DerrickWood/kraken2/blob/master/docs/MANUAL.markdown
.. _bcftools: https://github.com/samtools/bcftools 
