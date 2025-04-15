:orphan:

.. _docs_readset_file:

.. spelling:word-list::

     flowcell
     gz

Readset File
============

Readsets refer to replicates that belong to a particular sample. If a sample was divided over 3 lanes, each lane output would be a readset of that sample. Most pipelines merge readsets and run the analysis based on samples. You can think of readsets as technical replicates while Samples as biological replicates.

.. note::  **Why does GenPipes need Readset file?**

        A readset file is another file that accompanies our pipelines. While the configuration files contains information about the parameters needed by the tools in the pipeline, the readset file contains information about the samples to be analyzed. In the Readset file, you list each readset used for the analysis, which samples are to be merged and where your fastq files or bam files are located.


Readset File format
===================

.. warning::

     Readset file format may vary for different GenPipes Pipelines.  For example, ChIP-Seq and Nanopore pipelines use a slightly different readset format as compared to DNA-Seq, RNA-Seq or Covseq pipelines.

General Readset File Format
---------------------------

The general readset file format is meant for the following pipelines **only**. Refer to other pipeline specific readset file format in the subsequent sections if it does not belong to the list below:

#. DNA-Seq high Coverage,
#. RNA-Seq,
#. RNA-Seq De Novo Assembly,
#. Tumor Pair,
#. Methyl-Seq

For the pipelines listed above, the readset file is a tab-separated file that contains the information in the table below:

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
|                  | not available; mandatory if FASTQ1 value is missing, ignored otherwise.                   |
+------------------+-------------------------------------------------------------------------------------------+

.. note::

        If some optional information is missing, leave its position empty.

Example of Readset File
^^^^^^^^^^^^^^^^^^^^^^^

::

            Sample  Readset     Library RunType     Run     Lane    Adapter1                            Adapter2                            QualityOffset   BED                 FASTQ1                              FASTQ2                              BAM

            sampleA readset1    lib0001 PAIRED_END  run100  1       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed    path/to/readset1.paired1.fastq.gz   path/to/readset1.paired2.fastq.gz   path/to/readset1.bam

            sampleA readset2    lib0001 PAIRED_END  run100  2       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed    path/to/readset2.paired1.fastq.gz   path/to/readset2.paired2.fastq.gz   path/to/readset2.bam

            sampleB readset3    lib0002 PAIRED_END  run200  5       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed    path/to/readset3.paired1.fastq.gz   path/to/readset3.paired2.fastq.gz   path/to/readset3.bam

            sampleB readset4    lib0002 PAIRED_END  run200  6       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed    path/to/readset4.paired1.fastq.gz   path/to/readset4.paired2.fastq.gz   path/to/readset4.bam

.. _ref_example_ampliconseq_readset_file:

Amplicon Readset File Format
-----------------------------

The ampliconseq pipeline requires a slightly different readset file than the general readset format listed above. Amplicon sequencing pipeline readset file should have two additional columns called `primer1` and `primer2` referring to the primers that are used.  The sequence written in the columns "primer1" and "primer2" should be the adapter sequence followed by the primer sequence.

.. _ref_amplicon_readset_format:

+-------------------+---------------------+----------------------------------------+--------------------------------------------------+
| Adapter1          |     Adapter2        |   primer1                              |primer2                                           |
+===================+=====================+========================================+==================================================+
|<adapter1_sequence>|  <adapter2_sequence>|   <adapter1_sequence><primer1_sequence>|   <adapter2_sequence><primer2_sequence>          |
+-------------------+---------------------+----------------------------------------+--------------------------------------------------+

For example, consider 515f and 806r:

