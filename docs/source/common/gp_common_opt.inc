::

  -h                        show this help message and exit

::

  --help                    show detailed description of pipeline and steps

::

  -c CONFIG [CONFIG ...], --config CONFIG [CONFIG ...]

                            config INI-style list of files; config parameters
                            are overwritten based on files order

::

  -s STEPS, --steps STEPS   step range e.g. '1-5', '3,6,7', '2,4-8'

::

  -o OUTPUT_DIR, --output-dir OUTPUT_DIR

                            output directory (default: current)

::

  -j {pbs,batch,daemon,slurm}, --job-scheduler {pbs,batch,daemon,slurm}

                            job scheduler type (default: slurm)

::

  -f, --force               force creation of jobs even if up to date (default:
                            false)

::

  --no-json                 do not create JSON file per analysed sample to track
                            the analysis status (default: false i.e. JSON file
                            will be created)

::

  --report                  create 'pandoc' command to merge all job markdown
                            report files in the given step range into HTML, if
                            they exist; if --report is set, --job-scheduler,
                            --force, --clean options and job up-to-date status
                            are ignored (default: false)

::

  --clean                   create 'rm' commands for all job removable files in
                            the given step range, if they exist; if --clean is
                            set, --job-scheduler, --force options and job up-to-
                            date status are ignored (default: false)

                            Note: Do not use -g option with --clean, use '>' to redirect
                            the output of the --clean command option

::

  -l {debug,info,warning,error,critical}, --log {debug,info,warning,error,critical}

                            log level (default: info)

::

  --sanity-check            run the pipeline in `sanity check mode` to verify 
                            all the input files needed for the pipeline to run
                            are available on the system (default: false)

::

  --container {wrapper, singularity} <IMAGE PATH> 

                            run pipeline inside a container providing a container
                            image path or accessible singularity hub path

::

  -v, --version             show the version information and exit

::

  -g GENPIPES_FILE, --genpipes_file GENPIPES_FILE

                            Commands for running the pipeline are output to this
                            file pathname. The data specified to pipeline command 
                            line is processed and pipeline run commands are 
                            stored in GENPIPES_FILE, if this option is specified
                            . Otherwise, the output will be redirected to stdout
                            . This file can be used to actually "run the 
                            GenPipes Pipeline"

                            Note: Do not use -g option with -clean. Use '>' to redirect
                            the output to a file when using -clean option.
