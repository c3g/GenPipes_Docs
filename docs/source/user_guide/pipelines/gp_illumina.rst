:orphan:

.. _docs_gp_illumina_run_proc:

.. spelling::

      qc

.. warning:: **Not supported in GenPipes 4.0 Release**

     Please note that Illumina Run Processing Pipeline is not supported in GenPipes Release 4.0.  The pipeline is undergoing updates and enhancements. These include updates to run processing and MGI support. Watch out for future release of GenPipes.

Illumina Run Processing Pipeline
=================================
Genomic Analyzers create massive amounts of data. The Illumina Run Processing Pipeline transforms primary imaging output from the Genome Analyzer into discrete aligned strings of bases. A package of integrated algorithms perform the core primary data transformation steps: image analysis, intensity scoring, base calling, and alignment. It also converts Base Call (BCL) files into `FASTQ`_ files that are needed for higher genomic analysis such as :ref:`ChIP Sequencing<docs_gp_chipseq>`.

.. figure:: /img/pipelines/illumina_data_xform.png
   :align: center
   :alt: illumina-xform

   Figure: Pipeline data transformation steps (Source: Illumina)

.. contents:: :local:

----

Introduction
------------

The standard MUGQIC Illumina Run Processing pipeline uses the `Illumina bcl2fastq software`_ to convert and demultiplex the base call files (BCL) to FASTQ files. The pipeline runs some QCs on the raw data, on the FASTQ and on the alignment. It performs the core primary data transformation steps: image analysis, intensity scoring, base calling, and alignment.

#. **Image Analysis:** interpreting the image data to identify distinct clusters of genes
#. **Base Calling:** profiles for each cluster are used to call bases. Obtaining the quality of each base call is crucial for downstream analysis.
#. **Alignment:** entire set of called sequence reads are aligned to create a final sequence output file optimized for SNP identification.

**Sample Files**

This pipeline uses two input sample sheets.

#. `Casava`_ Sheet
#. Nanuq Run Sheet

You can see samples of :ref:`Casava Sheet<doc_casava_sheet>` and :ref:`Nanuq Run Sheet<doc_nanuq_runsheet>` and also refer to `Casava User Guide`_ for more details.

----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to Illumina Sequencing implementation `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/illumina_run_processing///README.md>`_ file.

----

Usage
-----

::

  illumina_run_processing.py [-h] [--help] [-c CONFIG [CONFIG ...]]
                                  [-s STEPS] [-o OUTPUT_DIR]
                                  [-j {pbs,batch,daemon,slurm}] [-f]
                                  [--no-json] [--report] [--clean]
                                  [-l {debug,info,warning,error,critical}]
                                  [--sanity-check]
                                  [--container {wrapper, singularity} <IMAGE PATH>
                                  [--genpipes_file GENPIPES_FILE]
                                  [-d RUN_DIR] [--lane LANE_NUMBER]
                                  [-r READSETS] [-i CASAVA_SHEET_FILE]
                                  [-x FIRST_INDEX] [-y LAST_INDEX]
                                  [-m NUMBER_OF_MISMATCHES] [-w] [-v]


**Optional Arguments**

.. include:: opt_illumina.inc
.. include:: /common/gp_readset_opt.inc
.. include:: /common/gp_common_opt.inc

----

Example Run
-----------

Use the following commands to execute Illumina Sequencing Pipeline:

.. include::  /user_guide/pipelines/example_runs/illumina.inc

.. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

----

Pipeline Schema
---------------- 

Figure below shows the schema of the Illumina Sequencing workflow. 

.. figure:: /img/pipelines/mmd/illumina.mmd.png
   :align: center
   :alt: illumina schema
   :width: 100%
   :figwidth: 95%

   Figure: Schema of Illumina Sequencing protocol

.. figure:: /img/pipelines/mmd/legend.mmd.png
   :align: center
   :alt: dada2 ampseq
   :width: 100%
   :figwidth: 75%

----

Pipeline Steps
--------------

The table below shows various steps that are part of Illumina Sequencing Pipeline:

+----+-------------------------------------------+
|    |  *Illumina Sequencing Steps*              |
+====+===========================================+
| 1. | |index|                                   |
+----+-------------------------------------------+
| 2. | |fastq|                                   |
+----+-------------------------------------------+
| 3. | |align|                                   |
+----+-------------------------------------------+
| 4. | |picard_mark_duplicates|                  |
+----+-------------------------------------------+
| 5. | |metrics|                                 |
+----+-------------------------------------------+
| 6. | |blast|                                   |
+----+-------------------------------------------+
| 7. | |qc_graphs|                               |
+----+-------------------------------------------+
| 8. | |md5|                                     |
+----+-------------------------------------------+
| 9. | |copy|                                    |
+----+-------------------------------------------+
| 10.| |end_copy_notification|                   |
+----+-------------------------------------------+

----

.. include:: steps_illumina.inc

----

More Information 
----------------

* `Illumina Genome Analyzer Data Analysis Software <https://www.illumina.com/documents/products/datasheets/datasheet_genome_analyzer_software.pdf>`_.

.. Following are the replacement texts used in the content above

.. |index| replace:: `Index`_
.. |fastq| replace:: `FASTQ Step`_
.. |align| replace:: `Align`_
.. |picard_mark_duplicates| replace:: `Picard Mark Duplicates`_
.. |metrics| replace:: `Metrics`_
.. |blast| replace:: `BLAST Step`_
.. |qc_graphs| replace:: `QC Graphs Step`_
.. |md5| replace:: `MD5 Step`_
.. |copy| replace:: `Copy Step`_
.. |end_copy_notification| replace:: `End Copy Notification`_

.. Following are the html links used in this text

.. _FASTQ: https://en.wikipedia.org/wiki/FASTQ_format
.. _Illumina bcl2fastq software: http://sapac.support.illumina.com/sequencing/sequencing_software/bcl2fastq-conversion-software.html
.. commeting out - no longer available -  _Casava: https://www.illumina.com/Documents/seminars/presentations/2011_09_smith.pdf
.. _Casava: https://www.illumina.com/Documents/products/technotes/technote_snp_caller_sequencing.pdf
.. _Casava User Guide: https://manualzz.com/doc/o/gzef1/casava-v1.8.2-user-guide--15011196-b--running-bcl-conversion-and-demultiplexing 
