<?php

include('header.htm');
include('inc/createuser.inc');

if (isset($_GET['changepw']))
  new_password($loginname, $_POST['newpass1'], $_POST['newpass2']);

?>

<form action = "?changepw" method = "post">
Old password: <input type = "password" name = "oldpass" class = "tekstilaatikko"><br>
New password: <input type = "password" name = "newpass1" class = "tekstilaatikko"><br>
Retype new password: <input type = "password" name = "newpass2" class = "tekstilaatikko"><br>
<input type = "submit" value = "ok" class = "nappi">
</form>

<?php include ('footer.htm'); ?>
