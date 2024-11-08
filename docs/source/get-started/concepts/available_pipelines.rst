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

.. table::
   :widths: 5, 10, 2, 20

   +------------------+------------------------------+----------+---------------------------------+
   | Genomic Analysis |       Pipeline               |   Flag   |        More Information         |
   +==================+==============================+==========+=================================+
   | ChIP-Seq         |::                            |          | `ChIP-Seq Manual`_              |
   |                  |                              |          |                                 |
   |                  |  chipseq                     |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | RNA-Seq          |::                            |          | `RNA-Seq Manual`_               |
   |                  |                              |          |                                 |
   |                  |  rnaseq                      |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | RNA-Seq(Light)   |::                            |          | `RNA-Seq-Light-Manual`_         |
   |                  |                              |          |                                 |
   |                  |  rnaseq_light                |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | De novo RNA-Seq  |::                            |          | `RNA-Seq De Novo Manual`_       |
   |                  |                              |          |                                 |
   |                  |  rnaseq_denovo_assembly      |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Whole Genome Seq |::                            |  default | `Whole Genome Seq Manual`_      |
   |                  |                              |          |                                 |
   |                  |   dnaseq                     |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Exome Seq        |::                            ||capture| | `Whole Genome Seq Manual`_      |
   |                  |                              |          |                                 |
   |                  |   dnaseq                     |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Deep Whole Genome|::                            ||ini_file|| `Whole Genome Seq Manual`_      |
   |                  |                              |          |                                 |
   |                  |   dnaseq                     |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Deep Exome Seq   |::                            | |capture|| `Whole Genome Seq Manual`_      |
   |                  |                              |          |                                 |
   |                  |   dnaseq                     |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Hi-C Seq         |::                            | -t hic   | `Hi-C Seq Manual`_              |
   |                  |                              |          |                                 |
   |                  |   hicseq                     |          | (Deprecated from GenPipes v5.x) |
   +------------------+------------------------------+----------+---------------------------------+
   | Capture Hi-C     |::                            | -t       | `Hi-C Capture Manual`_          |
   |                  |                              | capture  |                                 |
   |                  |   hicseq                     |          | (Deprecated from GenPipes v5.x) |
   +------------------+------------------------------+----------+---------------------------------+
   | Whole Genome     |::                            | default  | `Methyl WGS Manual`_            | 
   | Methyl Seq       |                              |          |                                 |
   |                  |   methylseq                  |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Capture Methyl   |::                            ||capture| | `Methyl WGS Manual`_            |
   | Seq              |                              |          |                                 |  
   |                  |   methylseq                  |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Cancer Analysis  |::                            ||somatic| | `Whole Genome Seq Manual`_      |
   |                  |                              |          |                                 |
   |                  |   dnaseq                     |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Meta Genomics    |::                            |          | `Meta Genomics Manual`_         |
   |                  |                              |          |                                 |
   |                  |   ampliconseq                |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | SARS-CoV-2       |::                            |          | `SARS-COV-2 Sequencing`_        |
   |                  |                              |          |                                 |
   |                  |   covseq                     |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+

.. |capture| replace:: capture :ref:`BED file<docs_bed_file>` in Readset file or init file 
.. |ini_file| replace:: use relevant ini file and -t germline_high_cov
.. |somatic| replace:: -t somatic_ensemble or -t somatic_sv or -t somatic_fastpass or -t somatic_tumor_only  

.. _ChIP-Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/chipseq/README.md
.. _RNA-Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/rnaseq/README.md
.. _RNA-Seq-Light-Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/rnaseq_light/README.md
.. _RNA-Seq De Novo Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/rnaseq_denovo_assembly/README.md
.. _Whole Genome Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq/README.md
.. _Exome Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq/README.md
.. _DNA High Coverage Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq/README.md
.. _Deep Exome Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq/README.md
.. _Hi-C Seq Manual: https://bitbucket.org/mugqic/genpipes/src/4.6.1/pipelines/hicseq//README.md
.. _Hi-C Capture Manual: https://bitbucket.org/mugqic/genpipes/src/4.6.1/pipelines/hicseq/README.md
.. _Methyl WGS Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/methylseq/README.md
.. _Capture Methyl WGS Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/methylseq/README.md
.. _Cancer Analysis Manual: https://bitbucket.org/mugqic/genpipes/src/4.6.1/pipelines/dna_seq/README.md
.. _Meta Genomics Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/ampliconseq/README.md
.. _SARS-COV-2 Sequencing: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/covseq/README.md
