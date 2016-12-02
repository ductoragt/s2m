<?php

$mysqli = new mysqli('localhost', 'root', '', 'energy');

if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}

$res = $mysqli->query("SELECT `horario` , `realPower` , `apparentPower` , `powerFActor` , `supplyVoltage` , `Irms` FROM `medidas` ORDER BY `horario` DESC LIMIT 1 ");
  $row = $res->fetch_assoc();
  
printf("horario = %s <br/>", $row['horario'], gettype($row['horario']));
printf("  realPower = %s<br/>", $row['realPower'], gettype($row['realPower']));
printf("  apparentPower = %s<br/>", $row['apparentPower'], gettype($row['apparentPower']));
printf("  powerFActor = %s<br/>", $row['powerFActor'], gettype($row['powerFActor']));
printf("  supplyVoltage = %s<br/>", $row['supplyVoltage'], gettype($row['supplyVoltage']));
printf("  Irms = %s\n", $row['Irms'], gettype($row['Irms']));
echo "<meta HTTP-EQUIV='refresh' CONTENT='10;URL=index.php'>";
mysqli_close ($mysqli);
?>