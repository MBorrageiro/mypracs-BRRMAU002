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
GPIO.setmode(GPIO.BOARD)
GPIO.setup(7, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(13, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(15, GPIO.OUT, initial=GPIO.LOW)
# Increase btn
increase_btn = 11
GPIO.setup(increase_btn, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.add_event_detect(increase_btn,GPIO.FALLING,bouncetime=300)
# Decrease btn
decrease_btn = 12
GPIO.setup(decrease_btn, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.add_event_detect(decrease_btn,GPIO.FALLING,bouncetime=300)
# Global counter
counter = 0
bi = itertools.product(range(2), repeat = 3) # product function used to create  an array of binary numbers
bi = list(bi) # result of product function iterable array

# Logic that you write
def main():
    global counter
    global bi
    global increase_btn
    global decrease_btn
    if GPIO.event_detected(increase_btn):
        if counter == 7:
            counter = 0
        else:
            counter = counter +1
        GPIO.output(15,bi[counter][0])
        GPIO.output(13,bi[counter][1])
        GPIO.output(7,bi[counter][2])

    if GPIO.event_detected(decrease_btn):
        if counter == 0:
            counter = 7
        else:
            counter = counter -1
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
