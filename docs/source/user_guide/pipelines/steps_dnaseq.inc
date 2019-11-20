.. _docs_steps_dnaseq:

.. spelling::

    Haplotype
    FastQ
    config
    param
    bwa
    picard
    sam   
    BVATools
    vcf
    gvcfs
    recalibrator
    Omni
    Biomart
    dbNSFP
    dbSNP
    Polyphen
    PhyloP
    transversion
    gz
    nb
    varfilter
    snpAndIndelBCF
    covarying
    bcf
    Mappability

Step Details
-------------

Following are the various steps that are part of GenPipes DNA Sequencing genomic analysis pipeline:

.. _Picard SAM to FastQ:

**Picard SAM to FastQ**

Convert SAM/BAM files from the input readset file into FASTQ format if FASTQ files are not already specified in the readset file. Do nothing otherwise.

.. _Sym Link FastQ:

**Sym Link FastQ**

TBD-GenPipes-Dev

.. _Step Trimmomatic:

**Trimmomatic**

If available, this step takes FastQ file from the readset as input. Otherwise, FastQ output files from the previous `Picard SAM to FastQ`_ step, where BAM files are converted to FastQ format, are utilized in this step.

Raw reads quality trimming and removing of Illumina adapters is performed using `Trimmomatic`_. If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, 'Adapter1' and 'Adapter2' columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. For PAIRED_END readsets, readset adapters are reversed-complemented and swapped, to match Trimmomatic Palindrome strategy. For SINGLE_END readsets, only Adapter1 is used and left unchanged.

.. _Merge Trimmomatic Stats:

**Merge Trimmomatic Stats**

The trim statistics per readset file are merged in this step.

.. _Skewer Trimming:

**Skewer Trimming**

TBD

.. _BWA Picard Sort SAM:

**BWA Picard Sort SAM**

The input for this step is the trimmed FASTQ files if available. Otherwise, it uses the FASTQ files from the readset. If those are not available then it uses FASTQ output files from the previous 'Picard SAM to FastQ`_ step where BAM files are converted to FASTQ format.

In this step, filtered reads are aligned to a reference genome. The alignment is done per sequencing readset. The alignment software used is `BWA`_ with algorithm: bwa mem. BWA output BAM files are then sorted by coordinate using `Picard`_.

.. _SAMBAM Merge SAM Files:

**SAMBAM Merge SAM Files**

This step takes as input files:

* Aligned and sorted BAM output files from previous bwa_mem_picard_sort_sam step if available
* Else, BAM files from the readset file

In this step, BAM readset files are merged into one file per sample. Merge is done using `Picard`_.

.. _GATK Indel Re-aligner:

**GATK Indel Re-aligner**

Insertion and deletion realignment is performed on regions where multiple base mismatches are preferred over indels by the aligner since it can appear to be less costly by the algorithm. Such regions will introduce false positive variant calls which may be filtered out by realigning those regions properly. Realignment is done using `GATK Software`_. The reference genome is divided by a number regions given by the nb_jobs parameter.

.. _SAMBAM Merge Realigned:

**SAMBAM Merge Realigned**

In this step, BAM files of regions of realigned reads are merged per sample using `SAMBAMBA`_.

.. _Fix Mate by Coordinate:

**Fix Mate by Coordinate**

This step fixes the read mates. Once local regions are realigned, the read mate coordinates of the aligned reads need to be recalculated since the reads are realigned at positions that differ from their original alignment. Fixing the read mate positions is done using`BVATools`_.

.. _Picard Mark Duplicates:

**Picard Mark Duplicates**

This step marks duplicates. Aligned reads per sample are duplicates if they have the same 5' alignment positions (for both mates in the case of paired-end reads). All but the best pair (based on alignment score) will be marked as a duplicate in the BAM file. Marking duplicates is done using `Picard`_.

.. _Recalibration:

**Recalibration**

Recalibrate base quality scores of sequencing-by-synthesis reads in an aligned BAM file. After recalibration, the quality scores in the QUAL field in each read in the output BAM are more accurate in that the reported quality score is closer to its actual probability of mismatching the reference genome. Moreover, the recalibration tool attempts to correct for variation in quality with machine cycle and sequence context, and by doing so, provides not only more accurate quality scores but also more widely dispersed ones.

