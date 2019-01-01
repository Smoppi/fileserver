<?php

include("inc/pagenum.inc");

function list_item($file, $dir, $os, $kuvaus, $koko, $pvm, $tyyppi, $sort, $filesperpage)
{
  global $file_dir;
  # tarkistetaan onko .zipissä file_id.dizziä
  if (strtolower(substr($file_dir . $file, -4)) == ".zip") 
  { 
    $file_id_diz = shell_exec("unzip -p -C " . $file_dir . "/" . escapeshellarg($dir) . "/" . escapeshellarg($file) . " file_id.diz");
    if ($file_id_diz == "caution: filename not matched:  file_id.diz")  $file_id_diz = NULL; 
  }
  else $file_id_diz = NULL;
  echo '<tr><td class = "dirlist1"><a href = "?sort=' . $sort . '&dir=' . $os . '&fpp=' . $filesperpage . '">' . $file . '</a>';
  if (isset($kuvaus)) 
    echo '<font color = "gray"><br>' . $kuvaus . '</font>'; 
  if ($file_id_diz !== NULL)
    echo "<font color = \"gray\"><br><br>FILE_ID.DIZ:<br>$file_id_diz</font>"; $file_id_diz = NULL; 
  echo '</td><td class = "dirlist2">' . $koko .'<br><font color = "gray">' . $pvm . '</font></td><td class = "dirlist3">' . $tyyppi . '</td></tr>';
}

