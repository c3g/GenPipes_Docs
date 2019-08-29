RNA Sequencing (Light) Pipeline 
================================

This is a lightweight RNA Sequencing Expression analysis pipeline based
on [Kallisto technique][Kallisto_id]. It is
used for quick Quality Control (QC) in gene sequencing studies.

* [Introduction](#introduction)
* [Version](#version)
* [Usage](#usage)
* [Example Run](#example-run)
* [Pipeline Schema](#pipeline-schema)
* [Pipeline Steps](#pipeline-steps)
* [More Information](#more-info)

Introduction
------------

The central computational problem in RNA-seq remains the efficient and accurate assignment of short sequencing reads to the transcripts they originated from and using this information to infer gene expressions. Conventionally, read assignment is carried out by aligning sequencing reads to a reference genome, such that relative gene expressions can be inferred by the alignments at annotated gene loci. These alignment-based methods are conceptually simple, but the read-alignment step can be time-consuming and computationally intensive.

Alignment-free RNA quantification tools have significantly increased the speed of RNA-seq analysis. The alignment-free pipelines are orders of magnitude faster than alignment-based pipelines, and they work by breaking sequencing reads into k-mers and then performing fast matches to pre-indexed transcript databases. To achieve fast transcript quantification without compromising quantification accuracy, different sophisticated algorithms were implemented in addition to k- mer counting, such as pseudo-alignments by [Kallisto technique][Kallisto_id] and quasi-mapping along with GC and sequence-bias corrections using [Salmon][Salmon_id].

RNA Sequencing Light is a lightweight pipeline that performs quick QC and removes a major computation bottleneck in RNA Sequence analysis. Kallisto is is two orders of magnitude faster than previous approaches and achieves similar accuracy. Kallisto pseudo-aligns reads to a reference, producing a list of transcripts that are compatible with each read while avoiding alignment of individual bases. For details refer to [More Information](#more-info) section below.

Version
-------

TBD

Usage
-----
```
rnaseq_light.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
                       [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]
                       [--json] [--report] [--clean]
                       [-l {debug,info,warning,error,critical}] [-d DESIGN]
                       [-t {cufflinks,stringtie}] [-r READSETS] [-v]
```

**Optional Arguments**

```
  -h                    show this help message and exit
  --help                show detailed description of pipeline and steps
  -c CONFIG [CONFIG ...], --config CONFIG [CONFIG ...]
                        config INI-style list of files; config parameters are
                        overwritten based on files order
  -s STEPS, --steps STEPS
                        step range e.g. '1-5', '3,6,7', '2,4-8'
  -o OUTPUT_DIR, --output-dir OUTPUT_DIR
                        output directory (default: current)
  -j {pbs,batch,daemon,slurm}, --job-scheduler {pbs,batch,daemon,slurm}
                        job scheduler type (default: slurm)
  -f, --force           force creation of jobs even if up to date (default:
                        false)
  --json                create a JSON file per analysed sample to track the
                        analysis status (default: false)
  --report              create 'pandoc' command to merge all job markdown
                        report files in the given step range into HTML, if
                        they exist; if --report is set, --job-scheduler,
                        --force, --clean options and job up-to-date status are
                        ignored (default: false)
  --clean               create 'rm' commands for all job removable files in
                        the given step range, if they exist; if --clean is
                        set, --job-scheduler, --force options and job up-to-
                        date status are ignored (default: false)
  -l {debug,info,warning,error,critical}, --log {debug,info,warning,error,critical}
                        log level (default: info)
  -d DESIGN, --design DESIGN
                        design file
  -t {cufflinks,stringtie}, --type {cufflinks,stringtie}
                        Type of RNA-seq assembly method (default cufflinks)
  -r READSETS, --readsets READSETS
                        readset file
  -v, --version         show the version information and exit

```

Example Run
-----------

TBD

Pipeline Schema
----------------

Refer to the diagram below for the schema of RNA Sequencing (Light) Pipeline.

![rnaseq_light workflow diagram](https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_rnaseq_light.resized.png)

You can [download a higher resolution diagram here](https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_rnaseq_light.png)

Pipeline Steps
--------------

|    | RNA Sequence Light Steps                                          |
| -- |:----------------------------------------------------------------- |
| 1. | [Picard SAM to FASTQ](#picard-sam-to-fastq)                       |
| 2. | [Trimmomatic](#trimmomatic)                                       |
| 3. | [Merge Trimmomatic Stats](#merge-trimmomatic-stats)               |
| 4. | [Kallisto](#kallisto)                                             |
| 5. | [Kallisto Count Matrix](#kallisto-count-matrix)                   |
| 6. | [GQ Seq Utils Exploratory](#gq-seq-utils-exploratory)             |
| 7. | [Sleuth Differential Expression](#sleuth-differential-expression) |

Step Details
-------------

#### Picard SAM to FASTQ

Convert SAM/BAM files from the input readset file into FASTQ format if FASTQ files are not already specified in the readset file. Do nothing otherwise.

#### Trimmomatic 

Raw reads quality trimming and removing of Illumina adapters is performed using [Trimmomatic](http://www.usadellab.org/cms/index.php?page=trimmomatic).  If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, 'Adapter1' and 'Adapter2' columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. For PAIRED_END readsets, readset adapters are reversed-complemented and swapped, to match Trimmomatic Palindrome strategy. For SINGLE_END readsets, only Adapter1 is used and left unchanged.

This step takes as input files:

1. FASTQ files from the readset file if available
2. Else, FASTQ output files from previous picard_sam_to_fastq conversion of BAM files

#### Merge Trimmomatic Stats

The trim statistics per readset are merged at this step.

#### Kallisto

Run Kallisto on fastq files for a fast estimate of abundance.

#### Kallisto Count Matrix

TBD

#### GQ Seq Utils Exploratory

Exploratory analysis using the gqSeqUtils R package adapted for RnaSeqLight.


#### Sleuth Differential Expression

Performs differential gene expression analysis using [Sleuth](http://pachterlab.github.io/sleuth/).  Analysis are performed both at a transcript and gene level, using two different tests: LRT and WT. 

# More Information

* Kallisto, a new [ultra-fast RNA Sequencing technique][ultra-fast-Kallisto-id]
* Limitations of alignment-free tools in [RNA sequencing quantification][limitation-Kallisto-id]

[//]: # (Following are the references of html links used in the text above.)

[Kallisto_id]: https://www.nature.com/articles/nbt.3519a
[ultra-fast-Kallisto-id]: http://nextgenseek.com/2015/05/kallisto-a-new-ultra-fast-rna-seq-quantitation-method/
[limitation-Kallisto-id]: https://www.biorxiv.org/content/biorxiv/early/2018/01/11/246967.full.pdf
[Salmon_id]: https://www.ncbi.nlm.nih.gov/pubmed/28263959
