/*
 * Prac4.cpp
 *
 * Written for EEE3096S 2019 by Keegan Crankshaw
 * 
 * This file is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef PRAC4_H
#define PRAC4_H

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

//Define buttons I used WiPi
#define PLAY_BUTTON 21 // Write your value here
#define STOP_BUTTON 22 // Write your value here
#define BUFFER_SIZE 1000

//SPI Settings
#define SPI_CHAN 0 // Write your value here
#define SPI_SPEED 450000  //305000//409600  // 256000//  //NOT SURE ABOUT THIS // Write your value here

//Filename
#define FILENAME "src/sound_16k_8bit.raw"

//Function definitions
void play_audio(void);
void stop_audio(void);
void stop_isr(void);
void play_pause_isr(void);
int setup_gpio(void);
int main(void);


#endif
