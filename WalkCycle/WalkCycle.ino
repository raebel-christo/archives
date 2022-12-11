#include<Wire.h>
#include<Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 145
#define SERVOMAX 465
#define lf1 0
#define lf2 1
#define lf3 2
#define lb1 4
#define lb2 5
#define lb3 6
#define rb1 8
#define rb2 9
#define rb3 10
#define rf1 12
#define rf2 13
#define rf3 14

double servoFreq = 50;
int LF_1 = 90, LF_2 = 90, LF_3 = 45;
int LB_1 = 80, LB_2 = 90, LB_3 = 60;
int RB_1 = 45, RB_2 = 105, RB_3 = 105;
int RF_1 = 70, RF_2 = 90, RF_3 = 65;
int degree,_time;

String input;

void setup(){
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(servoFreq);
  yield();
  Serial.flush();
  resetPos();
}

void loop(){
  
  while(Serial.available()>0){
    delay(10);
    char c = Serial.read();
    input+=c;
  }
  if(input.length()>0){
    Serial.print("Entered string: ");
    Serial.println(input);
  }
  
  if(input=="FWD"){
    Forward();
  }
  resetPos();
  input = "";
}

void servoWrite(uint8_t n, double angle){
  double pulse = map(angle,0,180,SERVOMIN,SERVOMAX);
  pwm.setPWM(n,0,pulse);
}

void resetPos(){
  servoWrite(0,90);
  servoWrite(1,90);
  servoWrite(2,45);
  servoWrite(4,80);
  servoWrite(5,90);
  servoWrite(6,60);
  servoWrite(8,45);
  servoWrite(9,105);
  servoWrite(10,105);
  servoWrite(12,70);
  servoWrite(13,90);
  servoWrite(14,65);
  LF_1 = 90, LF_2 = 90, LF_3 = 45;
  LB_1 = 80, LB_2 = 90, LB_3 = 60;
  RB_1 = 45, RB_2 = 105, RB_3 = 105;
  RF_1 = 70, RF_2 = 90, RF_3 = 65;
}

unsigned long prevMillis=0;

