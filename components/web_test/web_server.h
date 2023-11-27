#pragma once
#include <Arduino.h>
#include <MongooseCore.h>
#include <MongooseHttpServer.h>


#include "esphome/core/component.h"
#include "esphome/core/controller.h"
#include "esphome/components/network/util.h"



namespace esphome {
namespace web_server {
    


class WebServer : public Controller, public Component {
 public:
  WebServer(){};
  
// Copyright (c) 2015 Cesanta Software Limited
// All rights reserved

static void notFound(MongooseHttpServerRequest *request)
{
  request->send(404, "text/plain", "Not found");
}

MongooseHttpServer server;
const char *PARAM_MESSAGE = "message";

bool serverSetup () {
    bool started=false;
    server.begin(88);

  server.on("/$", HTTP_GET, [](MongooseHttpServerRequest *request) {
    request->send(200, "text/plain", "Hello world");
  });

  // Send a GET request to <IP>/get?message=<message>
  server.on("/get$", HTTP_GET, [](MongooseHttpServerRequest *request) {
    String message;
  /*  if (request->hasParam(PARAM_MESSAGE))
    {
      message = request->getParam(PARAM_MESSAGE);
    }
    else
    {
      message = "No message sent";
    }
    */
    request->send(200, "text/plain", "Hello, GET: " + message);
  });

  // Send a POST request to <IP>/post with a form field message set to <message>
  server.on("/post$", HTTP_POST, [](MongooseHttpServerRequest *request) {
    String message;
    /*if (request->hasParam(PARAM_MESSAGE))
    {
      message = request->getParam(PARAM_MESSAGE);
    }
    else
    {
      message = "No message sent";
    }
    */
    request->send(200, "text/plain", "Hello, POST: " + message);
  });

  // Test the basic response class
  server.on("/basic$", HTTP_GET, [](MongooseHttpServerRequest *request) {
    MongooseHttpServerResponseBasic *resp = request->beginResponse();
    resp->setCode(200);
    resp->setContentType("text/html");
    resp->addHeader("Cache-Control", "max-age=300");
    resp->addHeader("X-hello", "world");
    resp->setContent(
      "<html>\n"
      "<head>\n"
      "<title>Basic Page</title>\n"
      "</head>\n"
      "<body>\n"
      "<h1>Basic Page</h1>\n"
      "<p>\n"
      "This page has been sent using the MongooseHttpServerResponseBasic class\n"
      "</p>\n"
      "</body>\n"
      "</html>\n");
    request->send(resp);
  });

  // Test the stream response class
  server.on("/stream$", HTTP_GET, [](MongooseHttpServerRequest *request) {
    MongooseHttpServerResponseStream *resp = request->beginResponseStream();
    resp->setCode(200);
    resp->setContentType("text/html");
    resp->addHeader("Cache-Control", "max-age=300");
    resp->addHeader("X-hello", "world");

    resp->println("<html>");
    resp->println("<head>");
    resp->println("<title>Stream Page</title>");
    resp->println("</head>");
    resp->println("<body>");
    resp->println("<h1>Stream Page</h1>");
    resp->println("<p>");
    resp->println("This page has been sent using the MongooseHttpServerResponseStream class");
    resp->println("</p>");
    resp->println("<p>");
    resp->printf("micros = %lu<br/>", micros());
    resp->printf("free = %u<br/>", ESP.getFreeHeap());
    resp->println("</p>");
    resp->println("</body>");
    resp->println("</html>");

    request->send(resp);
  });

  server.onNotFound(notFound);
  return true;
    
}
  void setup() {
Serial.begin(115200);


  
  
  
  }
bool firstrun=true;
void loop() 
{
   if (firstrun && network::is_connected()) {
       Mongoose.begin();       
       serverSetup();
       firstrun=false;
   }
   if (network::is_connected())
    Mongoose.poll(0);
  //Serial.printf("Free memory %u\n", ESP.getFreeHeap());
}

  void dump_config() {};

};

}  // namespace web_server
}  // namespace esphome
