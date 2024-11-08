.. _docs_dep_gp_local:


.. spelling:word-list::

   modulefiles
   Ensembl
   GRCh

Deploying GenPipes locally in your server 
==========================================

This document covers details on how to deploy GenPipes locally on a bare metal or virtual server. If you wish to install GenPipes locally in a container, please refer to :ref:`GenPipes in a container<docs_dep_gp_container>` section of deployment guide.

For more details on other available options to deploy and access GenPipes you may refer to :ref:`GenPipes Deployment Options Page<docs_dep_options>`.

.. _docs_download_gp_src:

Step 1: Download latest GenPipes sources and install with pip
----------------------------------------------------------------

First of all, visit GenPipes `Download Page <https://bitbucket.org/mugqic/genpipes/downloads/>`_ and get a copy of the latest stable release software.  To fetch the most recent version of GenPipes, you may use the following command:

::

  git clone git@bitbucket.org:mugqic/genpipes.git
  cd <bitbucket_repo>
  pip install .

Step 2: Setup environment variables
-----------------------------------

Add the following lines in your your *$HOME/.bash_profile*: to set MUGQIC_PIPELINES_HOME to your local copy path. For example,

::

  export MUGQIC_PIPELINES_HOME=/path/to/your/local/genpipes
  export GENPIPES_INIS=$MUGQIC_PIPELINES_HOME/genpipes/pipelines

.. _accessing_sw_mod_genomes_local_dp:

Step 3: Accessing software modules and genomes needed for GenPipe
-----------------------------------------------------------------

GenPipes was formerly known as MUGQIC Pipelines. Genomic analysis executed using these pipelines requires `genomes <https://www.computationalgenomics.ca/cvmfs-genomes/>`_ and `software modules <https://docs.python.org/3/tutorial/modules.html>`_. You need to load the software modules in your shell environment. To do so, set the environment variable **MUGQIC_INSTALL_HOME** to the directory where you want to install those resources in your **$HOME/.bash_profile** as follows:

::

  ## MUGQIC genomes and modules

  export MUGQIC_INSTALL_HOME=/path/to/your/local/mugqic_resources
  module use $MUGQIC_INSTALL_HOME/modulefiles

**Installing available modules**

Software tools and associated modules must be installed in $MUGQIC_INSTALL_HOME/software/ and $MUGQIC_INSTALL_HOME/modulefiles/.  Default software/module installation scripts are already available in $MUGQIC_PIPELINES_HOME/resources/modules/. 

**Install new modules**

To install a new module or new software tool and associated modules semi-automatically, use the following instructions:

::

  cp $MUGQIC_PIPELINES_HOME/resources/modules/MODULE_INSTALL_TEMPLATE.sh $MUGQIC_PIPELINES_HOME/resources/modules/<my_software>.sh

Follow the instructions in the file $MUGQIC_PIPELINES_HOME/resources/modules/<my_software>.sh and modify it accordingly.  Next you need to run the following command with **No arguments**. By default, it will download and extract the remote software archive, build the software and create the associated module, all in $MUGQIC_INSTALL_HOME_DEV if it is set.

:: 

  $MUGQIC_PIPELINES_HOME/resources/modules/<my_software>.sh

If everything executes OK with no error, you are ready to install the `my_software` module in production. Use the command:

::

  $MUGQIC_PIPELINES_HOME/resources/modules/<my_software>.sh MUGQIC_INSTALL_HOME

.. note::

   Please note there is no $ before MUGQIC_INSTALL_HOME specified as argument above!.

Next, you need to check if the module is successfully installed and available for use by executing the following command:

::
  
  module avail 2>&1 | grep mugqic/<my_software>/<version>

This completes the software module setup for GenPipes execution. Next you need to make sure all required reference genomes are available in your local deployment. Refer to the next section if you wish to install additional genomes.

.. _ref_installing_genomes:

**Installing genomes**

Reference genomes and annotations must be installed in the following directory:

::

  $MUGQIC_INSTALL_HOME/genomes/

Default genome installation scripts are already available locally in the following directory:

