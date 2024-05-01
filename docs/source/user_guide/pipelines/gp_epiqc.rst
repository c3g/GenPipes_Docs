.. _docs_gp_epiqc:

.. spelling::

     heatmap
     epiQC
     ChromImpute
     epigenomic 
     bigwiginfo
     epiGeEC
     epiGenomic
     Correlator

EpiQC Pipeline
===============

:bdg-primary:`Version` |genpipes_version|

.. tab-set:: 
      .. tab-item:: About

         .. card::

            GenPipes introduces epiQC as a brand new pipeline with the sole focus of quality control for `BigWig`_ signal files. These `BigWig`_ signal files are generated as part of :ref:`ChIP-Sequencing Pipeline<docs_gp_chipseq>`. It is important to determine the quality of bases before using them for subsequent analysis as low quality bases can bias the downstream analysis such as SNP and SV calling.

            .. note::
       
                 At present, comparing large reference database with user samples is not supported.
  
            After the completion of computing metrics, the epiQC pipeline executes four consecutive report steps to create the `epiQC Final Report`_ of the pipeline with quality control labels.

            This brand new epiQC pipeline can be used for pre-validation of samples, in order to assess the usability of a dataset in any given study, even in the absence of the original raw reads files. This presents a huge advantage, for instance, in the case of human epigenomic datasets available in the `IHEC Datasets`_, as signal tracks are made publicly available, while raw data files are stored in controlled access repositories.

            You can test this pipeline with ChIP-Seq samples from the `IHEC Portal <https://epigenomesportal.ca/ihec/grid.html?assembly=4&build=2018-10>`_. 

            .. warning: 
   
                 Please **note** that GenPipes epiQC Pipeline allows you to use the same readset file as the one used in ChIP-seq pipeline **without any modifications**. However, make sure that the readset file is located in the same folder as the ChIP-Seq output. This is because the input files for epiQC pipeline are located based on the readset file path.

            For more information on epiQC pipeline implementation and design, refer to the `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/epiqc/README.md>`_ file.

      .. tab-item:: Usage

         .. dropdown:: Command

            .. code::

               epiqc.py [-h] [--help] [-c CONFIG [CONFIG ...]] [-s STEPS]            
                    [-o OUTPUT_DIR] [-j {pbs,batch,daemon,slurm}] [-f]         
                    [--no-json] [--report] [--clean]
                    [-l {debug,info,warning,error,critical}] [--sanity-check]
                    [--container {wrapper, singularity} <IMAGE PATH>]
                    [-r READSETS] [-v]
                    [--genpipes_file GENPIPES_FILE]

         .. dropdown:: Example Run

            Use the following commands to execute epiQC pipeline:

            .. include:: /user_guide/pipelines/example_runs/epiqc.inc

            .. include:: /user_guide/pipelines/notes/scriptfile_deprecation.inc

            .. card:: Test Dataset
               :link: docs_testdatasets
               :link-type: ref

               You can download the test dataset for this pipeline :ref:`here<docs_testdatasets>`. 

         .. dropdown:: Options

            .. include:: /common/gp_readset_opt.inc
            .. include:: /common/gp_common_opt.inc

      .. tab-item:: Schema
         :name: epiqcschema

         .. figure:: /img/pipelines/mmd/epiqc.mmd.png
            :align: center
            :alt: epiqc schema
            :width: 100%
            :figwidth: 95%

         Figure: Schema of epiQC pipeline

         .. figure:: /img/pipelines/mmd/legend.mmd.png
            :align: center
            :alt: dada2 ampseq
            :width: 100%
            :figwidth: 75%

      .. tab-item:: Steps

          +----+----------------------------------------+
          |    |  **epiQC Pipeline Steps**              |
          +====+========================================+
          | 1. | |bigwiginfo|                           |
          +----+-------------------------+--------------+
          | 2. | |chrom_impute|          | |bw_to_bedg| |
          |    |                         +--------------+
          |    |                         | |ci_preproc| |
          |    |                         +--------------+
          |    |                         | |ci_conv|    |
          |    |                         +--------------+
          |    |                         | |ci_cgd|     |
          |    |                         +--------------+
          |    |                         | |ci_gen_td|  |
          |    |                         +--------------+
          |    |                         | |ci_train|   |
          |    |                         +--------------+
          |    |                         | |ci_apply|   |
          |    |                         +--------------+
          |    |                         | |ci_eval|    |
          +----+-------------------------+--------------+
          | 3. | |signal_to_noise|                      |
          +----+----------------------------------------+
          | 4. | |epigeec|                              |
          +----+-------------------------+--------------+
          | 5. | |epiqc_report|          | |bwi_report| |
          |    |                         +--------------+
          |    |                         | |ci_report|  |
          |    |                         +--------------+
          |    |                         | |s2n_report| |
          |    |                         +--------------+
          |    |                         | |epigeec_r|  |
          |    |                         +--------------+
          |    |                         | |final_rep|  |
          +----+-------------------------+--------------+

        .. card::

           .. include:: steps_epiqc.inc

      .. tab-item:: Details

         .. card::

            The epiQC is a quality control pipeline for signal files (`BigWig`_) generated during :ref:`ChIP-Sequencing Pipeline<docs_gp_chipseq>` execution. The epiQC pipeline performs a series of calculations on these `BigWig`_ files to assess the quality of ChIP-Seq data. Low quality bases can bias various genomic analysis processes such as SNP and SV calling. The epiQC Pipeline helps in determining the quality of inputs.

            As part of epiQC pipeline, four different metrics are computed from a single `BigWig`_ file. 

            #. `BigWigInfo`_ tool prints out information about a BigWig file. This tool is used to perform the initial quality check on signal tracks.
            #. `ChromImpute`_ processing step imputes signal tracks for the given chromosome (currently only chr1 is supported, but it is sufficient to accurately detect issues in signal files).
            #.  `Signal to Noise`_ step of the epiQC pipeline processes the signal to noise measurement by calculating the proportion of signal in top bins. 
            #. This is followed by heatmap creation from the correlation matrix obtained via the epiGenomic Efficient Correlator (`epiGeEC`_) tool by comparing only the user samples.

