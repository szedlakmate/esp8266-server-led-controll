/** 
*     SOURCE:
*     https://techtutorialsx.com/2017/03/26/esp8266-webserver-accessing-the-body-of-a-http-request/
*
*     Example to send data to the ESP: curl -X POST -d "Hola" http://192.168.50.18:3000/body
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Credentials
#if defined __has_include
#if __has_include("credentials.h")
#include "credentials.h"
#else
// if you dont have a credentials.h file you can set them manually here
#define WIFI_SSID "Wifi SSID"
#define WIFI_PASS "password"
#endif
#endif


ESP8266WebServer server(3000);

void setup() {

  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); 

  WiFi.begin(WIFI_SSID, WIFI_PASS);  //Connect to the WiFi network
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection

    delay(500);
    Serial.println("Waiting to connect...");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP

  server.on("/blink", handleBody);  //Associate the handler function to the path

  server.begin();  //Start the server
  Serial.println("Server listening");
}

void loop() {

  server.handleClient();  //Handling of incoming requests
}

void handleBody() {  //Handler for the body path

  if (server.hasArg("plain") == false) {  //Check if body received

    server.send(200, "text/plain", "Body not received");
    return;
  }

  String command = server.arg("plain");
  server.send(200);

  Serial.println(command);
  handleCommand(command);
}

void handleCommand(String command) {
  
  // Controll built-in LED
  if (command == "true") {
    Serial.println("Turn led ON");
    digitalWrite(LED_BUILTIN, LOW);

  } else if (command == "false") {
    Serial.println("Turn led OFF");
    digitalWrite(LED_BUILTIN, HIGH);
  }
}