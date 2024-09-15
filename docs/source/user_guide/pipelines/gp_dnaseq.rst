.. _docs_gp_dnaseq:

.. spelling:: 
 
     haplotype
     Mpileup
     mpileup
     bcftools
     kilobases
     telomere
     mappability
     indel
     dna
     callsets
     intra
     nucleotid
     tdf

DNA Sequencing Pipeline
========================

:bdg-primary:`Version` |genpipes_version|

.. dropdown:: :material-outlined:`notifications_active;2em` v5.0.0 Update! 
   :color: success
   :open:

   Starting from **GenPipes v5.x** onwards, the DNA Sequencing Pipeline has been completely revamped. It is enhanced to include the functionality  that was earlier provided in **GenPipes v4.6.1** by the following standalone pipelines:
   
   * `Tumor Pair Sequencing Pipeline <https://genpipes.readthedocs.io/en/genpipes-v4.6.1/user_guide/pipelines/gp_tumourpair.html>`_ **Deprecated**
   * `DNA Sequencing (High Coverage) Pipeline <https://genpipes.readthedocs.io/en/genpipes-v4.6.1/user_guide/pipelines/gp_dnaseq_highcov.html>`_. **Deprecated**

.. tab-set:: 

      .. tab-item:: Usage

         .. dropdown:: Command
            :open:

            .. code::

                 genpipes dnaseq.py [-options ] [--genpipes_file GENPIPES_FILE.sh]
                 bash GENPIPES_FILE.sh

         .. dropdown:: Options

            .. include:: opt_dnaseq.inc
            .. include:: /common/gp_readset_opt.inc
            .. include:: /common/gp_common_opt.inc

         .. dropdown:: Example

            .. dropdown:: Germline

               .. tab-set:: 

                  .. tab-item:: SNV

                     .. include::  /user_guide/pipelines/example_runs/dnaseq_germ_snv.inc

                  .. tab-item:: SV
               
                     .. include::  /user_guide/pipelines/example_runs/dnaseq_germ_sv.inc

                  .. tab-item:: High Coverage
               
                     .. include::  /user_guide/pipelines/example_runs/dnaseq_germ_high_cov.inc

            .. dropdown:: Somatic

               .. tab-set:: 

                  .. tab-item:: Tumor Only
               
                     .. include::  /user_guide/pipelines/example_runs/dnaseq_som_tum_only.inc

                  .. tab-item:: FastPass
               
                     .. include::  /user_guide/pipelines/example_runs/dnaseq_som_fastpass.inc

                  .. tab-item:: Ensemble
               
                     .. include::  /user_guide/pipelines/example_runs/dnaseq_som_ensemble.inc

                  .. tab-item:: SV
               
                     .. include::  /user_guide/pipelines/example_runs/dnaseq_som_sv.inc

            .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

            .. card:: Test Dataset
               :link: docs_testdatasets
               :link-type: ref

               Use the :ref:`DNA sequencing test dataset <docs_testdatasets>` for this pipeline.

      .. tab-item:: Schema
         :name: dnaschema  

         .. dropdown:: Germline 
            
            .. tab-set::
               
               .. tab-item:: SNV

                  Figure below shows the schema of the DNA sequencing Germline SNV protocol. 

                  .. figure:: /img/pipelines/mmd/dnaseq.germ.snv.mmd.png
                     :align: center
                     :alt: dnaseq1 schema
                     :width: 100%
                     :figwidth: 95%

                     Figure: Schema - Germline SNV DNA Sequencing protocol

                  .. figure:: /img/pipelines/mmd/legend.mmd.png
                     :align: center
                     :alt: dada2 ampseq
                     :width: 100%
                     :figwidth: 75%

               .. tab-item:: SV

                  Figure below shows the schema of the DNA sequencing Germline SV protocol.

                  .. figure:: /img/pipelines/mmd/dnaseq.germ.sv.mmd.png
                     :align: center
                     :alt: dnaseq2 schema 
                     :width: 100%
                     :figwidth: 95%

                     Figure: Schema - Germline SV DNA Sequencing protocol

                  .. figure:: /img/pipelines/mmd/legend.mmd.png
                     :align: center
                     :alt: dada2 ampseq
                     :width: 100%
                     :figwidth: 75%

               .. tab-item:: High Coverage

                  Figure below shows the schema of the DNA sequencing Germline High Coverage protocol.

                  .. figure:: /img/pipelines/mmd/dnaseq.germ.highcov.mmd.png
                     :align: center
                     :alt: dnaseq3 schema 
                     :width: 100%
                     :figwidth: 95%

                     Figure: Schema - Germline High Coverage DNA Sequencing protocol

                  .. figure:: /img/pipelines/mmd/legend.mmd.png
                     :align: center
                     :alt: dada2 ampseq
                     :width: 100%
                     :figwidth: 75%

         .. dropdown:: Somatic 
            
            .. tab-set::
               
               .. tab-item:: Tumor Only

                  Figure below shows the schema of the DNA sequencing Somatic Tumor only protocol.

                  .. figure:: /img/pipelines/mmd/dnaseq.som.tumor.mmd.png
                     :align: center
                     :alt: dnaseq4 schema 
                     :width: 100%
                     :figwidth: 95%

                     Figure: Schema - Somatic Tumor Only DNA Sequencing protocol

                  .. figure:: /img/pipelines/mmd/legend.mmd.png
                     :align: center
                     :alt: dada2 ampseq
                     :width: 100%
                     :figwidth: 75%

               .. tab-item:: Fastpass

                  Figure below shows the schema of the DNA sequencing Somatic Fastpass protocol.

                  .. figure:: /img/pipelines/mmd/dnaseq.som.fastpass.mmd.png
                     :align: center
                     :alt: dnaseq4 schema 
                     :width: 100%
                     :figwidth: 95%

                     Figure: Schema - Somatic Fastpass DNA Sequencing protocol

                  .. figure:: /img/pipelines/mmd/legend.mmd.png
                     :align: center
                     :alt: dada2 ampseq
                     :width: 100%
                     :figwidth: 75%

               .. tab-item:: Ensemble

                  Figure below shows the schema of the DNA sequencing Somatic Ensemble protocol.

                  .. figure:: /img/pipelines/mmd/dnaseq.som.ensemble.mmd.png
                     :align: center
                     :alt: dnaseq4 schema 
                     :width: 100%
                     :figwidth: 95%

                     Figure: Schema - Somatic Ensemble DNA Sequencing protocol

                  .. figure:: /img/pipelines/mmd/legend.mmd.png
                     :align: center
                     :alt: dada2 ampseq
                     :width: 100%
                     :figwidth: 75%

               .. tab-item:: SV

                  Figure below shows the schema of the DNA sequencing Somatic SV protocol.

                  .. figure:: /img/pipelines/mmd/dnaseq.som.sv.mmd.png
                     :align: center
                     :alt: dnaseq4 schema 
                     :width: 100%
                     :figwidth: 95%

                     Figure: Schema - Somatic SV DNA Sequencing protocol

                  .. figure:: /img/pipelines/mmd/legend.mmd.png
                     :align: center
                     :alt: dada2 ampseq
                     :width: 100%
                     :figwidth: 75%

      .. tab-item:: Steps

         .. dropdown:: Germline

            .. tab-set::

               .. tab-item:: SNV

                  +----+------------------------------------+
                  |    | *Germline SNV*                     |
                  +====+====================================+
                  | 1. | |gatk_sam_to_fastq|                |
                  +----+------------------------------------+
                  | 2. | |trim_fastp|                       |
                  +----+------------------------------------+
                  | 3. | |bwa_mem2_samtools_sort|           |
                  +----+------------------------------------+
                  | 4. | |gatk_mark_dup|                    |
                  +----+------------------------------------+
                  | 5. | |set_interval_list|                |
                  +----+------------------------------------+
                  | 6. | |gatk_haplotype_caller|            |
                  +----+------------------------------------+
                  | 7. | |merge_call_i_gvcf|                |
                  +----+------------------------------------+
                  | 8. | |combine_gvcf|                     |
                  +----+------------------------------------+
                  | 9. | |merge_call_c_gvcf|                |
                  +----+------------------------------------+
                  | 10.| |variant_recalib|                  |
                  +----+------------------------------------+
                  | 11.| |hc_dec_norm|                      |
                  +----+------------------------------------+
                  | 12.| |hc_flag_map|                      |
                  +----+------------------------------------+
                  | 13.| |hc_snp_ann|                       |
                  +----+------------------------------------+
                  | 14.| |hc_snp_eff|                       |
                  +----+------------------------------------+
                  | 15.| |hc_dbnsfp_ann|                    |
                  +----+------------------------------------+
                  | 16.| |hc_gemini_ann|                    |
                  +----+------------------------------------+
                  | 17.| |m_dna_picard|                     |
                  +----+------------------------------------+
                  | 18.| |m_dna_sample_mosdepth|            |     
                  +----+------------------------------------+
                  | 19.| |picard_calc_hs_m|                 |
                  +----+------------------------------------+
                  | 20.| |m_verify_bam_id|                  |
                  +----+------------------------------------+
                  | 21.| |run_multiqc|                      |
                  +----+------------------------------------+
                  | 22.| |sym_link_fastq|                   |
                  +----+------------------------------------+
                  | 23.| |sym_link_final_bam|               |
                  +----+------------------------------------+
                  | 24.| |m_vcftools_missing_i|             |
                  +----+------------------------------------+
                  | 25.| |m_vcftools_depth_i|               |
                  +----+------------------------------------+
                  | 26.| |m_gatk_sample_fp|                 |
                  +----+------------------------------------+
                  | 27.| |m_gatk_cluster_fp|                |       
                  +----+------------------------------------+

               .. tab-item:: SV

                  +----+------------------------------------+
                  |    | *Germline SV*                      |
                  +====+====================================+
                  | 1. | |gatk_sam_to_fastq|                |
                  +----+------------------------------------+
                  | 2. | |trim_fastp|                       |
                  +----+------------------------------------+
                  | 3. | |bwa_mem2_samtools_sort|           |
                  +----+------------------------------------+
                  | 4. | |gatk_mark_dup|                    |
                  +----+------------------------------------+
                  | 5. | |sym_link_final_bam|               |
                  +----+------------------------------------+
                  | 6. | |set_interval_list|                |
                  +----+------------------------------------+
                  | 7. | |gatk_haplotype_caller|            |
                  +----+------------------------------------+
                  | 8. | |merge_call_i_gvcf|                |
                  +----+------------------------------------+
                  | 9. | |m_dna_picard|                     | 
                  +----+------------------------------------+
                  | 10.| |m_dna_sample_mosdepth|            |     
                  +----+------------------------------------+
                  | 11.| |picard_calc_hs_m|                 |
                  +----+------------------------------------+
                  | 12.| |run_multiqc|                      |
                  +----+------------------------------------+
                  | 13.| |delly_call_filter|                |
                  +----+------------------------------------+
                  | 14.| |delly_sv_annotation|              |
                  +----+------------------------------------+
                  | 15.| |germline_manta|                   |
                  +----+------------------------------------+
                  | 16.| |manta_sv_annotation|              |
                  +----+------------------------------------+
                  | 17.| |lumpy_paired_sv|                  |
                  +----+------------------------------------+
                  | 18.| |lumpy_sv_annotation|              |
                  +----+------------------------------------+
                  | 19.| |wham_sv_call|                     |
                  +----+------------------------------------+
                  | 20.| |wham_sv_annotation|               |
                  +----+------------------------------------+
                  | 21.| |cnvkit_batch|                     |
                  +----+------------------------------------+
                  | 22.| |cnvkit_sv_annotation|             |
                  +----+------------------------------------+
                  | 23.| |run_breakseq2|                    |
                  +----+------------------------------------+
                  | 24.| |ensemble_metasv|                  |
                  +----+------------------------------------+
                  | 25.| |metasv_sv_annotation|             |
                  +----+------------------------------------+

               .. tab-item:: High Coverage

                  +----+------------------------------------+
                  |    | *Germline High Coverage*           |
                  +====+====================================+
                  | 1. | |gatk_sam_to_fastq|                |
                  +----+------------------------------------+
                  | 2. | |trim_fastp|                       |
                  +----+------------------------------------+
                  | 3. | |bwa_mem2_samtools_sort|           |
                  +----+------------------------------------+ 
                  | 4. | |samtools_merge_files|             |                
                  +----+------------------------------------+ 
                  | 5. | |gatk_fixmate|                     |
                  +----+------------------------------------+ 
                  | 6. | |m_dna_picard|                     | 
                  +----+------------------------------------+
                  | 7. | |m_dna_sample_mosdepth|            |     
                  +----+------------------------------------+
                  | 8. | |picard_calc_hs_m|                 |
                  +----+------------------------------------+ 
                  | 9. | |m_verify_bam_id|                  |
                  +----+------------------------------------+ 
                  | 10.| |germline_varscan2|                |
                  +----+------------------------------------+ 
                  | 11.| |preprocess_vcf|                   |
                  +----+------------------------------------+
                  | 12.| |snp_effect|                       | 
                  +----+------------------------------------+ 
                  | 13.| |hc_gemini_ann|                    |
                  +----+------------------------------------+ 
                  | 14.| |run_multiqc|                      |
                  +----+------------------------------------+ 
                  | 15.| |cram_output|                      |
                  +----+------------------------------------+ 

         .. dropdown:: Somatic

            .. tab-set::

               .. tab-item:: Tumor Only
                                                    
                  +----+------------------------------------+
                  |    | *Somatic Tumor Only*               |
                  +====+====================================+
                  | 1. | |gatk_sam_to_fastq|                |
                  +----+------------------------------------+
                  | 2. | |trim_fastp|                       |
                  +----+------------------------------------+
                  | 3. | |bwa_mem2_samtools_sort|           |
                  +----+------------------------------------+                  
                  | 4. | |gatk_mark_dup|                    |
                  +----+------------------------------------+
                  | 5. | |sym_link_final_bam|               |
                  +----+------------------------------------+
                  | 6. | |m_dna_picard|                     |
                  +----+------------------------------------+
                  | 7. | |m_dna_sample_mosdepth|            |
                  +----+------------------------------------+                  
                  | 8. | |picard_calc_hs_m|                 |
                  +----+------------------------------------+
                  | 9. | |m_verify_bam_id|                  |
                  +----+------------------------------------+
                  | 10.| |run_multiqc|                      |
                  +----+------------------------------------+
                  | 11.| |set_interval_list|                |
                  +----+------------------------------------+                  
                  | 12.| |gatk_haplotype_caller|            |
                  +----+------------------------------------+
                  | 13.| |merge_call_i_gvcf|                |
                  +----+------------------------------------+
                  | 14.| |combine_gvcf|                     |
                  +----+------------------------------------+
                  | 15.| |merge_call_c_gvcf|                |
                  +----+------------------------------------+                  
                  | 16.| |variant_recalib|                  |
                  +----+------------------------------------+
                  | 17.| |hc_dec_norm|                      |
                  +----+------------------------------------+
                  | 18.| |cnvkit_batch|                     |
                  +----+------------------------------------+
                  | 19.| |split_tumor_only|                 |
                  +----+------------------------------------+                  
                  | 20.| |filter_tumor_only|                |
                  +----+------------------------------------+
                  | 21.| |report_cpsr|                      |
                  +----+------------------------------------+
                  | 22.| |report_pcgr|                      |
                  +----+------------------------------------+

               .. tab-item:: Fastpass
                                                    
                  +----+------------------------------------+
                  |    | *Somatic Fastpass*                 |
                  +====+====================================+
                  | 1. | |gatk_sam_to_fastq|                |
                  +----+------------------------------------+
                  | 2. | |trim_fastp|                       |
                  +----+------------------------------------+
                  | 3. | |bwa_mem2_samtools_sort|           |
                  +----+------------------------------------+
                  | 4. | |gatk_mark_dup|                    |
                  +----+------------------------------------+
                  | 5. | |set_interval_list|                |
                  +----+------------------------------------+
                  | 6. | |sequenza|                         |
                  +----+------------------------------------+
                  | 7. | |rawmpileup|                       |
                  +----+------------------------------------+
                  | 8. | |paired_varscan2|                  |
                  +----+------------------------------------+
                  | 9. | |merge_varscan2|                   |
                  +----+------------------------------------+
                  | 10.| |preprocess_vcf|                   |
                  +----+------------------------------------+
                  | 11.| |cnvkit_batch|                     |
                  +----+------------------------------------+
                  | 12.| |filter_germline|                  |
                  +----+------------------------------------+
                  | 13.| |report_cpsr|                      |
                  +----+------------------------------------+                  
                  | 14.| |filter_somatic|                   |
                  +----+------------------------------------+
                  | 15.| |report_pcgr|                      |
                  +----+------------------------------------+
                  | 16.| |conpair_concordance_contamination||
                  +----+------------------------------------+
                  | 17.| |m_dna_picard|                     |
                  +----+------------------------------------+
                  | 18.| |m_dna_sample_mosdepth|            |
                  +----+------------------------------------+
                  | 19.| |run_multiqc|                      |
                  +----+------------------------------------+
                  | 20.| |sym_link_report|                  |
                  +----+------------------------------------+
                  | 21.| |sym_link_fastq_pair|              |
                  +----+------------------------------------+
                  | 22.| |sym_link_panel|                   |
                  +----+------------------------------------+
                  | 23.| |cram_output|                      |
                  +----+------------------------------------+

               .. tab-item:: Ensemble
                                                    
                  +----+------------------------------------+
                  |    | *Somatic Ensemble*                 |
                  +====+====================================+
                  | 1. | |gatk_sam_to_fastq|                |
                  +----+------------------------------------+
                  | 2. | |trim_fastp|                       |
                  +----+------------------------------------+
                  | 3. | |bwa_mem2_samtools_sort|           |
                  +----+------------------------------------+
                  | 4. | |gatk_mark_dup|                    |
                  +----+------------------------------------+
                  | 5. | |set_interval_list|                |
                  +----+------------------------------------+
                  | 6. | |conpair_concordance_contamination||
                  +----+------------------------------------+
                  | 7. | |m_dna_picard|                     |
                  +----+------------------------------------+
                  | 8. | |m_dna_sample_mosdepth|            |
                  +----+------------------------------------+
                  | 9. | |sequenza|                         |
                  +----+------------------------------------+
                  | 10.| |manta_sv_calls|                   |
                  +----+------------------------------------+
                  | 11.| |strelka2_paired_somatic|          |
                  +----+------------------------------------+
                  | 12.| |strelka2_paired_germline|         |
                  +----+------------------------------------+
                  | 13.| |strelka2_paired_snpEff|           |
                  +----+------------------------------------+
                  | 14.| |purple|                           |
                  +----+------------------------------------+
                  | 15.| |rawmpileup|                       |
                  +----+------------------------------------+
                  | 16.| |paired_varscan2|                  |
                  +----+------------------------------------+
                  | 17.| |merge_varscan2|                   |
                  +----+------------------------------------+
                  | 18.| |paired_mutect2|                   |
                  +----+------------------------------------+
                  | 19.| |merge_mutect2|                    |
                  +----+------------------------------------+
                  | 20.| |vardict_paired|                   |
                  +----+------------------------------------+
                  | 21.| |merge_filter_paired_vardict|      |
                  +----+------------------------------------+
                  | 22.| |ensemble_somatic|                 |
                  +----+------------------------------------+
                  | 23.| |gatk_variant_annotator_somatic|   |
                  +----+------------------------------------+
                  | 24.| |merge_gatk_var_annotator_somatic| |
                  +----+------------------------------------+
                  | 25.| |ensemble_germline_loh|            |
                  +----+------------------------------------+
                  | 26.| |gatk_variant_annotator_germline|  |
                  +----+------------------------------------+
                  | 27.| |merge_gatk_var_anno_germline|     |
                  +----+------------------------------------+
                  | 28.| |cnvkit_batch|                     |
                  +----+------------------------------------+
                  | 29.| |filter_germline|                  |
                  +----+------------------------------------+
                  | 30.| |report_cpsr|                      |
                  +----+------------------------------------+
                  | 31.| |filter_somatic|                   |
                  +----+------------------------------------+
                  | 32.| |report_pcgr|                      |
                  +----+------------------------------------+
                  | 33.| |run_multiqc|                      |
                  +----+------------------------------------+
                  | 34.| |sym_link_fastq_pair|              |
                  +----+------------------------------------+
                  | 35.| |sym_link_final_bam|               |
                  +----+------------------------------------+                  
                  | 36.| |sym_link_report|                  |
                  +----+------------------------------------+
                  | 37.| |sym_link_ensemble|                |
                  +----+------------------------------------+
                  | 38.| |cram_output|                      |
                  +----+------------------------------------+

               .. tab-item:: SV
                                                    
                  +----+------------------------------------+
                  |    | *Somatic SV*                       |
                  +====+====================================+
                  | 1. | |gatk_sam_to_fastq|                |
                  +----+------------------------------------+
                  | 2. | |trim_fastp|                       |
                  +----+------------------------------------+
                  | 3. | |bwa_mem2_samtools_sort|           |
                  +----+------------------------------------+
                  | 4. | |gatk_mark_dup|                    |
                  +----+------------------------------------+
                  | 5. | |set_interval_list|                |
                  +----+------------------------------------+
                  | 6. | |manta_sv_calls|                   |
                  +----+------------------------------------+
                  | 7. | |strelka2_paired_somatic|          |
                  +----+------------------------------------+
                  | 8. | |gridss_paired_somatic|            |
                  +----+------------------------------------+
                  | 9. | |purple_sv|                        |
                  +----+------------------------------------+
                  | 10.| |linx_annotations_somatic|         |
                  +----+------------------------------------+
                  | 11.| |linx_annotations_germline|        |
                  +----+------------------------------------+
                  | 12.| |linx_plot|                        |
                  +----+------------------------------------+
                  | 13.| |run_multiqc|                      |
                  +----+------------------------------------+
                  | 14.| |cram_output|                      |
                  +----+------------------------------------+                 

         .. card::

            .. include:: steps_dnaseq.inc

      .. tab-item:: About

         .. card::

            DNA sequencing is the process of determining the sequence of nucleotides in a section of DNA. Over the past decade, `long-read`_, single-molecule DNA sequencing technologies have emerged as powerful players in genomics. With the ability to generate reads tens to thousands of kilobases in length with an accuracy approaching that of short-read sequencing technologies, these platforms have proven their ability to resolve some of the most challenging regions of the human genome, detect previously inaccessible structural variants and generate some of the first telomere-to-telomere assemblies of whole chromosomes.

            Burrows-Wheeler Alignment tool, `BWA`_, is a new read alignment package that is based on backward search with Burrows–Wheeler Transform (BWT), to efficiently align short sequencing reads against a large reference sequence such as the human genome, allowing mismatches and gaps. BWA is ∼10–20 times `faster than`_ Mapping and Assembly with Quality, `MAQ`_, while achieving similar accuracy. In addition, BWA outputs alignment in the new standard SAM (Sequence Alignment/Map) format. Variant calling and other downstream analyses after the alignment can be achieved with the open source `SAMtools software package`_.

            DNA Sequencing GenPipes pipeline has been implemented by optimizing the Genome Analysis Toolkit, `GATK`_ best practices standard operating protocols. This procedure entails trimming raw reads derived from whole-genome or exome data followed by alignment to a known reference, post-alignment refinements, and variant calling. Trimmed reads are aligned to a reference by the Burrows-Wheeler Aligner (BWA), `bwa-mem`_. Refinements of mismatches near insertions and deletions (indels) and base qualities are performed using GATK indels realignment and base recalibration to improve read quality after alignment. Processed reads are marked as fragment duplicates using Picard MarkDuplicates and single-nucleotide polymorphisms and small indels are identified using either GATK haplotype callers or `SAMtools`_ mpileup. 

            The `Genome in a Bottle dataset`_ was used to select steps and parameters minimizing the false-positive rate and maximizing the true-positive variants to achieve a sensitivity of 99.7%, precision of 99.1%, and F1 score of 99.4%. Finally, additional annotations are incorporated using `dbNSFP`_ and / or Gemini and QC metrics are collected at various stages and visualized using `MultiQC`_. 

            The standard MUGQIC DNA-Seq pipeline uses BWA to align reads to the reference genome. Treatment and filtering of mapped reads approaches as INDEL realignment, mark duplicate reads, recalibration and sort are executed using Picard and GATK. Samtools MPILEUP and bcftools are used to produce the standard SNP and indels variants file (VCF). Additional SVN annotations mostly applicable to human samples include mappability flags, dbSNP annotation and extra information about SVN by using published databases. The SNPeff tool is used to annotate variants using an integrated database of functional predictions from multiple algorithms (SIFT, Polyphen2, LRT and MutationTaster, PhyloP and GERP++, etc.) and to calculate the effects they produce on known genes. Refer to the list of `SnpEff effects`_. 

            GenPipes DNA sequencing pipeline offers the following protocol options:

            #. Default, Germline Single Neucleotide Variant Analysis uses GATK HaplotypeCaller caller (-t germline_snv)
            #. Germline Structural Variations for cancer predisposition analysis Another  (-t germline_sv) 
            #. Germline High Coverage for comprehensive variant detection (-t germline_high_cov)
            #. Somatic Tumor only analysis (-t somatic_tumor_only)
            #. Quick assessment using exome capture regions and the 1000bp flanking regions with Somatic FastPass (-t somatic_fastpass)
            #. Somatic Ensemble for detecting somatic mutations via the best combination of callers for both SNV and SV  (-t somatic_ensemble)
            #. Somatic Structural Variant (SV) detectiom (-t somatic_sv)

            See :ref:`dnaschema` tab for the pipeline workflow. For the latest implementation and usage details refer to DNA Sequencing implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq/README.md>`_ file.

            **References**

            * `Three-stage quality control strategies for DNA sequencing <https://academic.oup.com/bib/article/15/6/879/180439>`_
            * `NGS Mapping, errors and quality control <http://bioinformatics.org.au/ws14/wp-content/uploads/ws14/sites/5/2014/07/Felicity-Newell_presentation.pdf>`_
            * `dbNSFP: a lightweight database of human nonsynonymous SNPs and their functional predictions <https://www.ncbi.nlm.nih.gov/pubmed/21520341>`_
            * `DNA-Seq Pipeline <https://bitbucket.org/mugqic/genpipes/downloads/MUGQIC_Bioinfo_DNA-Seq.pptx>`_
            * `Manta - Rapid Detection of Structural Variants <https://pubmed.ncbi.nlm.nih.gov/26647377/>`_, `Using Manta for filtering and annotations <https://pmbio.org/module-05-somatic/0005/03/02/Somatic_SV_FilteringAnnotationReview/>`_.

