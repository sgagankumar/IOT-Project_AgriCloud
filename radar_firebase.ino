#include <FirebaseArduino.h>
#include  <ESP8266WiFi.h>
#include <Servo.h> 


const int trigPin = D2;  
const int echoPin = D3; 
//attach servo to D5


Servo myservo;  // create servo object to control a servo 

#define FIREBASE_HOST "agricloud-7458b.firebaseio.com"
#define WIFI_SSID "vinay" // Change the name of your WIFI
#define WIFI_PASSWORD "vinay1234" // Change the password of your WIFI

void setup()
{
   Serial.begin(9600);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) 
   {
      delay(500);
      Serial.print(".");
   }
  Serial.println ("");
  Serial.println ("WiFi Connected!");

  
  Firebase.begin(FIREBASE_HOST);
    
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output]
  
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  myservo.attach(D5);
  

 
  
}

void loop() 
{
 
  int angle;
  long duration;
  int distance;
  for(angle = 0; angle <= 90 ; angle += 10)
  {                                       // in steps of 1 degree 
              
          //   Clears the trigPin
              digitalWrite(trigPin, LOW);
              delayMicroseconds(2);
              
              // Sets the trigPin on HIGH state for 10 micro seconds
              digitalWrite(trigPin, HIGH);
              delayMicroseconds(10);
              digitalWrite(trigPin, LOW);
              
              // Reads the echoPin, returns the sound wave travel time in microseconds
              duration = pulseIn(echoPin, HIGH);
              
              // Calculating the distance
              
              distance= duration*0.034/2;
              
              // Prints the distance on the Serial Monitor
              
              Serial.print("Distance: ");
              Serial.println(distance);
                 
              Serial.print("angle: ");
              Serial.println(angle);
              

              if (distance >= 10 && angle == 10 && distance <=30 )
                          {
                            Firebase.setFloat ("box",4);
                          }
                          
                          if (distance <= 15 && angle == 30 && distance <=30 )
                          {
                            Firebase.setFloat ("box",2);
                          }
                      
                           if (distance <= 30 && distance >=15 && angle == 40)
                          {
                            Firebase.setFloat ("box",3);
                          }
                      
                           if (distance <= 15 && angle == 70 && distance <=30)
                          {
                            Firebase.setFloat ("box",1);
                          }
          
              
              
              
          
              myservo.write(angle);              // tell servo to go to position in variable 'pos' 
              delay(10);                       // waits 15ms for the servo to reach the position 
  }
    

   for(angle = 90; angle>=0; angle-=10)     // goes from 180 degrees to 0 degrees 
  {                                       // in steps of 1 degree 
                
            //   Clears the trigPin
                digitalWrite(trigPin, LOW);
                delayMicroseconds(2);
                
                // Sets the trigPin on HIGH state for 10 micro seconds
                digitalWrite(trigPin, HIGH);
                delayMicroseconds(10);
                digitalWrite(trigPin, LOW);
                
                // Reads the echoPin, returns the sound wave travel time in microseconds
                duration = pulseIn(echoPin, HIGH);
                
                // Calculating the distance
                
                distance= duration*0.034/2;
                
                // Prints the distance on the Serial Monitor

                Serial.print("Distance: ");
                Serial.println(distance);
                Serial.print("angle: ");
                Serial.println(angle);

                if (distance >= 10 && angle == 10 && distance <=30 )
              {
                Firebase.setFloat ("box",4);
              }
              
              if (distance <= 15 && angle == 30 && distance <=30 )
              {
                Firebase.setFloat ("box",2);
              }
          
               if (distance <= 30 && distance >=15  && angle == 40)
              {
                Firebase.setFloat ("box",3);
              }
          
               if (distance <= 15 && angle == 70 && distance <=30)
              {
                Firebase.setFloat ("box",1);
              }
     
                myservo.write(angle);              // tell servo to go to position in variable 'pos' 
                delay(100);                       // waits 15ms for the servo to reach the position 
  }
}
