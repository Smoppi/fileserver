<?php
  function printpagenums($jarjestysnum, $filesperpage, $page, $dir, $sort)
  {
    echo "Pages: ";
    # sivunumerot
    $ppage = $page-1;
    $npage = $page+1;
    if($page>1) echo '<a href = "?dir=' . $dir . '&sort=' . $sort . '&page=' . $ppage . '&fpp=' . $filesperpage . '">&lt;&lt;</a>&nbsp;';
    for($n=0,$m=1; $n<$jarjestysnum; $n++)
    {
      if($n % $filesperpage == 0)
      {
        if($m == $page) echo "<b>";
        echo '<a href = "?dir=' . $dir . '&sort=' . $sort . '&page=' . $m . '&fpp=' . $filesperpage . '">' . $m . '</a>&nbsp; ';
        if($m == $page) echo "</b>";
        $m++;
      }
    }
    if($page+1<$m) echo '<a href = "?dir=' . $dir . '&sort=' . $sort . '&page=' . $npage . '&fpp=' . $filesperpage . '">&gt;&gt;</a>&nbsp;';
  }
 
  function filesperpage_links($page, $dir, $sort)
  {
    echo "Files per page: ";
    echo '<a href = "?dir=' . $dir . '&sort=' . $sort . '&page=' . $page . '&fpp=10">10</a> ';
    echo '<a href = "?dir=' . $dir . '&sort=' . $sort . '&page=' . $page . '&fpp=30">30</a> ';
    echo '<a href = "?dir=' . $dir . '&sort=' . $sort . '&page=' . $page . '&fpp=50">50</a> ';
    echo '<a href = "?dir=' . $dir . '&sort=' . $sort . '&page=' . $page . '&fpp=100">100</a> ';
    echo '<a href = "?dir=' . $dir . '&sort=' . $sort . '&page=' . $page . '&fpp=200">200</a> ';
    echo '<a href = "?dir=' . $dir . '&sort=' . $sort . '&page=' . $page . '&fpp=500">500</a> ';
  }
?>
