.. _docs_gp_rnaseq:

.. spelling:word-list::

     html
     goseq
     StringTie
     stringtie
     arriba
     annofuse

RNA Sequencing Pipeline
========================

:bdg-primary:`Version` |genpipes_version|

.. note::
   **Have you tried the GenPipes Wizard?**
      We've developed a helpful tool: the :ref:`GenPipes Wizard <docs_gp_wizard>`. It guides users through selecting the appropriate deployment method, pipeline, and protocol, and helps construct the full command to run GenPipes.

.. tab-set::             

      .. tab-item:: Usage

         .. dropdown:: Command
            :open:

            .. code::

                 genpipes rnaseq [options] [--genpipes_file GENPIPES_FILE.sh]
                 bash GENPIPES_FILE.sh

         .. dropdown:: Options

            .. include:: opt_rnaseq.inc
            .. include:: /common/gp_design_opt.inc
            .. include:: /common/gp_readset_opt.inc
            .. include:: /common/gp_common_opt.inc

         .. dropdown:: Example

            .. include::  /user_guide/pipelines/example_runs/rnaseq.inc

            .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

            .. card:: Test Dataset
               :link: docs_testdatasets
               :link-type: ref

               You can download the `test dataset <https://www.computationalgenomics.ca/tutorial/c3g_analysis_workshop/C3GAW_RNA_TestData_Aug2018.zip>`_ for this pipeline. For more details, you can refer to GenPipes `RNA Sequencing Workshop 2018 presentation <https://www.computationalgenomics.ca/tutorial/c3g_analysis_workshop/C3GAW_RNASeq_Aug2018.zip>`_.

      .. tab-item:: Schema
         :name: rnaschema

         .. dropdown:: StringTie

            The following figure shows the schema of the RNA sequencing protocol (stringtie).

            .. figure:: /img/pipelines/mmd/rnaseq.stringtie.mmd.png
               :align: center
               :alt: rnaseq schema stringtie
               :width: 100%
               :figwidth: 95%

               Figure: Schema of RNA Sequencing pipeline (StringTie)

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: legend
               :width: 100%
               :figwidth: 75%

         .. dropdown:: Variants

            The following figure shows the schema of the RNA sequencing protocol (variants).

            .. figure:: /img/pipelines/mmd/rnaseq.variants.mmd.png
               :align: center
               :alt: rnaseq schema variants
               :width: 100%
               :figwidth: 95%

               Figure: Schema of RNA Sequencing pipeline (variants)

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: legend
               :width: 100%
               :figwidth: 75%

         .. dropdown:: Cancer

            The following figure shows the schema of the RNA sequencing protocol (variants).

            .. figure:: /img/pipelines/mmd/rnaseq.cancer.mmd.png
               :align: center
               :alt: rnaseq schema cancer
               :width: 100%
               :figwidth: 95%

               Figure: Schema of RNA Sequencing pipeline (cancer)

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: legend
               :width: 100%
               :figwidth: 75%

      .. tab-item:: Steps

         +----+-----------------------------+------------------------------------+-----------------------------------+
         |    |   *StringTie*               |  *Variants*                        | *Cancer*                          |
         +====+=============================+====================================+===================================+
         | 1. | |picard_sam_to_fastq|       |  |picard_sam_to_fastq|             | |picard_sam_to_fastq|             |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 2. | |trimmomatic|               |  |skewer_trimming|                 | |skewer_trimming|                 |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 3. | |merge_trimmomatic_stats|   |  |sortmerna_s|                     | |sortmerna_s|                     |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 4. | |sortmerna_s|               |  |star_step|                       | |star_step|                       |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 5. | |star_step|                 |  |picard_merge_sam_files|          | |picard_merge_sam_files|          | 
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 6. | |picard_merge_sam_files|    |  |mark_duplicates|                 | |mark_duplicates|                 |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 7. | |picard_sort_sam|           |  |split_N_trim|                    | |split_N_trim|                    |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 8. | |mark_duplicates|           |  |sambamba_merge_splitNtrim_files| | |sambamba_merge_splitNtrim_files| |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 9. | |picard_rna_metrics|        |  |gatk_indel_realigner|            | |gatk_indel_realigner|            |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 10.| |estimate_ribosomal_rna|    |  |sambamba_merge_realigned|        | |sambamba_merge_realigned|        | 
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 11.| |rnaseqc2|                  |  |recalibration|                   | |recalibration|                   |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 12.| |wiggle|                    |  |gatk_haplotype_caller|           | |gatk_haplotype_caller|           |  
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 13.| |raw_counts|                |  |merge_hc_vcf|                    | |merge_hc_vcf|                    |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 14.| |raw_counts_metrics|        |  |run_vcfanno|                     | |run_vcfanno|                     |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 15.| |stringtie_s|               |  |variant_filtration|              | |variant_filtration|              |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 16.| |stringtie_merge|           |  |decompose_and_normalize|         | |decompose_and_normalize|         |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 17.| |stringtie_abund|           |  |compute_snp_effects|             | |filter_gatk|                     |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 18.| |ballgown|                  |  |gemini_annotations|              | |report_cpsr|                     |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 19.| |differential_expression|   |  |picard_rna_metrics|              | |report_pcgr|                     |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 20.| |multiqc|                   |  |estimate_ribosomal_rna|          | |run_star_fusion|                 |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 21.| |cram_output|               |  |rnaseqc2|                        | |run_arriba|                      |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 22.|                             |  |gatk_callable_loci|              | |run_annofuse|                    |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 23.|                             |  |wiggle|                          | |picard_rna_metrics|              | 
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 24.|                             |  |multiqc|                         | |estimate_ribosomal_rna|          | 
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 25.|                             |  |cram_output|                     | |rnaseqc2|                        |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 26.|                             |                                    | |rseqc|                           |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 27.|                             |                                    | |gatk_callable_loci|              |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 28.|                             |                                    | |wiggle|                          |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 29.|                             |                                    | |multiqc|                         |
         +----+-----------------------------+------------------------------------+-----------------------------------+
         | 30.|                             |                                    | |cram_output|                     |
         +-----------------------------------------------------------------------+-----------------------------------+

         .. card::

            .. include:: steps_rnaseq.inc

      .. tab-item:: About

         .. card::

            The standard MUGQIC RNA-Seq pipeline has three protocols:

               * StringTie 
               * Variants
               * Cancer
            
            StringTie is the default protocol and applicable in most cases.

            All three protocols are based on the use of the `STAR aligner <https://code.google.com/p/rna-star/>`_ to align reads to the reference genome. These alignments are used during downstream analysis (for example in stringtie protocol, to determine differential expression of genes and transcripts).

            .. tab-set:: 
               
               .. tab-item:: StringTie
            
                  The `StringTie suite <https://ccb.jhu.edu/software/stringtie/>`_ is used for differential transcript expression (DTE) analysis, whereas `DESeq2 package <https://bioconductor.org/packages/release/bioc/html/DESeq2.html>`_ and `edgeR package <http://bioconductor.org/packages/release/bioc/html/edgeR.html>`_ are used for the differential gene expression (DGE) analysis.

                  StringTie protocol requires a design file which will be used to define the comparison groups
                  in the differential analyses. Refer to the `design file format  <https://genpipes.readthedocs.io/en/latest/get-started/concepts/design_file.html>`_. In addition, `Ballgown package <https://bioconductor.org/packages/release/bioc/html/ballgown.html>`_ is used to calculate differential transcript and gene expression levels and test them for significant differences. It can also take a batch file (optional) which will be used to correct for batch effects in the differential analyses. Note the `batch file format <https://bitbucket.org/mugqic/mugqic_pipelines/src#markdown-header-batch-file>`_.

               .. tab-item:: Variants Protocol
            
                  The variants protocol is used when variant detection, is the main goal of the analysis. GATK best practices workflow is used for variant calling. It also contains a step for annotating genes using the `gemini protocol <https://gemini.readthedocs.io/en/latest/>`_.

               .. tab-item:: Cancer
            
                  The cancer protocol contains all the steps in the variants protocol but it is specifically designed for cancer data sets due to the complexity of cancer samples and additional analyses those projects often entail. The goal of the cancer protocol is comparing expression to known benchmarks. In addition to the steps in the variants protocol, it contains four specific steps. Three of them (run_star_fusion, run_arriba, run_annofuse) are related to detection and annotation of gene fusions. For that, `Star-fusion  package <https://github.com/STAR-Fusion/STAR-Fusion-Tutorial/wiki>`_, `Arriba package <https://arriba.readthedocs.io/en/latest/>`_ and `anno-Fuse package <https://rdrr.io/github/d3b-center/annoFuse/>`_ are used. Furthermore, `RSeQC package <http://rseqc.sourceforge.net/>`_ provides RNA-seq quality control metrics to asses the quality of the data.

                  Finally, a summary html report is automatically generated by the pipeline at the end of the analysis. This report contains description of the sequencing experiment as well as a detailed presentation of the pipeline steps and results. Various Quality Control (QC) summary statistics are included in the report and additional QC analysis is accessible for download directly through the report. The report includes also the main references of the software tools and methods used during the analysis, together with the full list of parameters that have been passed to the pipeline main script.

                  See :ref:`rnaschema` tab for workflow. For the latest implementation and usage details refer to RNA Sequencing implementation `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/rnaseq/README.md>`_ file.

            **References**

            * `RNA Sequencing Workshop 2019 (Slides) <https://www.computationalgenomics.ca/analysis-workshop-2019-rnaseq-module/>`_

