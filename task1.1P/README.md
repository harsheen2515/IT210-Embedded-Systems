Task 1.1P - Switching ON Lights
Project Description
In this project, it is desired to turn on the porch and hall lights with pressing a button. Green LED symbolizes the porch light and the yellow LED symbolizes the hall light.
Pressing the button turns both lights on. Porch light remains on for 30 seconds whereas the hall light remains on for 60 seconds.

Hardware Used
1)Arduino Nano 33 IoT
2)Push button
4)Green LED
5)Yellow LED
6)Resistors
7)Breadboard
8)Jumper wires

Pin Connections
1)Push button: D4
2)Porch light (green LED): D2
3)Hallway light (yellow LED): D3

How the Program Works:
The button is configured as an input using INPUT_PULLUP, while the two LEDs are configured as outputs.
When the button is pressed and no lighting sequence is currently running, the turnLightsOn() function is called. This turns on both LEDs and records the starting time using millis().
The checkLights() function checks how much time has passed. After 30 seconds, the porch light is turned off. After 60 seconds, the hallway light is turned off and the lighting sequence ends.
The loop() function continuously checks the button and manages the lighting sequence while it is running.

Functions Used
setup():Sets the button as an input and the two LED pins as outputs.

turnLightsOn():Turns both LEDs on, records the starting time and indicates that the lighting sequence is running.

checkLights():Checks the elapsed time and turns the porch light off after 30 seconds and the hallway light off after 60 seconds.

loop():Checks whether the button has been pressed and starts the lighting sequence when appropriate. It also calls checkLights() while the sequence is running.

turnLightsOn():While the lighting sequence is running, loop() calls checkLights() so that the program can monitor the timing of both lights.

Modular Programming
The program is made up of parts that do different things. The turnLightsOn function is in charge of turning the lights on. The checkLights function is, in charge of the timing and turning the lights off.Breaking down the program into these parts makes it a lot easier to figure out and make changes to. For instance if you want to change when the lights come on you can do that in the checkLights function without having to mess with the part of the program that handles the buttons. This makes the program simpler to work with.