.. _Sym Link Final BAM:

**Sym Link Final BAM**

TBD

.. _Metrics DNA Picard:

**Metrics DNA Picard**

TBD

.. _Metrics DNA Sample Quality Map:

**Metrics DNA Sample Quality Map**

TBD

.. _Metrics DNA SAMBAM Flag Stats:

**Metrics DNA SAMBAM Flag Stats**

TBD

.. _Metrics DNA FastQC:

**Metrics DNA FastQC**

TBD

.. _Picard Calculate HS Metrics:

**Picard Calculate HS Metrics**

Compute on target percent of hybridization based capture happens in this step.

.. _GATK Callable Loci:

**GATK Callable Loci**

Computes the callable region or the genome as a bed track.

.. _Extract Common SNP Frequencies:

**Extract Common SNP Frequencies**

Extracts allele frequencies of possible variants across the genome.

.. _BAF Plot:

**BAF Plot**

Plots DepthRatio and B allele frequency of previously extracted alleles.

.. _GATK Haplotype Caller:

**GATK Haplotype Caller**

GATK Haplotype Caller is used for SNPs and small indels.

.. _Merge and call individual GVCF:

**Merge and call individual GVCF**

Merges the gvcfs of haplotype caller and also generates a per sample vcf containing genotypes.

.. _Combine GVCF:

**Combine GVCF**

Combine the per sample gvcfs of haplotype caller into one main file for all sample.

.. _Merge and call combined GVCF:

**Merge and call combined GVCF**

Merges the combined gvcfs and also generates a general vcf containing genotypes.

.. _Variant Recalibrator:

**Variant Recalibrator**

This step involves GATK variant recalibrator. The purpose of the variant recalibrator is to assign a well-calibrated probability to each variant call in a call set. You can then create highly accurate call sets by filtering based on this single estimate for the accuracy of each call. The approach taken by variant quality score recalibration is to develop a continuous, covarying estimate of the relationship between SNP call annotations (QD, MQ, HaplotypeScore, and ReadPosRankSum, for example) and the probability that a SNP is a true genetic variant versus a sequencing or data processing artifact. This model is determined adaptively based on "true sites" provided as input, typically HapMap 3 sites and those sites found to be polymorphic on the Omni 2.5M SNP chip array. This adaptive error model can then be applied to both known and novel variation discovered in the call set of interest to evaluate the probability that each call is real. The score that gets added to the INFO field of each variant is called the VQSLOD. It is the log odds ratio of being a true variant versus being false under the trained Gaussian mixture model. Using the tranche file generated by the previous step the ApplyRecalibration walker looks at each variant's VQSLOD value and decides which tranche it falls in. Variants in tranches that fall below the specified truth sensitivity filter level have their filter field annotated with its tranche level. This will result in a call set that simultaneously is filtered to the desired level but also has the information necessary to pull out more variants for a higher sensitivity but a slightly lower quality level.

.. _Haplotype caller decompose and normalize:

**Haplotype caller decompose and normalize**

TBD

.. _Haplotype caller flag mappability:

**Haplotype caller flag mappability**

Mappability annotation applied to haplotype caller vcf. An in-house database identifies regions in which reads are confidently mapped to the reference genome.

.. _Haplotype caller SNP ID annotation:

**Haplotype caller SNP ID annotation**

dbSNP annotation applied to haplotype caller vcf. The .vcf files are annotated for dbSNP using the software SnpSift (from the `SNPEff Suite`_).

.. _Haplotype caller SNP Effect:

**Haplotype caller SNP Effect**

Variant effect annotation applied to haplotype caller vcf. The .vcf files are annotated for variant effects using the `SNPEff Suite`_ software. SnpEff annotates and predicts the effects of variants on genes (such as amino acid changes).

.. _Haplotype caller dbNSFP annotation:

**Haplotype caller dbNSFP annotation**

Additional SVN annotations applied to haplotype caller vcf. Provides extra information about SVN by using numerous published databases. Applicable to human samples. Databases available include Biomart (adds GO annotations based on gene information) and dbNSFP (an integrated database of functional annotations from multiple sources for the comprehensive collection of human non-synonymous SNPs. It compiles prediction scores from four prediction algorithms (SIFT, Polyphen2, LRT and MutationTaster), three conservation scores (PhyloP, GERP++ and SiPhy) and other function annotations).

