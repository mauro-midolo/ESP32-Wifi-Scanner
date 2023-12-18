#include <Arduino.h>
#include <Heltec.h>
#include "WiFi.h"

class IndexedLogDisplay
{
private:
  static const int NUM_LINES = 6;    // Numero massimo di righe da visualizzare
  static const int LINE_HEIGHT = 10; // Altezza di ciascuna riga

  struct LogEntry
  {
    int lineNumber;
    String text;
  };

  String entries[NUM_LINES];
  bool initialized;

public:
  IndexedLogDisplay() : initialized(false) {}

  void begin()
  {
    Heltec.begin(true /* DisplayEnable Enable */, false /* LoRa Disable */, false /* Serial Enable */);
    initialized = true;
  }

  void clean()
  {
    for (int i = 0; i < NUM_LINES; i++)
    {
      entries[i] = "";
    }
    drawLog();
  }

  void add(int index, const String &logText)
  {
    if (!initialized)
    {
      Serial.println("Errore: Chiamare begin() prima di utilizzare la classe IndexedLogDisplay.");
      return;
    }

    if (index < 0 || index > NUM_LINES - 1)
    {
      Serial.println("Errore: L'indice di inserimento deve essere compreso tra 1 e " + String(NUM_LINES));
      return;
    }

    // Aggiungi l'entry alla lista
    entries[index] = logText;

    // Disegna il log sul display
    drawLog();
  }

private:
  void drawLog()
  {
    Heltec.display->clear();

    // Calcola la posizione iniziale per disegnare il testo
    int startY = 0;

    for (int i = 0; i < NUM_LINES; i++)
    {
      Heltec.display->drawString(0, startY + i * LINE_HEIGHT, entries[i]);
    }

    Heltec.display->display();
  }
};

// Usa la classe IndexedLogDisplay
IndexedLogDisplay indexedLogDisplay;

void setup()
{
  Serial.begin(115200);
  indexedLogDisplay.begin();
  indexedLogDisplay.add(0, "Wifi Scanner...");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop()
{
  int n = WiFi.scanNetworks();
  if (n == 0)
  {
    indexedLogDisplay.add(0, "No Connection found...");
  }
  else
  {
    for (int i = 0; i < n; ++i)
    {
      String result = "";
      result += String(i + 1) + " | " + WiFi.SSID(i).c_str();
      indexedLogDisplay.add(i, result);
      delay(10);
    }
  }

  WiFi.scanDelete();
  delay(5000);
}