// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"             // Include Emon Library
EnergyMonitor emon1;             // Create an instance

#include <SPI.h>
#include <Ethernet.h>

//Definicoes de IP, mascara de rede e gateway
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,88);          //Define o endereco IP
IPAddress gateway(192,168,1,1);     //Define o gateway
IPAddress subnet(255, 255, 255, 0); //Define a máscara de rede
 
//Inicializa o servidor web na porta 80
EthernetServer server(80);

void setup()
{  
  Serial.begin(9600);
  
  emon1.voltage(1, 114.57, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(4, 111.1);       // Current: input pin, calibration.


  //ethernet
    //Inicializa a interface de rede
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
}

void loop()
{
  emon1.calcVI(20,2000);         // Calculate all. No.of half wavelengths (crossings), time-out
  emon1.serialprint();           // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  
  float realPower       = emon1.realPower;        //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;    //extract Apparent Power into variable
  float powerFActor     = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;             //extract Vrms into Variable
  float Irms            = emon1.Irms;             //extract Irms into Variable


//--------------------
//ethernet block

 //Aguarda conexao do browser
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == 'n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 3"); //Recarrega a pagina a cada 2seg
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head>");
          
          client.println("<title>Ductor AGT - Power Supervising</title>");
          client.println("<meta http-equiv='Content-Type' content='text/html; charset=ISO-8859-1'>");
          client.println("<meta name='viewport' content='width=720, initial-scale=0.5' />");
          client.println("</head>");
          client.println("<body>");
          
          client.println("<div id='wrapper' align='center'><img alt='DuctorAGT' src='http://www.fundacity.com/media/cache/project_260/82bc86b85bfbf95d7c40b5d6822656934e25a038.jpg'/><br/>");          
          client.println("</div>");
          //Configura o texto e imprime o titulo no browser
          client.println("<div align='center'>");
          client.print("<font color=#00FF00><b><u>");
          client.print("Power Meter");
          client.print("</u></b></font>");
          client.println("<br />");
          client.println("<br />");
          //Mostra o estado da porta digital 3
          client.print("Real Power : ");
          client.print("<b>");
          client.print(realPower);
          client.print(" W");
          client.println("</b>");
          client.println("<br />");
          //Mostra as informacoes lidas pelo sensor ultrasonico
          client.print("Aparent Power : ");
          client.print("<b>");
          client.print(apparentPower);
          client.print(" W");
          client.println("</b>");
          client.println("<br />");
          //Mostra o estado da porta digital 3
          client.print("Power Factor : ");
          client.print("<b>");
          client.print(powerFActor);
          client.println("</b>");
          client.println("<br />");
          //Mostra as informacoes lidas pelo sensor ultrasonico
          client.print("Supply Voltage : ");
          client.print("<b>");
          client.print(supplyVoltage);
          client.print(" Vrms");
          client.println("</b>");
          client.println("<br />");
          //Mostra as informacoes lidas pelo sensor ultrasonico
          client.print("Current : ");
          client.print("<b>");
          client.print(Irms);
          client.print(" A");
          client.println("</b>");
          client.println("<br /></b>");
          client.println("</div>");
          
          client.println("</body>");
          client.println("</html>");
          break;
        }
        if (c == 'n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != 'r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    }
    
    
    
  
}
