//sensor library
#include <DHT11.h>

/// added 8-3-2024
#include <Wire.h>
#include <BH1750.h>
#include "SparkFun_SGP30_Arduino_Library.h" 

SGP30 mySensor; //co2 sensor
BH1750 lightMeter; //light sensor


// Define the type of DHT sensor 
#define DHTPIN 2     // Digital pin connected to the DHT sensor (temperature)
#define DHTPIN 3    //DHT sensor (humidity)
#define DHTTYPE DHT11   


// Initialize DHT temperature sensor
DHT11 dhttemp(2);
DHT11 dhthumi(3);


//ph sensor
#define SensorPin A1          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10];
int temp;


//////28-2-24 added
bool pump1; //water pump
bool pump2; //acidic pump



void setup() 
{
  //output of relays
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  
  delay(1000); 

  /// added 8-3-2024
  Wire.begin();
  lightMeter.begin();
  Serial.println(F("BH1750 Test begin"));

    if (mySensor.begin() == false) 
  {
    Serial.println("No SGP30 Detected. Check connections.");
    //while (1);
  }

  mySensor.initAirQuality();


}


void loop()
{

  delay(500);

  tempsensor(); 
  humidity();
  ph();
  lightsensor();
  co2sensor();

}


void tempsensor()
{
  //temperature.ino sensor 19-2-24
 // read the temperature value from the DHT11 sensor.
  int temperature = dhttemp.readTemperature();
 
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");  
 
  delay(500);

}

void humidity()
{

  int humidity = dhthumi.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

}



void ph()
{
  
   for(int i=0;i<10;i++)       
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value
  Serial.print("pH:");  
  Serial.print(phValue,2);
  Serial.println(" ");

  if(phValue<5.5)
  {
    onPump1Change();
  }
  else if(phValue>6.8)
  {
    onPump2Change();  
  }

}


///////28-2-24 adding pump1 and pump2

void onPump1Change()  
{

  digitalWrite(11,1);
  Serial.println("Water is adding to the solution ");
  delay(1500);
  digitalWrite(11,0);
  delay(1000);

}


void onPump2Change()  
{

  digitalWrite(12,1);
  Serial.println("Acidic fertiliser is adding to the solution ");
  delay(1500);
  digitalWrite(12,0);
  delay(1000);
  
}

///code added on 8-3-24

void lightsensor()
{
  float lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(1000);

  if(lux<1000)
  {
    digitalWrite(9,1);
    Serial.println("Lamp switched on");
    delay(1000);
  }
  else
  {
    digitalWrite(9,0);
    Serial.println("Lamp switched off");
    delay(1000);
  }

}

void co2sensor()
{

  delay(1000); //Wait 1 second
  //measure CO2 and TVOC levels
  mySensor.measureAirQuality();
  Serial.print("CO2: ");
  Serial.print(mySensor.CO2);

  //co2 level
   Serial.println(" ppm");

  //air quality level
  Serial.print("TVOC: ");
  Serial.print(mySensor.TVOC);
  Serial.println(" ppb");

}


