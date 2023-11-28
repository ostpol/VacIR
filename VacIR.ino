#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266WebServerSecureAxTLS.h>
#include <ESP8266WebServerSecureBearSSL.h>
#include <ESPAsyncUDP.h>
#include <AsyncPrinter.h>
#include <async_config.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncTCPbuffer.h>
#include <SyncClient.h>
#include <tcp_axtls.h>
#include <IRac.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRtimer.h>
#include <IRutils.h>
#include <ir_NEC.h>
#include <ESP8266WiFi.h>

const char* SSID = "";
const char* PSK = "";
ESP8266WebServer server(80); //Server on port 80

IRsend irsend(13);


String getContent()
{
  // create content for the website:
  String content = "<!DOCTYPE html> <html> <head> <title>VacIR</title> <meta charset=\"UTF-8\"> </head> <style type=\"text/css\"> body \{padding-top: 25px\;\} .tg \{border-collapse:collapse\;border-spacing:0\;border:none\;margin:0px auto\; font-size: 175px\;\} .tg td\{font-family:Arial, sans-serif\;padding:10px 13px\;overflow:hidden\;word-break:normal\;\} .tg .tg-lap0\{font-size:100%\;text-align:center\;vertical-align:center\} a \{text-decoration: none\; font-color: black\;\} @media screen and (max-width: 767px) \{.tg \{width: auto !important\;\}.tg col \{width: auto !important\;\}.tg-wrap \{overflow-x: auto\;-webkit-overflow-scrolling: touch\;margin: auto 0px\;\}\}</style> <body> <div class=\"tg-wrap\"> <table class=\"tg\"> <tr> <td class=\"tg-lap0\"><a href=\"/an\">&#x25B6\;</a></td> <td class=\"tg-lap0\"><a href=\"/up\">&#x2B06\;</a></td> <td class=\"tg-lap0\"><a href=\"/aus\">&#x23F9\;</a></td> </tr> <tr> <td class=\"tg-lap0\"><a href=\"/links\">&#x2B05\;</td> <td class=\"tg-lap0\"><a href=\"/station\">&#x1F3E0\;</a></td> <td class=\"tg-lap0\"><a href=\"/rechts\">&#x27A1\;</a></td> </tr> <tr> <td class=\"tg-lap0\"><a href=\"/max\">&#x1F680\;</a></td> <td class=\"tg-lap0\"><a href=\"/kreis\">&#x1F504\;</a></td> <td class=\"tg-lap0\"><a href=\"/kante\">&#x21AA\;</a></td> </tr> </table> </div> </body> </html>";
  return content;
}
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  initWiFi();

  // start HTTP server:
  server.begin();
  Serial.println("HTTP server started");

  // print start page:
  server.on("/", []() {
    server.send(200, "text/html", getContent());
  });

  // control output1:
  server.on("/an", []() {
    irsend.sendNEC(44704477, 32);
    delay(500);
    irsend.sendNEC(44704477, 32);
    Serial.println("AN");
    server.send(200, "text/html", getContent());
    delay(5);
  });

  server.on("/aus", []() {
    irsend.sendNEC(44704477, 32);
    Serial.println("AUS");
    server.send(200, "text/html", getContent());
    delay(5);
  });

  server.on("/station", []() {
    irsend.sendNEC(44730487, 32);
    Serial.println("Ladestation");
    server.send(200, "text/html", getContent());
    delay(5);
  });

  server.on("/links", []() {
    irsend.sendNEC(44708812, 32);
    Serial.println("Links");
    server.send(200, "text/html", getContent());
    delay(5);
  });

  server.on("/up", []() {
    irsend.sendNEC(44717482, 32);
    Serial.println("Up");
    server.send(200, "text/html", getContent());
    delay(5);
  });

  server.on("/rechts", []() {
    irsend.sendNEC(44713147, 32);
    Serial.println("Rechts");
    server.send(200, "text/html", getContent());
    delay(5);
  });

  server.on("/max", []() {
    irsend.sendNEC(44721817, 32);
    Serial.println("MAX");
    server.send(200, "text/html", getContent());
    delay(5);
  });

  server.on("/kreis", []() {
    irsend.sendNEC(44726152, 32);
    Serial.println("Kreis");
    server.send(200, "text/html", getContent());
    delay(5);
  });

  server.on("/kante", []() {
    irsend.sendNEC(44734822, 32);
    Serial.println("Kanten");
    server.send(200, "text/html", getContent());
    delay(5);
  });

}

void loop() {

  if (WiFi.status() != WL_CONNECTED) {
    initWiFi();
  }

  //client.print(output);
  server.handleClient();
}

void initWiFi() {
  WiFi.begin(SSID, PSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();
}
