.. _docs_gp_nanopore_cov:

.. spelling:word-list::

   artic
   Conda
   Minimap
   Nanopore
   Nanopolish
   basecall
   basecalled
   basecaller
   basecalling
   bp
   bcftools
   coronavirus
   epigenomics
   mRNA
   metagenomic
   nCoV
   nanopolish
   nt
   transcriptonomics
   minimap 

Nanopore CoVSeQ Pipeline 
========================

:bdg-primary:`Version` |genpipes_version|

.. tab-set:: 

      .. tab-item:: Usage

         .. dropdown:: Command
            :open:

            .. code::

               genpipes nanopore_covseq [options] [--genpipes_file GENPIPES_FILE.sh]
               bash GENPIPES_FILE.sh

         .. dropdown:: Options

            .. include:: opt_nanopore_cov.inc
            .. include:: /common/gp_readset_opt.inc
            .. include:: /common/gp_common_opt.inc

         .. dropdown:: Example

            .. include::  /user_guide/pipelines/example_runs/nanopore_covseq.inc
            .. include::  /user_guide/pipelines/example_runs/nanopore-readset.inc
            .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

            .. card:: Test Dataset
               :link: docs_testdatasets
               :link-type: ref

               You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

      .. tab-item:: Schema
         :name: nanocovschema 

         .. dropdown:: Default

            Figure below shows the schema of the Nanopore CoVSeQ ARTIC SARS-CoV2 sequencing protocol. You can also refer to the latest `pipeline implementation <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/nanopore_covseq/>`_  


            .. figure:: /img/pipelines/mmd/nanopore_covseq_df.mmd.png
               :align: center
               :alt: nanopore covseq (-t default) schema

               Figure: Schema of Nanopore CoVSeQ (Default)  Sequencing protocol

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: dada2 ampseq 
               :width: 100%
               :figwidth: 75%

         .. dropdown:: Basecalling

            .. figure:: /img/pipelines/mmd/nanopore_covseq_bc.mmd.png
               :align: center
               :alt: nanopore covseq (-t basecalling) schema

               Figure: Schema of Nanopore CoVSeQ (Basecalling)  Sequencing protocol

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: dada2 ampseq 
               :width: 100%
               :figwidth: 75%
   
      .. tab-item:: Steps

         +----+--------------------------------+--------------------------------+
         |    |  *Default Nanopore CoVSeQ*     | *Basecalling Nanopore CoVSeQ*  |
         +====+================================+================================+
         | 1. | |host_reads_removal|           |  |guppy_basecall|              |
         +----+--------------------------------+--------------------------------+
         | 2. | |kraken_analysis|              |  |guppy_demultiplex|           |
         +----+--------------------------------+--------------------------------+
         | 3. | |artic_nanopolish|             |  |pycoqc|                      |
         +----+--------------------------------+--------------------------------+
         | 4. | |wub_metrics|                  |  |host_reads_removal|          |
         +----+--------------------------------+--------------------------------+
         | 5. | |covseq_metrics|               |  |kraken_analysis|             |
         +----+--------------------------------+--------------------------------+
         | 6. | |snpeff_annotate|              |  |artic_nanopolish|            |
         +----+--------------------------------+--------------------------------+
         | 7. | |quast_consensus_metrics|      |  |wub_metrics|                 |
         +----+--------------------------------+--------------------------------+
         | 8. | |rename_consensus_header|      |  |covseq_metrics|              |
         +----+--------------------------------+--------------------------------+
         | 9. | |prepare_report|               |  |snpeff_annotate|             |
         +----+--------------------------------+--------------------------------+
         | 10.|                                |  |quast_consensus_metrics|     |
         +----+--------------------------------+--------------------------------+
         | 11.|                                |  |rename_consensus_header|     |
         +----+--------------------------------+--------------------------------+
         | 12.|                                |  |prepare_report|              |
         +----+--------------------------------+--------------------------------+

         .. card::

         .. include:: steps_nanopore_covseq.inc

      .. tab-item:: About

         .. card::

            The Nanopore CoVSeQ pipeline is used to analyze long reads produced by the Oxford Nanopore Technologies (ONT) sequencers. 

            The SOP for Nanopore data is based on the `ARTIC SARS-CoV2 protocol <https://artic.network/ncov-2019>`_, Version 4 / 4.1 (`V4.1 <https://github.com/artic-network/artic-ncov2019/tree/master/primer_schemes/nCoV-2019/V4.1>`_), using nanopolish. This protocol is closely followed in GenPipes Nanopore sequencing pipeline with majority of changes related to technical adaptation of the protocol to be able to run in a High Performance Computing (HPC) environment. In such environments, Conda is not advisable.

            Key steps in this pipeline include `basecalling with Guppy`_, demultiplexing, read filtering and consensus sequencing. Basecalling with Guppy happens only if the ```-t basecalling``` option is selected.

            If basecalling protocol option is selected through the -t command line option, the Nanopore CoVSeQ pipeline will do `basecalling with Guppy`_ (GPU) and demultiplexing. After basecalling, the pipeline performs de-hosting, for all the samples, followed by running the ARTIC-Nanopolish wrapper which performs alignment to the SARS-CoV2 reference (using `minimap2 <https://github.com/lh3/minimap2>`_), variant calling (using `Nanopolish software <https://github.com/jts/nanopolish>`_). The Nanopolish software performs signal-level analysis of Oxford Nanopore sequencing data. After Nanopolish processing, the pipeline performs consensus generation through artic_mask and bcftools consensus steps. Lastly, custom scripts and ncov_tools are run to report on quality metrics for Nanopore CoVSeQ GenPipes Sequencing Pipeline.

            Details of structure and contents of the `Nanopore readset file are available here <https://bitbucket.org/mugqic/genpipes/src/master/README.md#markdown-header-nanopore>`_.

            See See :ref:`nanocovschema` tab for the pipeline workflow. For more details, refer to the `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/nanopore/README.md>`_ file.

            **References**

            * `nCoV-2019 novel coronavirus bioinformatics protocol`_
            * `Phylogenetic Analysis of nCoV-2019 genome`_ using publicly shared genome sequences with datasets from NCBI or GISAID.
            * `Tiling Amplicon sequencing and downstream bioinformatics analysis`_

