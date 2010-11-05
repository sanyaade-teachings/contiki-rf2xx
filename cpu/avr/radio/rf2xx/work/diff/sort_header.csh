#!/bin/tcsh -f
cat  $argv[1] | /bin/grep "\#.*define" | sort > $argv[2]
