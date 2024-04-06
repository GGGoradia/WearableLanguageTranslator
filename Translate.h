#ifndef TRANSLATE_H
#define TRANSLATE_H

#include <Arduino.h>

class Translate {
public:
    Translate(String TranslateApiKey);
    String translateText(String text, String targetLanguage);

private:
    String TranslateApiKey; // Member variable to store API key
};

#endif
