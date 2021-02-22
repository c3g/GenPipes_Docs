.. _Skewer Trimming:

**Skewer Trimming**

TBD-GenPipes-Dev

.. _BWA SAMbamba Sort SAM:

**BWA SAMbamba Sort SAM**

The input for this step is the trimmed FASTQ files if available. Otherwise, it uses the FASTQ files from the readset. If those are not available then it uses FASTQ output files from the previous 'Picard SAM to FASTQ`_ step where BAM files are converted to FASTQ format.

In this step, filtered reads are aligned to a reference genome. The alignment is done per sequencing readset. The alignment software used is `BWA`_ with algorithm: bwa mem. BWA output BAM files are then sorted by coordinate using `SAMBAMBA`_.

.. _SAMBAM Merge SAM Files:

**SAMBAM Merge SAM Files**

This step takes as input files:

* Aligned and sorted BAM output files from previous bwa_mem_picard_sort_sam step if available
* Else, BAM files from the readset file

In this step, BAM readset files are merged into one file per sample. Merge is done using `Picard`_.

.. _SAMBAM Merge Realigned:

**SAMBAM Merge Realigned**

In this step, BAM files of regions of realigned reads are merged per sample using `SAMBAMBA`_.

.. _BWA: http://bio-bwa.sourceforge.net
.. _SAMBAMBA: http://lomereiter.github.io/sambamba/index.html
.. _Picard: http://broadinstitute.github.io/picard/


