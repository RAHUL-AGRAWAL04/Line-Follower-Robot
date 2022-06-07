
int s1=2;
int s2=3;
int s3=4;
int s4=5;
int s5=7;
int s6=8;
int s7=12;
int s8=13;

void setup() {
  // put your setup code here, to run once:
  pinMode(12,INPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(13,INPUT);
  pinMode(7,INPUT);
  pinMode(8,INPUT);
Serial.begin(9600);
}

void loop() {
 // delay(10000);
  Serial.print("s1=");Serial.print(digitalRead(s1));
  Serial.print("s2=");Serial.print(digitalRead(s2));
  Serial.print("s3=");Serial.print(digitalRead(s3));
  Serial.print("s4=");Serial.print(digitalRead(s4));
  Serial.print("s5=");Serial.print(digitalRead(s5));
  Serial.print("s6=");Serial.print(digitalRead(s6));
  Serial.print("s7=");Serial.print(digitalRead(s7));
  Serial.print("s8=");Serial.print(digitalRead(s8));
  Serial.print("\n\n");
  
  // put your main code here, to run repeatedly:

}
