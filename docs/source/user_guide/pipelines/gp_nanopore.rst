.. _docs_gp_nanopore:

.. spelling::

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

Nanopore Pipeline
==================

Structural Variations (SV) are genomic alterations including insertions, deletions, duplications, inversions, and translocation. They account for approximately 1% of the differences among human genomes and play a significant role in phenotypic variation and disease susceptibility.

Nanopore sequencing technology can generate long sequence reads and provides more accurate SV identification in terms of both sequencing and data analysis. For SV analysis, several new aligners and SV callers have been developed to leverage the long-read sequencing data. Assembly based approaches can also be used for SV identification. `Minimap2`_ aligner offers high speed and relatively balanced performance for calling both insertions as well as deletions.

The Nanopore sequencing technology commercialized by `Oxford Nanopore Technologies (ONT)`_.

.. contents:: :local:

----

Introduction
------------

The Nanopore is used to analyze long reads produced by the `Oxford Nanopore Technologies (ONT)`_ sequencers. Currently, the pipeline uses `Minimap2`_ to align reads to the reference genome. Additionally, it produces a QC report that includes an interactive dashboard for each readset with data from the basecalling summary file as well as the alignment. A step aligning random reads to the `NCBI nucleotide`_ database and reporting the species of the highest hits is also done as QC.

Once the QC and alignments have been produced, Picard is used to merge readsets coming from the same sample. Finally, SVIM is used to detect Structural Variants (SV) including deletions, insertions and translocations. For a full summary of the types of SVs detected, please consult the following `site <https://github.com/eldariont/svim#background-on-structural-variants-and-long-reads>`_.

The SV calls produced by SVIM are saved as VCFs for each sample, which can then be used in downstream analyses. No filtering is performed on the SV calls.

This pipeline currently does not perform base calling and requires both FASTQ and a sequencing_summary file produced by a ONT supported basecaller (we recommend `Guppy`_). Additionally, the testing and development of the pipeline were focused on genomics applications, and functionality has not been tested for transcriptomic or epigenomic datasets. Beyond the QC dashboards for each readset, there is currently no implemented reporting step in this pipeline.

For more information on using ONT data for structural variant detection, as well as an alternative approach, please consult `Oxford Nanopore Technologies SV Pipeline GitHub repository <https://github.com/nanoporetech/pipeline-structural-variation>`_.

For information on the structure and contents of the Nanopore readset file, please consult `Nanopore Readsets details <https://bitbucket.org/mugqic/genpipes/src/master/#markdown-header-readset-file>`_.

----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to Nanopore Sequencing implementation `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/nanopore/README.md>`_ file.

----

Usage
-----

::

  nanopore.py [-h] [--help] [-c CONFIG [CONFIG ...]]
              [-s STEPS] [-o OUTPUT_DIR]
              [-j {pbs,batch,daemon,slurm}] [-f]
              [--no-json] [--report] [--clean]
              [-l {debug,info,warning,error,critical}]
              [--sanity-check]
              [--container {docker, singularity} {<CONTAINER PATH>, <CONTAINER NAME>}]
              [-r READSETS] [-v]


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
  --no-json                create a JSON file per analysed sample to track the
                        analysis status (default: false i.e., JSON file is
                        created)
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
  --sanity-check        run the pipeline in `sanity check mode` to verify that
                        all the input files needed for the pipeline to run are
                        available on the system (default: false)
  --container {docker, singularity} {<CONTAINER PATH>, <CONTAINER NAME>}
                        run pipeline inside a container providing a container
                        image path or accessible docker/singularity hub path
  -r READSETS, --readsets READSETS
                        readset file. 
  -v, --version         show the version information and exit

----

Example Run
-----------

Use the following commands to execute Nanopore Sequencing Pipeline:

::

  nanopore.py <Add options - info not available in README file> >nanopore_cmd.sh

  bash nanopore_cmd.sh

You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

----

Pipeline Schema
---------------- 

No image or figure available in https://bitbucket.org/mugqic/genpipes/src/master/resources folder. TBD-GenPipes-Dev.

----

Pipeline Steps
--------------

The table below shows various steps that are part of Nanopore Sequencing Pipeline:

+----+-------------------------------------------+
|    |  *Nanopore Sequencing Steps*              |
+====+===========================================+
| 1. | |blastqc|                                 |
+----+-------------------------------------------+
| 2. | |minimap2_align|                          |
+----+-------------------------------------------+
| 3. | |pycoqc|                                  |
+----+-------------------------------------------+
| 4. | |picard_merge_sam_files|                  |
+----+-------------------------------------------+
| 5. | |svim|                                    |
+----+-------------------------------------------+

----

.. include:: steps_nanopore.inc

----

More Information 
----------------

* `Evaluating nanopore sequencing data processing pipelines for structural variation identification <https://genomebiology.biomedcentral.com/articles/10.1186/s13059-019-1858-1>`_.
* `Minimap2`_: Pairwise alignment for nucleotide sequences.
* `Basecalling using Guppy <https://timkahlke.github.io/LongRead_tutorials/BS_G.html>`_.

.. Following are the replacement texts used in the content above

.. |blastqc| replace:: `BlastQC`_
.. |minimap2_align| replace:: `Minimap2 Align`_
.. |pycoqc| replace:: `pycoQC`_
.. |picard_merge_sam_files| replace:: `Picard Merge SAM Files`_
.. |svim| replace:: `Structural Variant Identification using Mapped Long Reads`_

.. Following are the html links used in this text

.. _Oxford Nanopore Technologies (ONT): https://academic.oup.com/clinchem/article/61/1/25/5611478 
.. _Minimap2 aligner: https://github.com/lh3/minimap2
.. _Minimap2: https://academic.oup.com/bioinformatics/article/34/18/3094/4994778
.. _NCBI nucleotide: https://www.ncbi.nlm.nih.gov/nucleotide/
.. _Guppy: https://bio.tools/guppy
