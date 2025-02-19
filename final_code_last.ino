#include <ArduinoBLE.h>

const int button_pin = 3;  // Adjust pin numbers as needed
const int buzzer_pin = 10;
const int pir_pin = 9;
const int led_pin = 5; // New LED pin

const char* targetDeviceAddress = "d0:c9:85:e7:a2:e0"; // Adjust the target BLE device address

int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

bool systemActive = false;
bool pirEnabled = true; // Flag to control PIR sensor state 
bool ledState = false; // Flag to control LED state

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
  pinMode(pir_pin, INPUT);
  pinMode(led_pin, OUTPUT); // Initialize LED pin
  digitalWrite(led_pin, LOW); // Ensure LED is initially off
  digitalWrite(pir_pin, LOW);
  digitalWrite(buzzer_pin, LOW); // Ensure buzzer is initially off
  Serial.begin(9600); // Initialize serial communication if needed

  // Initialize BLE
  if (!BLE.begin()) {
    Serial.println("Failed to initialize BLE!");
    while (1);
  }

  Serial.println("Bluetooth® Low Energy Central scan callback");

  // Set the discovered event handle
  BLE.setEventHandler(BLEDiscovered, bleCentralDiscoverHandler);
}

void loop() {
  // Check PIR sensor
  int pirReading = digitalRead(pir_pin); // Read PIR sensor value
  Serial.println("PIR sensor reading: " + String(pirReading)); // Print PIR sensor value

  if (pirReading == HIGH && !systemActive && pirEnabled) {
    // Motion detected, start BLE scanning
    Serial.println("Starting BLE scanning...");
    BLE.scan(true); // Enable duplicates
    systemActive = true;
  }

  // Check button press to toggle system activation, PIR state, and LED state
  int buttonReading = digitalRead(button_pin);

  if (buttonReading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (buttonReading != buttonState) {
      buttonState = buttonReading;

      if (buttonState == LOW) {
        // Toggle PIR sensor state
        pirEnabled = !pirEnabled;

        // Toggle LED state
        ledState = !ledState;
        digitalWrite(led_pin, ledState ? HIGH : LOW);

        // Stop BLE scanning and turn off buzzer
        Serial.println("Stopping BLE scanning...");
        BLE.stopScan();
        digitalWrite(buzzer_pin, LOW);
        systemActive = false;
      }
    }
  }

  // Check if the second button press occurred and turn off the LED
  if (lastButtonState == LOW && buttonState == HIGH) {
    digitalWrite(led_pin, LOW);
  }

  lastButtonState = buttonReading;

  // Poll the BLE central for events
  BLE.poll();
}

// Callback for BLE discovery
void bleCentralDiscoverHandler(BLEDevice peripheral) {
  // Check if the discovered device is the target
  if (peripheral.address() == targetDeviceAddress) {
    Serial.println("Target device found!");
    // Activate the buzzer until the button is pressed
    digitalWrite(buzzer_pin, HIGH);
  }
}
