.. _cvmfs_modules:

GenPipes User Manual
====================

Bioinformatics resources
------------------------

C3G, in partnership with Compute Canada, offers and maintains a large set of bioinformatics resources for the community. Below is a list of software currently deployed on several HPC centres, including Guillimin, Cedar, Graham and Mammouth. Several reference genomes are also available.

To access these modules, you need to add the following lines to your .bashrc file.

.. code-block:: bash

    ## GenPipes/MUGQIC genomes and modules
    export MUGQIC_INSTALL_HOME=/cvmfs/soft.mugqic/CentOS6
    module use $MUGQIC_INSTALL_HOME/modulefiles


To explore the available tools, you can type:

module avail mugqic/
To load a module, for example samtools, you can use:

.. code-block:: bash

    # module add mugqic/<tool>/<version>
    module add mugqic/samtools/1.4.1
    # Now samtools 1.4.1 is available to use. To check:
    samtools



Available Modules
-----------------

Anaconda_, ASCAT_, `Aspera Connect`_, ATLAS_, BCFtools_, Beagle_, bedtools_, bismark_, BisSNP_, BLAST_, boost_, Bowtie_,
Bowtie2_, BbreakDancer_, butter_, bvatools_, BWA_, Bwakit_, CD-HIT_, `Cell Ranger`_, Cufflinks_, duk_, ea-utils_, emboss_,
EPACTS_, Exonerate_, FastQC_, FastTree_, FASTX-Toolkit_, FLASH_, gcc_, GEMINI_, GEM_, `Genome Analysis Toolkit`_,
Ghostscript_, Gnuplot_, HMMER_, HOMER_, HTSlib_, IGV_, igvtools_, Java_, JELLYFISH_, kentUtils_, KmerGenie_, KronaTools_,
LAPACK_, `Long Ranger`_, MACS_, MACS2_, miRDeep2_, mpich_, mugqic_pipelines_, mugqic_R_packages_, mugqic_tools_, MUMmer_,
MUSCLE_, MuTect_, NextClip_, OpenBLAS_, Pandoc_, parallel_, pbs-drmaa_, perl_, Picard_, pigz_, PRINSEQ-lite_, Prodigal_,
Python_, qualimap_, R_Bioconductor_, Ray_, RNAmmer_, RNA-SeQC_, RSEM_, SAMtools_, Scalpel_, ShortStack_, SignalP_,
SMRT-Analysis_, SNAP_, SnpEff_, Sphinx_, SPAdes_, SplAdder_, STAR_, Supernova_, Tabix_, TMHMM_, tools_, TopHat_,
TransDecoder_, Trimmomatic_, Trinity_, Tinotate_, `UCSC tools`_, USEARCH_, VarScan_, VCFtools_, VerifyBamID_, ViennaRNA_,
VSEARCH_, vt_, WebLogo_, `Celera Assembler`_

List of Modules
---------------

Anaconda
````````
Anaconda is a freemium open source distribution of the Python and R programming languages for large-scale data processing, predictive analytics, and scientific computing, that aims to simplify package management and deployment.
Versions Available: 2-4.0.0

ASCAT
`````
A tool for accurate dissection of genome-wide allele-specific copy number in tumors.
Versions Available: 2.3

Aspera Connect
``````````````
High-performance transfer plug-in
Versions Available: 3.3.3

ATLAS
`````
A data warehouse for integrative bioinformatics
Versions Available: 3.10.2

BCFtools
````````
Utilities for variant calling and manipulating VCFs and BCFs
Versions Available: 1.2, 1.3

Beagle
``````
Beagle is a software package that performs genotype calling, genotype phasing, imputation of ungenotyped markers, and identity-by-descent segment detection.
Versions Available: 03May16.862, r13994

bedtools
````````
A software suite for the comparison, manipulation and annotation of genomic features in browser extensible data (BED) and general feature format (GFF) format.
Versions Available: 2.17.0, 2.22.1, 2.25.0, 2.26.0

