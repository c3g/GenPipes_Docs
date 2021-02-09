.. _docs_tumor_pair_steps:

.. spelling::

      Somatics
      gzipped
      nb
      tdf
      bcftools 
      Mpileup
      snpAndIndelBCF
      varfilter
      vcflibs
      vcfsamplediff
      Bcbio
      germline
      haplotypes
      loh
      
Step Details
-------------

Following are the various steps that are part of GenPipes Tumor Pair Pipeline:

.. _Picard SAM to FastQ:

**Picard SAM to FastQ**

This step converts SAM/BAM files from the input readset file into FASTQ format, if FASTQ files are not already specified in the readset file. Otherwise, it does nothing.

.. _Trimmomatic:

**Trimmomatic**

This step takes as input files:

* FASTQ files from the readset file if available
* Else, FASTQ output files from previous picard_sam_to_fastq conversion of BAM files

Raw reads quality trimming and removing of Illumina adapters is performed using `Trimmomatic Method`_. If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, 'Adapter1' and 'Adapter2' columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. For PAIRED_END readsets, readset adapters are reversed-complemented and swapped, to match Trimmomatic Palindrome strategy. For SINGLE_END readsets, only Adapter1 is used and left unchanged.

.. _Merge Trimmomatic Stats:

**Merge Trimmomatic Stats**

The trim statistics per readset are merged at this step.

.. _BWA Picard Sort:

**BWA Picard Sort SAM**

This step takes as input files:

#. Trimmed FASTQ files if available
#. Else, FASTQ files from the readset file if available
#. Else, FASTQ output files from previous picard_sam_to_fastq conversion of BAM files


The filtered reads are aligned to a reference genome. The alignment is done per sequencing readset. The alignment software used is `BWA`_ with algorithm: bwa mem. BWA output BAM files are then sorted by coordinate using `Picard`_.

.. _SamBamba Merge Files:

**SamBamba Merge Files**

This step takes as input files:

* Aligned and sorted BAM output files from previous `BWA Picard Sort`_ step, if available
* Else, BAM files from the readset file

BAM readset files are merged into one file per sample. Merge is done using `Picard`_.

.. _GATK InDel Realigner:

**GATK InDel Realigner**

Insertion and deletion realignment is performed on regions where multiple base mismatches are preferred over indels by the aligner since it can appear to be less costly by the algorithm. Such regions will introduce false positive variant calls which may be filtered out by realigning those regions properly. Realignment is done using `GATK`_. The reference genome is divided by a number regions given by the nb_jobs parameter.

Note: modified to use both normal and tumor BAMs to reduce FPs around indels


.. _SamBamba Merge Realigned:

**SamBamba Merge Realigned**

BAM files of regions of realigned reads are merged per sample using `SamBamba`_.

.. _SamBamba Mark Duplicates:

**Sambamba Mark Duplicates**

Mark duplicates. Aligned reads per sample are duplicates if they have the same 5' alignment positions (for both mates in the case of paired-end reads). All but the best pair (based on alignment score) will be marked as a duplicate in the BAM file. Marking duplicates is done using `Picard`_.

.. _Recalibration:

**Recalibration**

This step re-calibrates base quality scores of sequencing-by-synthesis reads in an aligned BAM file. After recalibration, the quality scores in the QUAL field in each read in the output BAM are more accurate in that the reported quality score is closer to its actual probability of mismatching the reference genome. Moreover, the recalibration tool attempts to correct for variation in quality with machine cycle and sequence context, and by doing so, provides not only more accurate quality scores but also more widely dispersed ones.

.. _Conpair Concorance Contamination:

**Conpair Concorance Contamination**

`Conpair <https://github.com/nygenome/Conpair>`_ is a concordance and contamination estimator for tumor–normal pairs. This step is a quality control process to ensure the normal sample and cancer sample come from the same patient. It estimates this by determining the amount of normal sample in the tumor and the amount of tumor in normal sample.

.. _Raw Mpileup Panel:

**Raw Mpileup Panel**

Full pileup (optional). A raw Mpileup file is created using samtools Mpileup and compressed in gzipped format. One packaged Mpileup file is created per sample/chromosome.

.. _Paired VarScan 2:

**Paired VarScan 2**

This step involves variant calling and somatic mutation/CNV detection for next-generation sequencing data. For details see - `VarScan 2 Somatic mutation and copy number alteration discovery in cancer by exome sequencing <https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3290792/>`_.

This is a test.

