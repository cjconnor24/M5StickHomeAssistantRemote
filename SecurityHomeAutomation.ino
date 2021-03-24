
#include <M5StickCPlus.h>
#include <WiFi.h>
#include <HTTPClient.h>

void output_log_and_screen(char *msg);
void postRequest(char *webhook);

const char *ssid = "sidname";
const char *password = "pwd";

void setup()
{

  M5.begin();
  Serial.begin(115200);

  delay(4000);

  M5.Lcd.println("Booting up security activator");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    output_log_and_screen("Connecting to WiFi..");
  }

  output_log_and_screen("Connected to the WiFi network");
}

void output_log_and_screen(char *msg)
{
  Serial.println(msg);
  M5.Lcd.println(msg);
}

void loop()
{

  M5.update();

  if (M5.BtnB.wasPressed())
  {
    output_log_and_screen("Button B pressed");
    postRequest("http://192.168.100.105:8123/api/webhook/deactivate_security");
  }

  if (M5.BtnA.wasPressed())
  {

    output_log_and_screen("Main button pressed");

    postRequest("http://192.168.100.105:8123/api/webhook/activate_security");
  }

  delay(100);
}

void postRequest(char *webhook)
{
  HTTPClient http;

  http.begin(webhook);
  http.addHeader("Content-Type", "text/plain");

  int httpResponseCode = http.POST("POSTING from ESP32");
  M5.Lcd.println("Sending request to HASS");

  if (httpResponseCode > 0)
  {

    String response = http.getString();

    Serial.println(httpResponseCode);
    Serial.println(response);

    M5.Lcd.println(httpResponseCode);
    M5.Lcd.println(response);
  }
  else
  {

    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
    M5.Lcd.println("Something went wrong with post");
    M5.Lcd.println(httpResponseCode);
  }

  http.end();
}