----

.. The following are replacement texts used in this file

.. |picard_sam_to_fastq| replace:: `Picard SAM to FastQ`_
.. |star_step| replace:: `Star Processing`_
.. |run_star_fusion| replace:: `Run Star Fusion`_
.. |picard_merge_sam_files| replace:: `Picard Merge SAM Files`_
.. |picard_sort_sam| replace:: `Picard Sort SAM`_
.. |picard_rna_metrics| replace:: `Picard RNA Metrics`_
.. |mark_duplicates| replace:: `Mark Duplicates`_
.. |trimmomatic| replace:: `Trimmomatic`_
.. |merge_trimmomatic_stats| replace:: `Merge Trimmomatic Stats`_
.. |estimate_ribosomal_rna| replace:: `Estimate Ribosomal RNA`_
.. |rnaseqc| replace:: `RNA Seq Compress`_
.. |wiggle| replace:: `Wiggle`_
.. |raw_counts| replace:: `Raw Counts`_
.. |raw_counts_metrics| replace:: `Raw Counts Metrics`_
.. |differential_expression| replace:: `Differential Expression`_
.. |stringtie_s| replace:: `StringTie Step`_
.. |stringtie_abund| replace:: `StringTie Abund`_
.. |stringtie_merge| replace:: `StringTie Merge`_
.. |ballgown| replace:: `Ballgown Gene Expression`_
.. |sortmerna_s| replace:: `Sortmerna Step`_
.. |rnaseqc2| replace:: `Rnaseqc2`_
.. |skewer_trimming|  replace:: `Skewer Trimming`_
.. |split_N_trim|  replace:: `Split N Trim`_
.. |sambamba_merge_splitNtrim_files| replace:: `Sambamba Merge Split N Trim Files`_
.. |sambamba_merge_realigned|  replace:: `Sambamba Merge Realigned`_
.. |gatk_indel_realigner| replace:: `GATK Indel Realigner`_
.. |gatk_haplotype_caller| replace:: `GATK Haplotype Caller`_
.. |gatk_callable_loci| replace:: `GATK Callable Loci`_
.. |filter_gatk| replace:: `Filter GATK`_
.. |recalibration| replace:: `Recalibration`_
.. |merge_hc_vcf| replace:: `Merge HC VCF`_
.. |run_vcfanno| replace:: `Run VCF Anno`_
.. |variant_filtration| replace:: `Variant Filtration`_
.. |decompose_and_normalize| replace:: `Decompose and Normalize`_
.. |compute_snp_effects| replace:: `Compute SNP Effects`_
.. |gemini_annotations| replace:: `Gemini Annotations`_
.. |report_cpsr| replace:: `Report CPSR`_
.. |report_pcgr| replace:: `Report PCGR`_
.. |run_arriba| replace:: `Run Arriba`_
.. |run_annofuse| replace:: `Run Annofuse`_ 
.. |rseqc| replace:: `RSeqC`_
.. |multiqc| replace:: `Multiqc Report`_

.. include:: repl_cram_op.inc
