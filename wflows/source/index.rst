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

The process followed for GenPipes RTD documentation is as follows:

* Pipeline workflow diagrams are coded in this project
* Building this project renders them to high quality html diagrams
* You need to save these as screenshots/png (preferably on a mac for better resolution) and then update them in GenPipes RTD docs folder under GenPipes/docs/source/img/pipelines/mmd area.  These diagrams in png format are then referred to by the GenPipes RTD html docs.
* Note: This process need to be followed only if pipeline steps change, otherwise the existing previous copy of png in GenPipes RTD sources will be used to generate RTD docs.

.. note::  Auto embedding mermaid-sphinx in RTD directly

     As a trial, first process for mermaid integration was to use the extension in RTD docs project itself.  However, there are two issues encountered in that case:

     1. The build and page loading become significantly slower as the html builder and rendering method uses javascript to generate the diagrams.

     2. The resolution of the image and size of larger workflows is too small in auto generated diagrams.

     Hence the process above is used as an alternative until we find other better ways to integrate mermaid workflow code into RTD docs.
     
.. toctree::
   :maxdepth: 2
   :caption: Mermaid Diagrams

   mmd/mmd_fig
   mmd/diagram_fig

.. Indices and tables
.. ==================

.. * :ref:`genindex`
.. * :ref:`modindex`
.. * :ref:`search`
