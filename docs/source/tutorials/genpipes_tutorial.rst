.. _doc_genpipes_tutorial:

GenPipes Tutorial 
==================

GenPipes bioinformatics pipelines developed at the Canadian Centre for Computational Genomics (C3G), as part of the GenAP project, are available for public use. They include a wide array of pipelines, including RNA-Seq, ChIP-Seq, WGS, exome sequencing, Bisulfite sequencing, Hi-C, capture Hi-C, Metagenomics and SARS-CoV-2 genome sequencing pipeline. This document explains how to use the pipelines using Hi-C analysis pipeline and the ChIP-Seq pipeline, as examples.

Setting up the environment
--------------------------

Abacus, Compute Canada users
''''''''''''''''''''''''''''

Software and scripts used by GenPipes are already installed on several Compute Canada servers including Beluga, Cedar and others. To access the tools, you will need to add the tool path to your **bash_profile**. The bash profile is a hidden file in your home directory that sets up your environment every time you log in.

You can also use your bashrc file. For more information on the differences between the .bash_profile and the .bashrc profile, consult `this page <http://www.joshstaiger.org/archives/2005/07/bash_profile_vs.html>`__.

.. code-block:: bash

    ## open bash_profile:
    nano $HOME/.bash_profile

paste the following lines of code and save the file and Exit (Control + X):

.. code-block:: bash

    ## GenPipes/MUGQIC genomes and modules
    export MUGQIC_INSTALL_HOME=/cvmfs/soft.mugqic/CentOS6
    module use $MUGQIC_INSTALL_HOME/modulefiles
    module load mugqic/python/3.11.1
    module load mugqic/genpipes/<latest_version>
    export JOB_MAIL=<my.name@my.email.ca>
    export RAP_ID=<my-rap-id>

You will need to replace text within < >, with your information.

To find out the latest GenPipes version use the output of:

.. code-block:: bash

    module avail 2>&1 | grep mugqic/genpipes


**Note:** previous versions of GenPipes were named mugqic_pipelines and are still available for use.

**JOB_MAIL** is the email to which the notifications are sent after each job. We advise you to create a separate email for jobs since you can receive hundreds of emails per pipeline. You can also de-activate the email sending option by removing the **“-M $JOB_MAIL”** option from the .ini files (discussed below).

**RAP_ID** is the Resource Allocation Project ID from Compute Canada; It is usually in the format: rrg-lab-xy OR def-lab

When you make changes to your bash_profile, you will need to log out then log in again, or type in the following command:


.. code-block:: bash

    source $HOME/.bash_profile

By adding those lines to your bash profile, you are now ready to use our pipelines. This also gives you access to hundreds of bioinformatics tools pre-installed by our team. To explore the available tools, you can type:

.. code-block:: bash

    module avail mugqic/

For a full list of available modules, you can visit our :ref:`module page <doc_cvmfs_modules>`.

To load a tool, for example samtools, you can use:

.. code-block:: bash

    # module add mugqic/<tool>/<version>
    module add mugqic/samtools/1.4.1
    # Now samtools 1.4.1 is available to use. To check:
    samtools

You also have access to pre-installed genomes available in: **$MUGQIC_INSTALL_HOME/genomes/species/**
To check all the available species, type:

.. code-block:: bash

    ls $MUGQIC_INSTALL_HOME/genomes/species

All genome-related files, including indices for different aligners and annotation files can be found in:

.. code-block:: bash

    $MUGQIC_INSTALL_HOME/genomes/species/<species_scientific_name>.<assembly>/
    ## so for Homo Sapiens hg19 assembly, that would be:
    ls $MUGQIC_INSTALL_HOME/genomes/species/Homo_sapiens.hg19/

For a list of available genomes, you can visit our :ref:`genome page <doc_cvmfs_genomes>`.

Usage:
------
Now that your variables are set, you can launch any pipeline using the `genpipes` command:

::
    
    genpipes <pipeline_name> [options] -g genpipes_pipeline_cmd.sh
    bash genpipes_pipeline_cmd.sh

To check the help information for the `chipseq` pipeline pipeline, try:

.. code-block:: bash

    genpipes chipseq -h

All our pipelines use the same framework and work in similar ways; each with its own output of course. We will focus on two pipelines to demonstrate how the framework works.

To use most of our pipelines you will need two types of files; a **configuration file** that stores all the parameters used by the pipeline (extension .ini) and a **readset file** that stores all the information about your samples.

Configuration File:
-------------------
GenPipes pipelines are multi-step pipelines that run several tools, each with its own parameter inputs. All those parameters are stored in configuration files with **.ini** extension. Those files have a structure similar to Microsoft Windows INI files, where parameters are divided within sections.

.. note::

    **What is a “configuration file” or an “ini” file and why do we need it?**

    An ini file is a file that contains parameters needed to run a pipeline.
    Our genome alignment pipeline contains over 20 steps, each involving over 5
    parameters per step. Imagine having to type all 100 parameters to run a pipeline!
    For simplicity, all the parameters are stored in an “ini” file (extension .ini)
    that accompanies the pipeline.
    Try opening an ini file in a text editor and look at its content!

Each pipeline has several configuration/ini files in:

**$MUGQIC_PIPELINES_HOME/pipelines/<pipeline_name>/<pipeline_name>.*.ini**

For chipseq, that would be:

.. code-block:: bash

    ls $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini

You will find a **<pipeline_name>.base.ini** as well as an ini file for particular servers like Beluga (<pipeline_name>.beluga.ini). The base.ini file has all the parameters needed by the pipeline but is optimized for usage on our own server, Abacus. To use the pipeline on beluga server, you will need to use both base.ini and beluga.ini, as such:

.. code-block:: bash

    genpipes chipseq -c $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini

To change different parameters in the ini files, you can create your own ini file and overwrite the required parameters. For example, to change the number of threads for trimmomatic and hicup, I can create my own ini file: chipseq.test.ini
and in it I can include the parameters to be changed:

.. code-block:: bash

    [trimmomatic]

    threads=2

    [hicup_align]

    threads=4

then add my ini file after the other ini files:

.. code-block:: bash

    genpipes chipseq -c $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.beluga.ini chipseq.test.ini [options]

For different species, we have custom ini files stored in **$MUGQIC_INSTALL_HOME/genomes/species/<species_of_interest>/**

The genome default for our pipelines is human. To use other species, you can either create a custom .ini file or you can use the .ini files provided in **$MUGQIC_INSTALL_HOME/genomes/species/<species_of_interest>** if your species of interest is available.

To run the chipseq pipeline on mouse mm9, for example, you can do the following:

.. code-block:: bash

    genpipes chipseq -c $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.beluga.ini $MUGQIC_INSTALL_HOME/genomes/species/Mus_musculus.mm9/Mus_musculus.mm9.ini [options]

Readset File:
-------------

The readset file is a **tab-separated** file that contains the following information:

**Sample:** must contain letters A-Z, numbers 0-9, hyphens (-) or underscores (_) only; BAM files will be merged into a file named after this value; mandatory.

.. note::

   **Sample**

     The definition of a sample in the context of GenPipes is the "input" biological sample, i.e. the sample on which processing such as IP, IgG assay (ChIPSeq Pipeline) or nothing (input) was performed. This is in contrast to sample being defined as the "sample sent for sequencing".

**Readset:** a unique readset name with the same allowed characters as above; mandatory.

.. role:: red

**Library:** :red:`optional.`
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

Example:

.. code-block:: bash

    Sample Readset Library RunType Run Lane Adapter1 Adapter2 QualityOffset BED FASTQ1 FASTQ2 BAM
    sampleA readset1 lib0001 PAIRED_END run100 1 AGATCGGAAGAGCACACGTCTGAACTCCAGTCA AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT 33 path/to/file.bed path/to/readset1.paired1.fastq.gz path/to/readset1.paired2.fastq.gz path/to/readset1.bam
    sampleA readset2 lib0001 PAIRED_END run100 2 AGATCGGAAGAGCACACGTCTGAACTCCAGTCA AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT 33 path/to/file.bed path/to/readset2.paired1.fastq.gz path/to/readset2.paired2.fastq.gz path/to/readset2.bam
    sampleB readset3 lib0002 PAIRED_END run200 5 AGATCGGAAGAGCACACGTCTGAACTCCAGTCA AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT 33 path/to/file.bed path/to/readset3.paired1.fastq.gz path/to/readset3.paired2.fastq.gz path/to/readset3.bam
    sampleB readset4 lib0002 PAIRED_END run200 6 AGATCGGAAGAGCACACGTCTGAACTCCAGTCA AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT 33 path/to/file.bed path/to/readset4.paired1.fastq.gz path/to/readset4.paired2.fastq.gz path/to/readset4.bam

If some optional information is missing, leave its position empty.
**Sample vs Readset:**

Readsets refer to replicates that belong to a particular sample. If a sample was divided over 3 lanes, each lane output would be a readset of that sample. Most pipelines merge readsets and run the analysis based on samples. You can think of readsets as technical replicates while Samples as biological replicates.

.. note::

    **What is a “Readset file” and why do we need it?**

    A readset file is another file that accompanies our pipelines.
    While the configuration files contains information about the parameters needed by the
    tools in the pipeline, the readset file contains information about the samples to be
    analyzed. In the Readset file, you list each readset used for the analysis, which samples are to be merged and where your fastq files or bam files are located.

Creating a Readset File:
------------------------

If you have access to Abacus, we provide a script **$MUGQIC_PIPELINES_HOME/utils/nanuq2mugqic_pipelines.py** that can access your Nanuq data, creates symlinks to the data on Abacus and creates the Readset file for you.

If your data is on nanuq but you do not have access to Abacus, there is a helper script **$MUGQIC_PIPELINES_HOME/utils/csvToreadset.R** that takes a csv file downloadable from nanuq and creates the Readset file. However, you will have to download the data from Nanuq yourself.

If your data is not on nanuq, you will have to manually create the Readset file. You can use a template and enter your samples manually. Remember that it is a tab separated file. There is a helper **$MUGQIC_PIPELINES_HOME/utils/mugqicValidator.py** script that can validate the integrity of your readset file.


Design File:
------------

Certain pipelines where samples are compared against other samples, like `chipseq` and `rnaseq`, require a design file that describes which samples are to be compared. We will discuss this later during an example.


.. note::

    **What is a “Design file” and why do we need it?**

    A Design file is another file that accompanies some of our pipelines,
    where sample comparison is part of the pipeline. Unlike the configuration file and the
    Readset file, the Design file is not required by every pipeline. To check whether the pipeline
    you are interested in requires a Design file and to understand the format of the file, read the specific help pages for your pipeline of interest.

Running GenPipes on Compute Canada Servers: 
---------------------------------------------

Make sure you are logged into the server, say Beluga. The default scheduler is Slurm.

.. note::

     The Abacus server, unlike Beluga, Cedar, Narval servers, uses the PBS scheduler. To use GenPipes on Abacus, don’t forget to add the **“-j pbs”** option (default is -j Slurm).

See example below for more details.

Example run:
------------

chipseq Test Dataset:
''''''''''''''''''''''

