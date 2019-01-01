<?php
include("inc/settings.php");
include("inc/check_login.inc");

if(isset($loginname) && $loginname)
  include("inc/download.inc");
else
  echo "You are not logged in. :(";
?>
