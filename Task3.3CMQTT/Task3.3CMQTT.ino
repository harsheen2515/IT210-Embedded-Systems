#include <WiFiNINA.h>
#include <PubSubClient.h>

// WiFi details used to connect the Arduino to the hotspot
const char* ssid = "Galaxy A22805C";
const char* password = "YOUR_WIFI_PASSWORD";

// MQTT broker and the two topics used for the project
const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;

const char* waveTopic = "ES/Wave";
const char* patTopic  = "ES/Pat";

// Pins connected to the ultrasonic sensor
const int trigPin = 8;
const int echoPin = 9;

// Pins connected to the two LEDs
const int redLED = 4;   //Bathroom
const int greenLED = 5;   //Hallway

// MQTT connection setup
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

// Variables used to keep track of the measured distance
float distance;
float previousDistance = 0;

unsigned long lastDetection = 0;
const unsigned long detectionCooldown = 1500;


// Check messages received from the MQTT broker
void callback(char* topic, byte* payload, unsigned int length) {

  String message = "";

  // Convert the received MQTT message into a readable string
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Received topic: ");
  Serial.println(topic);

  Serial.print("Message: ");
  Serial.println(message);

  // When a wave message is received, turn both LEDs on
  if (String(topic) == waveTopic) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);

    Serial.println("WAVE -> LEDs ON");
  }

  // When a pat message is received, turn both LEDs off
  if (String(topic) == patTopic) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);

    Serial.println("PAT -> LEDs OFF");
  }
}


// Connect the Arduino to the MQTT broker
void reconnectMQTT() {

  while (!mqttClient.connected()) {

    Serial.print("Connecting to MQTT...");

    String clientID = "HarsheenNano33IoT";

    if (mqttClient.connect(clientID.c_str())) {

      Serial.println("MQTT connected!");

      // Listen for both wave and pat messages
      mqttClient.subscribe(waveTopic);
      mqttClient.subscribe(patTopic);

      Serial.println("Subscribed to ES/Wave");
      Serial.println("Subscribed to ES/Pat");

    } else {

      Serial.print("Failed, state=");
      Serial.println(mqttClient.state());

      delay(2000);
    }
  }
}


// Take a distance reading from the ultrasonic sensor
float getDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Send a short trigger pulse to start the measurement
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  // Return a large value if no echo is detected
  if (duration == 0) {
    return 999;
  }

  float d = duration * 0.0343 / 2;

  return d;
}


// Initial setup for the sensor, LEDs, WiFi and MQTT
void setup() {

  Serial.begin(9600);
  delay(1000);

  // Set the sensor and LED pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  // Start with both LEDs switched off
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);


  // Connect the Arduino to WiFi

  Serial.print("Connecting to WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected!");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  // Set up the MQTT connection

  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCallback(callback);

  reconnectMQTT();


  // Get the first distance reading before starting detection
  previousDistance = getDistance();

  Serial.println("System ready!");
}


// Main part of the program that runs continuously
void loop() {

  // Reconnect to MQTT if the connection is lost
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }

  mqttClient.loop();


  // Read the current distance from the ultrasonic sensor

  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  // Detect a wave when the hand moves from near the sensor to farther away

  if (previousDistance < 25 &&
      distance > 35 &&
      millis() - lastDetection > detectionCooldown) {

    Serial.println("WAVE DETECTED!");

    // Send the name to the wave topic
    mqttClient.publish(waveTopic, "Harsheen");

    // Turn both LEDs on when a wave is detected
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);

    lastDetection = millis();
  }


  // Detect a pat when the hand or object comes very close to the sensor

  if (distance < 10 &&
      millis() - lastDetection > detectionCooldown) {

    Serial.println("PAT DETECTED!");

    // Send the name to the pat topic
    mqttClient.publish(patTopic, "Harsheen");

    // Turn both LEDs off when a pat is detected
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);

    lastDetection = millis();
  }


  // Save the current reading so it can be compared next time
  previousDistance = distance;

  delay(100);
}
