:orphan:

.. _doc_casava_sheet:

Casava Sheet
============

Casava Sheet is input data used in :ref:`Illumina Run Processing Pipeline<docs_gp_illumina_run_proc>`. It is a .csv format file with the following columns:

* ``SampleID``
* ``FCID``
* ``SampleRef``
* ``Index``
* ``Description``
* ``Control``
* ``Recipe``
* ``Operator``
* ``SampleProject``

Here is a sample of Casava Sheet:

::

  FCID,Lane,SampleID,SampleRef,Index,Description,Control,Recipe,Operator,SampleProject
  H84WNADXX,1,sample1_MPS0001,,TAAGGCGA-AGAGTAGA,,N,,,nanuq
  H84WNADXX,1,sample47_MPS0047,,GTAGAGGA-CTAAGCCT,,N,,,nanuq

For more details, you can refer to `Casava User Guide <https://manualzz.com/doc/o/gzeeq/casava-v1.8.2-user-guide--15011196-b--introduction>`_.
