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
      
Tumor Pair Sequencing Pipeline
================================

.. warning::  Not available in GenPipes 3.2.0

     Please note that Tumor Pair Sequencing Pipeline is not available in GenPipes Release 3.2.0
     
     If you wish to use this pipeline, you may need to deploy GenPipes 3.1.5

     The documentation below refers to the pipeline corresponding to GenPipes Release 3.1.5.
     It is available here only for reference.

Human genome comprises of a set of chromosome pairs. One chromosome in each pair, called homolog, is derived from each parent. It is typically referred to as diploid whereas the set of chromosomes from a single parent is called haploid genome. For a given gene on a given chromosome, there is a comparable, if not identical, gene on the other chromosome in the pair, known as an allele. Large structural alterations in chromosomes can change the number of copies of affected genes on those chromosomes. This is one of the key reasons for causing cancer.  In cancer cells, instead of having a homologous pair of alleles for a given gene, there may be deletions or duplications of those genes. 


Such alterations leads to unequal contribution of one allele over the other, altering the copy number of a given allele. These variations in copy number indicated by the ratio of cancer cell copy number to normal cell copy number can provide information regarding the structure and history of cancer. However, when DNA is extracted, there is a mix of cancer and normal cells and this information regarding absolute copy number per cancer cell is lost in DNA extraction process.  Hence it must be inferred.

Inferring absolute copy number is difficult for `three reasons`_:

* cancer cells are nearly always intermixed with an unknown fraction of normal cells; the measure for this is tumor purity
* the actual quantity of DNA in the cancer cells after gross numerical and structural chromosomal changes is unknown; the measure for this is tumor ploidy
* the cancer cell population may be heterogeneous, possibly because of ongoing mutations and changes

Tumor purity and ploidy have a substantial impact on next-gen sequence analyses of tumor samples and may alter the biological and clinical interpretation of results.

GenPipes Tumor Analysis pipeline is designed to detect somatic variants from a tumor and match normal sample pair more accurately.

.. contents:: :local:

----

Introduction
------------

GenPipes Tumor Pair workflow consumes BAM files. It inherits the BAM processing protocol from DNA-seq implementation, for retaining the benchmarking optimizations, but differs in alignment refinement and mutation identification. It achieves this by maximizing the information, utilizing both tumor and normal samples together. 

The pipeline is based on an ensemble approach, which was optimized using both the `DREAM3 challenge`_ and the CEPH mixture datasets to select the best combination of callers for both SNV and structural variation detection. For SNVs, multiple callers such as 'GATK MuTect2`_, `VarScan 2`_, `BCFTools`_, `VarDict`_ were combined to achieve a sensitivity of 97.5%, precision of 98.8%, and F1 score of 98.1% for variants found in ≥2 callers.

Similarly, SVs were identified using multiple callers such as `DELLY`_, `LUMPY`_, `WHAM`_, `CNVKit`_, and `SvABA`_ combined using `MetaSV`_ to achieve a sensitivity of 84.6%, precision of 92.4%, and F1 score of 88.3% for duplication variants found in the DREAM3 dataset. The pipeline also integrates specific cancer tools to estimate tumor purity and tumor ploidy of sample pair normal−tumor.  

Additional annotations are incorporated to the SNV calls using `dbNSFP`_ and/or `Gemini`_, and QC metrics are collected at various stages and visualized using `MultiQC`_. 

GenPipes Tumor Pair pipeline has three protocol options: sv, ensemble, or fastpass.  For details refer to `Pipeline Schema`_ section below. 

----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to Tumor Pair Pipeline implementation `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/tumor_pair//README.md>`_ file.

----

Usage
-----

::

  python tumor_pair.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
                     [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]
                     [--no-json] [--report] [--clean]
                     [-l {debug,info,warning,error,critical}] [--sanity-check]
                     [--container {docker, singularity} {<CONTAINER PATH>, <CONTAINER NAME>}]
                     [-p PAIRS] [-t {sv,ensemble,fastpass}] [-r READSETS] [-v] 

**Optional Arguments**

