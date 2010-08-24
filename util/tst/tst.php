<?php

  function verifica($arr, $pal)
  {
    if(!isset($arr)) return false;
    $c = count($arr);
    for($i = 0; $i < $c; $i += 1)
    {
      if($arr[$i] == $pal)
        return true;
    }
    return false;
  }

  $w_indice = array();
  $f_indice = array();

  $dir = "../textos/";
  $lista = file($dir . "listarquivos");

  $n = count($lista);

  for($i = 0; $i < $n; $i += 1)
  {
    echo $lista[$i];
    $cont = implode(" ", file($dir . str_replace("\n", "", $lista[$i])));

    $f_indice[] = $lista[$i];
   
    $cont = utf8_encode($cont);   
    $cont = preg_replace('/\s\s+/', ' ', $cont);
    $cont = str_replace(".", "", $cont);
    $cont = str_replace(",", "", $cont);
    
    $cont = explode(" ", $cont);

    $cc = count($cont);
    for($j = 0; $j < $cc; $j += 1)
    {
      if(!verifica($indice[$cont[$j]], $i))
      {
        $indice[$cont[$j]][] = $i;
      }
    }


  }

    echo print_r($indice); exit;

?>
