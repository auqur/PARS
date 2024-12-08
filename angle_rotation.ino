#include <Arduino.h>
#include <AccelStepper.h>

// Pin definitions
#define STEP_PIN  14  // GPIO pin connected to DRV8825 STEP pin
#define DIR_PIN   12  // GPIO pin connected to DRV8825 DIR pin

// Motor setup
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// M1 HIGH || M0 & M2 LOW
#define STEP_ANGLE 0.45

void setup() {
  Serial.begin(115200);
  delay(2000);  

  stepper.setMaxSpeed(2000);    // Set maximum speed in steps per second
  stepper.setAcceleration(1000); // Set acceleration in steps per second^2
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command.startsWith("rotate")) {
      int angle = command.substring(7).toInt();

      if (angle > 0) {
        rotateClockwise(angle);
      } else if (angle < 0) {
        rotateCounterClockwise(-angle);
      } else {
        Serial.println("Invalid angle");
      }
    }
  }
}

void rotateClockwise(int angle) {
  int steps = angle / STEP_ANGLE;  
  stepper.move(-steps);            
  while (stepper.distanceToGo() != 0) {
    stepper.run();                
  }
  Serial.print("Rotated ");
  Serial.print(angle);
  Serial.println(" degrees clockwise.");
}

void rotateCounterClockwise(int angle) {
  int steps = angle / STEP_ANGLE;  
  stepper.move(steps);           
  while (stepper.distanceToGo() != 0) {
    stepper.run();               
  }
  Serial.print("Rotated ");
  Serial.print(angle);
  Serial.println(" degrees counterclockwise.");
}
