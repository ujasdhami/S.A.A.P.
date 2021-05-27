/* Integration of:
 *  Ultrasonic Sensor
 *  GPS Module
 *  SMS Module
 *  Shock Sensor
 *  
 *  Baud = 9600
 */
#include "TinyGPS++.h"  //GPS_Module Library
#include "SoftwareSerial.h"
#include <SoftwareSerial.h>
SoftwareSerial serial_connection(10, 11);
SoftwareSerial SIM900A(10,11);  //SIM900A SMS Module
int SHK_PIN = 3; //Pin for the shock sensor
int shk; //Variable to store the shk reading
TinyGPSPlus gps;
int trigPin = 9;
int echoPin = 10;
int LED = 13;  //For the Ultrasonic Sensor
int led2 = 2;  //LEDs
int led3 = 5;
int led4 = 4;
//Setup the Arduino
void setup() 
{
  SIM900A.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.println ("SIM900A Ready");
  delay(100);
  Serial.begin(9600); //Start the serial connection to the computer
  pinMode(SHK_PIN, INPUT); //shock pin
  pinMode(LED, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);//Make the pin you used an input on the Arduino
  serial_connection.begin(9600);//This opens up communications to the GPS
   pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("GPS Start");
}

//This code will run infinitely
void loop() 
{
  digitalWrite(LED, LOW);
  delay(1); //Delay 1mS to slow to 1000 readings per second
   while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
   
  if(digitalRead(SHK_PIN) == HIGH) //Read the shock sensor
  {
    SIM900A.println("AT + CMGS = \"+NUM_HERE\"");
  String dataMessage = ("Your car has experienced a high-pitched shock");
      delay(100);
  SIM900A.print(dataMessage);
      delay(100);
       SIM900A.println((char)26); 
      delay(100);
      SIM900A.println();
      // Give module time to send SMS
      delay(100);  
    digitalWrite(LED, HIGH);
    Serial.println("Shock Detected"); //Print out that we have been shaken
    Serial.println("Resetting...");
    delay(50); //Wait half a second before reading again
   
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.println("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.println("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.println("Longitude:");
    Serial.println(gps.location.lng(), 6);
    Serial.println("Speed MPH:");
    Serial.println(gps.speed.mph());
    Serial.println("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");
    SIM900A.println("AT + CMGS = \"+NUM_HERE\"");
  String dataMessage = ("latitude: ");
dataMessage = (gps.location.lat());
delay(100);
  SIM900A.print(dataMessage);
      delay(100);
       SIM900A.println((char)26); 
      delay(100);
      SIM900A.println();
      // Give module time to send SMS
      delay(100);  
    digitalWrite(LED, HIGH);
     SIM900A.println("AT + CMGS = \"+NUM_HERE\"");
  String dataMessage5 = ("longitude: ");
dataMessage5 = (gps.location.lng());
delay(100);
  SIM900A.print(dataMessage5);
      delay(100);
       SIM900A.println((char)26); 
      delay(100);
      SIM900A.println();
      // Give module time to send SMS
      delay(100);  
    digitalWrite(LED, HIGH);
     SIM900A.println("AT + CMGS = \"+NUM_HERE\"");
  String dataMessage4 = ("Altitude: ");
dataMessage4 = (gps.altitude.feet());
delay(100);
  SIM900A.print(dataMessage4);
      delay(100);
       SIM900A.println((char)26); 
      delay(100);
      SIM900A.println();
      // Give module time to send SMS
      delay(100);  
    digitalWrite(LED, HIGH);
     SIM900A.println("AT + CMGS = \"+NUM_HERE\"");
  String dataMessage3 = ("Speed: ");
dataMessage3 = (gps.speed.mph());
delay(100);
  SIM900A.print(dataMessage3);
      delay(100);
       SIM900A.println((char)26); 
      delay(100);
      SIM900A.println();
      // Give module time to send SMS
      delay(100);  
    digitalWrite(LED, HIGH);
     SIM900A.println("AT + CMGS = \"+NUM_HERE\"");
  String dataMessage2 = ("Satellite Count: ");
dataMessage2 = (gps.satellites.value());
delay(100);
  SIM900A.print(dataMessage2);
      delay(100);
       SIM900A.println((char)26); 
      delay(100);
      SIM900A.println();
      // Give module time to send SMS
      delay(100);  
    digitalWrite(LED, HIGH);
    Serial.println("Shock Detected"); //Print out that we have been shaken
    Serial.println("Resetting...");
    delay(50);
    
  }
    
  }
  else
  {
    digitalWrite(LED, LOW);
  }
   long duration, distance;
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance =(duration/2)/29.1;

 
 if((distance<=15)&& (distance>12))  //Ultrasonic Sensor configuration
  {
    digitalWrite(LED, HIGH);
    delay(1);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  if((distance<=12) && (distance>9))
  {
    digitalWrite(led2, HIGH);
    delay(1); 
  }
   else
  {
    digitalWrite(led2, LOW);
  }
  if((distance<=9) && (distance>6))
  {
    digitalWrite(led3, HIGH);
    delay(1);
  }
   else
  {
    digitalWrite(led3, LOW);
  }
  if((distance<=6))
  {
    digitalWrite(led4, HIGH);
    delay(1);
  }
   else
  {
    digitalWrite(led4, LOW);
  }
  
  
}
