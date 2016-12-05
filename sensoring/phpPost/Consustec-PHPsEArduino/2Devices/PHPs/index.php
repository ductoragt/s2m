<?php
//$mysqli = new mysqli('localhost', 'my_user', 'my_password', 'my_db');
$mysqli = new mysqli('localhost', 'consu186_brunno', 'n+?.5~*~(+$$', 'consu186_s2m');

if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: (" . $mysqli->connect_errno . ") " . $mysqli->connect_error;
}



$res1 = $mysqli->query("SELECT `realPower` , `apparentPower` , `powerFactor` , `supplyVoltage` , `Irms` , `DataHora` FROM `tb_teste` WHERE deviceId=1 ORDER BY `Id` DESC LIMIT 1");
$row1 = $res1->fetch_assoc();

    $DataHora1 = $row1['DataHora'];
    $realPower1 = $row1['realPower'];
    $apparentPower1 = $row1['apparentPower'];
    $powerFactor1 = $row1['powerFactor'];
    $supplyVoltage1 = $row1['supplyVoltage'];
    $Irms1 = $row1['Irms'];

    printf("Device Id 1 <br/>");
    printf("  DataHora = %s <br/>", $DataHora1);
    printf("  realPower = %s<br/>", $realPower1);
    printf("  apparentPower = %s<br/>", $apparentPower1);
    printf("  powerFactor = %s<br/>", $powerFactor1);
    printf("  supplyVoltage = %s<br/>", $supplyVoltage1);
    printf("  Irms = %s<br/><br/><br/>", $Irms1);

    
$res2 = $mysqli->query("SELECT `realPower` , `apparentPower` , `powerFactor` , `supplyVoltage` , `Irms` , `DataHora` FROM `tb_teste` WHERE deviceId=2 ORDER BY `Id` DESC LIMIT 1");
$row2 = $res2->fetch_assoc();

    $DataHora2 = $row2['DataHora'];
    $realPower2 = $row2['realPower'];
    $apparentPower2 = $row2['apparentPower'];
    $powerFactor2 = $row2['powerFactor'];
    $supplyVoltage2 = $row2['supplyVoltage'];
    $Irms2 = $row2['Irms'];


    printf("Device Id 2 <br/>");
    printf("  DataHora = %s <br/>", $DataHora2);
    printf("  realPower = %s<br/>", $realPower2);
    printf("  apparentPower = %s<br/>", $apparentPower2);
    printf("  powerFactor = %s<br/>", $powerFactor2);
    printf("  supplyVoltage = %s<br/>", $supplyVoltage2);
    printf("  Irms = %s<br/>", $Irms2);


echo "<meta HTTP-EQUIV='refresh' CONTENT='10;URL=index.php'>";
mysqli_close ($mysqli);

?>