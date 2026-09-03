#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;

// Pins
const int PIR_PIN = 2;
const int BUTTON_PIN = 3;
const int LED1_PIN = 4; //red led
const int LED2_PIN = 5;  //green led

// Interrupt flags
volatile bool motionEvent = false;
volatile bool buttonEvent = false;

// Light state
bool lightsOn = false;

// Darkness limit
const float DARK_THRESHOLD = 50.0;

// Interrupt functions
void motionISR() {
  motionEvent = true;
}

void buttonISR() {
  buttonEvent = true;
}

// Control both LEDs
void setLights(bool state) {
  lightsOn = state;

  digitalWrite(LED1_PIN, state ? HIGH : LOW);
  digitalWrite(LED2_PIN, state ? HIGH : LOW);
}

void setup() {

  Serial.begin(9600);

  // Pins
  pinMode(PIR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  // Start with lights OFF
  setLights(false);

  // Start BH1750
  Wire.begin();
  lightMeter.begin();

  // Hardware interrupts
  attachInterrupt(
    digitalPinToInterrupt(PIR_PIN),
    motionISR,
    RISING
  );

  attachInterrupt(
    digitalPinToInterrupt(BUTTON_PIN),
    buttonISR,
    FALLING
  );

  Serial.println("-----------------------------");
  Serial.println("TASK 4.1 INTERRUPT SYSTEM");
  Serial.println("SYSTEM STARTED");
  Serial.println("-----------------------------");
}

void loop() {

  // Read light level
  float lux = lightMeter.readLightLevel();

  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");


  // =================================
  // BUTTON INTERRUPT
  // =================================

  if (buttonEvent) {

    buttonEvent = false;

    delay(50);

    if (digitalRead(BUTTON_PIN) == LOW) {

      // Toggle lights
      setLights(!lightsOn);

      if (lightsOn) {
        Serial.println("BUTTON -> LIGHTS ON");
      }
      else {
        Serial.println("BUTTON -> LIGHTS OFF");
      }

      // Wait until button released
      while (digitalRead(BUTTON_PIN) == LOW) {
        delay(10);
      }
    }
  }


  // =================================
  // PIR INTERRUPT
  // =================================

  if (motionEvent) {

    motionEvent = false;

    Serial.println("MOTION DETECTED");

    // Only turn lights ON when it is dark
    if (lux < DARK_THRESHOLD) {

      setLights(true);

      Serial.println("DARK + MOTION -> LIGHTS ON");
    }
    else {

      Serial.println("BRIGHT + MOTION -> LIGHTS NOT ON");
    }
  }


  // =================================
  // AUTOMATIC LIGHT OFF
  // =================================

  // If lights were automatically turned on
  // and the environment becomes bright,
  // turn them OFF.

  if (lightsOn && lux >= DARK_THRESHOLD) {

    setLights(false);

    Serial.println("BRIGHT -> LIGHTS OFF");
  }


  delay(300);
}
