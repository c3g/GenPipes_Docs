.. admonition:: Using v4.x?
    :class: danger

    You are recommended to:

      * Review the changes in v5.x and v6.x (*See tabs*)
      * Migrate to using the latest GenPipes v6.x
        
**What has Changed?**

.. tab-set:: 

      .. tab-item:: **v6.x**

         Following changes are effective from GenPipes release v6.x onward: 

          - Requires **Python v3.12.0** or higher. 
          - A new environment variable ‘GENPIPES_INIS’ is introduced for streamlining access to the config files in the `genpipes` commands. In the future, 'MUGQIC_PIPELINES_HOME' will be deprecated. This is applicable when using **GenPipes deployed on the DRAC servers** such as |key_ccdb_server_name|. 

              - **Before** 

                :: 
                
                  $MUGQIC_PIPELINES_HOME/pipelines/<pipeline>/<pipeline>.base.ini

              - **Now** 

                :: 
                  
                  $GENPIPES_INIS/<pipeline>/<pipeline>.base.ini 

            .. admonition:: Note
                :class: note

                  Please note that the old variable, 'MUGQIC_PIPELINES_HOME' will still be accessible and is still in use for instructions on how to deploy GenPipes locally, in the cloud, or in a container.

          - A new :ref:`Long Read DNA Sequencing pipeline<docs_gp_longread_dnaseq>` is now available in v6.0 that supports three protocols:

              * Nanopore
              * Nanopore Paired Somatic
              * Revio 

      .. tab-item:: **v5.x**

         Following changes are effective from GenPipes release v5.x onward: 

          - Starting with v5.0, GenPipes uses **Python packaging** and *no longer relies on Python modules*. 
          - If you were using Python **v2.7**, you **must upgrade to Python v3.11.1**.
          - To run any GenPipes pipelines, use the **new command syntax:**

            .. include:: /common/commands/change_format_5.inc

          - :ref:`RNA Sequencing (De Novo)<docs_gp_rnaseq_denovo>` pipeline has been updated in v5.0 release.
          - :ref:`EpiQC pipeline<docs_gp_epiqc>`, :ref:`HiC-Seq pipeline<docs_gp_hicseq>`, and :ref:`AmpliconSeq qiime   protocol<docs_gp_ampliconseq>` have been deprecated starting v5.0 onward.
          - The DNA-Seq high coverage pipeline and the TumorPair pipeline have been merged into a single workflow :ref:`DNA-Seq<docs_gp_dnaseq>`.

          - The :ref:`Methylseq pipeline<docs_methylation>` has a new protocol option using the gemBS aligner in addition to Bismark.

          - Genome build GRCh38 (human) is now the default reference genome for all pipelines, but other versions or species can be selected via config files, as before.

          - Markdown style reports have been deprecated for all pipelines starting v5.0 onward and replaced entirely with MultiQC reports.