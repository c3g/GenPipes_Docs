:orphan:

.. _docs_bed_file:

BED file format
================
Browser Extensible Data (BED) is a high throughput gene sequencing file format. It contains region-based genome annotation information, often used for visualization. 

BED format provides a flexible way to define the data lines that are displayed in an annotation track. BED lines have three required fields and nine additional optional fields. The number of fields per line must be consistent throughout any single set of data in an annotation track. The order of the optional fields is binding: lower-numbered fields must always be populated if higher-numbered fields are used.

If your data set is BED-like, but it is very large (over 50MB) and you would like to keep it on your own server, you should use the bigBed data format.

The first three required BED fields are:

* **chrom** - The name of the chromosome (e.g. chr3, chrY, chr2_random) or scaffold (e.g. scaffold10671).

* **chromStart** - The starting position of the feature in the chromosome or scaffold. The first base in a chromosome is numbered 0.

* **chromEnd** - The ending position of the feature in the chromosome or scaffold. The chromEnd base is not included in the display of the feature. For example, the first 100 bases of a chromosome are defined as chromStart=0, chromEnd=100, and span the bases numbered 0-99.

There are 9 additional optional BED fields. You may refer to `BED format details <http://genome.ucsc.edu/FAQ/FAQformat.html#format1>`_ for examples and information on optional fields.
