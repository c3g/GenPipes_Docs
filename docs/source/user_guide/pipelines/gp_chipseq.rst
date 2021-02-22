.. _docs_gp_chipseq:

.. spelling::

   transposase
   Immunoprecipitation
   atacseq
   Transposon
   nucleosome

ChIP Sequencing Pipeline
========================

Chromatin Immunoprecipitation (ChIP) sequencing technique is used for mapping DNA-protein interactions. It is a powerful method for identifying genome-wide DNA binding sites for transcription factors and other proteins. The ChIP-Seq workflow is based on the `ENCODE Project`_ workflow. It aligns reads using the `Burrows-Wheeler Aligner`_. It creates tag directories using `Homer routines`_. Peaks are called using `Model based Analysis for Chip Sequencing (MACS2)`_ and annotated using Homer. Binding motifs are also identified using Homer. Metrics are calculated based on `IHEC requirements`_. The ChIP-Seq pipeline can also be used for assay for transposase-accessible chromatin using sequencing (ATAC-Seq) samples. At GenPipes, we are developing a pipeline that is specific to `ATAC-Seq`_.

.. contents:: :local:

----

Introduction
------------

ChIP-Seq experiments allows the isolation and sequencing of genomic DNA bound by a specific transcription factor, covalently modified histone, or other nuclear protein. The pipeline starts by trimming adapters and low quality bases and mapping the reads (single end or paired end ) to a reference genome using `Burrows-Wheeler Aligner`_ (BWA). Reads are filtered by mapping quality and duplicate reads are marked. Then, Homer quality control routines are used to provide information and feedback about the quality of the experiment. Peak calls is executed by MACS and annotation and motif discovery for narrow peaks are executed using Homer. Statistics of annotated peaks are produced for narrow peaks and a standard report is generated.

For more details, see `ChIP-Seq Guidelines`_, and  `MUGQIC_Bioinfo_Chip-Seq.pptx`_.

----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to Hi-C Sequencing implementation `ChIP-Seq Pipeline README`_ file.

----

Usage
-----

::

  chipseq.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
                  [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]
                  [--no-json] [--report] [--clean]
                  [-l {debug,info,warning,error,critical}] [--sanity-check]
                  [--container {docker, singularity} {<CONTAINER PATH>, <CONTAINER NAME>}]
                  [-d DESIGN] [-t {chipseq, atacseq}] [-r READSETS] [-v]

**Optional Arguments**

::

  -h                              show this help message and exit
  --help                          show detailed description of pipeline and steps
  -c CONFIG [CONFIG ...], --config CONFIG [CONFIG ...]
                                  config INI-style list of files; config parameters are
                                  overwritten based on files order
  -s STEPS, --steps STEPS
                                  step range e.g. '1-5', '3,6,7', '2,4-8'
  -o OUTPUT_DIR, --output-dir OUTPUT_DIR
                                  output directory (default: current)
  -j {pbs,batch,daemon,slurm}, --job-scheduler {pbs,batch,daemon,slurm}
                                  job scheduler type (default: slurm)
  -f, --force                     force creation of jobs even if up to date (default:
                                  false)
  --no-json                       do not create a JSON file per analysed sample to track the
                                  analysis status (default: false i.e., JSON file will be
                                  created)
  --report                        create 'pandoc' command to merge all job markdown
                                  report files in the given step range into HTML, if
                                  they exist; if --report is set, --job-scheduler,
                                  --force, --clean options and job up-to-date status are
                                  ignored (default: false)
  --clean                         create 'rm' commands for all job removable files in
                                  the given step range, if they exist; if --clean is
                                  set, --job-scheduler, --force options and job up-to-
                                  date status are ignored (default: false)
  -l {debug,info,warning,error,critical}, --log {debug,info,warning,error,critical}
                                  log level (default: info)
  --sanity-check                  run the pipeline in `sanity check mode` to verify that
                                  all the input files needed for the pipeline to run are 
                                  available on the system (default: false) 
  --container {docker, singularity} {<CONTAINER PATH>, <CONTAINER NAME>}
                                  run pipeline inside a container providing a container
                                  image path or accessible docker/singularity hub path
  -d DESIGN, --design DESIGN
                                  design file
  -t {chipseq, atacseq}, --type {chipseq, atacseq}
                                  Type of piipeline (default chipseq)
  -r READSETS, --readsets READSETS
                                  readset file
  -v, --version                   show the version information and exit


