:orphan:

.. _docs_config_ini_file:

Configuration File
==================

.. spelling::
   
   extention
   ini

GenPipes pipelines are multi-step pipelines that run several tools, each with its own parameter inputs. All those parameters are stored in configuration files with .ini extension. Those files have a structure similar to Microsoft Windows INI files, where parameters are divided within sections.


.. note:: **Why does GenPipes need configuration file?**

          An ini file is a file that contains parameters needed to run a pipeline.  Our genome alignment pipeline contains over 20 steps, each involving over 5 parameters per step. Imagine having to type all 100 parameters to run a pipeline! For simplicity, all the parameters are stored in an “ini” file (extention.ini) that accompanies the pipeline. 

          Try opening an ini file in a text editor and look at its content!

Configuration File Format
-------------------------

Pipeline command parameters and cluster settings can be customized using Configuration Files (.ini extension). Those files have a structure similar to Microsoft Windows INI files e.g.:

::

    #!ini
    [DEFAULT]
    module_trimmomatic=mugqic/trimmomatic/0.36

    [trimmomatic]
    min_length=50

A parameter value is first searched in its specific section, then, if not found, in the special DEFAULT section. The example above would resolve parameter module_trimmomatic value from section trimmomatic to mugqic/trimmomatic/0.36.

Configuration files support interpolation. For example:

::

    #!ini
    scientific_name=Homo_sapiens
    assembly=GRCh37
    assembly_dir=$MUGQIC_INSTALL_HOME/genomes/species/%(scientific_name)s.%(assembly)s
    genome_fasta=%(assembly_dir)s/genome/%(scientific_name)s.%(assembly)s.fa

Here, ``genome_fasta`` would resolve to ``$MUGQIC_INSTALL_HOME/genomes/species/Homo_sapiens.GRCh37/genome/Homo_sapiens.GRCh37.fa``.

Each pipeline has several configuration files in:

::

    #!bash
    $MUGQIC_PIPELINES_HOME/pipelines/<pipeline_name>/<pipeline_name>.*.ini

A default configuration file (``.base.ini`` extension) is set for running on abacus cluster using Homo sapiens reference genome and must always be passed first to the ``--config`` option.

You can also add a list of other configuration files to ``--config``. Files are read in the list order and each parameter value is overwritten if redefined in the next file.

This is useful to customize settings for a specific cluster or genome. Each pipeline has a special configuration file for beluga and cedar clusters (``.beluga.ini`` and ``.cedar.ini`` extensions respectively) in the same directory. And various genome settings are available in ``$MUGQIC_PIPELINES_HOME/resources/genomes/config/``.

For example, to run the DNA-Seq pipeline on beluga cluster with Mus musculus reference genome:

::

    #!bash
    genpipes $MUGQIC_PIPELINES_HOME/pipelines/dnaseq/dnaseq --config $MUGQIC_PIPELINES_HOME/pipelines/dnaseq/dnaseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini $MUGQIC_PIPELINES_HOME/resources/genomes/config/Mus_musculus.GRCm38.ini [other options] -g genpipes_command_list.sh
    bash genpipes_command_list.sh


