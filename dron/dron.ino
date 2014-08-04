#include <Servo.h>
#include <NewPing.h>
//#include <IRremote.h>

#define _angle  45


#define K_STOP   0x0

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

NewPing sonar(7, 6, 400);


#define ModeCheckArea 0
#define ModeWalk 1
#define ModeTurnLeft 2
#define ModeTurnRight 3



#define StepsCount 15




Servo myservo;


class Dron {
  public:
    
    Dron(){
      interval = 10;
      mode = ModeCheckArea;

       
       pinMode(10,OUTPUT); // Enable Motor B
       pinMode(8,OUTPUT); // Dir 1 Motor B
       pinMode(9,OUTPUT); // Dir 2 Motor B
       pinMode(12,OUTPUT); // Dir 1 Motor A
       pinMode(13,OUTPUT); // Dir 2 Motor A
       pinMode(11,OUTPUT); // Enab Motor A
       
       digitalWrite(10, 1);
       
       digitalWrite(11, HIGH);

    };
 
    void init(){
      
      for(int i = 0; i < StepsCount; i++)
      {
        _areaScan[i] = 0;      
      }
    };
    
    void startLoop(){
      switch(mode)
      {
        case ModeCheckArea:
          checkArea();
          break;
        case ModeWalk:
          go(K_TOP);
          break;
        case ModeTurnLeft:
          go(K_LEFT);
          break;
        case ModeTurnRight:
          go(K_RIGHT);
          break;
      }
    };
    
  private:
    
    void checkArea()
    {  
        go(K_STOP);
//      delay(90);
       int pos = 0;
       
       int angleStep = 90 / StepsCount;
       
         for(pos = 0; pos < StepsCount; pos += 1)  // от 0 до 180 градусов
          {                                  // с шагом в 1 градус 
            myservo.write(angleStep * pos + _angle);              
            delay(15);                       // ждём 15ms пока серва займёт новое положение
            
            scanArea(pos, getDistance(), false);
          } 
          
          for(pos = StepsCount; pos>=1; pos-=1)     // от 180 до 0 градусов
          {                                
            myservo.write(angleStep * pos + _angle);               
            delay(15);                       
            
            scanArea(pos, getDistance(), true);
          } 
          
          calculateDirection();
    };
    
    void calculateDirection(){
      
      int defPos = 0;
      int minDist = 500;
      
      int leftMin = 500;
      int rightMin = 500;
      
       for(int i = 0; i < StepsCount; i++)
       {
          minDist = min(_areaScan[i], minDist);

          if(StepsCount / 2 > i)
          {
            leftMin = min(_areaScan[i], leftMin);           
          }
          else
          {
            rightMin = min(_areaScan[i], rightMin);       
          }          
       }
       if(minDist > 100) 
       {
         mode = ModeWalk;
         interval = minDist * 20; /// meters per second
//         interval = 1000; //minDist * 10; /// meters per second
         
         return;
       } 
       else if(minDist > 50) 
       {
         mode = ModeWalk;
         interval = 500; /// meters per second
         
         return;
       } 
       else
       {
         interval = 300;
         
//         mode = ModeCheckArea;
         
         if(leftMin < rightMin)
         {
           mode = ModeTurnRight;
         }
         else
         {
           mode = ModeTurnLeft;
         }
       }       
    };
    
    
    void scanArea(int pos, int dist, boolean correction){
      if(!correction)
        _areaScan[pos] = dist;
      else
        _areaScan[pos] = (_areaScan[pos] + dist) / 2;      
    };
    
    int getDistance(){
      int uS = 0;

//      while(uS == 0)
      {
        delay(35);
          uS = sonar.ping_cm();
        if(uS == 0)
        {
          delay(15);
          uS = sonar.ping_cm();
          if(uS == 0)
          {            
            delay(15);
            uS = sonar.ping_cm();
            if(uS == 0)
            {
              uS = 500;
            }
          }
        }
      }   
   
       return uS;   
    };

    void go(int direction)
    { 
      switch(direction)
      {
      case K_STOP:
        {
          digitalWrite(9, LOW);
          digitalWrite(13, LOW);
    
          digitalWrite(8, LOW);
          digitalWrite(12, LOW);
    
          lastDir = K_STOP;
          return;          
        }
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
      
      delay(interval);
      
      mode = ModeCheckArea;
    };
    
    unsigned int _areaScan[StepsCount];
    
    unsigned int lastDir;
    unsigned int mode;
    float interval;
};

Dron dron;

void setup()   {
  //Serial.begin(9600);
   myservo.attach(3);
}


void loop() {

  dron.startLoop();

}


