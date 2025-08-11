# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source
BUILDDIR      = build

# Mermaid CLI settings
MMDC          = ./node_modules/.bin/mmdc
SCHEMA_DIR    = $(SOURCEDIR)/schema

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

# Target to ensure node_modules exists and mermaid-cli is installed
node_modules:
	@if [ ! -d "node_modules" ]; then \
		echo "Installing @mermaid-js/mermaid-cli..."; \
		npm install @mermaid-js/mermaid-cli; \
	else \
		echo "node_modules already exists"; \
	fi

# Target to generate PNG files from Mermaid diagrams
mermaid: node_modules
	@echo "Generating PNG files from Mermaid diagrams..."
	@mkdir -p $(BUILDDIR)/html/mmd
	@find $(SCHEMA_DIR) -name "*.mmd" -type f | while read file; do \
		filename=$$(basename "$$file" .mmd); \
		echo "Processing $$file -> $(BUILDDIR)/html/mmd/$$filename.mmd.png"; \
		$(MMDC) -i "$$file" -o "$(BUILDDIR)/html/mmd/$$filename.mmd.png" -s 2 -w 1200 -t neutral -b transparent; \
		if command -v magick >/dev/null 2>&1; then \
			echo "Adding title to $(BUILDDIR)/html/mmd/$$filename.mmd.png"; \
			magick "$(BUILDDIR)/html/mmd/$$filename.mmd.png" -gravity North -pointsize 30 -fill black -annotate +0+20 "$$filename" "$(BUILDDIR)/html/mmd/$$filename.mmd.titled.png"; \
			mv "$(BUILDDIR)/html/mmd/$$filename.mmd.titled.png" "$(BUILDDIR)/html/mmd/$$filename.mmd.png"; \
		else \
			echo "ImageMagick not found, skipping title addition for $$filename.mmd.png"; \
		fi; \
	done

# Target to clean generated PNG files
clean-mermaid:
	@echo "Cleaning generated Mermaid PNG files..."
	@rm -rf $(BUILDDIR)/html/mmd

.PHONY: help Makefile node_modules mermaid clean-mermaid

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@if [ "$@" != "clean" ] && [ "$@" != "clean-mermaid" ] && [ "$@" != "help" ] && [ "$@" != "node_modules" ] && [ "$@" != "mermaid" ]; then \
		echo "Generating Mermaid diagrams..."; \
		$(MAKE) mermaid; \
	fi
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)
