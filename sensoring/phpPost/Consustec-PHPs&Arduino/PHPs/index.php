<?php
//$mysqli = new mysqli('localhost', 'my_user', 'my_password', 'my_db');
$mysqli = new mysqli('localhost', 'consu186_brunno', 'n+?.5~*~(+$$', 'consu186_s2m');

if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}

$res = $mysqli->query("SELECT `realPower` , `apparentPower` , `powerFactor` , `supplyVoltage` , `Irms` , `DataHora`  FROM `tb_teste` ORDER BY `Id` DESC LIMIT 1 ");
$row = $res->fetch_assoc();

printf("DataHora = %s <br/>", $row['DataHora'], gettype($row['DataHora']));
printf("  realPower = %s<br/>", $row['realPower'], gettype($row['realPower']));
printf("  apparentPower = %s<br/>", $row['apparentPower'], gettype($row['apparentPower']));
printf("  powerFactor = %s<br/>", $row['powerFactor'], gettype($row['powerFactor']));
printf("  supplyVoltage = %s<br/>", $row['supplyVoltage'], gettype($row['supplyVoltage']));
printf("  Irms = %s<br/>", $row['Irms'], gettype($row['Irms']));
echo "<meta HTTP-EQUIV='refresh' CONTENT='10;URL=index.php'>";
mysqli_close ($mysqli);

?>