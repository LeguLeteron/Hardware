#include <Mouse.h>

//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 6;
////Pin connected to DS of 74HC595
int dataPin = 7;

byte dataRED;
byte dataGREEN;
byte dataArrayRED[19];
byte dataArrayGREEN[19];

int Mouse_Up = A0;
int Mouse_Down = A1;
int Mouse_Left = A2;
int Mouse_Right = A3;

int A0_Test = 0;
int A1_Test = 0;
int A2_Test = 0;
int A3_Test = 0;

int Left_Button = 2;
int Right_Button = 3;

int moterPin = 4;
int moterPin2 = 10;

int vertValue = 0;
int horzValue = 0;

int Original = 100;

const int sensitivity = 200;  // Higher sensitivity value = slower mouse, should be <= about 500

void setup()
{
  Serial.begin(9600); 

  pinMode(latchPin, OUTPUT);
  dataArrayRED[1] = 0x20;
  dataArrayRED[2] = 0x3A; 
  dataArrayRED[3] = 0x10; 
  dataArrayRED[4] = 0x1A; 
  dataArrayRED[5] = 0x20; 
  dataArrayRED[6] = 0x3A; 
  dataArrayRED[7] = 0x26; 
  dataArrayRED[8] = 0x3A; 
  dataArrayRED[9] = 0x20;
  dataArrayRED[10] = 0x6E;
  dataArrayRED[11] = 0x32;
  dataArrayRED[12] = 0x46;
  dataArrayRED[13] = 0x2A;
  dataArrayRED[14] = 0x26;
  dataArrayRED[15] = 0x2A;
  dataArrayRED[16] = 0x6C;
  dataArrayRED[17] = 0x00;
  dataArrayRED[18] = 0x00;

  dataArrayGREEN[1] = 0x00;
  dataArrayGREEN[2] = 0x00;
  dataArrayGREEN[3] = 0x00;
  dataArrayGREEN[4] = 0x00; 
  dataArrayGREEN[5] = 0x00; 
  dataArrayGREEN[6] = 0x00; 
  dataArrayGREEN[7] = 0x00;
  dataArrayGREEN[8] = 0x00;
  dataArrayGREEN[9] = 0x00;
  dataArrayGREEN[10] = 0x00;
  dataArrayGREEN[11] = 0x00;
  dataArrayGREEN[12] = 0x00;
  dataArrayGREEN[13] = 0x00;
  dataArrayGREEN[14] = 0x00;
  dataArrayGREEN[15] = 0x00;
  dataArrayGREEN[16] = 0x00;
  dataArrayGREEN[17] = 0x7E;
  dataArrayRED[18] = 0x00;
  
  pinMode(moterPin, OUTPUT);
  pinMode(moterPin2, OUTPUT);

  digitalWrite(moterPin, LOW);
  digitalWrite(moterPin2, LOW);

  pinMode(Mouse_Up, INPUT);
  pinMode(Mouse_Down, INPUT);
  pinMode(Mouse_Left, INPUT);
  pinMode(Mouse_Right, INPUT);

  pinMode(Left_Button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Left_Button), Left_Click, RISING);

  pinMode(Right_Button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(Right_Button), Right_Click, RISING);

}

//------------------------------------------------------------------------------------------------------

void Left_Click()
{
      Mouse.press(MOUSE_LEFT);
      Mouse.release(MOUSE_LEFT);
}

//------------------------------------------------------------------------------------------------------

void Right_Click()
{
     Mouse.press(MOUSE_RIGHT);
     Mouse.release(MOUSE_RIGHT);
}


//------------------------------------------------------------------------------------------------------

