.. warning::

     While issuing the pipeline run command, use ```-g GENPIPES_FILE``` option (see example above) instead of using the ``` > GENPIPES_FILE``` option supported by GenPipes so far, as shown below:

     ::

       [genpipes_seq_pipeline].py -t mugqic -c $MUGQIC_PIPELINES_HOME/pipelines/[genpipes_seq_pipeline]/[genpipes_seq_pipeline].base.ini $MUGQIC_PIPELINES_HOME/pipelines/[genpipes_seq_pipeline]/[genpipes_seq_pipeline].beluga.ini -r readset.[genpipes_seq_pipeline].txt -s 1-6 > [genpipes_seq_pipeline]_commands_mugqic.sh
      
       bash [genpipes_seq_pipeline]_commands_mugqic.sh

     ``` > scriptfile``` **should be considered deprecated and** ```-g scriptfile``` **option is recommended instead.**

     Please note that redirecting commands to a script ```> genpipe_script.sh``` is still supported for now. **But going forward, this mechanism might be dropped in a future GenPipes release.** 
