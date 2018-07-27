#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const byte addresses[6] = {"00001"};
void setup() {
  radio.begin();
  radio.openWritingPipe(addresses); // 00001
  radio.setPALevel(RF24_PA_MIN);
}
void loop() {
  delay(5);
  int X_osa = analogRead(A0);
  int Y_osa = analogRead(A2);
 //  X_osa= map(X_osa, 0, 1023, 0, 255);
 //  Y_osa= map(Y_osa,0,1023,0,255);
  radio.write(&X_osa, sizeof(X_osa));
  radio.write(&Y_osa, sizeof(Y_osa));
  
    
  
}
