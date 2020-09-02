byte channel;

void setup() 
{
  Serial.begin(31250);

  pinMode(0, OUTPUT);           // mulitplex channel select.
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);

  pinMode(3, INPUT);

  channel = 0;
}

void loop() 
{

  // channel 0 = volume button
  // channel 1 = tempo button
  // channel 2 = up button
  // channel 3 = down button
  // channel 4 = pattern/kit 1 button
  // channel 5 = volume LED
  // channel 6 = tempo LED
  // channel 7 = pattern/kit 1 LED.

  Serial.println(OUTPUT);
  incrementChannel();
  delay(500);

  digitalWrite(0, bitRead(channel, 0));         // bit 0
  digitalWrite(1, bitRead(channel, 1));         // bit 1
  digitalWrite(2, bitRead(channel, 2));         // bit 2

  delayMicroseconds(50);
  //Serial.println(int(digitalRead(3)));

  analogWrite(A0, 255);

  int reading1 = digitalRead(3);

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

void incrementChannel()
{
  if(channel <= 6)
  {
    channel ++;
  } else 
  {
    channel = 0;
  }
}
