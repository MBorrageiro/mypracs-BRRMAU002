#ifndef BINCLOCK_H
#define BINCLOCK_H

//Some reading (if you want)
//https://stackoverflow.com/questions/1674032/static-const-vs-define-vs-enum

// Function definitions
int hFormat(int hours);
void lightHours(void);
void lightMins(void);
int hexCompensation(int units);
int decCompensation(int units);
void initGPIO(void);
void cleanUpFunction(void);
void secPWM(int units);
void hourInc(void);
void minInc(void);
void toggleTime(void);
void myInterrupt(void); //interrupt for buttons

// define constants
const char RTCAddr = 0x6f;
const char SEC = 0x00; // see register table in datasheet
const char MIN = 0x01;
const char HOUR = 0x02;
const char TIMEZONE = 2; // +02H00 (RSA)
//const int mult = 10;

// define pins
const int LEDS[] = {7,0,2,3,12,13,14,21,22,23}; //H0-H4, M0-M5
const int SECS = 1;
const int BTNS[] = {15,16}; // B0, B1


#endif
