::

  genpipes rnaseq_light.py -c $MUGQIC_PIPELINES_HOME/pipelines/rnaseq_light/rnaseq_light.base.ini $MUGQIC_PIPELINES_HOME/pipelines/common_ini/beluga.ini -r readset.rnaseq.txt -d design.rnaseq.txt -s 1-25 -g rnaseqCommands.sh

  bash rnaseqCommands.sh