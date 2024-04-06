#include "Translate.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
Translate::Translate(String TranslateApiKey) {
    this->TranslateApiKey = TranslateApiKey; // Initialize API key
}

String Translate::translateText(String text, String targetLanguage) {
    String translatedText = ""; // Initialize translated text

    // Construct the URL for translation API
    String url = "https://translation.googleapis.com/language/translate/v2?key=";
    url += TranslateApiKey; // Use apiKey member variable

    // Construct the request payload
    String payload = "q=" + text;
    payload += "&target=" + targetLanguage;

    // Send HTTP POST request to translation API
    HTTPClient http;
    http.begin(url); // Specify the URL
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); // Set content type

    // Send the POST request and collect response
    int httpResponseCode = http.POST(payload);
    if (httpResponseCode > 0) {
        if (httpResponseCode == HTTP_CODE_OK) {
            String response = http.getString(); // Get response
            // Parse JSON response
            DynamicJsonDocument jsonBuffer(1024);
            deserializeJson(jsonBuffer, response);
            translatedText = jsonBuffer["data"]["translations"][0]["translatedText"].as<String>(); // Extract translated text
        } else {
            Serial.print("HTTP Error: ");
            Serial.println(httpResponseCode);
        }
    } else {
        Serial.println(F("HTTP request failed"));
    }

    http.end(); // Close connection

    return translatedText;
}

