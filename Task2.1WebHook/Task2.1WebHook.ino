#include <WiFiNINA.h>
#include <ThingSpeak.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>

// DHT22 is connected to digital pin 2
#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Create the BH1750 light sensor
BH1750 lightMeter;

// Wi-Fi details
char ssid[] = "Galaxy A22805C";
char pass[] = "harsheen";

// ThingSpeak channel details
unsigned long myChannelNumber = 3462158;
const char *myWriteAPIKey = "BPTJMKS0O0ORKJC1";

WiFiClient client;


// Connect the Nano to the Wi-Fi network
void connectWiFi()
{
  Serial.print("Connecting to Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)
  {
    WiFi.begin(ssid, pass);

    Serial.print(".");
    delay(5000);
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");
}


// Read the current temperature from the DHT22
float readTemperature()
{
  float temperature = dht.readTemperature();

  // Check if the sensor failed to give a reading
  if (isnan(temperature))
  {
    Serial.println("Temperature reading failed!");
    return -1;
  }

  return temperature;
}


// Read the current light level from the BH1750
float readLight()
{
  float light = lightMeter.readLightLevel();

  // Check if the light sensor failed to give a reading
  if (light < 0)
  {
    Serial.println("Light reading failed!");
    return -1;
  }

  return light;
}


// Send the temperature and light readings to ThingSpeak
void sendToThingSpeak(float temperature, float light)
{
  // Field 1 stores temperature
  ThingSpeak.setField(1, temperature);

  // Field 2 stores light level
  ThingSpeak.setField(2, light);

  // Send both values to the ThingSpeak channel
  int response = ThingSpeak.writeFields(
    myChannelNumber,
    myWriteAPIKey
  );

  // ThingSpeak returns 200 when the update is successful
  if (response == 200)
  {
    Serial.println("ThingSpeak update successful!");
  }
  else
  {
    Serial.print("ThingSpeak error: ");
    Serial.println(response);
  }
}


// Runs once when the Arduino starts
void setup()
{
  Serial.begin(9600);

  // Start the DHT22 sensor
  dht.begin();

  // Start communication with the BH1750
  Wire.begin();
  lightMeter.begin();

  // Connect to the Wi-Fi
  connectWiFi();

  // Start ThingSpeak communication
  ThingSpeak.begin(client);

  Serial.println("System ready!");
}


// Runs repeatedly while the Arduino is powered
void loop()
{
  // Get the latest readings from both sensors
  float temperature = readTemperature();
  float light = readLight();

  // Display the readings in the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Light: ");
  Serial.print(light);
  Serial.println(" lux");

  // Only send the data if both readings are valid
  if (temperature >= 0 && light >= 0)
  {
    sendToThingSpeak(temperature, light);
  }

  Serial.println("-------------------------");

  // Wait 30 seconds before the next update
  delay(30000);
}
