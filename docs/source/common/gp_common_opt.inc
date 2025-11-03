.. code-block:: bash

    -h                        show this help message and exit

.. code-block:: bash

    --help                    show detailed description of pipeline and steps

.. code-block:: bash

    -c CONFIG [CONFIG ...], 
    --config CONFIG [CONFIG ...]

                            config INI-style list of files; config parameters
                            are overwritten based on files order

.. code-block:: bash

    -s STEPS, --steps STEPS   step range e.g. '1-5', '3,6,7', '2,4-8'

.. code-block:: bash

    -o OUTPUT_DIR, --output-dir OUTPUT_DIR

                            output directory (default: current)

.. code-block:: bash

    -j {pbs,batch,daemon,slurm}, 
    --job-scheduler {pbs,batch,daemon,slurm}

                            job scheduler type (default: slurm)

.. code-block:: bash

    -f, --force               force creation of jobs even if up to date (default:
                              false)

                              Take the mem input in the ini file and force to have a 
                              minimum of mem_per_cpu by correcting the number of cpu 
                              (default: None)

.. code-block:: bash

    --force_mem_per_cpu       FORCE_MEM_PER_CPU

                              Take the mem input in the ini file and force to have a
                              minimum of mem_per_cpu by correcting the number of cpu
                              (default: None)

.. commenting out this option deprecated #306
.. .. code-block:: bash

..  --no-json                 do not create JSON file per analysed sample to track
..                            the analysis status (default: false i.e. JSON file
..                            will be created)

.. code-block:: bash

    --json-pt                 create JSON file for project_tracking database
                              ingestion (default: false i.e. JSON file will NOT be
                              created)

.. code-block:: bash

  - -report                   create 'pandoc' command to merge all job markdown
                              report files in the given step range into HTML, if
                              they exist; if --report is set, --job-scheduler,
                              --force, --clean options and job up-to-date status
                              are ignored (default: false)

.. code-block:: bash

    --clean                   create 'rm' commands for all job removable files in
                              the given step range, if they exist; if --clean is
                              set, --job-scheduler, --force options and job up-to-
                              date status are ignored (default: false)

                              Note: Do not use -g option with --clean, use '>' to redirect
                              the output of the --clean command option

.. code-block:: bash

    -l {debug,info,warning,error,critical}, 
    --log {debug,info,warning,error,critical}

                            log level (default: info)

.. code-block:: bash

    --sanity-check            run the pipeline in `sanity check mode` to verify 
                              all the input files needed for the pipeline to run
                              are available on the system (default: false)

.. code-block:: bash

    --container {wrapper, singularity} <IMAGE PATH> 

                            run pipeline inside a container providing a container
                            image path or accessible singularity hub path

.. code-block:: bash

    --wrap [WRAP]             path to the GenPipes cvmfs wrapper script (default:
                              genpipes/ressources/container/bin/container_wrapper.sh,
                              a convenience option for using GenPipes in a container)
                      
.. code-block:: bash

    -v, --version             show the version information and exit

.. include:: /common/gp_cmd_file_op.inc

.. include:: /user_guide/pipelines/notes/caution_redirect_output.inc
