.. _docs_gp_wizard:

.. spelling:word-list::

     cpu


.. comment
   .. raw:: html

     <span class="my-custom-banner">New</span>
   
GenPipes Wizard :bdg-warning:`New`
===================================

The GenPipes Wizard is an interactive command-line tool designed to guide users, especially beginners, through selecting the appropriate deployment method, pipeline, and protocol, and constructing the full command to run GenPipes. The Wizard works by asking a series of step-by-step questions.

How to Use the Wizard
---------------------

**Usage**

To launch the GenPipes Wizard, run:

.. code-block:: bash

   genpipes tools wizard

This will launch an interactive prompt where you can get help choosing a deployment option, pipeline and protocol and generate a ready-to-run GenPipes command.

Example Run
-----------

.. note::

   Add example image once Wizard tool is finalized.

Supported Pipelines and Protocols
---------------------------------

The Wizard currently supports the following pipelines and protocols:

.. dropdown:: Amplicon Sequencing Pipeline

   This pipeline has no protocol.
   
   For more details on this pipeline refer to the :ref:`Amplicon Sequencing Pipeline Reference Guide <docs_gp_ampliconseq>`

.. dropdown:: ChIP Sequencing Pipeline

   Protocols: ``chipseq``, ``atacseq``

   For more details on this pipeline refer to the :ref:`ChIP Sequencing Pipeline Reference Guide <docs_gp_chipseq>`

.. dropdown:: CoV Sequencing Pipeline

   This pipeline has no protocol.

   For more details on this pipeline refer to the :ref:`CoV Sequencing Pipeline Reference Guide <docs_gp_covseq>`

.. dropdown:: DNA Sequencing Pipeline

   Protocols: ``germline_snv``, ``germline_sv``, ``germline_high_cov``, ``somatic_tumor_only``, ``somatic_fastpass``, ``somatic_ensemble``, ``somatic_sv``

   For more details on this pipeline refer to the :ref:`DNA Sequencing Pipeline Reference Guide <docs_gp_dnaseq>`

.. dropdown:: Long Read DNA Sequencing Pipeline

   Protocols: ``nanopore``, ``revio``

   For more details on this pipeline refer to the :ref:`Long Read DNA Sequencing Pipeline Reference Guide <docs_gp_longread_dnaseq>`

.. dropdown:: Methylation Sequencing Pipeline

   Protocols: ``bismark``, ``gembs``, ``dragen``, ``hybrid``

   For more details on this pipeline refer to the :ref:`Methylation Sequencing Pipeline Reference Guide <docs_methylation>`

.. dropdown:: Nanopore CoVSeQ Pipeline

   Protocols: ``default``, ``basecalling``

   For more details on this pipeline refer to the :ref:`Nanopore CoVSeQ Pipeline Reference Guide <docs_gp_nanopore_cov>`

.. dropdown:: RNA Sequencing Pipeline

   Protocols: ``stringtie``, ``variants``, ``cancer``

   For more details on this pipeline refer to the :ref:`RNA Sequencing Pipeline Reference Guide <docs_gp_rnaseq>`

.. dropdown:: RNA Sequencing (De Novo) Pipeline

   Protocols: ``trinity``, ``seq2fun``

   For more details on this pipeline refer to the :ref:`RNA Sequencing Pipeline Reference Guide <docs_gp_rnaseq_denovo>`

.. dropdown:: RNA Sequencing (Light) Pipeline

   This pipeline has no protocol.

   For more details on this pipeline refer to the :ref:`RNA Sequencing Pipeline Reference Guide <docs_gp_rnaseqlight>`

Wizard Command Options
----------------------

The Wizard helps you construct a complete command to run GenPipes by asking a series of guided questions. It is designed to simplify the process for beginner users by focusing on the most commonly used options.

Currently, the Wizard supports generating commands with the following options:

**-t**: Protocol name

**-c**: Config INI-style list of files; config parameters are overwritten based on files order

**-r**: Readset file

**-d**: Design file

**-p**: Pair file

**-j**: Job scheduler type

**-s**: Step range to run (e.g. '1-5', '3,6,7', '2,4-8')

**-o**: Output directory

**-g**: Commands for running the pipeline are output to this file pathname. The data specified to pipeline command line is processed and pipeline run commands are stored in GENPIPES_FILE

.. note::

   The Wizard does not support every possible GenPipes option.
   
   For advanced or pipeline-specific options, refer to the :ref:`Pipeline Reference Guide <docs_pipeline_ref>` or run:

   .. code-block:: bash

      genpipes --help

.. dropdown:: List of unsupported options

   - -f, --force  
   - --force_mem_per_cpu  
   - --no-json  
   - --json-pt  
   - --report  
   - --clean  
   - -l  
   - --sanity-check  
   - --container  
   - --wrap  
   - -v, --version

Troubleshooting
---------------

**Q:** What if I selected the wrong option by mistake?                             

**A:** You can go back at any point during the wizard:  
   - For selection-type questions, choose the **"back"** option from the list.  
   - For input-type questions, type ``back`` and press Enter.


**Q:** How do I cancel or exit the wizard?  

**A:** Press **Ctrl+C** at any time to exit the wizard.  
   Please note that your progress will **not** be saved.
