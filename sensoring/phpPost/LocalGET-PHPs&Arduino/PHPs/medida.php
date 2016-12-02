<?php

$mysqli = new mysqli('localhost', 'root', '', 'energy');

if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}
// DEFINE O FUSO HORARIO COMO O HORARIO DE BRASILIA
date_default_timezone_set('America/Sao_Paulo'); 
$horario = date('Y-m-d H:i:s');
$realPower =isset($_GET["realPower"]) ? $_GET["realPower"]:'';
$apparentPower = isset($_GET["apparentPower"]) ? $_GET["apparentPower"]:'';;
$powerFactor = isset($_GET["powerFactor"]) ? $_GET["powerFactor"]:'';;
$supplyVoltage = isset($_GET["supplyVoltage"]) ? $_GET["supplyVoltage"]:'';;
$Irms = isset($_GET["Irms"]) ? $_GET["Irms"]:'';;

$query = "INSERT INTO medidas (horario,realPower,apparentPower,powerFactor,supplyVoltage,Irms) VALUES('$horario','$realPower','$apparentPower','$powerFactor','$supplyVoltage','$Irms')";
mysqli_query ($mysqli, $query);

mysqli_close ($mysqli);
?>

