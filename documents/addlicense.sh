#!/bin/bash  
for x in $*; do  
head -$LICENSELEN $x | diff preamble.txt - || ( ( cat preamble.txt; echo; cat $x) > /tmp/file;  
mv /tmp/file $x )  
done  

# find . -type f -iregex '.*?\.cpp' -print0 | xargs -0 ./addlicense.sh 
