:orphan:

.. _doc_nanuq_runsheet:

Nanuq Run Sheet
===============

The Nanuq Run Sheet is a csv file with the following minimal set of mandatory columns. The order of the columns in the file does not matter. 

Here is the list of columns for Nanuq run sheet:

* ``ProcessingSheetId`` Must be the same as the SampleID from the Casava Sheet.
* ``Name`` The sample name put in RG headers of bam files and on filename on disk.
* ``Run`` The run number.
* ``Region`` The lane number.
* ``Library Barcode`` The library barcode put in .bam's RG headers and on disk
* ``Library Source`` The type of library. If this value contains RNA or cDNA, STAR will be used to make the alignment, otherwise, bwa_mem will be used
* ``Library Type`` Used to determine is the sample is from cDNA/RNA when the Library Source is Library
* ``BED Files`` The name of the BED file containing the genomic targets. This is the filename parameter passed to the fetch_bed_file_command
* ``Genomic Database`` The reference used to make the alignment and calculate alignments metrics

Here is a sample of the Nanuq Run Sheet:

::

  Name,Genomic Database,Library Barcode,Library Source,Library Type,Run,Region,BED Files,ProcessingSheetId
  sample1,Rattus_norvegicus:Rnor_5.0,MPS0001,RNA,Nextera XT,1419,1,toto.bed,sample1_MPS0001
  sample47,,MPS1047,Library,Nextera XT,1419,2,toto.bed,sample47_MPS1047
