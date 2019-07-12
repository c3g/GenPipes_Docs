.. _docs_access_gp:


Accessing GenPipes
===================

There are multiple ways to access GenPipes and get started with using the genomic analysis pipelines therein.  Figure below represents the three options available to bioinformatics researchers to access GenPipes.

The infographic below represents various mechanisms that can be used to access GenPipes today.

.. image:: /img/accessing_gp.png

1. Local deployment - GenPipes in a container
2. GenPipes deployment on cloud - Google Cloud Platform (GCP)
3. GenPipes on Compute Canada infrastructure

Local deployment - GenPipes in a container
------------------------------------------

Users who would like to quickly download and try out GenPipes on their local compute and storage infrastructure can check out GenPipes in a container option.  This can be used for small scale genomic analyses using limited genome datasets.  GenPipes in a container image contains GenPipes software, common reference genomes and all that is needed to run the pre-built analysis pipelines.  Bioinformatics researchers who are not familiar with container technology may require assistance from System Administrators in deploying a local copy of GenPipes software.  For details refer to GenPipes installation guide section titled :ref:`How to deploy GenPipes<docs_how_to_deploy_genpipes>`.

GenPipes deployment on GCP
--------------------------
If you need to run large scale genomic analysis that requires resource scaling, GenPipes can be deployed and accessed from cloud.  At present, Google Compute Platform (GCP) is supported.  You may require assistance from System Administrator or your local cloud expert to install and deploy GenPipes in the cloud before you can access and run genomic analysis pipelines provided by GenPipes.  For details refer to GenPipes installation guide section titled :ref:`How to deploy GenPipes<docs_how_to_deploy_genpipes>`.

GenPipes on Compute Canada infrastructure
-----------------------------------------

Researchers who have access to Compute Canada resources need not deploy GenPipes for genomic analysis. They can simply login and access Compute Canada servers that have pre-installed stable release of GenPipes.  For details refer to :ref:`Accessing GenPipes deployment on Compute Canada infrastructure<docs_access_gp_pre_installed>`. External users who do not have access to Compute Canada data centre resources can apply for the same. Refer to `details here <http://www.computationalgenomics.ca/get-a-mammouth-account/>`_.

