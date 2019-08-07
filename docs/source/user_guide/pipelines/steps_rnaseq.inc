.. _docs_steps_rnaseq:

.. spelling:: 

      picard
      sam
      param
      config
      bwa
      hardclipped
      toxedo 
      rawcount
      transcriptome
      cxb
      pearson
      rRNA
      cuffnorm 

Step Details
-------------

.. _Picard SAM to FastQ:

**Picard SAM to FastQ**

In this step, if FASTQ files are not already specified in the readset file, then it 
convert SAM/BAM files from the input readset file into FASTQ format. 

.. _Trimmomatic:

**Trimmomatic**

This step takes as input files:

* FASTQ files from the readset file if available
* Else, FASTQ output files from previous picard_sam_to_fastq conversion of BAM files

Raw reads quality trimming and removing of Illumina adapters is performed using `Trimmomatic tool <http://www.usadellab.org/cms/index.php?page=trimmomatic>`_. If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, 'Adapter1' and 'Adapter2' columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. For PAIRED_END readsets, readset adapters are reversed-complemented and swapped, to match Trimmomatic Palindrome strategy. For SINGLE_END readsets, only Adapter1 is used and left unchanged.

.. _Merge Trimmomatic Stats:

**Merge Trimmomatic Stats**

The trim statistics per readset are merged at this step.

.. _Star Processing:

**Star Processing**

The filtered reads are aligned to a reference genome. The alignment is done per readset of sequencing using the STAR software. It generates a Binary Alignment Map file (.bam).

This step takes as input files:

* Trimmed FASTQ files if available
* Else, FASTQ files from the readset file if available
* Else, FASTQ output files from previous picard_sam_to_fastq conversion of BAM files

.. _Picard Merge SAM Files:

**Picard Merge SAM Files**

BAM readset files are merged into one file per sample. Merge is done using `Picard Tool <https://github.com/broadinstitute/picard/releases/tag/2.20.5>`_.

.. _Picard Sort SAM:

**Picard Sort SAM**

The alignment file is reordered (QueryName) using `Picard Tool <https://github.com/broadinstitute/picard/releases/tag/2.20.5>`_. The QueryName-sorted BAM files will be used to determine raw read counts.

.. _Picard Mark Duplicates:

**Picard Mark Duplicates**

Mark duplicates. Aligned reads per sample are duplicates if they have the same 5' alignment positions (for both mates in the case of paired-end reads). All but the best pair (based on alignment score) will be marked as a duplicate in the BAM file. Marking duplicates is done using `Picard package <http://broadinstitute.github.io/picard/>`_.

.. _Picard RNA Metrics:

**Picard RNA Metrics**

Computes a series of quality control metrics using both CollectRnaSeqMetrics and CollectAlignmentSummaryMetrics functions metrics are collected using `Picard package <http://broadinstitute.github.io/picard/>`_.

.. _Estimate Ribosomal RNA:

**Estimate Ribosomal RNA**

This step uses readset BAM files and bwa mem to align reads on the rRNA reference fasta and count the number of read mapped The filtered reads are aligned to a reference fasta file of ribosomal sequence. The alignment is done per sequencing readset. The alignment software used is `BWA package <http://bio-bwa.sourceforge.net>`_ with algorithm: bwa mem. BWA output BAM files are then sorted by coordinate using `Picard package <http://broadinstitute.github.io/picard/>`_.

.. _BAM Hard Clip:

**BAM Hard Clip**

Generate a hardclipped version of the BAM for the toxedo suite which does not support this official SAM feature.

.. _RNA Seq Compress:

**RNA Seq Compress**

Computes a series of quality control metrics using `RNA SeQC processing <https://software.broadinstitute.org/cancer/cga/rna-seqc>`_.

.. _Wiggle:

**Wiggle**

Generate wiggle tracks suitable for multiple browsers.

.. _Raw Counts:

**Raw Counts**

Count reads in feature using `HT Seq Count <https://htseq.readthedocs.io/en/release_0.11.1/>`_.

