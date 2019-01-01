<?php
if(isset($_GET['file']))
{
  $file = $_GET['file'];
  $fn_part = explode('/', $file);
  for($n=0;isset($fn_part[$n]);$n++)
    if(substr($fn_part[$n], 0, 1) == '.')
      die();
  $file = $file_dir . '/' . $file;

  if(file_exists($file)) {
    header('Content-Description: File Transfer');
    header('Content-Type: application/octet-stream');
    header('Content-Disposition: attachment; filename="'.basename($file).'"');
    header('Expires: 0');
    header('Cache-Control: must-revalidate');
    header('Pragma: public');
    header('Content-Length: ' . filesize($file));
    readfile($file);
    exit;
  }
}
?>