.. The following are replacement texts used in this file

.. |gatk_sam_to_fastq| replace:: `GATK SAM to FastQ`_
.. |trim_fastp| replace:: `Trim FastP`_
.. |bwa_mem2_samtools_sort| replace:: `BWA Mem2 SAMTools Sort`_
.. |gatk_mark_dup| replace:: `GATK Mark Duplicates`_
.. |set_interval_list| replace:: `Set Interval List`_
.. |gatk_haplotype_caller| replace:: `GATK Haplotype Caller`_
.. |merge_call_i_gvcf| replace:: `Merge and call individual GVCF`_
.. |merge_call_c_gvcf| replace:: `Merge and call combined GVCF`_
.. |combine_gvcf| replace:: `Combine GVCF`_
.. |variant_recalib| replace:: `Variant Recalibrator`_
.. |hc_dec_norm| replace:: `Haplotype caller decompose and normalize`_
.. |hc_flag_map| replace:: `Haplotype caller flag mappability`_
.. |hc_snp_ann| replace:: `Haplotype caller SNP ID annotation`_
.. |hc_snp_eff| replace:: `Haplotype caller SNP Effect`_
.. |hc_dbnsfp_ann| replace:: `Haplotype caller dbNSFP annotation`_
.. |m_dna_picard| replace:: `Metrics DNA Picard`_
.. |m_dna_sample_mosdepth| replace:: `DNA Sample MosDepth Metrics`_
.. |picard_calc_hs_m| replace:: `Picard Calculate HS Metrics`_
.. |m_verify_bam_id| replace:: `Metrics Verify BAM ID`_
.. |run_multiqc| replace:: `Run MultiQC`_
.. |sym_link_fastq| replace:: `Sym Link FastQ`_
.. |sym_link_final_bam| replace:: `Sym Link Final BAM`_
.. |m_vcftools_missing_i| replace:: `Metrics VCFTools Missing Individual`_
.. |m_vcftools_depth_i| replace:: `Metrics VCFTools Depth Individual`_
.. |m_gatk_sample_fp| replace:: `Metrics GATK Sample Fingerprint`_
.. |m_gatk_cluster_fp| replace:: `Metrics GATK Cluster Fingerprint`_
.. |delly_call_filter| replace:: `Delly2 Call Filter`_
.. |delly_sv_annotation| replace:: `Delly2 SV Annotation`_
.. |germline_manta| replace:: `Germline Manta`_
.. |manta_sv_annotation| replace:: `Manta SV Annotation`_
.. |lumpy_paired_sv| replace:: `Lumpy Paired SV`_
.. |lumpy_sv_annotation| replace:: `Lumpy SV Annotation`_
.. |wham_sv_call| replace:: `Wham SV Call`_
.. |wham_sv_annotation| replace:: `Wham SV Annotation`_
.. |cnvkit_batch| replace:: `CNVkit Batch`_
.. |cnvkit_sv_annotation| replace:: `CNVkit SV Annotation`_
.. |run_breakseq2| replace:: `Run BreakSeq2`_
.. |ensemble_metasv| replace:: `Ensemble MetaSV`_
.. |metasv_sv_annotation| replace:: `MetaSV Annotation`_
.. |samtools_merge_files| replace:: `SAMTools Merge Files`_
.. |gatk_fixmate| replace:: `GATK Fixmate`_
.. |germline_varscan2| replace:: `Germline Varscan2`_
.. |preprocess_vcf| replace:: `PreProcess VCF`_
.. |snp_effect| replace:: `SNP Effect`_
.. |hc_gemini_ann| replace:: `Haplotype caller Gemini annotation`_
.. |split_tumor_only| replace:: `Split Tumor Only`_
.. |filter_tumor_only| replace:: `Filter Tumor Only`_
.. |report_cpsr| replace:: `Report CPSR`_
.. |report_pcgr| replace:: `Report PCGR`_
.. |sequenza| replace:: `Sequenza Step`
.. |rawmpileup| replace:: `Raw Mpileup`_
.. |paired_varscan2| replace:: `Paired Var Scan 2`_
.. |merge_varscan2| replace:: `Merge Var Scan 2`_
.. |filter_germline| replace:: `Filter Germline`_
.. |filter_somatic|  replace:: `Filter Somatic`_
.. |conpair_concordance_contamination| replace:: `Conpair Concordance Contamination`_
.. |sym_link_report| replace:: `Sym Link Report`_
.. |sym_link_fastq_pair| replace:: `Sym Link FASTQ Pair`_
.. |sym_link_panel| replace:: `Sym Link Panel`_
.. |manta_sv_calls| replace:: `Manta SV Calls`_
.. |strelka2_paired_somatic| replace:: `Strelka2 Paired Somatic`_
.. |strelka2_paired_germline| replace:: `Strelka2 Paired Germline`_
.. |strelka2_paired_snpEff| replace:: `Strelka2 Paired SnpEff`_
.. |purple| replace:: `Purple Ploidy Estimator`_
.. |purple_sv| replace:: `Purple SV`_
.. |paired_mutect2| replace:: `Paired Mutect2`_
.. |merge_mutect2| replace:: `Merge Mutect2`_
.. |vardict_paired| replace:: `VarDict Paired`_
.. |merge_filter_paired_vardict| replace:: `Merge Filter Paired VarDict`_
.. |ensemble_somatic| replace:: `Ensemble Somatic`_
.. |gatk_variant_annotator_somatic| replace:: `GATK Variant Annotator Somatic`_
.. |merge_gatk_var_annotator_somatic| replace:: `Merge GATK Variant Annotator Somatic`_
.. |ensemble_germline_loh| replace:: `Ensemble Germline Loh`_
.. |gatk_variant_annotator_germline| replace:: `GATK Variant Annotator Germline`_
.. |merge_gatk_var_anno_germline| replace:: `Merge GATK Variant Annotator Germline`_
.. |sym_link_ensemble| replace:: `Sym Link Ensemble`_
.. |gridss_paired_somatic| replace:: `GRIDSS Paired Somatic`_
.. |linx_annotations_somatic| replace:: `Linx Annotations Somatic`_
.. |linx_annotations_germline| replace:: `Linx Annotations Germline`_
.. |linx_plot| replace:: `Linx Plot`_

