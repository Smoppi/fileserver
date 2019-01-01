<?php include ('header.htm'); ?>
<pre class = "teksti">

<?php
include('inc/dirlist.inc');

if(isset($_GET['dir']))
  $dir = $_GET['dir'];
else
  $dir = "";

if(isset($_GET['sort']))
  $sort = $_GET['sort'];
else
  $sort = "";

dirlist($dir, $sort);



?>
</table>
</pre>
<?php include('footer.htm'); ?>
