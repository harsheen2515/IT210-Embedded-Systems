// the pin numbers for the button and the two lights the porch LED is the green one, while the hallway LED is the yellow one
int button = 4;
int porch_light = 2;
int hallway_light = 3;

//  this helps us to remember when the lights were turned on
unsigned long startTime;

// it helps us to recognise if the lighting sequence is currently running or not
bool lightsOn = false;

void setup()
{
  // Button is used to take input
  pinMode(button, INPUT_PULLUP);

  // Both LEDs are outputs
  pinMode(porch_light, OUTPUT);
  pinMode(hallway_light, OUTPUT);
}

// This function turns both lights on, and also the timer gets started
void turnLightsOn()
{
  digitalWrite(porch_light, HIGH);
  digitalWrite(hallway_light, HIGH);

  startTime = millis();
  lightsOn = true;
}

// This function checks the time and turns the lights off
void checkLights()
{
  // After 30 seconds, turn the porch light off
  if (millis() - startTime >= 30000)
  {
    digitalWrite(porch_light, LOW);
  }

  // After 60 seconds, turn the hallway light off
  if (millis() - startTime >= 60000)
  {
    digitalWrite(hallway_light, LOW);
    lightsOn = false;
  }
}

void loop()
{
  // If the button is pressed and no sequence is running, start it
  if (digitalRead(button) == LOW && lightsOn == false)
  {
    turnLightsOn();
  }

  // Keep checking the time while the lights are running
  if (lightsOn)
  {
    checkLights();
  }
}
