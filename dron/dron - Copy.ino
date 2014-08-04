#include <NewPing.h>
#include <IRremote.h>









//#include <Adafruit_GFX.h>
//include <Adafruit_PCD8544.h>


// pin 7 - Serial clock out (SCLK)
// pin 6 - Serial data out (DIN)
// pin 5 - Data/Command select (D/C)
// pin 4 - LCD chip select (CS)
// pin 3 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(3, 4, 5, 7, 6);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define RECV_PIN 4

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16


#define K_TOP   0x511DBB
#define K_BOTTOM   0xA3C8EDDB
#define K_RIGHT   0x20FE4DBB
#define K_LEFT   0x52A3D41F
#define K_OK   0xD7E84B1B
#define K_STAR   0x32C6FDF7
#define K_SHARP   0x3EC3FC1B
#define K_0   0x1BC0157B
#define K_1   0xC101E57B
#define K_2   0x97483BFB
#define K_3   0xF0C41643
#define K_4   0x9716BE3F
#define K_5   0x3D9AE3F7
#define K_6   0x6182021B
#define K_7   0x8C22657B
#define K_8   0x488F3CBB
#define K_9   0x449E79F

#define K_CONTINUE 0x50C5D1F


#define MotorAForw 8
#define MotorARevers 9
#define MotorBForw 12
#define MotorBRevers 13


//NewPing sonar(7, 6, 400);

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()   {
  //  Serial.begin(115200);
  Serial.begin(9600);


  //  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  //  display.setContrast(38);

  //pinMode(RECV_PIN,INPUT);
  //pinMode(RECV_PIN,INPUT);

//  irrecv.enableIRIn();

   pinMode(10,OUTPUT); // Enable Motor B
   pinMode(8,OUTPUT); // Dir 1 Motor B
   pinMode(9,OUTPUT); // Dir 2 Motor B
   pinMode(12,OUTPUT); // Dir 1 Motor A
   pinMode(13,OUTPUT); // Dir 2 Motor A
   pinMode(11,OUTPUT); // Enab Motor A
   
   
   digitalWrite(10, 1);
   
   digitalWrite(11, HIGH);


//   digitalWrite(12, 1);

   
  /* analogWrite(10,255); 
   analogWrite(11,255); */


}

long lastDir = 0;

void go(long dir)
{  

  if(dir == K_CONTINUE)
  {
    dir = lastDir;
//    Serial.println("cont");
  }

//  Serial.println(dir);

  switch(dir)
  {
  case K_TOP:
    {
      digitalWrite(9, HIGH);
      digitalWrite(13, HIGH);

      digitalWrite(8, LOW);
      digitalWrite(12, LOW);

      lastDir = K_TOP;
      break;
    }
  case K_BOTTOM:
    {
      digitalWrite(8, HIGH);
      digitalWrite(12, HIGH);

      digitalWrite(9, LOW);
      digitalWrite(13, LOW);
      lastDir = K_BOTTOM;
      break;
    }
  case K_LEFT:
    {
      digitalWrite(13, HIGH);
      digitalWrite(8, HIGH);
      lastDir = K_LEFT;
      break;
    }
  case K_RIGHT:
    {
      digitalWrite(9, HIGH);
      digitalWrite(12, HIGH);
      lastDir = K_RIGHT;
      break;
    }    
  }
}

long step = 0;

void loop() {

//    delay(500);
  /* int uS = sonar.ping_cm();
   Serial.print("Ping: ");
   Serial.print(uS);
   Serial.println("cm");
   */


  //



  /*if (irrecv.decode(&results)) {
    {
      step = 0;

      //Serial.println("test");

      long val = decodeHash(&results);
      go(val);
    }
    irrecv.resume(); // Receive the next value
  } */
  /*  else
   {
   step ++;
   
   //Serial.println("khgkgk");
   
   if(step > 15)
   {
   digitalWrite(8, LOW);
   digitalWrite(9, LOW);
   digitalWrite(12, LOW);
   digitalWrite(13, LOW);
   
   lastDir = 0;
   step = 0;
   }
   }*/
}


int compare(unsigned int oldval, unsigned int newval) {
  if (newval < oldval * .8) {
    return 0;
  } 
  else if (oldval < newval * .8) {
    return 2;
  } 
  else {
    return 1;
  }
}

#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261

unsigned long decodeHash(decode_results *results) {
  unsigned long hash = FNV_BASIS_32;
  for (int i = 1; i+2 < results->rawlen; i++) {
    int value = compare(results->rawbuf[i], results->rawbuf[i+2]);
    hash = (hash * FNV_PRIME_32) ^ value;
  }
  return hash;
} 




void text(decode_results &results)
{
  int count = results.rawlen;

  /*  display.clearDisplay();
   
   display.setTextSize(1);
   display.setTextColor(BLACK);
   for (int i = 0; i < count; i++) {
   if ((i % 2) == 1) {
   display.print(results.rawbuf[i]*USECPERTICK, DEC);
   } 
   else {
   display.print(-(int)results.rawbuf[i]*USECPERTICK, DEC);
   }
   display.print(" ");
   }
   Serial.println(""); 
   display.display();
   */
}




void testdrawchar(void) {
  /*  display.setTextSize(0.5);
   display.setTextColor(BLACK);
   display.setCursor(0,0);
   
   for (uint8_t i=0; i < 168; i++) {
   if (i == '\n') continue;
   display.write(i);
   //if ((i > 0) && (i % 14 == 0))
   //display.println();
   }    
   display.display();*/
}