::
  
  -h                    show this help message and exit
  --help                show detailed description of pipeline and steps
  -c CONFIG [CONFIG ...], --config CONFIG [CONFIG ...]
                        config INI-style list of files; config parameters are
                        overwritten based on files order
  -s STEPS, --steps STEPS
                        step range e.g. '1-5', '3,6,7', '2,4-8'
  -o OUTPUT_DIR, --output-dir OUTPUT_DIR
                        output directory (default: current)
  -j {pbs,batch,daemon,slurm}, --job-scheduler {pbs,batch,daemon,slurm}
                        job scheduler type (default: slurm)
  -f, --force           force creation of jobs even if up to date (default:
                        false)
  --no-json             do not create a JSON file per analysed sample to track the
                        analysis status (default: false i.e., JSON file will be
                        created)
  --report              create 'pandoc' command to merge all job markdown
                        report files in the given step range into HTML, if
                        they exist; if --report is set, --job-scheduler,
                        --force, --clean options and job up-to-date status are
                        ignored (default: false)
  --clean               create 'rm' commands for all job removable files in
                        the given step range, if they exist; if --clean is
                        set, --job-scheduler, --force options and job up-to-
                        date status are ignored (default: false)
  -l {debug,info,warning,error,critical}, --log {debug,info,warning,error,critical}
                        log level (default: info)
  --sanity-check        run the pipeline in `sanity check mode` to verify that
                        all the input files needed for the pipeline to run are
                        available on the system (default: false)
  --container {docker, singularity} {<CONTAINER PATH>, <CONTAINER NAME>}
                        run pipeline inside a container providing a container
                        image path or accessible docker/singularity hub path
  -p PAIRS, --pairs PAIRS
                        pairs file
  -t {sv,ensemble,fastpass}, --type {sv,ensemble,fastpass}
                        tumor pair analysis type
  -r READSETS, --readsets READSETS
                        readset file
  -v, --version         show the version information and exit

----

Example Run
-----------

Use the following commands to execute MUGQIC DNA sequencing pipeline:

::

  python tumor_pair.py -c $MUGQIC_PIPELINES_HOME/pipelines/dnaseq/dnaseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/tumor_pair/tumor_pair.base.ini $MUGQIC_PIPELINES_HOME/pipelines/tumor_pair/tumor_pair.guillimin.ini -r readset.tumorPair.txt -p pairs.csv -s 1-44 > tumor_pairCommands.sh

  bash tumor_pairCommands.sh 

where, p pairs : format - patient_name,normal_sample_name,tumor_sample_name

You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

----

Pipeline Schema
---------------

Pair Pipeline. You can refer to the latest `pipeline implementation <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/tumor_pair/>`_.

There are three options for Tumor Pair Pipeline: sv, ensemble and fastpass.

Figure below shows the schema of the Tumor Pair Pipeline (sv) option. See here to download a high resolution image of `Tumor Pair Sequencing Pipeline (sv) <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_tumor_pair_sv.png>`_ to download a high resolution image of the same.

.. figure:: /img/pipelines/GenPipes_tumor_pair_sv.png
   :align: center
   :alt: tumor_pair_sv schema

   Figure: Schema of Tumor Pair Pipeline (sv)

Figure below shows the schema of the Tumor Pair Pipeline (ensemble) option. See here to download a high resolution image of `Tumor Pair Sequencing Pipeline (ensemble) <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_tumor_pair_ensemble.png>`_ to download a high resolution image of the same.

.. figure:: /img/pipelines/GenPipes_tumor_pair_ensemble.png
   :align: center
   :alt: tumor_pair_ensemble schema

   Figure: Schema of Tumor Pair Pipeline (ensemble)

Figure below shows the schema of the Tumor Pair Pipeline (fastpass) option. See here to download a high resolution image of `Tumor Pair Sequencing Pipeline (fastpass) <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_tumor_pair_fastpass.png>`_ to download a high resolution image of the same.

.. figure:: /img/pipelines/GenPipes_tumor_pair_fastpass.png
   :align: center
   :alt: tumor_pair_fastpass schema

   Figure: Schema of Tumor Pair Pipeline (fastpass)

----

Pipeline Steps
--------------

The table below shows various steps that constitute the Tumor Pair Pipeline.

