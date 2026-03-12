/*Orginal code by Enjoy-Mechatronics

https://github.com/Enjoy-Mechatronics/ESP32-Web-Server

Modified for relay and OLED Screen by Tat-Dan Truong Le

*/

// Load Wi-Fi library
#include <WiFi.h>
// Load SPI library
#include <SPI.h>
//AdaFruit thing
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

//Oled defines
#define screenWidth 128
#define screenHeight 64

#define oledAdress 0x3C

#define oledReset -1

Adafruit_SSD1306 display(screenWidth, screenHeight, &Wire, oledReset);

// Network credentials Here
const char* ssid     = "ESP32-S3-test";
const char* password = "Veldigbrapassord";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

//variables to store the current LED states
String statePin16 = "off";
String statePin17 = "off";
//Output variable to GPIO pins
const int ledPin16 = 3;
const int ledPin17 = 0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds
const long timeoutTime = 2000;


void relay1Circle(String x){
  if(x == "on"){
    display.fillCircle(3, 11, 3, WHITE);
  }
  else{
    display.drawCircle(3, 11, 3, WHITE);
  }
}
void relay2Circle(String x){
  if(x == "on"){
    display.fillCircle(3, 20, 3, WHITE);
  }
  else{
    display.drawCircle(3, 20, 3, WHITE);
  }
}

void setup() {
  // set up the LCD's number of columns and rows:

  // Print a message to the LCD.
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, oledAdress)) {

   Serial.println(F("SSD1306 allocation failed"));
 
  for(;;); // Don't proceed, loop forever
  }

  
  pinMode(ledPin16, OUTPUT);      // set the LED pin mode
  digitalWrite(ledPin16, 0);      // turn LED off by default
  pinMode(ledPin17, OUTPUT);      // set the LED pin mode
  digitalWrite(ledPin17, 0);      // turn LED off by default

  WiFi.softAP(ssid,password);
  
  // Print IP address and start web server
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Screen ON IP: ");
  display.println(WiFi.softAPIP());
  display.println("SSID: \n" + String(ssid));
  display.print("Password: \n" + String(password));
  display.display();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      // loop while the client's connected
      display.setCursor(0, 0);
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        display.clearDisplay();
        display.println("Relay Status");
        header += c;

        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /16/on") >= 0) {
              statePin16 = "on";
              digitalWrite(ledPin16, HIGH);               // turns the LED on
            } else if (header.indexOf("GET /16/off") >= 0) {
              statePin16 = "off";
              digitalWrite(ledPin16, LOW);                //turns the LED 
            }
            
            
            if (header.indexOf("GET /17/on") >= 0) {
              statePin17 = "on";
              digitalWrite(ledPin17, LOW);       // turns the LED on
            } else if (header.indexOf("GET /17/off") >= 0) {
              statePin17 = "off";
              digitalWrite(ledPin17, HIGH);             //turns the LED off
            }
            

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            client.println("<style>html { font-family: monospace; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: yellowgreen; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 32px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: gray;}</style></head>");
            client.println("<body><h1>ESP32 Web Server</h1>");
            client.println("<p>Control Relay State</p>");
            client.println("<p>Relay 1</p>");

            if (statePin16 == "off") {
              client.println("<p><a href=\"/16/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/16/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            if (statePin17 == "off") {
              client.println("<p><a href=\"/17/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/17/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    relay1Circle(statePin16);
    relay2Circle(statePin17);
    display.println("  Relay 1: " + statePin16);
    display.print("  Relay 2: " + statePin17);
    display.display();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
