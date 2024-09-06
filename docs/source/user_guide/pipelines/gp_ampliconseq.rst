.. _docs_gp_ampliconseq:

.. spelling:: 

      Amplicon
      Amplicons
      amplicon
      amplicons
      seqs 
      metagenomic   

Amplicon Sequencing Pipeline
============================

:bdg-primary:`Version` |genpipes_version|


.. warning::

   Amplicon *QIIME* protocol is **deprecated** from *GenPipes v5.x* onwards. 
   To use this protocol, try `an older version of GenPipes <https://genpipes.readthedocs.io/en/genpipes-v4.6.0/user_guide/pipelines/gp_ampliconseq.html>`_.

.. tab-set:: 

      .. tab-item:: Usage

         .. dropdown:: Command
            :open:

            ::

              genpipes ampliconseq.py [-t dada2] [--genpipes_file GENPIPES_FILE] [options]

         .. dropdown:: Options

            .. include:: opt_ampliconseq.inc
            .. include:: /common/gp_design_opt.inc 
            .. include:: /common/gp_readset_opt.inc 
            .. include:: /common/gp_common_opt.inc 

         .. dropdown:: Example
            :open:

            .. include::  /user_guide/pipelines/example_runs/ampliconseq.inc

            .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

            .. card:: Test Dataset
               :link: docs_testdatasets
               :link-type: ref

               You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

      .. tab-item:: Schema
         :name: ampschema    

         .. dropdown:: DADA2
            :open:

            .. figure:: /img/pipelines/mmd/ampliconseq.dada2.mmd.png
               :align: center
               :alt: dada2 ampseq 
               :width: 70%
               :figwidth: 95%

               Figure: Schema of DADA2 Amplicon Sequencing protocol

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: dada2 ampseq 
               :width: 100%
               :figwidth: 75%


      .. tab-item:: Steps

         +----+--------------------------------+
         |    |   *DADA2*                      |
         +====+================================+
         | 1. | |trimmomatic16S|               |
         +----+--------------------------------+
         | 2. | |merge_trimmomatic_stats16S|   |
         +----+--------------------------------+
         | 3. | |flash_pass1|                  |
         +----+--------------------------------+
         | 4. | |ampliconLengthParser|         |
         +----+--------------------------------+
         | 5. | |flash_pass2|                  |
         +----+--------------------------------+
         | 6. | |merge_flash_stats|            |
         +----+--------------------------------+
         | 7. | |asva|                         |
         +----+--------------------------------+
         | 8. | |run_multiqc|                  | 
         +----+--------------------------------+

         .. card::

            .. include:: steps_ampseq.inc

      .. tab-item:: About

         .. card::

            Amplicon sequencing (ribosomal RNA gene amplification analysis) is a highly targeted metagenomic pipeline used to analyze genetic variation in specific genomic regions. Amplicons are Polymerase Chain Reaction (PCR) products and the ultra-deep sequencing allows for efficient variant identification and characterization.

            **Uses of Amplicon sequencing**

            #. Diagnostic microbiology utilizes amplicon-based profiling that allows to sequence selected amplicons such as regions encoding 16S rRNA that are used for species identification. 

            #. Discovery of rare somatic mutations in complex samples such as tumors mixed with germline DNA.
            
            GenPipes supports the `DADA2`_ Amplicon sequencing protocol for recovering single-nucleotide resolved Amplicon Sequence Variants (ASVs) from the Amplicon data.

            See :ref:`ampschema` tab for the pipeline workflow. Check the `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/ampliconseq/README.md>`_ file for implementation details.

            **References**

            * `Amplicon sequencing techniques <https://sapac.illumina.com/techniques/sequencing/dna-sequencing/targeted-resequencing/amplicon-sequencing.html>`_

            * `Amplicon Sequencing Primer <http://apc.ucc.ie/pdf_old/Amplicon%20Sequencing.pdf>`_

            * `High-throughput amplicon sequencing <https://www.biorxiv.org/content/10.1101/392332v2>`_.

            * `Trimmomatic - flexible trimming <https://academic.oup.com/bioinformatics/article/30/15/2114/2390096>`_.

.. The following are html links used in this text

.. _DADA2 Pipeline: https://benjjneb.github.io/dada2/tutorial.html

.. The following are replacement texts used in this file

.. |trimmomatic16S| replace:: `Trimmomatic16S Step`_
.. |merge_trimmomatic_stats16S| replace:: `Merge Trimmomatic Stats`_
.. |flash_pass1| replace:: `Flash Pass 1`_
.. |ampliconLengthParser| replace:: `Amplicon Length Parser`_
.. |flash_pass2| replace:: `Flash Pass 2`_
.. |merge_flash_stats| replace:: `Merge Flash Stats`_
.. |asva| replace:: `ASVA`_
.. |run_multiqc| replace:: `Run MultiQC`_
