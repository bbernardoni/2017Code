const int inputPin = 
const int outputPin =  
long duration, inch;

void setup() {
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
}


void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(sonarRead(),DEC);
  delay(100);
}

int sonarRead(){
  digitalWrite(outputPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(outputPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);
  
  duration = pulseIn(inputPin, HIGH);
  inch = duration/74/2;
  return inch;
}