Example Run
-----------

You can download `ChIP-Seq test dataset`_ and use the following command to execute the ChIP-Seq genomics pipeline:

::

  chipseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.guillimin.ini -r readsets.chipseqTest.chr22.tsv -d designfile_chipseq.chr22.txt -s 1-15 > chipseqScript.txt

  bash chipseqScript.txt

The commands will be sent to the job queue and you will be notified once each step is done. If everything runs smoothly, you should get MUGQICexitStatus:0 or Exit_status=0. If that is not the case, then an error has occurred after which the pipeline usually aborts. To examine the errors, check the content of the job_output folder.

----

Pipeline Schema
---------------

Figure below shows the schema of ChIP-Seq protocol. You can refer to the latest `GenPipes ChIP-Seq pipeline implementation`_ and refer to the `ChIP-Seq Schema high resolution image`_.

.. figure:: /img/pipelines/chipseq.png
   :align: center
   :alt: ChIP-Seq schema

   Figure: Schema of ChIP Sequencing protocol

----

Pipeline Steps
---------------

The table below shows various steps that constitute the ChIP sequencing pipeline:

+----+---------------------------+--------------------------------------+
|    | ChIP Sequencing Steps     |    ChIP Sequencing (atacseq)         |
+====+===========================+======================================+
| 1. | |picard_sam_to_fastq|     | |picard_sam_to_fastq|                |
+----+---------------------------+--------------------------------------+
| 2. | |trimmomatic|             | |trimmomatic|                        |
+----+---------------------------+--------------------------------------+
| 3. | |merge_trimmomatic_stats| | |merge_trimmomatic_stats|            |
+----+---------------------------+--------------------------------------+
| 4. | |bwa_mem_picard_sort_sam| | |bwa_mem_picard_sort_sam|            |
+----+---------------------------+--------------------------------------+
| 5. | |samtools_view_filter|    | |samtools_view_filter|               |
+----+---------------------------+--------------------------------------+
| 6. | |picard_merge_sam_files|  | |picard_merge_sam_files|             | 
+----+---------------------------+--------------------------------------+
| 7. | |picard_mark_duplicates|  | |picard_mark_duplicates|             |
+----+---------------------------+--------------------------------------+
| 8. | |metrics|                 | |metrics|                            |
+----+---------------------------+--------------------------------------+
| 9. | |homer_make_tag_directory|| |homer_make_tag_directory|           |
+----+---------------------------+--------------------------------------+
| 10.| |qc_metrics|              | |qc_metrics|                         |
+----+---------------------------+--------------------------------------+
| 11.| |homer_make_ucsc_file|    | |homer_make_ucsc_file|               |
+----+---------------------------+--------------------------------------+
| 12.| |macs2_callpeak|          | |macs2_atacseq_callpeak|             |    
+----+---------------------------+--------------------------------------+
| 13.| |homer_annotate_peaks|    | |homer_annotate_peaks|               |
+----+---------------------------+--------------------------------------+
| 14.| |homer_find_motifs_genome|| |homer_find_motifs_genome|           |
+----+---------------------------+--------------------------------------+
| 15.| |annotation_graphs|       | |annotation_graphs|                  |
+----+---------------------------+--------------------------------------+
| 16.| |ihec_preprocess_files|   | |ihec_preprocess_files|              |
+----+---------------------------+--------------------------------------+
| 17.| |run_spp|                 | |run_spp|                            |
+----+---------------------------+--------------------------------------+
| 18.| |ihec_metrics|            | |ihec_metrics|                       |
+----+---------------------------+--------------------------------------+
| 19.| |multiqc_report|          | |multiqc_report|                     |
+----+---------------------------+--------------------------------------+
| 20.| |cram_output|             | |cram_output|                        |
+----+---------------------------+--------------------------------------+

----

.. include:: steps_chipseq.inc

----

More Information
----------------