function dirlist($dir, $sort) {

  global $filesperpage;
  global $file_dir;
  global $time_zone;

  date_default_timezone_set($time_zone);

  if(isset($_GET['fpp']) && is_numeric($_GET['fpp']))
    $filesperpage = $_GET['fpp'];

  $page=0;
  if(isset($_GET['page'])) {
    $page=$_GET['page'];
    $page--;
  }
  
  $dir_to_list = $file_dir . '/' . $dir;
  #ilmoitetaan kansio

  if(is_dir($dir_to_list)) echo 'Dir: / ';
  else echo 'File: / ';
  echo '<a href = "?sort=' . $sort . '&fpp=' . $filesperpage . '">root</a> ';
  $osadir = explode('/', $dir);
  $f = 0;
  $linkki = "";
  while ($f < count($osadir) && $osadir[$f] != "")
  {
    if($f)
      $linkki .= '/' . $osadir[$f];
    else
      $linkki = $osadir[$f];
    $print = $osadir[$f];
    # tarkistetaan ettei kansiosta löydy .. merkkejä
    if (substr($osadir[$f], 0, 1) == ".")
      die();
    if(is_dir($dir_to_list))
      echo '/ <a href = "?sort=' . $sort . '&dir=' . rawurlencode($linkki) . '&fpp=' . $filesperpage . '">' . $print . '</a> ';
    else
      echo '/ <a href = "?sort=' . $sort . '&dir=' . rawurlencode($linkki) . '&fpp=' . $filesperpage . '">' . $print . '</a> ';
    $f++;
  }

  if ($sort == "name")
    echo '<br><br><table class = "teksti2"><tr><td><a href = "?dir=' . $dir . '&fpp=' . $filesperpage . '&sort=rname" class = "jarjestyslinkki">Filename</a></td>';
  else
    echo '<br><br><table class = "teksti2"><tr><td><a href = "?dir=' . $dir . '&fpp=' . $filesperpage . '&sort=name" class = "jarjestyslinkki">Filename</a></td>';
  if ($sort == "size")
    echo '<td><a href = "?dir=' . $dir . '&fpp=' . $filesperpage . '&sort=ssize" class = "jarjestyslinkki">Size</a></td>';
  else
    echo '<td><a href = "?dir=' . $dir . '&fpp=' . $filesperpage . '&sort=size" class = "jarjestyslinkki">Size</a></td>';
  if ($sort == "type")
    echo '<td><a href = "?dir=' . $dir . '&fpp=' . $filesperpage . '&sort=rtype" class = "jarjestyslinkki">Filetype</a></td></tr>';
  else
    echo '<td><a href = "?dir=' . $dir . '&fpp=' . $filesperpage . '&sort=type" class = "jarjestyslinkki">Filetype</a></td></tr>';

  $oslist = array();
  $tiedlist = array();
  $kokolist = array();
  $pvmlist = array();
  $kuvauslist = array();
  $tyyppilist = array();
  $n_jarjestys = array();
  $takolist = array();

  $jarjestysnum = 0;

  // Open a known directory, and proceed to read its contents
  #tarkistetaan onko kansio
  if (is_dir($dir_to_list)) {
    if ($dh = opendir($dir_to_list)) {
      while (($file = readdir($dh)) !== false) {
        #ohitetaan . ja .. kansio ja infotiedostot
        if (substr($file, 0, 1) != '.' && substr($file, -5) != '.info') {
          $kokokerroin = "bytes";
          $koko = filesize($dir_to_list . "/" . $file);
          $tavukoko = $koko;
          if ($kokokerroin == "bytes" && $koko >= "1024") { $kokokerroin = "kilobytes"; $koko = $koko / 1024; }
          if ($kokokerroin == "kilobytes" && $koko >= "1024") { $kokokerroin = "megabytes"; $koko = $koko / 1024; }
          if ($kokokerroin == "megabytes" && $koko >= "1024") { $kokokerroin = "gigabytes"; $koko = $koko / 1024; }
          if ($kokokerroin == "gigabytes" && $koko >= "1024") { $kokokerroin = "terabytes"; $koko = $koko / 1024; }
          # Otetaan tiedoston osoite talteen
          if($dir == "")
            $oslist[$jarjestysnum] = rawurlencode($file);
          else
            $oslist[$jarjestysnum] = rawurlencode($dir . "/" . $file);
          # Otetaan tiedoston nimi talteen
          $tiedlist[$jarjestysnum] = $file;
          # Otetaan tiedoston koko talteen
          $kokolist[$jarjestysnum] = round($koko,2) . ' ' . $kokokerroin;
          # Otetaan tiedoston luontipäivämäärä talteen
          $pvmlist[$jarjestysnum] = date("F d Y H:i:s", filemtime($dir_to_list . "/" . $file));
          # Otetaan tiedoston tavukoko talteen
          $takolist[$jarjestysnum] = $tavukoko;
          # Jos kuvaus löytyy, otetaan tiedoston kuvaus talteen
          if (file_exists('../filut/' . $dir . '/' . $file . '.info'))
            $kuvauslist[$jarjestysnum] = file_get_contents($dir_to_list . '/' . $file .  '.info');
          else 
            $kuvauslist[$jarjestysnum] = NULL;
          # Otetaan tiedoston tyyppi talteen
          $tyyppilist[$jarjestysnum] = filetype($dir_to_list . "/" . $file);
          $jarjestysnum++;
          }
        }
        closedir($dh);
      }

    # Tulostetaan tiedostolistaus

    echo "<tr><td>";
    filesperpage_links($page+1, $dir, $sort);
    echo "<br>";
    printpagenums($jarjestysnum, $filesperpage, $page+1, $dir, $sort);
    echo "</td></tr>";


    switch ($sort)
    {
      # Jos järjestetään koon mukaan
      case "size":
        for ($l=0; $l<$jarjestysnum; $l++)
          $n_jarjestys[$l] = $l;
        $kokoislist = $takolist;
        array_multisort($kokoislist, SORT_DESC, SORT_NUMERIC, $n_jarjestys);
      break;
    # Jos järjestetään koon mukaan pienin ensin
      case "ssize":
        for ($l=0; $l<$jarjestysnum; $l++)
          $n_jarjestys[$l] = $l;
        $kokoislist = $takolist;
        array_multisort($kokoislist, SORT_ASC, SORT_NUMERIC, $n_jarjestys);
      break;
    # Jos järjestetään aakkosjärjestykseen
      case "name":
        for ($l=0; $l<$jarjestysnum; $l++)
          $n_jarjestys[$l] = $l;
        $aakkoslist = $tiedlist;
        array_multisort($aakkoslist, SORT_ASC, SORT_STRING, $n_jarjestys);
      break;
    # Jos järjestetään väärinpäin aakkosjärjestykseen
      case "rname":
        for ($l=0; $l<$jarjestysnum; $l++)
          $n_jarjestys[$l] = $l;
        $aakkoslist = $tiedlist;
        array_multisort($aakkoslist, SORT_DESC, SORT_STRING, $n_jarjestys);
      break;
    # Jos järjestetään tyypin mukaan
      case "type":
        for ($l=0; $l<$jarjestysnum; $l++)
          $n_jarjestys[$l] = $l;
        $tyyppislist = $tyyppilist;
        array_multisort($tyyppislist, SORT_ASC, SORT_STRING, $n_jarjestys);
      break;
    # Jos järjestetään tyypin mukaan tiedostot ensin
      case "rtype":
        for ($l=0; $l<$jarjestysnum; $l++)
          $n_jarjestys[$l] = $l;
        $tyyppislist = $tyyppilist;
        array_multisort($tyyppislist, SORT_DESC, SORT_STRING, $n_jarjestys);
      break;
    # ei järjestystä
      default:
        $sort = "default";
      break; 
    }

    if($sort != "default")
      for ($n=$page*$filesperpage; $n<$jarjestysnum && $n<($page+1)*$filesperpage; $n++) 
        list_item ($tiedlist[$n_jarjestys[$n]], $dir, $oslist[$n_jarjestys[$n]], $kuvauslist[$n_jarjestys[$n]], $kokolist[$n_jarjestys[$n]], $pvmlist[$n_jarjestys[$n]], $tyyppilist[$n_jarjestys[$n]], $sort, $filesperpage);
    else
      for ($n=$page*$filesperpage; $n<$jarjestysnum && $n<($page+1)*$filesperpage; $n++) 
        list_item ($tiedlist[$n], $dir, $oslist[$n], $kuvauslist[$n], $kokolist[$n], $pvmlist[$n], $tyyppilist[$n], $sort, $filesperpage);




    echo "<tr><td>";
    printpagenums($jarjestysnum, $filesperpage, $page+1, $dir, $sort);
    echo "<br>" . $jarjestysnum . " files in directory.";
    echo "</td></tr>";

  }

  #jos tiedosto, annetaan suora latauslinkki
  else
   {
    $kokokerroin = "bytes";
      $koko = filesize($file_dir . "/" . $dir);
      if ($kokokerroin == "bytes" && $koko >= "1024")
      {
        $kokokerroin = "kilobytes";
        $koko = $koko / 1024;
      }
      if ($kokokerroin == "kilobytes" && $koko >= "1024")
      {
        $kokokerroin = "megabytes";
        $koko = $koko / 1024;
      }
      if ($kokokerroin == "megabytes" && $koko >= "1024")
      { 
        $kokokerroin = "gigabytes";
        $koko = $koko / 1024;
      }
      if ($kokokerroin == "gigabytes" && $koko >= "1024")
      { $kokokerroin = "terabytes";
        $koko = $koko / 1024;
      }
      echo '<tr><td>' . $dir . '</td><td>' . round($koko, 2) . ' ' . $kokokerroin . '</td><td>file</td></tr>';

      # näytetään tiedoston kuvaus jos infotiedosto löytyy
      if (file_exists($file_dir . "/" . $dir . '.info'))
        echo '<tr><td><font color = "gray">' . file_get_contents($file_dir . "/" . $dir .  '.info') . '</font></td></tr>'; 
      # jos .zip tai tar-pakkaus, näytetään arkiston sisältö
      if (strtolower(substr($file_dir . "/" . $dir, -4)) == ".zip")
        echo '<tr><td><font color = "gray"> Files in archive:<br><textarea rows = "20" cols = "80" class = "tafilelist">' . shell_exec('unzip -l ' . $file_dir . "/" . escapeshellarg($dir) . ' | tail -n +2') . '</textarea></font></td></tr>';
      if (strtolower(substr($file_dir . "/" . $dir, -7)) == ".tar.gz")
        echo '<tr><td><font color = "gray"> Files in archive:<br><textarea rows = "20" cols = "80" class = "tafilelist">' . shell_exec('tar -ztf ' . $file_dir . "/" . escapeshellarg($dir)) . '</textarea></font></td></tr>';
      if (strtolower(substr($file_dir . "/" . $dir, -4)) == ".tar")
        echo '<tr><td><font color = "gray"> Files in archive:<br><textarea rows = "20" cols = "80" class = "tafilelist">' . shell_exec('tar -tf ' . $file_dir . "/" . escapeshellarg($dir)) . '</textarea></font></td></tr>';
      if (strtolower(substr($file_dir . "/" . $dir, -8)) == ".tar.bz2")
        echo '<tr><td><font color = "gray"> Files in archive:<br><textarea rows = "20" cols = "80" class = "tafilelist">' . shell_exec('tar -jtf ' . $file_dir . "/" . escapeshellarg($dir)) . '</textarea></font></td></tr>';
      # jos tekstitiedosto, näytetään tiedoston sisältö
      if (strtolower(substr($file_dir . "/" . $dir, -4)) == ".txt")
      {
        echo '<tr><td><font color = "gray"> File contents:<br><textarea rows = "20" cols = "80" class = "tafilelist">';
        $file_contents = htmlspecialchars(file_get_contents($file_dir . "/" . $dir), 0, 'UTF-8');
        if($file_contents == "") $file_contents = htmlspecialchars(file_get_contents($file_dir . "/" . $dir), 0, 'ISO-8859-15');
        if($file_contents == "") $file_contents = htmlspecialchars(file_get_contents($file_dir . "/" . $dir), ENT_SUBSTITUTE, 'ISO-8859-15');
        echo $file_contents . '</textarea></font></td></tr>';
      }
//      echo '<tr><td class = "latauslinkki"><a href = "../filut/' . $dir . '">Download</a></td><td></td><td></td></tr>';
      echo '<tr><td class = "latauslinkki"><a href = "download.php?file=' . rawurlencode($dir) . '">Download</a></td><td></td><td></td></tr>';
    }

  }

?>
