const int green_led = 18;
const int red_led = 5;
const int yellow_led = 4;

void setup(){
  Serial.begin(115200);
  pinMode(green_led,OUTPUT);
  pinMode(red_led,OUTPUT);
  pinMode(yellow_led,OUTPUT);
}

void loop(){
  digitalWrite(green_led,HIGH);
  delay(1000);
  digitalWrite(green_led,LOW);
  delay(1000);

  digitalWrite(red_led,HIGH);ś
  delay(1000);
  digitalWrite(red_led,LOW);
  delay(1000);

  digitalWrite(yellow_led,HIGH);
  delay(1000);
  digitalWrite(yellow_led,LOW);
  delay(1000);
}
