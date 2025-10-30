.. _doc_genpipes_tutorial:

.. spelling:word-list::

    userID

Tutorial: GenPipes on C3G/DRAC Servers 
========================================

.. dropdown:: :material-outlined:`bolt;2em` Usage Change Effective v5.x onward
   :color: success

   .. include:: /gp5_0.inc

.. include:: /common/new_wizard_dropdown.txt    

GenPipes bioinformatics :ref:`pipelines<docs_available_pipelines>` are developed as part of the GenAP project at the Canadian Centre for Computational Genomics (C3G).

This tutorial shows you how to run ChIP-Seq analysis using the ``chipseq`` pipeline 
with GenPipes on `Digital Research Alliance of Canada <https://alliancecan.ca/en>`_ servers, formerly Compute Canada.

.. contents:: 
    :local:
    :depth: 3
 
----

Prerequisites
-------------

You need the following to access GenPips, its scripts, bioinformatics modules, and launch any pipeline on the DRAC servers such as |key_ccdb_server_name|, |other_ccdb_server_names|:

*  A `DRAC account with access to specific servers <https://ccdb.alliancecan.ca/me/access_systems>`_  where you'll run the pipelines.
*  Bash configuration setup with GenPipes tooling path added to the **bash_profile**.
*  Input data such as configuration settings, test dataset, readset and design file (optional). 

.. tip:: 
    
    The bash profile is a hidden file in your home directory that sets up your environment every time you log in. 
    You can also use your ``.bashrc`` file. 
    
    To understand the differences between the .bash_profile and the .bashrc profile, click `here <http://www.joshstaiger.org/archives/2005/07/bash_profile_vs.html>`__.

:bdg-primary:`Step 1:`  Set up Environment
-------------------------------------------

Edit the ``.bash_profile`` file.

.. code-block:: bash

    ## open bash_profile:
    nano $HOME/.bash_profile

Copy and paste these settings in the ``.bash_profile``.

.. code-block:: bash

    ## GenPipes/MUGQIC genomes and modules
    export MUGQIC_INSTALL_HOME=/cvmfs/soft.mugqic/CentOS6
    module use $MUGQIC_INSTALL_HOME/modulefiles
    module load mugqic/genpipes/<latest_version>
    export JOB_MAIL=<my.name@my.email.ca>
    export RAP_ID=<my-rap-id>

You will need to replace text within < >, with data specific to your account.

**Note:** Older versions of GenPipes were named ``mugqic_pipelines`` and are still available for use.

**JOB_MAIL:** The email where notifications are sent for each pipeline job run. Create a separate email for receiving job notifications as these notifications can run into hundreds for a pipeline run. You can choose to not receive job notifications by removing the ``-M $JOB_MAIL`` environment setting.

