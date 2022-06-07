/**
 * Author:  RAHUL
 * Access:  RAHUL and team
 */

/**COMMENTS ONLY
 * readSensors(); before every condition check
 * straight done
 * stop 
 * u-turn 
 * cross left 
 * -| left
 * T-left
 * |- right 
 * 
 * 
 */
int leapTime = 120;
//IR pins
int s1=3;     //Left far
int s2=2;     // left near
int s3=4;     // left align
int s4=5;     // left center
int s5=7;     //right center
int s6=8;     //right align
int s7=13;    //right near
int s8=12;      //right far

//motor pins
#define left_motorH  10       //left motor a+...H= +ve pin
#define left_motorL  11       //left motor a-.....L= -ve pin

#define right_motorH 6      //right motor b+....H= +ve pin
#define right_motorL 9      // right motor b-....L= -ve pin

//  SPEED CONTROL
#define fwd_spdL 60           //forward speed defination left
#define fwd_spdR fwd_spdL-6   //fwd speed defination right
#define turn_spd 60           //turn speed defination
#define gnd 0                 // Ground
#define step_ahead 70         //step ahead motor

//line code
#define w 1   //white=1
#define b 0   //black=0
#define d 300   //delay
#define ta 200  //turn around delay

//sensor value storage variable..
int ir1;
int ir2;
int ir3;
int ir4;
int ir5;
int ir6;
int ir7;
int ir8;
void readSensors();
void oneInchLoop();
void stopBot();
void turnBack();
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
  pinMode(13,OUTPUT);
  // MOTOR output setup
  pinMode(left_motorH,OUTPUT);
  pinMode(left_motorL,OUTPUT);
  pinMode(right_motorH,OUTPUT);
  pinMode(right_motorL,OUTPUT);
Serial.begin(9600);
}

void loop() {

  readSensors();
straight();

 if ((ir4==w || ir5==w) && ir1==b && ir8==b){
    straight();
    Serial.print("LOOP_STRAIGHT");
  }
  else {
    leftHandRule();
  }
  

}

void straight(){
if(digitalRead(s3)==b && digitalRead(s4)==w && digitalRead(s5)==w && digitalRead(s6)==b ){
   // Serial.print("STRAIGHT-------222222222");
    analogWrite(left_motorH,70);
    analogWrite(left_motorL,0);
    analogWrite(right_motorH,70);
    analogWrite(right_motorL,0);
  //delay(2);
  }
else if(digitalRead(s3)==b && digitalRead(s4)==b && digitalRead(s5)==w && digitalRead(s6)==b ){
   // Serial.print("STRAIGHT-------222222222");
    analogWrite(left_motorH,70);
    analogWrite(left_motorL,0);
    analogWrite(right_motorH,50);
    analogWrite(right_motorL,0);
  //delay(1);
  }

else if(digitalRead(s3)==b && digitalRead(s4)==b || digitalRead(s5)==w && digitalRead(s6)==w ){
   // Serial.print("STRAIGHT-------222222222");
    analogWrite(left_motorH,70);
    analogWrite(left_motorL,0);
    analogWrite(right_motorH,50);
    analogWrite(right_motorL,0);
  //delay(1);
  }
else if(digitalRead(s3)==b && digitalRead(s4)==w && digitalRead(s5)==b && digitalRead(s6)==b ){
   // Serial.print("STRAIGHT-------222222222");
    analogWrite(left_motorH,50);
    analogWrite(left_motorL,0);
    analogWrite(right_motorH,70);
    analogWrite(right_motorL,0);
 // delay(1);
  }
else if(digitalRead(s3)==w && digitalRead(s4)==w || digitalRead(s5)==b && digitalRead(s6)==b ){
   // Serial.print("STRAIGHT-------222222222");
    analogWrite(left_motorH,50);
    analogWrite(left_motorL,0);
    analogWrite(right_motorH,70);
    analogWrite(right_motorL,0);
  //delay(1);
  }


}



void leftHandRule(){
if((ir1==w ) && (ir8==w )){
       oneInchLoop();
       delay(200);
       readSensors();
       if(ir1==w || ir8==w)
          stopBot();
       else
       if(digitalRead(s1)==b && digitalRead(s4)==w || digitalRead(s5)==w && digitalRead(s8)==b){
          turnLeft();}
   }
    
  if((ir1==w )){
       oneInchLoop();
       delay(200);
       readSensors();
       if(ir1==w && ir8==w)
          stopBot();
       else
          turnLeft();
   }
  if((ir8==w )){
       oneInchLoop();
       delay(50);
       readSensors();
       
       if(ir1==w){
          delay(leapTime-30);
          readSensors();
          if((ir1==w ) && (ir8==w ))
          stopBot();
          else
          turnLeft();
        return;
       }
   
   delay(leapTime+30);
  readSensors();
    if((ir1==b && ir8==b))
      {
      turnRight();
      return;
    } 

    straight();
    }
    readSensors();
    if((ir1==b  && ir3==b && ir4==b && ir5== b && ir6==b && ir8==b)){
       turnBack();
    }
    /*readSensors();
    if(ir1==w && ir3==w && ir4==w && ir5==w && ir6==w && ir8==w){
        oneInchLoop();
        delay(100);
        readSensors();
        if(ir1==w && ir3==w && ir4==w && ir5==w && ir6==w && ir8==w){
          stopBot();
        }
      }*/
  }
  
   
  
