.. _docs_faq_new_users:

.. spelling::

   computecanada
   Niagra
   GMail
   qsub
   sbatch

New Users
---------

To create a `new CCDB account`_, what should I fill in the form field: 'position'?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. image:: /img/faq/ccdb-position-formfield.png 

**Response**

Use the following option in the form:

:: 

  external collaborator

For the CCRI field, use the following as input:

:: 

  bws-221-01

What email ID should I use if I am an external collaborator?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

**Response**

GMail or your work ID should be fine as long as you provide the name of your institution (or college in case of students). 

My account is activated. How do I learn more about Compute Canada Servers and resources available?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

**Response**

See `Compute Canada Documentation <https://docs.computecanada.ca/wiki/Compute_Canada_Documentation>`_.

My account is activated but I cannot login into beluga-computecanada or any other node - Cedar, Niagra? What is wrong?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

**Response**

Check out the current CCDB server status `here <https://status.computecanada.ca/>`_. Many a times, not being able to log in might just be due to system unavailability.

Please note that if you try to log in 3 or more times consecutively with a wrong password, your account gets deactivated and your IP address might get blacklisted. You would need to write to `Compute Canada Support`_ to get that reversed. 

What is the best place to report GenPipes bugs?
+++++++++++++++++++++++++++++++++++++++++++++++

**Response**

The preferred way to report GenPipes bugs is on our Bitbucket issue page : https://bitbucket.org/mugqic/genpipes/issues.

You can always reach us by email at mailto:pipelines@computationalgenomics.ca or use `Google Group for GenPipes <https://groups.google.com/forum/#!forum/GenPipes>`_ for any requests.

For more details, visit :ref:`GenPipes Support<docs_how_to_get_support>` and :ref:`GenPipes Channels<docs_channels>` page in this documentation.

I was trying to use `GenPipes deployed in a Docker Container`_. What <tag> value should I use?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

**Response**

You can use the "latest" tag or one of the tags listed at `GenPipes Docker Hub: <https://hub.docker.com/r/c3genomics/genpipes/tags>`_. If you omit the <tag> Docker will use "latest" by default.

How do I run GenPipes locally in my infrastructure using a containerized setup? Is a scheduler setup necessary?
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

GenPipes pipelines use scheduler's calls (qsub, sbatch) for submitting genomic analysis compute jobs. If you plan to use GenPipes locally using your infrastructure, inside a container, you need to run the GenPipes pipeline python scripts using the "batch mode" option.  For local containerized versions of GenPipes, this is the preferred way of running the pipelines, if you don't have access to a scheduler locally such as SLURM or PBS.  

This is how you can run GenPipes pipelines such as :ref:`DNA Sequencing Pipeline<docs_gp_dnaseq>`, refer to the command below:

::

  dnaseq.py -c dnaseq.base.ini dnaseq.batch.ini -j batch -r your-readsets.tsv -d your-design.tsv -s 1-34 -t mugqic > run-in-container-dnaseq-script.sh
  
  bash run-in-container-dnaseq-script.sh

Please note, there is a disadvantage to running GenPipes Pipelines without a scheduler.  In the batch mode, which is configured using the "-j batch" option, all the jobs would run as a batch, one after another, on a single node.  If your server is powerful enough, this might be your preferable option.  Otherwise, if you would like to take advantage of GenPipes' job scheduling capabilities, you need to install a job scheduler locally in your infrastructure so that GenPipes can work effectively.  We recommend SLURM scheduler for GenPipes.

.. _new CCDB account: https://ccdb.computecanada.ca/account_application
.. _GenPipes deployed in a Docker Container: https://genpipes.readthedocs.io/en/latest/deploy/dep_gp_container.html
.. _Compute Canada Support: mailto:support@computecanada.ca
