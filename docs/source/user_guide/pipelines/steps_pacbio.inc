.. _docs_steps_pacbio:

.. spelling::

    smrtpipe
    fofnToSmrtpieInput
    prinseq
    Celera
    refUploader
    topre
    pbdagcon
    fastqToCA
    runCA
    bax
    bas
    variantCaller
    fofn
    cmp
    Nonhybrid 
    ipdSummary
    fofnToSmrtpipeInput
    percentageCutoff
    silico
    motifMaker
    csv
 
Step Details
-------------

Following are the various steps that are part of GenPipes PacBio Sequencing genomic analysis pipeline:

.. _SMRT Analysis Filtering:

**SMRT Analysis Filtering**

This step filters reads and subreads based on their length and QVs, using smrtpipe.py (from the `SMRTAnalysis`_ package. Next, it performs the following processing:

#. fofnToSmrtpipeInput.py
#. modifies RS_Filtering.xml files according to reads filtering values entered in .ini file
#. runs smrtpipe.py with filtering protocol 
#. uses prinseq-lite.pl to write FASTA file based on FASTQ file

Besides these, informative run metrics such as loading efficiency, read lengths and base quality are generated in this step as well. 

.. _PacBio Tools Cutoff:

**PacBio Tools Cutoff**

Cutoff value for splitting long reads from short reads is done here using estimated coverage and estimated genome size. You should estimate the overall coverage and length distribution for putting in the correct options in the configuration file. You will need to decide a length cutoff for the seeding reads. The optimum cutoff length will depend on the distribution of the sequencing read lengths, the genome size and the overall yield. Here, you provide a percentage value that corresponds to the fraction of coverage you want to use as seeding reads.

First, loop through fasta sequences, put the length of each sequence in an array, sort it, loop through it again and compute the cumulative length covered by each sequence as we loop through the array. Once that length is > (coverage * genome size) * $percentageCutoff (e.g. 0.10), we have our threshold. The idea is to consider all reads above that threshold to be seeding reads to which will be aligned lower shorter subreads.

.. _Pre-Assembly:

**Pre-Assembly**

Having in hand a cutoff value, filtered reads are split between short and long reads. Short reads are aligned against long reads and consensus (e.g. corrected reads) are generated from these alignments. In addition, it performs the following steps:

#. split reads between long and short
#. runs `BLASR`_ aligner for PacBio reads
#. executes m4topre: convert .m4 BLASR output in .pre format
#. uses pbdagcon (aka HGAP2) to generate corrected reads from alignments

.. _Assembly:

**Assembly**

Corrected reads are assembled to generates contigs. Please see the `Celera Documentation`_ . Quality of assembly seems to be highly sensitive to parameters you give Celera. Next it performs the following:

#. generate Celera config files using parameters provided in the .ini file
#. fastqToCA: generate input file compatible with the Celera assembler
#. runCA: run the Celera assembler

.. _Polishing:

**Polishing**

This step aligns raw reads on the Celera assembly with BLASR. Load pulse information from bax or bas files into aligned file. Sort that file and run quiver (variantCaller.py). Next, it performs the following actions:

#. generate fofn
#. upload Celera assembly with smrtpipe refUploader
#. compare sequences
#. load pulses
#. sort .cmp.h5 file
#. variantCaller.py

.. _PacBio Assembly Stats:

**PacBio Assembly Stats**

Missing description in original README.md file `here <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/pacbio_assembly/README.md>`_.

.. _BLAST:

**BLAST**

Uses `BLAST`_ polished assembly to search Nucleotide NR database using `dc-megablast`_ to find more distant sequences.

.. _Mummer:

**Mummer**:

Using `MUMmer tool`_, align polished assembly against best hit from blast job. Also align polished assembly against itself to detect structure variation such as repeats, etc.
 
.. _Compile:

**Compile**

This step compiles assembly stats of all conditions used in the pipeline (useful when multiple assemblies are performed).

.. _Circlator Step:

**Circlator Step**

Uses `Circlator`_ to circularize the assembly contigs if possible. User should launch this step after making sure the quality of the assembly is acceptable.

.. _Base Modification:

**Base Modification**

Run ipdSummary.py for in silico detection of modified bases.

.. _Motif Maker:

**Motif Maker**

Run motifMaker to generate motif_summary.csv

.. Following are the html links used in the content above

.. _SMRTAnalysis: https://www.pacb.com/products-and-services/analytical-software/smrt-analysis/
.. _Celera Documentation: http://wgs-assembler.sourceforge.net/wiki/index.php?title=RunCA 
.. _dc-megablast: https://www.ncbi.nlm.nih.gov/books/NBK279668/
.. _MUMmer tool: http://mummer.sourceforge.net