**RAP_ID:** The Resource Allocation Project ID assigned to your `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_, formerly Compute Canada account. It is usually of the format: ``rrg-lab-xy`` OR ``def-lab``.

Save the file and Exit (Control + X).

When you make changes to your bash_profile, you will need to log out of the DRAC account and then log back in again to activate
the changes in the environment settings. 

Alternatively, you can also this command to set the environment:

.. code-block:: bash

    source $HOME/.bash_profile

Once the environment is set, you are ready to use GenPipes. You also have access to hundreds of bioinformatics tools pre-installed by our team on the DRAC servers. 

:bdg-primary:`Step 2:` Check Deployed Tools
-------------------------------------------

Then, run this command to list available bioinformatics tools on your current server:

.. code-block:: bash

    module avail mugqic/

Bioinformatics modules
+++++++++++++++++++++++

See :ref:`module page <doc_cvmfs_modules>` for a full list of available bioinformatics modules.

GenPipes version
+++++++++++++++++

Check the pre-installed GenPipes versions available for use:

.. code-block:: bash

    module avail 2>&1 | grep mugqic/genpipes

You can load a specific version of GenPipes or any bioinformatics tool. For example, to load v1.4.1 of  ``samtools``  use:

.. code-block:: bash

    # module add mugqic/<tool>/<version>
    module add mugqic/samtools/1.4.1
    # Now samtools 1.4.1 is available to use. To check:
    samtools -h

Available genomes
+++++++++++++++++++

Check your access to the pre-installed genomes located in the folder **$MUGQIC_INSTALL_HOME/genomes/species/**

Explore the available species via the command:

.. code-block:: bash

    ls $MUGQIC_INSTALL_HOME/genomes/species

All genome-related files, including indices for different aligners and annotation files can be found in the folder:

.. code-block:: bash

    ls $MUGQIC_INSTALL_HOME/genomes/species/<species_scientific_name>.<assembly>/

.. code-block:: bash

    ## so for Homo Sapiens hg19 assembly, that would be:
    ls $MUGQIC_INSTALL_HOME/genomes/species/Homo_sapiens.hg19/

For a list of available genomes, you can visit our :ref:`genome page <doc_cvmfs_genomes>`.

:bdg-primary:`Step 3:` Construct Pipeline Command
--------------------------------------------------

Now we will construct the command to launch ``chipseq`` pipeline by using ``genpipes`` followed by the pipeline name, protocol type, options and inputs:

::
    
    genpipes <pipeline_name> [options] -g genpipes_pipeline_cmd.sh
    bash genpipes_pipeline_cmd.sh

Check the available protocols and options supported by the ``chipseq`` pipeline with the command:

.. code-block:: bash

    genpipes chipseq -h

Besides the protocols and options for the pipeline, you must also specify the required
inputs while constructing the pipeline launch command.

Pipeline Inputs
+++++++++++++++++

The ``chipseq`` :ref:`pipeline<docs_available_pipelines>` pipeline launch command requires the following inputs:

* **Test Dataset** refers to the data for pipeline analysis. Includes real sequencing data produced by scientific instruments or sample data.

* **Configuration** ``.ini`` files define pipeline parameters. They follow the Windows INI format. You can specify multiple configuration files per run.

* **Design File** describes which samples are to be compared. Not all pipelines require the design file.

* **Readset File** defines samples in the dataset, including raw file paths, sequencing type, and sample names

Configuration File
'''''''''''''''''''

GenPipes pipelines are multi-step pipelines that run several tools, each with its own parameter inputs. 

Many pipelines have more than 20 steps each with multiple options and parameters. Imagine having to specify hundreds of parameters to construct a pipeline command before launching it. Configuration files simplify the process of setting up pipeline parameters.

View the contents of any sample ``.ini`` file in a text editor to
understand how parameters are specified for various pipeline steps, and for the servers in use.

A pipeline may have one or more configuration files located in the folder:

``$GENPIPES_INIS/<pipeline_name>/<pipeline_name>.*.ini``

For example, refer to the ``chipseq`` configuration file:

.. code-block:: bash

    ls $GENPIPES_INIS/chipseq/chipseq.base.ini

There is a ``<pipeline_name>.base.ini`` file and a DRAC server specific ``.ini`` file  where the pipeline is run.

If ``chipseq`` is run on the |key_ccdb_server_name| server, the corresponding configuration file is:

<pipeline_name>.\ |key_ccdb_server_cmd_name|\.ini
    
The ``base.ini`` file has all the parameters needed by the pipeline but is optimized for usage on a C3G server Abacus. To use the pipeline on |key_ccdb_server_name| server, you will need to use both the ``base.ini`` file and the server specific ``.ini`` file:

.. parsed-literal::

    genpipes chipseq -c $GENPIPES_INIS/chipseq/chipseq.base.ini \\
        $GENPIPES_INIS/common_ini/\ |key_ccdb_server_cmd_name|\.ini

To change different parameters in the ``.ini`` files, you can create your own file and overwrite the required parameters. 

For example, to change the number of threads for ``trimmomatic`` and ``hicup`` steps in the pipeline, you can create a ``.ini`` file
named ``chipseq.test.ini`` and specify the following parameters:

.. code-block:: bash

    [trimmomatic]

    threads=2

    [hicup_align]

    threads=4

Add ``chipseq.test.ini`` file after the other ``.ini`` files when constructing the pipeline launch command:

.. parsed-literal::

    genpipes chipseq -c $GENPIPES_INIS/chipseq/chipseq.base.ini \\
        $GENPIPES_INIS/chipseq/chipseq.\ |key_ccdb_server_cmd_name|\.ini \\
        chipseq.test.ini [options]

Genome Species
^^^^^^^^^^^^^^^

The **custom .ini files** located in the folder:

``$MUGQIC_INSTALL_HOME/genomes/species/<species_of_interest>/``

contain genomic files for different species.

The human genome is the default for any pipelines. To use other species, you can either create a ``custom .ini`` configuration
file or use the ``.ini`` files provided in the ``$MUGQIC_INSTALL_HOME/genomes/species/<species_of_interest>`` folder. 

For example, to run the ``chipseq`` pipeline on *mouse mm9* genome, construct the pipeline command as follows:

.. parsed-literal::

    genpipes chipseq -c $GENPIPES_INIS/chipseq/chipseq.base.ini \\
        $GENPIPES_INIS/chipseq/chipseq.\ |key_ccdb_server_cmd_name|\.ini \\
        $MUGQIC_INSTALL_HOME/genomes/species/Mus_musculus.mm9/Mus_musculus.mm9.ini [options]

Design File
'''''''''''

Certain pipelines that require comparing samples against other samples, such as ``chipseq`` and ``rnaseq`` need a design file as input. A design file describes which samples are to be compared. Use ``-h`` flag or refer to the :ref:`Pipeline Reference<docs_pipeline_ref>` to see if a design file input is needed for constructing a pipeline launch command.

Readset File
'''''''''''''

The readset file contains the sample and readset data details. It specifies the unique readset used for the analysis, the samples that are to be merged and the location of FASTQ input files or the BAM files.

Its contents are *tab-separated* and contain the following details:

----

**Library:** (Optional)

**RunType:** PAIRED_END or SINGLE_END; mandatory.

**Run:** mandatory.

**Lane:** mandatory.

**Adapter1:** sequence of the forward trimming adapter

**Adapter2:** sequence of the reverse trimming adapter

**QualityOffset:** quality score offset integer used for trimming; optional.

**BED:** relative or absolute path to BED file; optional.

**FASTQ1:** relative or absolute path to first FASTQ file for paired-end readset or single FASTQ file for single-end readset; mandatory if BAM value is missing.

**FASTQ2:** relative or absolute path to second FASTQ file for paired-end readset; mandatory if RunType value is “PAIRED_END”.

**BAM:** relative or absolute path to BAM file which will be converted into FASTQ files if they are not available; mandatory if FASTQ1 value is missing, ignored otherwise.

----

Sample
^^^^^^^

In the context of GenPipes, a sample is defined as the "input" biological sample. This is different from a typical sample being defined as the "sample sent for sequencing".

Sample refers to data on which IP, IgG assay (ChIPSeq Pipeline) processing (or none) was performed.


Each sample must contain letters A-Z, numbers 0-9, hyphens (-) or underscores (_) only; BAM files will be merged into a file named after this value; mandatory.    

Readset Data
^^^^^^^^^^^^

A readset file refers to a unique input readset data. 

Its contents are specified using the same *allowed* characters as in the sample file above. Readset is a mandatory input for launching any GenPipes pipeline. While the configuration files contains information about the parameters needed by various steps that use bioinformatics tools in the pipeline, the readset file contents specify the samples that need to be analyzed.

Sample vs. Readset
^^^^^^^^^^^^^^^^^^

Readsets refer to replicates that belong to a particular sample. If a sample was divided over 3 lanes, each lane output would be a readset of that sample. Most pipelines merge readsets and run the analysis based on samples. You can think of readsets as technical replicates while Samples as biological replicates.  

Creating a Readset File
++++++++++++++++++++++++

If you have access to Abacus server, GenPipes provides a script ``nanuq2mugqic_pipelines.py`` that can access the Nanuq data, creates symlinks to the data on Abacus and creates the Readset file for you.

* If your data is on nanuq but you do not have access to Abacus, there is a helper script ``csvToreadset.R`` that takes a ``.csv`` file downloadable from nanuq and creates the Readset file. However, you will have to download the data from Nanuq yourself.

* If your data is not on nanuq, you will have to manually create the Readset file. You can use a template and enter your samples manually. Remember that it is a tab separated file. There is a helper **mugqicValidator.py** script that can validate the integrity of your readset file.
  
Readset Example
'''''''''''''''

.. code-block:: bash

    Sample  Readset     Library RunType     Run     Lane    Adapter1                            Adapter2                            QualityOffset   BED                 FASTQ1                              FASTQ2                              BAM
    sampleA readset1    lib0001 PAIRED_END  run100  1       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed    path/to/readset1.paired1.fastq.gz   path/to/readset1.paired2.fastq.gz   path/to/readset1.bam
    sampleA readset2    lib0001 PAIRED_END  run100  2       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed    path/to/readset2.paired1.fastq.gz   path/to/readset2.paired2.fastq.gz   path/to/readset2.bam
    sampleB readset3    lib0002 PAIRED_END  run200  5       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed    path/to/readset3.paired1.fastq.gz   path/to/readset3.paired2.fastq.gz   path/to/readset3.bam
    sampleB readset4    lib0002 PAIRED_END  run200  6       AGATCGGAAGAGCACACGTCTGAACTCCAGTCA   AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT   33              path/to/file.bed    path/to/readset4.paired1.fastq.gz   path/to/readset4.paired2.fastq.gz   path/to/readset4.bam

If some optional information is missing in the readset, the contents of that column should be empty. 

:bdg-primary:`Step 4a:` Run ``chipseq`` on DRAC Server 
--------------------------------------------------------

The ``chipseq`` pipeline can be run both with and without a design file as input.
We will first run it without a design file. Then we will launch it
using a design file as input.

Make sure you are logged into the server, say |key_ccdb_server_name|. The default scheduler is Slurm.

``chipseq`` Test Dataset
+++++++++++++++++++++++++

To construct the ``chipseq`` launch command, we will start by `downloading the dataset for ChIP-Seq <https://datahub-90-cw3.p.genap.ca/chipseq.chr19.new.tar.gz>`_.

