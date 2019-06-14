# GenPipes
GenPipes Read the Docs repository

_Watch out this space for updates, we are working on bringing you latest GenPipes documentation via_ [Read The Docs](http://readthedocs.org)

# RTD hosting
At present, we are hosting draft version of GenPipes docs on RTD https://genpipes.readthedocs.io/en/latest/

This repository is work in progress.  

# How to build GenPipes docs locally on your system for documentation development

Step 1:  Please make sure you have Sphinx, VirtualEnv installed locally.  Refer to requirements.txt for more details on dependencies.

Step 2:  Git Clone the sources. Use the following commands to build html version of docs.

cd docs 
make BUILDDIR=[directory location where html docs will be built] html

If you make any changes to the docs, please ensure you verify spelling. Use the following command to check spellings.


make BUILDDIR=[directory location where html docs will be built] spelling
