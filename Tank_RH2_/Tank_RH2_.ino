int Lights = 2;
int PwmA =  3;
char a;
char c;
char setMode;
int PwmB = 11;
int DirA = 12;
int DirB = 13;
int BrakeA = 9;
int BrakeB = 8;
int RightSensor = A2;
int LeftSensor = A3;
String command, mode;
boolean GotMode = false;
boolean Manual1 = false;
boolean Auto1 = false;
boolean manualcommand = false;

void setup(){
  Serial.begin(9600);
  pinMode(RightSensor, INPUT);
  pinMode(Lights, OUTPUT);
  pinMode(LeftSensor, INPUT);
  Serial.println("Waiting for Mode");
  while(GotMode == false){
   if(Serial.available()>0){
    a = Serial.read();
   }
   if(a=='0'){
    GotMode = true;
    mode = "Auto";
   }
   if(a=='1'){
    GotMode = true;
    mode = "Manual";
   }
  }
  if(mode == "Auto"){
    setMode = '0';
    Serial.println("Mode set to Auto");
  }
  if(mode == "Manual"){
    setMode = '1';
    Serial.println("Mode set to Manual");
  }
  Serial.println("Setup() complete.");
}

void loop(){
  if(setMode == '0'){
    Auto1 = true;
    Serial.println("Auto1 = true");
  }
  if(setMode == '1'){
    Manual1 = true;
    Serial.println("Manual1 = true");
  }
  while(Auto1 == true){
    Auto();
    Serial.println("Auto() function is in use.");
  }
  while(Manual1 == true){
    Manual();
  }
}

void Forward(){
  analogWrite(PwmA,200);
  analogWrite(PwmB,255);
  digitalWrite(BrakeA,0);
  digitalWrite(BrakeB,0);
  digitalWrite(DirA,1);
  digitalWrite(DirB,1);
}

void Stop(){
  analogWrite(PwmA,0);
  analogWrite(PwmB,0);
  digitalWrite(BrakeA,1);
  digitalWrite(BrakeB,1);
  digitalWrite(DirA,1);
  digitalWrite(DirB,1);
}

void Left(){
  analogWrite(PwmA,255);
  analogWrite(PwmB,255);
  digitalWrite(BrakeA,0);
  digitalWrite(BrakeB,0);
  digitalWrite(DirA,0);
  digitalWrite(DirB,1);
}

void Right(){
  analogWrite(PwmA,255);
  analogWrite(PwmB,255);
  digitalWrite(BrakeA,0);
  digitalWrite(BrakeB,0);
  digitalWrite(DirA,1);
  digitalWrite(DirB,0);
}

void Backward(){
  analogWrite(PwmA,200);
  analogWrite(PwmB,255);
  digitalWrite(BrakeA,0);
  digitalWrite(BrakeB,0);
  digitalWrite(DirA,0);
  digitalWrite(DirB,0);
}
void Auto(){
    if(analogRead(RightSensor)>500 && analogRead(LeftSensor)>500){
    Forward();
  }
  if(analogRead(RightSensor)<500 && analogRead(LeftSensor)>500){
    Left();
    delay(500);
    Forward();
  }
  if(analogRead(RightSensor)>500 &&analogRead(LeftSensor)<500){
    Right();
    delay(500);
    Forward();
  }
  if(analogRead(RightSensor)<500 && analogRead(LeftSensor)<500){
    Backward();
    delay(1000);
    Stop();
    delay(1000);
    Right();
    delay(1000);
    Stop();
    delay(500);
    Forward();
  }
}
void Manual(){
   while(manualcommand == false){
   if(Serial.available()>0){
    c = Serial.read();
    manualcommand = true;
   }
   }
  if(c == '8'){
    Forward();
  }
  if(c == '2'){
    Backward();
  }
  if(c == '5'){
    Stop();
    Serial.println("stopped");
  }
  if(c== '4'){
    Left();
  }
  if(c == '6'){
    Right();
  }
  if(c == '7'){
    digitalWrite(Lights, HIGH);
  }
  if(c == '9'){
    digitalWrite(Lights, LOW);
  }
  Serial.println("Manual() function is in use.");
  manualcommand = false;
}