In the downloaded tar file, you will find the fastq read files in folder “rawData” and will find the readset file (readset.chipseq.txt) that describes that dataset.

To run this analysis on |key_ccdb_server_name| server, create the launch command as follows:

.. parsed-literal::

    genpipes chipseq -c $GENPIPES_INIS/chipseq/chipseq.base.ini \\
        $GENPIPES_INIS/common_ini/|key_ccdb_server_cmd_name|.ini \\
        -r readsets.chipseq.txt -s 1-15 -g chipseqcmd.sh

- **-c**  ``.ini`` configuration files
- **-r**  readset file
- **-s**  selected pipeline steps that must be executed. 

You can check available pipeline steps by using ``genpipes chipseq -h`` option.

Note that the command above does not actually execute a pipeline run. It outputs the text commands that must be issued to launch the pipeline_name.  The `-g filname.sh` option stores these commands in a script file. You must run that script to launch the pipeline on the 
DRAC server.

By default, the command specified above works for any server that uses the Slurm scheduler such as |key_ccdb_server_name|, |other_ccdb_server_names|. 

For the server such as Abacus that uses PBS scheduler you must add the ``-j pbs`` option to the command:

.. code-block:: bash

    genpipes chipseq -c $GENPIPES_INIS/chipseq/chipseq.base.ini \\
        $GENPIPES_INIS/common_ini/abacus.ini \\
        -r readsets.chipseq.tsv -s 1-15 -j pbs -g chipseqcmd.sh

