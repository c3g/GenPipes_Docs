.. _docs_steps_dnaseq_highcov:

Step Details
-------------

Following are the various steps that are part of GenPipes DNA (High Coverage) Sequencing genomic analysis pipeline:

.. _Picard SAM to FastQ:

**Picard SAM to FastQ**

This step converts SAM/BAM files from the input readset file into FASTQ format if FASTQ files are not already specified in the readset file. Otherwise, it does no processing.

.. _Trimmomatic:

**Trimmomatic**

This step takes as input files:

- FASTQ files from the readset file if available
- Else, FASTQ output files from previous picard_sam_to_fastq conversion of BAM files

Raw reads quality trimming and removing of Illumina adapters is performed using `Trimmomatic - Flexible sequencing data trimmer <http://www.usadellab.org/cms/index.php?page=trimmomatic>`_. If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, 'Adapter1' and 'Adapter2' columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. For PAIRED_END readsets, readset adapters are reversed-complemented and swapped, to match Trimmomatic Palindrome strategy. For SINGLE_END readsets, only Adapter1 is used and left unchanged.

.. _Merge Trimmomatic Stats:

**Merge Trimmomatic Stats**

The trim statistics per readset are merged at this step.

.. _BWA Mem Picard Sort SAM:

**BWA Mem Picard Sort SAM**

This step takes as input files:

- Trimmed FASTQ files if available
- Else, FASTQ files from the readset file if available
- Else, FASTQ output files from previous picard_sam_to_fastq conversion of BAM files

The filtered reads are aligned to a reference genome. The alignment is done per sequencing readset. The alignment software used is `BWA with algorithm: bwa mem <http://bio-bwa.sourceforge.net/>`. BWA output BAM files are then sorted by coordinate using `Picard Tools <http://broadinstitute.github.io/picard/>`_.

.. _Picard Merge SAM Files:

**Picard Merge SAM Files**

This step takes as input files:

- Aligned and sorted BAM output files from previous bwa_mem_picard_sort_sam step if available
- Else, BAM files from the readset file

BAM readset files are merged into one file per sample. Merge is done using `Picard Tools <http://broadinstitute.github.io/picard/>`_.

.. _GATK Indel Realigner:

**GATK Indel Realigner**

Insertion and deletion realignment is performed on regions where multiple base mismatches are preferred over indels by the aligner since it can appear to be less costly by the algorithm. Such regions will introduce false positive variant calls which may be filtered out by realigning those regions properly. Realignment is done using `GATK Toolkit <https://software.broadinstitute.org/gatk/>`_. The reference genome is divided by a number regions given by the nb_jobs parameter.

.. _Merge Realigned:

**Merge Realigned**

BAM files of regions of realigned reads are merged per sample using `Picard Tools <http://broadinstitute.github.io/picard/>`_.

.. _Picard Fixmate:

**Picard Fixmate**

TBD

.. _Metrics:

**Metrics**

Compute metrics and generate coverage tracks per sample. Multiple metrics are computed at this stage: Number of raw reads, Number of filtered reads, Number of aligned reads, Number of duplicate reads, Median, mean and standard deviation of insert sizes of reads after alignment, percentage of bases covered at X reads (%_bases_above_50 means the % of exons bases which have at least 50 reads) whole genome or targeted percentage of bases covered at X reads (%_bases_above_50 means the % of exons bases which have at least 50 reads). A TDF (.tdf) coverage track is also generated at this step for easy visualization of coverage in the IGV browser.

.. _Picard Calculate HS Metrics:

**Picard Calculate HS Metrics**

Compute on target percent of hybridization based capture.

.. _GATK callable loci:

**GATK callable loci**

Computes the callable region or the genome as a bed track.

.. _Call Variants:

**Call Variants**

This step uses VarScan caller for insertions and deletions.

.. _Pre-process VCF:

**Pre-process VCF**

Pre-process vcf for loading into a annotation database - `Gemini <http://gemini.readthedocs.org/en/latest/index.html>`_. Processes include normalization and decomposition of MNPs by `Vt <http://genome.sph.umich.edu/wiki/Vt>`_ and vcf FORMAT modification for correct loading into Gemini.

.. _SNP Effect:

**SNP Effect**

This step performs Variant effect annotation. The .vcf files are annotated for variant effects using the SnpEff software. SnpEff annotates and predicts the effects of variants on genes (such as amino acid changes).

.. _Gemini Annotations:

**Gemini Annotations**

This step loads functionally annotated vcf file into a mysql lite annotation database as part of `Gemini processing <http://gemini.readthedocs.org/en/latest/index.html>`_.
