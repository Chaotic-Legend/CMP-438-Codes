# CMP 438: Communicating Robots - Isaac D. Hoyos
# Lab 1 - Raspberry Pi Pico: https://wokwi.com/projects/450077101174254593

import time
from machine import Pin

# This statement initializes the LED on pin 13 as an output.
led = Pin(13, Pin.OUT)

# This statement initializes the push button on pin 18 as a pull-up input.
pushbutton = Pin(18, Pin.IN, Pin.PULL_UP)

# This statement defines a short delay for debouncing.
debounce_delay = 0.05

# This variable stores the previous button state.
previous_state = 1

while True:
    # This statement reads the current state of the push button.
    button_state = pushbutton.value()

    # This statement turns the LED on when the button is pressed.
    if button_state == 0:
        led.on()
    else:
        led.off()

    # This statement prints only when the button state changes.
    if button_state != previous_state:
        if button_state == 0:
            print("PushButton Pressed.\n")
        else:
            print("PushButton Unpressed.\n")
        previous_state = button_state

    # This delay stabilizes readings and prevents unnecessary CPU usage.
    time.sleep(debounce_delay)
