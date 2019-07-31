.. _docs_steps_ampseq:

Step Details
-------------

Following are the various steps that are part of GenPipes Amplicon Sequencing genomic analysis pipeline:

.. _Trimmomatic16S Step:

**Trimmomatic16S Step**

MiSeq raw reads adapter & primers trimming and basic QC is performed using `Trimmomatic`_. If an adapter FASTA file is specified in the config file (section 'trimmomatic', param 'adapter_fasta'), it is used first. Else, Adapter1, Adapter2, Primer1 and Primer2 columns from the readset file are used to create an adapter FASTA file, given then to Trimmomatic. Sequences are reversed-complemented and swapped. This step takes as input files: 1. MiSeq paired-End FASTQ files from the readset file.

.. _Merge Trimmomatic Stats:

**Merge Trimmomatic Stats**

The trim statistics per readset are merged in this step.

.. _Flash Pass 1:

**Flash Pass 1**

TBD

.. _Amplicon Length Parser:

**AMplicon Length Parser**

In this step, we look at `FLASH`_ output to set amplicon lengths input for `DADA2`_. As minimum eligible length, a given length needs to have at least 1% of the total number of amplicons.

.. _Flash Pass 2:

**Flash Pass 2**

TBD

.. _Merge Flash Stats:

**Merge Flash Stats**

The paired end merge statistics per readset are merged in this step.

.. _Catenate:

**Catenate**

This step catenates all the reads in one file for further analysis. As input, it takes the merged FASTQ files from the previous FLASH step.

.. _UCHIME Step:

**UCHIME Step**

This step takes catenated FASTA file from the previous Catenate step and uses it for reference based chimera detection using `VSearch tool`_.

.. _Merge UCHIME Stats:

**Merge UCHIME Stats**

The chimeric sequences filtered out statistics per readset are merged at this step.

.. _OTU Picking:

**Operational Taxonomic Unit (OTU) Picking**

This step takes catenated FASTA file from the previous Catenate step as input. The OTU picking step (de novo & close_ref) assigns similar sequences to operational taxonomic units (OTUs) by clustering sequences based on a user-defined similarity threshold. Method per default uses the following tools:

* `VSearch tool`_
* `QIIME tool`_

.. _OTU Rep Picking:

**OTU Representative Picking**

After picking OTUs, this step pick a representative sequence for each OTU.
This step takes as input files:

- OTU file from previous step
- Catenated and filtered FASTA file from filter_chimeras step.

.. _OTU Assigning:

**OTU Assigning**

Given a set of OTUS, this step attempts to assign the taxonomy of each OTU using `Uclust algorithm`_. As input, it takes OTU representative sequence file from the previous step.

.. _OTU Table:

**OTU Table**

This step make a consensus OTU table in biom format. It tabulates the number of times an OTU is found in each sample, and adds the taxonomic predictions for each OTU.

This step takes as input files:

- OTU picking file.
- Taxonomy assignment for each OTU from the previous step.

.. _OTU Alignment:

**OTU Alignment**

OTU Alignment uses OTU representative sequence file as input and aligns the OTU representative sequence using `PyNAST tool`_.

.. _Filter Alignment:

**Filter Alignment**

This step takes the alignment sequence file as input and filters it by removing positions that are gaps in every sequence.

.. _Phylogeny:

**Phylogeny**

This step uses filtered alignment sequence file from previous step and builds a phylogenetic tree from a multiple sequence alignment using `FastTree algorithm`_.

.. _QIIME Report:

**QIIME Report**

In this step, the first part of the report for taxonomic affiliation is created.

.. _Multiple Rarefaction:

**Multiple Rarefaction**

This is the first of the four steps (1/4) for rarefaction plot. It takes OUT non-rarefied table in biom format as input. It rarefies OTU table by random sampling (without replacement) at different depth in order to perform rarefaction analysis. You need to provide the minimum/maximum number of sequences per samples and the size of each steps between the min/max of seqs/sample.

.. _Alpha Diversity:

**Alpha Diversity**

