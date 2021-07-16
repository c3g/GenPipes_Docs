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
      FASTQ       
 
DNA Sequencing (High Coverage) Pipeline
=======================================

DNA Sequencing (High Coverage) is another GenPipes pipeline that is optimized for deep coverage samples. It is based on :ref:`DNA Sequencing Pipeline<docs_gp_dnaseq>`.

.. contents:: :local:

----

Introduction
------------

The DnaSeq High Coverage Pipeline is based on the :ref:`DNA Sequencing Pipeline<docs_gp_dnaseq>` and follows the same initial pipeline steps. The difference begins at the Mark Duplicates step. Since this data is high coverage Mark Duplicates step is not run. Recalibration is not run either because typically, these datasets are targeted with amplicons or custom capture which render recalibration useless. Also variant calling is done only using frequency. Bayesian callers are not used because these typically don't fare well with the high coverage.

----

Version
-------

|genpipes_version|

For latest pipeline implementation details visit `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq_high_coverage/README.md>`_.

----

Usage
-----

::

  dnaseq_high_coverage.py [-h] [--help] [-c CONFIG [CONFIG ...]]
                               [-s STEPS] [-o OUTPUT_DIR]
                               [-j {pbs,batch,daemon,slurm}] [-f] [--no-json]
                               [--report] [--clean]
                               [-l {debug,info,warning,error,critical}]
                               [--sanity-check]
                               [--container {wrapper, singularity} <IMAGE PATH>
                               [-r READSETS] [-v]

**Optional Arguments**

.. include:: opt_dnaseq_hc.inc
.. include:: /common/gp_readset_opt.inc
.. include:: /common/gp_common_opt.inc

----
 
Example Run
-----------

Following instructions are meant to be run on C3G deployed GenPipes on Beluga server.  It uses human genome data available at Beluga server. Use the following command on Beluga server to run DNA Sequencing (high coverage) pipeline:

:: 

    dnaseq_high_coverage.py -c 
    $MUGQIC_PIPELINES_HOME/pipelines/dnaseq_high_coverage/dnaseq_high_coverage.base.ini
    $MUGQIC_PIPELINES_HOME/pipelines/dnaseq_high_coverage/dnaseq_high_coverage.beluga.ini
    -j slurm -s 1-15 > dna_high_cov_commands.sh

    bash dna_high_cov_commands.sh

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
| 2. | |skewer_trimming|                            |
+----+----------------------------------------------+
| 3. | |bwa_mem_sambamba_sort_sam|                  |
+----+----------------------------------------------+
| 4. | |sambamba_merge|                             |
+----+----------------------------------------------+
| 5. | |gatk_indel_realigner|                       |
+----+----------------------------------------------+
| 6. | |sambamba_merge_realigned|                   |
+----+----------------------------------------------+
| 7. | |picard_fixmate|                             |
+----+----------------------------------------------+
| 8. | |metrics|                                    |
+----+----------------------------------------------+
| 9. | |picard_calculate_hs_metrics|                |
+----+----------------------------------------------+
| 10 | |gatk_callable_loci|                         |
+----+----------------------------------------------+
| 11.| |call_variants|                              |
+----+----------------------------------------------+
| 12.| |pre-process_vcf|                            |
+----+----------------------------------------------+
| 13.| |snp_effect|                                 |
+----+----------------------------------------------+
| 14.| |gemini_annotations|                         |
+----+----------------------------------------------+
| 15.| |cram_output|                                |
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

.. |picard_sam_to_fastq| replace:: `Picard SAM to FASTQ`_
.. |gatk_indel_realigner| replace:: `GATK Indel Realigner`_
.. |picard_fixmate| replace:: `Picard Fixmate`_
.. |metrics| replace:: `Metrics`_
.. |picard_calculate_hs_metrics| replace:: `Picard Calculate HS Metrics`_
.. |gatk_callable_loci| replace:: `GATK callable loci`_
.. |call_variants| replace:: `Call Variants`_
.. |pre-process_vcf| replace:: `Pre-process VCF`_
.. |snp_effect| replace:: `SNP Effect`_
.. |gemini_annotations| replace:: `Gemini Annotations`_
.. |skewer_trimming| replace:: `Skewer Trimming`_
.. |bwa_mem_sambamba_sort_sam| replace:: `BWA SAMbamba Sort SAM`_
.. |sambamba_merge| replace:: `SAMBAM Merge SAM Files`_
.. |sambamba_merge_realigned| replace:: `SAMBAM Merge Realigned`_

.. include:: repl_cram_op.inc
