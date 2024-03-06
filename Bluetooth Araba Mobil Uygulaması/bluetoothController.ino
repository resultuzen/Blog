/*                                                              
       __                 _   _____ _   _               
      /__\ ___  ___ _   _| | /__   (_) (_)_______ _ __  
     / \/// _ \/ __| | | | |   / /\/ | | |_  / _ \ '_ \ 
    / _  \  __/\__ \ |_| | |  / /  | |_| |/ /  __/ | | |
    \/ \_/\___||___/\__,_|_|  \/    \__,_/___\___|_| |_|
    
*/

#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial Bluetooth (10, 9); // (RX, TX) Pinleri

AF_DCMotor motor1 (1, MOTOR12_64KHZ); // 1.Motor
AF_DCMotor motor2 (2, MOTOR12_64KHZ); // 2.Motor

#define solMotorHizi 255 // Sol motorun hızını ayarlamak için kullanılan komuttur.
#define sagMotorHizi 255 // Sağ motorun hızını ayarlamak için kullanılan komuttur.

#define solaDonKomutu 1  // Android uygulamadan gelen sola dönme komutudur.
#define ileriGitKomutu 2 // Android uygulamadan gelen ileri gitme komutudur.
#define sagaDonKomutu 3  // Android uygulamadan gelen sağa dönme komutudur.
#define geriGitKomutu 4  // Android uygulamadan gelen geri gitme komutudur.

int gelenVeri = 0;

void setup() 
{
   Bluetooth.begin(9600); 
   
   motor1.setSpeed(solMotorHizi); 
   motor2.setSpeed(sagMotorHizi); 
}
void loop() 
{
  if (Bluetooth.available() > 0)
  {
    gelenVeri = Serial.read();    
  }
  
  else if (gelenVeri == ileriGitKomutu) // İleri gidecek.
  {
    motor1.run(RELEASE);
    motor2.run(FORWARD);
  }
  
  else if (gelenVeri == geriGitKomutu) // Geri gidecek.
  {
    motor1.run(RELEASE);
    motor2.run(BACKWARD);
  }
  
  else if (gelenVeri == sagaDonKomutu) // Sağa dönecek.
  {
    motor1.run(FORWARD);
    motor2.run(RELEASE);    
  }
  
  else if (gelenVeri == solaDonKomutu) // Sola dönecek.
  {
    motor1.run(BACKWARD);
    motor2.run(RELEASE);
  }
  
  else
  {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }
}
