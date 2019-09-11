.. _docs_gp_illumina_run_proc:

.. spelling::

      qc
 
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

#. Image Analysis: interpreting the image data to identify distinct clusters of genes
#. Base Calling: profiles for each cluster are used to call bases. Obtaining the quality of each base call is crucial for downstream analysis.
#. Alignment: entire set of called sequence reads are aligned to create a final sequence output file optimized for SNP identification.

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
                                  [-j {pbs,batch,daemon,slurm}] [-f] [--json]
                                  [--report] [--clean]
                                  [-l {debug,info,warning,error,critical}]
                                  [-d RUN_DIR] [--lane LANE_NUMBER]
                                  [-r READSETS] [-i CASAVA_SHEET_FILE]
                                  [-x FIRST_INDEX] [-y LAST_INDEX]
                                  [-m NUMBER_OF_MISMATCHES] [-w] [-v]


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
  -d RUN_DIR, --run RUN_DIR
                        run directory
  --lane LANE_NUMBER    lane number
  -r READSETS, --readsets READSETS
                        nanuq readset file. The default file is
                        'run.nanuq.csv' in the output folder. Will be
                        automatically downloaded if not present.
  -i CASAVA_SHEET_FILE  illumina casava sheet. The default file is
                        'SampleSheet.nanuq.csv' in the output folder. Will be
                        automatically downloaded if not present
  -x FIRST_INDEX        first index base to use for demultiplexing
                        (inclusive). The index from the sample sheet will be
                        adjusted according to that value.
  -y LAST_INDEX         last index base to use for demultiplexing (inclusive)
  -m NUMBER_OF_MISMATCHES
                        number of index mistmaches allowed for demultiplexing
                        (default 1). Barcode collisions are always checked.
  -w, --force-download  force the download of the samples sheets (default:
                        false)
  -v, --version         show the version information and exit

----

Example Run
-----------

Use the following commands to execute Illumina Sequencing Pipeline:

::

  illumina_run_processing.py <Add options - info not available in README file> >illumina_cmd.sh

  bash illumina_cmd.sh

You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

----

Pipeline Schema
---------------- 

No image or figure available in https://bitbucket.org/mugqic/genpipes/src/master/resources folder. TBD.

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
.. _Casava: https://www.illumina.com/Documents/seminars/presentations/2011_09_smith.pdf
.. _Casava User Guide: http://gensoft.pasteur.fr/docs/casava/1.8.2/CASAVA_1_8_2_UG_15011196C.pdf

