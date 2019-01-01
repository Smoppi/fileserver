find filut/ -name "*.tar" -type f -exec sh -c 'echo "                    A" $1 | cut -c 1-21,29-' _ {} \; -exec tar -tvf {}  \; -exec echo "                    e"  \; | cut -c 21- > tararchive_filelist2.txt
echo "E" >> tararchive_filelist2.txt
cp tararchive_filelist2.txt tararchive_filelist.txt
