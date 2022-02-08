.. _docs_gp_covseq:

.. spelling::

     des
     du
     sociaux
     santé
     Ministere
     quast
     covseq

CoV Sequencing Pipeline
========================

CoV Sequencing Pipeline can be used to effectively amplify and detect SARS-CoV-2 RNA in samples such that it enables reliable results from even low copy numbers. It helps to assay clean characteristic target peaks of defined sizes, allowing for direct detection of the presence of viral genome from the Coronaviridae family.  Sequencing provides confirmation for the species as well as phylogenetic information for the specific strain discrimination.

The design of this pipeline is directed against SARS-CoV-2 and other coronaviruses as well. By amplifying conserved regions of other coronaviruses in a sample, along with mutation tolerant panels, it can provide additional insights and pinpoint sequence variability, thus offering a powerful solution for more in-depth research and surveillance of the rapidly evolving virus.

CoVSeQ pipeline is designed as part of the `partnership for Québec SARS-CoV-2`_ sequencing. It is funded by the CanCOGeN initiative through Genome Canada and from the Ministere de la santé et des services sociaux du Québec. For more details, see `CoVSeQ website`_.

.. contents:: :local:

----

Introduction
------------

The ongoing COVID-19 pandemic demands surveillance of the SARS-CoV-2 variants and fast spreading mutants through rapid and near real-time sequencing of the viral genome.  This is critical for effective health policy decision making. Gene sequencing pipelines require to be focused on specific characteristics of the COVID genome such as spike protein. To that effect, SARS-CoV-2 sequencing has been standardized through initiatives such as the Advancing Real-Time Infection Control Network (ARTIC) international initiative in which Illumina or Oxford Nanopore sequencing is carried out prior to whole viral genome amplification by tiling PCR or metagenomic approaches. 

SARS-CoV-2 whole genome sequencing data can help researchers in the following ways:

* characterize viral variants that occur within a given host
* understand variant fixation in a given population
* understand how the virus changes over time.

GenPipes offers CoVSeQ Pipeline, a bioinformatic workflow that incorporates Illumina and ONT sequence. This pipeline is intended to address both short as well as long reads and input data obtained from Illumina as well as ONT Nanopore instruments.
 
CoVSeQ pipeline helps in the genomic epidemiology of SARS-CoV-2 that output sequence alignment analysis and/or variants in various formats. It uses `Kraken2`_, `FreeBayes`_, `SnpEff`_ for genomic processing and `bcftools`_, `QUAST`_ for consensus. The latest version of the pipeline uses ncov-tools v1.8 for alignment and quality control. SAM Tools are used for sorting and indexing BAM files. It performs variant calling on every sorted BAM file, obtaining major frequency viral variants per genome in VCF format using the Freebayes variant calling program, as frequency-based pooled caller. Merged variants are annotated using SnpEff.  

CoVSeQ pipeline can be used for SARS-CoV-2 whole genome sequencing as per `ARTIC`_ protocol `V4`_ or `V4.1`_ by specifying appropriate .ini file as described below in usage and example sections. 

----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to DNA Sequencing implementation `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/covseq/README.md>`_ file.

----

Usage
-----

::

  covseq.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
            [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]
            [--no-json] [--report] [--clean]
            [-l {debug,info,warning,error,critical}] [--sanity-check]
            [--container {wrapper, singularity} <IMAGE PATH>]
            [--genpipes_file GENPIPES_FILE]
            [-r READSETS] [-v]

**Optional Arguments**

.. include:: /common/gp_readset_opt.inc
.. include:: /common/gp_common_opt.inc

----

Example Run
-----------

Use the following commands to execute CoVSeq sequencing pipeline:

.. include::  /user_guide/pipelines/example_runs/covseq.inc

.. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

.. include:: /user_guide/pipelines/notes/artic_version.inc

You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

----

Pipeline Schema
---------------

Figure below shows the schema of the CovSeq sequencing protocol. 

.. figure:: /img/pipelines/mmd/covseq.mmd.png
   :align: center
   :alt: covseq schema
   :width: 100%
   :figwidth: 95%

   Figure: Schema of CoVSeq Sequencing protocol

.. figure:: /img/pipelines/mmd/legend.mmd.png
   :align: center
   :alt: dada2 ampseq
   :width: 100%
   :figwidth: 75%

----

Pipeline Steps
--------------

The table below shows various steps that constitute the CoVSeq genomic analysis pipeline.

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

----

.. include:: steps_covseq.inc

----

.. _More Information on CoVSeq Sequencing:

More information
-----------------

For the latest implementation and usage details refer to CoVSeq Pipeline implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/covseq/README.md>`_.

* `CoVSeq Cost Effective Workflow`_

* `CoVSeq Genome Analysis and Visualization`_

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
