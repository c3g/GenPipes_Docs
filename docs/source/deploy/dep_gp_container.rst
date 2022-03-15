.. _docs_dep_gp_container:

.. spelling::

        supercomputing
	dropdown
        genpipes
        qsub
        sbatch
        zshrc
        macFUSE

Deploying GenPipes in a container
=================================

This document covers details on how to deploy GenPipes locally on your infrastructure using the container mechanism. For more details on other available options to deploy and access GenPipes you may refer to :ref:`GenPipes Deployment Options Page<docs_dep_options>`.

You can locally deploy GenPipes by creating a container that hosts all necessary software, configuration details to get you started with running GenPipes within the container. You only need $User privileges to deploy and use GenPipes locally in a container, no root privileges are needed for this option.

GenPipes genomic analysis tools are designed to run on supercomputing infrastructure or HPC data centres such as Compute Canada servers. However, you can generate the pipeline scripts and run smaller experiments on a server with container technology. This mechanism is useful if you are a contributor to GenPipes code or wish to add a feature of your own in the code. Containers make it easy for you to debug and develop GenPipes on your local machine, if you do not have access to GenPipes deployed on :ref:`Compute Canada servers <docs_access_gp_pre_installed>`.

Another use case where it makes sense to deploy GenPipes in a container is if you have a smaller dataset that you would like to run on your personal computer. However, since your computer does not have a job scheduler such as the SLURM or PBS that can be installed in a cluster, you will not be able to run GenPipes pipeline steps in parallel. You can run them in a sequential mode **only** through GenPipes in a container kind of deployment.

.. warning::

     GenPipes in a container allows pipeline steps run in a sequential order only as there are no schedulers such as SLURM or PBS in a container setup on a personal computer. 

Step 1: Install a compatible container technology on your local server
----------------------------------------------------------------------

GenPipes can be deployed either using `Docker <https://docs.docker.com/install/>`_ or `Singularity <https://singularity.lbl.gov/index.html>`_ based containers. Refer to the respective container technology tutorial and user manuals to deploy and check if your container setup is working locally.

Step 2: Setup a GenPipes development environment
------------------------------------------------

.. warning::

   This step is required only if you wish to make some changes or modifications to GenPipes code before running the pipelines in a container deployment on your personal computer.

   If you simply wish to run the latest GenPipes release in a container with your small dataset, you can skip this step and go to Step 3.

Once your container environment and requisite software is all setup and working, proceed to clone GenPipes somewhere locally under $HOME directory using the following command:

::

  git clone https://bitbucket.org/mugqic/genpipes $HOME/some/dir/genpipes

Add the following line to your .bashrc file:

::

  export GENPIPES_DEV_DIR=$HOME/some/dir/genpipes

.. note::

     Instead of .bashrc, use ~/.zshrc file, if your personal computer is running Mac OSX.

Next, use instructions below to start your GenPipes container.

Step 3: Setup GenPipes in the container
----------------------------------------

For Docker, use the following command:

::

  docker run --privileged -v /tmp:/tmp --network host -it -w $PWD -v $HOME:$HOME --user $UID:$GROUPS -v /etc/group:/etc/group  -v /etc/passwd:/etc/passwd  [ -v < CACHE_ON_HOST >:/cvmfs-cache/ ] c3genomics/genpipes:<TAG>

For Singularity, use the following command:

::

  singularity run [ -B < /HOST/CACHE/ >:/cvmfs-cache/  ] docker://c3genomics/genpipes:<TAG>

Please note, <TAG> refers to one of the tagged GenPipes sources as listed at `GitHub <https://github.com/c3g/genpipes_in_a_container/tags>`_ or `Docker Hub <https://hub.docker.com/r/c3genomics/genpipes/tags>`_. Choose 'Tags' to select the version that you wish to use for GenPipes.

<CACHE_ON_HOST> can be any place in your computer that can be used to store the CVMFS cache. For example,

