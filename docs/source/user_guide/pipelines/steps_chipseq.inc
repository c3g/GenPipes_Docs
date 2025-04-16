.. _docs_steps_chipseq:

.. spelling:word-list::

     config
     param
     bwa
     picard
     sam
     mfold
     intron
     introns

**Step Details**

Following are the various steps that are part of the ChIP Sequencing Pipeline:

.. _Picard Sam to Fastq:

**Picard Sam to Fastq**

If FASTQ files are not already specified in the Readset file, then this step converts SAM/BAM files from the input Readset into FASTQ format. Otherwise, it does nothing.

.. _Trimmomatic:

**Trimmomatic**

Raw reads quality trimming and removing of Illumina adapters is performed using `Trimmomatic Process <http://www.usadellab.org/cms/index.php?page=trimmomatic>`_.  If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, 'Adapter1' and 'Adapter2' columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. For PAIRED_END readsets, readset adapters are reversed-complemented and swapped, to match Trimmomatic Palindrome strategy. For SINGLE_END readsets, only Adapter1 is used and left unchanged.  

If available, trimmomatic step in Hi-C analysis takes FASTQ files from the readset file as input. Otherwise, it uses the FASTQ output file generated from the previous `Picard Sam to Fastq`_ step conversion of the BAM files. 

.. _Merge Trimmomatic Stats:

**Merge Trimmomatic Stats** 

The trim statistics per Readset file are merged at this step.

.. _Mapping BWA Mem Sambamba:

**Mapping BWA Mem Sambamba**

This step takes as input files trimmed FASTQ files, if available. Otherwise it takes FASTQ files from the readset. If readset is not supplied then it uses FASTQ output files from the previous `Picard Sam to Fastq`_ conversion of BAM files.

.. _SAMbamba Merge BAM:

**SAMbamba Merge BAM**

BAM readset files are merged into one file per sample. Merge is done using `Sambamba`_.

If available, the aligned and sorted BAM output files from previous `Mapping BWA Mem Sambamba`_ step are used as input. Otherwise, BAM files from the readset file is used as input.

.. _SAMbamba Mark Duplicates:

**SAMbamba Mark Duplicates**

Mark duplicates. Aligned reads per sample are duplicates if they have the same 5' alignment positions (for both mates in the case of paired-end reads). All but the best pair (based on alignment score) will be marked as a duplicate in the BAM file. Marking duplicates is done using `SAMbamba`_.

.. _SAMbamba View Filter:

**SAMbamba View Filter**

Filter unique reads by mapping quality using `SAMbamba`_.

.. _Metrics:

**Metrics**

The number of raw/filtered and aligned reads per sample are computed at this stage.

.. _Homer Make Tag Directory:

**Homer Make Tag Directory**

The Homer Tag directories, used to check for quality metrics, are computed at this step.

.. _QC Metrics:

**QC Metrics**

Sequencing quality metrics as tag count, tag auto-correlation, sequence bias and GC bias are generated.

.. _Deeptools QC:

**Deeptools QC**

`Fingerplot <https://deeptools.readthedocs.io/en/develop/content/tools/plotFingerprint.html>`_ quality control answers the question “Did my ChIP work?” for ChIP-seq sample analysis. The tool processes indexed BAM files, creating a profile of cumulative read coverage. Reads in a specified window (bin) are counted, sorted, and plotted as a cumulative sum. 

The Correlation Matrix tool analyzes and visualizes sample correlations using multiBamSummary or multiBigwigSummary output. It supports Pearson or Spearman methods to calculate correlation coefficients.

.. _Homer Make UCSC file:

**Homer Make UCSC files**

Wiggle Track Format files are generated from the aligned reads using Homer.  The resulting files can be loaded in browsers like `IGV <https://software.broadinstitute.org/software/igv/>`_ or `UCSC <https://genome.ucsc.edu>`_.

.. _MACS2 call peak:

**MACS2 call peak**

Peaks are called using the `MACS2`_ software. Different calling strategies are used for narrow and broad peaks.  The mfold parameter used in the model building step is estimated from a peak enrichment diagnosis run.  The estimated mfold lower bound is 10 and the estimated upper bound can vary between 15 and 100.

The default mfold parameter of MACS2 is [10,30].

.. _MACS2 ATAC-seq call peak:

**MACS2 ATAC-seq call peak**

Assay for Transposon Accessible Chromatin (ATAC-seq) analysis enables measurement of chromatin structure modifications (nucleosome free regions) on gene regulation. This step involves calling peaks using the `MACS2`_ software. Different calling strategies are used for narrow and broad peaks. The mfold parameter used in the model building step is estimated from a peak enrichment diagnosis run. The estimated mfold lower bound is 10 and the estimated upper bound can vary between 15 and 100.

