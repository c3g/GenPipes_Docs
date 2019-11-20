# GenPipes
_This is the source code repository for GenPipes Documentation._

The latest GenPipes documentation is now hosted via [Read The Docs](http://readthedocs.org). You can refer to it at the link https://genpipes.readthedocs.io/en/latest/.

If you make any changes to the GenPipes documentation sources, the updates will show up on Read The Docs links above once they are merged into the master branch.

This documentation was created as part of Google's first [Seasons of Docs](https://developers.google.com/season-of-docs/docs/participants) project. If you have any comments of feedback, you can write to Rola Dali or Mathieu Bourgey at gsod@computationalgenomics.ca 

# How to Contribute to GenPipes?

If you wish to contribute to this documentation, see [GenPipes Contribution Guide](https://genpipes.readthedocs.io/en/latest/community/contributing.html).

# Building documentation sources locally 

**Step 1:**  Please make sure you have Sphinx, VirtualEnv installed locally.  Refer to requirements.txt for more details on dependencies.

**Step 2:**  Git Clone the sources. Use the following commands to build html version of docs.

```
cd docs 
make html
```

By default, html documentation is generated in _build directory. You can change the location of build directory using the following command:

```
cd docs 
make BUILDDIR=[directory location where html docs will be built] html
```

>  If you make any changes to the docs, please ensure you verify spelling.
>  Use the following command to check spellings.

```
make BUILDDIR=[directory location where html docs will be built] spelling
```

For building PDF version of the documentation, use the following instructions:

```
make latexpdf
```

Please note, you need to have texlive-full package and latexmk command installed on the machine where you are issuing this make latexpdf command.
