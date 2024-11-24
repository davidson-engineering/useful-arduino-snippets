#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <Arduino.h>

class Button {
private:
    bool previousState;        // Previous button state
    bool currentState;         // Current button state
    unsigned long pressTime;   // Time when the button was first pressed
    unsigned long threshold;   // Long press threshold in milliseconds
    bool isPressed;            // Whether the button is currently being pressed
    bool longPressTriggered;   // To prevent multiple long press triggers

public:
    // Constructor
    Button(unsigned long longPressThreshold = 1000)
        : previousState(false), currentState(false),
          pressTime(0), threshold(longPressThreshold),
          isPressed(false), longPressTriggered(false) {}

    // Update button state
    void update(bool buttonState) {
        previousState = currentState;
        currentState = buttonState;

        if (currentState && !previousState) {
            // Button just pressed
            pressTime = millis();
            isPressed = true;
            longPressTriggered = false;
        } else if (!currentState && previousState) {
            // Button just released
            isPressed = false;
        }
    }

    // Check for short press
    bool isShortPress() {
        if (!isPressed && previousState && (millis() - pressTime < threshold)) {
            // Button was released before the threshold
            return true;
        }
        return false;
    }

    // Check for long press
    bool isLongPress() {
        if (isPressed && (millis() - pressTime >= threshold) && !longPressTriggered) {
            // Long press detected
            longPressTriggered = true;
            return true;
        }
        return false;
    }
};

#endif // BUTTON_HPP