:: 
 
  $MUGQIC_PIPELINES_HOME/resources/genomes/

To install all of the available genomes that are bundled with GenPipes package, use the following script:

$MUGQIC_PIPELINES_HOME/resources/genomes/install_all_genomes.sh

All species related files are in the following directory:

::

  $MUGQIC_INSTALL_HOME/genomes/species/<species_scientific_name>.<assembly>/

For example, *Homo Sapiens* assembly *GRCh37* genome directory hierarchy is as follows:

::

  $MUGQIC_INSTALL_HOME/genomes/species/Homo_sapiens.GRCh37/
  ├── annotations/
  │   ├── gtf_tophat_index/
  │   ├── Homo_sapiens.GRCh37.dbSNP142.vcf.gz
  │   ├── Homo_sapiens.GRCh37.dbSNP142.vcf.gz.tbi
  │   ├── Homo_sapiens.GRCh37.Ensembl75.geneid2Symbol.tsv
  │   ├── Homo_sapiens.GRCh37.Ensembl75.genes.length.tsv
  │   ├── Homo_sapiens.GRCh37.Ensembl75.genes.tsv
  │   ├── Homo_sapiens.GRCh37.Ensembl75.GO.tsv
  │   ├── Homo_sapiens.GRCh37.Ensembl75.gtf
  │   ├── Homo_sapiens.GRCh37.Ensembl75.ncrna.fa
  │   ├── Homo_sapiens.GRCh37.Ensembl75.rrna.fa
  │   ├── Homo_sapiens.GRCh37.Ensembl75.transcript_id.gtf
  │   ├── Homo_sapiens.GRCh37.Ensembl75.vcf.gz
  │   ├── ncrna_bwa_index/
  │   └── rrna_bwa_index/
  ├── downloads/
  │   ├── ftp.1000genomes.ebi.ac.uk/
  │   ├── ftp.ensembl.org/
  │   └── ftp.ncbi.nih.gov/
  ├── genome/
  │   ├── bowtie2_index/
  │   ├── bwa_index/
  │   ├── Homo_sapiens.GRCh37.dict
  │   ├── Homo_sapiens.GRCh37.fa
  │   ├── Homo_sapiens.GRCh37.fa.fai
  │   └── star_index/
  ├── Homo_sapiens.GRCh37.ini
  └── log/

The assembly name is the one used by the download source. For e.g. "GRCh37" is used for `Ensembl <http://www.ensembl.org/>`_.

Each species directory contains a ".ini" file such as:

::

  <scientific_name>.<assembly>.ini

Among other things, this ".ini" file lists the assembly synonyms. In case of "hg19", the contents of Homo_sapiens.GRCh37.ini are as shown below:

::

  [DEFAULT]
  scientific_name=Homo_sapiens
  common_name=Human
  assembly=GRCh37
  assembly_synonyms=hg19
  source=Ensembl
  version=75
  dbsnp_version=142

**Install a new Genome**

New genomes and annotations can be installed semi-automatically from `Ensembl <http://www.ensembl.org/>`_ (vertebrate species), `Ensemble Genomes`_ (other species) or `UCSC`_ (genome and indexes only; no annotations).

*Example - how to set up genomes for Chimpanzee:*

1. Retrieve the species scientific name on `Ensemble Genomes`_ or `UCSC`_ :

::

  Pan troglodytes

2. Retrieve the assembly name:
   
   - Ensembl: "CHIMP2.1.4"
   - UCSC: "panTro4"

3. Retrieve the source version:

   - Ensembl: "78"
   - UCSC: unfortunately, UCSC does not have version numbers. Use `panTro4.2bit <http://hgdownload.soe.ucsc.edu/goldenPath/panTro4/bigZips/>`_ date formatted as "YYYY-MM-DD": "2012-01-09" 

4. Next, copy the template file to a new file name using the scientific name. 

::

  cp $MUGQIC_PIPELINES_HOME/resources/genomes/GENOME_INSTALL_TEMPLATE.sh $MUGQIC_PIPELINES_HOME/resources/genomes/<scientific_name>.<assembly>.sh

