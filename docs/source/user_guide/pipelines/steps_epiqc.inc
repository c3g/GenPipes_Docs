.. _docs_steps_epiqc:

.. spelling::

     bedgraph
     inputinfo
     hdf
     epigenome
     chromsizes
     bp

Step Details
-------------

Following are the various steps that are part of GenPipes epiQC pipeline:

.. _BigWigInfo Processing:

BigWigInfo Processing
^^^^^^^^^^^^^^^^^^^^^

This step takes BigWig file as input and runs the `BigWigInfo Tool <https://bioconda-recipes-demo.readthedocs.io/en/docs/recipes/ucsc-bigwiginfo/README.html>`_ to inspect signal tracks and identify obvious issues that may impact the quality of the ChIP-Seq data. BigWigInfo is capable of identifying various obvious issues such as missing chromosomes and insufficient track coverage. These are usually symptoms of improperly generated tracks.

If the user has specified BigWig files in the readset file under BIGIWIG column, they will be utilized by the tool. Otherwise, the user is required to process files using ChIp-Seq pipeline to generate these BigWig files that are required as inputs for epiQC Pipeline. In this case, the paths for BigWig files are reconstructed based on the ChIP-Seq readset file and will be used subsequently.

.. warning:: Location of readset file

    The readset file should be in the same folder as the ChIP-Seq output.

.. _ChromImpute Processing:

ChromImpute Processing
^^^^^^^^^^^^^^^^^^^^^^

`ChromImpute`_ is a Java software for large-scale systematic epigenome imputation.  ChromImpute takes an existing compendium of signal tracks (`BedGraph Files`_)  and uses it for:

* Predicting signal tracks for mark-sample combinations that are not experimentally mapped.
* Generates a potentially more robust version of data sets that have been mapped experimentally. 

ChromImpute bases its predictions on features from signal tracks of other marks that have been mapped in the target sample and the target mark in other samples with these features combined using an ensemble of regression trees. For better results, usage of multiple histone marks from one sample is recommended.

.. note::  Support for GRCh38, GRCh37

   The current epiQC Pipeline implementation supports only those signal tracks  that are mapped to GRCh38 during ChromImpute analysis. GRCh37 will be added in the future. For better results, usage of multiple histone marks from one sample is recommended.

ChromImpute processing step comprises of several sub-steps that are invoked internally in the pipeline. 

.. contents:: ChromImpute Sub-steps 
      :local:

----

Refer to the section below for the sub-step details:

.. _BigWig to BED Graph:

BigWig to BED Graph
~~~~~~~~~~~~~~~~~~~

In this sub-step of ChromImpute Processing, BigWig file is the input to the `BigWigtoBEDGraph Tool <https://bioconda-recipes-demo.readthedocs.io/en/docs/recipes/ucsc-bigwigtobedgraph/README.html>`_ for converting BigWig files to `BedGraph Files`_. These BedGraph files are used in other ChromImpute steps subsequently.

.. _ChromImpute Preprocessing:

ChromImpute Preprocessing
~~~~~~~~~~~~~~~~~~~~~~~~~

This sub-step of ChromImpute Processing is performed to create ChromImpute directories, chromosome sizes file, inputinfo file with IHEC and user samples. Finally, this step also links the converted IHEC `BedGraph Files`_ to user directory. In order to run the ChromImpute, it is required that the inputinfo and chromsizes file are located in the imputation directory. 

.. note:: 

     The chromsizes and inputinfo files are created dynamically when the user runs the epiQC pipeline. It is not necessary to submit jobs to create them.
    
     Although the current implementation supports only GRCh38 chr1 for ChromImpute analysis, it is sufficient to accurately evaluate the signal quality. Chromosome name can be specified in the `ChromImpute Preprocessing`_ section of the epiQC pipeline .ini file.

.. _ChromImpute Convert:

ChromImpute Convert
~~~~~~~~~~~~~~~~~~~

The ChromImpute convert sub-step is performed to convert each unique mark and sample combination signal tracks (`BedGraph Files`_) in the user dataset into binned (25 bp) signal resolution tracks. Since the stored, converted files are binned using 25bps, changing the resolution value specified in the epiQC pipeline .ini file is not recommended for ChromImpute analysis.

.. note:: 

     If you encounter an 'index out of bound exception', check whether your reference genome version of the BedGraph file is similar to chromosome_sizes_file inside the imputation folder.

The ChromImpute convert sub-step takes as input files:

#. BigWig files from `BigWig to BED Graph`_ sub-step earlier.
#. Chromosome sizes file
#. inputinfo file

.. _ChromImpute Compute Global Distance:

ChromImpute Compute Global Distance
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This sub-step is used to compute the global distance based on correlation for each mark in each sample with the same mark in all other samples in inputinfo file. It creates a file for each mark, in each sample containing a ranked list of the globally nearest samples.

This sub-step takes as input the following files:

#. Converted signal tracks from :ref:`ChromImpute Convert sub-step<ChromImpute Convert>`
#. Converted and linked signal tracks from IHEC data portal
#. Chromosome sizes file
#. inputinfo file

.. _ChromImpute Generate Train Data:

ChromImpute Generate Train Data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This step is performed to generate a set of training data instances taking directory of converted data and global distances.

This step takes as input the following files:

