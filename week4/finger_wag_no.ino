#include <ESP32Servo.h>

#define SERVO_PIN 13
#define BUTTON_PIN 4

Servo myServo;

bool lastButtonState = HIGH;
unsigned long wagStartTime = 0;
bool wagging = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);  
  myServo.attach(SERVO_PIN);
  myServo.write(90);  
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN);


  if (lastButtonState == HIGH && currentButtonState == LOW && !wagging) {
    wagStartTime = millis();
    wagging = true;
  }

  lastButtonState = currentButtonState;

  if (wagging) {
    // Wag back and forth fast
    static bool wagDirection = false;
    static unsigned long lastWagTime = 0;

    if (millis() - lastWagTime >= 100) {  // 100ms = fast wag
      wagDirection = !wagDirection;
      myServo.write(wagDirection ? 60 : 120);
      lastWagTime = millis();
    }

    // Stop wagging after 5 seconds
    if (millis() - wagStartTime >= 5000) {
      myServo.write(90);  // Return to center
      wagging = false;
    }
  }
}
