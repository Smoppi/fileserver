<?php
function logout()
{
  global $dbhost, $dbuser, $dbpass, $mysql_db, $mysql_table, $debug, $algorthm, $cookie_name;
  $conn = mysqli_connect($dbhost, $dbuser, $dbpass, $mysql_db);
  if(!$conn && $debug)
    die("Error: Unable to connect to MySQL.");
  $user = mysqli_real_escape_string($conn, $_COOKIE[$cookie_name . "user"]);
  $sql = "DELETE FROM " . $mysql_table . "logins WHERE username = '" . $user . "'";
  $retval = mysqli_query($conn, $sql);
  if(!$retval && $debug)
    die('Could not update data: ' . mysqli_error($conn));
  setcookie($cookie_name . "user", "", time() - 3600);
  unset($_COOKIE[$cookie_name . "user"]);
}

function check_cookie()
{
  global $dbhost, $dbuser, $dbpass, $mysql_db, $mysql_table, $debug, $algorthm, $cookie_name, $login_timeout;
  if(isset($_COOKIE[$cookie_name . "user"]))
  {
    $conn = mysqli_connect($dbhost, $dbuser, $dbpass, $mysql_db);
    if(!$conn && $debug)
      die("Error: Unable to connect to MySQL.");
    $user = mysqli_real_escape_string($conn, $_COOKIE[$cookie_name . "user"]);
    $sql = "SELECT username, session_id, lastvisit FROM " . $mysql_table . "logins WHERE username = '" . $user . "'";
    $retval = mysqli_query($conn, $sql);
    if($retval)
    {
      if (mysqli_num_rows($retval) != 0)
      {
        $row = mysqli_fetch_array($retval, MYSQLI_ASSOC);
        mysqli_free_result($retval);
        if($row['session_id'] == $_COOKIE[$cookie_name . "sessionid"])
        {
          if($row['lastvisit'] > time() - $login_timeout)
          {
            $login_name = $row['username'];
            setcookie($cookie_name . "user", $_COOKIE[$cookie_name . "user"], time() + $login_timeout); // renew cookie
            setcookie($cookie_name . "sessionid", $_COOKIE[$cookie_name . "sessionid"], time() + $login_timeout); // renew cookie
            $sql = "UPDATE " . $mysql_table . "logins SET lastvisit = '" . time() . "' WHERE username = '" . $user . "'";
            $retval = mysqli_query($conn, $sql);
            if(!$retval && $debug)
              die('Could not update data: ' . mysqli_error($conn));
          }
          else
          {
            logout();
            $login_name = false;
          }             
        }
      }
    }
    else
      if($debug)
        die("Error: " . mysqli_sqlstate($conn));    
    mysqli_close($conn);
  }
  if(isset($login_name))
    return $login_name;
  else return false;
}

function check_login($username, $password)
{
  global $dbhost, $dbuser, $dbpass, $mysql_db, $mysql_table, $debug, $algorthm, $cookie_name, $login_timeout;
  $conn = mysqli_connect($dbhost, $dbuser, $dbpass, $mysql_db);
  if(!$conn && $debug)
    die("Error: Unable to connect to MySQL.");
  $username = mysqli_real_escape_string($conn, $username);
  $sql = "SELECT username, password, salt FROM " . $mysql_table . "users WHERE username = '$username'";
  $retval = mysqli_query($conn, $sql);
  if($retval)
  {
    if (mysqli_num_rows($retval) == 1)
    {
      $row = mysqli_fetch_array($retval, MYSQLI_ASSOC);
      mysqli_free_result($retval);
      if(hash($algorthm, $password . $row["salt"]) != $row["password"])
      {
        $return = "Invalid password.";
      }
      else
      {
        $sql = "SELECT username FROM " . $mysql_table . "logins WHERE username = '$username'"; // check if already logged in
        $retval = mysqli_query($conn, $sql);
        if($retval)
        {
          if(mysqli_num_rows($retval) != 0) // remove old login
          {
            mysqli_free_result($retval);
            $sql = "DELETE FROM " . $mysql_table . "logins WHERE username = '$username'";
            $retval = mysqli_query($conn, $sql);
            if(!$retval && $debug)
              die('Could not remove login data: ' . mysqli_error($conn));
          }
          else
            mysqli_free_result($retval);
        }

        $session_id = shell_exec("./random_salt 64 a"); // create a randomized session id
        $lastvisit = time();
        $sql = "INSERT INTO " . $mysql_table . "logins (username, session_id, lastvisit) VALUES ('$username', '" . mysqli_real_escape_string($conn, $session_id) . "', '$lastvisit')";
        $retval = mysqli_query($conn, $sql); // store session information
        if(!$retval && $debug)
          die('Could not insert login data: ' . mysqli_error($conn));
        setcookie($cookie_name . "user", $username, time() + $login_timeout);
        setcookie($cookie_name . "sessionid", $session_id, time() + $login_timeout);
        $return = "Logged in as " . htmlspecialchars($username) . ".";
      }
    }
    else
    {
      $return = "Invalid username.";
      mysqli_free_result($retval);
    }
  }
  else
    if($debug)
      die("Error: " . mysqli_sqlstate($conn));
  mysqli_close($conn);
  if(isset($return))
    return $return;
}

if(isset($_GET['login']))
{
  if(isset($_POST['user']) && isset($_POST['pass']))
  {
    $user = $_POST['user'];
    $pass = $_POST['pass'];
    $user_message = check_login($user, $pass);
  }
}

if(isset($_GET['logout']))
{
  logout();
  $user_message = "You have been logged out.";
}

if(isset($_COOKIE[$cookie_name . "user"]))
{
  $loginname = check_cookie();
}

?>
