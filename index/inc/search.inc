<?php

function search_new($keyword)
{
  global $site_dir;
  echo shell_exec($site_dir . "/search_files " . $site_dir . "/find_filelist.txt " . escapeshellarg($keyword));
}

?>
