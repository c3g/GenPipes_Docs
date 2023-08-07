.. _docs_gp_tumorpair:

.. spelling::

      ploidy
      sv
      fastpass
      vcf
      VCF
      CNV
      Koboldt
      Preprocess
      bp
      Ensembl
      vcfanno
      Kataegis
      Microsatellite
      
Tumor Pair Sequencing Pipeline
================================

.. admonition:: **Reporting System Changes**

    .. container:: toggle, toggle-hidden

         From the GenPipes Release 4.2.0, the Tumor Pair pipeline reporting system has changed from `GEMINI Framework <https://gemini.readthedocs.io/en/latest/>`_ to `PCGR <https://sigven.github.io/pcgr/>`_/`CPSR <https://sigven.github.io/cpsr/index.html>`_ reporting.

         PCGR interprets primarily somatic SNVs/InDels and copy number aberrations. The software extends basic gene and variant annotations from the Ensembl's Variant Effect Predictor (VEP) with oncology-relevant, up-to-date annotations retrieved flexibly through vcfanno, and produces interactive HTML reports intended for clinical interpretation. 

         PCGR performs multiple types of analysis, including:

         * Somatic variant classification (ACMG/AMP)

         * mapping the therapeutic and prognostic implications of somatic DNA aberrations

         * Tumor mutational burden (TMB) estimation

         * Tumor-only analysis (variant filtering)

         * Mutational signature analysis

         * Kataegis detection

         * Micro-satellite instability (MSI) classification

         The accompanying tool CPSR is used to interrogate germline variants and their relation to cancer predisposition. 

