#include <SoftwareSerial.h>
#include "EmonLib.h"             // Include Emon Library

EnergyMonitor emon1;             // Create an instance

#define DEBUG true

// RX, TX do ESP8266
SoftwareSerial ser(2,3); 

void setup() {                
 
  //inicializa a serial do arduino 
  Serial.begin(9600);
  //inicialza a serial do ESP8266
  ser.begin(9600);
  
  emon1.voltage(0, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(1, 111.1);       // Current: input pin, calibration.
  //reseta o ESP8266
  sendData("AT+RST\r\n", 2000, DEBUG); // rst
  // Conecta a rede wireless
  sendData("AT+CWJAP=\"GVT\",\"(trapinho)\"\r\n", 2000, DEBUG);
  delay(13000);
  // Mostra o endereco IP
  sendData("AT+CIFSR\r\n", 1000, DEBUG);
  
  
}

//loop 
void loop() {
  
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFactor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable
  int deviceId          = 1; 
 
  //criar a string apenas dos dados a serem enviados
  delay(20);
  String data ="realPower=";
  data += String(realPower);
  data +="&apparentPower=";
  data += String(apparentPower);
  data +="&powerFactor=";
  data += String(powerFactor);
  data +="&supplyVoltage=";
  data += String(supplyVoltage);
  data +="&Irms=";
  data += String(Irms);
  data +="&deviceId=";
  data += String(deviceId);
  
  //conexao TCP com o site
  sendData("AT+CIPSTART=\"TCP\",\"consustecengenharia.com.br\",80\r\n", 5000, DEBUG);

  //string para envio dos dados
  String getStr ="POST /s2m/ductor/medida.php HTTP/1.1\r\n";
         getStr +="Host:www.consustecengenharia.com.br\r\n";
         getStr +="Connection: close\r\n";
         getStr +="Content-Type: application/x-www-form-urlencoded\r\n";
         getStr +="Content-Length: ";
         getStr += data.length();
         getStr +="\r\n\r\n";
         getStr += data;

  //verifica e envia para o ESP8266 o tamanho da string de SET 
  String cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
  Serial.println(cmd);

  //verifica se o modulo esta pronto para enviar a string procurando por ">"
  if(ser.find(">")){
    ser.print(getStr);
    Serial.println(getStr);
    String response = "";
    Serial.println(response);
  }
  else{
    //caso  nao tenha conseguido achar o ">"
    ser.println("AT+CIPCLOSE");  
    Serial.println("AT+CIPCLOSE");
  }
    
  // 16 sec de delay entre updates
  delay(30000); 
}

// Envio dos comandos AT para o modulo com timeout e debug.
String sendData(String command, const int timeout, boolean debug)
{
  
  String response = "";
  //print do comando na serial do ESP8266
  ser.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (ser.available())
    {
      // Le o output da serial do ESP8266 
      char c = ser.read(); // le o proximo caractere.
      response += c;
    }
  }
  if (debug)
  {
    //imprime a resposta do ESP8266
    Serial.print(response);
  }
  //retorno da funcao
  return response;
}
