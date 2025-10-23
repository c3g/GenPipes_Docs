.. _docs_dev_guide:

.. spelling:word-list::
      dev

Developer Guide
================

GenPipes is an open-source (`LGPL <https://github.com/c3g/GenPipes/blob/main/COPYING.LESSER>`_) Python-based *next generation sequencing (NGS)* platform for managing genomics workflows. This guide provides information for developers who are interested in contributing to the GenPipes source or identify and fix bugs.


Prerequisites
-------------

* Python 3.11.x or higher 
* Command line Linux tooling
* Familiar with HPC, Cloud, deploying and using Python packages
* Schedulers: Slurm, PBSPro, others
* GitHub CI/CD processes
* Bioinformatics gene sequencing pipelines and protocols, design and readset file formats, result analysis tools

Get Started
-----------

#. Learn about how to :ref:`get involved<docs_get_involved>` with GenPipes and the process of making contributions to the project.

#. Refer to the latest :ref:`Release Notes<docs_release_notes>` to familiarize yourself with the latest GenPipes pipeline processes and protocol options.

#. Fork and get GenPipes sources via the `GitHub`_ repository.

#. Open a new GitHub issue with the suggested source modifications, new feature, bug, other changes.

#. Follow the :ref:`GenPipes Coding Guidelines<docs_gp_coding_guide>`.

#. Use a local dev branch in order to make your changes / modifications / enhancements. Validate your changes and issue a Pull Request from your fork's local dev branch to GenPipes dev branch.

#. Submit your PR along with the associated issue number (use -m "Fix: #[issue-num] when committing changes to your branch) for review by the GenPipes Dev team. If the changes are tested, working and acceptable, those will be merged into the GenPipes/dev branch.

#. For any further queries regarding contributing to GenPipes, refer to `README.md`_ file. 

.. External References

.. _GitHub: https://github.com/c3g/GenPipes
.. _README.md: https://github.com/c3g/GenPipes/blob/main/README.md