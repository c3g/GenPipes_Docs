.. _docs_troubleshooting_rt_rap_id_notset:

Error: RAP_ID not set
----------------------

If you try to run GenPipes deployed by C3G on Compute Canada servers, the initial run shows error related to RAP_ID not set. Sometimes, this same issue manifests in the form of timing error as shown in figure below:

.. figure:: /img/error/rap_id_error.png
   :align: center
   :alt: rap_id error 

   Figure:  Error encountered if RAP_ID not set or set incorrectly

**Fix**

Make sure you have updated your .bashrc file as directed in :ref:`setting_up_gp_environment_modules`.  Once you set up the correct RAP_ID when you run the bash commands for your pipeline, they all go through and get scheduled depending on the scheduler (default or as as specified by -j option in pipeline command)
