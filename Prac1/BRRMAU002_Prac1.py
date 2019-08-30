#!/usr/bin/python3
"""
Python Practical Template
Keegan Crankshaw
Readjust this Docstring as follows:
Names: Mauro Borrageiro
Student Number: BRRMAU002
Prac: 1
Date: 26/07/2019
"""

# import Relevant Librares
import RPi.GPIO as GPIO
import itertools

# GPIO initialization
# Following pins set as outputs for LEDS in counter
GPIO.setmode(GPIO.BOARD) # Setting the pin numbering system to physical board numbering
GPIO.setup(7, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(13, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(15, GPIO.OUT, initial=GPIO.LOW)

# Increase btn
increase_btn = 11 # pin number for increase button
GPIO.setup(increase_btn, GPIO.IN, pull_up_down=GPIO.PUD_UP) # increase pin set to input with a pull up resistor
GPIO.add_event_detect(increase_btn,GPIO.FALLING,bouncetime=300) # increase pin responds on a falling edge interrupt with 300ms button bounce delay

# Decrease btn, same setup as increase button just for decrease.
decrease_btn = 12
GPIO.setup(decrease_btn, GPIO.IN, pull_up_down=GPIO.PUD_UP) 
GPIO.add_event_detect(decrease_btn,GPIO.FALLING,bouncetime=300)

# Global counter
counter = 0
biCombos = itertools.product(range(2), repeat = 3) # product function used to create unique combinations of binary numbers from 0(000) to 7(111)
bi = list(biCombos) # result of biCombos is changed into an iterable list

# Logic that you write
def main():
    # Global variable delceration
    global counter
    global bi
    global increase_btn
    global decrease_btn
    
    # Increase btn Logic
    if GPIO.event_detected(increase_btn):
        if counter == 7: # check to restart counting
            counter = 0
        else:
            counter = counter +1 # ascending counting
        # displaying corresponding bits of the current count on the respective LEDs
        GPIO.output(15,bi[counter][0])
        GPIO.output(13,bi[counter][1])
        GPIO.output(7,bi[counter][2])
        
    # Decrease btn logic
    if GPIO.event_detected(decrease_btn):
        if counter == 0: # check to start count back at maximum
            counter = 7
        else:
            counter = counter -1 # descending counting
        # displaying corresponding bits of the current count on the respective LEDs
        GPIO.output(15,bi[counter][0])
        GPIO.output(13,bi[counter][1])
        GPIO.output(7,bi[counter][2])

###
if __name__ == "__main__":
    # Make sure the GPIO is stopped correctly
    try:
        while True:
            main()
    except KeyboardInterrupt:
        print("Exiting gracefully")
        # Turn off your GPIOs here
        GPIO.cleanup()
    except Exception as e:
        GPIO.cleanup()
        print("Some other error occurred")
        print(e.message)
