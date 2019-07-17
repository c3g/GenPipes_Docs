:orphan:

.. _docs_config_ini_file:

Configuration File
==================

.. spelling::
   
   extention
   ini

GenPipes pipelines are multi-step pipelines that run several tools, each with its own parameter inputs. All those parameters are stored in configuration files with .ini extension. Those files have a structure similar to Microsoft Windows INI files, where parameters are divided within sections.


.. note:: **Why does GenPipes need configuration file?**

          An ini file is a file that contains parameters needed to run a pipeline.  Our genome alignment pipeline contains over 20 steps, each involving over 5 parameters per step. Imagine having to type all 100 parameters to run a pipeline! For simplicity, all the parameters are stored in an “ini” file (extention.ini) that accompanies the pipeline. 

          Try opening an ini file in a text editor and look at its content!
