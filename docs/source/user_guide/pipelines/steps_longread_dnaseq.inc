.. _docs_steps_longread_dnaseq:

.. spelling:word-list::

     Nanopore
     NCBI
     basecalled
     PycoQC
     Nanoplot
     pbmm2
     Mosdepth
     DeepVariant
     Germline


**Step Details**

Following are the various steps that are part of GenPipes Nanopore genomic analysis pipeline:

.. _BlastQC:

**BlastQC**

In this step, `Blast-QC utility`_ is used for sequence alignment and identification. It performs a basic QC test by aligning 1000bp of randomly selected reads to the `NCBI Nucleotide Database`_ in order to detect potential contamination.

.. _Minimap2 Align:

**Minimap2 Align**

`Minimap2 Align Program`_ is a fast, general purpose sequencing alignment program that maps DNA and long mRNA sequences against a large reference database.  It can be used for Nanopore sequencing for mapping 1kb genomic reads at an error rate of 15% (e.g., PacBio or Oxford Nanopore genomic reads), among other uses.

In this step,  minimap2 to align the FastQ reads that passed the minimum QC threshold to the provided reference genome. By default, it aligns to the human genome reference (GRCh38) with Minimap2.

.. _pycoQC:

**pycoQC**

In this step, `pycoQC Software`_ is used  produce an interactive quality report based on the summary file and alignment outputs. PycoQC relies on the sequencing_summary.txt file generated by Guppy. If needed, it can also generate a summary file from basecalled FAST5 files. PycoQC computes metrics and generates interactive QC plots for Oxford Nanopore technologies sequencing data.

.. _Picard Merge SAM Files:

**Picard Merge SAM Files**

BAM readset files are merged into one file per sample in this step. Using aligned and sorted BAM output files from :ref:`Minimap2 Align<Minimap2 Align>` step, it performs the merge using `Picard`_.

.. _Structural Variant Identification using Mapped Long Reads:

**Structural Variant Identification using Mapped Long Reads**

In this step, Structural Variant Identification using Mapped Long Reads (`SVIM methodology`_), is used to perform structural variant (SV) analysis on each sample.

.. _Metrics Nanoplot:

**Metrics Nanoplot**

This step collects QC metrics on unaligned BAM or FastQ files with `Nanoplot`_.

.. _pbmm2 Align:

**pbmm2 Align**

Uses `pbmm2`_ to align fastq files or the raw HiFi BAM to the reference. Sorted output can be used directly for polishing using GenomicConsensus, if BAM has been used as input to pbmm2.

.. _Metrics Mosdepth:

**Metrics Mosdepth**

Calculate depth stats with `mosdepth`_.

.. _Set DeepVariant Regions:

**Set DeepVariant Regions**

Create an interval list with `ScatterIntervalsByNs from GATK`_. Used for creating a broken-up interval list that can be used for scattering a variant-calling pipeline in a way that will not cause problems at the edges of the intervals. By using large enough N blocks (so that the tools will not be able to anchor on both sides) we can be assured that the results of scattering and gathering the variants with the resulting interval list will be the same as calling with one large region.

.. _DeepVariant Germline VC:

**DeepVariant Germline VC**

Germline variant calling with `DeepVariant`_.

.. _Merge Filter DeepVariant:

**Merge Filter DeepVariant**

Merge `DeepVariant`_ outputs from the previous step, if applicable, and filter vcf.

.. _HiFi CNV:

**HiFi CNV**

Call copy number variation and visualize results with `HiFiCNV`_.

.. _Target Genotyping:

**Target Genotyping**

Call tandem repeats for pathogenic and full repeats with `trgt`_ for `targeted genotyping`_.

.. _Sawfish:

**Sawfish**

Call structural variants from mapped HiFi sequencing reads with `Sawfish SV Caller`_.

.. _Annotate SV:

**Annotate SV**

Annotate and rank structural variants with `AnnotSV`_.

.. _Hi Phase:

**Hi Phase**

Phase variant calls with `HiPhase`_.

.. _Report CPSR:

**Report CPSR**

Creates a `CPSR`_ germline report. It takes annotated/filter VCF as the input and outputs an html report along with additional flat files.

.. _MultiQC:

**MultiQC**

The `MultiQC aggregator`_ collates results from bioinformatics analyses across many samples into a single report. It searches for a given directory for analysis logs and compiles a HTML report. This is a tool for general usage, perfect for summarizing the output from numerous bioinformatics tools.

.. References

.. _Blast-QC utility: https://environmentalmicrobiome.biomedcentral.com/articles/10.1186/s40793-020-00361-y
.. _NCBI Nucleotide Database: https://www.ncbi.nlm.nih.gov/nucleotide/
.. _Minimap2 Align Program: https://chipster.csc.fi/manual/minimap2.html
.. _pycoQC software: https://github.com/a-slide/pycoQC
.. _Picard: http://broadinstitute.github.io/picard/
.. _SVIM methodology:  https://pubmed.ncbi.nlm.nih.gov/30668829/
.. _Nanoplot: https://github.com/wdecoster/NanoPlot
.. _mosdepth: https://github.com/brentp/mosdepth
.. _ScatterIntervalsByNs from GATK: https://gatk.broadinstitute.org/hc/en-us/articles/360041416072-ScatterIntervalsByNs-Picard
.. _DeepVariant: https://github.com/google/deepvariant
.. _HiFiCNV: https://github.com/PacificBiosciences/HiFiCNV
.. _targeted genotyping: https://sapac.illumina.com/techniques/popular-applications/genotyping/targeted-genotyping.html
.. _trgt: https://github.com/PacificBiosciences/trgt
.. _Sawfish SV Caller: https://github.com/PacificBiosciences/sawfish
.. _AnnotSV: https://github.com/lgmgeo/AnnotSV
.. _HiPhase: https://github.com/PacificBiosciences/HiPhase
.. _CPSR: https://sigven.github.io/cpsr/
.. _MultiQC aggregator: https://multiqc.info/