bismark
```````
Bismark is a program to map bisulfite treated sequencing reads to a genome of interest and perform methylation calls in a single step.
Versions Available: 0.16.1, 0.16.3, 0.17.0

BisSNP
``````
A bisulfite space genotyper & methylation caller
Versions Available: 0.82.2

BLAST
`````
Basic Local Alignment Search Tool
Versions Available: 2.2.29+, 2.3.0+

boost
`````
Boost provides free portable peer-reviewed C++ libraries. The emphasis is on portable libraries which work well with the C++ Standard Library.
Versions Available: 1.63.0

Bowtie
``````
An ultra fast, memory-efficient short read aligner.
Versions Available: 1.0.0, 1.1.2, 1.2.0

Bowtie2
```````
Bowtie 2 is an ultra fast and memory-efficient tool for aligning sequencing reads to long reference sequences.
Versions Available: 2.2.3, 2.2.4, 2.2.9

BbreakDancer
````````````
A Perl/C++ package that provides genome-wide detection of structural variants from next generation paired-end sequencing reads.
Versions Available: 1.1_2011_02_21

butter
``````
A wrapper for Bowtie to produce small RNA-seq alignments where multi-mapped small RNAs tend to be placed near regions of confidently high density.
Versions Available: 0.3.3

bvatools
````````
BVATools -- Bam and Variant Analysis Tools
Versions Available: 1.3, 1.4, 1.5, 1.6

BWA
```
A software package for mapping low-divergent sequences against a large reference genome, such as the human genome.
Versions Available: 0.7.10, 0.7.12

Bwakit
``````
Bwakit is a self-consistent installation-free package of scripts and precompiled binaries, providing an end-to-end solution to read mapping.
Versions Available: 0.7.12

CD-HIT
``````
CD-HIT is a very widely used program for clustering and comparing protein or nucleotide sequences.
Versions Available: 4.5.4-2011-03-07

Cell Ranger
```````````
Cell Ranger is a set of analysis pipelines that processes Chromium single cell 3â€™ RNA-seq output to align reads, generate gene-cell matrices and perform clustering and gene expression analysis.
Versions Available: 1.3.0

Cufflinks
`````````
Cufflinks assembles transcripts, estimates their abundances, and tests for differential expression and regulation in RNA-Seq samples.
Versions Available: 2.2.1

duk
```
Duk is a fast, accurate,and memory efficient DNA sequence matching tool. It finds whether a query sequence partially or totally matches given reference sequences or not, but it does not give how a query matches a reference sequence. The common application is to group sequencing reads into small manageable chunks for downstream analysis in assessing quality of a sequencing run, which includes contaminant removal (with contaminant sequences known), organelle genome separation, and assembly refinement.
Versions Available: 1.1

ea-utils
````````
A command-line tools for processing biological sequencing data. Barcode demultiplexing, adapter trimming, etc.
Versions Available: 1.1.2-537

emboss
``````
EMBOSS is 'The European Molecular Biology Open Software Suite'. EMBOSS is a free Open Source software analysis package specially developed for the needs of the molecular biology (e.g. EMBnet) user community.
Versions Available: 6.4.0, 6.6.0

EPACTS
``````
A versatile software pipeline to perform various statistical tests for identifying genome-wide association from sequence data through a user-friendly interface, both to scientific analysts and to method developers.
Versions Available: 3.2.6

Exonerate
`````````
A generic tool for pairwise sequence comparison.
Versions Available: 2.2.0

FastQC
``````
A quality control tool for high throughput sequence data.
Versions Available: 0.11.2, 0.11.5

FastTree
````````
FastTree infers approximately-maximum-likelihood phylogenetic trees from alignments of nucleotide or protein sequences.
Versions Available: 2.1.7

FASTX-Toolkit
`````````````
The FASTX-Toolkit is a collection of command line tools for Short-Reads FASTA/FASTQ files preprocessing.
Versions Available: 0.0.14

