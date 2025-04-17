.. _doc_cvmfs_genomes:

GenPipes Genome resources
=========================

C3G, in partnership with the `Digital Research Alliance of Canada <https://alliancecan.ca/en>`_, formerly Compute Canada, maintains `several genomes <https://computationalgenomics.ca/cvmfs-genome/>`_. These genomes are available on multiple servers such as Beluga, Niagara, Cedar and Graham. 

In addition to the FASTA sequence, many genomes include aligner indices and annotation files.

To access these genomes, you need to add the following lines to your .bashrc file.

.. code-block:: bash

    ## GenPipes/MUGQIC genomes and modules
    export MUGQIC_INSTALL_HOME=/cvmfs/soft.mugqic/CentOS6

To explore the available genomes, you can type:

.. code-block:: bash

    ls $MUGQIC_INSTALL_HOME/genomes/species/
