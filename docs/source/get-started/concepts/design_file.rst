:orphan:

.. _docs_design_file:

Design File
===========

Certain pipelines where samples are compared against other samples, like chipseq.py and rnaseq.py, require a design file that describes which samples are to be compared. 


.. note::

        **Why does GenPipes need a Design File?**

        A Design file is another file that accompanies some of our pipelines, where sample comparison is part of the pipeline. Unlike the configuration file and the Readset file, the Design file is not required by every pipeline. To check whether the pipeline you are interested in requires a Design file and to understand the format of the file, read the specific help pages for your pipeline of interest.


Format of Design File
======================

The Design File is a tab-separated plain text file with one line per sample and the following columns:

+-------------------+-----------------------------------------------------------+
| *Field*           |  *Contents*                                               |
+===================+===========================================================+
| **Sample**        | first column; must contain letters A-Z, numbers 0-9,      |
|                   | hyphens (-) or underscores (_) only; the sample name must |
|                   | match a sample name in the readset file; mandatory.       |
+-------------------+-----------------------------------------------------------+
| **Contrast**      | each of the following columns defines an experimental     |
|                   | design contrast; the column name defines the contrast     |
|                   | name, and the following values represent the sample group |
|                   | membership for this contrast:                             |
|                   |                                                           |
|                   | **'0'** or ": the sample does not belong to any group     |
|                   |                                                           |
|                   | **'1'**: the sample belongs to the control group          |
|                   |                                                           |
|                   | **'2'**: the sample belongs to the treatment test case    |
|                   |          group.                                           |
+-------------------+-----------------------------------------------------------+

Example of a Design File
========================

::

            Sample Contrast_AB Contrast_AC
            sampleA 1 1
            sampleB 2 0
            sampleC 0 2
            sampleD 0 0

where Contrast_AB compares treatment sampleB to control sampleA, while Contrast_AC compares sampleC to sampleA.

.. note::

        You can add several contrasts per design file.
