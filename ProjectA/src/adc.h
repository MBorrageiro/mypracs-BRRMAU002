#ifndef ADC_H
#define ADC_H

//Includes
#include <wiringPi.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <iostream>
#include "mcp3004.h"

//Define buttons I used WiPi
#define PLAY_BUTTON 21 // Write your value here
#define STOP_BUTTON 22 // Write your value here

//SPI Settings
#define SPI_CHAN 0 // Write your value here
#define SPI_SPEED 1350000 // adc max clock for 3.3V

//Filename
//#define FILENAME "src/sound_16k_8bit.raw"

//Function definitions
void readAdc(int channel);
/*void play_audio(void);
void stop_audio(void);
void stop_isr(void);
void play_pause_isr(void);*/

void setup_gpio(void);
double tempConvert(int channel);
double voltageConversion(int channel);
int main(void);


#endif
