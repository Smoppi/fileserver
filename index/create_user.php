<?php

include('header.htm');
include('inc/createuser.inc');

if(isset($_GET['createuser']))
{
  if(isset($_POST['user']) && $_POST['user'] != "")
  {
    $username = $_POST['user'];
    if(isset($_POST['pass']) && isset($_POST['pass2']))
    {
      $password = $_POST['pass'];
      $passrepeat = $_POST['pass2'];
      if($password == $passrepeat)
      {
        if(strlen($password) >= 6)
        {
          if(strlen($username) <= 36)
          {
            create_user($username, $password);
          }
          else
            echo "The username you entered is too long. Maximum length is 36 characters.";
        }
        else
          echo "The password you entered is too short. Minimum length is 6 characters.";
      }
      else
        echo "You entered different passwords.";
    }
    else
      echo "You entered an empty password.";
  }
  else
    echo "You entered an empty username.";

}

?>

<h2>Register</h2><br><br>
<form action = "?createuser" method = "post">
Username: <input type = "text" name = "user" class = "tekstilaatikko"><br>
Password: <input type = "password" name = "pass" class = "tekstilaatikko"><br>
Retype password: <input type = "password" name = "pass2" class = "tekstilaatikko">
<input type = "submit" value = "Create account" class = "nappi">
</form>

<?php include('footer.htm'); ?>
