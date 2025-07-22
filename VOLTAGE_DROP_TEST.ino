// Diode Signal Detector on ESP32
// This program detects high voltage signals using a diode as a protection component.
// The diode ensures that only safe voltages are passed to the ESP32's GPIO pin.

const int signalPin = 23; // Pin connected after the diode

void setup() {
    Serial.begin(115200); // Initialize serial communication at 115200 baud rate
    pinMode(signalPin, INPUT); // Set the signalPin as an input pin

    // Print a message to indicate that the program has started
    Serial.println("Diode Signal Detector Initialized.");
    Serial.println("Monitoring voltage on pin " + String(signalPin) + ".");
    Serial.println("Press any key to start monitoring...");
    
    // Wait for user input to start monitoring (optional)
    while (!Serial.available()) {}
    Serial.read(); // Clear the buffer
}

void loop() {
    static bool lastState = LOW; // To store the previous state of the signal
    int signalState = digitalRead(signalPin); // Read the current state of the signalPin

    // Debounce mechanism: Ensure stable readings by checking for consistent states
    if (signalState != lastState) {
        delay(10); // Small delay to debounce
        signalState = digitalRead(signalPin); // Re-read the pin
    }

    // Check the current state of the signal
    if (signalState == HIGH) {
        Serial.println("High voltage detected!");
    } else {
        Serial.println("No high voltage detected (safe).");
    }

    lastState = signalState; // Update the last state for the next iteration

    delay(500); // Wait for 500 milliseconds before the next reading
}