.. _Haplotype caller Gemini annotation:

**Haplotype caller Gemini annotation**

TBD

.. _Haplotype caller metrics VCF stats:

**Haplotype caller metrics VCF stats**

Metrics SNV applied to haplotype caller vcf. Multiple metrics associated to annotations and effect prediction are generated at this step: change rate by chromosome, changes by type, effects by impact, effects by functional class, counts by effect, counts by genomic region, SNV quality, coverage, InDel lengths, base changes, transition-transversion rates, summary of allele frequencies, codon changes, amino acid changes, changes per chromosome, change rates.

.. _Run MultiQC:

**Run MultiQC**

TBD

.. _Raw MPileup:

**Raw MPileup**

Full pileup (optional). A raw mpileup file is created using samtools mpileup and compressed in gz format. One packaged mpileup file is created per sample/chromosome.

.. _Compress Raw MPileup:

**Compress Raw MPileup**

Merge mpileup files per sample/chromosome into one compressed gzip file per sample.

.. _SNP and indel BCF:

**SNP and indel BCF**

Mpileup and Variant calling. Variants (SNPs and INDELs) are called using `SAMTools software package`_ mpileup. bcftools view is used to produce binary bcf files.

.. _Merge Filter BCF:

**Merge Filter BCF**

bcftools is used to merge the raw binary variants files created in the snpAndIndelBCF step. The output of bcftools is fed to varfilter, which does an additional filtering of the variants and transforms the output into the VCF (.vcf) format. One vcf file contain the SNP/INDEL calls for all samples in the experiment.

.. _MPileup decompose and normalize:

**MPileup decompose and normalize**

TBD

.. _MPileup Flag Mappability:

**MPileup Flag Mappability**

Mappability annotation applied to mpileup vcf. An in-house database identifies regions in which reads are confidently mapped to the reference genome.

.. _Mpileup SNP ID annotation:

**Mpileup SNP ID annotation**

dbSNP annotation applied to `MPileup`_ vcf. The .vcf files are annotated for dbSNP using the software SnpSift (from the `SNPEff Suite`_).

.. _MPileup SNP Effect:

**MPileup SNP Effect**

Variant effect annotation applied to mpileup vcf. The .vcf files are annotated for variant effects using the SnpEff software. SnpEff annotates and predicts the effects of variants on genes (such as amino acid changes).

.. _MPileup dbNSFP annotation:

**MPileup dbNSFP annotation**

Additional SVN annotations applied to mpileup vcf. Provides extra information about SVN by using numerous published databases. Applicable to human samples. Databases available include Biomart (adds GO annotations based on gene information) and dbNSFP (an integrated database of functional annotations from multiple sources for the comprehensive collection of human non-synonymous SNPs. It compiles prediction scores from four prediction algorithms (SIFT, Polyphen2, LRT and MutationTaster), three conservation scores (PhyloP, GERP++ and SiPhy) and other function annotations).

.. _MPileup Gemini annotation:

**MPileup Gemini annotation**

TBD

.. _MPileup Metrics VCF stats:

**MPileup Metrics VCF stats**

Metrics SNV applied to mpileup caller vcf. Multiple metrics associated to annotations and effect prediction are generated at this step: change rate by chromosome, changes by type, effects by impact, effects by functional class, counts by effect, counts by genomic region, SNV quality, coverage, InDel lengths, base changes, transition-transversion rates, summary of allele frequencies, codon changes, amino acid changes, changes per chromosome, change rates.

.. Following are the html link references:

.. _Trimmomatic: http://www.usadellab.org/cms/index.php?page=trimmomatic
.. _BWA: http://bio-bwa.sourceforge.net
.. _Picard: http://broadinstitute.github.io/picard/
.. _GATK Software: https://software.broadinstitute.org/gatk/
.. _SAMBAMBA: http://lomereiter.github.io/sambamba/index.html
.. _BVATools: https://bitbucket.org/mugqic/bvatools/src/master/
.. _SNPEff Suite: http://snpeff.sourceforge.net