void Forward(){
  boolean cycledone = false;
  while(Serial.available()==0){
    boolean liftcycle = false;
    boolean lifted = false;
    //--------------------------------
    while(liftcycle==false&&(!cycledone)){
      if(lifted==false&&liftcycle==false){
        RB_2-=5;
        servoWrite(rb2,RB_2);
        Serial.print("RB_2:");
        Serial.println(RB_2);
        if(RB_2==65){
          lifted=true;
        }
      }
      unsigned long currentMillis = millis();
      if((currentMillis-prevMillis>=10)&&RB_1!=80){
        prevMillis=currentMillis;
        if(RB_1%2!=0){
          servoWrite(rb1,++RB_1);
          Serial.print("RB_1:");
          Serial.println(RB_1);
        }
        else{
          RB_1+=2;
          servoWrite(rb1,RB_1);
          Serial.print("RB_1:");
          Serial.println(RB_1);
        }
      }
      if(lifted==true&&RB_1==80){
        RB_2+=5;
        servoWrite(rb2,RB_2);
        Serial.print("RB_2:");
        Serial.println(RB_2);
        if(RB_2==105){
          lifted=false;
          liftcycle=true;
        }
      }
      if(Serial.available()>0)
      break;
    }
    liftcycle = false;
    lifted = false;
    //-------------------------
    while(liftcycle==false&&(!cycledone)){
      if(lifted==false&&liftcycle==false){
        LB_2-=5;
        servoWrite(lb2,LB_2);
        Serial.print("LB_2:");
        Serial.println(LB_2);
        if(LB_2==65){
          lifted=true;
        }
      }
      unsigned long currentMillis = millis();
      if((currentMillis-prevMillis>=10)&&LB_1!=45){
        prevMillis=currentMillis;
        if(LB_1%2==0){
          LB_1--;
          servoWrite(lb1,LB_1);
          Serial.print("LB_1:");
          Serial.println(LB_1);
        }
        else{
          LB_1-=2;
          servoWrite(lb1,LB_1);
          Serial.print("LB_1:");
          Serial.println(LB_1);
        }
      }
      if(lifted==true&&LB_1==45){
        LB_2+=5;
        servoWrite(lb2,LB_2);
        Serial.print("LB_2:");
        Serial.println(LB_2);
        if(LB_2==100){
          lifted=false;
          liftcycle=true;
        }
      }
      if(Serial.available()>0)
      break;
    }
    liftcycle = false;
    lifted = false;
    Serial.println("--------------------------");
    //--------------------------------
    while(liftcycle==false&&(!cycledone)){
      if(lifted==false&&liftcycle==false){
        RB_2-=5;
        servoWrite(rb2,RB_2);
        Serial.print("RB_2:");
        Serial.println(RB_2);
        if(RB_2==65){
          lifted=true;
        }
      }
      unsigned long currentMillis = millis();
      if((currentMillis-prevMillis>=10)&&RB_1!=35){
        prevMillis=currentMillis;
        if(RB_1%2==0){
          RB_1--;
          servoWrite(rb1,RB_1);
          Serial.print("RB_1:");
          Serial.println(RB_1);
        }
        else{
          RB_1-=2;
          servoWrite(rb1,RB_1);
          Serial.print("RB_1:");
          Serial.println(RB_1);
        }
      }
      if(lifted==true&&RB_1==35){
        if(RB_3!=125){
          RB_3+=5;
          servoWrite(rb3,RB_3);
          Serial.print("RB_3:");
          Serial.println(RB_3);
        }
        RB_2+=5;
        servoWrite(rb2,RB_2);
        Serial.print("RB_2:");
        Serial.println(RB_2);
        if(RB_2==110){
          lifted=false;
          liftcycle=true;
        }
      }
      if(Serial.available()>0)
      break;
    }
    lifted=false;
    liftcycle=false;
    Serial.println("-------------------------------------");
    //----------------------------------------
    while((!liftcycle)&&(!cycledone)){
      /*unsigned long currentMillis = millis();
      if(RB_1!=60||LB_1!=80||LF_1!=65||RF_1!=45){
        if(RB_1!=60){
          servoWrite(rb1,++RB_1);
          Serial.print("RB_1:");
          Serial.println(RB_1);
        }
        if(LB_1!=80){
          servoWrite(lb1,++LB_1);
          Serial.print("LB_1:");
          Serial.println(LB_1);
        }
        if(RF_1!=45){
          servoWrite(rf1,--RF_1);
          Serial.print("RF_1:");
          Serial.println(RF_1);
        }
        if(LF_1!=65){
          servoWrite(lf1,--LF_1);
          Serial.print("LF_1:");
          Serial.println(LF_1);
        }
      }
      if(RB_2!=105){
        servoWrite(rb2,--RB_2);
        Serial.print("RB_2:");
        Serial.println(RB_2);
      }
      if(LF_2!=100){
        servoWrite(lf2,++LF_2);
        Serial.print("LF_2:");
        Serial.println(LF_2);
      }
      if(LB_2!=90){
        servoWrite(lb2,--LB_2);
        Serial.print("LB_2:");
        Serial.println(LB_2);
      }
      if(RB_3!=95){
        RB_3-=2;
        servoWrite(rb3,RB_3);
        Serial.print("RB_3:");
        Serial.println(RB_3);
      }
      if(LF_3!=75){
        LF_3+=2;
        servoWrite(lf3,LF_3);
        Serial.print("LF_3:");
        Serial.println(LF_3);
      }
      if(LB_3!=80){
        LB_3+=2;
        servoWrite(lb3,LB_3);
        Serial.print("LB_3:");
        Serial.println(LB_3);
      }
      if(Serial.available()>0){
        break;
      }*/
    }
    cycledone=true;
  }
}

