.. spelling:word-list::

     Flowcell

.. dropdown:: :material-outlined:`report;2em` Nanopore Readset Format
   :color: info

     Use the following **readset** file format for Nanopore, Nanopore CoV-Seq pipelines:

     * Sample: must contain letters A-Z, numbers 0-9, hyphens (-) or underscores (_) only; mandatory;
     * Readset: a unique readset name with the same allowed characters as above; mandatory;
     * Run: a unique ONT run name, usually has a structure similar to PAE0000_a1b2c3d;
     * Flowcell: code of the type of Flowcell used, for example: the code for PromethION Flow Cell (R9.4) is FLO-PRO002;
     * Library: code of the type of library preparation kit used, for example: the code for the Ligation Sequencing Kit is SQK-LSK109;
     * Summary: path to the sequencing_summary.txt file outputted by the ONT basecaller; mandatory;
     * FASTQ: mandatory, path to the fastq_pass directory, that is usually created by the basecaller
     * FAST5: path to the directory containing the raw fast5 files, before basecalling

     Example:

     +--------+----------+------------------+-----------------+-------------+----------------------------------------+-----------------------------+-----------------------------+
     |Sample  | Readset  | Run              | Flowcell        | Library     | Summary                                | FASTQ                       | FAST5                       |
     +--------+----------+------------------+-----------------+-------------+----------------------------------------+-----------------------------+-----------------------------+
     |sampleA | readset1 | PAE00001_abcd123 | FLO-PRO002      | SQK-LSK109  |path/to/readset1_sequencing_summary.txt | path/to/readset1/fastq_pass | path/to/readset1/fast5_pass |
     +--------+----------+------------------+-----------------+-------------+----------------------------------------+-----------------------------+-----------------------------+          
     |sampleA |readset2  | PAE00002_abcd456 | FLO-PRO002      | SQK-LSK109  |path/to/readset2_sequencing_summary.txt | path/to/readset2/fastq_pass | path/to/readset2/fast5_pass |
     +--------+----------+------------------+-----------------+-------------+----------------------------------------+-----------------------------+-----------------------------+
     |sampleA |readset3  | PAE00003_abcd789 | FLO-PRO002      | SQK-LSK109  |path/to/readset3_sequencing_summary.txt | path/to/readset3/fastq_pass | path/to/readset3/fast5_pass | 
     +--------+----------+------------------+-----------------+-------------+----------------------------------------+-----------------------------+-----------------------------+
     |sampleA |readset4  | PAE00004_abcd246 | FLO-PRO002      | SQK-LSK109  |path/to/readset4_sequencing_summary.txt | path/to/readset4/fastq_pass | path/to/readset4/fast5_pass |
     +--------+----------+------------------+-----------------+-------------+----------------------------------------+-----------------------------+-----------------------------+



     