FLASH
`````
FLASH (Fast Length Adjustment of Short reads) is a very fast and accurate software tool to merge paired-end reads from next-generation sequencing experiments. FLASH is designed to merge pairs of reads when the original DNA fragments are shorter than twice the length of reads. The resulting longer reads can significantly improve genome assemblies.
Versions Available: 1.2.8, 1.2.11

gcc
```
The GNU Compiler Collection includes front ends for C, C++, Objective-C, Fortran, Java, Ada, and Go, as well as libraries for theselanguages (libstdc++, libgcj,...). GCC was originally written as the compiler for the GNU operating system.
Versions Available: 4.9.3

GEMINI
``````
Flexible framework for exploring genetic variation in the context of the wealth of genome annotations available for the human genome.
Versions Available: 0.18.0, 0.18.2, 0.18.3

GEM
```
The GEM library strives to be a true 'next-generation' tool for handling any kind of sequence data, offering state-of-the-art algorithms and data structures specifically tailored to this demanding task.
Versions Available: v1.315

Genome Analysis Toolkit
```````````````````````
Developed by the Data Science and Data Engineering group at the Broad Institute, the toolkit offers a wide variety of tools with a primary focus on variant discovery and genotyping.
Versions Available: 3.2-2, 3.3-0, 3.5, 3.7

Ghostscript
```````````
An interpreter for the PostScript language and for PDF.
Versions Available: '8.70'

Gnuplot
```````
Gnuplot is a portable command-line driven graphing utility for Linux, OS/2, MS Windows, OSX, VMS, and many other platforms.
Versions Available: 4.6.4, 4.6.6

HMMER
`````
HMMER is used for searching sequence databases for sequence homologs,and for making sequence alignments. It implements methods using probabilistic models called profile hidden Markov models (profile HMMs).
Versions Available: 2.3.2, 3.1b1, 3.1b2

HOMER
`````
HOMER offers tools and methods for interpreting Next-gen-Seq experiments.Â In addition to Genome Browser/UCSC visualization support and peak finding [and motif finding of course], HOMER can help assemble data across multiple experiments and look at positional specific relationships between sequencing tags, motifs, and other features. You do not need to use the peak finding methods in this package to use motif finding.
Versions Available: 4.7

HTSlib
``````
A C library for reading/writing high-throughput sequencing data
Versions Available: 1.2.1, 1.3

IGV
```
The Integrative Genomics Viewer (IGV) is a high-performance visualization tool for interactive exploration of large, integrated genomic datasets.
Versions Available: 2.3.23

igvtools
````````
The igvtools utility provides a set of tools for preprocessing data files. File names must contain an accepted file extension, e.g. test-xyz.bam.
Versions Available: 2.3.14, 2.3.67

Java
````
Java technology is the foundation of most networked applications and is used worldwide to develop and deliver mobile and nested applications, games, web content and enterprise software.
Versions Available: openjdk-jdk1.6.0_38, openjdk-jdk1.7.0_60, openjdk-jdk1.8.0_72

JELLYFISH
`````````
JELLYFISH is a tool for fast, memory-efficient counting of k-mers in DNA.
Versions Available: 2.1.3

kentUtils
`````````
UCSC command-line bioinformatic utilities, implemented by Jim Kent
Versions Available: 302.1.0

KmerGenie
`````````
KmerGenie estimates the best k-mer length for genome de Novo assembly.
Versions Available: 1.5692

KronaTools
``````````
Krona Tools is a set of scripts to create Krona charts from several Bioinformatics tools as well as from text and XML files.
Versions Available: 2.6.1

LAPACK
``````
LAPACK provides routines for solving systems of simultaneous linear equations, least-squares solutions of linear systems of equations, eigenvalue problems, and singular value problems.
Versions Available: 3.5.0

