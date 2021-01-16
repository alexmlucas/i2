//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

int potPin = A0;  
int mux1InPin = A2;
int mux2InPin = A1;
int muxSelPin0 = 7;
int muxSelPin1 = 8;
int muxSelPin2 = 9;
int ledIndex = 0;
int soloLedPin = 5;

int lastPotValue = 0;

//Pin connected to ST_CP of 74HC595
int latchPin = 10;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

int ledToLight[] = {1, 2, 4, 8, 16, 32, 64, 128};

elapsedMillis ledTimer;

void setup() 
{
  pinMode(potPin, INPUT);
  pinMode(mux1InPin, INPUT);
  pinMode(mux2InPin, INPUT);
  pinMode(muxSelPin0, OUTPUT);
  pinMode(muxSelPin1, OUTPUT);
  pinMode(muxSelPin2, OUTPUT);
  pinMode(soloLedPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {

  int currentPotValue = analogRead(potPin);

  if(currentPotValue != lastPotValue)
  {
    //Serial.println(currentPotValue);
    lastPotValue = currentPotValue;
  }
 

  if(ledTimer > 500)
  {
    if (ledIndex == 8)
    {
      ledIndex = 0;
      //digitalWrite(soloLedPin, HIGH);           // abitrary lighting of the solo LED.
    } else
    {
      digitalWrite(soloLedPin, LOW);
    }
    
    // take the latchPin low so 
    // the LEDs don't change while you're sending in bits:
    digitalWrite(latchPin, LOW);
    // shift out the bits:
    shiftOut(dataPin, clockPin, MSBFIRST, ledToLight[ledIndex]);  

    //take the latch pin high so the LEDs will light up:
    digitalWrite(latchPin, HIGH);
    // pause before next value:
    ledIndex++;
    ledTimer = 0;
  }

  /*// show all 8 sensor readings
  for (byte i = 0; i < 8; i++)
  {
    if (readSensor(i, mux1InPin) == LOW) 
    {
     //Button is not pressed...
    } else 
    {
    //Button is pressed
    Serial.print(i);
    Serial.println(" Button  is pressed!!!");
    }
  }*/

  // show all 8 sensor readings
  for (int i = 0; i < 8; i++)
  {
    Serial.print(i);
    Serial.print(" = ");
    setSensor(i);

    if (i == 4)
    {
      Serial.print(analogRead(mux1InPin));
    } else
    {
      Serial.print(digitalRead(mux1InPin));
    }

    Serial.print("  ");
    delay(5);

    if(i == 7)
    {
      Serial.println();
    }
  }

  
}


 
void setSensor(int index)
{
  int b0 = bitRead(index, 0);
  int b1 = bitRead(index, 1);
  int b2 = bitRead(index, 2);

  digitalWrite(muxSelPin0, b0);
  digitalWrite(muxSelPin1, b1);
  digitalWrite(muxSelPin2, b2);  
} 
