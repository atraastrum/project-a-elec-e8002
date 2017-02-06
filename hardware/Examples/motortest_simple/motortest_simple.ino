//include the libraries here
#include <AFMotor.h>

//define motors
AF_DCMotor motor(2);

void setup() {
  //Setup the serial
  Serial.begin(9600);
  //Print simple message to serial monitor
  Serial.println("Simple motor test - Let's start!");
}

void loop() {
    Serial.println("Forward");
    //Set the speed of motor
    motor.run(FORWARD); //direction
    motor.setSpeed(150); //speed set
    delay(3000); //3 s delay
    Serial.println("Backward");
    motor.run(BACKWARD);
    motor.setSpeed(100);
    delay(4000);
    //Acceleration + decceleration
    Serial.println("Acceleration forward");
    motor.run(FORWARD);
    for(int i=0; i<255; i++){
      motor.setSpeed(i);
      delay(10);
    }
    Serial.println("Decceleration forward");
    for(int i=255;i!=0;i--){
      motor.setSpeed(i);
      delay(10);
    }
    delay(2000);
}