Long Ranger
```````````
Long Ranger is a set of analysis pipelines that processes Chromium sequencing output to align reads and call and phase SNPs, indels, and structural variants.
Versions Available: 2.1.2

MACS
````
Model-based Analysis of ChIP-Seq (MACS) on short reads sequencers such as Genome Analyzer (Illumina / Solexa)
Versions Available: 2.0.10.09132012

MACS2
`````
Novel algorithm, named Model-based Analysis of ChIP-Seq (MACS), for identifying transcript factor binding sites.
Versions Available: 2.1.0.20140616, 2.1.0.20151222, 2.1.1.20160309

miRDeep2
````````
miRDeep2 is a completely overhauled tool which discovers microRNA genes by analyzing sequenced RNAs. The tool reports known and hundreds of novel microRNAs with high accuracy in seven species representing the major animal clades. The low consumption of time and memory combined with user-friendly interactive graphic output makes miRDeep2 accessible for straightforward application in current research.
Versions Available: 0.0.8

mpich
`````
MPICH is a high performance and widely portable implementation of the Message Passing Interface (MPI) standard.
Versions Available: 3.1.4

mugqic_pipelines
````````````````
MUGQIC pipelines consist of Python scripts which create a list of jobs running Bash commands. Those scripts support dependencies between jobs and smart restart mechanism if some jobs fail during pipeline execution. Jobs can be submitted in different ways: by being sent to a PBS scheduler like Torque or by being run as a series of commands in batch through a Bash script
Versions Available: 2.0.1, 2.0.2, 2.1.0, 2.1.1, 2.2.0, 2.2.1

mugqic_R_packages
`````````````````
This library implements various -seq downstream analysis, as well as Nozzle-based reporting for mugqic_pipelines.
Versions Available: 1.0.1, 1.0.2, 1.0.3, 1.0.4

mugqic_tools
````````````
Perl, python, R, awk and sh scripts use in several bioinformatics pipelines of the MUGQIC PIPELINE.
Versions Available: 2.0.2, 2.0.3, 2.1.0, 2.1.1, 2.1.3, 2.1.4, 2.1.5, 2.1.6, 2.1.7

MUMmer
``````
Ultra-fast alignment of large-scale DNA and protein sequences
Versions Available: 3.23

MUSCLE
``````
Program for creating multiple alignments of protein sequences.
Versions Available: 3.8.31

MuTect
``````
Reliable and accurate identification of somatic point mutations in next generation sequencing data of cancer genomes
Versions Available: 1.1.6

NextClip
````````
Tool for analyzing reads from LMP libraries, generating a comprehensive quality report and extracting good quality trimmed and deduplicated reads
Versions Available: b833dd9

OpenBLAS
````````
Optimized BLAS library based on GotoBLAS2 1.13 BSD version
Versions Available: 0.2.14, 0.2.17

Pandoc
``````
Universal document converter
Versions Available: 1.13.1, 1.15.2

parallel
````````
Shell tool for executing jobs in parallel using one or more computers
Versions Available: 20130822

pbs-drmaa
`````````
DRMAA for Torque/PBS Pro is implementation of Open Grid Forum DRMAA (Distributed Resource Management Application API) specification for submission and control jobs to PBS systems
Versions Available: 1.0.18

perl
````
Feature-rich programming language
Versions Available: 5.18.2, 5.22.1

Picard
``````
Set of tools (in Java) for working with next generation sequencing data in the BAM format
Versions Available: 1.118, 1.123, 2.0.1

pigz
````
Replacement for gzip that exploits multiple processors and multiple cores when compressing data
Versions Available: 2.3

PRINSEQ-lite
````````````
Used to filter, reformat, or trim your Genomic and Metagenomic sequence data
Versions Available: 0.20.3, 0.20.4

Prodigal
````````
Prodigal (Prokaryotic Dynamic Programming Gene finding Algorithm) is a microbial (bacterial and archaeal) gene finding program developed at Oak Ridge National Laboratory and the University of Tennessee.
Versions Available: 2.6.3

Python
``````
Programming language that lets you work quickly and integrate systems more effectively
Versions Available: 2.7.8, 2.7.10_qiime, 2.7.11, 2.7.12, 2.7.13, 3.4.0, 3.5.2

qualimap
````````
Qualimap is a platform-independent application written in Java and R that provides both a Graphical User Interface (GUI) and a command-line interface to facilitate the quality control of alignment sequencing data.
Versions Available: 2.2.1

R_Bioconductor
``````````````
face (GUI) and a command-line interface to facilitate the quality control of alignment sequencing data
Versions Available: 3.1.2_3.0, 3.2.3_3.2

Ray
```
Parallel genome assemblies for parallel DNA sequencing
Versions Available: 2.3.1

