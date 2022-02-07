.. _docs_gp_cov_nanopore:

.. spelling::

   Conda
   Minimap
   Nanopore
   basecalled
   basecaller
   basecalling
   bp
   coronavirus
   epigenomics
   mRNA
   metagenomic
   nCoV
   nanopolish
   nt
   transcriptonomics
   minimap 

Nanopore ARTIC-Nanopolish SOP Pipeline
======================================

The `Nanopore ARTIC-Nanopolish protocol`_ has been widely adopted by research groups worldwide to assist in epidemiological investigations. This protocol is mainly focused around the use of portable Oxford Nanopore MinION sequencer. However, other aspects of the protocol related to primer scheme and sample amplification can be generalized to other sequencing platforms.

Direct amplification of the virus using tiled, multiplexed primers approach has been proven to have high sensitivity. It enables researchers to work directly from clinical samples compared to metagenomic projects.  It has been widely used to analyze viral genome data generated during outbreaks such as SARS-CoV-2 for information about relatedness to other viruses.

The GenPipes Nanopore Sequencing Pipeline is based on nCoV-2019 novel coronavirus bioinformatics protocol that takes the output from the sequencing protocol to consensus genome sequences. It includes basecalling, de-multiplexing, mapping, polishing and consensus generation.

.. contents:: :local:

----

Introduction
------------

The SOP for Nanopore data is based on the `ARTIC SARS-CoV2 protocol <https://artic.network/ncov-2019/ncov2019-bioinformatics-sop.html>`_ using nanopolish. This protocol is closely followed in GenPipes Nanopore sequencing pipeline with majority of changes related to technical adaptation of the protocol to be able to run in a High Performance Computing (HPC) environment. In such environments, Conda is not advisable.

Key steps include `basecalling with Guppy`_, demultiplexing, read filtering and consensus sequencing.

The Nanopore is used to analyze long reads produced by the Oxford Nanopore Technologies (ONT) sequencers. Currently, the pipeline uses Minimap2 to align reads to the reference genome. Additionally, it produces a QC report that includes an interactive dashboard for each readset with data from the basecalling summary file as well as the alignment. A step aligning random reads to the NCBI nt database and reporting the species of the highest hits is also done as QC.

Once the QC and alignments have been produced, Picard is used to merge readsets coming from the same sample. Finally, SVIM is used to detect Structural Variants (SV) including deletions, insertions and translocation. For a full summary of the types of SVs detected, refer to background material on `Structural Variants and Long Reads`_.

The SV calls produced by SVIM are saved as VCFs for each sample, which can then be used in downstream analyses. No filtering is performed on the SV calls.

This pipeline currently does not perform base calling and requires both FASTQ and a sequencing_summary file produced by a ONT supported basecaller (we recommend Guppy). Additionally, the testing and development of the pipeline were focused on genomics applications, and functionality has not been tested for transcriptonomics or epigenomics datasets. Beyond the QC dashboards for each readset, there is currently no implemented reporting step in this pipeline.

For more information on using ONT data for structural variant detection, as well as an alternative approach, see `pipeline-structural-variation on GitHub`_.

Details of structure and contents of the `Nanopore readset file are available here <https://bitbucket.org/mugqic/genpipes/src/master/README.md#markdown-header-nanopore>`_.


----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to Nanopore Sequencing implementation `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/nanopore/README.md>`_ file.

----

Usage
-----

::

  nanopore.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
            [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]
            [--no-json] [--report] [--clean]
            [-l {debug,info,warning,error,critical}] [--sanity-check]
            [--container {wrapper, singularity} {<CONTAINER PATH>, <CONTAINER NAME>}]
            [-r READSETS] [-v]

**Optional Arguments**

.. include:: /common/gp_common_opt.inc
.. include:: /common/gp_readset_opt.inc

----

Example Run
-----------

Use the following commands to execute Nanopore sequencing pipeline:

.. include::  /user_guide/pipelines/example_runs/cov_nanopore.inc

.. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`. Nanopore readset file structure and content details are available `here <https://bitbucket.org/mugqic/genpipes/src/master/README.md#markdown-header-nanopore>`_.

.. note::

     Check with Paul/Hector if this pipeline requires a test dataset and whether one is available. Then update/edit the test dataset link above accordingly.
 
----

Pipeline Schema
---------------

Figure below shows the schema of the Nanopore ARTIC SARS-CoV2 sequencing protocol. You can refer to the latest `pipeline implementation <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/nanopore/>`_  

.. figure:: /img/pipelines/ONT_ArticPipelineDigaram.png
   :align: center
   :alt: nanopore schema

   Figure: Schema of Nanopore Sequencing protocol

----

Pipeline Steps
--------------

The table below shows various steps that constitute the Nanopore genomic analysis pipeline.

+----+--------------------------------+
|    |  *Nanopore Sequencing Steps*   |
+====+================================+
| 1. | |blastqc|                      |
+----+--------------------------------+
| 2. | |minimap2_align|               |
+----+--------------------------------+
| 3. | |pycoqc|                       |
+----+--------------------------------+
| 4. | |picard_merge_sam_files|       |
+----+--------------------------------+
| 5. | |svim|                         |
+----+--------------------------------+

----

.. include:: steps_cov_nanopore.inc

----

.. _More Information on Nanopore Sequencing:

More information
-----------------

For the latest implementation and usage details refer to CoVSeq Pipeline implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/covseq/README.md>`_.

* `nCoV-2019 novel coronavirus bioinformatics protocol`_

* `Phylogenetic Analysis of nCoV-2019 genome`_ using publicly shared genome sequences with datasets from NCBI or GISAID.

* `Tiling Amplicon sequencing and downstream bioinformatics analysis`_

.. The following are replacement texts used in this file

.. |blastqc| replace:: `BlastQC`_
.. |minimap2_align| replace:: `Minimap2 Align`_
.. |pycoqc| replace:: `pycoQC`_
.. |picard_merge_sam_files| replace:: `Picard Merge SAM Files`_
.. |svim| replace:: `Structural Variant Identification using Mapped Long Reads`_

.. The following are links and references used in this file

.. _Nanopore ARTIC-Nanopolish protocol: https://artic.network/ncov-2019
.. _Phylogenetic Analysis of nCoV-2019 genome: https://virological.org/t/phylodynamic-analysis-176-genomes-6-mar-2020/356
.. _nCoV-2019 novel coronavirus bioinformatics protocol: https://artic.network/ncov-2019/ncov2019-bioinformatics-sop.html
.. _Tiling Amplicon sequencing and downstream bioinformatics analysis: https://artic.network/quick-guide-to-tiling-amplicon-sequencing-bioinformatics.html
.. _basecalling with Guppy: https://timkahlke.github.io/LongRead_tutorials/BS_G.html
.. _Structural Variants and Long Reads: https://github.com/eldariont/svim/blob/master/README.rst 
.. _pipeline-structural-variation on GitHub: https://github.com/nanoporetech/pipeline-structural-variation
