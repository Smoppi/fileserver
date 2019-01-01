<?php include ('header.htm'); ?>

<pre class = "teksti">

<?php

$tiedostoteksti = "Otsikko: \n" . $_POST['file_name'] . "\n\n\nTeksti:\n" . $_POST['description'];

$uploaddir = "upload/";
$uploadfile = $uploaddir . time() . "_" . basename($_FILES['userfile']['name']);

if ($_FILES['userfile']['size'] > 16777216)
{
  die("Your file is too big. :(</td></tr></table></body></html>");
}

$infofilu = fopen($uploadfile . '.info', 'w');
fwrite($infofilu, $tiedostoteksti);
fclose($infofilu);

if (move_uploaded_file($_FILES['userfile']['tmp_name'], $uploadfile))
  echo "Your file has succesfully been uploaded to the server.";

else
  echo "Uploading your file failed for some reason.";

?>

</pre>

<?php include ('footer.htm'); ?>

