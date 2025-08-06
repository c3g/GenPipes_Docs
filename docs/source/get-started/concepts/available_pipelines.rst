:orphan:

.. _docs_available_pipelines:

.. spelling:word-list::

   SARS-COV-2
   COV
   fastpass
   germline_high_cov
   germline
   cov

Available Pipelines
===================

.. list-table:: 
   :header-rows: 1
   :widths: auto
   :class: table-responsive

   * - Genomic Analysis
     - `genpipes <pipeline_cmd>`
     - Flag
   * - `ChIP Seq`_
     - ``chipseq``
     -  
   * - `RNA Seq`_
     - ``rnaseq``
     - 
   * - `RNA Seq Light`_
     - ``rnaseq_light``
     -  
   * - `De novo RNA-Seq`_
     - ``naseq_denovo_assembly``
     -  
   * - `Whole Genome Seq`_
     - ``dnaseq``
     - :code:`default`
   * - `Exome Seq <Whole Genome Seq>`_
     - ``dnaseq``
     - |capture|
   * - `Deep Whole Genome <Whole Genome Seq>`_
     - ``dnaseq``
     - |ini_file|
   * - `Deep Exome Seq <Whole Genome Seq>`_
     - ``dnaseq``
     - |capture|
   * - `Whole Genome Methyl Seq <Methyl WGS>`_
     - ``methylseq``
     - :code:`default`
   * - `Capture Methyl Seq <Methyl WGS>`_
     - ``methylseq``
     - |capture| 
   * - `Cancer Analysis <Whole Genome Seq>`_
     - ``dnaseq``
     - |somatic|
   * - `Whole Chromosome Telomere Assembly <Longread DNA Seq>`_
     - ``longread_dnaseq``
     - |lr_flags|
   * - `Meta Genomics`_
     - ``ampliconseq``
     - 
   * - `SARS-COV-2 <SARS-COV-2 Sequencing>`_
     - ``covseq``
     -  

.. Substitution strings and links

.. |capture| replace:: capture :ref:`BED file<docs_bed_file>` in Readset file or init file 
.. |ini_file| replace:: use relevant ini file and -t germline_high_cov
.. |somatic| replace:: -t somatic_ensemble or -t somatic_sv or -t somatic_fastpass or -t somatic_tumor_only 
.. |lr_flags| replace:: -t nanopore or -t revio 

.. _ChIP Seq: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/chipseq/README.md
.. _RNA Seq: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/rnaseq/README.md
.. _RNA Seq Light: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/rnaseq_light/README.md
.. _De novo RNA-Seq: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/rnaseq_denovo_assembly/README.md
.. _Whole Genome Seq: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/dnaseq/README.md
.. _Exome Seq: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/dnaseq/README.md
.. _DNA High Coverage Seq: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/dnaseq/README.md
.. _Deep Exome Seq: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/dnaseq/README.md
.. _Methyl WGS: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/methylseq/README.md
.. _Capture Methyl WGS: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/methylseq/README.md
.. _Cancer Analysis: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/dnaseq/README.md
.. _Meta Genomics: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/ampliconseq/README.md
.. _SARS-COV-2 Sequencing: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/covseq/README.md
.. _Longread DNA Seq: https://github.com/c3g/GenPipes/blob/main/genpipes/pipelines/longread_dnaseq/README.md
