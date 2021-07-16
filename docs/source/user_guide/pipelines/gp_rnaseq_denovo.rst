.. _docs_gp_rnaseq_denovo:

.. spelling::

      contigs
      transcriptome
      isoforms
      Bioconductor
      edgeR
      goseq
      trinotate
      config
      param
      sam
      rRNA
      Transdecoder
      edgeR 
      denovo
      Grabherr
      Yassour

De-Novo RNA Sequencing Pipeline
================================

RNA Sequencing is a technique that allows `transcriptome studies`_ based on high throughput next-generation gene sequencing (NGS). De novo sequencing refers to sequencing a novel genome where there is no reference sequence available for alignment. Sequence reads are assembled as contigs, and the coverage quality of de novo sequence data depends on the size and continuity of the contigs (i.e., the number of gaps in the data).

De-Novo RNASeq pipeline is adapted from the `Trinity-Trinotate`_ `suggested workflow`_. It reconstructs transcripts from short reads, predicts proteins, and annotates, leveraging several databases. Quantification is computed using `RSEM Tool`_, and differential expression is tested in a manner identical to the RNA-seq pipeline. We observed that the default parameters of the Trinity suite are very conservative, which could result in the loss of low-expressed but biologically relevant transcripts. To provide the most complete set of transcripts, the pipeline was designed with lower stringency during the assembly step in order to produce every possible transcript and not miss low-expressed messenger RNA. A stringent filtration step is included afterward in order to provide a set of transcripts that make sense biologically.

.. contents:: :local:

----

Introduction
------------
The standard MUGQIC RNA-Seq *De Novo* Assembly pipeline uses the `Trinity <http://trinityrnaseq.sourceforge.net/>`_ software suite to reconstruct transcriptomes from RNA-Seq data without using any reference genome or transcriptome.  First, reads are trimmed with `Trimmomatic <http://www.usadellab.org/cms/index.php?page=trimmomatic>`_ and normalized in order to reduce memory requirement and decrease assembly runtime, using the Trinity normalization utility inspired by the `Diginorm <http://arxiv.org/abs/1203.4802>`_ algorithm.

Then, the transcriptome is assembled on normalized reads using the Trinity assembler. Trinity creates a Trinity.fasta file with a list of contigs representing the transcriptome isoforms. Those transcripts are grouped in components mostly representing genes.  Components and transcripts are functionally annotated using the `Trinotate <http://trinotate.sourceforge.net/>`_ suite.  Gene abundance estimation for each sample has been performed using `RSEM Tool`_ (RNA-Seq by Expectation-Maximization). Differential gene expression analysis is performed using `DESeq2`_ and `edgeR`_ Bioconductor packages.
  
The `DESeq2`_ and `edgeR`_ methods model **count data** by a negative binomial distribution. The parameters of the distribution (mean and dispersion) are estimated from the data, i.e. from the read counts in the input files.  Both methods compute a measure of read abundance, i.e. expression level (called *base mean* or *mean of normalized counts* in `DESeq2`_, and *concentration* in `edgeR`_) for each gene and apply a hypothesis test to each gene to evaluate differential expression. In particular, both methods determine a p-value and a log2 fold change (in expression level) for each gene. The Log2 FC of edgeR is reported in the differential gene results file, one file per design.

The log2fold change is the logarithm (to basis 2) of the fold change condition from condition A to B (mutation or treatment are the most common conditions). A "fold change" between conditions A and B at a gene or transcript is normally computed as the ratio at gene or transcript of the base mean of scaled counts for condition B to the base mean of scaled counts for condition A. Counts are scaled by a size factor in a step called normalization (if the counts of non-differentially expressed genes in one sample are, on average, twice as high as in another,  the size factor for the first sample should be twice that of the other sample).  Each column of the count table is then divided by the size factor for this column and the count values are brought to a common scale, making them comparable. See the `edgeR vignette <http://www.bioconductor.org/packages/2.12/bioc/vignettes/edgeR/inst/doc/edgeR.pdf>`_ for additional information on normalization approaches used in the pipeline.
  
