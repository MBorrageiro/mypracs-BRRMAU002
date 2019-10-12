#!/usr/bin/python3
"""
Python Practical Template
Keegan Crankshaw
Readjust this Docstring as follows:
Names: <names>
Student Number: <studnum>
Prac: <Prac Num>
Date: <dd/mm/yyyy>
"""

# import Relevant Librares
import RPi.GPIO as GPIO
import spidev
import time

# SpiDev Initialization
spi = spidev.SpiDev(0,0)
#spi_ch = 0
#spi.open(0,spi_ch)
spi.max_speed_hz = 1350000

#GPIO #start bit, SGL, D2 D1 D0

# Logic that you write
def adc():
    reply = spi.xfer2(ch1)
    reading = int(reply,2)
    voltage = (3.3*reading)/1024
    #adc = spiFunc()
    print("Voltage reading: ", round(adc,2))
    time.sleep(0.2)

def main():
   # ch1 = [0b11001000, 0b0] #bits 6,9
    #write = spi.writebytes(ch1)
   # print("ch1: ",ch1) #" Rw: ",write)
    adc = spi.xfer2([1,(8+1)<<4,0])
    #read = spi.readbytes(2)
    adc1 = ((adc[1]&3)<<8)+adc[2]
   # for n in reply:
	#adc = (adc<<8)+n
    #adc = adc >> 1
    print("Voltage: ", adc1, "Read: ",adc)
    time.sleep(0.5)


# Only run the functions if 
if __name__ == "__main__":
    # Make sure the GPIO is stopped correctly
    try:
        while True:
            main()
    except KeyboardInterrupt:
        print("Exiting gracefully")
        # Turn off your GPIOs here
	spi.close()
        GPIO.cleanup()
    except Exception as e:
        print("Some other error occurred")
        print(e.message)
	GPIO.cleanup()
