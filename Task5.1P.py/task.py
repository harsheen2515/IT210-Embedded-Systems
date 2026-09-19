import tkinter as tk
import RPi.GPIO as GPIO

# Use BCM GPIO numbering
GPIO.setmode(GPIO.BCM)

# GPIO pins for each room
living_room = 5
bathroom = 6
closet = 13

# Set all three pins as outputs
GPIO.setup(living_room, GPIO.OUT)
GPIO.setup(bathroom, GPIO.OUT)
GPIO.setup(closet, GPIO.OUT)


# This function controls which room light is ON
def control_led():

    # First turn OFF all lights
    GPIO.output(living_room, GPIO.LOW)
    GPIO.output(bathroom, GPIO.LOW)
    GPIO.output(closet, GPIO.LOW)

    # Turn ON the selected room light
    if led.get() == 1:
        GPIO.output(living_room, GPIO.HIGH)

    elif led.get() == 2:
        GPIO.output(bathroom, GPIO.HIGH)

    elif led.get() == 3:
        GPIO.output(closet, GPIO.HIGH)


# Close the GUI and safely reset GPIO pins
def exit_program():
    GPIO.cleanup()
    root.destroy()


# Create the main GUI window
root = tk.Tk()
root.title("Room Light Control")

# Variable used to store the selected radio button
led = tk.IntVar()

# Living Room radio button
tk.Radiobutton(
    root,
    text="Living Room",
    variable=led,
    value=1,
    command=control_led
).pack()

# Bathroom radio button
tk.Radiobutton(
    root,
    text="Bathroom",
    variable=led,
    value=2,
    command=control_led
).pack()

# Closet radio button
tk.Radiobutton(
    root,
    text="Closet",
    variable=led,
    value=3,
    command=control_led
).pack()

# Exit button
tk.Button(
    root,
    text="Exit",
    command=exit_program
).pack()

# Keep the GUI running
root.mainloop()
