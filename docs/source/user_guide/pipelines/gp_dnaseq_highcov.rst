.. _docs_gp_dnaseq_highcov:

.. spelling:: 

      samplespell      
 
DNA Sequencing (High Coverage) Pipeline
=======================================


.. contents:: :local:

----

Introduction
------------


See `More Information`_ section below for details. 

----

Version
-------
::

  3.1.4

For latest pipeline.....

----

Usage
-----

::


**Optional Arguments**

::


----
 
Example Run
-----------

TBD - Link below needs to be updated - not listed in current README.md file


::

   TBD

---- 

Pipeline Schema
---------------

Figure below shows the schema of the DNA Sequencing (High Coverage) sequencing protocol - QIIME type. You can refer to the latest `pipeline implementation <https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/https://bitbucket.org/mugqic/genpipes/src/master/resources/workflows/GenPipes_ampliconseq.png>`_ to download a high resolution image of the same.

.. figure:: /img/pipelines/ampseq.png
   :align: center
   :alt: schema

   Figure: Schema of QIIME Amplicon Sequencing protocol

----

Pipeline Steps
--------------

The table below shows various steps that constitute the Hi-C and Hi-C capture genomic analysis pipelines.

+----+--------------------------------+---------------------------------+
|    |  *QIIME sequencing Steps*      |   *DADA2 sequencing Steps*      |
+====+================================+=================================+
| 1. | |samplestepsequencing|         | |samplestepsequencing|          |
+----+--------------------------------+---------------------------------+

----

.. include:: steps_dnaseq_highcov.inc

----

.. _More Information:

More information
-----------------
For the latest implementation and usage details refer to DNA Sequencing implementation `README.md <https://bitbucket.org/mugqic/genpipes/src/master/pipelines/hicseq/README.md>`_ file.

* `Amplicon sequencing techniques <https://sapac.illumina.com/techniques/sequencing/dna-sequencing/targeted-resequencing/amplicon-sequencing.html>`_

----

.. The following are html links used in this text

.. _DADA2 Pipeline: https://benjjneb.github.io/dada2/tutorial.html

.. The following are replacement texts used in this file

.. |samplestepsequencing| replace:: `Sample Step`_
