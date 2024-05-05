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
      cufflinks
      stringtie

**Step Details**

.. _Picard SAM to FastQ:

**Picard SAM to FastQ**

In this step, if FASTQ files are not already specified in the readset file, then it converts SAM/BAM files from the input readset file into FASTQ format. Otherwise, nothing is done. 

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

.. _Run Star Fusion:

**Run Star Fusion**

`STAR-Fusion <https://github.com/STAR-Fusion/STAR-Fusion/wiki>`_ is a component of the Trinity Cancer Transcriptome Analysis Toolkit (CTAT). Based on the STAR aligner it identifies candidate fusion transcripts supported by Illumina reads.

.. _Picard Merge SAM Files:

**Picard Merge SAM Files**

BAM readset files are merged into one file per sample. Merge is done using `Picard Tool <https://github.com/broadinstitute/picard/releases/tag/2.20.5>`_.

.. _Picard Sort SAM:

**Picard Sort SAM**

The alignment file is reordered (QueryName) using `Picard Tool <https://github.com/broadinstitute/picard/releases/tag/2.20.5>`_. The QueryName-sorted BAM files will be used to determine raw read counts.

.. _Mark Duplicates:

**Mark Duplicates**

This step handles duplicates. Aligned reads per sample are duplicates if they have the same 5' alignment positions (for both mates in the case of paired-end reads). All but the best pair (based on alignment score) will be marked as a duplicate in the BAM file. Marking duplicates is done using `Picard package <http://broadinstitute.github.io/picard/>`_.

.. _Picard RNA Metrics:

**Picard RNA Metrics**

Computes a series of quality control metrics using both CollectRnaSeqMetrics and CollectAlignmentSummaryMetrics functions metrics are collected using `Picard package <http://broadinstitute.github.io/picard/>`_.

.. _Estimate Ribosomal RNA:

**Estimate Ribosomal RNA**

This step uses readset BAM files and bwa mem to align reads on the rRNA reference fasta and count the number of read mapped The filtered reads are aligned to a reference fasta file of ribosomal sequence. The alignment is done per sequencing readset. The alignment software used is `BWA package <http://bio-bwa.sourceforge.net>`_ with algorithm: bwa mem. BWA output BAM files are then sorted by coordinate using `Picard package <http://broadinstitute.github.io/picard/>`_.

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

.. _Differential Expression:

**Differential Expression**

Performs differential gene expression analysis using `DESEQ package <https://bioconductor.riken.jp/packages/3.8/bioc/html/DESeq.html>`_ and `EDGER package <http://www.bioconductor.org/packages/release/bioc/html/edgeR.html>`_. Merge the results of the analysis in a single csv file.

.. _StringTie Step:

**StringTie Step**

Assemble transcriptome using `StringTie assembler <https://ccb.jhu.edu/software/stringtie/index.shtml>`_.

.. _StringTie Merge:

**StringTie Merge**

Merge assemblies into a master transcriptome reference using `StringTie assembler <https://ccb.jhu.edu/software/stringtie/index.shtml>`_.

.. _StringTie Abund:

**StringTie Abund**

Assemble transcriptome and compute RNA-seq expression using `StringTie <https://ccb.jhu.edu/software/stringtie/index.shtml>`_.

.. _Ballgown Gene Expression:

**Ballgown Gene Expression**

`Ballgown tool <https://bioconductor.org/packages/release/bioc/html/ballgown.html>`_ is used to calculate differential transcript and gene expression levels and test them for significant differences. 

.. _Sortmerna Step:

**Sortmerna Step**

This step calculates the ribosomal RNA per read based on known ribosomal sequences from archea, bacteria and eukaryotes. It uses `sortmeRNA <https://github.com/sortmerna/sortmerna>`_ protocol that takes trimmed fastqs and reports on each read, either paired-end or single end.

.. _Rnaseqc2:

**Rnaseqc2**

Computes a series of quality control metrics using `RNA-SeQC <https://data.broadinstitute.org/cancer/cga/tools/rnaseqc/RNA-SeQC_Help_v1.1.2.pdf>`_.

.. _Skewer Trimming:

**Skewer Trimming**

`Skewer <https://bmcbioinformatics.biomedcentral.com/articles/10.1186/1471-2105-15-182>`_ is used mainly for
detection and trimming adapter sequences from raw fastq files. Other features of Skewer is listed
`here <https://github.com/relipmoc/skewer>`_.

.. _Split N Trim:

**Split N Trim**

During the 'Split N Trim' step, a `GATK Tool <https://software.broadinstitute.org/gatk/>`_ called `SplitNCigarReads` developed specially for RNAseq, splits reads into exon segments. During this splitting, it gets rid of Ns but maintains grouping information and hard-clips any sequences overhanging into the intronic regions.

.. _Sambamba Merge Split N Trim Files:

**Sambamba Merge Split N Trim Files**

BAM readset files are merged into one file per sample. Merge is done using `Sambamba Merge <http://lomereiter.github.io/sambamba/docs/sambamba-merge.html>`_.

.. _Sambamba Merge Realigned:

**Sambamba Merge Realigned**

In this step, BAM files of regions of realigned reads are merged per sample using `Sambamba <http://lomereiter.github.io/sambamba/index.html>`_.

