.. GenPipes Mermaid diagrams documentation master file, created by
   sphinx-quickstart on Tue Jul 20 10:45:53 2021.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. spelling:word-list::

     javascript
     png

Welcome to GenPipes Mermaid Diagrams! 
=====================================

Click the link below to view html generated workflows.

.. toctree::
   :maxdepth: 1
   :caption: GenPipes v6.x Schema
   :name: sec-schema

   schema/legend
   schema/ampliconseq/ampliconseq 
   schema/chipseq/chipseq
   schema/covseq/covseq
   schema/dnaseq/dnaseq
   schema/longread_dnaseq/longread_dnaseq
   schema/methylseq/methylseq
   schema/nanopore_covseq/nanopore_covseq
   schema/rnaseq/rnaseq
   schema/rnaseq_denovo_assembly/rnaseq_denovo_assembly
   schema/rnaseq_light/rnaseq_light

.. toctree::
   :maxdepth: 2
   :caption: GenPipes Diagrams
   :name: sec-diagrams

   diagrams/index

.. tip:: How to Generate Schema?
   
   The process followed for GenPipes Mermaid Schema diagram generation is as follows:

   * Pipeline schema workflow diagrams are coded in this project under source/mmd/pipelines folder
   * Building this project renders them to high quality html diagrams
   * You need to save these as screenshots/png (preferably on a mac for better resolution) and then update them in GenPipes RTD docs folder under GenPipes/docs/source/img/pipelines/mmd section.  These diagrams in png format are then referred to by the GenPipes RTD html docs.
   * Note: This process need to be followed only if pipeline steps change, otherwise the existing previous copy of png in GenPipes RTD sources will be used to generate RTD docs.

   .. note::  Issues with Auto embedding mermaid-sphinx in RTD directly

      As a trial, first process for mermaid integration was to use the extension in RTD docs project itself.  However, there are two issues encountered in that case:

      1. The build and page loading become significantly slower as the html builder and rendering method uses javascript to generate the diagrams.

      2. The resolution of the image and size of larger workflows is too small in auto generated diagrams.

      Hence the process above is used as an alternative until we find other better ways to integrate mermaid workflow code into RTD docs.

.. toctree::
   :maxdepth: 2
   :caption: Schema Archive
   :name: sec-mmd

   deprecated/index    

.. Indices and tables
.. ==================

.. * :ref:`genindex`
.. * :ref:`modindex`
.. * :ref:`search`
