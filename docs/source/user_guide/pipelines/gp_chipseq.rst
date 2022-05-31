.. _docs_gp_chipseq:

.. spelling::

   transposase
   Immunoprecipitation
   atacseq
   Transposon
   nucleosome

ChIP Sequencing Pipeline
========================

Chromatin Immunoprecipitation (ChIP) sequencing technique is used for mapping DNA-protein interactions. It is a powerful method for identifying genome-wide DNA binding sites for transcription factors and other proteins. The ChIP-Seq workflow is based on the `ENCODE Project`_ workflow. It aligns reads using the `Burrows-Wheeler Aligner`_. It creates tag directories using `Homer routines`_. Peaks are called using `Model based Analysis for Chip Sequencing (MACS2)`_ and annotated using Homer. Binding motifs are also identified using Homer. Metrics are calculated based on `IHEC requirements`_. The ChIP-Seq pipeline can also be used for assay for transposase-accessible chromatin using sequencing (ATAC-Seq) samples. At GenPipes, we are developing a pipeline that is specific to `ATAC-Seq`_.

.. contents:: :local:

----

Introduction
------------

ChIP-Seq experiments allows the isolation and sequencing of genomic DNA bound by a specific transcription factor, covalently modified histone, or other nuclear protein. The pipeline starts by trimming adapters and low quality bases and mapping the reads (single end or paired end ) to a reference genome using `Burrows-Wheeler Aligner`_ (BWA). Reads are filtered by mapping quality and duplicate reads are marked. Then, Homer quality control routines are used to provide information and feedback about the quality of the experiment. Peak calls is executed by MACS and annotation and motif discovery for narrow peaks are executed using Homer. Statistics of annotated peaks are produced for narrow peaks and a standard report is generated.

For more details, see `ChIP-Seq Guidelines`_, and  `MUGQIC_Bioinfo_Chip-Seq.pptx`_.

----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to Hi-C Sequencing implementation `ChIP-Seq Pipeline README`_ file.

----

Usage
-----

