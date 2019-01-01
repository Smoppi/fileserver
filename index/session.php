<?php

if(isset($user_message))
  die ($user_message . "</body></html>");

#jos keksiä ei ole eikä olla kirjautumissivulla

$uris_without_login = array($index_request_dir . '/index/login.php',
  $index_request_dir . '/index/create_user.php',
  $index_request_dir . '/index/create_user.php?createuser');

if(!isset($loginname) && !in_array($_SERVER['REQUEST_URI'], $uris_without_login))
{
  #ilmoitetaan sisäänkirjautumisvaatimus
  die('You must be logged in! <a href = "login.php">Click here</a> to log in. If you do not have an account, click <a href = "create_user.php">here</a> to create account.</body></html>');
}

#jos keksi on jo annettu, annetaan uloskirjauslinkki

  if(isset($loginname) && $loginname)
    echo 'Logged in as ' . htmlspecialchars($loginname) . '. <a href = "?logout">Log out</a> | <a href = "newpass.php">Change password</a> | <a href = "upload.php">Upload a file</a>';

?>
