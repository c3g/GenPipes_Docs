.. _docs_get_gp:

Get GenPipes
------------

Once you have made your :ref:`choice<docs_choose_gp_dep>` regarding GenPipes deployment option, if you chose to use C3G pre-built and deployed GenPipes setup on Compute Canada servers, you don't need to get and setup any build or code. It is already taken care of.  You simply need to start using your Compute Canada account and access the latest copy of GenPipes deployed therein.

However, f you choose to deploy GenPipes on your own instead of using the  pre-installed setup managed by C3G using Compute Canada servers, you can use either of the options listed below.  You can either obtain a downloadable GenPipes Release Build or obtain a copy of GenPipes sources and build, deploy them yourself. 

* Pre-built, packaged GenPipes via the `GenPipes Download Page`_

  - For detailed instructions on how to setup and configure GenPipes locally on your server refer to :ref:`Deploying GenPipes locally<docs_dep_gp_local>`.
  - If you wish to deploy and setup GenPipes inside a container, :ref:`see here for instructions<docs_dep_gp_container>`.
  - You can also choose to deploy GenPipes on Google Compute Cloud. :ref:`See here<docs_dep_gp_cloud>` for details.

* Build your own version of GenPipes by downloading `GenPipes Source Code`_

  - For details on GenPipes build process, see :ref:`GenPipes Developer Guide<docs_dev_guide>`. Once you generate the build, you can follow the same instructions as for using a downloadable release to setup and configure GenPipes.

.. _GenPipes Download Page: https://bitbucket.org/mugqic/genpipes/downloads/
.. _GenPipes Source Code: https://bitbucket.org/mugqic/genpipes/src/master/