+----+-----------------------------------------+
|    | *Tumor Pair Pipeline Steps*             |
+====+=========================================+
| 1. | |picard_sam_to_fastq|                   |
+----+-----------------------------------------+
| 2. | |trimmomatic|                           |
+----+-----------------------------------------+
| 3. | |merge_trimmomatic_stats|               |
+----+-----------------------------------------+
| 4. | |bwa_mem_picard_sort_sam|               |
+----+-----------------------------------------+
| 5. | |sambamba_merge_sam_files|              |
+----+-----------------------------------------+
| 6. | |gatk_indel_realigner|                  |
+----+-----------------------------------------+
| 7. | |sambamba_merge_realigned|              |
+----+-----------------------------------------+
| 8. | |sambamba_mark_duplicates|              |
+----+-----------------------------------------+
| 9. | |recalibration|                         |
+----+-----------------------------------------+
| 10.| |conpair_concordance_contamination|     |
+----+-----------------------------------------+
| 11.| |rawmpileup_panel|                      |
+----+-----------------------------------------+
| 12.| |paired_varscan2_panel|                 |
+----+-----------------------------------------+
| 13.| |merge_varscan2_panel|                  |
+----+-----------------------------------------+
| 14.| |preprocess_vcf_panel|                  |
+----+-----------------------------------------+
| 15.| |snp_effect_panel|                      |
+----+-----------------------------------------+
| 16.| |gemini_annotations_panel|              |
+----+-----------------------------------------+
| 17.| |metrics|                               |
+----+-----------------------------------------+
| 18.| |picard_calculate_hs_metrics|           |
+----+-----------------------------------------+
| 19.| |gatk_callable_loci|                    |
+----+-----------------------------------------+
| 20.| |extract_common_snp_freq|               |
+----+-----------------------------------------+
| 21.| |baf_plot|                              |
+----+-----------------------------------------+
| 22.| |rawmpileup|                            |
+----+-----------------------------------------+
| 23.| |paired_varscan2|                       |
+----+-----------------------------------------+
| 24.| |merge_varscan2|                        |
+----+-----------------------------------------+
| 25.| |paired_mutect2|                        |
+----+-----------------------------------------+
| 26.| |merge_mutect2|                         |
+----+-----------------------------------------+
| 27.| |samtools_paired|                       |
+----+-----------------------------------------+
| 28.| |merge_filter_paired_samtools|          |
+----+-----------------------------------------+
| 29.| |vardict_paired|                        |
+----+-----------------------------------------+
| 30.| |merge_filter_paired_vardict|           |
+----+-----------------------------------------+
| 31.| |ensemble_somatic|                      | 
+----+-----------------------------------------+
| 32.| |gatk_variant_annotator_somatic|        |
+----+-----------------------------------------+
| 33.| |merge_gatk_variant_annotator_somatic|  |
+----+-----------------------------------------+
| 34.| |compute_cancer_effects_somatic|        |
+----+-----------------------------------------+
| 35.| |combine_tumor_pairs_somatic|           |
+----+-----------------------------------------+
| 36.| |all_pairs_compute_effects_somatic|     |
+----+-----------------------------------------+
| 37.| |gemini_annotations_somatic|            |
+----+-----------------------------------------+
| 38.| |ensemble_germline_loh|                 |
+----+-----------------------------------------+
| 39.| |gatk_variant_annotator_germline|       |
+----+-----------------------------------------+
| 40.| |merge_gatk_variant_annotator_germline| |
+----+-----------------------------------------+
| 41.| |compute_cancer_effects_germline|       |
+----+-----------------------------------------+
| 42.| |combine_tumor_pairs_germline|          |
+----+-----------------------------------------+
| 43.| |all_pairs_compute_effects_germline|    |
+----+-----------------------------------------+
| 44.| |gemini_annotations_germline|           |
+----+-----------------------------------------+
| 45.| |cram_output|                           |
+----+-----------------------------------------+

----

.. include:: steps_tumor_pair.inc

----

.. _More Information on Tumor Pair Pipeline:

More information
-----------------

For the latest implementation and usage details refer to the latest `pipeline implementation <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/tumor_pair/>`_.

* MuTect2 Tool for calling somatic SNVs and indels via local assembly of haplotypes - `See here <https://software.broadinstitute.org/gatk/documentation/tooldocs/current/org_broadinstitute_hellbender_tools_walkers_mutect_Mutect2.php>`_.

* A `three-caller pipeline <https://www.ncbi.nlm.nih.gov/pmc/articles/PMC5428716/>`_ for variant analysis of cancer whole-exome sequencing data. 


.. Following are the replacement texts used in this file

