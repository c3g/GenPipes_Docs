.. _docs_step_methylseq:

.. spelling::

     bwa
     tdf
     chrM

Step Details
------------

.. _Picard SAM to FastQ:

**Picard SAM to FastQ**

In this step, if FASTQ files are not already specified in the readset file, then it converts SAM/BAM files from the input readset file into FASTQ format. Otherwise, nothing is
done.

.. _Trimmomatic:

**Trimmomatic**

This step takes as input files:

* FASTQ files from the readset file if available
* Else, FASTQ output files from previous picard_sam_to_fastq conversion of BAM files

Raw reads quality trimming and removing of Illumina adapters is performed using `Trimmomatic Tool`_. If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, 'Adapter1' and 'Adapter2' columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. For PAIRED_END readsets, readset adapters are reversed-complemented and swapped, to match Trimmomatic Palindrome strategy. For SINGLE_END readsets, only Adapter1 is used and left unchanged.

.. _Merge Trimmomatic Statistics:

**Merge Trimmomatic Statistics**

The trim statistics per readset are merged at this step.

.. _Bismark Aligner Step:

**Bismark Aligner Step**

In this step, reads are aligned using the `Bismark Tool`_.

.. _UMI BAM Tag Processing:

**UMI BAM Tag Processing**

This step uses `fgbio tool`_ to add read UMI tag to individual BAM files.

.. _Sambamba Merge SAM Files:

**Sambamba Merge SAM Files**

`Sambamba`_ is a powerful filtering tool used for extracting information from SAM/BAM files.

In this step, BAM readset files are merged into one file per sample. Merge is done using `Picard Tool`_.  

As input, this step takes the aligned and sorted BAM output files from previous step, `UMI BAM Tag Processing`_,  if available. Otherwise, it uses BAM files from the readset file as input.

.. _Picard remove duplicates:

**Picard remove duplicates**

This step removes duplicates. Aligned reads per sample are duplicates if they have the same 5' alignment positions (for both mates in the case of paired-end reads). All but the best pair (based on alignment score) will be removed as a duplicate in the BAM file. Removing duplicates is done using `Picard Tool`_.

.. _Compute Metrics:

**Compute Metrics**

Besides computing metrics, this step also generate coverage tracks per sample. Multiple metrics are computed at this stage: Number of raw reads, Number of filtered reads, Number of aligned reads, Number of duplicate reads, Median, mean and standard deviation of insert sizes of reads after alignment, percentage of bases covered at X reads (%_bases_above_50 means the % of exons bases which have at least 50 reads) whole genome or targeted percentage of bases covered at X reads (%_bases_above_50 means the % of exons bases which have at least 50 reads). A TDF (.tdf) coverage track is also generated at this step for easy visualization of coverage in the IGV browser.

.. _Methylation Call:

**Methylation Call**

The script in this pipeline step reads in a bisulfite read alignment file produced by the Bismark bisulfite mapper and extracts the methylation information for individual cytosines. The methylation extractor outputs result files for cytosines in CpG, CHG and CHH context. It also outputs `bedGraph`_, a coverage file from positional methylation data and cytosine methylation report.

.. _Wiggle Tracks:

**Wiggle Tracks**

This step generates wiggle tracks suitable for multiple browsers, to show coverage and methylation data. When using GRCh37 build of Human genome, to be compatible with the UCSC Genome Browser we only keep chromosomes 1-22, X, Y and MT, and we also rename them by prefixing "chr" to the chromosome name (e.g. "1" becomes "chr1"), and changing the mitochondrial chromosome from "MT" to "chrM", and keeping the GRCh37 coordinates.

.. _Methylation Profile:

**Methylation Profile**

This step involves generation of a CpG methylation profile by combining both forward and reverse strand Cs. 

It also generates all the methylation metrics: 

* CpG stats,
* `pUC19 <https://en.wikipedia.org/wiki/PUC19>`_ CpG stats,
* lambda conversion rate,
* median CpG coverage,
* GC bias

.. _IHEC Sample Metrics Report:

**IHEC Sample Metrics Report**

In this step, computed metrics which fit the IHEC standards, are retrieved.  It also build a tsv report table for IHEC.

.. _Bis SNP Processing:

**Bis SNP Processing**

Identifying SNPs is important for accurate quantification of methylation levels and for identification of allele-specific epigenetic events such as imprinting. This step uses bisulfite SNP caller, `Bis-SNP`_, for correctly identifying SNPs using the default high-stringency settings at an average 30× genomic coverage.

.. _Filter SNP CpGs:

**Filter SNP CpGs**

This step involves SNP CpGs filtering. The goal here is to use a known variants db (:abbr:`Variant Call Format(VCF)` file provided via the ini file) to filter the CpG sites produced earlier during the step `Methylation Profile`_.

.. _Prepare for MethylKit Differential Analysis:

**Prepare for MethylKit Differential Analysis**

This step enables comparison of methylation profile across samples. It prepares inputs that are required for the subsequent step of MethylKit Differential Analysis.

.. _MethylKit Differential Analysis:

**MethylKit Differential Analysis**

This step involves running of `MethylKit`_ to get DMCs & DMRs for different designed comparisons.

.. include:: steps_cram_op.inc 

.. Following are the html links used in this text

.. _Trimmomatic Tool: http://www.usadellab.org/cms/index.php?page=trimmomatic
.. _Bismark Tool: https://github.com/FelixKrueger/Bismark
.. _Picard Tool: http://broadinstitute.github.io/picard/
.. _fgbio tool: https://github.com/fulcrumgenomics/fgbio 
.. _bedGraph: https://genome.ucsc.edu/goldenPath/help/bedgraph.html 
.. _Bis-SNP: http://people.csail.mit.edu/dnaase/bissnp2011/
.. _CRAM file format: https://samtools.github.io/hts-specs/CRAMv3.pdf
.. _MethylKit: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3491415/
.. _Sambamba:  https://lomereiter.github.io/sambamba/