void shiftOut(int myDataPin, int myClockPin, byte myDataOut) 
{
  // This shifts 8 bits out MSB first, 
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights. 
  for (i=7; i>=0; i--)  
  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result 
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000 
    // and proceeds to set pinState to 1.
    if ( myDataOut & (1<<i) ) 
    {
      pinState= 1;
    }
    else 
    {  
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

//------------------------------------------------------------------------------------------------------

void loop()
{
  while(Serial.available() > 0)
  {
    char data = Serial.read();
    if(data == '1')
    {
      Serial.println("ok1");
       digitalWrite(moterPin, HIGH);
       digitalWrite(moterPin2, HIGH);
       delay(140);
       digitalWrite(moterPin, LOW);
       digitalWrite(moterPin2, LOW);
    }
    
    else if(data == '2')
    {
      Serial.println("ok2");
       digitalWrite(moterPin, HIGH);
       digitalWrite(moterPin2, HIGH);
       delay(140);
       digitalWrite(moterPin, LOW);
       digitalWrite(moterPin2, LOW);
       delay(140);
       digitalWrite(moterPin, HIGH);
       digitalWrite(moterPin2, HIGH);
       delay(140);
       digitalWrite(moterPin, LOW);
       digitalWrite(moterPin2, LOW);
    }   

    else if(data == '3')
    {
       Serial.println("ok3");
       digitalWrite(moterPin, HIGH);
       digitalWrite(moterPin2, HIGH);
       delay(140);
       digitalWrite(moterPin, LOW);
       digitalWrite(moterPin2, LOW);
       delay(140);
       digitalWrite(moterPin, HIGH);
       digitalWrite(moterPin2, HIGH);
       delay(140);
       digitalWrite(moterPin, LOW);
       digitalWrite(moterPin2, LOW);
       delay(140);
       digitalWrite(moterPin, HIGH);
       digitalWrite(moterPin2, HIGH);
       delay(140);
       digitalWrite(moterPin, LOW);
       digitalWrite(moterPin2, LOW);
    }
     
    else if(data == '4')
    {
       for (int j = 1; j <= 18; j++) 
      {
      //load the light sequence you want from array
      dataRED = dataArrayRED[j];
      dataGREEN = dataArrayGREEN[j];
      //ground latchPin and hold low for as long as you are transmitting
      digitalWrite(latchPin, 0);
      
      //move 'em out
      shiftOut(dataPin, clockPin, dataGREEN);   
      shiftOut(dataPin, clockPin, dataRED);
      //return the latch pin high to signal chip that it 
      //no longer needs to listen for information
      
      digitalWrite(latchPin, 1);
      delay(300);

      digitalWrite(latchPin, 0);
      dataRED = dataArrayRED[18];
      dataGREEN = dataArrayGREEN[18];
      shiftOut(dataPin, clockPin, dataGREEN);   
      shiftOut(dataPin, clockPin, dataRED);
      digitalWrite(latchPin, 1);
      delay(100);

      if(j != 18)
      {
      digitalWrite(latchPin, 0);
      dataRED = dataArrayRED[17];
      dataGREEN = dataArrayGREEN[17];
      shiftOut(dataPin, clockPin, dataGREEN);   
      shiftOut(dataPin, clockPin, dataRED);
      digitalWrite(latchPin, 1);
      delay(100);
      }
      }
    }
  }
  
  A0_Test = analogRead(Mouse_Up);
  A1_Test = analogRead(Mouse_Down);
  A2_Test = analogRead(Mouse_Left);
  A3_Test = analogRead(Mouse_Right);

//------------------------------------------------------------------------------------------------------
/*
  if(A0_Test > Original)
  {
    vertValue = (-1 * A0_Test);
    
    if(A2_Test > A3_Test)
    {
      if(A2_Test > Original)
      {
        horzValue = (-1 * A2_Test);
      }
      else
      {
        horzValue = 0;
      }
    }

    else if(A3_Test > A2_Test)
    {
      if(A3_Test > Original)
      {
        horzValue = A3_Test;
      }
      else
      {
        horzValue = 0;
      }
    }
     Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
     Mouse.move(horzValue/sensitivity, 0, 0);  // move mouse on x axis
  }
  
//------------------------------------------------------------------------------------------------------

  if(A1_Test > Original)
  {
    vertValue = A1_Test;
    
    if(A2_Test > A3_Test)
    {
      if(A2_Test > Original)
      {
        horzValue = (-1 * A2_Test);
      }
      else
      {
        horzValue = 0;
      }
    }

    else if(A3_Test > A2_Test)
    {
      if(A3_Test > Original)
      {
        horzValue = A3_Test;
      }
      else
      {
        horzValue = 0;
      }
    }
     Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
     Mouse.move(horzValue/sensitivity, 0, 0);  // move mouse on x axis
  }

//------------------------------------------------------------------------------------------------------
  if(A2_Test > Original)
  {
    horzValue = (-1 * A2_Test);
    
    if(A0_Test > A1_Test)
    {
      if(A0_Test > Original)
      {
        vertValue = (-1 * A0_Test);
      }
      else
      {
        vertValue = 0;
      }
    }

    else if(A1_Test > A0_Test)
    {
      if(A1_Test > Original)
      {
        vertValue = A1_Test;
      }
      else
      {
        vertValue = 0;
      }
    }
     Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
     Mouse.move(horzValue/sensitivity, 0, 0);  // move mouse on x axis
  }
//------------------------------------------------------------------------------------------------------
  if(A3_Test > Original)
  {
    horzValue = A3_Test;
    
    if(A0_Test > A1_Test)
    {
      if(A0_Test > Original)
      {
        vertValue = (-1 * A0_Test);
      }
      else
      {
        vertValue = 0;
      }
    }

    else if(A1_Test > A0_Test)
    {
      if(A1_Test > Original)
      {
        vertValue = A1_Test;
      }
      else
      {
        vertValue = 0;
      }
    }
     Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
     Mouse.move(horzValue/sensitivity, 0, 0);  // move mouse on x axis
  }
  */
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

  if(A0_Test > Original)
  {
    vertValue = (-1 * A0_Test);
    
     horzValue = 0;
   
     Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
     Mouse.move(horzValue/sensitivity, 0, 0);  // move mouse on x axis
  }
  
//------------------------------------------------------------------------------------------------------

  if(A1_Test > Original)
  {
    vertValue = A1_Test;
    
    horzValue = 0;
  
     Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
     Mouse.move(horzValue/sensitivity, 0, 0);  // move mouse on x axis
  }

//------------------------------------------------------------------------------------------------------
  if(A2_Test > Original)
  {
    horzValue = (-1 * A2_Test);

    vertValue = 0;
  
   Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
     Mouse.move(horzValue/sensitivity, 0, 0);  // move mouse on x axis
  }
//------------------------------------------------------------------------------------------------------
  if(A3_Test > Original)
  {
    horzValue = A3_Test;
    
    vertValue = 0;
    
     Mouse.move(0, vertValue/sensitivity, 0);  // move mouse on y axis
     Mouse.move(horzValue/sensitivity, 0, 0);  // move mouse on x axis
  }
//------------------------------------------------------------------------------------------------------
  /*
  Serial.print(analogRead(horzPin)); // mouse X
  Serial.print("  ");           //space
  Serial.print(analogRead(vertPin)); // mouse Y
  Serial.print("  ");           //space
  //delay(5);
  */
}
