
#include <AFMotor.h>
AF_DCMotor motor1(2);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.flush();
}

void loop() {
  uint8_t i;
  // put your main code here, to run repeatedly:
  motor1.run(FORWARD);
  for(i=0;i<100;i++){
    motor1.setSpeed(i);
    
  }

  delay(15);
  
  Serial.print("tech");
  

}
