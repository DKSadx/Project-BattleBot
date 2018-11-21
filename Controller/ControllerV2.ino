#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(8, 9); // CE, CSN
const byte addresses[6] = {"00001"};
int L1 = 2;
int R1 = 3;
int btn1 = 4;
int btn2 = 5;
int btn3 = 6;
int btn4 = 7;
int led = 10;
void setup() {
// Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses); // 00001
  radio.setPALevel(RF24_PA_MIN);
  pinMode(L1,INPUT_PULLUP);
  pinMode(R1,INPUT_PULLUP);
  pinMode(btn1,INPUT_PULLUP);
  pinMode(btn2,INPUT_PULLUP);
  pinMode(btn3,INPUT_PULLUP);
  pinMode(btn4,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
}

void loop() {
   delay(5);
  int ose[10];
  ose[0]= analogRead(3);
  ose[1]= analogRead(4);
  ose[2]= analogRead(1);
  ose[3]= analogRead(2);
  
 /* Serial.print("Analog 1:   ");
  Serial.print(ose[0]);
  Serial.print("   ");
  Serial.println(ose[1]);
  Serial.print("Analog 2:   ");
  Serial.print(ose[2]);
  Serial.print("   ");
  Serial.println(ose[3]);*/
  ose[4]= digitalRead(2);
  ose[5]= digitalRead(3);
  ose[6]= digitalRead(4);
  ose[7]= digitalRead(5);
  ose[8]= digitalRead(6);
  ose[9]= digitalRead(9);
/*  for(int i=4;i<=9;i++){
   Serial.print("Button "); Serial.print(i-3);Serial.print("  :     "); Serial.println(ose[i]);
  }*/
  radio.write(ose, sizeof(ose));

  
}