.. include:: /user_guide/pipelines/notes/artic_version.inc

.. The following are replacement texts used in this file

.. |guppy_basecall| replace:: `Guppy Basecall`_
.. |guppy_demultiplex| replace:: `Guppy Demultiplex`_
.. |pycoqc| replace:: `pycoQC`_
.. |host_reads_removal| replace:: `Host Reads Removal`_
.. |kraken_analysis| replace:: `Kraken Analysis`_
.. |artic_nanopolish| replace:: `ARTIC Nanopolish`_
.. |wub_metrics| replace:: `Wub Metrics`_
.. |covseq_metrics| replace:: `CoVSeQ Metrics`_
.. |snpeff_annotate| replace:: `SnpEff Annotate`_
.. |quast_consensus_metrics| replace:: `Quast Consensus Metrics`_
.. |rename_consensus_header| replace:: `Rename Consensus Header`_
.. |prepare_report| replace:: `Prepare Report`_

.. The following are links and references used in this file

.. _Nanopore ARTIC-Nanopolish protocol: https://artic.network/ncov-2019
.. _Phylogenetic Analysis of nCoV-2019 genome: https://virological.org/t/phylodynamic-analysis-176-genomes-6-mar-2020/356
.. _nCoV-2019 novel coronavirus bioinformatics protocol: https://artic.network/ncov-2019/ncov2019-bioinformatics-sop.html
.. _Tiling Amplicon sequencing and downstream bioinformatics analysis: https://artic.network/quick-guide-to-tiling-amplicon-sequencing-bioinformatics.html
.. _basecalling with Guppy: https://timkahlke.github.io/LongRead_tutorials/BS_G.html
.. _Wub Package: https://github.com/nanoporetech/wub
.. _Guppy: https://timkahlke.github.io/LongRead_tutorials/BS_G.html
