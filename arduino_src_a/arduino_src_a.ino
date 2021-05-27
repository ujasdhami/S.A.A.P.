/* Integration of:
 *  Temperature Sensor
 *  Voltage Sensor
 *  Sound Sensor (Voice Recognition)
 *  LCD Display
 *  
 *  Baud = 9600
 */
#include <LiquidCrystal.h>  //LED Display
#include <dht.h>  //Temperature Sensor
#define dht_apin A0 // Analog Pin sensor is connected to //Pin for the shock 

int analogInput = A1;
float vout = 0.0;
float vin = 0.0;
float R1 = 30000.0; 
float R2 = 7500.0; 
int value = 0;
const int soundpin=A2;  //Sound Sensor for Voice Recogntion (Config)
const int threshold=200;
const int ledpin = 13;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

dht DHT;


void setup()
{
   lcd.begin(16, 2);
  pinMode(soundpin,INPUT);
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
  pinMode(analogInput, INPUT);
 lcd.print("Temp: Humidity: Voltage: ");
  
  // Print a message to the LCD.
}

void loop()
{
  lcd.setCursor(0, 1);
   DHT.read11(dht_apin);
   int soundsens=analogRead(soundpin); // reads analog data from sound sensor
if (soundsens>=threshold) {
digitalWrite(ledpin,HIGH); //turns led on

   Serial.println("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    delay(3);
    Serial.println("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.print("C  ");
    delay(3);//Wait 5 seconds before accessing sensor again.
 //Delay 1mS to slow to 1000 readings per second
 
   value = analogRead(analogInput);
   vout = (value * 5.0) / 1024.0; // see text
   vin = vout / (R2/(R1+R2)); 
   
Serial.println("INPUT V= ");
Serial.print(vin,2);
delay(3);
  lcd.print(DHT.humidity);
  lcd.setCursor(7,1);
  lcd.print(DHT.temperature);  
  delay(4000);

}
else{
  digitalWrite(ledpin,LOW);

}
}
