.. _docs_run_gp:

Run GenPipes
------------
.. note::
   **Have you tried the GenPipes Wizard?**
      We've developed a helpful tool: the :ref:`GenPipes Wizard <docs_gp_wizard>`. It guides users through selecting the appropriate deployment method, pipeline, and protocol, and helps construct the full command to run GenPipes.


.. dropdown:: :material-outlined:`bolt;2em` Usage Change Effective v5.x onward
   :color: success

   .. include:: /gp5_0.inc

After :ref:`selecting a GenPipes deployment option<docs_choose_gp_dep>` you must setup and configure your GenPipes environment as per your deployment choice. After you have configured it, you are ready to execute GenPipes.

First, test that GenPipes is correctly deployed and it works, without actually running a pipeline. Use :code:`genpipes <pipeline_cmd>` with the  :code:`--help` or ``-h`` option. 

For details, please refer to the Getting Started Guide :ref:`Run GenPipes section<docs_using_gp>`.

Earlier, you could run GenPipes by invoking individual <pipeline_cmd>. With the release of version 5.0.0 onwards, there is a new format to run GenPipes pipelines.

.. include:: /common/commands/change_format_5.inc
    
See :ref:`Pipeline Reference Guide<docs_pipeline_ref>` for details on how to run a specific pipeline in the *example* section. 

New users may benefit from the :ref:`GenPipes Tutorial<doc_list_tutorials>` section of this documentation that provides step by step instructions on how to execute a few sample GenPipes pipelines.  There is also a tutorial available for :ref:`running GenPipes in the cloud using Google Compute Platform<genpipes_in_the_cloud>`.

In case you run into any runtime issues or errors, do refer to :ref:`Troubleshooting GenPipes Runtime Issues<docs_troubleshooting_rt_issues>` or browse the GenPipes :ref:`Support<docs_how_to_get_support>` sections.

Happy analysis with GenPipes! We would love to hear your feedback on GenPipes or the documentation. 

:ref:`Contributions<docs_contributing>` to GenPipes or its documentation are most welcome!
