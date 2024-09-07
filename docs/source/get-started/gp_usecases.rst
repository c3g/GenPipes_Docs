.. _docs_gp_usecases:

.. spelling::

    miRNA
    miRNAs
    Pac
    Biosciences
    microarrays
    Amplicon
    pyrotags
    amplicons
    metagenome
    immunoprecipitated
    CpG
    exomes
    Coronavirus
    biobank

GenPipes Real-life Applications
===============================

GenPipes offers several :ref:`genomic analysis pipelines<docs_pipeline_ref>` that can be used for various bioinformatic analyses.

These can be utilized for performing a wide range of standardized and tailored analysis. Following is a brief summary that highlights potential use case for each of the GenPipes Pipelines.  

C3G has extensive experience analyzing data from various sequencing applications with state of the art computation methods. It offers various `services <https://www.computationalgenomics.ca/services/>`_ to next-generation sequencing researchers who wish to use these pipelines for advanced genomic analysis. For customized and case-by-case analysis service, `submit your request today <https://www.computationalgenomics.ca/services/#submitRequestInquiry>`_.

----

Following is a summary of real-life application use case for each of the GenPipes Pipelines:

COVID-19 genome sequencing to detect mutations
----------------------------------------------

GenPipes :ref:`CoVSeQ Pipeline<docs_gp_covseq>` has been used as part of `CoVSeQ <https://covseq.ca>`_ project.  CoVSeQ deals with real-time tracking of Quebec SARS-CoV-2 evolution. 

CoVSeQ is a partnership between the `Institut National de Santé Publique du Québec (INSPQ) <https://www.inspq.qc.ca/>`_ and the `McGill Genome Centre <http://www.mcgillgenomecentre.org/>`_ to sequence the viral genome of Quebec patients with COVID-19 disease. The viral samples are taken from a Quebec viral biobank, termed the CoVBanQ, which is hosted in the `Laboratoire de Santé; Publique du Québec (LSPQ) <https://www.inspq.qc.ca/lspq>`_.

You can obtain a real-time snapshot of evolving SARS-CoV-2 populations in Québec and access interactive data visualizations. It is meant for virologists, epidemiologists, public health officials and citizen scientists. Through interactive data visualizations, CoVSeQ allows exploration of continually up-to-date datasets, providing a novel surveillance tool to the scientific and public health communities.

For more details, visit `CoVSeQ Website <https://covseq.ca>`_ and `Sequencing Workflows <https://covseq.ca/methods>`_.

GenPipes Release version 4.1 supports a new sequencing pipeline to support Nanopore CoVSeQ analysis.  For details, visit :ref:`Nanopore CoVSeQ Pipeline<docs_gp_nanopore_cov>`.

RNA Sequencing
--------------

The :ref:`RNA Sequencing Pipeline<docs_gp_rnaseq>` helps to quantify transcripts and genes using a reference genome and test for differential expression across experimental conditions. It is also possible to call single nucleotide variants (SNVs), detect fusion gene events and assess alternative splicing events.

De Novo RNA Sequencing
-----------------------

The :ref:`De Novo RNA Sequencing Pipeline<docs_gp_rnaseq_denovo>` assembles reads to transcripts in the absence of a reference genome, annotates transcripts and tests for differential expression. This is well suited to organisms that are not yet characterized.

miRNA Sequencing
-----------------

This pipeline can be used to quantify known miRNAs, discovers novel ones using a reference genome and performs differential expression analysis. Additional analysis may include pathway testing, target candidates analysis or miRNA editing.

SARS-CoV-2 Genome Sequencing Pipeline
--------------------------------------

The :ref:`SARS-CoV-2 genome Sequencing Pipeline<docs_gp_covseq>` is designed for COVID-19 Coronavirus research and surveillance, enabling complete genome sequencing of the new SARS-CoV-2 virus responsible for the COVID-19 pandemic. 

SARS-CoV-2 Nanopore CoVSeQ Pipeline
-----------------------------------

The :ref:`SARS-CoV-2 Nanopore CoVSeQ Pipeline<docs_gp_nanopore_cov>` is designed to implement `ARTIC SARS-CoV2 protocol <https://artic.network/ncov-2019>`_, Version 4 / 4.1 (`V4.1 <https://github.com/artic-network/artic-ncov2019/tree/master/primer_schemes/nCoV-2019/V4.1>`_), using Nanopolish. This protocol is closely followed in GenPipes Nanopore sequencing pipeline with majority of changes related to technical adaptation of the protocol to be able to run in a High Performance Computing (HPC) environment.

DNA Methylation Pipeline
-------------------------

The :ref:`Methylation Pipeline<docs_methylation>` helps to analyze data coming from bisulfite converted DNA assayed by various sequencing assays such as RRBS, CpG capture, whole genome sequencing or microarrays. Our analysis computes methylation levels and performs differential analysis between experimental conditions.

Amplicon Sequencing Pipeline
-----------------------------

The :ref:`Amplicon Sequencing Pipeline<docs_gp_ampliconseq>` can process Illumina, PacBio pyrotags amplicons from the 16S, 18S or ITS amplicons. OTUs are picked and diversity is analyzed within and between communities. Further analyses include differential abundance testing or metagenome functional content prediction.

DNA Sequencing
---------------

The :ref:`DNA Sequencing Pipeline<docs_gp_dnaseq>` offers state of the art DNA-seq analyses detects and annotates variants in whole exomes, whole genomes or high coverage amplicons. The analysis can also be pushed further by assisting with variant prioritization, or perform advanced cancer related analysis.

ChIP Sequencing Pipeline
------------------------

The :ref:`ChIP Sequencing Pipeline<docs_gp_chipseq>` helps in analyzing DNA fragments from immunoprecipitated chromatin by calling alignment peaks on the genome, annotating the said peaks and performing additional analyses such as motif enrichment and discovery. Designed experiments can be analyzed by testing for differential binding between experimental conditions.

