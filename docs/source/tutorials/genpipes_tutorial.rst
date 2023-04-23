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
    module load mugqic/python/3.9.1
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
Now that your variables are set, you can launch any pipeline using:
**<pipeline_name>.py**
To check the help information for our hicseq (Hi-C analysis) and our chipseq pipelines, try:

.. code-block:: bash

    hicseq.py -h
    chipseq.py -h

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
For hicseq, that would be:

.. code-block:: bash

    ls $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini


For chipseq, that would be:

.. code-block:: bash

    ls $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini

You will find a **<pipeline_name>.base.ini** as well as an ini file for particular servers like Beluga (<pipeline_name>.beluga.ini). The base.ini file has all the parameters needed by the pipeline but is optimized for usage on our own server, Abacus. To use the pipeline on beluga server, you will need to use both base.ini and beluga.ini, as such:

.. code-block:: bash

    hicseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini …

To change different parameters in the ini files, you can create your own ini file and overwrite the required parameters. For example, to change the number of threads for trimmomatic and hicup, I can create my own ini file: hicseq.test.ini
and in it I can include the parameters to be changed:

.. code-block:: bash

    [trimmomatic]

    threads=2

    [hicup_align]

    threads=4

then add my ini file after the other ini files:

.. code-block:: bash

    hicseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.beluga.ini hicseq.test.ini...

