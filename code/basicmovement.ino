///////////////////////////////////////////////////////////////////
//-- Movement Functions ---------------------------------------------//
//These are some functions to move your ottobot---------------------------//
///////////////////////////////////////////////////////////////////
//   Otto.walk(2,1000,1);
//   Otto.walk(2,1000,-1); //2 steps, T, -1 BACKWARD 
//   Otto.turn(2,1000,1);//3 steps turning LEFT
//   Otto.turn(2,1000,-1);//3 steps turning RIGHT 
//   Otto.bend (1,500,1); //usually steps =1, T=2000
//   Otto.bend (1,2000,-1);     
//   Otto.shakeLeg (1,1500, 1);
//   Otto.shakeLeg (1,2000,-1);
//   Otto.moonwalker(3, 1000, 25,1); //LEFT
//   Otto.moonwalker(3, 1000, 25,-1); //RIGHT  
//   Otto.crusaito(2, 1000, 20,1);
//   Otto.crusaito(2, 1000, 20,-1);
//   Otto.flapping(2, 1000, 20,1);
//   Otto.flapping(2, 1000, 20,-1);
//   Otto.swing(2, 1000, 20);
//   Otto.tiptoeSwing(2, 1000, 20);
//   Otto.jitter(2, 1000, 20); //(small T)
//   Otto.updown(2, 1500, 20);  // 20 = H "HEIGHT of movement"T 
//   Otto.ascendingTurn(2, 1000, 50);
//   Otto.jump(1,500); // It doesn't really jumpl ;P

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <Otto.h> //-- Otto Library
Otto Otto;  //This is Otto!
//***OPEN SERIAL MONITOR FOR FINER CALIBRATION***

//Servos
//ensure you have wired the servos to these ports on the nano
#define LeftLeg 2 
#define RightLeg 3
#define LeftFoot 4 
#define RightFoot 5
#define Buzzer  13 // if there is a buzzer

// Ultrasonic Sensor Pins
//ensure you have wired the trig and echo pins to these digital ports on the nano
#define TRIG_PIN 8
#define ECHO_PIN 9

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
int YL;
int YR;
int RL;
int RR;
double charRead;
int detectDistance = 10; // the distance in cm that otto wil detect objects till
///////////////////////////////////////////////////////////////////
//-- SETUP-------------------------------------------------------//
//This code will run once every time the otto is connected-------//
///////////////////////////////////////////////////////////////////
void setup(){
    Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer);
    Serial.begin(9600);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT); 
    YL = EEPROM.read(0);
    if (YL > 128) YL -= 256;
    YR = EEPROM.read(1);
    if (YR > 128) YR -= 256;
    RL = EEPROM.read(2);
    if (RL > 128) RL -= 256;
    RR = EEPROM.read(3);
    if (RR > 128) RR -= 256;
    Otto.home(); //home the servos to the right positions
    Serial.println("OTTO CALIBRATION PROGRAM");
    Serial.println("PRESS a or z for adjusting Left Leg");
    Serial.println("PRESS s or x for adjusting Left Foot");
    Serial.println("PRESS k or m for adjusting Right Leg");
    Serial.println("PRESS j or n for adjusting Right Foot");
    Serial.println();
    Serial.println("PRESS f to test Otto walking");
    Serial.println("PRESS h to return servos to home position"); 
}

///////////////////////////////////////////////////////////////////
//-- Main Loop ---------------------------------------------//
//This loop will run indefinitely---------------------------//
///////////////////////////////////////////////////////////////////
void loop(){

  // check if there is an object within the detection distance
  // if there is, the otto will execute whatever function is in this loop
  if (checkForObjects(detectDistance)) {
    // Serial.println("see you");
    // copy a movement function from above here
    Otto.walk(1, 1000, -1);  
  }

    //read the input from the serial monitor
    if((Serial.available()) > (0)){
        charRead = Serial.read();
    }
    if((charRead)==('a' )){
        YL++;
        Otto.setTrims(YL,YR,RL,RR);
        calib_homePos();
        Otto.saveTrimsOnEEPROM();
    }else if((charRead)==( 'z' )){
        YL--;
        Otto.setTrims(YL,YR,RL,RR);
        calib_homePos();
        Otto.saveTrimsOnEEPROM();
    }else if((charRead)==( 's' )){
        RL++;
        Otto.setTrims(YL,YR,RL,RR);
        calib_homePos();
        Otto.saveTrimsOnEEPROM();
    }else if((charRead)==( 'x' )){
        RL--;
        Otto.setTrims(YL,YR,RL,RR);
        calib_homePos();
        Otto.saveTrimsOnEEPROM();
    }else if(((charRead)==( 'k' ))){
        YR++;
        Otto.setTrims(YL,YR,RL,RR);
        calib_homePos();
        Otto.saveTrimsOnEEPROM();
    }else if(((charRead)==( 'm' ))){
        YR--;
        Otto.setTrims(YL,YR,RL,RR);
        calib_homePos();
        Otto.saveTrimsOnEEPROM();
    }else if(((charRead)==( 'j' ))){
        RR++;
        Otto.setTrims(YL,YR,RL,RR);
        calib_homePos();
        Otto.saveTrimsOnEEPROM();
        RR--;
        Otto.setTrims(YL,YR,RL,RR);
        calib_homePos();
        Otto.saveTrimsOnEEPROM();
     }else if(((charRead)==( 'f' ))){
        Otto.walk(1,1000,1);
     }else if(((charRead)==( 'h' ))){
        Otto.home();
     }
  
}

void calib_homePos() {
  int servoPos[4];
  servoPos[0]=90; // Left Leg
  servoPos[1]=90; // Right Leg
  servoPos[2]=90; // Left Foot
  servoPos[3]=90; // Right Foot
  Otto._moveServos(500, servoPos);
  Otto.detachServos();
}

// Function to check for objects with the ultrasonic sensor within a certain range
// returns true if it has detected something, otherwise false
bool checkForObjects(int detectDistance) {
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.034) / 2; // Convert to distance
  // Serial.println(distance);
  if (distance < detectDistance && distance > 0) {
    return true;
  } else {
    return false;
  }
}


