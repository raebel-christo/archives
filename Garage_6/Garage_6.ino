#include<Servo.h>

int degrees = ;//rate of rotation of servo
int GreenLed =  ; //Use PWM
int RedLed = ;//Use PWM
int Light = ;//Lights
int SerPin = ;//Servo input pin
int DoorClosed = ;
int DoorOpened = ;
int GndPin1 = ;
int GndPin2 = ;
int speed = ;
String BytesRecieved;
Servo servo;
boolean GotBytes = false;
const long intervals = ;//Delay
int a = DoorClosed;
unsigned long PreviousMillis = 0;

void setup(){
    Serial.begin(9600);
    servo.attach(SerPin);
    pinMode(GreenLed, OUTPUT);
    pinMode(RedLed, OUTPUT);
    pinMode(GndPin1, OUTPUT);
    pinMode(GndPin2, OUTPUT);
    servo.write(DoorClosed);
    digitalWrite(GreenLed,1);
    digitalWrite(GndPin1, LOW);
    digitalWrite(GndPin2, LOW);
}

void loop(){
    ManualSequence();
}

void ManualSequence(){
    while(GotBytes == false){
        if(Serial.available()>0){
            char c = Serial.read();
            BytesRecieved += c;
            GotBytes = true;
        }
    }
    if(BytesRecieved == "1"){
        while(servo.read() != DoorOpened){
            unsigned long CurrentMillis = millis();
            if(CurrentMillis-PreviousMillis >= intervals){
                PreviousMillis = CurrentMillis;
                a+=degrees;
                servo.write(a);
                digitalWrite(RedLed, 1);
                digitalWrite(GreenLed,1);
                digitalWrite(Lights, 1);
            }
        }
        digitalWrite(GreenLed,0);
    }
    else if(BytesRecieved == "0"){
        while(servo.read() != DoorClosed){
            unsigned long CurrentMillis = millis();
            if(CurrentMillis-PreviousMillis >= intervals){
                PreviousMillis = CurrentMillis;
                a-=degrees;
                servo.write(a);
                digitalWrite(RedLed, 1);
                digitalWrite(GreenLed,1);
                digitalWrite(Lights, 1);
            }
        }
        digitalWrite(RedLed,0);
        digitalWrite(Lights, 0);
    }
    BytesRecieved = "";
    GotBytes = false;
}