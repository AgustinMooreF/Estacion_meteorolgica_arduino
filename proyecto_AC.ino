
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <SoftwareSerial.h>    



#define DHTPIN 6 //Defiene el pin al que se conectará el sensor
#define DHTTYPE DHT11 //Seleciona el tipo de sensor


int RS = 12;
int E = 11;
int d4 = 5;
int d5 = 4;
int d6 = 3;
int d7 = 2;

Servo servo1; // definir Servo
Adafruit_BMP280 bmp; // definir sensor barometrico i2c
DHT dht(DHTPIN, DHTTYPE);//definir tipo de sensor dht
LiquidCrystal lcd( RS, E, d4, d5, d6, d7); //configurar pantalla lcd
SoftwareSerial BT(10,11); 

void setup() {
  
  BT.begin(9600);
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16,2);
  servo1.attach(9);
  pinMode(2,OUTPUT);
  
   if (!bmp.begin()) {
    Serial.println(F("no encontro el bmp280"));
    while (1);
  }

   
}

void loop() {

  
  int hum_dht = dht.readHumidity();
  int temp_dht = dht.readTemperature();
  int pres_bmp = bmp.readPressure();

  if (isnan(hum_dht)||isnan(temp_dht))
   {
        Serial.print("error en el sensor DHT11");
        return;
    }
  Serial.print(temp_dht);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("tem:");
  lcd.print(temp_dht);
  lcd.print("C ");
  lcd.setCursor(8, 0);
  lcd.print("hum:");
  lcd.print(hum_dht);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("presion:");
  lcd.print(pres_bmp);
  lcd.print("Hpa");
  
  delay(8000);

   if(BT.available())    
  {
    Serial.write(BT.read());
  }
 
  if(Serial.available())  
  {
     BT.write(Serial.read());
  }  
 
  if(temp_dht > 22 && hum_dht < 40 && pres_bmp > 28000 ){
       digitalWrite(7,HIGH);
        servo1.write(90);
    }
       else{
          digitalWrite(7,LOW);
          servo1.write(0);
       }
  
    
}
