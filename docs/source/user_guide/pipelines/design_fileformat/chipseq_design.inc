.. spelling:word-list::

     atac
     
.. note::  **ChIPSeq Pipeline Design File Format**

     The ChIPSeq Pipeline has two protocols: atac-seq and chip-seq. Each of these protocols requires a specific design file.

     **ChIPseq Protocol Format**

     .. code::

         Sample        MarkName        EW22_EW3_vs_EW7_TC71
         EW22          H3K27ac         1
         EW3           H3K27ac         1
         EW7           H3K27ac         2
         TC71          H3K27ac         2

     **ATACseq Protocol Format**

     .. important::

        Note that the MarkName value for ATACseq protocol should be `atac` unlike the ChIPseq protocol.

     .. code::

         Sample        MarkName        EW22_EW3_vs_EW7_TC71
         EW22          atac            1
         EW3           atac            1
         EW7           atac            2
         TC71          atac            2

     where, the numbers specify the sample group membership for this contrast:

     .. code::

           '0' or '': the sample does not belong to any group;
           '1': the sample belongs to the control group;
           '2': the sample belongs to the treatment test case group.  


     The design file only accepts 1 for control, 2 for treatment and 0 for other samples that do not need to compare. 
    
.. warning::  Incorrect Design File Format

     Please note that the first and second column in the design file must be sample name and histone mark/binding protein respectively. 
     
     **If the user specifies any value other than the permitted ones above in the design file, the pipeline will fail.**