For the latest implementation and usage details, see `ChIP-Seq Pipeline README`_. Here is some more information about ChIP sequencing pipeline that you may find interesting.

* `ChIP-Seq and Beyond <https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3591838/>`_. 

* `ChIP-Seq Technology and Workflow <https://www.sciencedirect.com/science/article/pii/S1046202320300591>`_.

* `Schematic representation of major methods to detect functional elements in DNA <https://journals.plos.org/plosbiology/article/figure?id=10.1371/journal.pbio.1001046.g001>`_.

* `ChIP Sequencing and ATAC Sequencing <https://bioinformatics-core-shared-training.github.io/cruk-autumn-school-2017/ChIP/Materials/Lectures/Lecture4_Introduction%20to%20ChIP-seq%20and%20ATAC-seq_SS.pdf>`_

.. figure:: /img/pipelines/ChIP-Seq-hl-diag.png
   :align: center
   :alt: ChIP-Seq-HL 

   Figure:  Schematic representation of major methods used to detect functional elements in DNA (Source PLOS)

.. The following are replacement texts used in this file

.. |picard_sam_to_fastq| replace:: `Picard Sam to Fastq`_
.. |trimmomatic| replace:: `Trimmomatic`_
.. |merge_trimmomatic_stats| replace:: `Merge Trimmomatic Stats`_
.. |bwa_mem_picard_sort_sam| replace:: `BWA Mem Picard Sort`_
.. |samtools_view_filter| replace:: `Samtools View Filter`_
.. |picard_merge_sam_files| replace:: `Picard Merge SAM Files`_
.. |picard_mark_duplicates| replace:: `Picard Mark Duplicates`_
.. |metrics| replace:: `Metrics`_
.. |homer_make_tag_directory| replace:: `Homer Make Tag Directory`_
.. |qc_metrics| replace:: `QC Metrics`_
.. |homer_make_ucsc_file| replace:: `Homer Make UCSC file`_
.. |macs2_callpeak| replace:: `MACS2 call peak`_
.. |macs2_atacseq_callpeak| replace:: `MACS2 ATAC-seq call peak`_
.. |homer_annotate_peaks| replace:: `Homer annotate peaks`_
.. |homer_find_motifs_genome| replace:: `Homer find motifs genome`_
.. |annotation_graphs| replace:: `Annotation Graphs`_
.. |ihec_preprocess_files| replace:: `IEHC Preprocess file`_
.. |run_spp| replace:: `Run SPP`_
.. |ihec_metrics| replace:: `IHEC Metrics`_
.. |multiqc_report| replace:: `MultiQC Report`_

.. include:: repl_cram_op.inc

.. The following are html link targets used in this text

.. _ENCODE Project: https://www.genome.gov/Funded-Programs-Projects/ENCODE-Project-ENCyclopedia-Of-DNA-Elements
.. _Burrows-Wheeler Aligner: http://bio-bwa.sourceforge.net
.. _Homer routines: https://www.researchgate.net/publication/44640585_Simple_Combinations_of_Lineage-Determining_Factors_Prime_cis-Regulatory_Elements_Required_for_Macrophage_and_B-Cell_Identities
.. _Model based Analysis for Chip Sequencing (MACS2): https://genomebiology.biomedcentral.com/articles/10.1186/gb-2008-9-9-r137
.. _IHEC requirements: https://github.com/IHEC/ihec-assay-standards
.. _ATAC-Seq: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4374986/
.. _ChIP-Seq Guidelines: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3431496/
.. _ChIP-Seq report: http://gqinnovationcenter.com/services/bioinformatics/tools/chipReport/index.html
.. _ChIP-Seq Pipeline README: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/chipseq/README.md 
.. _ChIP-Seq test dataset: https://www.computationalgenomics.ca/tutorials/chipseq.zip
.. _GenPipes ChIP-Seq pipeline implementation: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/chipseq/ 
.. _ChIP-Seq Schema high resolution image: https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_chipseq.png
.. _MUGQIC_Bioinfo_ChIP-Seq.pptx: https://bitbucket.org/mugqic/genpipes/downloads/MUGQIC_Bioinfo_ChIP-Seq.pptx