.. _Raw Counts Metrics:

**Raw Counts Metrics**

Create rawcount matrix, zip the wiggle tracks and create the saturation plots based on standardized read counts.

.. _Cufflinks Process:

**Cufflinks Process**

Compute RNA-Seq data expression using `cufflinks package <http://cole-trapnell-lab.github.io/cufflinks/cufflinks/>`_. Warning: It needs to use a hard clipped bam file while Tuxedo tools do not support official soft clip SAM format.

.. _Cuffmerge Process:

**Cuffmerge Process**

Merge assemblies into a master transcriptome reference using `cuffmerge package <http://cole-trapnell-lab.github.io/cufflinks/cuffmerge/>`_.

.. _Cuffquant Step:

**Cuffquant Step**

Compute expression profiles (abundances.cxb) using `cuffquant <http://cole-trapnell-lab.github.io/cufflinks/cuffquant/>`_. Warning: It needs to use a hard clipped bam file while Tuxedo tools do not support official soft clip SAM format.

.. _Cuffdiff Process:

**Cuffdiff Process**

`Cuffdiff package <http://cole-trapnell-lab.github.io/cufflinks/cuffdiff/>`_ is used to calculate differential transcript expression levels and test them for significant differences.

.. _Cuffnorm Normalization:

**Cuffnorm Normalization**

This step performs global normalization of RNA-Sequence expression levels using `Cuffnorm algorithm <http://cole-trapnell-lab.github.io/cufflinks/cuffnorm/>`_.

.. _FPKM Correlation:

**FPKM Correlation**

Compute the pearson correlation matrix of gene and transcripts FPKM. FPKM data are those estimated by cuffnorm.

.. _GQ RNA Sequencing Utility:

**GQ RNA Sequencing Utility**

Exploratory analysis using the `gqSeqUtils R package <https://bitbucket.org/mugqic/rpackages/src/master/gqSeqUtils/>`_.

.. _Differential Expression:

**Differential Expression**

Performs differential gene expression analysis using `DESEQ package <http://bioconductor.org/packages/release/bioc/html/DESeq.html>`_ and `EDGER package <http://www.bioconductor.org/packages/release/bioc/html/edgeR.html>`_. Merge the results of the analysis in a single csv file.

.. _Differential Expression GO sequencing:

**Differential Expression GO sequencing**

Gene Ontology analysis for RNA-Seq using the `Bioconductor's R package goseq <http://www.bioconductor.org/packages/release/bioc/html/goseq.html>`_.
Generates GO annotations for differential gene expression analysis.

.. _IHEC Metrics:

**IHEC Metrics**

Generate IHEC's standard metrics.

.. _Verify BAM ID:

**Verify BAM ID**

The software `verifyBamId <http://csg.sph.umich.edu/kang/verifyBamID/>`_ is used in this step to verify whether the reads in particular file match previously known genotypes for an individual (or group of individuals), and checks whether the reads are contaminated
as a mixture of two samples. verifyBamID can detect sample contamination and swaps when external genotypes are available. When external genotypes are not available, verifyBamID still robustly detects sample swaps.  

.. _Stringtie:

**Stringtie**

Assemble transcriptome using `Stringtie assembler <https://ccb.jhu.edu/software/stringtie/index.shtml>`_.

.. _Stringtie Assemble Transcriptome:

**Stringtie Assemble Transcriptome**

This step assembles transcriptome and compute RNA-seq expression using `Stringtie assembler <https://ccb.jhu.edu/software/stringtie/index.shtml>`_.

.. _Stringtie Merge:

**Stringtie Merge**

Merge assemblies into a master transcriptome reference using `Stringtie assembler <https://ccb.jhu.edu/software/stringtie/index.shtml>`_.

.. _Ballgown Gene Expression:

**Ballgown Gene Expression**

`Ballgown tool <https://bioconductor.org/packages/release/bioc/html/ballgown.html>`_ is used to calculate differential transcript and gene expression levels and test them for significant differences. 
