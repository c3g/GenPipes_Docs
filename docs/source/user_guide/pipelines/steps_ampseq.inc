.. _docs_steps_ampseq:

.. _Trimmomatic16S Step:

**Trimmomatic16S**

MiSeq raw reads adapter & primers trimming and basic QC is performed using `Trimmomatic`_. If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, Adapter1, Adapter2, Primer1 and Primer2 columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. Sequences are reversed-complemented and swapped. 

This step takes as input files: 

#. MiSeq paired-End FASTQ files from the readset file.

.. _Merge Trimmomatic Stats:

**Merge Trimmomatic Stats**

The trim statistics per readset are merged in this step.

.. _Flash Pass 1:

**Flash Pass 1**

Perform first pass of `FLASH`_. FLASH is a fast computational tool to extend the length of short reads by overlapping paired-end reads from fragment libraries that are sufficiently short.

.. _Flash Pass 2:

**Flash Pass 2**

Perform second pass of `FLASH`_ to find the correct overlap between paired-end reads and extend the reads by stitching them together.

.. _Amplicon Length Parser:

**Amplicon Length Parser**

In this step, we look at `FLASH`_ output to set amplicon lengths input for `DADA2`_. As minimum eligible length, a given length needs to have at least 1% of the total number of amplicons.

.. _Merge Flash Stats:

**Merge Flash Stats**

The paired end merge statistics per readset are merged in this step.

.. _ASVA:

**Asva**

This step checks for the design file required for the principal component analysis (PCA) based on amplicon sequence variant (ASV). 

.. _Run MultiQC:

**Run MultiQC**

A quality control report for all samples is generated.
See `MultiQC documentation <http://multiqc.info/>`_ for details.

.. Following are the html link references:

.. _Trimmomatic: http://www.usadellab.org/cms/index.php?page=trimmomatic
.. _FLASH: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3198573/
.. _DADA2: https://benjjneb.github.io/dada2/tutorial.html