To run it, use:

.. code-block:: bash

    bash chipseqcmd.sh

Congratulations on your first successful launch of the ``chipseq`` pipeline. In this run we did not use any design file for the analysis.

:bdg-primary:`Step 4b:` Run ``chipseq`` on DRAC Server (with Design File) 
--------------------------------------------------------------------------

The ChIP-Seq pipeline can also be run with a design file, but requires a specific design file format.

.. admonition:: **Change in the Chipsequence Design File Format**
    :class: danger

    .. include:: /user_guide/pipelines/design_fileformat/chipseq_design.inc

We will use a subset of the ENCODE data. They represent a ChIP-Seq analysis dataset with the chromatin mark `H3K27ac` and its control input.

If you have not already done so in the tutorial above, we will start by `downloading the dataset for ChIP-Seq <https://datahub-90-cw3.p.genap.ca/chipseq.chr19.new.tar.gz>`_.

In the downloaded tar file, you will find the fastq read files in folder rawData and will find the readset file (readset.chipseq.txt) that describes that dataset. You will also find the design file 

::
   
	design.chipseq.txt

that contains the contrast of interest for this analysis.

Review the contents of the Readset file: 

::

	readsets.chipseqTest.tsv

It contains the following details:

.. parsed-literal::

    Sample	Readset	                MarkName	MarkType	Library	RunType	        Run	Lane	Adapter1	Adapter2	QualityOffset	BED	FASTQ1	FASTQ2	BAM
    EW22	EW22_A787C17_input	input	        I		        SINGLE_END	2965	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW22_A787C17_input_chr19.fastq.gz		
    EW22	EW22_A787C20_H3K27ac	H3K27ac 	N		        SINGLE_END	2962	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW22_A787C20_H3K27ac_chr19.fastq.gz		
    EW3	        EW3_1056C284_input	input	        I		        SINGLE_END	2963	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW3_1056C284_input_chr19.fastq.gz		
    EW3	        EW3_A1056C287_H3K27ac	H3K27ac	        N		        SINGLE_END	2964	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW3_A1056C287_H3K27ac_chr19.fastq.gz		
    EW7	        EW7_A485C51_input	input	        I		        SINGLE_END	2966	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW7_A485C51_input_chr19.fastq.gz		
    EW7	        EW7_A490C39_H3K27ac	H3K27ac	        N		        SINGLE_END	2970	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW7_A490C39_H3K27ac_chr19.fastq.gz		
    TC71	TC71_A379C48_H3K27ac	H3K27ac	        N		        SINGLE_END	2980	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/TC71_A379C48_H3K27ac_chr19.fastq.gz		
    TC71	TC71_A379C51_input	input	        I		        SINGLE_END	2981	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/TC71_A379C51_input_chr19.fastq.gz		

