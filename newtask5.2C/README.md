# Task 5.2C - Change the Light Intensity Using GUI

## Overview

This task uses a Raspberry Pi and a Tkinter graphical user interface (GUI) to control three LEDs representing the Living Room, Bathroom, and Closet.

The Living Room LED uses PWM (Pulse Width Modulation) so its brightness can be changed using a slider from 0% to 100%. The Bathroom and Closet LEDs are controlled using radio buttons.

## Hardware Used

- Raspberry Pi
- 3 LEDs
- 3 current-limiting resistors
- Breadboard
- Jumper wires

## GPIO Connections

| Room | GPIO Pin | Control |
|---|---|---|
| Living Room | GPIO 13 | PWM brightness control |
| Bathroom | GPIO 6 | ON/OFF |
| Closet | GPIO 5 | ON/OFF |

The program uses BCM GPIO numbering.

## Software Used

- Python
- Tkinter
- RPi.GPIO

## GUI Features

- Living Room radio button
- Living Room Intensity slider (0-100%)
- Bathroom radio button
- Closet radio button
- Exit button

## Program Operation

When the program starts, the GPIO pins are configured as outputs and PWM is started on GPIO 13 for the Living Room LED.

When Living Room is selected, the intensity slider changes the PWM duty cycle and controls the LED brightness.

When Bathroom is selected, the Living Room PWM is set to 0 and the Bathroom LED is turned ON.

When Closet is selected, the Living Room PWM is set to 0 and the Closet LED is turned ON.

## Main Functions

### control_led()

Controls the selected room LED using the radio button selection.

### change_intensity(value)

Changes the Living Room LED brightness by changing the PWM duty cycle according to the slider value.

### exit_program()

Stops PWM, cleans up the GPIO pins, and closes the GUI safely.

## Flowchart

The program flowchart is included in this folder as a PDF file.

## Files

- `Task5.2C.py` - Python program for GUI and LED control
- `Flowchart.pdf` - Program flowchart
- `README.md` - Task description and program explanation

## Conclusion

This task demonstrates the integration of Raspberry Pi GPIO, PWM, and a Tkinter GUI to control LED brightness and room selection.