.. include::  repl_cram_op.inc

.. The following are html links used in this text

.. _BWA: http://bio-bwa.sourceforge.net
.. _faster than:  https://scinapse.io/papers/2103441770
.. _MAQ: http://maq.sourceforge.net
.. _bwa-mem: https://www.ncbi.nlm.nih.gov/pubmed/19451168
.. _SAMtools software package: http://samtools.sourceforge.net
.. _Genome in a Bottle dataset: https://www.nist.gov/programs-projects/genome-bottle
.. _MultiQC: https://multiqc.info
.. _Mpileup: http://samtools.sourceforge.net/mpileup.shtml 
.. _SnpEff effects: https://pcingola.github.io/SnpEff/se_introduction/
.. _Sample DNA-Seq Report: http://gqinnovationcenter.com/services/bioinformatics/tools/dnaReport/index.html
.. _long-read: https://www.nature.com/articles/s41576-020-0236-x 
.. _Structural Variation: https://www.longdom.org/open-access/structural-variation-detection-from-next-generation-sequencing-2469-9853-S1-007.pdf
.. _three reasons: https://software.broadinstitute.org/cancer/software/genepattern/modules/docs/ABSOLUTE/1
.. _DREAM3 challenge: https://www.ncbi.nlm.nih.gov/pubmed/25984700
.. _CEPH mixing: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2816205/
.. _VarScan 2: https://github.com/dkoboldt/varscan/releases 
.. _VarScan 2 Paper: https://www.ncbi.nlm.nih.gov/pubmed/22300766
.. _BCFTools: http://www.htslib.org/doc/bcftools.html
.. _VarDict: https://www.ncbi.nlm.nih.gov/pubmed/27060149
.. _Delly: https://www.ncbi.nlm.nih.gov/pubmed/22962449
.. _Lumpy: https://genomebiology.biomedcentral.com/articles/10.1186/gb-2014-15-6-r84
.. _CNVKit Paper: https://www.ncbi.nlm.nih.gov/pubmed/27100738
.. _SvABA Paper: https://www.ncbi.nlm.nih.gov/pubmed/29535149
.. _MetaSV Paper: https://www.ncbi.nlm.nih.gov/pubmed/25861968
.. _dbNSFP Paper: https://www.ncbi.nlm.nih.gov/pubmed/26555599
.. _GATK MuTect2: https://software.broadinstitute.org/gatk/documentation/tooldocs/3.8-0/org_broadinstitute_gatk_tools_walkers_cancer_m2_MuTect2.php
.. _Strelka2: https://github.com/Illumina/strelka
.. _Purple: https://github.com/hartwigmedical/hmftools/blob/master/purple/README.md
.. _Sequenza: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC4269342/
.. _Manta: https://github.com/Illumina/manta
.. _Delly2: https://github.com/dellytools/delly
.. _GRIDSS: https://github.com/PapenfussLab/gridss