We will start by downloading  `chipseq test dataset <https://datahub-90-cw3.p.genap.ca/chipseq.chr19.new.tar.gz>`__.

In the downloaded tar file, you will find the fastq read files in folder “rawData” and will find the readset file (readset.chipseq.txt) that describes that dataset.

We will run this analysis on Beluga server as follows:

.. code-block:: bash

    genpipes chipseq -c $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readsets.chipseq.txt -s 1-15 -g chipseqcmd.sh

**-c** defines the ini configuration files
**-r** defines the readset file
**-s** defines the steps of the pipeline to execute. To check pipeline steps use `genpipes chipseq -h`

The pipelines do not run the commands directly; they output them as text commands.  Use the `-g filname.sh` option to store these commands in a script file. Then run the script to execute the pipeline.

This command works for servers using a SLURM scheduler like Cedar, Graham or Beluga. For the PBS scheduler, used by Abacus, you need to add the “-j pbs” option, as follows:

.. code-block:: bash

    genpipes chipseq -c $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/abacus.ini -r readsets.chipseq.tsv -s 1-15 -j pbs -g chipseqcmd.sh

To run it, use:

.. code-block:: bash

    bash chipseqcmd.sh


You will not see anything happen, but the commands will be sent to the server job queue. **So do not run this more than once per job.**
To confirm that the commands have been submitted, wait a minute or two depending on the server and type:

