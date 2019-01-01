<?php

function salthash_password($password, $salt)
{
//  $algorthm = "sha512"; // this must be the safest hashing algorithm supported by the system
  global $algorthm;
  $hash = hash($algorthm, $password . $salt);
  return $hash;
}

function new_password($username, $password, $password2)
{
  if($password == $password2)
  {
    global $dbhost, $dbuser, $dbpass, $mysql_db, $mysql_table, $debug;
    $salt = shell_exec("./random_salt 512 a"); // generates a 512 chars long base95 salt
    $pwhash = salthash_password($password, $salt);
    $conn = mysqli_connect($dbhost, $dbuser, $dbpass, $mysql_db);
    if(!$conn && $debug)
      die("Error: Unable to connect to MySQL.");
    $username = mysqli_real_escape_string($conn, $username);
    $hash = mysqli_real_escape_string($conn, $pwhash);
    $salt = mysqli_real_escape_string($conn, $salt);
    $sql = "UPDATE " . $mysql_table . "users SET password = '" . $hash . "', salt = '" . $salt . "' WHERE username = '" . $username . "'";
    $retval = mysqli_query($conn, $sql);
    if(!$retval && $debug)
      die("Error: " . mysqli_sqlstate($conn));
    mysqli_close($conn);
    echo "Password changed.";
  }
  else
  {
    echo "You entered different passwords.";
  }
}

function store_user_information($username, $hash, $salt)
{
  global $dbhost, $dbuser, $dbpass, $mysql_db, $mysql_table, $debug;
  $conn = mysqli_connect($dbhost, $dbuser, $dbpass, $mysql_db);
  if(!$conn && $debug)
    die("Error: Unable to connect to MySQL.");
  $username = mysqli_real_escape_string($conn, $username);
  $hash = mysqli_real_escape_string($conn, $hash);
  $salt = mysqli_real_escape_string($conn, $salt);
  $sql = "SELECT username FROM " . $mysql_table . "users WHERE username = '$username'";
  $retval = mysqli_query($conn, $sql);
  if($retval)
  {
    if (mysqli_num_rows($retval) == 0)
    {
      mysqli_free_result($retval);
      $sql = "INSERT INTO " . $mysql_table . "users (username, password, salt) VALUES ('$username', '$hash', '$salt')";
      $retval = mysqli_query($conn, $sql);
      if(!$retval && $debug)
        die("Error: " . mysqli_sqlstate($conn));
      echo 'Account created. You can now <a href = "login.php">log in.</a>';
    }
    else
    {
      echo("The username you entered already exists.");
      mysqli_free_result($retval);
    }
  }
  else
    if($debug)
      die("Error: " . mysqli_sqlstate($conn));
  mysqli_close($conn);
}

function create_user($username, $password)
{
  $salt = shell_exec("./random_salt 512 a"); // generates a 512 chars long base95 salt
  $pwhash = salthash_password($password, $salt);
  store_user_information($username, $pwhash, $salt);
  return array($pwhash, $salt);
}

?>