.. _Merge VarScan 2 Panel:

**Merge VarScan 2 Panel**

Merge Mpileup files per sample/chromosome into one compressed gzip file per sample.

.. _PreProcess VCF Panel:

**PreProcess VCF Panel**

Preprocess VCF for loading into a annotation database called `Gemini`_. Processes include normalization and decomposition of MNPs by `Vt` and VCF modification for correct loading into `Gemini`_.

.. _SNP Effect Panel:

**SNP Effect Panel**

Variant effect annotation. The .vcf files are annotated for variant effects using the SnpEff software. SnpEff annotates and predicts the effects of variants on genes (such as amino acid changes).

.. _Gemini Annotations Panel:

**Gemini Annotations Panel**

Load functionally annotated VCF file into a MySQL lite annotation database `Gemini`_.

.. _Metrics:

**Metrics**

Compute metrics and generate coverage tracks per sample. Multiple metrics are computed at this stage: Number of raw reads, Number of filtered reads, Number of aligned reads, Number of duplicate reads, Median, mean and standard deviation of insert sizes of reads after alignment, percentage of bases covered at X reads (%_bases_above_50 means the % of exons bases which have at least 50 reads) whole genome or targeted percentage of bases covered at X reads (%_bases_above_50 means the % of exons bases which have at least 50 reads). A TDF (.tdf) coverage track is also generated at this step for easy visualization of coverage in the IGV browser.

.. _Picard Calculate HS Metrics:

**Picard Calculate HS Metrics**

Compute on target percent of hybridization based capture.

.. _GATK callable Loci:

**GATK callable Loci**

Computes the callable region or the genome as a bed track.

.. _Extract Common SNP Frequency:

**Extract Common SNP Frequency**

Extracts allele frequencies of possible variants across the genome.

.. _BAF Plot:

**BAF Plot**

Plots DepthRatio and B allele frequency of previously extracted alleles.

.. _Raw Mpileup:

**Raw Mpileup**

Full pileup (optional). A raw Mpileup file is created using samtools Mpileup and compressed in gzipped format. One packaged Mpileup file is created per sample/chromosome.


.. _Paired Var Scan 2:

**Paired Var Scan 2**

Variant calling and somatic mutation/CNV detection for next-generation sequencing data. Uses `VarScan 2`_ for Somatic mutation and copy number alteration discovery in cancer by exome sequencing `VarScan 2`_ thresholds based on `DREAM3 results`_ generated by SC INFO field remove to prevent collision with Samtools output during ensemble.

.. _Merge Var Scan 2:

**Merge Var Scan 2**

Merge Mpileup files per sample/chromosome into one compressed gzip file per sample.

.. _Paired Mutect2:

**Paired Mutect2**

`GATK MuTect2 Overview`_ caller for SNVs and Indels.

.. _Merge Mutect2:

**Merge Mutect2**

Merge SNVs and indels for `GATK MuTect2 Overview`_ Replace TUMOR and NORMAL sample names in VCF to the exact tumor/normal sample names Generate a somatic VCF containing only PASS variants

.. _SAM Tools Paired:

**SAM Tools Paired**

Samtools caller for SNVs and Indels using version 0.1.19.

.. _Merge Filter Paired SAM Tools:

**Merge Filter Paired SAM Tools**

In this step, `bcftools`_ is used to merge the raw binary variants files created in the snpAndIndelBCF step. The output of bcftools is fed to varfilter, which does an additional filtering of the variants and transforms the output into the VCF (.vcf) format. One VCF file contain the SNP/INDEL calls for all samples in the experiment. Additional somatic filters are performed to reduce the number of FPs: 1. vcflibs vcfsamplediff tags each variant with <tag>={`germline`_,`somatic`_,`loh`_} to specify the type of variant given the genotype difference between the two samples. 2. bcftools filter is used to retain only variants with CLR>=15 and have STATUS=somatic from VCFsamplediff 3. bcftools filter is used to retain only variants that have STATUS=germline or STATUS=loh from vcfsamplediff

.. _VarDict Paired:

**VarDict Paired**

In this step, `VarDict`_ caller is used for SNVs and Indels. Note: variants are filtered to remove instance where REF == ALT and REF modified to 'N' when REF is AUPAC nomenclature

.. _Merge Filter Paired VarDict:

**Merge Filter Paired VarDict**

The fully merged VCF is filtered using following steps: 1. Retain only variants designated as somatic by VarDict: either StrongSomatic or LikelySomatic 2. Somatics identified in step 1 must have PASS filter.