This is the second of the four steps (2/4) for rarefaction plot. It takes as input, multiple OUT rarefied table in biom format from the previous step and calculates alpha diversity on each sample using a variety of alpha diversity metrics (chao1, shannon, observed otus).

.. _Collate Alpha:

**Collate Alpha**

This is the third of the four steps (3/4) for rarefaction plot. It merges all the alpha diversity computed in the previous step.

.. _Sample Rarefaction Plot:

**Sample Rarefaction Plot**

This is the fourth and last of the four steps (4/4) for rarefaction plot. Here, rarefaction curve for each sample is plotted.

.. _QIIME Report 2:

**QIIME Report 2**

In this step, the second part of the report for taxonomic affiliation is created.

.. _Single Rarefaction:

**Single Rarefaction**

Single rarefaction takes OTU table in biom format as input. This step is recommended. It subsamples (rarefy) all the samples to an equal number of sequences for further comparison. You have to provide the number of sequences to subsample per sample in the configuration file (single_rarefaction_depth).

.. _CSS Normalization:

**CSS Normalization**

CSS Normalization takes OTU table in biom format as input. This is the alternative method for normalization to rarefaction. The CSS Matrix normalization step is recommended.


.. _Rarefaction Plot:

**Rarefaction Plot**

In this step, rarefaction curve for each sample is plotted on the same plot.

.. _Summarize Taxonomy:

**Summarize Taxonomy**

This is the first of three (1/3) steps for taxonomic affiliation plot. If available, it takes OTU rarefied table in biom format as input. Otherwise, it takes OTU non-rarefied table in biom format. It summarizes information of taxonomic groups within each sample at different taxonomic level.

.. _Plot Taxonomy:

**Plot Taxonomy**

This is the second of three (2/3) steps for taxonomic affiliation plot. It takes summarization information from the previous step as input and makes taxonomy summary  bar plot based on taxonomy assignment.

.. _Plot Heatmap:

**Plot Heatmap**

This is the third and last of three (3/3) steps for taxonomic affiliation plot. It takes summarized information from previous step and makes heatmap at phylum level.

.. _Krona:

**Krona**

This step plots the `Krona chart`_ for taxonomic affiliation.


.. _Plot to Alpha:

**Plot to Alpha**

This step generates the first part of the final report for Amplicon sequencing pipeline. The report displays results related to taxonomy, heatmap and alpha diversity.

.. _Beta Diversity:

**Beta Diversity**

This is the first of three (1/3) steps for 2D `PCoA analysis`_ plot.

It takes the following data as input files:

- OTU rarefied table in biom format
- Tree file

This step calculates beta diversity (pairwise sample dissimilarity) on OTU table. The OTU table has to be normalized.  Only works with >= 4 samples

.. _Principal Coordinate Analysis:

Principal Coordinate Analysis (`PCoA analysis`_) is the second step of three (2/3) for PCoA plot. It takes the matrix produced in the previous step and computes coordinates for PCoA.

.. _PCoA Plot:

**PCoA Plot**

This is the last of three (3/3) steps for 2D `PCoA analysis`_ plot.

.. _Plot to Beta:

**Plot to Beta**

Here the last part of the final report for Amplicon sequencing pipeline is generated. The report displays results related to beta diversity PCoA plots.

.. _ASVA:

**Asva**

TBD
This step checks for the design file (required for `PCA plots`_) 

.. Following are the html link references:

.. _Trimmomatic: http://www.usadellab.org/cms/index.php?page=trimmomatic
.. _FLASH: https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3198573/
.. _DADA2: https://benjjneb.github.io/dada2/tutorial.html
.. _VSearch tool: https://github.com/torognes/vsearch
.. _QIIME tool: http://qiime.org
.. _Uclust algorithm: http://drive5.com/usearch/manual/uclust_algo.html
.. _PyNAST tool: http://biocore.github.io/pynast/
.. _FastTree algorithm: http://www.microbesonline.org/fasttree/
.. _Krona chart: https://github.com/marbl/Krona/wiki
.. _PCoA analysis: https://link.springer.com/chapter/10.1007/978-0-387-45972-1_15
.. _PCA plots: http://www.marcottelab.org/users/BCH391L_2015/NBT_primer_PCA.pdf