.. code-block:: bash

    squeue -u <userID>

where <userID> is your login id for accessing Compute Canada infrastructure. 
On abacus, the equivalent command is:

.. code-block:: bash

    showq -u <userID>


In case you ran the command to submit the jobs several times and launched too many commands you do not want, you can use the following line of code to cancel ALL commands:

.. code-block:: bash

    scancel -u <userID>

Or on abacus:

.. code-block:: bash

    showq -u <userID> | tr "|" " "| awk '{print $1}' | xargs -n1 canceljob

Congratulations! you just ran the `chipseq` pipeline.

After the processing is complete, you can access quality control plots in the report/ directory and find peak data in the peak_call/ directory.

For more information about output formats please consult the webpage of the third party tool used.

Creating a Design File:
-----------------------

Certain pipelines that involve comparing and contrasting samples, need a Design File.

The Design File is a **tab-separated** plain text file with one line per sample and the following columns:

**Sample:** first column; must contain letters A-Z, numbers 0-9, hyphens (-) or underscores (_) only; the sample name must match a sample name in the readset file; mandatory.

**contrast:** each of the following columns defines an experimental design contrast; the column name defines the contrast name, and the following values represent the sample group membership for this contrast:

- **‘0’ or ”:** the sample does not belong to any group.
- **‘1’:** the sample belongs to the control group.
- **‘2’:** the sample belongs to the treatment test case group.


