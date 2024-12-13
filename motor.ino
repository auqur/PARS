#include <AccelStepper.h>

// Pin definitions
#define STEP_PIN  32  // GPIO pin connected to DRV8825 STEP pin
#define DIR_PIN   26  // GPIO pin connected to DRV8825 DIR pin

// Motor setup
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// M1 HIGH || M0 & M2 LOW
#define STEP_ANGLE 0.45

// Predefined angles to rotate to (can be customized as needed)
int predefinedAngles[] = {60, 120, 180, -60, -120, -180, 5, 10, 15, -5, -10, -15};  // List of angles in degrees
int currentIndex = 0;  // Keeps track of which angle to execute next

void setup() {
  Serial.begin(115200);
  delay(2000);  

  stepper.setMaxSpeed(3000);    // Set maximum speed in steps per second
  stepper.setAcceleration(2000); // Set acceleration in steps per second^2
  
  Serial.println("Press any key to execute the next predefined rotation.");
}

void loop() {
  if (Serial.available()) {
    Serial.read();  // Read any key from the user (doesn't matter what key it is)
    
    int angle = predefinedAngles[currentIndex];
    
    if (angle > 0) {
      rotateClockwise(angle);
    } else if (angle < 0) {
      rotateCounterClockwise(-angle);
    }
    
    currentIndex++;
    if (currentIndex >= sizeof(predefinedAngles) / sizeof(predefinedAngles[0])) {
      currentIndex = 0;  // Loop back to the first angle in the list
      Serial.println("All angles executed. Restarting from the beginning.");
    } else {
      Serial.print("Next angle: ");
      Serial.println(predefinedAngles[currentIndex]);
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