.. _More Information on epiQC Pipeline:

More information
-----------------

For the latest implementation and usage details refer to epiQC Pipeline implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/epiqc/README.md>`_.

* `Epigenomics Quality Control`_.

* `epiGeEC`_ Tool.

* About `ChromImpute`_.

.. The following are replacement texts used in this file

.. |bigwiginfo| replace:: `BigWigInfo Processing`_
.. |chrom_impute| replace:: `ChromImpute Processing`_
.. |bw_to_bedg| replace:: `BigWig to BED Graph`_
.. |ci_preproc| replace:: `ChromImpute Preprocessing`_
.. |ci_conv| replace:: `ChromImpute Convert`_
.. |ci_cgd| replace:: `ChromImpute Compute Global Distance`_
.. |ci_gen_td| replace:: `ChromImpute Generate Train Data`_
.. |ci_train| replace:: `ChromImpute Train`_
.. |ci_apply| replace:: `ChromImpute Apply`_
.. |ci_eval| replace:: `ChromImpute Evaluation`_
.. |signal_to_noise| replace:: `Signal To Noise`_
.. |epigeec| replace:: `epiGeEC Processing`_
.. |epiqc_report| replace:: `epiQC Report`_
.. |bwi_report| replace:: `BigWigInfo Report`_
.. |ci_report| replace:: `ChromImpute Report`_
.. |s2n_report| replace:: `Signal to Noise Report`_
.. |epigeec_r| replace:: `epiGeEC Report`_
.. |final_rep| replace:: `epiQC Final Report`_

.. The following are links and references used in this file

.. _BigWig: http://genome.ucsc.edu/goldenPath/help/bigWig.html
.. _BigWigInfo: https://genome.ucsc.edu/goldenPath/help/bigWig.html
.. _ChromImpute: https://ernstlab.biolchem.ucla.edu/ChromImpute/
.. _epiGeEC: https://pubmed.ncbi.nlm.nih.gov/30052804/
.. _IHEC Datasets: https://epigenomesportal.ca/ihec/
.. _Epigenomics Quality Control: https://www.biorxiv.org/content/10.1101/2020.12.14.421529v2.full.pdf
