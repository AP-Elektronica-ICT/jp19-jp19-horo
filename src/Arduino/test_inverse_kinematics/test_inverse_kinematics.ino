// Arduino/Teensy example for Arduino Braccio

// Include the library InverseK.h
#include <InverseK.h>
#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;
void setup() {
  Serial.begin(9600);
  // Setup the lengths and rotation limits for each link
  Link base, upperarm, forearm, hand;
  
  base.init(0, b2a(0.0), b2a(180.0));
  upperarm.init(200, b2a(15.0), b2a(165.0));
  forearm.init(200, b2a(0.0), b2a(180.0));
  hand.init(270, b2a(0.0), b2a(180.0));

  // Attach the links to the inverse kinematic model
  InverseK.attach(base, upperarm, forearm, hand);

 

  // InverseK.solve() return true if it could find a solution and false if not. 
  
  // Calculates the angles without considering a specific approach angle
  // InverseK.solve(x, y, z, a0, a1, a2, a3)
 
  
 Braccio.begin();
}

void loop() {
   float a0, a1, a2, a3;
   if(InverseK.solve(500, -200, 50, a0, a1, a2, a3)) {
    Serial.print(a2b(a0)); Serial.print(',');
    Serial.print(a2b(a1)); Serial.print(',');
    Serial.print(a2b(a2)); Serial.print(',');
    Serial.println(a2b(a3));
  } else {
     Braccio.ServoMovement(20,90,90, 90, 90, 90,  60);
  }
  
   Braccio.ServoMovement(20,a2b(a0),a2b(a1), a2b(a2), a2b(a3), 90,  60);
   while(true){
    
   }
}

// Quick conversion from the Braccio angle system to radians 
float b2a(float b){ 
  return b / 180.0 * PI - HALF_PI;
}

// Quick conversion from radians to the Braccio angle system
float a2b(float a) { 
  return (a + HALF_PI) * 180 / PI;
}
