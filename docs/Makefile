# Makefile for Sphinx based GenPipes documentation 
# This documentation is hosted on Read the Docs https://readthedocs.org
#

# You can set these variables from the command line.
SPHINXOPTS    =
SPHINXBUILD   = sphinx-build
SOURCEDIR     = source
BUILDDIR      = build
PAPER         = 

.PHONY: help html Makefile

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

download:
#@( shell cp ../../mugqic/readme.md ./source/user_guide/pipelines/gp_readme.md)
#	@$(shell curl -s https://bitbucket.org/mugqic/genpipes/downloads/?tab=tags | grep -m 1 "/mugqic/genpipes/get/" | grep -E -o ".{0,6}zip." | head -n 1 | cut -c1-5 > VERSION)
	@$(shell curl -s https://bitbucket.org/mugqic/genpipes/downloads/ | grep "genpipes-5" |  grep -E -o ".{0,9}.gz"  |head -n 1 | cut -c1-5 > VERSION)

usage:
	@$(shell curl -s https://datahub-90-cw3.p.genap.ca/testCommands.txt > source/resources/testCommands.txt)

workflow:
	@$(shell curl -s https://bitbucket.org/mugqic/genpipes/raw/master/resources/workflows/GenPipes_methylseq.png > source/img/pipelines/wgs_methylseq.png)
	@$(shell curl -s https://bitbucket.org/mugqic/genpipes/src/master/resources/workflows/GenPipes_tumor_pair_fastpass.png > source/img/pipelines/GenPipes_tumor_pair_fastpass.png)
	@$(shell curl -s https://bitbucket.org/mugqic/genpipes/src/master/resources/workflows/GenPipes_tumor_pair_sv.png > source/img/pipelines/GenPipes_tumor_pair_sv.png)
	@$(shell curl -s https://bitbucket.org/mugqic/genpipes/src/master/resources/workflows/GenPipes_tumor_pair_ensemble.png > source/img/pipelines/GenPipes_tumor_pair_ensemble.png)

html:
	@echo "Making html docs"
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
	@echo
	@echo "GenPipes documentation build finished. The HTML pages are in $(BUILDDIR)/html."

spelling:
	@$(SPHINXBUILD) -M spelling "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
	@echo "Checking spelling..."
	@test ! -s $(BUILDDIR)/spelling/output.txt

postmake:
	@$(shell rm -rf source/resources/testCommands.txt)

#  Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