RNAmmer
```````
Predicts 5s/8s, 16s/18s, and 23s/28s ribosomal RNA in full genome sequences.
Versions Available: 1.2

RNA-SeQC
````````
Java program which computes a series of quality control metrics for RNA-seq data
Versions Available: 1.1.7, 1.1.8

RSEM
````
Accurate quantification of gene and isoform expression from RNA-Seq data
Versions Available: 1.2.12

SAMtools
````````
A suite of programs for interacting with high-throughput sequencing data.
Versions Available: 0.1.19, 1.0, 1.2, 1.3, 1.3.1

Scalpel
```````
Software package for detecting INDELs (INsertions and DELetions) mutations in a reference genome
Versions Available: 0.3.2, 0.5.2

ShortStack
``````````
Tool developed to process and analyze small RNA-seq data with respect to a reference genome, and output a comprehensive and informative annotation of all discovered small RNA genes
Versions Available: 3.3

SignalP
```````
Predicts the presence and location of signal peptide cleavage sites in amino acid sequences from different organisms
Versions Available: 4.1

SMRT-Analysis
`````````````
Pacbio secondary analysis through a graphical or command-line user interface.
Versions Available: 2.3.0.140936.p1, 2.3.0.140936.p2, 2.3.0.140936.p4, 2.3.0.140936.p5

SNAP
````
General purpose gene finding program suitable for both eukaryotic and prokaryotic genomes
Versions Available: '2013-11-29'

SnpEff
``````
Variant annotation and effect prediction tool. It annotates and predicts the effects of variants on genes
Versions Available: 3.6, 4.0, 4.2

Sphinx
``````
Sphinx is a tool that makes it easy to create intelligent and beautiful documentation of Python projects
Versions Available: master

SPAdes
``````
SPAdes â€“ St. Petersburg genome assembler â€“ is an assembly toolkit containing various assembly pipelines.
Versions Available: 3.10.0

SplAdder
````````
Splicing Adder, a toolbox for alternative splicing analysis based on RNA-Seq alignment data. Briefly, the software takes a given annotation and RNA-Seq read alignments, transforms the annotation into a splicing graph representation, augments the splicing graph with additional information extracted from the read data, extracts alternative splicing events from the graph and quantifies the events.
Versions Available: 1.0.0

STAR
````
Spliced Transcripts Alignment to a Reference. Based on a previously undescribed RNA-seq alignment algorithm that uses sequential maximum mappable seed search in uncompressed suffix arrays followed by seed clustering and stitching procedure.
Versions Available: 2.4.0f1, 2.5.0c, 2.5.1b, 2.5.2a, 2.5.2b

Supernova
`````````
Supernova is a software package for de Novo assembly from Chromium Linked-Reads that are made from a single whole-genome library from an individual DNA source.
Versions Available: 1.1.4

Tabix
`````
Tabix indexes a TAB-delimited genome position file in.tab.bgz and creates an index file ( in.tab.bgz.tbi or in.tab.bgz.csi ) when region is absent from the command-line.
Versions Available: 0.2.6

TMHMM
`````
Predicting Transmembrane Protein Topology with a Hidden Markov Model
Versions Available: 2.0c

tools
`````
Perl, Python, R, awk and sh scripts use in several bioinformatics pipelines of the MUGQIC PIPELINES repo.
Versions Available: 1.10.4

