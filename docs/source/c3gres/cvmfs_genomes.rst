.. _doc_cvmfs_genomes:

GenPipes Genome resources
=========================

C3G, in partnership with Compute Canada, maintains several genomes that are available on several HPC centres including Beluga, Cedar and others. In addition to the fasta sequence, many genomes include aligner indices and annotation files.

To access these genomes, you need to add the following lines to your .bashrc file.

.. code-block:: bash

    ## GenPipes/MUGQIC genomes and modules
    export MUGQIC_INSTALL_HOME=/cvmfs/soft.mugqic/CentOS6

To explore the available genomes, you can type:

.. code-block:: bash

    ls $MUGQIC_INSTALL_HOME/genomes/species/



Available Genomes
-----------------

Human
`````
Species: Homo_sapiens
Available builds: GRCh38, GRCh37, hg19

Mouse
`````
species: Mus_musculus
Available builds: GRCm38, mm10, mm9, NCBIM37

Rat
```
Species: Rattus_norvegicus
Available builds: rn5, Rnor_5.0, Rnor_6.0

Monkey
``````
Species: Macaca_mulatta
Available builds: MMUL_1

Chimpanzee
``````````
Species: Pan_troglodytes
Available builds: panTro4, CHIMP2.1.4

Baboon
``````
Species: Papio_anubis
Available builds: PapAnu2.0

Dog
```
Species: Canis_familiaris
Available builds: CanFam3.1

Cow
```
Species: Bos_taurus
Available builds: UMD3.1

Chicken
```````
Species: Gallus_gallus
Available builds: Galgal4

Fly
```
Species: Drosophila_melanogaster
Available builds: BDGP5

C. Elegans
``````````
Species: Caenorhabditis_elegans
Available builds: WBcel235

Yeast
`````
Species: Saccharomyces_cerevisiae
Available builds: R64-1-1
Species: Schizosaccharomyces_pombe
Available builds: ASM294v2

Bacteria
````````
Species: Escherichia_coli_str_k_12_substr_dh10b
Available builds: ASM1942v1
Species: pseudomonas_aeruginosa_pa14
Available builds: Pseu_aeru_PA14_V1
Species: Pseudomonas_aeruginosa_UCBPP_PA14
Available builds: ASM1462v1

Plants
``````
Species: Arabidopsis_thaliana
Available builds: TAIR10
