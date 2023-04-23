.. _docs_gp_hicseq:

.. spelling:: 

   epigenome
   rmap
   picard
   sam
   readName
   bams
   TADs
   TopDom
   RobusTAD
   multiqc
   baitmap
   runChicago
   featureOverlap
   readname
   interactome
   config
   NPerBin
   nbaitsperbin
   npb
   nbpb
   poe
   chinput
   WashU
   intra
   sams
   proxOE
   param

HiC Sequencing Pipeline
=======================

The HiC-Seq workflow aligns reads using `HiCUP`_. It creates tag directories, produces interaction matrices, and identifies compartments and significant interactions using Homer. It identifies topologically associating domains using `TopDom`_ and `RobusTAD`_ (bioRxiv 293175). It also creates “.hic” files using `JuiceBox`_ and metrics reports using `MultiQC`_. The HiC-Seq workflow can also process capture Hi-C data with the flag “-t capture” using `CHICAGO`_. 

.. contents:: :local:

----

Introduction
------------
`Hi-C experiments <https://pdfs.semanticscholar.org/ca99/4823723e34e8b2c7c44848ad85ae2c7cf0be.pdf>`_ allow researchers to understand chromosomal folding and structure using proximity ligation techniques.  This pipeline analyzes both Hi-C experimental data (-t hic) and capture Hi-C data (-t capture).  

**Hi-C**

The Hi-C pipeline, selected using the "-t hic" parameter, starts by trimming adapters and low quality bases. It then maps the reads to a reference genome using `HiCUP`_.  HiCUP first truncates chimeric reads, maps reads to the genome, then it filters Hi-C artifacts and removes read duplicates.  Samples from different lanes are merged and a tag directory is created by Homer, which is also used to produce the interaction matrices and compartments. TopDom is used to predict topologically associating domains (TADs) and Homer is used to identify significant interactions.

**Hi-C capture**

The capture Hi-C pipeline, selected using the "-t capture" parameter, starts by trimming adapters and low quality bases. It then maps the reads to a reference genome using HiCUP. HiCUP first truncates chimeric reads, maps reads to the genome, then it filters Hi-C artifacts and removes read duplicates. Samples from different lanes are merged and CHiCAGO is then used to filter capture-specific artifacts and call significant interactions. This pipeline also identifies enrichment of regulatory features when provided with ChIP-Seq marks. It can also return bed interactions with significant baits (bait_intersect step) or with captured interactions (capture_intersect step).

An example of the Hi-C report for an analysis on public data (GM12878 Rao. et al.) is available for illustration purposes only: `Hi-C report`_.

----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to Hi-C Sequencing implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/hicseq/README.md>`_ file.

----

Usage
-----

::

  hicseq.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
                 [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]
                 [--no-json] [--report] [--clean]
                 [-l {debug,info,warning,error,critical}] [--sanity-check]
                 [--container {wrapper, singularity} <IMAGE PATH>
                 [--genpipes_file GENPIPES_FILE]
                 -e {DpnII,HindIII,NcoI,MboI,Arima} [-t {hic,capture}]
                 [-r READSETS] [-v]

**Optional Arguments**

.. include:: opt_hicseq.inc
.. include:: /common/gp_readset_opt.inc
.. include:: /common/gp_common_opt.inc

----
 
Example Run
-----------

You can download `Hi-C test dataset <https://datahub-90-cw3.p.genap.ca/hicseq.chr19.tar.gz>`_ and run the following commands:

.. include::  /user_guide/pipelines/example_runs/hicseq.inc

.. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

---- 

Pipeline Schema
---------------
Figure below shows the schema of the Hi-C protocol. 

.. figure:: /img/pipelines/mmd/hicseq.mmd.png
   :align: center
   :alt: HiC schema
   :width: 100%
   :figwidth: 95%

   Figure: Schema of Hi-C Sequencing protocol

.. figure:: /img/pipelines/mmd/legend.mmd.png
   :align: center
   :alt: dada2 ampseq
   :width: 100%
   :figwidth: 75%

The following figure shows the pipeline schema for capture Hi-C protocol. 

.. figure:: /img/pipelines/mmd/hicseq.capture.mmd.png
   :align: center
   :alt: HiC schema
   :width: 100%
   :figwidth: 95%

   Figure: Schema of Hi-C capture protocol

.. figure:: /img/pipelines/mmd/legend.mmd.png
   :align: center
   :alt: dada2 ampseq
   :width: 100%
   :figwidth: 75%

The following figure shows the pipeline schema for capture Hi-C protocol. 

----

Pipeline Steps
--------------

The table below shows various steps that constitute the Hi-C and Hi-C capture genomic analysis pipelines.

