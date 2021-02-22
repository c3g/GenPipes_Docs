.. _docs_steps_dnaseq_highcov:

.. spelling::

     unsynchronized
    
Step Details
-------------

Following are the various steps that are part of GenPipes DNA (High Coverage) Sequencing genomic analysis pipeline:

.. _Picard SAM to FASTQ:

**Picard SAM to FASTQ**

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

.. _GATK Indel Realigner:

**GATK Indel Realigner**

Insertion and deletion realignment is performed on regions where multiple base mismatches are preferred over indels by the aligner since it can appear to be less costly by the algorithm. Such regions will introduce false positive variant calls which may be filtered out by realigning those regions properly. Realignment is done using `GATK Toolkit <https://gatk.broadinstitute.org/hc/en-us>`_. The reference genome is divided by a number regions given by the nb_jobs parameter.

.. _Picard Fixmate:

**Picard Fixmate**

After realignment, some read pairs might become unsynchronized. This step verifies that the information is correct between the two pairs and if it is not, it fixes any inaccuracies to avoid problems during the following steps.

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

.. include:: steps_dnaseq_common.inc
.. include:: steps_cram_op.inc
