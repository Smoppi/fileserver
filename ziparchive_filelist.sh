find filut/ -name "*.zip" -exec sh -c 'echo "A" $1 | cut -c 1,9-' _ {} \; -exec unzip -lqq {} \; -exec echo "e" \; > ziparchive_filelist2.txt
cp ziparchive_filelist2.txt ziparchive_filelist.txt
