.. caution::

    *Users of GenPipes v4.x or prior releases must carefully read the usage changes listed below.*

**What has Changed?**

1. Effective v5.0 onward, the GenPipes distribution is based on Python packaging and not on Python modules as before. Also Python 2.7 users must upgrade to Python v3.11.1 or higher to use v5.x GenPipes pipelines.
2. The latest GenPipes v6.0 supports *only* Python **v3.12.0** and above. 
3. To run any GenPipes pipelines, follow the new command syntax *(effective GenPipes v5.x onward)*:

  - **Old Format** 

    ::
    
      user@beluga % <pipeline name>.py [options] -g genpipes_cmd.sh
      user@beluga % bash genpipes_cmd.sh

  - **New Format** 
  
    ::

      user@beluga % genpipes <pipeline name> [options] -g genpipes_cmd.sh
      user@beluga % bash genpipes_cmd.sh

4. When using **GenPipes deployed on the Digital Research Alliance Canada servers such as beluga**, a new variable ‘GENPIPES_INIS’ is introduced for streamlining access to the config files in the `genpipes` commands. In the future, 'MUGQIC_PIPELINES_HOME' will be deprecated.

  - **Before** 

    :: 
    
      $MUGQIC_PIPELINES_HOME/pipelines/<pipeline>/<pipeline>.base.ini

  - **Now** 

    :: 
      
      $GENPIPES_INIS/<pipeline>/<pipeline>.base.ini 

  .. note::

        Please note that the old variable, 'MUGQIC_PIPELINES_HOME' will still be accessible and is still in use for instructions on how to deploy GenPipes locally, in the cloud, or in a container.

5. A new :ref:`Long Read DNA Sequencing pipeline<docs_gp_longread_dnaseq>` is now available in v6.0 that supports two protocols:

   * Nanopore
   * Revio 

6. The `Nanopore pipeline <https://genpipes.readthedocs.io/en/genpipes-v5.1.0/user_guide/pipelines/gp_nanopore.html>`_ available in v5.0 and earlier releases is no longer supported. The same functionality is now available as one of the supported protocols in the new :ref:`Long Read DNA Sequencing pipeline<docs_gp_longread_dnaseq>`.

7. The :ref:`RNA Sequencing (De Novo)<docs_gp_rnaseq_denovo>` pipeline has been updated in v5.0 release.

8. The :ref:`EpiQC pipeline<docs_gp_epiqc>`, :ref:`HiC-Seq pipeline<docs_gp_hicseq>`, and :ref:`AmpliconSeq qiime protocol<docs_gp_ampliconseq>` have been deprecated starting v5.0 onward.

9. The DNA-Seq high coverage pipeline and the TumorPair pipeline have been merged into a single workflow :ref:`DNA-Seq<docs_gp_dnaseq>`.

10. The :ref:`Methylseq pipeline<docs_methylation>` has a new protocol option using the gemBS aligner in addition to Bismark.

11. Genome build GRCh38 (human) is now the default reference genome for all pipelines, but other versions or species can be selected via config files, as before.

12. Markdown style reports have been deprecated for all pipelines starting v5.0 onward and replaced entirely with MultiQC reports.
