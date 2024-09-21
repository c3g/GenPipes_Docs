This is a major release of GenPipes.

**What has changed in 5.0?**

* GenPipes 5.0 distribution is now based on Python packaging. Earlier it was Python module based.
* It supports Python v3.11.1 and above. 
* To run GenPipes pipelines, the command syntax has changed.

  - **Old Format** 

    ::
    
      user@beluga % <pipeline name>.py [options] -g genpipes_cmd.sh
      user@beluga % bash genpipes_cmd.sh

  - **New Format** 
  
    ::

      user@beluga % genpipes <pipeline name> [options] -g genpipes_cmd.sh
      user@beluga % bash genpipes_cmd.sh

* The :ref:`RNA Sequencing (De Novo)<docs_gp_rnaseq_denovo>` pipeline has been updated in this release
* The :ref:`EpiQC pipeline<docs_gp_epiqc>`, :ref:`HiC-Seq pipeline<docs_gp_hicseq>`, and :ref:`AmpliconSeq qiime protocol<docs_gp_ampliconseq>` have been deprecated.
* The DNA-Seq high coverage pipeline and the TumorPair pipeline have been merged into a single workflow :ref:`DNA-Seq<docs_gp_dnaseq>`.
* The :ref:`Methylseq pipeline<docs_methylation>` has a new protocol option using the gemBS aligner instead of Bismark.
* Genome build GRCh38 (human) is now the default reference genome for all pipelines, but other versions or species can be selected via config files, as before.
* Markdown style reports have been deprecated for all pipelines in v5.0 and replaced entirely with MultiQC reports.
