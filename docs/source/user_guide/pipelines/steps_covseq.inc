.. _docs_steps_covseq:

Step Details
-------------

Following are the various steps that are part of GenPipes CoVSeq genomic analysis pipeline:

.. _Host Reads Removal:

**Host Reads Removal**

In this step, the filtered reads are aligned to a reference genome. The alignment is done per sequencing readset using the `BWA Software`_ and `BWA-Mem Algorithm`_. BWA output BAM files are then sorted by coordinate using `Sambamba`_.

Input files for this step include:

* Trimmed FASTQ files, if available
* If no FASTQ files then FASTQ files from supplied readset is used.
* If no readset is supplied then FASTQ output from Picard SAM to FASTQ conversion of BAM files is used.

.. _Kraken Analysis:

**Kraken Analysis**

`Kraken`_ is an ultrafast and highly accurate mechanism for assigning taxonomic abels to metagenomic DNA sequences. It achieves high sensitivity and speed by utilizing exact alignments of k-mers and a novel classification algorithm. This step performs Kraken analysis using output of the Sambamba processing in :ref:`previous step<Host Reads Removal>`.

.. _Cutadapt:

**Cutadapt**

`Cutadapt processing`_ cleans data by finding and removing adapter sequences, primers, poly-A tails and other types of unwanted sequence from high throughput sequencing reads obtained after Kraken analysis. In this step, quality trimming of raw reads and removing of adapters is performed by giving 'Adapter1' and 'Adapter2' columns from the readset file to Cutadapt. For PAIRED_END readsets, both adpaters are used. For SINGLE_END readsets, only Adapter1 is used and left unchanged.

To trim the front of the read, use adapter_5p_fwd and adapter_5p_rev (For PAIRED_END obly) in cutadpat setction of the .ini file.

This step takes as input files:

1. FASTQ files from the readset file, if available.
2. Otherwise, FASTQ output files from previous Picard SAM to FASQ conversion of BAM files is used.

.. _Mapping BWA Mem Sambamba:

**Mapping BWA Mem Sambamba**

This step takes as input files trimmed FASTQ files, if available. Otherwise it takes FASTQ files from the readset. If readset is not supplied then it uses FASTQ output files from the previous Picard SAM to FASTQ conversion of BAM files.

Here, the filtered reads are aligned to a reference genome. The alignment is done per sequencing readset. `BWA Software`_ is used for alignment with `BWA-Mem Algorithm`_. BWA output BAM files are then sorted by coordinate using `Sambamba`_.

.. _Sambamba Merge SAM Files:

**Sambamba Merge SAM Files**

This step uses `Sambamba-Merge Tool`_ to merge several BAM files into one. SAM headers are merged automatically similar to how it is done in Picard merging tool.

.. _Sambamba Filtering:

**Sambamba Filtering**

In this step, raw BAM files are filtered using `Sambamba`_ and and ```awk``` command is run to filter by insert size.

.. _iVar Trim Primers:

**iVar Trim Primers**

`iVar`_ uses primer positions supplied in a BED file to soft clip primer sequences from an aligned and sorted BAM file. Following this, the reads are trimmed based on a quality threshold(Default: 20). To do the quality trimming, iVar uses a sliding window approach(Default: 4). The windows slides from the 5' end to the 3' end and if at any point the average base quality in the window falls below the threshold, the remaining read is soft clipped.

In this step, primer sequences are removed from individual BAM files using iVar.

.. _CoVSeq Metrics:

**CoVSeq Metrics**

In this step, multiple metrices are computed from sequencing:

* DNA Sample `Qualimap`_ to facilitate quality control of alignment sequencing
* `Sambamba-flagstat`_ for obtaining flag statistics from BAM file
* `BED Tools GenomeCov`_ is used for computing histograms(default), per-base reports and BEDGRAPH summaries of feature coverage of aligned sequences for a given genome.
* `Picard HS Metrics`_ are picked from SAM/BAM files. Only those metrics are collected that are specific for sequence datasets generated through hybrid-selection. Hybrid-selection (HS) is the most commonly used technique to capture exon-specific sequences for tageted sequencing experiments such as exome sequencing.

.. _iVar Calling:

**iVar Calling**

In this step, `iVar`_ is used for creating a trimmed BAM file after trimming aligned reads in the input BAM file using primer positions specified in the BED input file.

.. _QUAST Consensus Metrics:

**QUAST Consensus Metrics**

In this step, QUAST is used to compare and evaluate assemblies to rule out mis-assemblies.

.. _Rename Consensus Header:

**Rename Consensus Header**

`Consensus sequence`_ is the calculated order of most frequent residues found at each position in a sequence alignment. This information is important when considering sequence-dependent enzymes such as RNA Polymerase which is important for SAR-CoV-2 studies. In this step, `header sequence`_ can be modified in various ways as specified in rename type parameter: Multipart header, Replace word, Replace interval, and Add prefix/suffix.

This is the final step of CovSeq pipeline.

.. Following are the links used as references above

.. _iVar: https://andersen-lab.github.io/ivar/html/manualpage.html
.. _QUAST: https://academic.oup.com/bioinformatics/article/29/8/1072/228832
.. _QUAST-lg: http://cab.spbu.ru/software/quast-lg/
.. _BWA Software: http://bio-bwa.sourceforge.net
.. _BWA-Mem Algorithm: http://bio-bwa.sourceforge.net/bwa.shtml 
.. _Sambamba: http://lomereiter.github.io/sambamba/index.html
.. _Kraken: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4053813/
.. _Kraken speed: http://ccb.jhu.edu/software/kraken/
.. _Cutadapt processing: https://cutadapt.readthedocs.io/en/stable/index.html
.. _Sambamba-Merge Tool: https://lomereiter.github.io/sambamba/docs/sambamba-merge.html
.. _Sambamba-flagstat: https://lomereiter.github.io/sambamba/docs/sambamba-flagstat.html
.. _Qualimap: http://qualimap.conesalab.org
.. _BED Tools GenomeCov: https://bedtools.readthedocs.io/en/latest/content/tools/genomecov.html
.. _Picard HS Metrics:  https://github.com/broadinstitute/picard/blob/master/src/main/java/picard/analysis/directed/CollectHsMetrics.java
.. _Consensus sequence: https://en.wikipedia.org/wiki/Consensus_sequence
.. _header sequence: http://www.sing-group.org/seda/downloads/manuals/0.4.0/operations.html#rename-header
