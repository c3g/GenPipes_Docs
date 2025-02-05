.. caution::
                            
    **The -p option is mandatory for running the following protocols:**
    
    * `somatic_fastpass`
    * `somatic_ensemble`
    * `somatic_sv`
    
    The pair file specified via the -p option is a comma-separated file with the following format:

    <patient_name>,<normal_sample_name>,<tumor_sample_name>

    The patient name value specified in the first column of the pair file (the patient/sample pair name) must be unique. You can specify multiple patients/sample pairs data, one per line, in the pair file.

    For example:

    ::
        
        tumorPair_CEPHmixture_chr19,tumorPair_CEPHmixture_chr19_normal,tumorPair_CEPHmixture_chr19_tumor
        john_doe_tumorPair_CEPHmixture_chr19,john_doe_tumorPair_CEPHmixture_chr19_normal,john_doe_tumorPair_CEPHmixture_chr19_tumor

        ...