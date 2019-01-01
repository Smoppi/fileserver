<?php include ('header.htm'); ?>

<pre class = "teksti">
  <form enctype="multipart/form-data" action="upload_file.php" method="POST">
    <p>
The largest allowed file size is 16 MB. If your file is bigger, please /msg Sompi @ Quakenet or Ircnet.<br>
    </p>
    <input type="hidden" name="MAX_FILE_SIZE" value="16777216">
Name of the file, program, game or other thing you are uploading: <br>
<input type = "text" name = "file_name" size = "50" class = "tekstilaatikko"><br>
About: <br><textarea rows = "10" cols = "50" name = "description" class = "tekstilaatikko"></textarea>
File: <input name="userfile" type="file" class = "nappi">
<input type="submit" value="Upload file" class = "nappi">
  </form>
</pre>

<?php include ('footer.htm'); ?>