::

  chipseq.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
                  [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]
                  [--no-json] [--report] [--clean]
                  [-l {debug,info,warning,error,critical}] [--sanity-check]
                  [--container {wrapper, singularity} <IMAGE PATH>
                  [--genpipes_file GENPIPES_FILE]
                  [-d DESIGN] [-t {chipseq, atacseq}] [-r READSETS] [-v]

**Optional Arguments**

.. include:: opt_chipseq.inc
.. include:: /common/gp_design_opt.inc
.. include:: /common/gp_readset_opt.inc
.. include:: /common/gp_common_opt.inc

.. warning::

     Please make sure you use the special :ref:`ChIPSeq Pipeline Readfile format<ref_example_chipseq_readset_file>` and not the general readfile format.

.. _ref_chipseq_design_ff:

.. note::  ChIPSeq Pipeline Design File Format

     .. code::

         Sample        MarkName        EW22_EW3_vs_EW7_TC71
         EW22          H3K27ac         1
         EW3           H3K27ac         1
         EW7           H3K27ac         2
         TC71          H3K27ac         2

     where, the numbers specify the sample group membership for this contrast:

     .. code::

           '0' or '': the sample does not belong to any group;
           '1': the sample belongs to the control group;
           '2': the sample belongs to the treatment test case group.  


     The design file only accepts 1 for control, 2 for treatment and 0 for other samples that do not need to compare. 
    
.. warning::  Incorrect Design File Format

     Please note that the first and second column in the design file must be sample name and histone mark/binding protein respectively. 
     
     **If the user specifies any value other than the permitted ones above in the design file, the pipeline will fail.**

Example Run
-----------

You can download `ChIP-Seq test dataset`_ and use the following command to execute the ChIP-Seq genomics pipeline:

.. include:: /user_guide/pipelines/example_runs/chipseq.inc

.. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

The commands will be sent to the job queue and you will be notified once each step is done. If everything runs smoothly, you should get MUGQICexitStatus:0 or Exit_status=0. If that is not the case, then an error has occurred after which the pipeline usually aborts. To examine the errors, check the content of the job_output folder.

----

Pipeline Schema
---------------

Figure below shows the schema of ChIP-Seq protocol. 

.. figure:: /img/pipelines/mmd/chipseq.mmd.png
   :align: center
   :alt: ChIP-Seq schema
   :figwidth: 95%
   :width: 100%

   Figure: Schema of ChIP Sequencing protocol

.. figure:: /img/pipelines/mmd/legend.mmd.png
   :align: center
   :alt: dada2 ampseq
   :width: 100%
   :figwidth: 75%

Following is the schema for the ChIP-Seq pipeline using the -t atacseq option:

.. figure:: /img/pipelines/mmd/chipseq.atac.mmd.png
   :align: center
   :alt: ChIP-Seq schema atacseq option
   :figwidth: 95%
   :width: 100%

   Figure: Schema of ChIP Sequencing -t atacseq protocol

.. figure:: /img/pipelines/mmd/legend.mmd.png
   :align: center
   :alt: dada2 ampseq
   :width: 100%
   :figwidth: 75%

----

Pipeline Steps
---------------

The table below shows various steps that constitute the ChIP sequencing pipeline:

+----+---------------------------+--------------------------------------+
|    | ChIP Sequencing Steps     |    ChIP Sequencing (atacseq)         |
+====+===========================+======================================+
| 1. | |picard_sam_to_fastq|     | |picard_sam_to_fastq|                |
+----+---------------------------+--------------------------------------+
| 2. | |trimmomatic|             | |trimmomatic|                        |
+----+---------------------------+--------------------------------------+
| 3. | |merge_trimmomatic_stats| | |merge_trimmomatic_stats|            |
+----+---------------------------+--------------------------------------+
| 4. | |mapping_bwamem_sambamba| | |mapping_bwamem_sambamba|            |
+----+---------------------------+--------------------------------------+
| 5. | |sambamba_merge_bam|      | |sambamba_merge_bam|                 |
+----+---------------------------+--------------------------------------+
| 6. | |sambamba_mark_dup|       | |sambamba_mark_dup|                  | 
+----+---------------------------+--------------------------------------+
| 7. | |sambamba_view_filter|    | |sambamba_view_filter|               |
+----+---------------------------+--------------------------------------+
| 8. | |metrics|                 | |metrics|                            |
+----+---------------------------+--------------------------------------+
| 9. | |homer_make_tag_directory|| |homer_make_tag_directory|           |
+----+---------------------------+--------------------------------------+
| 10.| |qc_metrics|              | |qc_metrics|                         |
+----+---------------------------+--------------------------------------+
| 11.| |homer_make_ucsc_file|    | |homer_make_ucsc_file|               |
+----+---------------------------+--------------------------------------+
| 12.| |macs2_callpeak|          | |macs2_atacseq_callpeak|             |    
+----+---------------------------+--------------------------------------+
| 13.| |homer_annotate_peaks|    | |homer_annotate_peaks|               |
+----+---------------------------+--------------------------------------+
| 14.| |homer_find_motifs_genome|| |homer_find_motifs_genome|           |
+----+---------------------------+--------------------------------------+
| 15.| |annotation_graphs|       | |annotation_graphs|                  |
+----+---------------------------+--------------------------------------+
| 16.| |run_spp|                 | |run_spp|                            |
+----+---------------------------+--------------------------------------+
| 17.| |differential_binding|    | |ihec_metrics|                       |
+----+---------------------------+--------------------------------------+
| 18.| |ihec_metrics|            | |multiqc_report|                     |
+----+---------------------------+--------------------------------------+
| 19.| |multiqc_report|          | |cram_output|                        |
+----+---------------------------+                                      |
| 20.| |cram_output|             |                                      |
+----+---------------------------+--------------------------------------+

----

.. include:: steps_chipseq.inc

----

More Information
----------------

For the latest implementation and usage details, see `ChIP-Seq Pipeline README`_. Here is some more information about ChIP sequencing pipeline that you may find interesting.

* `ChIP-Seq and Beyond <https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3591838/>`_. 

* `ChIP-Seq Technology and Workflow <https://www.sciencedirect.com/science/article/pii/S1046202320300591>`_.

* `Schematic representation of major methods to detect functional elements in DNA <https://journals.plos.org/plosbiology/article/figure?id=10.1371/journal.pbio.1001046.g001>`_.

* `ChIP Sequencing and ATAC Sequencing <https://bioinformatics-core-shared-training.github.io/cruk-autumn-school-2017/ChIP/Materials/Lectures/Lecture4_Introduction%20to%20ChIP-seq%20and%20ATAC-seq_SS.pdf>`_

.. figure:: /img/pipelines/ChIP-Seq-hl-diag.png
   :align: center
   :alt: ChIP-Seq-HL 

   Figure:  Schematic representation of major methods used to detect functional elements in DNA (Source PLOS)

.. The following are replacement texts used in this file

.. |picard_sam_to_fastq| replace:: `Picard Sam to Fastq`_
.. |trimmomatic| replace:: `Trimmomatic`_
.. |merge_trimmomatic_stats| replace:: `Merge Trimmomatic Stats`_
.. |metrics| replace:: `Metrics`_
.. |homer_make_tag_directory| replace:: `Homer Make Tag Directory`_
.. |qc_metrics| replace:: `QC Metrics`_
.. |homer_make_ucsc_file| replace:: `Homer Make UCSC file`_
.. |macs2_callpeak| replace:: `MACS2 call peak`_
.. |macs2_atacseq_callpeak| replace:: `MACS2 ATAC-seq call peak`_
.. |homer_annotate_peaks| replace:: `Homer annotate peaks`_
.. |homer_find_motifs_genome| replace:: `Homer find motifs genome`_
.. |annotation_graphs| replace:: `Annotation Graphs`_
.. |run_spp| replace:: `Run SPP`_
.. |differential_binding| replace:: `Differential Binding`_
.. |ihec_metrics| replace:: `IHEC Metrics`_
.. |multiqc_report| replace:: `MultiQC Report`_
.. |mapping_bwamem_sambamba| replace:: `Mapping BWA Mem Sambamba`_
.. |sambamba_merge_bam| replace:: `SAMbamba Merge BAM`_
.. |sambamba_mark_dup| replace:: `SAMbamba Mark Duplicates`_
.. |sambamba_view_filter| replace:: `SAMbamba View Filter`_ 

.. include:: repl_cram_op.inc

.. The following are html link targets used in this text

.. _ENCODE Project: https://www.genome.gov/Funded-Programs-Projects/ENCODE-Project-ENCyclopedia-Of-DNA-Elements
.. _Burrows-Wheeler Aligner: http://bio-bwa.sourceforge.net
.. _Homer routines: https://www.researchgate.net/publication/44640585_Simple_Combinations_of_Lineage-Determining_Factors_Prime_cis-Regulatory_Elements_Required_for_Macrophage_and_B-Cell_Identities
.. _Model based Analysis for Chip Sequencing (MACS2): https://genomebiology.biomedcentral.com/articles/10.1186/gb-2008-9-9-r137
.. _IHEC requirements: https://github.com/IHEC/ihec-assay-standards
.. _ATAC-Seq: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4374986/
.. _ChIP-Seq Guidelines: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3431496/
.. _ChIP-Seq report: http://gqinnovationcenter.com/services/bioinformatics/tools/chipReport/index.html
.. _ChIP-Seq Pipeline README: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/chipseq/README.md 
.. _ChIP-Seq test dataset: https://datahub-90-cw3.p.genap.ca/chipseq.chr19.tar.gz
.. _GenPipes ChIP-Seq pipeline implementation: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/chipseq/ 
.. _ChIP-Seq Schema high resolution image: https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_chipseq.png
.. _MUGQIC_Bioinfo_ChIP-Seq.pptx: https://bitbucket.org/mugqic/genpipes/downloads/MUGQIC_Bioinfo_ChIP-Seq.pptx