.. tabs:: 

      .. tab:: About

         Tumor Pair pipeline helps in inferring the cancer cell copy number to normal cell copy number.

         Human genome comprises of a set of chromosome pairs. One chromosome in each pair, called homolog, is derived from each parent. It is typically referred to as diploid whereas the set of chromosomes from a single parent is called haploid genome. For a given gene on a given chromosome, there is a comparable, if not identical, gene on the other chromosome in the pair, known as an allele. Large structural alterations in chromosomes can change the number of copies of affected genes on those chromosomes. This is one of the key reasons for causing tumors or cancer. In cancer cells, instead of having a homologous pair of alleles for a given gene, there may be deletions or duplications of those genes. 

         Such alterations leads to unequal contribution of one allele over the other, altering the copy number of a given allele. These variations in copy number indicated by the ratio of cancer cell copy number to normal cell copy number can provide information regarding the structure and history of cancer. However, when DNA is extracted, there is a mix of cancer and normal cells and this information regarding absolute copy number per cancer cell is lost in DNA extraction process.  Hence it must be inferred.

         Inferring absolute copy number is difficult for `three reasons`_:

         * Cancer cells are nearly always intermixed with an unknown fraction of normal cells; the measure for this is tumor purity.
         * The actual quantity of DNA in the cancer cells after gross numerical and structural chromosomal changes is unknown; the measure for this is tumor ploidy.
         * The cancer cell population may be heterogeneous, possibly because of ongoing mutations and changes.

         Tumor purity and ploidy have a substantial impact on next-gen sequence analyses of tumor samples and may alter the biological and clinical interpretation of results.

         GenPipes Tumor Analysis pipeline is designed to detect somatic variants from a tumor and match normal sample pair more accurately. 
         
         GenPipes Tumor Pair workflow consumes BAM files. It inherits the BAM processing protocol from DNA-seq implementation, for retaining the benchmarking optimizations. However, it differs from DNA-seq implementation in the indel alignment step. It achieves this by maximizing the information, utilizing both tumor and normal samples together. 

         The pipeline is based on an ensemble approach, which was optimized using both the `DREAM3 challenge`_ and the CEPH mixture datasets to select the best combination of callers for both SNV and structural variation detection. For SNVs, multiple callers such as `GATK MuTect2`_, `Strelka2`_, `VarScan 2`_, and `VarDict`_ were combined for somatic calls to achieve a sensitivity of 98.1%, precision of 98.4%, and F1 score of 98.3% for variants found in ≥2 callers. For germline calls, `Strelka2`_, `VarScan 2`_ and `VarDict`_ calls were combined.

         Similarly, SVs were identified using multiple callers such as `Strelka2`_, `GridSS`_ to achieve a sensitivity of 84.6%, precision of 92.4%, and F1 score of 88.3% for duplication variants found in the DREAM3 dataset. The pipeline also integrates specific cancer tools to estimate tumor purity and tumor ploidy of sample pair normal−tumor using `Sequenza`_ and `PURPLE`_.  

         Additional annotations are incorporated to the SNV calls using `dbNSFP`_ and/or `Gemini`_, and QC metrics are collected at various stages and visualized using `MultiQC`_. 

         GenPipes Tumor Pair pipeline has three protocol options: sv, ensemble (default), and fastpass.  For details refer to `Pipeline Schema <Pipeline Schema>` section below. 

      .. tab:: Usage

         .. code::

            python tumor_pair.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
                                 [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]
                                 [--no-json] [--report] [--clean]
                                 [-l {debug,info,warning,error,critical}] [--sanity-check]
                                 [--container] {wrapper, singularity} <IMAGE PATH>
                                 [--genpipes_file GENPIPES_FILE]
                                 [-p PAIRS] [-t {sv,ensemble (default) ,fastpass}] [-r READSETS] [-v]


         .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

      .. tab:: Options


         .. include:: opt_tumorpair.inc
         .. include:: /common/gp_readset_opt.inc
         .. include:: /common/gp_common_opt.inc

         .. admonition::  -t fastpass

            The fastpass option in tumor_pair.py pipeline is meant for quick assessment using exome capture regions and the 1000bp flanking regions. The somatic/germline calls are made using one variant caller `VarScan 2`_ with permissive variant calling thresholds.

         .. admonition:: -p option

               The pairs file specified along with -p option has the following format:
         
               <patient_name>,<normal_sample_name>,<tumor_sample_name>

               For example:

               ::

                  tumorPair_CEPHmixture_chr19,tumorPair_CEPHmixture_chr19_normal,tumorPair_CEPHmixture_chr19_tumor

      .. tab:: Example Run

         Use the following commands to execute Tumor Pair pipeline:

         .. include::  /user_guide/pipelines/example_runs/tumor_pair.inc

         You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

      .. tab:: Schema
         :name: Pipeline Schema

         There are three options for Tumor Pair Pipeline: sv, ensemble(default) and fastpass.

         .. tabs::

            .. tab:: SV

               .. figure:: /img/pipelines/mmd/tumor_pair.sv.png
                  :align: center
                  :alt: tumor_pair_sv schema
                  :width: 100%
                  :figwidth: 95%

                  Figure: Schema of Tumor Pair Pipeline (sv)

               `Click for a high resolution image of Tumor Pair Sequencing Pipeline (sv) schema <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_tumor_pair_sv.png>`_.

            .. tab:: Ensemble

               .. figure:: /img/pipelines/mmd/tumor_pair.ensemble.png
                  :align: center
                  :alt: tumor_pair_ensemble schema
                  :width: 100%
                  :figwidth: 95%

                  Figure: Schema of Tumor Pair Pipeline (ensemble)

               `Click for a high resolution image of Tumor Pair Sequencing Pipeline (ensemble) <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_tumor_pair_ensemble.png>`_.

            .. tab:: Fastpass

               .. figure:: /img/pipelines/mmd/tumor_pair.fastpass.png
                  :align: center
                  :alt: tumor_pair_fastpass schema
                  :width: 100%
                  :figwidth: 95%

                  Figure: Schema of Tumor Pair Pipeline (fastpass)

               `Click for a high resolution image of Tumor Pair Sequencing Pipeline (fastpass) <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_tumor_pair_fastpass.png>`_.

      .. tab:: Steps

         The table below shows various steps that constitute the Tumor Pair Pipeline.

         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         |    | *Fastpass*                              | *Ensemble*                            | *SV*                            |
         +====+=========================================+=======================================+=================================+
         | 1. | |picard_sam_to_fastq|                   | |picard_sam_to_fastq|                 | |picard_sam_to_fastq|           |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 2. | |skewer_trim|                           | |skewer_trim|                         | |skewer_trim|                   |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 3. | |bwa_mem_sambamba_sort_sam|             | |bwa_mem_sambamba_sort_sam|           | |bwa_mem_sambamba_sort_sam|     |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 4. | |sambamba_sort|                         | |sambamba_sort|                       | |sambamba_sort|                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 5. | |sambamba_merge_sam_files|              | |sambamba_merge_sam_files|            | |sambamba_merge_sam_files|      |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 6. | |gatk_indel_realigner|                  | |gatk_indel_realigner|                | |gatk_indel_realigner|          |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 7. | |sambamba_merge_realigned|              | |sambamba_merge_realigned|            | |sambamba_merge_realigned|      |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 8. | |sambamba_mark_duplicates|              | |sambamba_mark_duplicates|            | |sambamba_mark_duplicates|      |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 9. | |recalibration|                         | |recalibration|                       | |recalibration|                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 10.| |manta_sv_calls|                        | |conpair_concordance_contamination|   | |manta_sv_calls|                |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 11.| |rawmpileup_panel|                      | |metrics_dna_picard_metrics|          | |strelka2_paired_somatic|       |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 12.| |paired_varscan2_panel|                 | |metrics_dna_sample_qualimap|         | |gridss_paired_somatic|         |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 13.| |merge_varscan2_panel|                  | |metrics_dna_fastqc|                  | |purple_sv|                     |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 14.| |preprocess_vcf_panel|                  | |sequenza|                            | |linx_annotations_somatic|      |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 15.| |snp_effect_panel|                      | |strelka2_paired_somatic|             | |linx_annotations_germline|     |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 16.| |gemini_annotations_panel|              | |strelka2_paired_germline|            | |linx_plot|                     |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 17.| |conpair_concordance_contamination|     | |strelka2_paired_germline_snpEff|     |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 18.| |metrics_dna_picard_metrics|            | |purple|                              |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 19.| |metrics_dna_sample_qualimap|           | |rawmpileup|                          |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 20.| |metrics_dna_fastqc|                    | |paired_varscan2|                     |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 21.| |sequenza|                              | |merge_varscan2|                      |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 22.| |run_pair_multiqc|                      | |paired_mutect2|                      |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 23.| |sym_link_report|                       | |merge_mutect2|                       |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 24.| |sym_link_fastq_pair|                   | |vardict_paired|                      |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 25.| |sym_link_panel|                        | |merge_filter_paired_vardict|         |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 26.|                                         | |ensemble_somatic|                    |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 27.|                                         | |gatk_variant_annotator_somatic|      |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 28.|                                         | |merge_gatk_variant_annotator_somatic||                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 29.|                                         | |ensemble_germline_loh|               |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 30.|                                         | |gatk_variant_annotator_germline|     |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 31.|                                         | |filter_ensemble_somatic|             |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 32.|                                         | |report_cpsr|                         |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 33.|                                         | |report_pcgr|                         |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 34.|                                         | |run_pair_multiqc|                    |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 35.|                                         | |sym_link_fastq_pair|                 |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 36.|                                         | |sym_link_final_bam|                  |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 37.|                                         | |sym_link_report|                     |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+
         | 38.|                                         | |sym_link_ensemble|                   |                                 |
         +----+-----------------------------------------+---------------------------------------+---------------------------------+

         .. include:: steps_tumor_pair.inc

