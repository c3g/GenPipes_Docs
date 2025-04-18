#!/bin/bash

`ls /cvmfs/soft.mugqic/CentOS6/modulefiles/mugqic/* > input.log`

# Process the log file
awk -F'/' '
BEGIN {
    print "+------------------------------+----------------------------------+";
    print "| Module Name                  | Version(s)                       |";
    print "+==============================+==================================+";
}
/^[[:space:]]*$|^[[].*]/ {next} /^\/.*:/ {
    module=$NF; version_count=0; versions[0]="";
    while (getline && $0 !~ /^\/|^[[].*]|^[[:space:]]*$/) {
        versions[version_count]=$1;
        version_count++;
    }
    if (version_count == 0) {
        printf "| %-28s | %-32s |\n", module, "N/A";
        print "+------------------------------+----------------------------------+";
    } else {
        for (i=0; i<version_count; i++) {
            if (i == 0) {
                printf "| %-28s | %-32s |\n", module, versions[i];
            } else {
                printf "| %-28s | %-32s |\n", "", versions[i];
            }
            print i == version_count-1 ? "+------------------------------+----------------------------------+" : "|                              +----------------------------------+";
        }
    }
}
END {
    print "";
    print "Last updated: " strftime("%Y-%m-%d %H:%M:%S UTC", systime(), 1);
}' input.log > output.log
