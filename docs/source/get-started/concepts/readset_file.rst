:orphan:

.. _docs_readset_file:

Readset File
============

Readsets refer to replicates that belong to a particular sample. If a sample was divided over 3 lanes, each lane output would be a readset of that sample. Most pipelines merge readsets and run the analysis based on samples. You can think of readsets as technical replicates while Samples as biological replicates.

.. note::  **Why does GenPipes need Readset file?**

        A readset file is another file that accompanies our pipelines. While the configuration files contains information about the parameters needed by the tools in the pipeline, the readset file contains information about the samples to be analyzed. In the Readset file, you list each readset used for the analysis, which samples are to be merged and where your fastq files or bam files are located.


Readset File format
===================

The readset file is a tab-separated file that contains the following information:

+------------------+-------------------------------------------------------------------------------------------+
|   *Field*        |   *Contents*                                                                              |
+==================+===========================================================================================+
| **Sample:**      | Sample must contain letters A-Z, numbers 0-9, hyphens (-) or underscores (_) only; BAM    |
|                  | files will be merged into a file named after this value; mandatory.                       |
|                  |                                                                                           | 
|                  | |sample_note_francois|                                                                    | 
|                  |                                                                                           | 
+------------------+-------------------------------------------------------------------------------------------+
|**Readset:**      | a unique readset name with the same allowed characters as above; mandatory.               |
+------------------+-------------------------------------------------------------------------------------------+
|**Library:**      | optional.                                                                                 |
+------------------+-------------------------------------------------------------------------------------------+
|**RunType:**      | PAIRED_END or SINGLE_END; mandatory.                                                      |
+------------------+-------------------------------------------------------------------------------------------+
|**Run:**          | mandatory.                                                                                | 
+------------------+-------------------------------------------------------------------------------------------+
|**Lane:**         | mandatory.                                                                                |
+------------------+-------------------------------------------------------------------------------------------+
|**Adapter1:**     | sequence of the forward trimming adapter                                                  |
+------------------+-------------------------------------------------------------------------------------------+
|**Adapter2:**     | sequence of the reverse trimming adapter                                                  |
+------------------+-------------------------------------------------------------------------------------------+
|**QualityOffset:**| quality score offset integer used for trimming; optional.                                 |
+------------------+-------------------------------------------------------------------------------------------+
|**BED:**          | relative or absolute path to BED file; optional.                                          |
+------------------+-------------------------------------------------------------------------------------------+
|**FASTQ1:**       | relative or absolute path to first FASTQ file for paired-end readset or single FASTQ file |
|                  | for single-end readset; mandatory if BAM value is missing.                                |
+------------------+-------------------------------------------------------------------------------------------+
|**FASTQ2:**       | relative or absolute path to second FASTQ file for paired-end readset; mandatory if       |
|                  | RunType value is “PAIRED_END”.                                                            |
+------------------+-------------------------------------------------------------------------------------------+
|**BAM:**          | relative or absolute path to BAM file which will be converted into FASTQ files if they are|
|                  |  not available; mandatory if FASTQ1 value is missing, ignored otherwise.                  |
+------------------+-------------------------------------------------------------------------------------------+

.. note::

        If some optional information is missing, leave its position empty.

Difference between a Genome Sample File and Readset file
========================================================

Readsets refer to replicates that belong to a particular sample. If a sample was divided over 3 lanes, each lane output would be a readset of that sample. Most pipelines merge readsets and run the analysis based on samples. You can think of readsets as technical replicates while Samples as biological replicates.

Creating a Readset File
=======================
If you have access to Abacus, we provide a script $MUGQIC_PIPELINES_HOME/utils/nanuq2mugqic_pipelines.py that can access your Nanuq data, creates symlinks to the data on Abacus and creates the Readset file for you.

If your data is on nanuq but you do not have access to Abacus, there is a helper script $MUGQIC_PIPELINES_HOME/utils/csvToreadset.R that takes a csv file downloadable from nanuq and creates the Readset file. However, you will have to download the data from Nanuq yourself.

If your data is not on nanuq, you will have to manually create the Readset file. You can use a template and enter your samples manually. Remember that it is a tab separated file. There is a helper $MUGQIC_PIPELINES_HOME/utils/mugqicValidator.py script that can validate the integrity of your readset file.

Example of Readset File
=======================

::

            Sample Readset Library RunType Run Lane Adapter1 Adapter2 QualityOffset BED FASTQ1 FASTQ2 BAM

            sampleA readset1 lib0001 PAIRED_END run100 1 AGATCGGAAGAGCACACGTCTGAACTCCAGTCA AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT 33 path/to/file.bed path/to/readset1.paired1.fastq.gz path/to/readset1.paired2.fastq.gz path/to/readset1.bam

            sampleA readset2 lib0001 PAIRED_END run100 2 AGATCGGAAGAGCACACGTCTGAACTCCAGTCA AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT 33 path/to/file.bed path/to/readset2.paired1.fastq.gz path/to/readset2.paired2.fastq.gz path/to/readset2.bam

            sampleB readset3 lib0002 PAIRED_END run200 5 AGATCGGAAGAGCACACGTCTGAACTCCAGTCA AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT 33 path/to/file.bed path/to/readset3.paired1.fastq.gz path/to/readset3.paired2.fastq.gz path/to/readset3.bam

            sampleB readset4 lib0002 PAIRED_END run200 6 AGATCGGAAGAGCACACGTCTGAACTCCAGTCA AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT 33 path/to/file.bed path/to/readset4.paired1.fastq.gz path/to/readset4.paired2.fastq.gz path/to/readset4.bam

.. Add a note from Francois via Paul S regarding Sample definition

.. |sample_note_francois| replace:: **Note**:  The definition of a sample in the context of GenPipes is the "input" biological sample, i.e. the sample on which processing such as IP, IgG assay (ChIPSeq Pipeline) or nothing (input) was performed. This is in contrast to sample being defined as the "sample sent for sequencing".
