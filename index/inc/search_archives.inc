<?php

function search($keyword)
{
  global $site_dir;

  echo '<font color = "green"><br>';
  echo "Searching from .ZIP files.<br>";
  echo shell_exec($site_dir . '/search_zip ' . $site_dir . '/ziparchive_filelist.txt ' . escapeshellarg($keyword));
  echo '<br><br>Searching from .TAR.GZ files.<br>';
  echo shell_exec($site_dir . '/search_targz ' . $site_dir . '/targzarchive_filelist.txt ' . escapeshellarg($keyword));
  echo '<br><br>Searching from .TAR files.<br>';
  echo shell_exec($site_dir . '/search_targz ' . $site_dir . '/tararchive_filelist.txt ' . escapeshellarg($keyword));
  echo '<br><br>Searching from .TAR.BZ2 files.<br>';
  echo shell_exec($site_dir . '/search_targz ' . $site_dir . '/tarbz2archive_filelist.txt ' . escapeshellarg($keyword));
}

?>