::

  CACHE_ON_HOST="-v ~/cvmfs-cache/:/cvmfs-cache/" 

<CACHE_ON_HOST> will hold a cache for GenPipes in a container `CVMFS <https://cernvm.cern.ch/portal/filesystem>`_ system. It will hold the genomes and software that is used by GenPipes. This folder will grow with GenPipes usage. You can delete it in between usage, but keep in mind that once deleted it will need to be rebuilt by downloading data from the internet.

.. note::

     From GenPipes Release 2.X.X onward, `FUSE <https://en.wikipedia.org/wiki/Filesystem_in_Userspace>`_ needs to be installed on the host where GenPipes is deployed. This is a requirement with the container technology itself, the only dependency of the system.

If you are using a Mac computer, first you will need to install macFUSE and SSHFS from `here <https://osxfuse.github.io/>`_. In the case of Linux, Fuse typically comes preinstalled with the OS.

After installing FUSE, run the following command:

::

  docker run --rm  --device /dev/fuse --cap-add SYS_ADMIN  -v /tmp:/tmp -it -w $PWD -v $HOME:$HOME  - [ -v < CACHE_ON_HOST >:/cvmfs-cache/ ]  c3genomics/genpipes:<TAG>


Step 4: Load GenPipes dependency modules in the container
-----------------------------------------------------------

As shown in previous steps, you can initiate the container process on your machine locally. Next, you need to load GenPipes module using the following command:

::

  module load dev_genpipes

With this command, GenPipes uses whatever commit branch that has been checked out in $HOME/some/dir/genpipes directory.

*Voila! Now you can use GenPipes inside the container just like you would use it locally on a server or on Compute Canada servers.*

For each pipeline, you can get help about its usage through the help command:

::

  $MUGQIC_PIPELINES_HOME/pipelines/<pipeline_name>/<pipeline_name>.py --help

Step 5: Running GenPipes Pipelines in a container
--------------------------------------------------

Running pipelines requires other inputs such as :ref:`Configuration File<docs_config_ini_file>`, :ref:`Readset File<docs_readset_file>` and :ref:`Design File<docs_design_file>`. For details on how to run individual pipelines you can see :ref:`Running GenPipes<docs_using_gp>` or :ref:`GenPipes User Guide<docs_user_guide>`.

You need to make a note of the fact that GenPipes Pipelines use scheduler's calls (qsub, sbatch) for submitting genomic analysis compute jobs. If you plan to use GenPipes locally using your infrastructure, inside a container, you need to run the GenPipes pipeline python scripts using the "batch mode" option.  For local containerized versions of GenPipes, this is the preferred way of running the pipelines, if you don't have access to a scheduler locally such as the SLURM or PBS.  

This is how you can run GenPipes pipelines such as :ref:`DNA Sequencing Pipeline<docs_gp_dnaseq>`, refer to the command below:

::

  dnaseq.py -c dnaseq.base.ini dnaseq.batch.ini -j batch -r your-readsets.tsv -d your-design.tsv -s 1-34 -t mugqic > run-in-container-dnaseq-script.sh
   
  bash run-in-container-dnaseq-script.sh

Please note, there is a disadvantage to running GenPipes Pipelines without a scheduler.  In the batch mode, which is configured using the "-j batch" option, all the jobs would run as a batch, one after another, on a single node.  If your server is powerful enough, this might be your preferable option.  Otherwise, if you would like to take advantage of GenPipes' job scheduling capabilities, you need to install a job scheduler locally in your infrastructure so that GenPipes can work effectively.  We recommend the SLURM scheduler for GenPipes.

.. note::

    In case of any issues, you can try GenPipes :ref:`Support<docs_how_to_get_support>` or check out other :ref:`communication channels<docs_channels>` to view latest discussions around using GenPipes by the community.

    You may also want to check the latest GenPipes deployment and setup instructions listed in the `GenPipes README.md file <https://bitbucket.org/mugqic/genpipes_in_a_container/src/master/README.md>`_.
  