The default mfold parameter of MACS2 is [10,30].

.. _Homer annotate peaks:

**Homer annotate peaks**

The peaks called previously are annotated with `HOMER tool <http://homer.ucsd.edu/homer/ngs/peaks.html>`_ using RefSeq annotations for the reference genome.  Gene ontology and genome ontology analysis are also performed at this stage.

.. _Homer find motifs genome:

**Homer find motifs genome**

In this step, De novo and known motif analysis per design are performed using `HOMER <http://homer.ucsd.edu/homer/motif/>`_.

.. _Annotation Graphs:

**Annotation Graphs**

This step focuses on peak location statistics. The following peak location statistics are generated per design: proportions of the genomic locations of the peaks. The locations are: Gene (exon or intron), Proximal ([0;2] kb upstream of a transcription start site), Distal ([2;10] kb upstream of a transcription start site), 5d ([10;100] kb upstream of a transcription start site), Gene desert (>= 100 kb upstream or downstream of a transcription start site), Other (anything not included in the above categories); The distribution of peaks found within exons and introns; The distribution of peak distance relative to the transcription start sites (TSS); the Location of peaks per design.

.. _Run SPP:

**Run SPP**

This step runs spp to estimate NSC and RSC ENCODE metrics. For more information - see quality enrichment of ChIP sequence data, `phantompeakqualtools <https://github.com/kundajelab/phantompeakqualtools>`_.

.. _Differential Binding:

**Differential Binding**

Differential Binding step is meant for processing DNA data enriched for genomic loci, including ChIP- seq data enriched for sites where specific protein binding occurs, or histone marks are enriched. It uses `DiffBind`_ package that helps in identifying sites that are differentially bound between sample groups. 

GenPipes Chipseq pipeline performs differential binding based on the provided treatments and controls as per the particular comparison specified in the design file. The differential analysis results are generated separately for each specified comparison in the :ref:`Design File<ref_chipseq_design_ff>`, with correctly specified treatments (2) and controls (1) samples.

Samples with '0' (zero) are ignored during the comparison. For details regarding how to specify sample group membership in the design file, refer to :ref:`Design File Format details<ref_chipseq_design_ff>`.

For comparison, at least two samples for each group must be specified. If two samples per group are not specified, the differential binding step will be skipped during the pipeline run.

.. warning:: **Incorrect Design File Format**

     If the specified design file does not follow the specified :ref:`Design File Format<ref_chipseq_design_ff>` for ChIPseq pipeline, the differential binding step will be skipped during the pipeline run.

The output of differential analysis containing differentially bound peaks are saved as a TSV. In addition, for each comparison done using `DiffBind`_, an html report is also generated for QC differential analysis.

.. note:: **Limitation of Differential Binding**

     1. Differential Binding analysis currently supports pair-wise (two groups) comparisons **only**. If you have a more complex experimental design, you may manually conduct the analysis.

     2. The Chip Sequencing protocol expects an input for the differential binding step. If pipeline users want to run this protocol without an input, they should skip the  Differential Binding step and run it themselves locally.

.. _IHEC Metrics:

**IHEC Metrics**

This step generates IHEC's `standard metrics <http://ihec-epigenomes.org/research/reference-epigenome-standards/>`_.

.. _MultiQC Report:

**MultiQC Report** 

A quality control report for all samples is generated.
For more detailed information see `MultiQC documentation <http://multiqc.info/>`_.

.. _Bedtools Blacklist Filter:

**Bedtools Blacklist Filter**

Remove reads in blacklist regions from BAM with `Bedtools`_ intersect, if blacklist file is supplied, otherwise, do nothing.

.. _GATK Haplotype Caller:

**GATK Haplotype Caller**

Use `GATK Haplotype`_ caller for SNPs and small indels.

.. _Merge and Call Individual GVCF:

**Merge & Call Individual GVCF**

Merges the GVCFs of haplotype caller and also generates a per sample VCF containing genotypes.

.. 
.. include:: steps_cram_op.inc

.. _Samtools: http://www.htslib.org/
.. _Picard: http://broadinstitute.github.io/picard/
.. _MACS2: https://www.biorxiv.org/content/10.1101/496521v1
.. _SAMbamba: https://lomereiter.github.io/sambamba/
.. _DiffBind: http://bioconductor.org/packages/release/bioc/vignettes/DiffBind/inst/doc/DiffBind.pdf
.. _Bedtools: https://bedtools.readthedocs.io
.. _GATK Haplotype:  https://gatk.broadinstitute.org/hc/en-us/articles/360037225632-HaplotypeCaller
