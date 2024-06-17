:orphan:

.. NOTE: THis pipeline is deprecated. Not used. Leaving it in code for posterity.

.. _docs_gp_pacbio:

.. spelling::

      contig
      contigs
      ba
      subread
      subreads
      preassembly
      spli 
      
 
PacBio Whole Genome Assembly Pipeline
=======================================

The PacBio whole-genome assembly pipeline is built following the Hierarchical Genome Assembly Process (`HGAP`_) method including additional features, such as base `modification detection`_ and genome circularization using `Circlator`_. De novo assembly is performed using PacBio’s `SMRT Link`_ software. Assembly contigs are generated using `HGAP4`_. Alignments are then corrected and used as seeds by `FALCON`_ to create contigs. The resulting contigs are then polished and processed by `Arrow`_, which ultimately generates high-quality consensus sequences. An optional step allowing assembly circularization is integrated at the end of the pipeline. 

.. contents:: :local:

----

Introduction
------------

In GenPipes PacBio Whole Genome Assembly Pipeline, contigs assembly with PacBio reads is done using `HGAP`_ workflow. Briefly, raw subreads generated from raw .ba(s|x).h5 PacBio data files are filtered for quality. A subread length cutoff value is extracted from subreads, depending on subreads distribution, and used into the preassembly (aka correcting step) using the long read aligner, (`BLASR`_ step), which consists of aligning short subreads on long subreads. Since errors in PacBio reads is random, the alignment of multiple short reads on longer reads allows to correct sequencing error on long reads. These long corrected reads are then used as seeds into assembly (Celera assembler) which gives contigs. These contigs are then polished by aligning raw reads on contigs, `BLASR`_, that are then processed through a variant calling algorithm,(`Quiver`_), that generates high quality consensus sequences using local realignments and PacBio quality scores.

----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to PacBio Sequencing implementation `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/pacbio_assembly//README.md>`_ file.

----

Usage
-----

::

  pacbio_assembly.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
                          [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]
                          [--no-json] [--report] [--clean]
                          [-l {debug,info,warning,error,critical}]
                          [--sanity-check]
                          [--container {docker, singularity} {<CONTAINER PATH>, <CONTAINER NAME>}]
                          [-r READSETS] [-v]

**Optional Arguments**

.. include:: /common/gp_readset_opt.inc
.. include:: /common/gp_common_opt.inc

----

Example Run
-----------

Use the following commands to execute PacBio Assembly Pipeline:

.. include::  /user_guide/pipelines/example_runs/pacbio.inc

.. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

----

Pipeline Schema
---------------

Figure below shows the schema of the PacBio Whole Genome Assembly sequencing pipeline. You can refer to the latest `pipeline implementation <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/pacbio_assembly/>`_ and see here to download a high resolution image of `PacBio Assembly Sequencing Pipeline <https://bitbucket.org/mugqic/genpipes/src/master/resources/workflows/GenPipes_pacbio_assembly.png>`_. 

.. figure:: /img/pipelines/pacbio.png
   :align: center
   :alt: pacbio schema

   Figure: Schema of PacBio Whole Genome Assembly Pipeline

----

Pipeline Steps
--------------

The table below shows various steps that are part of PacBio Assembly Pipeline:

+----+-------------------------------------------+
|    |  *PacBio Assembly Steps*                  |
+====+===========================================+
| 1. | |smrtanalysis|                            |
+----+-------------------------------------------+
| 2. | |pacbio_tools_get_cutoff|                 |
+----+-------------------------------------------+
| 3. | |preassembly|                             |
+----+-------------------------------------------+
| 4. | |assembly|                                |
+----+-------------------------------------------+
| 5. | |polishing|                               |
+----+-------------------------------------------+
| 6. | |pacbio_tools_assembly_stats|             |
+----+-------------------------------------------+
| 7. | |blast|                                   |
+----+-------------------------------------------+
| 8. | |mummer|                                  |
+----+-------------------------------------------+
| 9. | |compile|                                 |
+----+-------------------------------------------+
| 10 | |circlator_step|                          |
+----+-------------------------------------------+
| 11.| |basemodification|                        |
+----+-------------------------------------------+
| 12.| |motifMaker|                              |
+----+-------------------------------------------+

----

.. include:: steps_pacbio.inc

----

More Information
----------------

You can refer to the following publications for details on PacBio Whole Genome Assembly Sequencing method:

* Nonhybrid, finished microbial genome assemblies from `long-read SMRT sequencing data <https://www.ncbi.nlm.nih.gov/pubmed/23644548>`_ 

* Genome Modeling System (`GMS) <https://pdfs.semanticscholar.org/b93d/519dfbe9dcc592c4f6e8ba311dd35462e9fd.pdf?_ga=2.127763597.1688638338.1568098920-1838119301.1567504695>`_.

.. Following are the replacement texts used in the content above

.. |smrtanalysis| replace:: `SMRT Analysis Filtering`_
.. |pacbio_tools_get_cutoff| replace:: `PacBio Tools Cutoff`_
.. |preassembly| replace:: `Pre-Assembly`_
.. |assembly| replace:: `Assembly`_
.. |polishing| replace:: `Polishing`_
.. |pacbio_tools_assembly_stats| replace:: `PacBio Assembly Stats`_
.. |blast| replace:: `BLAST`_
.. |mummer| replace:: `Mummer`_
.. |compile| replace:: `Compile`_
.. |circlator_step| replace:: `Circlator Step`_
.. |basemodification| replace:: `Base Modification`_
.. |motifMaker| replace:: `Motif Maker`_


.. Following are the html links used in text above.
 
..  _HGAP: https://github.com/PacificBiosciences/Bioinformatics-Training/wiki/HGAP
.. _modification detection: https://github.com/PacificBiosciences/Bioinformatics-Training/wiki/Methylome-Analysis-Technical-Note
.. _Circlator:  https://www.ncbi.nlm.nih.gov/pubmed/26714481
.. _SMRT Link: https://www.pacb.com/products-and-services/sequel-system/software/
.. _HGAP4: https://www.pacb.com/videos/tutorial-hgap4-de-novo-assembly-application/
.. _FALCON: https://github.com/PacificBiosciences/FALCON/wiki
.. _Arrow: https://github.com/PacificBiosciences/GenomicConsensus
.. _Quiver: https://github.com/PacificBiosciences/GenomicConsensus
.. _BLASR: https://github.com/PacificBiosciences/blasr
