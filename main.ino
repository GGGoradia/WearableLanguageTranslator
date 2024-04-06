#include "Audio.h"
#include "CloudSpeechClient.h"
#include "Translate.h"
#include "wifi.h"
const String TranslateApiKey="AIzaSyCbtZr9ZxoC-u5XW6_2RNDjvbH7ojwx_O0";
String transcription;
AsyncWebServer server(80);
WiFiHandler wifiHandler(&server, "ESP32wifi", "12345679");
void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println(F("\r\nRecord start!\r\n"));
  Audio* audio = new Audio(ICS43434);
  audio->Record();
  Serial.println(F("Recording Completed. Now Processing..."));
  CloudSpeechClient* cloudSpeechClient = new CloudSpeechClient(USE_APIKEY);
  cloudSpeechClient->Transcribe(audio);
  String targetLanguage = "fr"; 
  Translate* translator = new Translate(TranslateApiKey);
  String translatedText = translator->translateText(transcription, targetLanguage);
  delete cloudSpeechClient;
  delete audio;
}
void loop() {
}