This analysis contains 4 samples with a single readset each. They are all SINGLE_END runs and have a single fastq file in the “rawData” folder. Each sample has a treatment (`H3K27ac`) and a control (`input`). 

.. attention:: **Unique Readset for ChIP-Seq**
    
    Note that the readset file format for the ChIP-Seq pipeline differs from the other pipelines. It requires the columns `MarkName` and `MarkType` unlike other pipelines.

Review the contents of the Design file

::

	design.chipseq.txt

It contains the following details:

.. parsed-literal::

        Sample	MarkName    EW22_EW3_vs_EW7_TC71
        EW22	H3K27ac	    1
        EW3	H3K27ac	    1
        EW7	H3K27ac	    2
        TC71	H3K27ac	    2

The design file shows a single analysis that compares samples EW22 and EW3 to samples EW7 and TC71. 

First create the launch command for this analysis on |key_ccdb_server_name| server as follows:

.. parsed-literal::

    genpipes chipseq -c $GENPIPES_INIS/chipseq/chipseq.base.ini \\
        $GENPIPES_INIS/common_ini/|key_ccdb_server_cmd_name|.ini \\
        -r readsets.chipseqTest.chr22.tsv \\
        -d designfile_chipseq.chr22.txt -s 1-15 > chipseqScript.txt

Then run the ``chipseq`` pipeline with the commands in the file:

.. parsed-literal::
    
        bash chipseqScript.txt

Congratulations! you just ran the `chipseq` pipeline using a design file as input.

The commands will be sent to the job queue and you will be notified once each step is done. 

If everything runs smoothly, you should get **MUGQICexitStatus:0** or **Exit_status=0**. If that is not the case, then an error has occurred after which the pipeline usually aborts. To examine the errors, check the content of the **job_output** folder.

Creating a Design File
+++++++++++++++++++++++

Certain pipelines that involve comparing and contrasting samples, need a Design File.

The Design File is a **tab-separated** plain text file with one line per sample and the following columns:

**Sample:** first column; must contain letters A-Z, numbers 0-9, hyphens (-) or underscores (_) only; the sample name must match a sample name in the readset file; mandatory.