Example:

.. code-block:: bash

    Sample Contrast_AB Contrast_AC
    sampleA 1 1
    sampleB 2 0
    sampleC 0 2
    sampleD 0 0


where Contrast_AB compares treatment sampleB to control sampleA, while Contrast_AC compares sampleC to sampleA.

You can add several contrasts per design file.

To see how this works, lets run an RNA-Seq experiment.

Start by downloading the `RNA sequencing pipeline test dataset <https://datahub-90-cw3.p.genap.ca/rnaseq.chr19.tar.gz>`_

In the downloaded tar file, you will find the fastq read files in the folder `rawData` and you will find the readset file (readset.rnaseq.txt) that describes the dataset. You will also find the design file
::
   
	design.rnaseq.txt

that contains the contrast of interest.

Looking at the contents of the design file, we see:
::

	Sample	H1ESC_GM12787
    H1ESC_Rep1	1
    H1ESC_Rep2	1
    GM12878_Rep1	2
    GM12878_Rep2	2

We will run this analysis on the Beluga cluster as follows:
::

	genpipes rnaseq -c $MUGQIC_PIPELINES_HOME/pipelines/rnaseq/rnaseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readset.rnaseq.txt -d design.rnaseq.txt -g rnaseq_commands.sh
    bash rnaseq_commands.sh

The commands will be sent to the job queue to be executed. You can check the progress of the jobs with
::

	squeue -u <userID>

Once the queue is empty and all jobs have run, you can verify the exit status of each job with the GenPipes log_report tool:
::

	log_report.py --tsv log.out job_output/RnaSeq.stringtie.job_list.<TIMESTAMP>

Take a look at the output with 
::

	less -S log.out

and check that all jobs finished successfully. If you find that any jobs failed, look at the outputs in the `job_output` directory to identify the reason for the failure. 

If everything ran successfully, you will find an interactive html report under `report/RnaSeq.stringtie.multiqc.html` and the results of the differential expression analysis under the folder `DGE`.
 

Test Dataset: Chipseq:
----------------------

The ChIP-Seq pipeline can also be run with a design file, but requires a specific design file format.

