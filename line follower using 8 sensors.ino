
 
//IR pins
int s1=2;     //Left far
int s2=3;     // left near
int s3=4;     // left align
int s4=5;     // left center
int s5=7;     //right center
int s6=8;     //right align
int s7=12;    //right near
int s8=13;      //right far

//motor pins
#define left_motorH  10       //left motor a+...H= +ve pin
#define left_motorL  11       //left motor a-.....L= -ve pin

#define right_motorH 6      //right motor b+....H= +ve pin
#define right_motorL 9      // right motor b-....L= -ve pin

//  SPEED CONTROL
#define fwd_spdL 82           //forward speed defination left
#define fwd_spdR fwd_spdL-6   //fwd speed defination right
#define turn_spd 80           //turn speed defination
#define stop_spd 0            //stop speed
#define gnd 0                 // Ground
#define step_ahead 70         //step ahead motor
//line code
#define w 1   //white=1
#define b 0   //black=0
#define d 400   //delay
#define ta 600  //turn around delay

//sensor value storage variable..
int ir1;
int ir2;
int ir3;
int ir4;
int ir5;
int ir6;
int ir7;
int ir8;

void setup() {
  //IR sensor pin mode
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  pinMode(s3,INPUT);
  pinMode(s4,INPUT);
  pinMode(s5,INPUT);
  pinMode(s6,INPUT);
  pinMode(s7,INPUT);
  pinMode(s8,INPUT);

  // MOTOR output setup
  pinMode(left_motorH,OUTPUT);
  pinMode(left_motorL,OUTPUT);
  pinMode(right_motorH,OUTPUT);
  pinMode(right_motorL,OUTPUT);
Serial.begin(9600);
}

void loop() {
  readSensors();
  if((ir4==w || ir5==w) && (ir1==b && ir2==b && ir7==b && ir8==b)){
    straight();
    Serial.print("LOOP_STRAIGHT");
  }
  readSensors();
  if(ir1==w || ir2==w || ir7==w || ir8==w){
    leftHandRule();
  }

}

void straight(){
  if(ir4==1 && ir5==1){
    Serial.print("STRAIGHT-----111111111");
    analogWrite(left_motorH,fwd_spdL);
    analogWrite(left_motorL,gnd);
    analogWrite(right_motorH,fwd_spdR);
    analogWrite(right_motorL,gnd);
  }
  readSensors();
  if(ir3==w && ir4==w && ir5==b ){
    Serial.print("STRAIGHT-------222222222");
    analogWrite(left_motorH,fwd_spdL);
    analogWrite(left_motorL,gnd);
    analogWrite(right_motorH,fwd_spdR+15);
    analogWrite(right_motorL,gnd);
  }
  readSensors();
  if(ir4==b && ir5==w && ir6==w){
    Serial.print("STRAIGHT--------33333333");
    analogWrite(left_motorH,fwd_spdL+15);
    analogWrite(left_motorL,gnd);
    analogWrite(right_motorH,fwd_spdR);
    analogWrite(right_motorL,gnd);
  }
}



void leftHandRule(){
  Serial.print("LHR-----ENTERED---------------------------------------------------------------");

  //crossing
  readSensors();
  if((ir1==w || ir2==w) && (ir8==w || ir7==w)){//junction.
   oneInchLoop();
   readSensors();
   if(ir1==b && ir2==b && ir8==b && ir7==b){
    Serial.print("LHR----CROSS------LEFT");
    turnLeft();
    delay(d);
    Serial.print("LHR----CROSS------STRAIGHT AFTER LEFT");
    straight();
   }
   else{
    oneInchLoop();
      readSensors();
      if(ir1==w && ir2==w && ir3==w && ir4==w && ir5==w && ir6==w && ir7==w && ir8==w){
        oneInchLoop();
        readSensors();
        if(ir1==w && ir2==w && ir3==w && ir4==w && ir5==w && ir6==w && ir7==w && ir8==w){
          Serial.print("LHR----CROSS-----STOP");
          stopBot();
        }
      }
    } 
  }
  //t-point(-|)
  readSensors();
  if((ir1==w || ir2==w) && (ir8==b && ir7==b)){
   oneInchLoop();
    turnLeft();
    Serial.print("LHR----T-POINT------LEFT(--||)");
    delay(d);
    straight();
  }
  //T-point(|-)
  readSensors();
  if((ir1==b && ir2==b) && (ir8==w || ir7==w)){
    oneInchLoop();
    readSensors();
    if(ir4==w || ir5==w){
      straight();
      Serial.print("LHR--------T-POINT(|-)-------STRAIGHT");
      return;
    }
    else{
      turnRight();
      Serial.print("LHR--------T-POINT(|-)-------RIGHT");
      return;
    }
  }

  //Turn back
 /* readSensors();
  if( ir3==w || ir4==w || ir5==w || ir6==w ){
    oneInchLoop();*/
    readSensors();
    if(ir1==b && ir2==b && ir3==b && ir4==b && ir5==b && ir6==b && ir7==b && ir8==b){
      oneInchLoop();
      turnBack();
      //Serial.print("LHR------OUT OF LINE-------U-TURN");
      delay(ta);
      straight();
      return;
    }
    
  }
  Serial.print("LHR----EXIT-------------------------------------------");
}
  
void turnLeft(){
  analogWrite(left_motorH,gnd);
  analogWrite(left_motorL,fwd_spdL);
  analogWrite(right_motorH,fwd_spdR);
  analogWrite(right_motorL,gnd);
}

void turnRight(){
  analogWrite(left_motorH,fwd_spdL);
  analogWrite(left_motorL,gnd);
  analogWrite(right_motorH,gnd);
  analogWrite(right_motorL,fwd_spdR);
   
   
}

void turnBack(){
  analogWrite(left_motorH,gnd);
  analogWrite(left_motorL,fwd_spdL);
  analogWrite(right_motorH,fwd_spdR);
  analogWrite(right_motorL,gnd);
  
}
void stopBot(){
  analogWrite(left_motorH,gnd);
  analogWrite(left_motorL,gnd);
  analogWrite(right_motorH,gnd);
  analogWrite(right_motorL,gnd);
}

void oneInchLoop(){
  analogWrite(left_motorH,60);
  analogWrite(left_motorL,gnd);
  analogWrite(right_motorH,60);
  analogWrite(right_motorL,gnd);
  delay(70);
  stopBot();

}
void readSensors(){

  ir1 = digitalRead(s1);
  ir2 = digitalRead(s2);
  ir3 = digitalRead(s3);
  ir4 = digitalRead(s4);
  ir5 = digitalRead(s5);
  ir6 = digitalRead(s6);
  ir7 = digitalRead(s7);
  ir8 = digitalRead(s8);
  
}
