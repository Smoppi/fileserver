<?php
  $file_dir = "/var/www/htdocs/fileserver/filut";
  $site_dir = "/var/www/htdocs/fileserver/";
  $index_request_dir = "/fileserver";
  $filesperpage=30;
  $time_zone = 'Europe/Helsinki';

  $dbhost = 'localhost';
  $dbuser = 'asd';
  $dbpass = 'hevosen kyrpä';
  $mysql_db = 'sami';
  $mysql_table = 'fileserver_';
  $debug = true;

  $login_timeout = 3600;
  $cookie_name = "paskaa";
  $algorthm = "sha512"; // this must be the safest hashing algorithm supported by the system
?>
