#define oil_limit 1600 ///Threshold for warning

///Importing required library
#include <Wifi.h>
#include <WifiCLient.h>
#include <WebServer.h> 
#include <index.h> ///Webpage header

const char* SSID "Test_Wifi"; ///Wifi Name
const char* PSSWRD "08071202abcd";///Wifi Password

WifiServer server (80); ///Web server port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleADC() {
 int a = analogRead(A0);
 String adcValue = String(a);
 
 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}

void setup() {
   Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Sketch...");

/*
//ESP32 As access point
  WiFi.mode(WIFI_AP); //Access Point mode
  WiFi.softAP(ssid, password);
*/
//ESP32 connects to your wifi -----------------------------------
  WiFi.mode(WIFI_STA); //Connectto your wifi
  WiFi.begin(SSID, PSSWRD);

  Serial.println("Connecting to ");
  Serial.print(SSID);

  //Wait for WiFi to connect
  while(WiFi.waitForConnectResult() != WL_CONNECTED){      
      Serial.print(".");
    }
    
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
//----------------------------------------------------------------
 
  server.on("/", handleRoot);      //This is display page
  server.on("/readADC", handleADC);//To get update of ADC Value only
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

}
//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void loop() {
  server.handleClient();
  delay(1);

}
