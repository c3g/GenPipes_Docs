.. _docs_pipeline_ref:

.. spelling:word-list::

    tumour
    Biosciences

Pipelines Reference Guide
=========================

.. dropdown:: :material-outlined:`bolt;2em` Usage Change Effective v5.x onward
   :color: success

   .. include:: /gp5_0.inc

GenPipes implements :ref:`standardized genomics workflows<docs_available_pipelines>`, including  DNA-Seq, tumour analysis, RNA-Seq, de novo RNA-Seq, ChIP-Seq, SARS-CoV-2 genome sequencing, methylation sequencing, Hi-C, capture Hi-C, and metagenomics. All pipelines have been implemented following a robust design and development routine by following established best practices standard operating protocols. The pipelines accept a binary sequence alignment map `(BAM) <http://samtools.github.io/hts-specs/SAMv1.pdf>`_ or a `FASTQ <https://en.wikipedia.org/wiki/FASTQ_format>`_ file as input.
 
This guide contains usage manual and reference information for all available GenPipes genomic analysis pipelines. Visit :ref:`GenPipes Real-life Applications and use cases<docs_gp_usecases>` to see how these pipelines can be deployed for complex next-generation genomic analysis in real life scenarios.

.. toctree::
   :maxdepth: 1
   :name: toc-pipeline-ref
   :caption: Active Pipelines

   pipelines/gp_ampliconseq
   pipelines/gp_chipseq
   pipelines/gp_covseq
   pipelines/gp_dnaseq
   pipelines/gp_longread_dnaseq
   pipelines/gp_wgs_methylseq
   pipelines/gp_nanopore_covseq
   pipelines/gp_rnaseq
   pipelines/gp_rnaseq_denovo
   pipelines/gp_rnaseq_light

.. toctree::
   :maxdepth: 1
   :name: toc-pipeline-ref-deprecated
   :caption: Deprecated/Merged Pipelines

   pipelines/gp_dnaseq_highcov
   pipelines/gp_epiqc
   pipelines/gp_hicseq
   pipelines/gp_tumourpair

.. Issue #168 comment out for 4.0 Release
..   pipelines/gp_illumina
