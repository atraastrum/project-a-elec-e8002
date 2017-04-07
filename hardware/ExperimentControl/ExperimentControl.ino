//This is the code for ExperimentControl Arduino software.

//Place for variables
bool pump_status = false; //variable for pump status
int liquid_used = 1; //variable for liquid usage, 1 = liquid 1 and 2 = liquid 2
String cmd; //string variable for saving the last command

//For testing!!
//int pumpLed = 4;
//int liquid1Led = 5;
//int liquid2Led = 6;
//

//motor
int EnablePin1 = 8;
int duty;
int PWMPinA1 = 11;  // Timer2
int PWMPinB1 = 3;
const byte CPin1 = A0;  // analog input channel
int CRaw1;      // raw A/D value

//Function for starting the pump
void startPump(){
  //Implement your pump starting code here
  digitalWrite(EnablePin1, HIGH); //enable the board
  analogWrite(PWMPinB1, 0);
  for (duty = 0; duty <= 255; duty += 1) // ramp up speed
  {
    analogWrite(PWMPinA1, duty);
    delay(5);
  }
  analogWrite(PWMPinA1, 255);
  //Testing
  //digitalWrite(pumpLed, HIGH);
  Serial.write("Pump started\n");
  //
  pump_status = true; //pump is on
}

//Function for stopping the pump
void stopPump(){
  //Impelement your pump stopping code here
  for (duty = 255; duty >= 0; duty -= 5) // ramp down speed
  {
    analogWrite(PWMPinA1, duty);
    delay(20);
  }
  analogWrite(PWMPinA1, 0); //set to 0 speed
  delay(500);
  //Testing
  //digitalWrite(pumpLed, LOW);
  Serial.write("Pump stopped\n");
  //
  pump_status = false; //pump is off
}

//Function for opening the liquid 1 solenoid and closing the liquid 2 solenoid
void liquid1(){
  /*
   Implement your relay control code here 
   to open liquid 1 and close liquid 2
  */

  //Testing
  //digitalWrite(liquid1Led, HIGH);
  //digitalWrite(liquid2Led, LOW);
  Serial.write("Liquid 1 valve is open\n");
  //
  liquid_used = 1; //set liquid 1 as used
}

void liquid2(){
  /*
   Implement your relay control code here 
   to open liquid 2 and close liquid 1
  */
  
  //Testing
  //digitalWrite(liquid1Led, LOW);
  //digitalWrite(liquid2Led, HIGH);
  Serial.write("Liquid 2 valve is open\n");
  //
  liquid_used = 2; //set liquid 2 as used
}

void setup() {
  //Initialize other needed function here
  pinMode(EnablePin1, OUTPUT);
  pinMode(PWMPinA1, OUTPUT);
  pinMode(PWMPinB1, OUTPUT);
  //
  //testing leds
  //pinMode(pumpLed, OUTPUT);
  //pinMode(liquid1Led, OUTPUT);
  //pinMode(liquid2Led, OUTPUT);
  //
  //Start serial
  Serial.begin(9600);
  //Wait until serial is ready
  while(!Serial){
    ;
  }
  Serial.println("Connection ready");
}

void loop() {
  //Check if serial is available
  cmd = "";
  if(Serial.available()>0){
    char c = Serial.read(); //read one byte coming through the serial
    cmd += c;
    if(cmd == "s"){
      //start command for pump is given
      startPump();
    }
    else if (cmd == "p"){
      //stop command for pump is given
      stopPump();
    }
    else if (cmd == "o"){
      //liquid 1 valve open command is given
      liquid1();
    }
    else if (cmd == "c"){
      //liquid 2 valve open command is given
      liquid2();
    }
  }
}
