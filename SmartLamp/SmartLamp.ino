#include <stdio.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

#define HTTP_REST_PORT 80
#define WIFI_RETRY_DELAY 500
#define MAX_WIFI_INIT_RETRY 50

#define red_LED 0
#define green_LED 5
#define blue_LED 4

struct Led {
    int id;
    int red;
    int green;
    int blue;
    int status;
    float brightness;
} led_resource;

const char* wifi_ssid = "OutOfBoundsError";
const char* wifi_passwd = "YouWillNeverGuess7";

ESP8266WebServer http_rest_server(HTTP_REST_PORT);

/* 
This code does not support driving multiple led strips. There should be an ESP8266 board for
each led strip.
*/

void init_led_resource()
{
    led_resource.red = 0;
    led_resource.green = 0;
    led_resource.blue = 0;
    led_resource.status = 0;
    led_resource.brightness = 1.0;
}

int init_wifi() {
    int retries = 0;

    Serial.println("Connecting to WiFi AP..........");

    WiFi.mode(WIFI_STA);
    WiFi.begin(wifi_ssid, wifi_passwd);
    // check the status of WiFi connection to be WL_CONNECTED
    while ((WiFi.status() != WL_CONNECTED) && (retries < MAX_WIFI_INIT_RETRY)) {
        retries++;
        delay(WIFI_RETRY_DELAY);
        Serial.print("#");
    }
    return WiFi.status(); // return the WiFi connection status
}

void json_to_resource(StaticJsonDocument<500> &jsonBody) {
    led_resource.red = jsonBody["red"];
    led_resource.green = jsonBody["green"];
    led_resource.blue = jsonBody["blue"];
    led_resource.status = jsonBody["status"];

    Serial.println(led_resource.red);
    Serial.println(led_resource.green);
    Serial.println(led_resource.blue);
    Serial.println(led_resource.status);
}

StaticJsonDocument<500> get_jsonBody(String post_body) {
    StaticJsonDocument<500> jsonBody;
    DeserializationError error = deserializeJson(jsonBody, post_body);

    return jsonBody;
}

void update_led_state() {
    if (led_resource.status == 1) {
        analogWrite(red_LED, int(led_resource.red * led_resource.brightness));
        analogWrite(green_LED, int(led_resource.green * led_resource.brightness));
        analogWrite(blue_LED, int(led_resource.blue * led_resource.brightness));
    }
    else {
        analogWrite(red_LED, 1024);
        analogWrite(green_LED, 1024);
        analogWrite(blue_LED, 1024);
    }
}

void get_led() {
    StaticJsonDocument<300> doc;
    char JSONmessageBuffer[300];

    doc["red"] = led_resource.red;
    doc["green"] = led_resource.green;
    doc["blue"] = led_resource.blue;
    doc["status"] = led_resource.status;
    doc["brightness"] = led_resource.brightness;
    
    serializeJson(doc, Serial);
    serializeJson(doc, JSONmessageBuffer);
    http_rest_server.send(200, "application/json", JSONmessageBuffer);
}


void turn_on_led() {
    led_resource.status = 1;
    update_led_state();

    http_rest_server.send(200, "text/html", "[+] Successfully turned on LED");
}

void turn_off_led() {
    led_resource.status = 0;
    update_led_state();

    http_rest_server.send(200, "text/html", "[+] Successfully turned on LED");
}

void color_led() {
    StaticJsonDocument<500> jsonBody;
    DeserializationError error = deserializeJson(jsonBody, http_rest_server.arg("plain"));

    if (error) {
        http_rest_server.send(302, "text/html", "[!] Error message");
    }
    else {
        if (jsonBody.containsKey("color")) {
            http_rest_server.send(200, "text/html", "[!] Color names not yet supported");    
        }
        else if (jsonBody.containsKey("red")  && jsonBody.containsKey("green")  && jsonBody.containsKey("blue")) {
            led_resource.red = jsonBody["red"];
            led_resource.blue = jsonBody["blue"];
            led_resource.green = jsonBody["green"];
            update_led_state();
            http_rest_server.send(200, "text/html", "[+] Successfully changed LED color");
        }
        else http_rest_server.send(304, "text/html", "[!] Color missing");
    }
}

