.. _Skewer Trimming:

**Skewer Trimming**

`Skewer`_ is used for adapter `trimming`_ in GenPipes pipelines. `Adapter trimming`_ is a prerequisite step for analyzing next-generation sequencing (NGS) data when the reads are longer than the target DNA/RNA fragments. Although typically used in small RNA sequencing, adapter trimming is also used widely in other applications, such as genome DNA sequencing and transcriptome RNA/cDNA sequencing, where fragments shorter than a read are sometimes obtained because of the limitations of NGS protocols. For the newly emerged Nextera long mate-pair (LMP) protocol, junction adapters are located in the middle of all properly constructed fragments; hence, adapter trimming is essential to gain the correct paired reads.

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
.. _Skewer: https://sourceforge.net/projects/skewer/
.. _trimming: https://dnatech.genomecenter.ucdavis.edu/faqs/when-should-i-trim-my-illumina-reads-and-how-should-i-do-it/
.. _Adapter trimming: https://pubmed.ncbi.nlm.nih.gov/24925680/