+----+--------------------------------+-------------------------------------+
|    |  *Hi-C sequencing Steps*       |   *Hi-C Capture sequencing Steps*   |
+====+================================+=====================================+
| 1. | |samtools_bam_sort|            | |samtools_bam_sort|                 |
+----+--------------------------------+-------------------------------------+
| 2. | |picard_sam_to_fastq|          | |picard_sam_to_fastq|               |
+----+--------------------------------+-------------------------------------+
| 3. | |trimmomatic|                  | |trimmomatic|                       |
+----+--------------------------------+-------------------------------------+
| 4. | |merge_trimmomatic_stats|      | |merge_trimmomatic_stats|           |
+----+--------------------------------+-------------------------------------+
| 5. | |fastq_readName_Edit|          | |fastq_readName_Edit|               |
+----+--------------------------------+-------------------------------------+
| 6. | |hicup_align|                  | |hicup_align|                       |
+----+--------------------------------+-------------------------------------+
| 7. | |samtools_merge_bams|          | |samtools_merge_bams|               |
+----+--------------------------------+-------------------------------------+
| 8. | |homer_tag_directory|          | |create_rmap_file|                  |
+----+--------------------------------+-------------------------------------+
| 9. | |interaction_matrices_Chr|     | |create_baitmap_file|               |
+----+--------------------------------+-------------------------------------+
| 10.| |interaction_matrices_genome|  | |create_design_files|               |
+----+--------------------------------+-------------------------------------+
| 11.| |identify_compartments|        | |create_input_files|                |
+----+--------------------------------+-------------------------------------+
| 12.| |identify_TADs_TopDom|         | |runChicago|                        |
+----+--------------------------------+-------------------------------------+
| 13.| |identify_TADs_RobusTAD|       | |runChicago_featureOverlap|         |
+----+--------------------------------+-------------------------------------+
| 14.| |identify_peaks|               | |bait_intersect|                    |
+----+--------------------------------+-------------------------------------+
| 15.| |create_hic_file|              | |capture_intersect|                 |
+----+--------------------------------+-------------------------------------+
| 16.| |repro_scores|                 | |create_hic_file|                   |
+----+--------------------------------+-------------------------------------+
| 17.| |quality_scores|               | |multiqc_report|                    |
+----+--------------------------------+-------------------------------------+
| 18.| |cram_output|                  | |cram_output|                       |
+----+--------------------------------+-------------------------------------+
| 19.| |multiqc_report|               |                                     |
+----+--------------------------------+-------------------------------------+

----

.. include:: steps_hicseq.inc

----

More information
-----------------
For the latest implementation and usage details refer to Hi-C Sequencing implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/hicseq/README.md>`_ file.

* Comprehensive Mapping of Long-Range Interactions Reveals Folding Principles of the Human Genome - `Paper introducing Hi-C <https://pdfs.semanticscholar.org/ca99/4823723e34e8b2c7c44848ad85ae2c7cf0be.pdf>`_.

* A high-resolution map of the three-dimensional chromatin interactome in human cells. `Defining target gene using Hi-C`_.

* `Measuring the reproducibility of Hi-C data`_.

----

.. The following are html links used in this text

.. _HiCUP: https://www.ncbi.nlm.nih.gov/pubmed/26835000
.. _TopDom: https://www.ncbi.nlm.nih.gov/pubmed/26704975
.. _RobusTAD: https://www.biorxiv.org/content/10.1101/293175v1
.. _JuiceBox Documenation: http://aidenlab.org/documentation.html
.. _MultiQC: https://multiqc.info
.. _CHICAGO: http://regulatorygenomicsgroup.org/chicago
.. _Hi-C report: https://bitbucket.org/mugqic/genpipes/src/341cab2f01883af0184b850062bd8537dcd32e41/pipelines/hicseq/url 
.. _Defining  target gene using Hi-C: https://www.nature.com/articles/nature12644
.. _Measuring the reproducibility of Hi-C data: https://pubmed.ncbi.nlm.nih.gov/30890172/

.. The following are replacement texts used in this file

.. |samtools_bam_sort| replace:: `Samtools Bam Sort`_
.. |picard_sam_to_fastq| replace:: `Picard Sam to Fastq`_
.. |trimmomatic| replace:: `Trimmomatic`_
.. |merge_trimmomatic_stats| replace:: `Merge Trimmomatic Stats`_
.. |fastq_readName_Edit| replace:: `Fastq ReadName Edit`_
.. |hicup_align| replace:: `Hicup Align`_
.. |samtools_merge_bams| replace:: `Samtools Merge Bams`_
.. |homer_tag_directory| replace:: `Homer Tag Directory`_
.. |interaction_matrices_Chr| replace:: `Interaction Matrices Chr`_
.. |interaction_matrices_genome| replace:: `Interaction Matrices Genome`_
.. |identify_compartments| replace:: `Identify Compartments`_
.. |identify_TADs_TopDom| replace:: `Identify TADs TopDom`_
.. |identify_TADs_RobusTAD| replace:: `Identify TADs RobusTAD`_
.. |identify_peaks| replace:: `Identify Peaks`_
.. |create_rmap_file| replace:: `Create RMAP File`_
.. |create_baitmap_file| replace:: `Create Baitmap File`_
.. |create_design_files| replace:: `Create Design Files`_
.. |create_input_files| replace:: `Create Input Files`_
.. |runChicago| replace:: `Run Chicago`_
.. |runChicago_featureOverlap| replace:: `RunChicago FeatureOverlap`_
.. |bait_intersect| replace:: `Bait Intersect`_
.. |capture_intersect| replace:: `Capture Intersect`_
.. |create_hic_file| replace:: `Create Hic File`_
.. |multiqc_report| replace:: `Multiqc Report`_
.. |repro_scores| replace:: `Reproducibility Scores`_
.. |quality_scores| replace:: `Quality Scores`_

.. include:: repl_cram_op.inc
