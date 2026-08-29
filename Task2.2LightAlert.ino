#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <BH1750.h>
#include <Wire.h>

// =========================
// Wi-Fi DETAILS
// =========================
const char* ssid = "YOUR_WIFI_NAME";
const char* wifiPassword = "YOUR_WIFI_PASSWORD";

// =========================
// HIVEMQ DETAILS
// =========================
const char* mqtt_server =
  "fc04ed8fa91345c58f4ac4590f7597f0.s1.eu.hivemq.cloud";

const int mqtt_port = 8883;

const char* mqtt_user = "YOUR_MQTT_USERNAME";
const char* mqtt_password = "YOUR_MQTT_PASSWORD";

// MQTT topic
const char* mqtt_topic = "lightsensor/lux";

// =========================
// OBJECTS
// =========================
WiFiSSLClient wifiClient;
PubSubClient mqttClient(wifiClient);
BH1750 lightMeter;

// =========================
// WIFI CONNECTION
// =========================
void connectWiFi() {

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    WiFi.begin(ssid, wifiPassword);

    for (int i = 0; i < 10; i++) {
      delay(500);
      Serial.print(".");

      if (WiFi.status() == WL_CONNECTED) {
        break;
      }
    }
  }

  Serial.println();
  Serial.print("WiFi connected");
  Serial.print(" IP Address: ");
  Serial.println(WiFi.localIP());
}

// =========================
// MQTT CONNECTION
// =========================
void connectMQTT() {

  while (!mqttClient.connected()) {

    Serial.print("Connecting to HiveMQ...");

    if (mqttClient.connect(
          "ArduinoNano33IoT",
          mqtt_user,
          mqtt_password)) {

      Serial.println("connected");

    } else {

      Serial.print("failed, state=");
      Serial.println(mqttClient.state());

      delay(5000);
    }
  }
}

// =========================
// SETUP
// =========================
void setup() {

  Serial.begin(9600);

  delay(2000);

  // Start I2C
  Wire.begin();

  // Start BH1750
  lightMeter.begin();

  // Connect Wi-Fi
  connectWiFi();

  // Set HiveMQ server
  mqttClient.setServer(mqtt_server, mqtt_port);

  // Connect to HiveMQ
  connectMQTT();
}

// =========================
// LOOP
// =========================
void loop() {

  // Make sure MQTT is connected
  if (!mqttClient.connected()) {
    connectMQTT();
  }

  mqttClient.loop();

  // Read light
  float lux = lightMeter.readLightLevel();

  Serial.print("Light: ");
  Serial.print(lux, 2);
  Serial.println(" lx");

  // Convert lux to String
  String message = String(lux, 2);

  // Publish to HiveMQ
  if (mqttClient.publish(mqtt_topic, message.c_str())) {

    Serial.print("Published: ");
    Serial.println(message);

  } else {

    Serial.println("Publish failed");
  }

  delay(2000);
}
