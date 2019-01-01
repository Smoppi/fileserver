find filut/ -name "*.tar.bz2" -type f -exec sh -c 'echo "                    A" $1 | cut -c 1-21,29-' _ {} \; -exec tar -jtvf {}  \; -exec echo "                    e"  \; | cut -c 21- > tarbz2archive_filelist2.txt
echo "E" >> tarbz2archive_filelist2.txt
cp tarbz2archive_filelist2.txt tarbz2archive_filelist.txt
