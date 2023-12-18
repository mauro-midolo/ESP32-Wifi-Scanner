# ESP32 WiFi Scanner

This project utilizes the Arduino framework and the Heltec library to implement a WiFi scanner on ESP32. The sketch scans the surrounding WiFi networks and displays the results on an OLED display

## Requirements

- ESP32 board
- OLED display (using the Heltec library)
- Arduino WiFi library

## Getting Started

1. Upload the sketch to the ESP32 using the Arduino IDE.
2. Ensure you have the Heltec library installed for the OLED display.
3. Connect the OLED display to the ESP32.
4. Power up the ESP32 and observe the WiFi scanner in action.

## Configuration

The project is configured to use the `IndexedLogDisplay` class to display WiFi scanning results on an OLED display. Customize the hardware and code according to your needs.

```cpp
// Example usage of the IndexedLogDisplay class
IndexedLogDisplay indexedLogDisplay;

void setup() {
  // Initialize the display and add an initial message
  indexedLogDisplay.begin();
  indexedLogDisplay.add(1, "Wifi Scanner...");
  // Other configurations...
}

void loop() {
  // Scan for WiFi networks and display results on the OLED
  // Other operations...
}