For example, in case of Ensembl, use the following command:

::

  cp $MUGQIC_PIPELINES_HOME/resources/genomes/GENOME_INSTALL_TEMPLATE.sh $MUGQIC_PIPELINES_HOME/resources/genomes/Pan_troglodytes.CHIMP2.1.4.sh

In case of genomes from UCSC, use the following command to copy the genome install instructions:

::

  cp $MUGQIC_PIPELINES_HOME/resources/genomes/GENOME_INSTALL_TEMPLATE.sh $MUGQIC_PIPELINES_HOME/resources/genomes/Pan_troglodytes.panTro4.sh

5. Next, you need to modify the following file:

::

  $MUGQIC_PIPELINES_HOME/resources/genomes/<scientific_name>.<assembly>.sh

Please note that ASSEMBLY_SYNONYMS can be left empty but if you know that 2 assemblies
are identical apart from chr sequence prefixes, document it.

Example below shows the modifications for Ensembl:

::

  SPECIES=Pan_troglodytes   # With "_"; no space!
  COMMON_NAME=Chimpanzee
  ASSEMBLY=CHIMP2.1.4
  ASSEMBLY_SYNONYMS=panTro4
  SOURCE=Ensembl
  VERSION=78

Example below shows the modifications for UCSC:

::

  SPECIES=Pan_troglodytes   # With "_"; no space!
  COMMON_NAME=Chimpanzee
  ASSEMBLY=panTro4
  ASSEMBLY_SYNONYMS=CHIMP2.1.4
  SOURCE=UCSC
  VERSION=2012-01-09

6. Now you can run the following command to install the genome in $MUGQIC_INSTALL_HOME_DEV (by default). This will download and install genomes, indexes and, for Ensembl only, annotations (GTF, VCF, etc.).

::

  bash $MUGQIC_PIPELINES_HOME/resources/genomes/<scientific_name>.<assembly>.sh

**Admin-only**
To install it in $MUGQIC_INSTALL_HOME, run the following command:

::

  bash $MUGQIC_PIPELINES_HOME/resources/genomes/<scientific_name>.<assembly>.sh MUGQIC_INSTALL_HOME

7. **Admin-only** If the new genome has been installed in $MUGQIC_INSTALL_HOME_DEV, to deploy in $MUGQIC_INSTALL_HOME you can use the following command:

::

  rsync -vca --no-o --no-g --no-p --size-only -I -O --ignore-times $MUGQIC_INSTALL_HOME_DEV/genomes/species/<scientific_name>.<assembly> $MUGQIC_INSTALL_HOME/genomes/species/

8. Lastly, add the newly created ".ini" file to the genome configuration files for further use in subsequent genomic analysis pipeline runs by the following command:

::

  cp $MUGQIC_INSTALL_HOME/genomes/species/<scientific_name>.<assembly>/<scientific_name>.<assembly>.ini $MUGQIC_PIPELINES_HOME/resources/genomes/config/

Step 4: Validating GenPipes local deployment
---------------------------------------------

You are now all set to use GenPipes pipelines. For each pipeline, you can get help about its usage through the help command:

::

  genpipes <pipeline_name> --help

Running pipelines requires other inputs such as :ref:`Configuration File<docs_config_ini_file>`, :ref:`Readset File<docs_readset_file>` and :ref:`Design File<docs_design_file>`. For details on how to run individual pipelines you can see :ref:`Running GenPipes<docs_using_gp>` or :ref:`GenPipes User Guide<docs_user_guide>`.

.. note::

    In case of any issues, you can try GenPipes :ref:`Support<docs_how_to_get_support>` or check out other :ref:`communication channels<docs_channels>` to view latest discussions around using GenPipes by the community.

.. note::

   You may also want to check the latest GenPipes deployment and setup instructions listed in `GenPipes README.md file <https://bitbucket.org/mugqic/genpipes/src/master/README.md>`_.

.. _Ensemble Genomes: http://ensemblgenomes.org
.. _UCSC: http://genome.ucsc.edu/

