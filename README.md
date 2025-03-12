# Arduino BLE Motion Detection System

Arduino BLE Motion Detection

## Overview
This project implements a motion detection system using an Arduino-compatible board with Bluetooth Low Energy (BLE) capabilities. The system utilizes a Passive Infrared (PIR) sensor to detect motion and triggers a Bluetooth scan to locate a target device. If the target device is found, an alarm (buzzer) is activated. The system can be controlled via a push button that toggles the PIR sensor and an LED indicator.

## Features
- Motion detection using a PIR sensor
- BLE scanning to detect a specific device
- Buzzer alarm upon detecting the target device
- Toggle button to enable/disable motion detection and LED indicator
- LED indicator to show the system status
- Debounced button handling
- 3D printed case for the PIR sensor

## Hardware Requirements
- Arduino board with BLE support (e.g., Arduino Nano 33 BLE, ESP32, etc.)
- PIR motion sensor
- Push button
- Buzzer
- LED
- Resistors and jumper wires as needed

## Pin Configuration
| Component  | Arduino Pin |
|------------|------------|
| Button     | 3          |
| Buzzer     | 10         |
| PIR Sensor | 9          |
| LED        | 5          |

## Software Requirements
- Arduino IDE
- `ArduinoBLE` library

## Installation & Setup
1. Install the Arduino IDE from [Arduino Website](https://www.arduino.cc/en/software).
2. Install the `ArduinoBLE` library via the Library Manager in the Arduino IDE.
3. Clone this repository:
   ```sh
   git clone https://github.com/yourusername/arduino-ble-motion-detection.git
   ```
4. Connect the hardware components as per the pin configuration.
5. Open the project in Arduino IDE and upload the code to your Arduino board.
6. Open the Serial Monitor to view logs and debug information.

## How It Works
1. The system starts with the PIR sensor enabled.
2. When motion is detected, it triggers a BLE scan for the target device.
3. If the target device is found, the buzzer is activated.
4. The button can be pressed to toggle the PIR sensor state and the LED indicator.
5. Pressing the button again stops the BLE scan and turns off the buzzer.

## Code Breakdown
- **Setup:** Initializes the pins, serial communication, and BLE.
- **Loop:** Continuously checks for PIR sensor activation, button presses, and BLE events.
- **BLE Discovery Handler:** Checks if the detected BLE device matches the target address and activates the buzzer if a match is found.

## Customization
- Modify `targetDeviceAddress` in the code to change the target BLE device.
- Adjust `debounceDelay` if needed for different button responsiveness.
- Change pin assignments as required for different hardware configurations.

## Troubleshooting
- If the BLE scan does not start, check if the board supports BLE and that the `ArduinoBLE` library is installed correctly.
- If the PIR sensor does not trigger, verify wiring and sensor functionality.
- If the button is unresponsive, check debounce settings and wiring.

## Contributing
Contributions are welcome! Feel free to open an issue or submit a pull request.

## License
This project is open-source and can be modified and shared.

## Author
Ofek Barzilay

