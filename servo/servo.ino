#include <Servo.h>

Servo myservo;  // создаём объект для контроля сервы 
                // максимальное количество таких объектов - 8
 
int pos = 0;    // переменная для хранения позиции сервы 
 
void setup() 
{ 
  
  myservo.attach(3);  // серва подключена к 9-му пину
} 
 
 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // от 0 до 180 градусов
  {                                  // с шагом в 1 градус 
    myservo.write(pos);              // 
    delay(15);                       // ждём 15ms пока серва займёт новое положение
  } 
  for(pos = 180; pos>=1; pos-=1)     // от 180 до 0 градусов
  {                                
    myservo.write(pos);               
    delay(15);                       
  } 
}
