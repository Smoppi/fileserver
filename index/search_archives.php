<?php include ('header.htm'); ?>
Search files inside archives<br>

<form action = "" method = "get">
Keyword: <input type = "text" name = "q" class = "tekstilaatikko" autofocus>
<input type = "submit" value = "search" class = "nappi">
</form>

<?php
include ('inc/search_archives.inc');
if(isset($_GET['q']))
  search($_GET['q']);
?>


<?php include ('footer.htm'); ?>