#. Converted signal tracks from `ChromImpute Convert`_.
#. Converted and linked signal tracks from IHEC data portal
#. Chromosome sizes file
#. inputinfo file
#. global distance files from `ChromImpute Compute Global Distance`_ sub-step.

.. _ChromImpute Train:

ChromImpute Train
~~~~~~~~~~~~~~~~~

This step is used to train regression trees based on the feature data produced by `ChromImpute Generate Train Data`_.

This step takes as input files:

#. Predictor data produced by `ChromImpute Generate Train Data`_ sub-step.
#. Chromosome sizes file
#. inputinfo file

.. _ ChromImpute Apply:

ChromImpute Apply
~~~~~~~~~~~~~~~~~

This step is used to apply the predictors generated in the Train command to generate the imputed data. A job is created for each sample and mark given in the dataset.

This sub-step takes as input files:

#. Converted signal tracks from `ChromImpute Convert`_
#. Converted and linked signal tracks from IHEC data portal
#. Chromosome sizes file
#. inputinfo file
#. global distance files from `ChromImpute Compute Global Distance`_
#. Predictor data produced by `ChromImpute Generate Train Data`_

.. _ChromImpute Evaluation:

ChromImpute Evaluation
~~~~~~~~~~~~~~~~~~~~~~

The final sub-step of `ChromImpute Processing`_ involves comparing the agreement between an observed and imputed data set. A job is created for every sample-mark given in the dataset. percent1 percent2 Gives lower and upper percentages to use in evaluation. Default values for percent1 is 1% and percent2 is 5%

This step takes as input files:

#. Converted signal tracks from `ChromImpute Convert`_
#. Imputed signal tracks from `ChromImpute Apply`_

.. _Signal To Noise:

Signal To Noise
^^^^^^^^^^^^^^^

Binned signal resolution tracks from `ChromImpute Convert`_ step is used to determine the percentage of the whole file signal that was located in the top percent1 and percent2 of the bins. The default percentages are 5% and 10% and the resulted output is a tsv file.

This step takes converted signal tracks from `ChromImpute Convert`_ as input file.

.. _epiGeEC Processing:

epiGeEC Processing
^^^^^^^^^^^^^^^^^^

This step is performed to run the `EpiGeEC pipeline <https://bitbucket.org/labjacquespe/epigeec/src/master/>`_.  EpiGeEC pipeline consists of three sub-steps:

#. Bigwig files are first converted to the hdf5 format.
#. Next, it filters or selects the provided regions as a BED file (include or exclude) [optional]. The user can specify the options and the BED file path in the epiQC pipeline .ini file. Otherwise, this step will be skipped
#. Finally, the correlation matrix is computed.

.. _epiQC Report:

epiQC Report
^^^^^^^^^^^^

epiQC report comprises of five sub-steps including four independent steps to generate individual report files for each metric that is computed and one step to combine all of them to generate a final epiQC report file. A user can independently run each sub step but in order to generate final report, there is a dependency on the reports generated from `BigWigInfo Processing`_, `ChromImpute Processing`_  and `EpiGeEC Processing`_ steps.

This final report is a TSV file with the decision of each signal track [i.e whether the sample has passed based on all the metrics involved in various reports or are there any alerts that the user need to be concerned about.]

.. contents:: epiQC Report Sub-steps
     :local:

----

.. BigWigInfo Report:

BigWigInfo Report
~~~~~~~~~~~~~~~~~

This step is performed to generate report on bigwiginfo result

.. ChromImpute Report:

ChromImpute Report
~~~~~~~~~~~~~~~~~~~

This step is performed to generate a report comparing ChromImpute
imputed signal track and input signal track (in bedgraph format).

.. _Signal to Noise Report:

Signal to Noise Report
~~~~~~~~~~~~~~~~~~~~~~

This step is performed to generate report on signal_to_noise result

.. _epiGeEC Report:

epiGeEC Report
~~~~~~~~~~~~~~~

This step is performed to generate a heatmap from EpiGeEC results

.. _epiQC Final Report:

epiQC Final Report
~~~~~~~~~~~~~~~~~~

Once all metrics have been obtained, they are gathered in a TSV formatted report and compared to predetermined thresholds. A column holding epiQC's verdict for a signal track is also included, using these thresholds evaluations. 

The following metrics threshold were used:

.. note::

    An Alert will be generated even if there is an issue with one of the several quality metrics.

-  **High Level Alert:**

   -  Chromosome count is under 23

-  **Medium Level Alert:**

   -  Whole genome bases covered under 25,000,000
   -  Signal in top 10% bins below 30%
   -  ChromImpute OBSERVED_1.0_IMPUTE_5.0 below 30%

-  **Low Level Alert:**

   -  Whole genome bases covered under 75,000,000
   -  Signal in top 5% bins below 20%
   -  ChromImpute BOTH_1.0 below 20%

Refer to the figure below for insights related to probability of error and threshold levels:

.. figure:: /img/pipelines/epiqc_base_qc.png
   :align: center
   :alt: epiqc error prob
   :width: 75%
   :figwidth: 95%

   Figure: Base Quality Threshold and error probability


.. note::

     In the current implementation of the epiQC pipeline, the epiGeEC metric is not used for the final quality decision.

.. Following are the links used as references above

.. _BedGraph Files: http://genome.ucsc.edu/goldenPath/help/bedgraph.html