.. _Ensemble Somatic:

**Ensemble Somatic**

Apply `Bcbio.variations`_ ensemble approach for `GATK MuTect2 Overview`_, `VarDict`_, Samtools and `VarScan 2`_ calls Filter ensemble calls to retain only calls overlapping 2 or more callers

.. _GATK Variant Annotator Somatic:

**GATK Variant Annotator Somatic**

Add VCF annotations to ensemble VCF: Standard and Somatic annotations.

.. _Merge GATK Variant Annotator Somatic:

**Merge GATK Variant Annotator Somatic**

Merge annotated somatic VCFs.

.. _Compute Cancer Efects Somatic:

**Compute Cancer Efects Somatic**

Variant effect annotation. The .vcf files are annotated for variant effects using the SnpEff software. SnpEff annotates and predicts the effects of variants on genes (such as amino acid changes). Modified arguments to consider paired cancer data.

.. _Combine Tumor Pairs Somatic:

**Combine Tumor Pairs Somatic**

Combine numerous ensemble VCFs into one VCF for `Gemini`_ annotations.

.. _All Pairs Compute Effects Somatic:

**All Pairs Compute Effects Somatic**

Variant effect annotation. The .vcf files are annotated for variant effects using the SnpEff software. SnpEff annotates and predicts the effects of variants on genes (such as amino acid changes). Modified arguments to consider paired cancer data. Applied to all tumor pairs.

.. _Gemini Annotations Somatic:

**Gemini Annotations Somatic**

Load functionally annotated VCF file into a MySQL lite annotation database `Gemini`_.

.. _Ensemble Germline Loh:

**Ensemble Germline Loh**

Apply Bcbio.variations ensemble approach for `VarDict`_, Samtools and `VarScan 2`_ calls Filter ensemble calls to retain only calls overlapping 2 or more callers.

.. _GATK Variant Annotator Germline:

**GATK Variant Annotator Germline**

Add VCF annotations to ensemble VCF: most importantly the AD field.

.. _Merge GATK Variant Annotator Germline:

**Merge GATK Variant Annotator Germline**

Merge annotated germline and LOH VCFs.

.. _Compute Cancer Effects Germline:

**Compute Cancer Effects Germline**

Variant effect annotation. The .vcf files are annotated for variant effects using the SnpEff software. SnpEff annotates and predicts the effects of variants on genes (such as amino acid changes). Modified arguments to consider paired cancer data.

.. _Combine Tumor Pairs Germline:

**Combine Tumor Pairs Germline**

Combine numerous ensemble VCFs into one VCF for `Gemini`_ annotations.

.. _All Pairs Compute Effects Germline:

**All Pairs Compute Effects Germline**

Variant effect annotation. The .vcf files are annotated for variant effects using the SnpEff software. SnpEff annotates and predicts the effects of variants on genes (such as amino acid changes). Modified arguments to consider paired cancer data. Applied to all tumor pairs.

.. _Gemini Annotations Germline:

**Gemini Annotations Germline**

Load functionally annotated VCF file into a MySQL lite annotation database `Gemini`_.

.. include:: steps_cram_op.inc

.. Html links 

.. _Trimmomatic Method: http://www.usadellab.org/cms/index.php?page=trimmomatic
.. _BWA: http://bio-bwa.sourceforge.net/
.. _Picard: http://broadinstitute.github.io/picard/
.. _GATK: https://gatk.broadinstitute.org/hc/en-us
.. _SamBamba: http://lomereiter.github.io/sambamba/index.html
.. _Vt: http://genome.sph.umich.edu/wiki/Vt
.. _Gemini: http://gemini.readthedocs.org/en/latest/index.html
.. _DREAM3 results: https://github.com/dkoboldt/varscan/releases
.. _GATK MuTect2 Overview: https://gatk.broadinstitute.org/hc/en-us/articles/360037593851-Mutect2 
.. _bcftools: http://www.htslib.org/doc/bcftools.html
.. _loh: https://www.cancer.gov/publications/dictionaries/genetics-dictionary/def/loh
.. _germline: https://www.cancer.gov/publications/dictionaries/genetics-dictionary/def/germline-variant 
.. _somatic: https://www.cancer.gov/publications/dictionaries/genetics-dictionary/def/somatic-variant
.. _Bcbio.variations: https://github.com/chapmanb/bcbio.variation
.. _VarDict: https://www.ncbi.nlm.nih.gov/pubmed/27060149
