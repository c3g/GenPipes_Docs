.. _docs_gp_dnaseq_highcov:

.. spelling:: 

      amplicons
      config
      param
      picard
      sam
      bwa
      nb
      tdf
      vcf
      mysql
            
 
DNA Sequencing (High Coverage) Pipeline
=======================================

DNA Sequencing (High Coverage) is another GenPipes pipeline that is optimized for deep coverage samples. It is based on :ref:`DNA Sequencing Pipeline<docs_gp_dnaseq>`.

.. contents:: :local:

----

Introduction
------------

The DnaSeq high Coverage Pipeline is based on the :ref:`DNA Sequencing Pipeline<docs_gp_dnaseq>` and follows the same initial pipeline steps. The difference begins at the Mark Duplicates step. Since this data is high coverage Mark Duplicates step is not run. Recalibration is not run either because typically, these datasets are targeted with amplicons or custom capture which render recalibration useless. Also variant calling is done only using frequency. Bayesian callers are not used because these typically don't fare well with the high coverage.

----

Version
-------
::

  3.1.4

For latest pipeline implementation details visit `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq_high_coverage/README.md>`_.

----

Usage
-----

::

  dnaseq_high_coverage.py [-h] [--help] [-c CONFIG [CONFIG ...]]
                               [-s STEPS] [-o OUTPUT_DIR]
                               [-j {pbs,batch,daemon,slurm}] [-f] [--json]
                               [--report] [--clean]
                               [-l {debug,info,warning,error,critical}]
                               [-t {mugqic,mpileup,light}] [-r READSETS] [-v]

**Optional Arguments**

::

  -h                    show this help message and exit
  --help                show detailed description of pipeline and steps
  -c CONFIG [CONFIG ...], --config CONFIG [CONFIG ...]
                        config INI-style list of files; config parameters are
                        overwritten based on files order
  -s STEPS, --steps STEPS
                        step range e.g. '1-5', '3,6,7', '2,4-8'
  -o OUTPUT_DIR, --output-dir OUTPUT_DIR
                        output directory (default: current)
  -j {pbs,batch,daemon,slurm}, --job-scheduler {pbs,batch,daemon,slurm}
                        job scheduler type (default: slurm)
  -f, --force           force creation of jobs even if up to date (default:
                        false)
  --json                create a JSON file per analysed sample to track the
                        analysis status (default: false)
  --report              create 'pandoc' command to merge all job markdown
                        report files in the given step range into HTML, if
                        they exist; if --report is set, --job-scheduler,
                        --force, --clean options and job up-to-date status are
                        ignored (default: false)
  --clean               create 'rm' commands for all job removable files in
                        the given step range, if they exist; if --clean is
                        set, --job-scheduler, --force options and job up-to-
                        date status are ignored (default: false)
  -l {debug,info,warning,error,critical}, --log {debug,info,warning,error,critical}
                        log level (default: info)
  -t {mugqic,mpileup,light}, --type {mugqic,mpileup,light}
                        DNAseq analysis type
  -r READSETS, --readsets READSETS
                        readset file
  -v, --version         show the version information and exit

----
 
Example Run
-----------

TBD - Link below needs to be updated - not listed in current README.md file


::

   TBD

---- 

Pipeline Schema
---------------

Figure below shows the schema of the DNA Sequencing (High Coverage) sequencing protocol. You can refer to the latest `pipeline implementation <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_dnaseq_high_coverage.png>`_ to download a high resolution image of the same.

.. figure:: /img/pipelines/dnaseq_highcov.png
   :align: center
   :alt: schema

   Figure: Schema of DNA Sequencing (High Coverage) Sequencing protocol

----

Pipeline Steps
--------------

The table below shows various steps that constitute the DNA Sequencing (High Coverage) genomic analysis pipelines.

+----+----------------------------------------------+
|    |  *DNA (High Coverage) sequencing Steps*      |
+====+==============================================+
| 1. | |picard_sam_to_fastq|                        |
+----+----------------------------------------------+
| 2. | |trimmomatic|                                |
+----+----------------------------------------------+
| 3. | |merge_trimmomatic_stats|                    |
+----+----------------------------------------------+
| 4. | |bwa_mem_picard_sort_sam|                    |
+----+----------------------------------------------+
| 5. | |picard_merge_sam_files|                     |
+----+----------------------------------------------+
| 6. | |gatk_indel_realigner|                       |
+----+----------------------------------------------+
| 7. | |merge_realigned|                            |
+----+----------------------------------------------+
| 8. | |picard_fixmate|                             |
+----+----------------------------------------------+
| 9. | |metrics|                                    |
+----+----------------------------------------------+
| 10.| |picard_calculate_hs_metrics|                |
+----+----------------------------------------------+
| 11.| |gatk_callable_loci|                         |
+----+----------------------------------------------+
| 12.| |call_variants|                              |
+----+----------------------------------------------+
| 13.| |pre-process_vcf|                            |
+----+----------------------------------------------+
| 14.| |snp_effect|                                 |
+----+----------------------------------------------+
| 15.| |gemini_annotations|                         |
+----+----------------------------------------------+

----

.. include:: steps_dnaseq_highcov.inc

----

.. _More Information:

More information
-----------------
For the latest implementation and usage details refer to DNA Sequencing (High Coverage) `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq_high_coverage/README.md>`_ file.

* `Gemini Annotations Paper <https://www.ncbi.nlm.nih.gov/pubmed/23874191>`_

----

.. The following are replacement texts used in this file

.. |picard_sam_to_fastq| replace:: `Picard SAM to FastQ`_
.. |trimmomatic| replace:: `Trimmomatic`_
.. |merge_trimmomatic_stats| replace:: `Merge Trimmomatic Stats`_
.. |bwa_mem_picard_sort_sam| replace:: `BWA Mem Picard Sort SAM`_
.. |picard_merge_sam_files| replace:: `Picard Merge SAM Files`_
.. |gatk_indel_realigner| replace:: `GATK Indel Realigner`_
.. |merge_realigned| replace:: `Merge Realigned`_
.. |picard_fixmate| replace:: `Picard Fixmate`_
.. |metrics| replace:: `Metrics`_
.. |picard_calculate_hs_metrics| replace:: `Picard Calculate HS Metrics`_
.. |gatk_callable_loci| replace:: `GATK callable loci`_
.. |call_variants| replace:: `Call Variants`_
.. |pre-process_vcf| replace:: `Pre-process VCF`_
.. |snp_effect| replace:: `SNP Effect`_
.. |gemini_annotations| replace:: `Gemini Annotations`_

