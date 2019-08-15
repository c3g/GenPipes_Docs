.. _docs_faq_gp_dev:

GenPipes Developers
-------------------

Pytest command on CCDB server results in command not found error. Pytest install fails.
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

A new developer trying to setup and run GenPipes tests found the following issues:

::

  I am trying to run some python test cases using "pytest" on beluga cluster. 
  I am running into "pytest command not found " error. 

.. image:: /img/faq/pytest-err1.png

::

  I googled that error and found that it might be due to older version of setup tools.
  I tried to upgrade it and I'm seeing this error now.

.. image:: /img/faq/pytest-err2.png

**Response** 

Once your account is activated, you can login in CCDB servers such as Beluga, Cedar, Niagra.  However, these are National Systems on a shared grid and users don't have permission to install or upgrade the software there.

For more information on what software is installed on Compute Canada infrastructure, refer to `https://docs.computecanada.ca/wiki/Available_software <https://docs.computecanada.ca/wiki/Available_software>`_.
