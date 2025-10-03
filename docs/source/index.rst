.. .. codeauthor:: Shaloo Shalini <shaloo_shalini@yahoo.com>

GenPipes v\ |genpipes_version|\  Documentation
==============================================


   **GenPipes** is a flexible *Python-based framework* to facilitates the development and deployment of multi-step *genomic workflows*, optimized for *High-Performance Computing (HPC) clusters* and the *cloud.* 

.. grid:: 2

    .. grid-item-card:: 

        GenPipes offers open-source, validated and scalable :ref:`gene sequencing pipelines<docs_pipeline_ref>` for various :ref:`genomics applications<docs_gp_usecases>`. 

        This documentation is meant for **new genomics users** as well as the **seasoned ones**. 
        
        We welcome all community :ref:`contributions<docs_contributing>` to GenPipes including this documentation. 
        
        See :ref:`Documentation Map<docs_genpipes_archmap>` for more information on how this documentation is organized.      
        
    .. grid-item-card:: 

        .. dropdown:: :material-outlined:`dangerous;2em` DRAC Server Availability
            :color: danger

            .. include:: /server_narval.inc 

        .. dropdown:: :material-outlined:`bolt;2em` Usage Changes (from v5.x)
            :color: success

            .. include:: gp5_0.inc

        .. dropdown:: :material-outlined:`handshake;2em` Sponsors
            :color: info

            GenPipes is an open-source genomics workflow and next generation gene sequencing pipeline platform. It is developed and financed by the `Canadian Centre for Computational Genomics <https://www.computationalgenomics.ca>`_ (C3G).

            C3G, a core platform affiliated with `McGill University <https://www.mcgill.ca>`_, provides bioinformatics analysis and HPC services for life sciences research. 

            These services include:
            
            * Bespoke pipeline development
            * Fee-based analyses
            * Other suite of software solutions genomics  

        .. dropdown::  :material-outlined:`coronavirus;2em` Fighting COVID-19
            :color: secondary

            GenPipes offers two pipelines: :ref:`CoVSeq<docs_gp_covseq>` for short-read sequencing (e.g., Illumina) and :ref:`Nanopore_CoVSeq<docs_gp_nanopore_cov>` for long-read sequencing. These pipelines help researchers analyze viral sequences and detect mutations quickly, preventing the spread of new strains.

        .. dropdown::  :material-outlined:`fiber_new;2em` GenPipes Wizard
            :color: warning

            Use the :ref:`GenPipes Wizard <docs_gp_wizard>` to quickly run genomic analysis, discover the appropriate deployment method, pipeline, protocol options.

.. grid:: 3

    .. grid-item-card:: 

        .. toctree::
            :maxdepth: 1
            :caption: Overview 
            :name: sec-general

            about/index
            get-started/gp_usecases
            faq/gp_faq

    .. grid-item-card:: 

         .. toctree::
            :maxdepth: 1
            :caption: Get Started
            :name: sec-learn

            deploy/how_to_deploy_genpipes
            get-started/index
            user_guide/user_guide
            tutorials/list_tutorials

    .. grid-item-card:: 

         .. toctree::
            :maxdepth: 1
            :caption: Support
            :name: sec-support

            support/how_to_get_support
            user_guide/gp_wizard

.. grid:: 3

    .. grid-item-card:: 

         .. toctree::
            :maxdepth: 1
            :caption: Community
            :name: sec-community

            community/channels
            community/contributing

    .. grid-item-card:: 

         .. toctree::
            :maxdepth: 1
            :caption: Resources
            :name: sec-resources

            resources/citation
            resources/publications
            resources/workshops
            resources/testdataset
            resources/compute_resources

    .. grid-item-card:: 

         .. toctree::
            :maxdepth: 1
            :caption: Development
            :name: sec-devel

            development/release_notes
            development/gp_release_instructions
            development/dev_guide
            development/troubleshooting_guide

.. grid:: 3

    .. grid-item-card:: 


    .. grid-item-card:: 

         .. toctree::
            :maxdepth: 1
            :caption: Documentation
            :name: sec-documentation

            documentation/about
            documentation/genpipes_doc_archmap
            documentation/docs_changelog

    .. grid-item-card:: 


.. Indices and tables
.. ------------------
..
.. * :ref:`genindex`
.. * :ref:`modindex`
.. * :ref:`search`

.. _GitHub Issue 110: https://github.com/c3g/GenPipes/issues/110
