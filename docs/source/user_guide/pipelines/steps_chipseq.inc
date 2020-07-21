.. _docs_steps_chipseq:

.. spelling::

     config
     param
     bwa
     picard
     sam
     mfold
     intron
     introns

Step Details
-------------

Following are the various steps that are part of GenPipes ChIP-Seq genomic analysis pipeline:

.. _Picard Sam to Fastq:

**Picard Sam to Fastq**

If FASTQ files are not already specified in the Readset file, then this step converts SAM/BAM files from the input Readset into FASTQ format. Otherwise, it does nothing.

.. _Trimmomatic:

**Trimmomatic**

Raw reads quality trimming and removing of Illumina adapters is performed using `Trimmomatic Process <http://www.usadellab.org/cms/index.php?page=trimmomatic>`_.  If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, 'Adapter1' and 'Adapter2' columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. For PAIRED_END readsets, readset adapters are reversed-complemented and swapped, to match Trimmomatic Palindrome strategy. For SINGLE_END readsets, only Adapter1 is used and left unchanged.  

If available, trimmomatic step in Hi-C analysis takes FASTQ files from the readset file as input. Otherwise, it uses the FASTQ output file generated from the previous `Picard Sam to Fastq` step conversion of the BAM files. 

.. _Merge Trimmomatic Stats:

**Merge Trimmomatic Stats** 

The trim statistics per Readset file are merged at this step.

.. _BWA Mem Picard Sort:

**BWA Mem Picard Sort**

In this step, the filtered reads are aligned to a reference genome. The alignment is done per sequencing readset.  The alignment software used is `BWA <http://bio-bwa.sourceforge.net/>`_ with algorithm: bwa mem.  BWA output BAM files are then sorted by coordinate using `Picard`_.

This step takes as input files:

* Trimmed FASTQ files if available
* Else, FASTQ files from the readset file if available
* Else, FASTQ output files from previous picard_sam_to_fastq conversion of BAM files

.. _Samtools View Filter:

**Samtools View Filter**

This step filter unique reads by mapping quality using `Samtools`_.

.. _Picard Merge SAM Files:

**Picard Merge SAM Files**

BAM readset files are merged into one file per sample. Merge is done using `Picard`_.

This step takes as input files:

* Aligned and sorted BAM output files from previous bwa_mem_picard_sort_sam step if available
* Else, BAM files from the readset file

.. _Picard Mark Duplicates:

**Picard Mark Duplicates**

Mark duplicates. Aligned reads per sample are duplicates if they have the same 5' alignment positions (for both mates in the case of paired-end reads). All but the best pair (based on alignment score) will be marked as a duplicate in the BAM file. Marking duplicates is done using `Picard`_. 
 
.. _Metrics:

**Metrics**

The number of raw/filtered and aligned reads per sample are computed at this stage.

.. _Homer Make Tag Directory:

**Homer Make Tag Directory**

The Homer Tag directories, used to check for quality metrics, are computed at this step.

.. _QC Metrics:

**QC Metrics**

Sequencing quality metrics as tag count, tag autocorrelation, sequence bias and GC bias are generated.

.. _Homer Make UCSC file:

**Homer Make UCSC files**

Wiggle Track Format files are generated from the aligned reads using Homer.  The resulting files can be loaded in browsers like `IGV <https://software.broadinstitute.org/software/igv/>`_ or `UCSC <https://genome.ucsc.edu>`_.

.. _MACS2 call peak:

**MACS2 call peak**

Peaks are called using the `MACS2 <https://www.biorxiv.org/content/10.1101/496521v1>`_ software. Different calling strategies are used for narrow and broad peaks.  The mfold parameter used in the model building step is estimated from a peak enrichment diagnosis run.  The estimated mfold lower bound is 10 and the estimated upper bound can vary between 15 and 100.

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

.. _IEHC Preprocess file:

**IEHC Preprocess file**

This step generates `IHEC <http://ihec-epigenomes.org/research/tools/>`_ files.

.. _Run SPP:

**Run SPP**

This step runs spp to estimate NSC and RSC ENCODE metrics. For more information - see quality enrichment of ChIP sequence data, `phantompeakqualtools <https://github.com/kundajelab/phantompeakqualtools>`_.

.. _IHEC Metrics:

**IHEC Metrics**

This step generates IHEC's `standard metrics <http://ihec-epigenomes.org/research/reference-epigenome-standards/>`_.

.. _Multiqc Report:

**Multiqc Report** 

A quality control report for all samples is generated.
For more detailed information see `MultiQC documentation <http://multiqc.info/>`_.

.. _Samtools: http://www.htslib.org/
.. _Picard: http://broadinstitute.github.io/picard/