.. _More Information on Tumor Pair Pipeline:

More information
-----------------

For the latest implementation and usage details see `pipeline implementation <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/tumor_pair/>`_.

* MuTect2 Tool for calling somatic SNVs and indels via local assembly of haplotypes - `See here <https://gatk.broadinstitute.org/hc/en-us/articles/360037593851-Mutect2>`_.

* A `three-caller pipeline <https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5428716/>`_ for variant analysis of cancer whole-exome sequencing data. 

.. Following are the replacement texts used in this file

.. |picard_sam_to_fastq| replace:: `Picard SAM to FastQ`_
.. |skewer_trim| replace:: `Skewer Trimming`_
.. |bwa_mem_sambamba_sort_sam| replace:: `BWA Mem SAMBAMBA Sort SAM`_
.. |sambamba_sort| replace:: `SAMbamba Sort`_
.. |sambamba_merge_sam_files| replace:: `SamBamba Merge Files`_
.. |gatk_indel_realigner| replace:: `GATK InDel Realigner`_
.. |sambamba_merge_realigned| replace:: `SamBamba Merge Realigned`_
.. |sambamba_mark_duplicates| replace:: `SamBamba Mark Duplicates`_ 
.. |recalibration| replace:: `Recalibration`_
.. |conpair_concordance_contamination| replace:: `Conpair Concordance Contamination`_
.. |metrics_dna_picard_metrics| replace:: `Metrics DNA Picard Metrics`_
.. |metrics_dna_sample_qualimap| replace:: `Metrics DNA Sample Qualimap`_
.. |metrics_dna_fastqc| replace:: `Metrics DNA FASTQ`_
.. |sequenza| replace:: `Sequenza Step`_
.. |strelka2_paired_somatic| replace:: `Strelka2 Paired Somatic`_
.. |strelka2_paired_germline| replace:: `Strelka2 Paired Germline`_
.. |strelka2_paired_germline_snpEff| replace:: `Strelka2 Paired Germline SnpEff`_
.. |purple| replace:: `Purple Step`_
.. |rawmpileup| replace:: `Raw Mpileup`_
.. |paired_varscan2| replace:: `Paired Var Scan 2`_
.. |merge_varscan2| replace:: `Merge Var Scan 2`_
.. |paired_mutect2| replace:: `Paired Mutect2`_
.. |merge_mutect2| replace:: `Merge Mutect2`_
.. |vardict_paired| replace:: `VarDict Paired`_
.. |merge_filter_paired_vardict| replace:: `Merge Filter Paired VarDict`_
.. |ensemble_somatic| replace:: `Ensemble Somatic`_
.. |gatk_variant_annotator_somatic| replace:: `GATK Variant Annotator Somatic`_
.. |merge_gatk_variant_annotator_somatic| replace:: `Merge GATK Variant Annotator Somatic`_
.. |compute_cancer_effects_somatic| replace:: `Compute Cancer Efects Somatic`_
.. |ensemble_somatic_dbnsfp_annotation| replace:: `Ensemble Somatic dbNSFP Annotation`_
.. |sample_gemini_annotations_somatic| replace:: `Sample Gemini ANnotations Somatic`_
.. |ensemble_germline_loh| replace:: `Ensemble Germline Loh`_
.. |gatk_variant_annotator_germline| replace:: `GATK Variant Annotator Germline`_
.. |merge_gatk_variant_annotator_germline| replace:: `Merge GATK Variant Annotator Germline`_
.. |compute_cancer_effects_germline| replace:: `Compute Cancer Effects Germline`_
.. |ensemble_germline_dbnsfp_annotation| replace:: `Ensemble Germline dbNSFP Annotation`_
.. |sample_gemini_annotations_germline| replace:: `Sample Gemini Annotations Germline`_
.. |run_pair_multiqc| replace:: `Run Pair MultiQC`_
.. |sym_link_fastq_pair| replace:: `Sym Link FASTQ Pair`_
.. |sym_link_final_bam| replace:: `Sym Link Final BAM`_
.. |sym_link_report| replace:: `Sym Link Report`_
.. |sym_link_ensemble| replace:: `Sym Link Ensemble`_
.. |filter_ensemble_somatic| replace:: `Filter Ensemble Somatic`_
.. |manta_sv_calls| replace:: `Manta SV Calls`_
.. |rawmpileup_panel| replace:: `Raw Mpileup Panel`_
.. |paired_varscan2_panel| replace:: `Paired VarScan 2`_
.. |merge_varscan2_panel| replace:: `Merge VarScan 2 Panel`_
.. |preprocess_vcf_panel| replace:: `PreProcess VCF Panel`_
.. |snp_effect_panel| replace:: `SNP Effect Panel`_
.. |gemini_annotations_panel| replace:: `Gemini Annotations Panel`_
.. |sym_link_panel| replace:: `Sym Link Panel`_
.. |report_cpsr| replace:: `Report CPSR`_
.. |report_pcgr| replace:: `Report PCGR`_
.. |gridss_paired_somatic| replace:: `GridSS Paired Somatic`_
.. |purple_sv| replace:: `Purple SV`_
.. |linx_annotations_somatic| replace:: `Linx Annotations Somatic`_
.. |linx_annotations_germline| replace:: `Linx Annotations Germline`_
.. |linx_plot| replace:: `Linx Plot`_

