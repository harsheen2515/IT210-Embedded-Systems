#define BLYNK_TEMPLATE_ID "TMPL3OM9UCRTb"
#define BLYNK_TEMPLATE_NAME "Task4.2D Light Control"
#define BLYNK_AUTH_TOKEN "tdIvMzJtIK5HbifulBekjyAmGBB8jYjp"

#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>

// Your phone hotspot details
char ssid[] = "Student";
char pass[] = "CUPunjab";

// LED pins
// Red LED = Living Room
const int livingRoomRedLED = 5;

// Green LED = Bathroom
const int bathroomGreenLED = 3;

// Yellow LED = Closet
const int closetYellowLED = 4;


// This function toggles the LED for the room received
void toggleRoom(String room)
{
  if (room == "living room")
  {
    digitalWrite(livingRoomRedLED, !digitalRead(livingRoomRedLED));
  }
  else if (room == "bathroom")
  {
    digitalWrite(bathroomGreenLED, !digitalRead(bathroomGreenLED));
  }
  else if (room == "closet")
  {
    digitalWrite(closetYellowLED, !digitalRead(closetYellowLED));
  }
}


// Living Room - Red LED - V0
BLYNK_WRITE(V0)
{
  toggleRoom("living room");
}


// Bathroom - Green LED - V1
BLYNK_WRITE(V1)
{
  toggleRoom("bathroom");
}


// Closet - Yellow LED - V2
BLYNK_WRITE(V2)
{
  toggleRoom("closet");
}



void setup()
{
  Serial.begin(9600);

  // Set LED pins as outputs
  pinMode(livingRoomRedLED, OUTPUT);
  pinMode(bathroomGreenLED, OUTPUT);
  pinMode(closetYellowLED, OUTPUT);

  // Start with all LEDs OFF
  digitalWrite(livingRoomRedLED, LOW);
  digitalWrite(bathroomGreenLED, LOW);
  digitalWrite(closetYellowLED, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}


void loop()
{
  Blynk.run();
}