#include <PrintEx.h>

StreamEx mySerial = Serial;

// Motor Pins // 

int motorEnablePin = 8;
int motorDirPin = 5; // X axis 
int motorStepPin = 2; // x axis
bool motorDir = false;
bool motorEnable = 0;


// motorMicroStepping
int ms1 = 3;
int ms2 = 4;
int ms3 = 6;

// Endstops ///

int endstopHomePin = 10;
int endstopEndPin = 9;
int homeReached = 0;
int endReached = 0;
int debounceSteps = 200*16;
int seekDone = 0;

int currentMillis = 0;
int lastMillis = 0;
int motorDelay = 100; // Delay between steps


int ms = 0;


/////////// FUNCTIONS ////////////////////////
//////////////////////////////////////////////

void endEndstopReached(){
  homeReached = digitalRead(endstopHomePin);
  if(!homeReached){
      mySerial.println("HomeReached");
      seekDone = 1;
    }
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

void homeEndstopReached(){
  endReached = digitalRead(endstopEndPin);
  if(!endReached){
      mySerial.println("EndReached");
      seekDone = 1;
    }
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

void reportEndstopState(){
  mySerial.printf("HomeEndstop state : %i",digitalRead(endstopHomePin)); 
  mySerial.printf("     LimitEndstop state : %i\n",digitalRead(endstopEndPin)); 
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

void seekHome(){
  digitalWrite(motorDirPin,LOW);
  while(seekDone == 0){
      motorStep();
      homeEndstopReached(); // check if we reached the endstop
   }
   debounceFromEndstop();
   seekDone = 0;
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

void seekEnd(){
  digitalWrite(motorDirPin,HIGH);
  while(seekDone == 0){
      motorStep();
      endEndstopReached(); // check if we reached the endstop
    }
    debounceFromEndstop();
    seekDone = 0;
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

void motorStep(){
  digitalWrite(motorStepPin,HIGH);
  delayMicroseconds(motorDelay);
  digitalWrite(motorStepPin,LOW); 
  delayMicroseconds(motorDelay);
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

void changeDir(){
  motorDir =! motorDir;
  digitalWrite(motorDirPin,motorDir);
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

void setDir(int dir){  // 1 forward, 0 backward;
  if(dir == 1){digitalWrite(motorDirPin,HIGH);}
  else{digitalWrite(motorDirPin,LOW);}
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

void debounceFromEndstop(){
  mySerial.println("Debouncing");
  changeDir();
  for(int i=0; i < debounceSteps; i++){
    motorStep();
    delayMicroseconds(10);
    
//    Serial.println("Debouncing");
  }
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

void setMotSpeed(float delaym){
  motorDelay = delaym;
  mySerial.printf("Setting Delay = %i \n",motorDelay);
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////


void motorMicroStepping(int ms){
  mySerial.println("Setting Microstepping");
  if(ms == 0){ // no micromotorStepPing
    digitalWrite(ms1,LOW);
    digitalWrite(ms2,LOW);
    digitalWrite(ms3,LOW);
    mySerial.println("Microstepping set to 0");
    }

   else if(ms == 4){ // 4x micromotorStepPing
    digitalWrite(ms1,HIGH);
    digitalWrite(ms2,LOW);
    digitalWrite(ms3,LOW);
    mySerial.println("Microstepping set to 4");
    }

    else if(ms == 8){ // 8x micromotorStepPing
    digitalWrite(ms1,HIGH);
    digitalWrite(ms2,HIGH);
    digitalWrite(ms3,LOW);
    mySerial.println("Microstepping set to 8");
    }

    else if(ms == 16){ // 16x micromotorStepPing
    digitalWrite(ms1,HIGH);
    digitalWrite(ms2,HIGH);
    digitalWrite(ms3,HIGH);
    mySerial.println("Microstepping set to 16");
    }
  
}

//////////////////////////////////////////////
//////////////////////////////////////////////
//////////////////////////////////////////////

// Supported commands 
// b = goHome
// e = enable motors / disable motors
// f = run to end of rope
// d = delay motor between steps
// m = microstepping
// h = help menu

void runBuffCommand(char c){
  
if(c == 'e'){
 motorEnable =! motorEnable;
 digitalWrite(motorEnablePin, motorEnable);
 if(motorEnable == 1){mySerial.println("Motor enabled.");}
 else{mySerial.println("Motor disabled.");}
}

if(c == 'b'){
  setDir(0);
  mySerial.println("Homing....");
  seekHome();
}

if(c == 'f'){
  setDir(0);
  mySerial.println("Scanning....");
  seekEnd();
}

if(c == 'd'){
int gotmotorDelay = 0;
motorDelay = 0;
mySerial.println("Set motor speed: 10-100ms");
  while(gotmotorDelay == 0){
    if(mySerial.available()>0){
      motorDelay = mySerial.parseInt(); 
      if(motorDelay < 10){motorDelay = 10;}
      if(motorDelay > 100){motorDelay = 100;}
      gotmotorDelay = 1;
      c = ' ';
    }
  }
  mySerial.print("Setting delay for motor: ");mySerial.println(motorDelay); 
}


if(c == 'r'){
  reportEndstopState();
}

if(c == 'm'){
  mySerial.println("Give a value for micromotorStepPing. Expecting values 0,4,8,16");
  int gotMicrostepValue = 0;
  while(gotMicrostepValue == 0){
    if(mySerial.available()>0){
      ms = mySerial.parseInt(); 
      if(ms == 0 || ms == 4 || ms == 8 || ms == 16){
        gotMicrostepValue = 1;
        c = ' ';
      }
      else{
        Serial.println("Invalid number, accepted values = 0, 4, 8, 16");
      }
    }
  }
  motorMicroStepping(ms);
}


if(c == 'h'){
  mySerial.println("");
  mySerial.println("Help menu");
  mySerial.println("Following commands are supported.\n b = Go home. \n f = Start scanning. \n e = Enable/disable motors \n d = Delay between steps");
  mySerial.println(" m = Set microstepping \n r = Report endstop state \n h = This help menu \n");
  mySerial.println();
}

// b = goHome
// e = enable motors / disable motors
// f = run to end of rope
// d = delay motor between steps
// m = microstepping
// h = help menu

 
}


//////////////////////////////////////////////
/////////// FUNCTIONS END ////////////////////
//////////////////////////////////////////////

void setup() {
  Serial.begin(115200);
  pinMode(motorEnablePin,OUTPUT);
  pinMode(motorDirPin,OUTPUT);
  pinMode(motorStepPin,OUTPUT);
//  pinMode(ms1,OUTPUT);
//  pinMode(ms2,OUTPUT);
//  pinMode(ms3,OUTPUT);
  pinMode(endstopHomePin,INPUT);
  pinMode(endstopEndPin,INPUT);

  
  int firstMillis = micros();
    
  mySerial.println("CableBot Controller v0.1");
  mySerial.println("Type h for help. Set Serial monitor to \"no line ending\"");
  motorMicroStepping(0);
}


int index = 0;
char c;



void loop() {
 
 currentMillis = micros();
 if(mySerial.available() > 0){
    c = mySerial.read();
    runBuffCommand(c); 
    if(c == '\n'){
      c = '0';
     }
  }

  


//
//  motorConfigue();
//  motorStep();
//  digitalWrite(13,!start);


}



