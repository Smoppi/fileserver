find filut/ -name "*.tar.gz" -type f -exec sh -c 'echo "                    A" $1 | cut -c 1-21,29-' _ {} \; -exec tar -ztvf {}  \; -exec echo "                    e"  \; | cut -c 21- > targzarchive_filelist2.txt
echo "E" >> targzarchive_filelist2.txt
cp targzarchive_filelist2.txt targzarchive_filelist.txt