+--------+---------+---------+------------+------+------+------------------------------------+-----------------------------------+------------------------------------------------------+-------------------------------------------------------+--------------+---------------------------------------------------------+---------------------------------------------------------+-----------+-------+   
| Sample | Readset | Library |   RunType  | Run  | Lane | Adapter1                           | Adapter2                          | primer1                                              |  primer2                                              |QualityOffset |    BED                                                  | FASTQ1                                                  |   FASTQ2  | BAM   |
+========+=========+=========+============+======+======+====================================+===================================+======================================================+=======================================================+==============+=========================================================+==================================================+======+===========+=======+
| 1340   | 1340    |1340     | PAIRED_END | 0123 | L001 | AGATCGGAAGAGCACACGTCTGAACTCCAGTCAC | AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT | AGATCGGAAGAGCACACGTCTGAACTCCAGTCACGTGYCAGCMGCCGCGGTAA| AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGTGGACTACHVGGGTWTCTAAT | 33           | raw_reads/Sample_1340/1340_S119_L001_R1_001.fastq.gz    |  raw_reads/Sample_1340/1340_S119_L001_R2_001.fastq.gz   |           |       |
+--------+---------+---------+------------+------+------+------------------------------------+-----------------------------------+------------------------------------------------------+-------------------------------------------------------+--------------+---------------------------------------------------------+---------------------------------------------------------+-----------+-------+   
| 1341   | 1341    |1341     | PAIRED_END | 0123 | L001 | AGATCGGAAGAGCACACGTCTGAACTCCAGTCAC | AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT | AGATCGGAAGAGCACACGTCTGAACTCCAGTCACGTGYCAGCMGCCGCGGTAA| AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGTGGACTACHVGGGTWTCTAAT | 33           | raw_reads/Sample_1341/1341_S120_L001_R1_001.fastq.gz    |  raw_reads/Sample_1341/1341_S120_L001_R2_001.fastq.gz   |           |       |
+--------+---------+---------+------------+------+------+------------------------------------+-----------------------------------+------------------------------------------------------+-------------------------------------------------------+--------------+---------------------------------------------------------+---------------------------------------------------------+-----------+-------+   

In case multiple Amplicon primers are used in the readset, they should all be listed in the same format() column, separated by semicolons. 

For example:

+----------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| primer1                                                                                                                                                              |
+======================================================================================================================================================================+
|ACACTGACGACATGGTTCTACACCTACGGGNGGCWGCAG;ACACTGACGACATGGTTCTACATCCTACGGGNGGCWGCAG;ACACTGACGACATGGTTCTACAACCCTACGGGNGGCWGCAG;ACACTGACGACATGGTTCTACACTACCTACGGGNGGCWGCAG |
+----------------------------------------------------------------------------------------------------------------------------------------------------------------------+

.. _ref_example_chipseq_readset_file:

ChIP-Seq Pipeline Readset File Format
-------------------------------------

Use the following readset file format for the ChIP-Seq Pipeline. **Do NOT** use the general readset file format above for ChIP-Seq pipeline.

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
|**MarkName:**     | Name of the histone mark; mandatory                                                       |
+------------------+-------------------------------------------------------------------------------------------+
|**MarkType:**     | Type of mark for MACS2 calling. It must be either B (Broad), N (Narrow) or I (Input);     |
|                  | mandatory                                                                                 |
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
|                  | not available; mandatory if FASTQ1 value is missing, ignored otherwise.                   |
+------------------+-------------------------------------------------------------------------------------------+

Example of ChIP-Seq Readset File
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

            Sample  Readset  MarkName MarkType Library RunType     Run     Lane    Adapter1                            Adapter2                            QualityOffset   BED                    FASTQ1                              FASTQ2                              BAM

            sampleA readset1 H3K27ac  N        lib0001 PAIRED_END  run100  1       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed       path/to/readset1.paired1.fastq.gz   path/to/readset1.paired2.fastq.gz   path/to/readset1.bam

            sampleA readset2 Input    I        lib0002 PAIRED_END  run200  6       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed       path/to/readset4.paired1.fastq.gz   path/to/readset4.paired2.fastq.gz   path/to/readset4.bam

            sampleB readset3 H3K27ac  N        lib0001 PAIRED_END  run100  2       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed       path/to/readset2.paired1.fastq.gz   path/to/readset2.paired2.fastq.gz   path/to/readset2.bam

            sampleB readset4 Input    I        lib0002 PAIRED_END  run200  5       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed       path/to/readset3.paired1.fastq.gz   path/to/readset3.paired2.fastq.gz   path/to/readset3.bam

.. note::

    The sample name of the treatment and control sample should be matched. 

    If there are multiple histone marks for the same sample, make sure that the sample name is the same for all.

.. _ref_example_longread_dnaseq_readset_file:

Long Read Readset File Format
-------------------------------

Use the long read readset file format for the following pipelines:

* Long Read DNA Sequencing Pipeline
* Nanopore Covseq Pipeline

**Do NOT** use the general readset file format for these pipelines.

