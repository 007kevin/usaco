#!/bin/bash

############################################
#### Recursively delete all temp files  ####
############################################
echo "Executing cleanup script: "
exec=$(find . -perm /+x -type f ! -name "cleanup.sh" -type d)
in=$(find . -name "*.in" -type f)
out=$(find . -name "*.out" -type f)
if [[ $exec ]] || [[ $in ]] || [[ $out ]]; then
    find . -perm /+x -type f ! -name "cleanup.sh" -type d
    find . -name "*.in" -type f
    find . -name "*.out" -type f
    read -p "Delete these files? " -n 1 -r
    if [[ $REPLY =~ ^[Yy]$ ]]
    then
        find . -perm /+x -type f ! -name "cleanup.sh" -type d -delete
        find . -name "*.in" -type f -delete
        find . -name "*.out" -type f -delete
    fi
else
    echo "Nothing to clean up"
fi
