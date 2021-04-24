.. _docs_gp_covseq:

.. spelling::

     des
     du
     sociaux
     santé
     Ministere

CoV Sequencing Pipeline
========================

CoV Sequencing Pipeline can be used to effectively amplify and detect SARS-CoV-2 RNA in samples such that it enables reliable results from even low copy numbers. It helps to assay clean characteristic target peaks of defined sizes, allowing for direct detection of the presence of viral genome from the Coronaviridae family.  Sequencing provides confirmation for the species as well as phylogenetic information for the specific strain discrimination.

The design of this pipeline is directed against SARS-CoV-2 and other coronaviruses as well. By amplifying conserved regions of other coronaviruses in a sample, along with mutation tolerant panels, it can provide additional insights and pinpoint sequence variability, thus offering a powerful solution for more in-depth research and surveillance of the rapidly evolving virus.

CoVSeQ pipeline is designed as part of the `partnership for Québec SARS-CoV-2`_ sequencing. It is funded by the CanCOGeN initiative through Genome Canada and from the Ministere de la santé et des services sociaux du Québec. For more details, see `CoVSeQ website`_.

.. contents:: :local:

----

Introduction
------------

TBD some high level introduction about Pipeline steps et all and how it is different from other available CoV Seq pipelines (if any). Refer to Ed and Hector.

----

Version
-------

|genpipes_version|

For the latest implementation and usage details refer to DNA Sequencing implementation `README file <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/covseq/README.md>`_ file.

----

Usage
-----

::

  covseq.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]
            [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]
            [--no-json] [--report] [--clean]
            [-l {debug,info,warning,error,critical}] [--sanity-check]
            [--container {docker, singularity} {<CONTAINER PATH>, <CONTAINER NAME>}]
            [-t {mugqic,mpileup,light}] [-r READSETS] [-v]

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
  -r READSETS, --readsets READSETS
                        readset file
  -v, --version         show the version information and exit

----

Example Run
-----------

Use the following commands to execute CoVSeq sequencing pipeline:

::

  covseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/covseq/covseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/covseq/covseq.beluga.ini > covseqCommands_mugqic.sh

  bash covseqCommands_mugqic.sh

You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.

.. note::

     Check with Paul/Hector if this pipeline requires a test dataset and whether one is available. Then update/edit the test dataset link above accordingly.
 
----

Pipeline Schema
---------------

Figure below shows the schema of the CovSeq sequencing protocol. You can refer to the latest `pipeline implementation <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/covseq/>`_  

.. figure:: /img/pipelines/covseq.png
   :align: center
   :alt: covseq schema

   Figure: Schema of CoVSeq Sequencing protocol

----

Pipeline Steps
--------------

The table below shows various steps that constitute the CoVSeq genomic analysis pipeline.

+----+--------------------------------+
|    |  *SARS-CoV-2 Sequencing Steps* |
+====+================================+
| 1. | |host_reads_removal|           |
+----+--------------------------------+
| 2. | |kraken_analysis|              |
+----+--------------------------------+
| 3. | |cutadapt|                     |
+----+--------------------------------+
| 4. | |mapping_bwa_mem_sambamba|     |
+----+--------------------------------+
| 5. | |sambamba_merge_sam_files|     |
+----+--------------------------------+
| 6. | |sambamba_filtering|           |
+----+--------------------------------+
| 7. | |ivar_trim_primers|            |
+----+--------------------------------+
| 8. | |covseq_metrics|               |
+----+--------------------------------+
| 9. | |ivar_calling|                 |
+----+--------------------------------+
| 10.| |snpeff_annotate|              |
+----+--------------------------------+
| 11.| |ivar_create_consensus|        |
+----+--------------------------------+
| 12.| |quast_consensus_metrics|      |
+----+--------------------------------+
| 13.| |rename_consensus_header|      |
+----+--------------------------------+

----

.. include:: steps_covseq.inc

----

.. _More Information on CoVSeq Sequencing:

More information
-----------------

For the latest implementation and usage details refer to CoVSeq Pipeline implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/covseq/README.md>`_.

* `CoVSeq Cost Effective Workflow`_

* `CoVSeq Genome Analysis and Visualization`_

.. The following are replacement texts used in this file

.. |host_reads_removal| replace:: `Host Reads Removal`_
.. |kraken_analysis| replace:: `Kraken Analysis`_
.. |cutadapt| replace:: `Cutadapt`_
.. |mapping_bwa_mem_sambamba| replace:: `Mapping BWA Mem Sambamba`_
.. |sambamba_merge_sam_files| replace:: `Sambamba Merge SAM Files`_
.. |sambamba_filtering| replace:: `Sambamba Filtering`_
.. |ivar_trim_primers| replace:: `iVar Trim Primers`_
.. |covseq_metrics| replace:: `CoVSeq Metrics`_
.. |ivar_calling| replace:: `iVar Calling`_
.. |snpeff_annotate| replace:: `SNPEff Annotate`_
.. |ivar_create_consensus| replace:: `iVar Create Consensus`_
.. |quast_consensus_metrics| replace:: `QUAST Consensus Metrics`_
.. |rename_consensus_header| replace:: `Rename Consensus Header`_

.. The following are links and references used in this file

.. _CoVSeQ website: https://covseq.ca
.. _partnership for Québec SARS-CoV-2: https://c3g.github.io/covseq_McGill/SARS_CoV2_Sequencing/about.html
.. _Paragon CleanPlex Product Documents: https://www.paragongenomics.com/customer-support/product_documents/ 
.. _CoVSeq Cost Effective Workflow: https://www.researchgate.net/publication/348593724_COVseq_is_a_cost-effective_workflow_for_mass-scale_SARS-CoV-2_genomic_surveillance
.. _CoVSeq Genome Analysis and Visualization: https://www.researchgate.net/publication/341117511_CoV-Seq_SARS-CoV-2_Genome_Analysis_and_Visualization
