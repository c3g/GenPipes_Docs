.. _docs_pipeline_ref:


.. spelling::

    tumour
    Biosciences

Pipelines Reference Guide
=========================

GenPipes implements :ref:`standardized genomics workflows<docs_available_pipelines>`, including  DNA-Seq, tumour analysis, RNA-Seq, de novo RNA-Seq, ChIP-Seq, Pacific Biosciences (PacBio) assembly, methylation sequencing, Hi-C, capture Hi-C, and metagenomics. All pipelines have been implemented following a robust design and development routine by following established best practices standard operating protocols. The pipelines accept a binary sequence alignment map `(BAM) <http://samtools.github.io/hts-specs/SAMv1.pdf>`_ or a `FASTQ <https://en.wikipedia.org/wiki/FASTQ_format>`_ file as input.
 
This guide contains usage manual and reference information for all available GenPipes genomic analysis pipelines.

.. toctree::
   :maxdepth: 1
   :name: toc-pipeline-ref

   pipelines/gp_hicseq
   pipelines/gp_chipseq
