.. _docs_steps_rnaseq_light:

.. _Picard SAM to FASTQ:

**Picard SAM to FASTQ**

Convert SAM/BAM files from the input readset file into FASTQ format if FASTQ files are not already specified in the readset file. Do nothing otherwise.

.. _Trimmomatic:

**Trimmomatic**

Raw reads quality trimming and removing of Illumina adapters is performed using `Trimmomatic Tool`_.  If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, 'Adapter1' and 'Adapter2' columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. For PAIRED_END readsets, readset adapters are reversed-complemented and swapped, to match Trimmomatic Palindrome strategy. For SINGLE_END readsets, only Adapter1 is used and left unchanged.

This step takes as input files:

1. FASTQ files from the readset file if available
2. Else, FASTQ output files from previous picard_sam_to_fastq conversion of BAM files

.. _Merge Trimmomatic Stats:

**Merge Trimmomatic Stats**

The trim statistics per readset are merged at this step.

.. _Kallisto:

**Kallisto**

Run Kallisto on FastQ files for a fast estimate of abundance.

.. _Kallisto Count Matrix:

**Kallisto Count Matrix**

Use the output from Kallisto to create a transcript count matrix.

.. _GQ Seq Utils Exploratory:

**GQ Seq Utils Exploratory**

Exploratory analysis using the gqSeqUtils R package adapted for RnaSeqLight.

.. _Sleuth Differential Expression:

**Sleuth Differential Expression**

Performs differential gene expression analysis using `Sleuth`_.  Analysis are performed both at a transcript and gene level, using two different tests: LRT and WT. 

.. _MultiQC:

**MultiQC**

Aggregate results from bioinformatics analyses across many samples into a single report. MultiQC searches a given directory for analysis logs and compiles a HTML report. It's a general use tool, perfect for summarizing the output from numerous bioinformatics tools. For details, refer to `MultiQC Info <https://multiqc.info>`_.