For different species, we have custom ini files stored in **$MUGQIC_PIPELINES_HOME/resources/genomes/config/**

The genome default for our pipelines is human. To use other species, you can either create a custom .ini file or you can use the .ini files provided in **$MUGQIC_PIPELINES_HOME/resources/genomes/config/** if your species of interest is available.

To run the hicseq pipeline on mouse mm9, for example, you can do the following:

.. code-block:: bash

    hicseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.beluga.ini $MUGQIC_PIPELINES_HOME/resources/genomes/config/Mus_musculus.mm9.ini ...

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

Certain pipelines where samples are compared against other samples, like chipseq.py and rnaseq.py, require a design file that describes which samples are to be compared. We will discuss this later during an example.


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

     Guillimin, unlike Beluga, Cedar, Narval use the PBS scheduler. To use GenPipes on Guillimin, don’t forget to add the **“-j pbs”** option (default is -j Slurm).

See example below for more details.

Example run:
------------

hicseq Test Dataset:
''''''''''''''''''''

Let’s now run the pipeline using a test dataset. We will use the first 2 million reads from HIC010 from Rao et al. 2014 (SRR1658581.sra). This is an in situ Hi-C experiment of GM12878 using MboI restriction enzyme.

We will start by downloading the dataset from `here <https://datahub-90-cw3.p.genap.ca/hicseq.chr19.tar.gz>`__.
In the downloaded zip file, you will find the two fastq read files in folder “rawData” and will find the readset file (readsets.HiC010.tsv) that describes that dataset.

We will run this analysis on Beluga server as follows:

.. code-block:: bash

    hicseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readsets.HiC010.tsv -s 1-15 -e MboI > hicseqScript_SRR1658581.txt

**-c** defines the ini configuration files
**-r** defines the readset file
**-s** defines the steps of the pipeline to execute. To check pipeline steps use **hicseq -h**
**-e** defines the restriction enzyme used in the HiC library

The pipelines do not run the commands directly; they output them as text commands. So we need to redirect them into a file using “>”. In this case, **hicseqScript_SRR1658581.txt** is the script that contains the analysis commands.

This command works for servers using a SLURM scheduler like Cedar, Graham or Beluga. For the PBS scheduler, used by Guillimin, you need to add the “-j pbs” option, as follows:

.. code-block:: bash

    hicseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/hicseq/hicseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readsets.HiC010.tsv -s 1-15 -e MboI -j pbs > hicseqScript_SRR1658581.txt


To run it, use:

.. code-block:: bash

    bash hicseqScript_SRR1658581.txt


You will not see anything happen, but the commands will be sent to the server job queue. **So do not run this more than once per job.**
To confirm that the commands have been submitted, wait a minute or two depending on the server and type:

.. code-block:: bash

    showq -u <userID>

In case you ran it several times and launched too many commands you do not want, you can use the following line of code to cancel ALL commands:

.. code-block:: bash

    showq -u <userID> | tr "|" " "| awk '{print $1}' | xargs -n1 canceljob

Congratulations! you just ran the hicseq pipeline.
After the processing is complete, you can access quality control plots in the homer_tag_directory/HomerQcPlots. You can find the compartment data in the compartments folder, TADs in the TADs folder and significant interactions in the peaks folder.

For more information about output formats please consult the webpage of the third party tool used.

.. note::

    The hicseq pipeline also analyzes capture hic data if the “-t capture” flag is used. For more information on the available steps in that pipeline use: **hicseq -h**

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

To see how this works, lets run a ChIP-Seq experiment.

chipseq Test Dataset:
---------------------

We will use a subset of the ENCODE data. Specifically, the reads that map to chr22 of the following samples `ENCFF361CSC <https://www.encodeproject.org/experiments/ENCSR828XQV/>`__ and `ENCFF837BCE <https://www.encodeproject.org/experiments/ENCSR236YGF/>`_. They represent a ChIP-Seq analysis dataset with the CTCF transcription factor and its control input.

We will start by downloading the dataset from `here <https://datahub-90-cw3.p.genap.ca/chipseq.chr19.new.tar.gz>`_

In the downloaded zip file, you will find the two fastq read files in folder rawData and will find the readset file (readsets.chipseqTest.chr22.tsv) that describes that dataset. You will also find the design file 

::
   
	designfile_chipseq.chr22.txt

that contains the contrast of interest.

Looking at the content of the Readset file 

::

	readsets.chipseqTest.tsv

we see:

::

	Sample Readset Library RunType Run Lane Adapter1 Adapter2 QualityOffset BED FASTQ1 FASTQ2 BAM
	ENCFF361CSC_ctrl ENCFF361CSC_chr22 SINGLE_END 2965 1 AGATCGGAAGAGCACACGTCTGAACTCCAGTCA AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT 33 rawData/ENCFF361CSC.chr22.fastq
	ENCFF837BCE_ctcf ENCFF837BCE_chr22 SINGLE_END 2962 1 AGATCGGAAGAGCACACGTCTGAACTCCAGTCA AGATCGGAAGAGCGTCGTGTAGGGAAAGAGTGT 33 rawData/ENCFF837BCE.chr22.fastq

This analysis contains 2 samples with a single readset each. They are both SINGLE_END runs and have a single fastq file in the “rawData” folder.

Looking at the content of the Design file

::

	designfile_chipseq.txt)

we see:

::

	Sample CTCF_Input,N
	ENCFF361CSC_ctrl 1
	ENCFF837BCE_ctcf 2

We see a single analysis CTCF_Input run as Narrow peaks (coded by “N”; you can use “B” for broad peak analysis). This analysis compares CTCF peaks in ENCFF837BCE_ctcf to its input control peaks identified from ENCFF361CSC_ctrl.

We will run this analysis on Beluga server as follows:

.. code-block:: bash

    chipseq.py -c $MUGQIC_PIPELINES_HOME/pipelines/chipseq/chipseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readsets.chipseqTest.chr22.tsv -d designfile_chipseq.chr22.txt -s 1-15 > chipseqScript.txt
    bash chipseqScript.txt

The commands will be sent to the job queue and you will be notified once each step is done. If everything runs smoothly, you should get **MUGQICexitStatus:0** or **Exit_status=0**. If that is not the case, then an error has occurred after which the pipeline usually aborts. To examine the errors, check the content of the **job_output** folder.

Available pipelines:
--------------------

For more information:
---------------------
Our pipelines are built around third party tools that the community uses in particular fields. To understand the output of each pipeline, please read the documentation pertaining to the tools that produced the output.

For more information or help with particular pipelines, you can send us an email to:
`info@computationalgenomics.ca <info@computationalgenomics.ca>`_

Or drop by during our `Open Door <https://www.computationalgenomics.ca/open-door/>`_ slots.  We are located at:

*740 Dr. Penfield avenue, room 4200
Montréal, QC H3A 1A5*
