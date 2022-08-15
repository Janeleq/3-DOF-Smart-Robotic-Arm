//Libraries Used
#include <TLE9879_Group.h> //BLDC Driver Shield
#include <SoftwareSerial.h> //Bluetooth Connection
#include <Servo.h> //Servo Library

//Intialisation of Objects
Servo servoBase; //Base
Servo servoGripper; //Gripper
TLE9879_Group *shields; //Shoulder and elbow (run joints 1 and 2)

//Bluetooth Intialisation
SoftwareSerial Bluetooth(2,3); //Arduino(RX,TX) - HC-05 Bluetooth (TX,RX)


//Intialisation of Variables
int servoBasePos, servoGripperPos, brushlessElbowPos, brushlessShoulderPos; //Store current position
int servoBasePPos, servoGripperPPos, brushlessElbowPPos, brushlessShoulderPPos; //Store previous position
int speedDelayBase = 20;
int speedDelayGripper = 50;
int dataIn;
int m = 0; //Identify different data received from phone interface

void setup() 
{
  servoBase.attach(9);
  servoGripper.attach(10);
  shields = new TLE9879_Group(2);
  shields->setParameter(FOC_MAX_SPEED,100,BOARD1);
  shields->setParameter(FOC_MAX_SPEED,100,BOARD2);
  shields->setMode(FOC,BOARD1);
  shields->setMode(FOC,BOARD2);
    delay(100);
  
  Bluetooth.begin(9600); // Default baud rate of the Bluetooth module
  Bluetooth.setTimeout(5);
    delay(20);
  
  Serial.begin(9600); //For Serial Monitoring
  
  // Move robot arm to initial position
  servoBasePPos = 90;
  servoBase.write(servoBasePPos);
  
  brushlessShoulderPPos = 0;
  shields->setMotorSpeed(brushlessShoulderPPos,BOARD2);
  shields->setMotorMode(STOP_MOTOR,BOARD2);

  brushlessElbowPPos = 0;
  shields->setMotorSpeed(brushlessElbowPPos, BOARD1);
  shields->setMotorMode(STOP_MOTOR,BOARD1);
  
  servoGripperPPos = 90;
  servoGripper.write(servoGripperPPos);
}

void loop() 
{
  // Check for incoming data
  if (Bluetooth.available() > 0)
  {
    dataIn = Bluetooth.read();  // Read the data (One byte number specified on app inventor)  

    //m: 0-6 (Base positioning control)
    if (dataIn == 0) {
      m = 0;}
    
    if (dataIn == 1) {
      m = 1;}

    if (dataIn == 2) {
      m = 2;}

    if (dataIn == 3) {
      m = 3;}

    if (dataIn == 4) {
      m = 4;}

    if(dataIn == 5) {
      m = 5;}

    if(dataIn == 6) {
      m = 6;}
      
    //m: 7-14 (Control of different parts of robot arm)
    if (dataIn == 7) {
      m = 7;}
    
    if (dataIn == 8) {
      m = 8;}
    
    if (dataIn == 9) {
      m = 9;}
    
    if (dataIn == 10) {
      m = 10;}
    
    if (dataIn == 11) {
      m = 11;}
    
    if (dataIn == 12) {
      m = 12;}
    
    if (dataIn == 13) {
      m = 13;}
    
    if (dataIn == 14) {
      m = 14;}
   
    
    //Control parts of robot arm
    
    //Move Base with servo in positive direction
    while (m == 8) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();}
      
      servoBase.write(servoBasePPos);
      servoBasePPos++;
      delay(speedDelayBase);
      
      Serial.print("+");
    }
    // Move Base with servo in negative direction
    while (m == 7) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();}
      
      servoBase.write(servoBasePPos);
      servoBasePPos--;
      delay(speedDelayBase);

      Serial.print("-");
    }
    
    // Move Shoulder with brushless in clockwise direction
    while (m == 10) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();}
      
      shields->setMotorSpeed(80);
      shields->setMotorMode(START_MOTOR,BOARD2);
    }
    //Move Shoulder with brushless in anti-clockwise direction
    while (m == 9) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();}
      
      shields->setMotorSpeed(-80);
      shields->setMotorMode(START_MOTOR,BOARD2);
    }
    
    // Move Elbow with brushless in clockwise direction
    while (m == 12) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();}
   
      shields->setMotorSpeed(80);
      shields->setMotorMode(START_MOTOR,BOARD1);
    }
    //Move Elbow with brushless in anti-clockwise direction
    while (m == 11) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();}
   
      shields->setMotorSpeed(-80);
      shields->setMotorMode(START_MOTOR,BOARD1);
    }
   
    // Move Gripper with servo in positive direction
    while (m == 14) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();}
      
      servoGripper.write(servoGripperPPos);
      servoGripperPPos++;
      delay(speedDelayGripper);
      
      Serial.print("+");
    }
    // Move Gripper with servo in negative direction
    while (m == 13) {
      if (Bluetooth.available() > 0) {
        m = Bluetooth.read();}
      
      servoGripper.write(servoGripperPPos);
      servoGripperPPos--;
      delay(speedDelayGripper);

      Serial.print("-");
    }

    servoGripperPPos = 90;
    servoGripper.write(servoGripperPPos);
    shields->setMotorMode(STOP_MOTOR,BOARD1);
    shields->setMotorMode(STOP_MOTOR,BOARD2);


    //Base positioning 

    //If (45deg cw clicked)
    if(m == 1 ){
      servoBase.write(45);
      delay(250);

      Serial.print("45deg Clockwise");
    }

    //If 90deg cw clicked
    if(m == 2){
      servoBase.write(45);
      delay(450);

      Serial.print("90deg Clockwise");
    }

    //If 180deg cw clicked
    if(m == 3){
      servoBase.write(45);
      delay(800);

      Serial.print("180deg Clockwise");
    }

    //If 45deg acw clicked
    if(m == 4){
      servoBase.write(135);
      delay(250);

      Serial.print("45deg Anti-Clockwise");
    }
    //If 90deg acw clicked
    if(m == 5){
      servoBase.write(135);
      delay(450);

      Serial.print("90deg Anti-Clockwise");
    }
    //If 180deg acw clicked
    if(m == 6){
      servoBase.write(135);
      delay(800);

      Serial.print("180deg Anti-Clockwise");
    }
    servoBasePPos = 90;
    servoBase.write(servoBasePPos);
    
  } 
}
 