.. |picard_sam_to_fastq| replace:: `Picard SAM to FastQ`_
.. |trimmomatic| replace:: `Trimmomatic`_
.. |merge_trimmomatic_stats| replace:: `Merge Trimmomatic Stats`_
.. |bwa_mem_picard_sort_sam| replace:: `BWA Picard Sort`_
.. |sambamba_merge_sam_files| replace:: `SamBamba Merge Files`_
.. |gatk_indel_realigner| replace:: `GATK InDel Realigner`_
.. |sambamba_merge_realigned| replace:: `SamBamba Merge Realigned`_
.. |sambamba_mark_duplicates| replace:: `SamBamba Mark Duplicates`_ 
.. |recalibration| replace:: `Recalibration`_
.. |conpair_concordance_contamination| replace:: `Conpair Concorance Contamination`_
.. |rawmpileup_panel| replace:: `Raw Mpileup Panel`_
.. |paired_varscan2_panel| replace:: `Paired VarScan 2`_
.. |merge_varscan2_panel| replace:: `Merge VarScan 2 Panel`_
.. |preprocess_vcf_panel| replace:: `PreProcess VCF Panel`_
.. |snp_effect_panel| replace:: `SNP Effect Panel`_
.. |gemini_annotations_panel| replace:: `Gemini Annotations Panel`_
.. |metrics| replace::  `Metrics`_
.. |picard_calculate_hs_metrics| replace:: `Picard Calculate HS Metrics`_
.. |gatk_callable_loci| replace:: `GATK callable Loci`_
.. |extract_common_snp_freq| replace:: `Extract Common SNP Frequency`_
.. |baf_plot| replace:: `BAF Plot`_
.. |rawmpileup| replace:: `Raw Mpileup`_
.. |paired_varscan2| replace:: `Paired Var Scan 2`_
.. |merge_varscan2| replace:: `Merge Var Scan 2`_
.. |paired_mutect2| replace:: `Paired Mutect2`_
.. |merge_mutect2| replace:: `Merge Mutect2`_
.. |samtools_paired| replace:: `SAM Tools Paired`_
.. |merge_filter_paired_samtools| replace:: `Merge Filter Paired SAM Tools`_
.. |vardict_paired| replace:: `VarDict Paired`_
.. |merge_filter_paired_vardict| replace:: `Merge Filter Paired VarDict`_
.. |ensemble_somatic| replace:: `Ensemble Somatic`_
.. |gatk_variant_annotator_somatic| replace:: `GATK Variant Annotator Somatic`_
.. |merge_gatk_variant_annotator_somatic| replace:: `Merge GATK Variant Annotator Somatic`_
.. |compute_cancer_effects_somatic| replace:: `Compute Cancer Efects Somatic`_
.. |combine_tumor_pairs_somatic| replace:: `Combine Tumor Pairs Somatic`_
.. |all_pairs_compute_effects_somatic| replace:: `All Pairs Compute Effects Somatic`_
.. |gemini_annotations_somatic| replace:: `Gemini Annotations Somatic`_
.. |ensemble_germline_loh| replace:: `Ensemble Germline Loh`_
.. |gatk_variant_annotator_germline| replace:: `GATK Variant Annotator Germline`_
.. |merge_gatk_variant_annotator_germline| replace:: `Merge GATK Variant Annotator Germline`_
.. |compute_cancer_effects_germline| replace:: `Compute Cancer Effects Germline`_
.. |combine_tumor_pairs_germline| replace:: `Combine Tumor Pairs Germline`_
.. |all_pairs_compute_effects_germline| replace:: `All Pairs Compute Effects Germline`_
.. |gemini_annotations_germline| replace:: `Gemini Annotations Germline`_

.. include:: repl_cram_op.inc

.. Following are the links used in the text above

.. _three reasons: https://software.broadinstitute.org/cancer/software/genepattern/modules/docs/ABSOLUTE/1
.. _DREAM3 challenge: https://www.ncbi.nlm.nih.gov/pubmed/25984700
.. _CEPH mixing: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC2816205/
.. _VarScan 2: https://www.ncbi.nlm.nih.gov/pubmed/22300766
.. _BCFTools: http://www.htslib.org/doc/bcftools.html
.. _VarDict: https://www.ncbi.nlm.nih.gov/pubmed/27060149
.. _DELLY: https://www.ncbi.nlm.nih.gov/pubmed/22962449
.. _LUMPY: https://genomebiology.biomedcentral.com/articles/10.1186/gb-2014-15-6-r84
.. _WHAM: https://www.ncbi.nlm.nih.gov/pubmed/26625158
.. _CNVKit: https://www.ncbi.nlm.nih.gov/pubmed/27100738
.. _SvABA: https://www.ncbi.nlm.nih.gov/pubmed/29535149
.. _MetaSV: https://www.ncbi.nlm.nih.gov/pubmed/25861968
.. _dbNSFP: https://www.ncbi.nlm.nih.gov/pubmed/26555599
.. _GATK MuTect2: https://software.broadinstitute.org/gatk/documentation/tooldocs/3.8-0/org_broadinstitute_gatk_tools_walkers_cancer_m2_MuTect2.php
.. _MultiQC: https://multiqc.info/docs/
