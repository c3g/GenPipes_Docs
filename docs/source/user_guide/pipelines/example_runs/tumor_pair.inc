::

  python tumor_pair.py -c $MUGQIC_PIPELINES_HOME/pipelines/dnaseq/dnaseq.base.ini $MUGQIC_PIPELINES_HOME/pipelines/tumor_pair/tumor_pair.base.ini $MUGQIC_PIPELINES_HOME/pipelines/tumor_pair/tumor_pair.guillimin.ini -r readset.tumorPair.txt -p pairs.csv -s 1-44 -g tumor_pairCommands.sh

  bash tumor_pairCommands.sh