.. Following are the links used in the text above

.. _three reasons: https://software.broadinstitute.org/cancer/software/genepattern/modules/docs/ABSOLUTE/1
.. _DREAM3 challenge: https://www.ncbi.nlm.nih.gov/pubmed/25984700
.. _CEPH mixing: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2816205/
.. _VarScan 2: https://github.com/dkoboldt/varscan/releases 
.. _VarScan 2 Paper: https://www.ncbi.nlm.nih.gov/pubmed/22300766
.. _BCFTools: http://www.htslib.org/doc/bcftools.html
.. _VarDict: https://www.ncbi.nlm.nih.gov/pubmed/27060149
.. _Delly: https://www.ncbi.nlm.nih.gov/pubmed/22962449
.. _Lumpy: https://genomebiology.biomedcentral.com/articles/10.1186/gb-2014-15-6-r84
.. _WHAM: https://www.ncbi.nlm.nih.gov/pubmed/26625158
.. _CNVKit Paper: https://www.ncbi.nlm.nih.gov/pubmed/27100738
.. _SvABA Paper: https://www.ncbi.nlm.nih.gov/pubmed/29535149
.. _MetaSV Paper: https://www.ncbi.nlm.nih.gov/pubmed/25861968
.. _dbNSFP Paper: https://www.ncbi.nlm.nih.gov/pubmed/26555599
.. _GATK MuTect2: https://software.broadinstitute.org/gatk/documentation/tooldocs/3.8-0/org_broadinstitute_gatk_tools_walkers_cancer_m2_MuTect2.php
.. _Strelka2: https://github.com/Illumina/strelka
.. _MultiQC: https://multiqc.info/docs/
.. _PURPLE: https://github.com/hartwigmedical/hmftools/blob/master/purple/README.md
.. _Sequenza: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4269342/
.. _Manta: https://github.com/Illumina/manta
.. _Delly2: https://github.com/dellytools/delly
.. _GridSS: https://github.com/PapenfussLab/gridss