+------------------------------+-------------------------------------------------------------------------------------------+
|   *Field*                    |   *Contents*                                                                              |
+==============================+===========================================================================================+
| **Sample:**                  | Sample must contain letters A-Z, numbers 0-9, hyphens (-) or underscores (_) only; BAM    |
|                              | files will be merged into a file named after this value; mandatory.                       |
|                              |                                                                                           | 
+------------------------------+-------------------------------------------------------------------------------------------+
|**Readset:**                  | A unique readset name with the same allowed characters as above; mandatory                |
+------------------------------+-------------------------------------------------------------------------------------------+
|**Run:**                      | A unique ONT run name, usually has a structure similar to PAE000_alb2c3d.                 | 
+------------------------------+-------------------------------------------------------------------------------------------+
|**Flowcell:**                 | Code of the type of flowcell used. For example, the code for PromethION Flow Cell (R9.4)  |
|                              | is FLO-PRO002.                                                                            | 
+------------------------------+-------------------------------------------------------------------------------------------+
|**Library:**                  | Code of the type of library preparation kit used. For example, the code for the Ligation  |
|                              | Sequencing Kit is SQK-LSK109.                                                             | 
+------------------------------+-------------------------------------------------------------------------------------------+
|**Summary**                   | Path to the ``sequencing_summary.txt`` file output by the ONT basecaller; mandatory.      | 
+------------------------------+-------------------------------------------------------------------------------------------+
|**FASTQ:**                    | The path to the ``fastq_pass`` **directory**, that is usually created by the basecaller;  |
|                              | mandatory.                                                                                | 
+------------------------------+-------------------------------------------------------------------------------------------+
|**FAST5:**                    | The path to the **directory** containing the raw fast5 files, before basecalling.         |
+------------------------------+-------------------------------------------------------------------------------------------+
|**BAM:**  (For Revio)         | BAM column is required for Revio protocol in case the FASTQ, FAST5 are not available. The |
|                              | relative/absolute path to BAM file that will be converted into FASTQ files if they are not|
|                              | available.                                                                                |
+------------------------------+-------------------------------------------------------------------------------------------+

Example of Long Read Readset File
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

::

     Sample  Readset     Run                 Flowcell    Library    Summary                                 FASTQ                         FAST5                           BAM (Optional)

     sampleA readset1    PAE00001_abcd123    FLO-PRO002  SQK-LSK109 path/to/readset1_sequencing_summary.txt path/to/readset1/fastq_pass   path/to/readset1/fast5_pass   path/to/sampleA/readset1/BAM/file

     sampleA readset2    PAE00002_abcd456    FLO-PRO002  SQK-LSK109 path/to/readset2_sequencing_summary.txt path/to/readset2/fastq_pass   path/to/readset2/fast5_pass   path/to/sampleA/readset2/BAM/file

     sampleA readset3    PAE00003_abcd789    FLO-PRO002  SQK-LSK109 path/to/readset3_sequencing_summary.txt path/to/readset3/fastq_pass   path/to/readset3/fast5_pass   path/to/sampleA/readset3/BAM/file

     sampleA readset4    PAE00004_abcd246    FLO-PRO002  SQK-LSK109 path/to/readset4_sequencing_summary.txt path/to/readset4/fastq_pass   path/to/readset4/fast5_pass   path/to/sampleA/readset4/BAM/file

Difference between a Genome Sample File and Readset file
========================================================

Readsets refer to replicates that belong to a particular sample. If a sample was divided over 3 lanes, each lane output would be a readset of that sample. Most pipelines merge readsets and run the analysis based on samples. You can think of readsets as technical replicates while Samples as biological replicates.

Creating a Readset File
=======================

If you have access to Abacus, we provide a script ``nanuq2mugqic_pipelines.py`` that can access your Nanuq data, creates symlinks to the data on Abacus and creates the Readset file for you.

If your data is on nanuq but you do not have access to Abacus, there is a helper script ``csvToreadset.R`` that takes a csv file downloadable from nanuq and creates the Readset file. However, you will have to download the data from Nanuq yourself.

If your data is not on nanuq, you will have to manually create the Readset file. You can use a template and enter your samples manually. Remember that it is a tab separated file. There is a helper ``mugqicValidator.py`` script that can validate the integrity of your readset file.

.. note::

     **For abacus users with Nanuq readsets**

     If your readsets belong to a `Nanuq <http://gqinnovationcenter.com/services/nanuq.aspx>`_ project, use ``nanuq2mugqic_pipelines.py`` script to automatically create a Readset File and symlinks to your readsets on abacus.

.. Add a note from Francois via Paul S regarding Sample definition

.. |sample_note_francois| replace:: **Note**:  The definition of a sample in the context of GenPipes is the "input" biological sample, i.e. the sample on which processing such as IP, IgG assay (ChIPSeq Pipeline) or nothing (input) was performed. This is in contrast to sample being defined as the "sample sent for sequencing".
