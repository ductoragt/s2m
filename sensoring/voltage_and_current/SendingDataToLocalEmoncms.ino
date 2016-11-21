

#include <SoftwareSerial.h>
#include "EmonLib.h"             // Include Emon Library

EnergyMonitor emon1;             // Create an instance

#define DEBUG true

// pino do sensor 
int sensor_pin=A0;  
float temp = 0;  
// API key do canal do thingspeak
String apiKey = "98918a3cea37fa102b86d7681c3f86e4";
// RX, TX do ESP8266
SoftwareSerial ser(2,3); 

//http://localhost/emoncms/input/post.json?node=1&json={power:200}&apikey=98918a3cea37fa102b86d7681c3f86e4

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
  float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable
  
   //le o LM35 e converte para celcius
   
    
    delay(20);
   //conexao TCP com o site do thingspeak
    sendData("AT+CIPSTART=\"TCP\",\"192.168.25.12\",4000\r\n", 5000, DEBUG);

  //monta a string de GET para o thingspeak
    //http://localhost/emoncms/input/post.json?node=1&json={power1:100,power2:200,power3:300}
  String getStr = "GET /emoncms/input/post.json?node=1&json={";
  getStr +="realPower:";
  getStr += String(realPower);
  getStr +=",apparentPower:";
  getStr += String(apparentPower);
  getStr +=",powerFActor:";
  getStr += String(powerFActor);
  getStr +=",supplyVoltage:";
  getStr += String(supplyVoltage);
  getStr +=",Irms:";
  getStr += String(Irms);
  getStr +="}&apikey=";
  getStr += apiKey;
  //getStr +="HTTP/1.0";
  getStr += "\r\n\r\n";

  // verifica e envia para o ESP8266 o tamanho da string de GET 
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
    
  // o thingspeak precisa de 15 sec de delay entre updates
  delay(16000); 
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
