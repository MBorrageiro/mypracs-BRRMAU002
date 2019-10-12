/*ADC testing in C*/

#include "adc.h"
#define BASE 777 //defines base for the chip of the analog pins
#define VREF 3.3 //reference voltage
#define VZERO 0.5 //reference temperature voltage
#define TC 0.01 //temp -Coefficient
using namespace std;

int adcCh;
//unsigned int Pot=0;
//int mcp_answer;
int reads [3];

void setup_gpio(void){
    //Set up wiring Pi
    printf("Setting Up\n");
    if(wiringPiSetup()==-1){
	printf("Error setting up");
    }
    mcp3004Setup(BASE, SPI_CHAN);
    printf("Set up success");
}
double tempConvert(int channel){
    double Vout = voltageConversion(channel);
    return (Vout-VZERO)/TC;
}

double voltageConversion(int channel){
    //Voltage conversion function
    return (VREF*reads[channel])/1024;
}

int main(){
    setup_gpio();
    printf("Reading values");
    while(1){
	for(adcCh=0; adcCh<3;adcCh++){
	   // int port = BASE + adcCh;
	    reads[adcCh] = analogRead(BASE+adcCh);
	    //read[adcCh] = pot;
	}
	//Pot = reads[0];
	printf("Pot: %3.2f V\t Light sen: %d \t Temp: %3.2f *C\n", voltageConversion(0),reads[1],tempConvert(2));
	for(int i = 0; i<10000000;i++);//voltageConversion(2));
    }

}
