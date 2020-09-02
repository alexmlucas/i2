void setup() 
{
  Serial.begin(31250);

  pinMode(0, OUTPUT);           // mulitplexer channel select.
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);

  pinMode(A0, OUTPUT);
  pinMode(A2, INPUT);  
  pinMode(A8, INPUT);
  pinMode(3, INPUT);
}

void loop() 
{
  digitalWrite(0, HIGH);         // bit 0
  digitalWrite(1, LOW);         // bit 1
  digitalWrite(2, LOW);         // bit 2

  delayMicroseconds(50);
  //Serial.println(int(digitalRead(3)));

  analogWrite(A0, 255);

  int reading1 = analogRead(A2);
  int reading2 = analogRead(A8);

  //Serial.println(OUTPUT);

  /*if(reading1 > 15)
  {
    Serial.println(int(reading1));
  }*/

  /*if(reading2 > 15)
  {
    Serial.println(int(reading2));
  }*/

  delay(10);

  // The next thing - put piezo ground on separate plane to reduce noise
}
