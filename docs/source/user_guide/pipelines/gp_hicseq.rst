.. _docs_gp_hicseq:

.. spelling:: 

   picard
   sam
   readName
   bams
   TADs
   TopDom
   RobusTAD
   multiqc
   rmap
   baitmap
   runChicago
   featureOverlap
   readname
   interactome
   config
   Rmap
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

The Hi-C pipeline, selected using the "-t hic" parameter, starts by trimming adapters and low quality bases. It then maps the reads to a reference genome using `HiCUP`_.  HiCUP first truncates chimeric reads, maps reads to the genome, then it filters Hi-C artifacts and removes read duplicates.  Samples from different lanes are merged and a tag directory is created by Homer, which is also used to produce the interaction matrices and compartments. TopDom is used to predict topologically associating domains (TADs) and homer is used to identify significant interactions.

**Hi-C capture**

The capture Hi-C pipeline, selected using the "-t capture" parameter, starts by trimming adapters and low quality bases. It then maps the reads to a reference genome using HiCUP. HiCUP first truncates chimeric reads, maps reads to the genome, then it filters Hi-C artifacts and removes read duplicates. Samples from different lanes are merged and CHiCAGO is then used to filter capture-specific artifacts and call significant interactions. This pipeline also identifies enrichment of regulatory features when provided with ChIP-Seq marks. It can also return bed interactions with significant baits (bait_intersect step) or with captured interactions (capture_intersect step).

An example of the Hi-C report for an analysis on public data (GM12878 Rao. et al.) is available for illustration purpose only: `Hi-C report`_.

----

Version
-------
::

  3.1.4

For the latest implementation and usage details refer to Hi-C Sequencing implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/hicseq/README.md>`_ file.

----

Usage
-----

::

  hicseq.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
  [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f] [--json]
  [--report] [--clean] [-l {debug,info,warning,error,critical}]
  -e {DpnII,HindIII,NcoI,MboI,Arima} [-t {hic,capture}] [-r READSETS] [-v]

**Optional Arguments**

::

    -h                                       show this help message and exit
    --help                                   show detailed description of pipeline and steps
  
    -c CONFIG [CONFIG ...]                   config INI-style list of files; config parameters
    --config CONFIG [CONFIG ...]             are overwritten based on files order 
    
    -s STEPS
    --steps STEPS                            step range e.g. '1-5', '3,6,7', '2,4-8'
     
    -o OUTPUT_DIR
    --output-dir OUTPUT_DIR                  output directory (default: current)
  
    -j {pbs,batch,daemon,slurm},
    --job-scheduler {pbs,batch,daemon,slurm} job scheduler type (default: slurm)
  
    -f,
    --force                                  force creation of jobs even if up to date (default: false)
  
    --json                                   create a JSON file per analysed sample to track the
                                             analysis status (default: false)
  
    --report                                 create 'pandoc' command to merge all job markdown report 
                                             files in the given step range into HTML, if they exist; 
                                             if --report is set, --job-scheduler, --force, --clean options 
                                             and job up-to-date status are ignored (default: false)
  
    --clean                                  create 'rm' commands for all job removable files in
                                             the given step range, if they exist; if --clean is
                                             set, --job-scheduler, --force options and job up-to-
                                             date status are ignored (default: false)
  
    -l {debug,info,warning,error,critical},
    --log {debug,info,warning,error,critical} log level (default: info)
  
    -e {DpnII,HindIII,NcoI,MboI,Arima},
    --enzyme {DpnII,HindIII,NcoI,MboI,Arima} Restriction Enzyme used to generate Hi-C library (default DpnII)
  
    -t {hic,capture},
    --type {hic,capture}                     Hi-C experiment type (default hic)
  
    -r READSETS,
    --readsets READSETS                      readset file
  
    -v,
    --version                                show the version information and exit
 
----
 
Example Run
-----------

You can download `Hi-C test dataset <http://www.computationalgenomics.ca/tutorial/hicseq.zip>`_ and run the following commands:

::

     hicseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.guillimn.ini -r readsets.HiC010.tsv -s 1-15 -e MboI -j pbs > hicseqScript_SRR1658581.txt

     bash hicseqScript_SRR1658581.txt

---- 

Pipeline Schema
---------------
Figure below shows the schema of the Hi-C protocol. You can refer to the latest `Hi-C pipeline implementation <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_hicseq_hic.png>`_ to download a high resolution image of the same.

.. figure:: /img/pipelines/hicseq_hic.png
   :align: center
   :alt: HiC schema

   Figure: Schema of Hi-C Sequencing protocol

The following figure shows the pipeline schema for capture Hi-C protocol. See latest `Hi-C capture implementation <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_hicseq_capture.png>`_ to download a high resolution image of this schema.

.. figure:: /img/pipelines/hicseq_hic_capture.png
   :align: center
   :alt: HiC schema

   Figure: Schema of Hi-C capture protocol

----

Steps
-----

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
| 16.| |multiqc_report|               | |create_hic_file|                   |
+----+--------------------------------+-------------------------------------+
| 17.|                                | |multiqc_report|                    |
+----+--------------------------------+-------------------------------------+

----

More information
-----------------
For the latest implementation and usage details refer to Hi-C Sequencing implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/hicseq/README.md>`_ file.

* Comprehensive Mapping of Long-Range Interactions Reveals Folding Principles of the Human Genome - `Paper introducing Hi-C <https://pdfs.semanticscholar.org/ca99/4823723e34e8b2c7c44848ad85ae2c7cf0be.pdf>`_.

* A high-resolution map of the three-dimensional chromatin interactome in human cells - `Defining target gene using Hi-C <A high-resolution map of the three-dimensional chromatin interactome in human cells>`_. 

.. include:: steps_hicseq.inc

.. _HiCUP: https://www.ncbi.nlm.nih.gov/pubmed/26835000
.. _TopDom: https://www.ncbi.nlm.nih.gov/pubmed/26704975
.. _RobusTAD: https://www.biorxiv.org/content/10.1101/293175v1
.. _JuiceBox: http://aidenlab.org/documentation.html
.. _MultiQC: https://multiqc.info
.. _CHICAGO: http://regulatorygenomicsgroup.org/chicago
.. _Hi-C report: https://bitbucket.org/mugqic/genpipes/src/341cab2f01883af0184b850062bd8537dcd32e41/pipelines/hicseq/url 

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
.. |create_rmap_file| replace:: `Create Rmap File`_
.. |create_baitmap_file| replace:: `Create Baitmap File`_
.. |create_design_files| replace:: `Create Design Files`_
.. |create_input_files| replace:: `Create Input Files`_
.. |runChicago| replace:: `Run Chicago`_
.. |runChicago_featureOverlap| replace:: `RunChicago FeatureOverlap`_
.. |bait_intersect| replace:: `Bait Intersect`_
.. |capture_intersect| replace:: `Capture Intersect`_
.. |create_hic_file| replace:: `Create Hic File`_
.. |multiqc_report| replace:: `Multiqc Report`_

