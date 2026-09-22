import tkinter as tk
import RPi.GPIO as GPIO

# Use BCM GPIO numbering
GPIO.setmode(GPIO.BCM)

# GPIO pins
living_room = 13
bathroom = 6
closet = 5

# Set pins as outputs
GPIO.setup(living_room, GPIO.OUT)
GPIO.setup(bathroom, GPIO.OUT)
GPIO.setup(closet, GPIO.OUT)

# PWM for Living Room LED
pwm = GPIO.PWM(living_room, 100)
pwm.start(0)


# Control the selected room
def control_led():

    # Turn OFF Bathroom and Closet
    GPIO.output(bathroom, GPIO.LOW)
    GPIO.output(closet, GPIO.LOW)

    # Living Room selected
    if led.get() == 1:
        pwm.ChangeDutyCycle(slider.get())

    # Bathroom selected
    elif led.get() == 2:
        pwm.ChangeDutyCycle(0)
        GPIO.output(bathroom, GPIO.HIGH)

    # Closet selected
    elif led.get() == 3:
        pwm.ChangeDutyCycle(0)
        GPIO.output(closet, GPIO.HIGH)


# Change Living Room brightness
def change_intensity(value):

    if led.get() == 1:
        pwm.ChangeDutyCycle(float(value))


# Exit program safely
def exit_program():

    pwm.stop()
    GPIO.cleanup()
    root.destroy()


# Create GUI
root = tk.Tk()
root.title("Room Light Control")

# Variable for radio buttons
led = tk.IntVar()

# Living Room radio button
tk.Radiobutton(
    root,
    text="Living Room",
    variable=led,
    value=1,
    command=control_led
).pack()

# Living Room intensity slider
slider = tk.Scale(
    root,
    from_=0,
    to=100,
    orient=tk.HORIZONTAL,
    label="Living Room Intensity",
    command=change_intensity
)
slider.set(50)
slider.pack()

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

# Keep GUI running
root.mainloop()  give me read me file for this
