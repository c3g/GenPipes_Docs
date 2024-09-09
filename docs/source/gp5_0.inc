This is a major release of GenPipes.

Key Modifications**** 

* Genpipes 5.0 distribution is now based on Python packaging. Earlier it was Python module based.
* It supports Python v3.11.1 and above. 
* To run GenPipes pipelines, the command format has changed.

  - **Old Format** 

    ::
    
      <pipeline name>.py [options] -g genpipes_cmd.sh
      bash genpipes_cmd.sh

  - **New Format** 
  
    ::

      genpipes <pipeline name>.py [options] -g genpipes_cmd.sh
      bash genpipes_cmd.sh`

* The :ref:`RNA Sequencing (De Novo)<docs_gp_rnaseq_denovo>` pipeline has been updated in this release (to do what?)
* The :ref:`EpiQC pipeline<docs_gp_epiqc>`, :ref:`HiC-Seq pipeline<docs_gp_hicseq>`, and :ref:`AmpliconSeq qiime protocol<docs_gp_ampliconseq>` have been deprecated.
* The DNA-Seq high coverage pipeline has been merged into :ref:`DNA-Seq<docs_gp_dnaseq>` along with the TumorPair pipeline. 
* Markdown style reports have been deprecated for all pipelines in v5.0 and replaced with MultiQC reports.
* The :ref:`Methylseq pipeline<docs_methylation>` has a new protocol option using gemBS (TBD if this will be in the initial release)