.. attention:: **Change in the Chipsequence Design File Format**

    .. include:: /user_guide/pipelines/design_fileformat/chipseq_design.inc

We will use a subset of the ENCODE data. They represent a ChIP-Seq analysis dataset with the chromatin mark `H3K27ac` and its control input.

If you have not already done so in the tutorial above, we will start by downloading the `Chipseq pipeline test dataset <https://datahub-90-cw3.p.genap.ca/chipseq.chr19.new.tar.gz>`_.

In the downloaded tar file, you will find the fastq read files in folder rawData and will find the readset file (readset.chipseq.txt) that describes that dataset. You will also find the design file 

::
   
	design.chipseq.txt

that contains the contrast of interest.

Looking at the content of the Readset file 

::

	readsets.chipseqTest.tsv

we see:

::

	Sample	Readset	MarkName	MarkType	Library	RunType	Run	Lane	Adapter1	Adapter2	QualityOffset	BED	FASTQ1	FASTQ2	BAM
    EW22	EW22_A787C17_input	input	I		SINGLE_END	2965	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW22_A787C17_input_chr19.fastq.gz		
    EW22	EW22_A787C20_H3K27ac	H3K27ac	N		SINGLE_END	2962	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW22_A787C20_H3K27ac_chr19.fastq.gz		
    EW3	EW3_1056C284_input	input	I		SINGLE_END	2963	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW3_1056C284_input_chr19.fastq.gz		
    EW3	EW3_A1056C287_H3K27ac	H3K27ac	N		SINGLE_END	2964	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW3_A1056C287_H3K27ac_chr19.fastq.gz		
    EW7	EW7_A485C51_input	input	I		SINGLE_END	2966	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW7_A485C51_input_chr19.fastq.gz		
    EW7	EW7_A490C39_H3K27ac	H3K27ac	N		SINGLE_END	2970	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/EW7_A490C39_H3K27ac_chr19.fastq.gz		
    TC71	TC71_A379C48_H3K27ac	H3K27ac	N		SINGLE_END	2980	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/TC71_A379C48_H3K27ac_chr19.fastq.gz		
    TC71	TC71_A379C51_input	input	I		SINGLE_END	2981	1	AGATCGGAAGAGCACACGTCTGAACTCCAGTCA	AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT	33		raw_data/TC71_A379C51_input_chr19.fastq.gz		

This analysis contains 4 samples with a single readset each. They are all SINGLE_END runs and have a single fastq file in the “rawData” folder. Each sample has a treatment (`H3K27ac`) and a control (`input`). Note that the readset file format for the ChIP-Seq pipeline varies from other pipelines in that it requires the columns `MarkName` and `MarkType`.

Looking at the content of the Design file

::

	design.chipseq.txt

we see:

::

	Sample	MarkName	EW22_EW3_vs_EW7_TC71
    EW22	H3K27ac	1
    EW3	H3K27ac	1
    EW7	H3K27ac	2
    TC71	H3K27ac	2

We see a single analysis that compares samples EW22 and EW3 to samples EW7 and TC71. 

We will run this analysis on Beluga server as follows:

.. code-block:: bash

    genpipes chipseq -c $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readsets.chipseqTest.chr22.tsv -d designfile_chipseq.chr22.txt -s 1-15 > chipseqScript.txt
    bash chipseqScript.txt

The commands will be sent to the job queue and you will be notified once each step is done. If everything runs smoothly, you should get **MUGQICexitStatus:0** or **Exit_status=0**. If that is not the case, then an error has occurred after which the pipeline usually aborts. To examine the errors, check the content of the **job_output** folder.

Available pipelines:
--------------------

For more information:
---------------------
Our pipelines are built around third party tools that the community uses in particular fields. To understand the output of each pipeline, please read the documentation pertaining to the tools that produced the output.

For more information or help with particular pipelines, you can send us an email to:
`info@computationalgenomics.ca <info@computationalgenomics.ca>`_

Or drop by during our `Open Door <https://www.computationalgenomics.ca/open-door/>`_ slots.