TopHat
``````
TopHat is a fast splice junction mapper for RNA-Seq reads. It aligns RNA-Seq reads to mammalian-sized genomes using the ultra high-throughput short read aligner Bowtie, and then analyzes the mapping results to identify splice junctions between exons.
Versions Available: 2.0.13, 2.0.14

TransDecoder
````````````
TransDecoder identifies candidate coding regions within transcript sequences, such as those generated by de Novo RNA-Seq transcript assembly using Trinity, or constructed based on RNA-Seq alignments to the genome using Tophat and Cufflinks
Versions Available: 2.0.1

Trimmomatic
```````````
Trimmomatic performs a variety of useful trimming tasks for Illumina paired-end and single ended data.The selection of trimming steps and their associated parameters are supplied on the command line.
Versions Available: 0.32, 0.35, 0.36

Trinity
```````
Trinity assembles transcript sequences from Illumina RNA-Seq data
Versions Available: 20140413p1, 2.0.4, 2.1.1, 2.2.0

Tinotate
````````
A comprehensive annotation suite for functional annotation of transcriptomes, particularly de Novo assembled transcriptomes, from model or non-model organisms. Trinotate makes use of a number of different well referenced methods for functional annotation including homology search to known sequence data (BLAST+/SwissProt), protein domain identification (HMMER/PFAM), protein signal peptide and transmembrane domain prediction (signalP/tmHMM), and leveraging various annotation databases (eggNOG/GO/Kegg databases).
Versions Available: 20131110, 2.0.1, 2.0.2

UCSC tools
``````````
UCSC genome browser 'kent' bioinformatic utilities
Versions Available: 20140212, v326

USEARCH
```````
Ultra-fast search for high-identity top hit or hits from sequence files
Versions Available: 7.0.1090, 8.1.1861

VarScan
```````
VarScan is a platform-independent mutation caller for targeted, exome, and whole-genome resequencing data generated on Illumina, SOLiD, Life/PGM, Roche/454 and similar instruments. It can be used to detect different types of variation: Germline variants, multi-sample variants, somatic mutations and somatic copy number alterations
Versions Available: 2.3.9

VCFtools
````````
A program package that can be used to perform the following operations on standard variants (VCF) files: Filter out specific variantsCompare filesSummarize variantsConvert to different file typesValidate and merge filesCreate intersections and subsets of variants
Versions Available: 0.1.11, 0.1.14

VerifyBamID
```````````
Verifies whether the reads in particular file match previously known genotypes for an individual (or group of individuals), and checks whether the reads are contaminated as a mixture of two samples. verifyBamID can detect sample contamination and swaps when external genotypes are available. When external genotypes are not available, verifyBamID still robustly detects sample swaps
Versions Available: devMaster_20151216

ViennaRNA
`````````
The ViennaRNA Package consists of a C code library and several stand-alone programs for the prediction and comparison of RNA secondary structures.
Versions Available: 2.3.0

VSEARCH
```````
VSEARCH supports de Novo and reference based chimera detection, clustering, full-length and prefix dereplication, reverse complementation, masking, all-vs-all pairwise global alignment, exact and global alignment searching, shuffling, subsampling and sorting. It also supports FASTQ file analysis, filtering and conversion.
Versions Available: 1.11.1

vt
``
A tool set for short variant discovery in genetic sequence data.
Versions Available: 0.57

WebLogo
```````
A tool for creating sequence logos from biological sequence alignments. It can be run on the command line as a standalone webserver, as a CGI webapp, or as a python library.
Versions Available: 2.8.2, 3.3

Celera Assembler
````````````````
A de Novo whole-genome shotgun (WGS) DNA sequence assembler. It reconstructs long sequences of genomic DNA from fragmentary data produced by whole-genome shotgun sequencing
Versions Available: 8.1, 8.2, 0.0, 0.2
