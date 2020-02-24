//**************************************************************//
//  Name    : shiftOutCode, Predefined Dual Array Style         //
//  Author  : Carlyn Maw, Tom Igoe                              //
//  Date    : 25 Oct, 2006                                      //
//  Version : 1.0                                               //
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                            //
//****************************************************************

//Pin connected to ST_CP of 74HC595
int latchPin = 5;
//Pin connected to SH_CP of 74HC595
int clockPin = 6;
////Pin connected to DS of 74HC595
int dataPin = 7;

int moterPin = 4;
int moterPin2 = 10;
int test = 1;

//holders for infromation you're going to pass to shifting function
byte dataRED;
byte dataGREEN;
byte dataArrayRED[10];
byte dataArrayGREEN[10];

void setup() 
{
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  //Serial.begin(9600);

  //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 
  dataArrayRED[1] = 0x02;
  dataArrayRED[2] = 0x04; 
  dataArrayRED[3] = 0x08; 
  dataArrayRED[4] = 0x10; 
  dataArrayRED[5] = 0x20; 
  dataArrayRED[6] = 0x40; 
  dataArrayRED[7] = 0x00; 
  dataArrayRED[8] = 0x00; 

  //Arduino doesn't seem to have a way to write binary straight into the code 
  //so these values are in HEX.  Decimal would have been fine, too. 
  dataArrayGREEN[1] = 0x00;
  dataArrayGREEN[2] = 0x00;
  dataArrayGREEN[3] = 0x00;
  dataArrayGREEN[4] = 0x00; 
  dataArrayGREEN[5] = 0x00; 
  dataArrayGREEN[6] = 0x00; 
  dataArrayGREEN[7] = 0x7E;
  dataArrayGREEN[8] = 0x7E; 

  //function that blinks all the LEDs
  //gets passed the number of blinks and the pause time

  //pinMode(moterPin, OUTPUT);
  //pinMode(moterPin2, OUTPUT);
}

void loop()
{ 
  for (int j = 1; j <= 7; j++) 
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
    delay(500);

   if(test == 1)
  {
    digitalWrite(moterPin, HIGH);
    digitalWrite(moterPin2, HIGH);
    test = 0;
  }
  else
  {
    digitalWrite(moterPin, LOW);
    digitalWrite(moterPin2, LOW);
    test = 1;
  }
  }


  
}

// the heart of the program
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


//blinks the whole register based on the number of times you want to 
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
