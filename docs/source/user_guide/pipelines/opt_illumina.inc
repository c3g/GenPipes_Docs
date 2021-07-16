::

  -d RUN_DIR, --run RUN_DIR

                        run directory

::

  --lane LANE_NUMBER    lane number

::

  -r READSETS, --readsets READSETS

                        nanuq readset file. The default file is
                        'run.nanuq.csv' in the output folder. Will be
                        automatically downloaded if not present.

::

  -i CASAVA_SHEET_FILE  illumina casava sheet. The default file is
                        'SampleSheet.nanuq.csv' in the output folder. Will be
                        automatically downloaded if not present

::

  -x FIRST_INDEX        first index base to use for demultiplexing
                        (inclusive). The index from the sample sheet will be
                        adjusted according to that value.

::

  -y LAST_INDEX         last index base to use for demultiplexing (inclusive)

::

  -m NUMBER_OF_MISMATCHES

                        number of index mistmaches allowed for demultiplexing
                        (default 1). Barcode collisions are always checked.

::

  -w, --force-download  force the download of the samples sheets (default:
                        false)