void turnLeft(){
 //digitalWrite(13,HIGH);
  analogWrite(left_motorH,0);
  analogWrite(left_motorL,60);
  analogWrite(right_motorH,60);
  analogWrite(right_motorL,0);
  delay(150);
  while( digitalRead(s4) == b || digitalRead(s5) == b ){
     analogWrite(left_motorH,gnd);
  analogWrite(left_motorL,50);
  analogWrite(right_motorH,50);
  analogWrite(right_motorL,gnd);

  }
     analogWrite(left_motorH,60);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,0);
  analogWrite(right_motorL,60);
 delay(30);
     analogWrite(left_motorH,0);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,0);
  analogWrite(right_motorL,0);
 delay(10);
 
// digitalWrite(13,LOW); 
 return;
}

void turnRight(){
 digitalWrite(13,HIGH);
  analogWrite(left_motorH,60);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,0);
  analogWrite(right_motorL,60);
  delay(150);
  while( digitalRead(s4) == b || digitalRead(s5) == b ){
     analogWrite(left_motorH,60);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,0);
  analogWrite(right_motorL,60);

  }
    analogWrite(left_motorH,60);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,0);
  analogWrite(right_motorL,60);
 delay(50);
     analogWrite(left_motorH,0);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,0);
  analogWrite(right_motorL,0);
 delay(10);
 

 
 digitalWrite(13,LOW); 
 
  }
  
 


/*void turnBack(){
 digitalWrite(13,HIGH);
  analogWrite(left_motorH,60);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,0);
  analogWrite(right_motorL,60);
  delay(150);
  while( digitalRead(s4) == b || digitalRead(s5) == b ){
     analogWrite(left_motorH,60);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,0);
  analogWrite(right_motorL,60);

  }*/


void turnBack(){
 //digitalWrite(13,HIGH);
  analogWrite(left_motorH,0);
  analogWrite(left_motorL,60);
  analogWrite(right_motorH,60);
  analogWrite(right_motorL,0);
  delay(150);
  while( digitalRead(s4) == b || digitalRead(s5) == b ){
     analogWrite(left_motorH,gnd);
  analogWrite(left_motorL,50);
  analogWrite(right_motorH,50);
  analogWrite(right_motorL,gnd);

  }
     analogWrite(left_motorH,60);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,0);
  analogWrite(right_motorL,60);
 delay(30);
     analogWrite(left_motorH,0);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,0);
  analogWrite(right_motorL,0);
 delay(10);
 
 //digitalWrite(13,LOW); 
 return;
  }
void stopBot(){
  delay(400);
  while(digitalRead(s1)==w && digitalRead(s3)==w && digitalRead(s4)==w && digitalRead(s5)==w && digitalRead(s6)==w && digitalRead(s8)==w){
  analogWrite(left_motorH,gnd);
  analogWrite(left_motorL,gnd);
  analogWrite(right_motorH,gnd);
  analogWrite(right_motorL,gnd);
  analogWrite(A0,153);
  analogWrite(A5,0);
  }
  analogWrite(A0,0);
}

void stopPulse(){
  analogWrite(left_motorH,gnd);
  analogWrite(left_motorL,gnd);
  analogWrite(right_motorH,gnd);
  analogWrite(right_motorL,gnd);
  delay(800);
}

void oneInchLoop(){
  analogWrite(left_motorH,60);
  analogWrite(left_motorL,0);
  analogWrite(right_motorH,60);
  analogWrite(right_motorL,0);
  
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
  Serial.print(ir1); 
  Serial.print("           ");
  Serial.print(ir2); 
  Serial.print("           ");
  Serial.print(ir3); 
  Serial.print("           ");
  Serial.print(ir4); 
  Serial.print("           ");
  Serial.print(ir5); 
  Serial.print("           ");
  Serial.print(ir6); 
  Serial.print("           ");
  Serial.print(ir7); 
  Serial.print("           ");
  Serial.print(ir8); 
  Serial.println("           ");
  
}