.. _GATK Indel Realigner:

**GATK Indel Realigner**

Insertion and deletion realignment is performed on regions where multiple base mismatches are preferred over indels by the aligner since it can appear to be less costly by the algorithm. Such regions will introduce false positive variant calls which may be filtered out by realigning those regions properly. Realignment is done using `GATK <https://www.broadinstitute.org/gatk/>`_. The reference genome is divided by a number regions given by the `nb_jobs` parameter.

.. _GATK Haplotype Caller:

**GATK Haplotype Caller**

`GATK haplotype caller step <https://gatk.broadinstitute.org/hc/en-us/articles/360037225632-HaplotypeCaller>`_ is used for SNPs and small indels. The Haplotype caller is capable of calling SNPs and indels simultaneously via local de-novo assembly of haplotypes in an active region. Regions that contain different types of variants close to each other are traditionally difficult to call. For such regions, HaplotypeCaller is more accurate. This is because whenever it encounters such regions with different types of variants, it discards the existing mapping information and completely reassembles the reads in that region.

.. _GATK Callable Loci:

**GATK Callable Loci**

This step computes the callable region or the genome as a BED track.

.. _Filter GATK:

**Filter GATK**

As part of filter GATK processing, a custom script is applied to inject FORMAT information - tumor/normal DP and VAP into the INFO field
of the filter on those generated fields.

.. _Recalibration:

**Recalibration**

In this step, we recalibrate the base quality scores of sequencing-by-synthesis reads in an aligned BAM file. After recalibration,
the quality scores in the QUAL field in each read in the output BAM are more accurate in that the reported quality score is closer to its actual probability of mismatching the reference genome. Moreover, the recalibration tool attempts to correct for variation in quality with machine cycle and sequence context, and by doing so, provides not only more accurate quality scores but also more widely dispersed ones.

.. _Merge HC VCF:

**Merge HC VCF**

Merges VCFs from `Haplotype caller <https://gatk.broadinstitute.org/hc/en-us/articles/360037225632-HaplotypeCaller>`_ to generate a sample level VCF.

.. _Run VCF Anno:

**Run VCF Anno**

`VCFAnno <https://github.com/brentp/vcfanno>`_ is used to annotate VCF files with preferred INFO fields from anu number of VCF or BED files.

.. _Variant Filtration:

**Variant Filtration**

`VariantFiltration <https://gatk.broadinstitute.org/hc/en-us/articles/4404604763547-VariantFiltration>`_ is a GATK tool for hard-filtering variant calls based on certain criteria. Records are hard-filtered
by changing the value in the FILTER field to something other than PASS.

.. _Decompose and Normalize:

**Decompose and Normalize**

The `vt Normalization <https://genome.sph.umich.edu/wiki/Vt#Normalization>`_ is used to normalized and decompose VCF files. For more
information about normalizing and decomposing visit `Variant Normalization <https://research-help.genomicsengland.co.uk/display/GERE/Variant+Normalisation>`_. An indexed file is also generated from the output file using `htslib <http://www.htslib.org/download/>`_.

.. _Compute SNP Effects:

**Compute SNP Effects**

`SnpEff <https://pcingola.github.io/SnpEff/>`_ is used to variant annotation and effect prediction on genes by using an interval forest approach. It annotates and predicts the effects of genetic variants, such as amino acid changes.

.. _Gemini Annotations:

**Gemini Annotations**

`Gemini <https://github.com/arq5x/gemini>`_ (GEnome MINIng) is used to integrative exploration of genetic
variation and genome annotations. See `latest Gemini documentation <https://gemini.readthedocs.io/en/latest/>`_ for more information.

.. _Report CPSR:

**Report CPSR**

In this step a `cpsr <https://sigven.github.io/cpsr/>`_ germline report is created input: filtered ensemble germline vcf
output: html report and addtional flat files.

.. _Report PCGR:

**Report PCGR**

Creates a `PCGR <https://sigven.github.io/pcgr/>`_  somatic + germline report. Input is a filtered ensemble germline VCF and the output is an html report with additional flat files.

.. _Run Arriba:

**Run Arriba**

`Arriba <https://github.com/suhrig/arriba>`_ is a command-line tool for the detection of gene fusions from RNA-Seq data. It is based on the `STAR <https://github.com/alexdobin/STAR>`_ aligner. Apart from gene fusions, Arriba can detect other structural rearrangements with potential clinical relevance, including viral integration sites, internal tandem duplications, whole exon duplications and intragenic inversions, etc.

.. _Run Annofuse:

**Run Annofuse**

`Annofuse <https://bmcbioinformatics.biomedcentral.com/articles/10.1186/s12859-020-03922-7>`_ is an R package used to annotate, prioritize, and interactively explore putative oncogenic RNA fusions.

.. _RSeqC:

**RSeqC**

RSeqC computes a series of quality control metrics using both CollectRnaSeqMetrics and CollectAlignmentSummaryMetrics functions
metrics are collected using `Picard <http://broadinstitute.github.io/picard/>`_.

.. _Multiqc Report:

**Multiqc Report** 

A quality control report for all samples is generated.
For more detailed information see `MultiQC documentation <http://multiqc.info/>`_.

.. include:: steps_cram_op.inc
