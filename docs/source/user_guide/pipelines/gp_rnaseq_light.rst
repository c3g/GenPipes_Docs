.. _docs_gp_rnaseqlight:

.. spelling::

     html
     Kallisto
  
RNA Sequencing (Light) Pipeline 
================================

:bdg-primary:`Version` |genpipes_version|

.. tab-set:: 

      .. tab-item:: Usage

         .. dropdown:: Command
            :open:

            .. code::

                 genpipes rnaseq_light [options] [--genpipes_file GENPIPES_FILE.sh]
                 bash GENPIPES_FILE.sh

         .. dropdown:: Options

            .. include:: /common/gp_design_opt.inc
            .. include:: /common/gp_readset_opt.inc
            .. include:: /common/gp_common_opt.inc

         .. dropdown:: Example
                 
            .. include::  /user_guide/pipelines/example_runs/rnaseq_light.inc

            .. tip::

                 Replace ``beluga.ini`` file name in the command above with the appropriate *clustername.ini* file located in the ``$MUGQIC_PIPELINES_HOME/pipelines/common_ini`` folder, depending upon the cluster where you are executing the pipeline.  For e.g., ``narval.ini``, ``cedar.ini``, ``graham.ini`` or ``narval.ini``.

            .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

            .. card:: Test Dataset
               :link: docs_testdatasets
               :link-type: ref

               You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`.  

      .. tab-item:: Schema
         :name: rnalightschema  

            .. figure:: /img/pipelines/mmd/rnaseq.light.mmd.png
               :align: center
               :alt: rnaseq light schema
               :width: 100%
               :figwidth: 95%

               Figure: Schema of RNA Sequencing (Light) pipeline 

            .. figure:: /img/pipelines/mmd/legend.mmd.png
               :align: center
               :alt: dada2 ampseq
               :width: 100%
               :figwidth: 75%

      .. tab-item:: Steps

         +----+--------------------------------------+
         |    | *RNA Sequence Light Steps*           |
         +====+======================================+
         | 1. | |picard-sam-to-fastq|                |
         +----+--------------------------------------+
         | 2. | |trimmomatic|                        |
         +----+--------------------------------------+
         | 3. | |merge-trimmomatic-stats|            |
         +----+--------------------------------------+
         | 4. | |kallisto|                           |
         +----+--------------------------------------+
         | 5. | |kallisto-count-matrix|              |
         +----+--------------------------------------+
         | 6. | |gq-seq-utils-exploratory|           |
         +----+--------------------------------------+
         | 7. | |sleuth-differential-expression|     |
         +----+--------------------------------------+
         | 8. | |multiqc|                            |
         +----+--------------------------------------+

         .. card::

            .. include:: steps_rnaseqlight.inc

      .. tab-item:: About

         .. card::

            This is a lightweight RNA Sequencing Expression analysis pipeline based on `Kallisto technique`_. It is used for quick Quality Control (QC) in gene sequencing studies.

            The central computational problem in RNA-seq remains the efficient and accurate assignment of short sequencing reads to the transcripts they originated from and using this information to infer gene expressions. Conventionally, read assignment is carried out by aligning sequencing reads to a reference genome, such that relative gene expressions can be inferred by the alignments at annotated gene loci. These alignment-based methods are conceptually simple, but the read-alignment step can be time-consuming and computationally intensive.

            Alignment-free RNA quantification tools have significantly increased the speed of RNA-seq analysis. The alignment-free pipelines are orders of magnitude faster than alignment-based pipelines, and they work by breaking sequencing reads into k-mers and then performing fast matches to pre-indexed transcript databases. To achieve fast transcript quantification without compromising quantification accuracy, different sophisticated algorithms were implemented in addition to k- mer counting, such as pseudo-alignments by `Kallisto technique`_ and quasi-mapping along with GC and sequence-bias corrections using `Salmon`_.

            RNA Sequencing Light is a lightweight pipeline that performs quick QC and removes a major computation bottleneck in RNA Sequence analysis. Kallisto is two orders of magnitude faster than previous approaches and achieves similar accuracy. Kallisto pseudo-aligns reads to a reference, producing a list of transcripts that are compatible with each read while avoiding the alignment of individual bases. In the latest release of GenPipes, calls to `kallisto quant` are now aggregated by sample instead of by the readset for better performance.

            See :ref:`rnalightschema` tab for pipeline workflow. Check the `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/rnaseq_light/README.md>`_ file for implementation details.

            **References**

            * Kallisto, a new `ultra-fast RNA Sequencing technique`_
            * Limitations of alignment-free tools in `RNA sequencing quantification`_

.. The following are replacement texts used in this file

.. |picard-sam-to-fastq| replace:: `Picard SAM to FASTQ`_
.. |trimmomatic| replace:: `Trimmomatic`_
.. |merge-trimmomatic-stats| replace:: `Merge Trimmomatic Stats`_
.. |kallisto| replace:: `Kallisto`_
.. |kallisto-count-matrix| replace:: `Kallisto Count Matrix`_
.. |gq-seq-utils-exploratory| replace:: `GQ Seq Utils Exploratory`_
.. |sleuth-differential-expression| replace:: `Sleuth Differential Expression`_
.. |multiqc| replace:: `MultiQC`_

.. Following are the links used in the text above

.. _Kallisto technique: https://www.nature.com/articles/nbt.3519
.. _ultra-fast RNA Sequencing technique: https://altanalyze.readthedocs.io/en/latest/Kallisto-Splice/
.. _RNA sequencing quantification: https://www.biorxiv.org/content/biorxiv/early/2018/01/11/246967.full.pdf
.. _Salmon: https://www.ncbi.nlm.nih.gov/pubmed/28263959
.. _Trimmomatic Tool: http://www.usadellab.org/cms/index.php?page=trimmomatic
.. _Sleuth: http://pachterlab.github.io/sleuth/