**Contrast:** each of the following columns defines an experimental design contrast; the column name defines the contrast name, and the following values represent the sample group membership for this contrast:

- **‘0’ or ”:** the sample does not belong to any group.
- **‘1’:** the sample belongs to the control group.
- **‘2’:** the sample belongs to the treatment test case group.


Design Example
''''''''''''''

.. code-block:: bash

    Sample  Contrast_AB Contrast_AC
    sampleA 1   1
    sampleB 2   0
    sampleC 0   2
    sampleD 0   0


* Contrast_AB compares treatment sampleB to control sampleA
* Contrast_AC compares sampleC to sampleA.

You can add several contrasts per design file.

To see how this works, lets run an RNA-Seq experiment.

Start by `downloading the data for RNA-Seq  <https://datahub-90-cw3.p.genap.ca/rnaseq.chr19.tar.gz>`_.

In the downloaded tar file, you will find the fastq read files in the folder `rawData` and you will find the readset file (readset.rnaseq.txt) that describes the dataset. You will also find the design file
::
   
	design.rnaseq.txt

that contains the contrast of interest.

The design file contents are as follows:
::

	Sample	H1ESC_GM12787
    H1ESC_Rep1	1
    H1ESC_Rep2	1
    GM12878_Rep1	2
    GM12878_Rep2	2

We will run this analysis on the |key_ccdb_server_name| cluster by first constructing the command for ``rnaseq`` pipeline:

.. parsed-literal::

	genpipes rnaseq -c $GENPIPES_INIS/rnaseq/rnaseq.base.ini \\
        $GENPIPES_INIS/common_ini/|key_ccdb_server_cmd_name|.ini \\
        -r readset.rnaseq.txt -d design.rnaseq.txt -g rnaseq_commands.sh

Then run the pipeline via the command:

.. parsed-literal::
    
        bash rnaseq_commands.sh

The commands will be sent to the job queue to be executed. You can check the progress of the jobs with:

::

	squeue -u <userID>

:bdg-primary:`Step 5:` Monitor Submitted Jobs
-----------------------------------------------

When you launch a pipeline run by issuing ``bash [-goptionfilename.sh]`` command, you will not see anything happen immediately on the terminal but the commands will be sent to the server job queue. 

**Do not run the pipline launch command more than once per job.**

To confirm that the commands have been submitted, wait a minute or two depending on the server and use this command to check job status:

.. code-block:: bash

    squeue -u <userID>

where <userID> is your login id for accessing the `Digital Research Alliance of Canada (DRAC) <https://alliancecan.ca/en>`_ infrastructure, formerly Compute Canada.

On Abacus (PBS Scheduler), the equivalent command is:

.. code-block:: bash

    showq -u <userID>

Cancel Job
+++++++++++

In case you ran the command to submit the jobs several times and launched too many commands you do not want, you can cancel ALL commands by issuing:

.. code-block:: bash

    scancel -u <userID>

On Abacus (PBS Scheduler), the equivalent command is:

.. code-block:: bash

    showq -u <userID> | tr "|" " "| awk '{print $1}' | xargs -n1 canceljob
    
View Logs & Reports
+++++++++++++++++++

Once the queue is empty and all jobs have run, you can verify the exit status of each job with the GenPipes log_report tool:

::

	log_report.py --tsv log.out job_output/RnaSeq.stringtie.job_list.<TIMESTAMP>

Take a look at the output with:

::

	less -S log.out

and check that all jobs finished successfully. 

If you find that any jobs failed, look at the outputs in the ``job_output`` directory to identify the reason for the failure. 

If everything ran successfully, you will find an interactive html report under ``report/RnaSeq.stringtie.multiqc.html`` and the results of the differential expression analysis under the folder ``DGE``.

After the processing is complete, you can access quality control plots in the report/ directory and find peak data in the peak_call/ directory.

For more information about output formats please consult the webpage of the third party tools used by the pipeline.

Getting Help
-------------

GenPipes pipelines are built around third party tools used by the genomic research community in specific fields. To understand the output of each pipeline, refer to the  documentation for these specific tools used in pipeline steps to understand the produced output. 

For more information on contacting the GenPipes team or get help, click :ref:`support<docs_how_to_get_support>`.