The differential gene analysis is followed by a Gene Ontology (GO) enrichment analysis.  This analysis use the `goseq approach <http://bioconductor.org/packages/release/bioc/html/goseq.html>`_.  The goseq is based on the use of non-native GO terms resulting from trinotate annotations (see details in the section 5 of `the corresponding vignette <http://bioconductor.org/packages/release/bioc/vignettes/goseq/inst/doc/goseq.pdf>`_.
  
Thus a high quality contigs assembly is created by extracting all transcripts having a functional annotation as defined by trinotate, the Top BLASTX hit and TmHMM annotations are used by default.

Finally, different exploratory data analysis (EDA) techniques are applied to filtered isoforms expression levels.  Main goals of expression level EDA are the detection of outliers, potential mislabeling,  to explore the homogeneity of biological replicates and  to appreciate the global effects of the different experimental variables.
  
An HTML summary report is automatically generated by the pipeline. This report contains description of the sequencing experiment as well as a detailed presentation of the pipeline steps and results. Various Quality Control (QC) summary statistics are included in the report and additional QC analysis is accessible for download directly through the report. The report includes also the main references of the software and methods used during the analysis, together with the full list of parameters that have been passed to the pipeline main script.

----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to RNA Sequencing implementation `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/rnaseq_denovo_assembly/README.md>`_ file.

----

Usage
-----

::

  usage: rnaseq_denovo_assembly.py [-h] [--help] [-c CONFIG [CONFIG ...]]
                                 [-s STEPS] [-o OUTPUT_DIR]
                                 [-j {pbs,batch,daemon,slurm}] [-f]
                                 [--no-json] [--report] [--clean]
                                 [-l {debug,info,warning,error,critical}]
                                 [--sanity-check]
                                 [--container {wrapper, singularity} <IMAGE PATH>
                                 [--genpipes_file GENPIPES_FILE]
                                 [-d DESIGN] [-t {cufflinks,stringtie}]
                                 [-r READSETS] [-v]

**Optional Arguments**

.. include:: opt_rnaseq_denovo.inc
.. include:: /common/gp_design_opt.inc
.. include:: /common/gp_readset_opt.inc
.. include:: /common/gp_common_opt.inc

----

Example Run
-----------

Use the following commands to execute the *De Novo* sequencing pipeline:

::

  rnaseq_denovo_assembly.py -c $MUGQIC_PIPELINES_HOME/pipelines/rnaseq_denovo_assembly/rnaseq_denovo_assembly.base.ini $MUGQIC_PIPELINES_HOME/pipelines/rnaseq_denovo_assembly/rnaseq_denovo_assembly.guillimin.ini -r readset.rnaseq.txt -d design.rnaseq.txt -s 1-23 > rnaseqDeNovoCommands.sh

  bash rnaseqDeNovoCommands.sh

You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.  

----

Pipeline Schema
---------------

Figure below shows the schema of RNA Sequencing *De Novo* Assembly pipeline. You can refer to the latest `RNA Sequencing De Novo pipeline implementation <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/rnaseq_denovo_assembly/README.md>`_ and `high resolution schema image <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_rnaseq_denovo_assembly.png>`_. 

.. figure:: /img/pipelines/rnaseq_denovo.png 
   :align: center
   :alt: RNA Sequencing De Novo schema

   Figure: Schema of De Novo assembly RNA Sequencing protocol

----

Pipeline Steps
--------------

The table below lists various steps that constitute the RNA Sequencing *De Novo* Assembly.

+----+-------------------------------------------+
|    | RNA Sequencing De Novo Assembly Steps     |
+====+===========================================+
| 1. | |picard_sam_to_fastq|                     |
+----+-------------------------------------------+
| 2. | |trimmomatic|                             |
+----+-------------------------------------------+
| 3. | |merge_trimmomatic_stats|                 |
+----+-------------------------------------------+
| 4. | |insilico_read_normalization_readsets|    |
+----+-------------------------------------------+
| 5. | |insilico_read_normalization_all|         |
+----+-------------------------------------------+
| 6. | |trinity_step|                            |
+----+-------------------------------------------+
| 7. | |exonerate_fastasplit|                    |
+----+-------------------------------------------+
| 8. | |blastx_trinity_uniprot|                  |
+----+-------------------------------------------+
| 9. | |blastx_trinity_uniprot_merge|            |
+----+-------------------------------------------+
| 10.| |transdecoder_s|                          |
+----+-------------------------------------------+
| 11.| |hmmer|                                   |
+----+-------------------------------------------+
| 12.| |rnammer_transcriptome|                   |
+----+-------------------------------------------+
| 13.| |blastp_transdecoder_uniprot|             |
+----+-------------------------------------------+
| 14.| |signalp|                                 |
+----+-------------------------------------------+
| 15.| |tmhmm|                                   |
+----+-------------------------------------------+
| 16.| |trinotate_step|                          |
+----+-------------------------------------------+
| 17.| |align_and_estimate_abn_p_ref|            |
+----+-------------------------------------------+
| 18.| |align_and_estimate_abn|                  |
+----+-------------------------------------------+
| 19.| |gq_seq_rna_denovo|                       |
+----+-------------------------------------------+
| 20.| |differential_expression|                 |
+----+-------------------------------------------+
| 21.| |filter_annotated_components|             |
+----+-------------------------------------------+
| 22.| |gq_seq_rna_denovo_filtered|              |
+----+-------------------------------------------+
| 23.| |differential_expression_filtered|        |
+----+-------------------------------------------+

----

.. include:: steps_rnaseq_denovo.inc

----

.. _More Information on RNA Sequencing De Novo:

More information
-----------------

You can find more information about RNA Sequencing *De Novo* Assembly Pipeline in the following references:

* Grabherr MG, Haas BJ, Yassour M, et al. Full-length transcriptome assembly from RNA-Seq data without a reference genome - `Trinity-Trinotate`_.

* Chin CS, Alexander DH, Marks P, et al. Non-hybrid, finished microbial genome assemblies from long-read SMRT sequencing data - `suggested workflow`_.

* Trinity RNA sequencing utilities `Workshop Slides <http://biohpc.cornell.edu/lab/doc/Trinity_workshop.pdf>`_.

----

.. The following are replacement texts used in this file

.. |picard_sam_to_fastq| replace:: `Picard SAM to FastQ`_
.. |trimmomatic| replace:: `Trimmomatic Step`_
.. |merge_trimmomatic_stats| replace:: `Merge Trimmomatic Stats`_
.. |insilico_read_normalization_readsets| replace:: `InSilico Read Normalization of Readsets`_
.. |insilico_read_normalization_all| replace:: `InSilico Read Normalization (All)`_
.. |trinity_step| replace:: `Trinity Step`_
.. |exonerate_fastasplit| replace:: `Exonerate FASTA Split`_
.. |blastx_trinity_uniprot| replace:: `BLASTX Trinity UniProt`_
.. |blastx_trinity_uniprot_merge| replace:: `BLASTX Trinity UniProt Merge`_
.. |transdecoder_s| replace:: `TransDecoder Step`_
.. |hmmer| replace:: `HMMER Biosequence Analysis Step`_
.. |rnammer_transcriptome| replace:: `RNAmmer Method`_
.. |blastp_transdecoder_uniprot| replace:: `BLAST Transdecoder UniProt`_
.. |signalp| replace:: `SignalP Method`_
.. |tmhmm| replace:: `TMHMM Method`_
.. |trinotate_step| replace:: `Trinotate Step`_
.. |align_and_estimate_abn_p_ref| replace:: `Align and estimate Abundance Prep Reference`_
.. |align_and_estimate_abn| replace:: `Align and estimate Abundance`_
.. |gq_seq_rna_denovo| replace:: `Exploratory Analysis with gqSeqUtils R package`_
.. |differential_expression| replace:: `Differential Expression`_
.. |filter_annotated_components| replace:: `Filter Annotated Components`_
.. |gq_seq_rna_denovo_filtered| replace:: `Exploratory Analysis with subset of filtered transcripts`_
.. |differential_expression_filtered| replace:: `GOSEQ using filtered transcripts`_


.. The following are the html links referred to in this text.

.. _transcriptome studies: https://en.wikipedia.org/wiki/Transcriptome
.. _Trinity-Trinotate: https://www.ncbi.nlm.nih.gov/pubmed/21572440
.. _suggested workflow: https://www.ncbi.nlm.nih.gov/pubmed/23644548
.. _RSEM Tool: https://github.com/deweylab/RSEM
.. _DESeq2: https://bioconductor.org/packages/release/bioc/html/DESeq2.html
.. _edgeR: http://bioinformatics.oxfordjournals.org/content/26/1/139/
