<?php include ('header.htm'); ?>
Search files
<form action = "" method = "get">
Keyword: <input type = "text" name = "q" class = "tekstilaatikko" autofocus>
<input type = "submit" value = "search" class = "nappi">
</form>

<?php
include ('inc/search.inc');
if(isset($_GET['q']))
  search_new($_GET['q']);
?>

<br>
<a href = "search_archives.php">Search files inside archives</a>

<?php include ('footer.htm'); ?>