void brightness_led() {
    StaticJsonDocument<500> jsonBody;
    DeserializationError error = deserializeJson(jsonBody, http_rest_server.arg("plain"));

    if (error) {
        http_rest_server.send(302, "text/html", "[!] Error message");
    }
    else {
        if (jsonBody.containsKey("brightness") && jsonBody["brightness"] <= 1) {
            led_resource.brightness = jsonBody["brightness"];
            update_led_state();
            http_rest_server.send(200, "text/html", "[+] Successfully changed LED brightness");

        }
        else http_rest_server.send(303, "text/thml", "[!] brightness value range: 0 to 1");
    }
}

void incbright() {
    StaticJsonDocument<500> jsonBody;
    DeserializationError error = deserializeJson(jsonBody, http_rest_server.arg("plain"));

    if (error) {
        http_rest_server.send(302, "text/html", "[!] Error message");
    }
    else {
        http_rest_server.send(200, "text/html", "[+] Successfully increased LED brightness");
    }
}

void decbright() {
    StaticJsonDocument<500> jsonBody;
    DeserializationError error = deserializeJson(jsonBody, http_rest_server.arg("plain"));

    if (error) {
        http_rest_server.send(302, "text/html", "[!] Error message");
    }
    else {
        http_rest_server.send(200, "text/html", "[+] Successfully descreased LED brightness");
    }
}

void test_api_json() {
    StaticJsonDocument<500> jsonBody;
    DeserializationError error = deserializeJson(jsonBody, http_rest_server.arg("plain"));

    if (error) {
        http_rest_server.send(302, "text/html", "[!] Error message");
    }
    else {
        if (!jsonBody.containsKey("test")) {
            http_rest_server.send(200, "text/html", "[+] json key test passed");
        }
        else if (jsonBody["test"] != NULL) {
            http_rest_server.send(200, "text/html", "[+] NULL test passed");
        }
        else if (jsonBody["test"] != "") {
            http_rest_server.send(200, "text/html", "[+] Empty string test passed");
        }
        else {
            http_rest_server.send(200, "text/html", "[+] Test failed");
        }
    }
}

void test_api_param() {
  if (http_rest_server.hasArg("arg")) {
    http_rest_server.send(200, "text/html", "[+] Test worked!");
  }
  else {
    http_rest_server.send(333, "text/html", "[!] Test didn't work...");
  }
}

void config_rest_server_routing() {
    http_rest_server.on("/", HTTP_GET, []() {
        http_rest_server.send(200, "text/html",
            "Welcome to the ESP8266 REST Web Server\n");
    });
    http_rest_server.on("/leds", HTTP_GET, get_led);
    http_rest_server.on("/turn_on", HTTP_GET, turn_on_led);
    http_rest_server.on("/turn_off", HTTP_GET, turn_off_led);
    http_rest_server.on("/color", HTTP_POST, color_led);
    http_rest_server.on("/brightness", HTTP_POST, brightness_led);
    http_rest_server.on("/incbright", HTTP_GET, incbright);
    http_rest_server.on("/decbright", HTTP_GET, decbright);

    http_rest_server.on("/test", HTTP_GET, test_api_param);
    http_rest_server.on("/test", HTTP_POST, test_api_json);
}

void setup(void) {
    Serial.begin(115200);

    init_led_resource();
    if (init_wifi() == WL_CONNECTED) {
        Serial.print("Connetted to ");
        Serial.print(wifi_ssid);
        Serial.print("--- IP: ");
        Serial.println(WiFi.localIP());
    }
    else {
        Serial.print("Error connecting to: ");
        Serial.println(wifi_ssid);
    }

    config_rest_server_routing();

    http_rest_server.begin();
    Serial.println("HTTP REST Server Started");
}

void loop(void) {
    http_rest_server.handleClient();
}
