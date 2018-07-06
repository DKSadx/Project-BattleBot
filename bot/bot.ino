#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#include <Servo.h>
RF24 radio(9, 10); // CE, CSN
const byte addresses[6] = {"00001"};
//Servo myServo;
const int dirAPin = 7;  //     LIJEVI MOTOR     // define pin used to control rotational direction of motor A
const int pwmAPin = 6;                          // define pin for PWM used to control rotational speed of motor A
const int dirBPin = 4;  //     DESNI MOTOR      // define pin used to control rotational direction of motor B
const int pwmBPin = 5;                          // define pin for PWM used to control rotational speed of motor B
const int snsAPin = 0;                          // define pin for detecting current of motor A
const int snsBPin = 1;                         // define pin for detecting current of motor B
int brzinaA;
int brzinaB;
int motorSpeedA = 0;
int motorSpeedB = 0;
int ose[10];
                                                                   /*         ose[4]= L1 = 2;
                                                                              ose[5]= R1 = 3;
                                                                              ose[6]= btn1 = 4;
                                                                              ose[7]= btn2 = 5;
                                                                              ose[8]= btn3 = 6;
                                                                              ose[9]= btn4 = 9;          */
void setup() {
//  Serial.begin(9600);
  pinMode(dirAPin, OUTPUT);   // set dirAPin to output mode
  pinMode(pwmAPin, OUTPUT);   // set pwmAPin to output mode
  pinMode(dirBPin, OUTPUT);   // set dirBPin to output mode
  pinMode(pwmBPin, OUTPUT);   // set pwmBPin to output mode
//  myServo.attach(2);
  radio.begin();
  radio.openReadingPipe(0, addresses); // 00001
  radio.setPALevel(RF24_PA_MIN);
}
int X_osa;
int Y_osa;
void loop() {
  radio.startListening();
  if ( radio.available()) {
    radio.read(&ose,sizeof(ose));
    X_osa = ose [1];
    Y_osa = ose [0];  
int Xservo = ose [2]; 
int L1 = ose[4];
int R1 = ose[5];
int btn1 = ose[5];
int btn2 = ose[7];
int btn3 = ose[8];
int btn4 = ose[9];      
          //                                            
          // ose[3] is not being used
          //
//     Serial.print("POLOZAJ JOYSTICKA  : ");
//     Serial.print(X_osa);
//     Serial.print("    ");
//     Serial.println(Y_osa);
//     Serial.print("POLOZAJ SERVA  : ");
//     Serial.print(Xservo);
//     Serial.print("Button L1 : "); Serial.print(L1);
//     Serial.print("Button R1 : "); Serial.print(R1);
//     Serial.print("Button 1 : "); Serial.print(btn1);
//     Serial.print("Button 2 : "); Serial.print(btn2);
//     Serial.print("Button 3 : "); Serial.print(btn3);
//     Serial.print("Button 4 : "); Serial.print(btn4);

//        MAX SPEED L1 R1
  if( L1 == 0 )
 Y_osa = 1023;      
  if( R1 == 0 )  
 Y_osa = 0;   
                                                              // MOTOR
                                                              
  if (Y_osa < 470) {
    digitalWrite(dirAPin,HIGH);
      digitalWrite(dirBPin,LOW);
    // Convert the declining Y-axis readings for going backward from 470 to 0 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(Y_osa, 470, 0, 0, 255);
    motorSpeedB = map(Y_osa, 470, 0, 0, 255);
  }
  else if (Y_osa > 550) {
    digitalWrite(dirAPin,LOW);
      digitalWrite(dirBPin,HIGH);
    // Convert the increasing Y-axis readings for going forward from 550 to 1023 into 0 to 255 value for the PWM signal for increasing the motor speed
    motorSpeedA = map(Y_osa, 550, 1023, 0, 255);
    motorSpeedB = map(Y_osa, 550, 1023, 0, 255);
  }
  // If joystick stays in middle the motors are not moving
  else {
    motorSpeedA = 0;
    motorSpeedB = 0;
  }
  // X-axis used for left and right control
  if (X_osa < 470) {
    // Convert the declining X-axis readings from 470 to 0 into increasing 0 to 255 value
    int xMapped = map(X_osa, 470, 0, 0, 255);
    // Move to left - decrease left motor speed, increase right motor speed
    motorSpeedA = motorSpeedA - xMapped;
    motorSpeedB = motorSpeedB + xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA < 0) {
      motorSpeedA = 0;
    }
    if (motorSpeedB > 255) {
      motorSpeedB = 255;
    }
  }
  if (X_osa > 550) {
    // Convert the increasing X-axis readings from 550 to 1023 into 0 to 255 value
    int xMapped = map(X_osa, 550, 1023, 0, 255);
    // Move right - decrease right motor speed, increase left motor speed
    motorSpeedA = motorSpeedA + xMapped;
    motorSpeedB = motorSpeedB - xMapped;
    // Confine the range from 0 to 255
    if (motorSpeedA > 255) {
      motorSpeedA = 255;
    }
    if (motorSpeedB < 0) {
      motorSpeedB = 0;
    }
  }
  // Prevent buzzing at low speeds (Adjust according to your motors. My motors couldn't start moving if PWM value was below value of 70)
  if (motorSpeedA < 70) {
    motorSpeedA = 0;
  }
  if (motorSpeedB < 70) {
    motorSpeedB = 0;
  }
  analogWrite(pwmAPin, motorSpeedA); // Send PWM signal to motor A
  analogWrite(pwmBPin, motorSpeedB); // Send PWM signal to motor B   

  
  delay(10);
}
else {
  analogWrite(pwmAPin, 0); // Send PWM signal to motor A
  analogWrite(pwmBPin, 0); // Send PWM signal to motor B   
  }
}

