#include "Button.hpp"

// Simulated button states for testing
bool simulatedButtonState = false;

// Mock function to simulate hardware input
bool mockGetButtonState() {
    return simulatedButtonState;
}

// Create an instance of the Button class
Button testButton(1000); // Long press threshold = 1000ms

void setup() {
    Serial.begin(9600);

    Serial.println("Starting Button Test...");
}

void loop() {
    // Simulate short press
    simulatedButtonState = true;  // Button pressed
    testButton.update(mockGetButtonState());
    delay(200);                   // Hold button for 200ms
    simulatedButtonState = false; // Button released
    testButton.update(mockGetButtonState());
    if (testButton.isShortPress()) {
        Serial.println("Short press detected!");
    } else {
        Serial.println("Short press NOT detected!");
    }

    delay(1000); // Wait for a second before testing long press

    // Simulate long press
    simulatedButtonState = true;  // Button pressed
    testButton.update(mockGetButtonState());
    delay(1500);                  // Hold button for 1500ms (greater than threshold)
    testButton.update(mockGetButtonState());
    if (testButton.isLongPress()) {
        Serial.println("Long press detected!");
    } else {
        Serial.println("Long press NOT detected!");
    }

    simulatedButtonState = false; // Button released
    testButton.update(mockGetButtonState());

    // Delay before the next test iteration
    delay(2000);
}
