.. _docs_steps_hicseq:

Step Details
------------

Following are the various steps that are part of Hi-C genomic analysis pipelines:

.. _Samtools Bam Sort:

**Samtools Bam Sort**

Sorts bam by readname prior to picard_sam_to_fastq step in order to minimize memory consumption.  If bam file is small and the memory requirements are reasonable, this step can be skipped.

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

.. _Fastq ReadName Edit:

**Fastq ReadName Edit**

Removes the added /1 and /2 by picard's sam_to_fastq transformation to avoid issues with downstream software like HOMER.

.. _Hicup Align:

**Hicup Align** 

Paired-end Hi-C reads are truncated, mapped and filtered using HiCUP. The resulting bam file is filtered for Hi-C artifacts and duplicated reads. It is ready for use as input for downstream analysis.  For more detailed information about the HICUP process visit `HiCUP Project Page <https://www.bioinformatics.babraham.ac.uk/projects/hicup/overview/>`_.

.. _Samtools Merge Bams:

**Samtools Merge Bams**

BAM readset files are merged into one file per sample. Merge is done using `samtools <http://samtools.sourceforge.net/>`_.
This step takes as input files the aligned bams/sams from the hicup_align step.

.. _Homer Tag Directory:

**Homer Tag Directory** 

The bam file produced by HiCUP is used to create a tag directory using HOMER for further analysis that includes interaction matrix generation, compartments and identifying significant interactions. For more details, visit `Homer Page <http://homer.ucsd.edu/homer/interactions/index.html>`_.

.. _Interaction Matrices Chr:

**Interaction Matrices Chr** 

In this step, intra-chromosomal interaction matrices are produced by `Homer Matrices <http://homer.ucsd.edu/homer/interactions/HiCmatrices.html>`_ at resolutions defined in the ini config file and plotted by `HiCPlotter <https://github.com/kcakdemir/HiCPlotter>`_. 

.. _Interaction Matrices Genome:

**Interaction Matrices Genome** 

Genome-wide interaction matrices are produced by Homer at resolutions defined in the ini config file. See `Homer Matrices <http://homer.ucsd.edu/homer/interactions/HiCmatrices.html>`_ for details.

.. _Identify Compartments:

**Identify Compartments**

Genomic compartments are identified using Homer at resolutions defined in the ini config file. For details, see `Homer Compartments <http://homer.ucsd.edu/homer/interactions/HiCpca.html>`_.

.. _Identify TADs TopDom:

**Identify TADs TopDom** 

Topological associating Domains (TADs) are identified using TopDom at resolutions defined in the ini config file. For details, see `TopDom <https://www.ncbi.nlm.nih.gov/pubmed/26704975>`_.

.. _Identify TADs RobusTAD:

**Identify TADs RobusTAD**

In this step, topological associating Domain (TAD) scores are calculated using RobusTAD for every bin in the genome.  RobusTAD is resolution-independent and will use the first resolution in "resolution_TADs" under [identify_TADs] in the ini file.  For details, see `latest README.md for RobusTAD <https://github.com/rdali/RobusTAD>`_.

.. _Identify Peaks:

**Identify Peaks** 

This step users `Homer Peaks <http://homer.ucsd.edu/homer/interactions/HiCinteractions.html>`_ to identify significant intra-Chromosomal interactions or **peaks**.

.. _Create Rmap File:

**Create Rmap File** 

In this step, the Rmap file for Chicago capture analysis is created using the HiCUP digestion file.

.. _Create Baitmap File:

**Create Baitmap File** 

Here, the baitmap file for Chicago capture analysis is created using the created rmap file and the probe capture bed file.

.. _Create Design Files:

**Create Design Files**

In this step, the design files (`NPerBin file`_ (.npb), nbaitsperbin file (.nbpb), `Proximal Other End`_ (proxOE) file (.poe)) for Chicago capture analysis are created using the rmap file and the baitmap file.

.. _Create Input Files:

**Create Input Files** 

Here, the input file (sample.chinput) for Chicago capture analysis is created using the rmap file, the baitmap file and the hicup aligned bam.

.. _Run Chicago:

**Run Chicago** 

Chicago is run on capture data. Chicago will filter capture hic artifacts and identify significant interactions. It will output data as a bed file and will also output SeqMonk and WashU tracks.  For more detailed information about the Chicago, including how to interpret the plots, visit `Chicago documentation`_.

.. _RunChicago FeatureOverlap:

**RunChicago FeatureOverlap** 

This step runs the feature enrichment of Chicago significant interactions. See `Chicago documentation`_ for details.

.. _Bait Intersect:

**Bait Intersect**

With a bed file as input, for example a bed of `GWAS`_ SNPs or features of interest, this method returns the lines in the bed file that intersect with the baits that have significant interactions. Input bed must have 4 columns (<chr> <start> <end> <annotation>) and must be tab separated.

.. _Capture Intersect:

**Capture Intersect** 

With bed file as input, for example a bed of GWAS SNPs or features of interest, this method returns the lines in the bed file that intersect with the captured ends ("Other Ends") that have significant interactions.  Input bed must have 4 columns (<chr> <start> <end> <annotation>) and must be tab separated.

.. _Create Hic File:

**Create Hic File** 

A .hic file is created per sample in order to visualize in JuiceBox, WashU `epigenome`_ browser or as input for other tools.
For more detailed information see `JuiceBox documentation <http://www.aidenlab.org/software.html>`_.

.. _Multiqc Report:

**Multiqc Report** 

A quality control report for all samples is generated.
For more detailed information see `MultiQC documentation <http://multiqc.info/>`_.

.. _Chicago documentation: https://bioconductor.org/packages/release/bioc/vignettes/Chicago/inst/doc/Chicago.html
.. _NPerBin file: http://regulatorygenomicsgroup.org/resources/Chicago_vignette.html
.. _Proximal Other End: https://buildmedia.readthedocs.org/media/pdf/chi-c/stable/chi-c.pdf
.. _GWAS: https://en.wikipedia.org/wiki/Genome-wide_association_study
.. _epigenome: https://www.genome.gov/about-genomics/fact-sheets/Epigenomics-Fact-Sheet
.. _WashU: https://epigenomegateway.wustl.edu 
