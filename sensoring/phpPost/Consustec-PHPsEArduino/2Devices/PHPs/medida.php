<?php
//$mysqli = new mysqli('localhost', 'my_user', 'my_password', 'my_db');
$mysqli = new mysqli('localhost', 'consu186_brunno', 'n+?.5~*~(+$$', 'consu186_s2m');

if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}

$realPower =isset($_POST["realPower"]) ? $_POST["realPower"]:'';
$apparentPower = isset($_POST["apparentPower"]) ? $_POST["apparentPower"]:'';
$powerFactor = isset($_POST["powerFactor"]) ? $_POST["powerFactor"]:'';;
$supplyVoltage = isset($_POST["supplyVoltage"]) ? $_POST["supplyVoltage"]:'';
$Irms = isset($_POST["Irms"]) ? $_POST["Irms"]:'';
$deviceId =isset($_POST["deviceId"]) ? $_POST["deviceId"]:'';

$query = "INSERT INTO tb_teste (realPower,apparentPower,powerFactor,supplyVoltage,Irms,deviceId) VALUES('$realPower','$apparentPower','$powerFactor','$supplyVoltage','$Irms','$deviceId')";
mysqli_query ($mysqli, $query);

mysqli_close ($mysqli);
?>

