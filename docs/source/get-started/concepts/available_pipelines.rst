:orphan:

.. _docs_available_pipelines:

Available Pipelines
===================

.. table::
   :widths: 5, 10, 2, 20

   +------------------+------------------------------+----------+---------------------------------+
   | Genomic Analysis |       Pipeline               |   Flag   |        More Information         |
   +==================+==============================+==========+=================================+
   | ChIP-Seq         |::                            |          | `ChIP-Seq Manual`_              |
   |                  |                              |          |                                 |
   |                  |    chipseq.py                |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | RNA-Seq          |::                            |          | `RNA-Seq Manual`_               |
   |                  |                              |          |                                 |
   |                  |  rnaseq.py                   |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | De novo RNA-Seq  |::                            |          | `RNA-Seq De Novo Manual`_       |
   |                  |                              |          |                                 |
   |                  |  rnaseq_denovo_assembly.py   |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Whole Genome Seq |::                            |  default | `Whole Genome Seq Manual`_      |
   |                  |                              |          |                                 |
   |                  |   dnaseq.py                  |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Exome Seq        |::                            ||capture| | `Exome Seq Manual`_             |
   |                  |                              |          |                                 |
   |                  |   dnaseq.py                  |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Deep Whole Genome|::                            | default  | `DNA High Coverage Seq Manual`_ |
   |                  |                              |          |                                 |
   |                  |   dnaseq.py                  |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Deep Exome Seq   |::                            | |capture|| `Deep Exome Seq Manual`_        |
   |                  |                              |          |                                 |
   |                  |   dnaseq_high_coverage.py    |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Hi-C Seq         |::                            | -t hic   | `Hi-C Seq Manual`_              |
   |                  |                              |          |                                 |
   |                  |   hicseq.py                  |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Capture Hi-C     |::                            | -t       | `Hi-C Capture Manual`_          |
   |                  |                              | capture  |                                 |
   |                  |   hicseq.py                  |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Whole Genome     |::                            | default  | `Methyl WGS Manual`_            | 
   | Methyl Seq       |                              |          |                                 |
   |                  |   methylseq.py               |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Capture Methyl   |::                            ||capture| | `Capture Methyl WGS Manual`_    |
   | Seq              |                              |          |                                 |  
   |                  |   methylseq.py               |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Cancer Analysis  |::                            |          | `Cancer Analysis Manual`_       |
   |                  |                              |          |                                 |
   |                  |   tumor_pair.py              |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | Meta Genomics    |::                            |          | `Meta Genomics Manual`_         |
   |                  |                              |          |                                 |
   |                  |   ampliconseq.py             |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+
   | PacBio Assembly  |::                            |          | `PacBio Assembly Manual`_       |
   |                  |                              |          |                                 |
   |                  |   pacbio_assembly.py         |          |                                 |
   +------------------+------------------------------+----------+---------------------------------+

.. |capture| replace:: capture :ref:`BED file<docs_bed_file>` in Readset file or init file 

.. _ChIP-Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/chipseq/README.md
.. _RNA-Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/rnaseq/README.md
.. _RNA-Seq De Novo Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/rnaseq_denovo_assembly/README.md
.. _Whole Genome Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq/README.md
.. _Exome Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq/README.md
.. _DNA High Coverage Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq_high_coverage/README.md
.. _Deep Exome Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/dnaseq_high_coverage/README.md
.. _Hi-C Seq Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/hicseq/README.md
.. _Hi-C Capture Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/hicseq/README.md
.. _Methyl WGS Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/methylseq/README.md
.. _Capture Methyl WGS Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/methylseq/README.md
.. _Cancer Analysis Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/tumor_pair/README.md
.. _Meta Genomics Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/ampliconseq/README.md
.. _PacBio Assembly Manual: https://bitbucket.org/mugqic/genpipes/src/master/pipelines/pacbio_assembly/README.md
