#include "adc.h"
#define BASE 777 //defines base for the chip of the analog pins
#define VREF 3.3 //reference voltage
#define VZERO 0.5 //reference temperature voltage
#define TC 0.01 //temp -Coefficient
using namespace std;

int adcCh;
int reads [3];
bool alarmErr = false;

void setup_gpio(void){
    //Set up wiring Pi
    printf("Setting Up\n");
    if(wiringPiSetup()==-1){
	printf("Error setting up");
    }
    mcp3004Setup(BASE, SPI_CHAN);
    printf("Set up success");
}

double Vout(void){
    /*Alarm detection variable*/
    double vout =1;
    vout =  (reads[1]/1023.0)*voltageConvert(0);
    if(vout<0.65 || vout>2.65){
	alarmErr = true; //alarm sound
    }
    else{
	alarmErr = false; //operating stage is fine
    }
    return vout;
}

double tempConvert(int channel){
    double Vadc = voltageConvert(channel);
    return (Vadc-VZERO)/TC;
}

double voltageConvert(int channel){
    //Voltage conversion function
    return (VREF*reads[channel])/1024;
}

/*void *readAdcThread(void *threadarg){
     printf("Testing if these run sim\n");
     while(printDone){
	for(adcCh=0; adcCh<3;adcCh++){
	    // int port = BASE + adcCh;
	    reads[adcCh] = analogRead(BASE+adcCh);
	    //read[adcCh] = pot;
	    printf("%d",read[adcCh]);
	}
	printDone = !printDone;
    }
    pthread_exit(NULL);
}*/

int main(){
    setup_gpio();
	///Thread///
    /*pthread_attr_t tattr;
    pthread_t thread_id;
    int newprio = 99;
    pthread_attr_init (&tattr);
    sched_param param;
    pthread_attr_getschedparam (&tattr, &param);
    param.sched_priority = newprio; // set the priority; others are unchanged
    pthread_attr_setschedparam (&tattr, &param); //setting the new scheduling param
    pthread_create(&thread_id, &tattr, readAdcThread, (void *)1); // with new priority specified
    pthread_join(thread_id, NULL);
    printf("Reading values");*/
    while(1){
	for(adcCh=0; adcCh<3;adcCh++){
	    reads[adcCh] = analogRead(BASE+adcCh);
	}
	printf("Pot: %3.2f V\t Light sen: %d \t Temp: %3.2f *C \t Vout: %3.2f\n", voltageConvert(0),reads[1],tempConvert(2),Vout());
	for(int i = 0; i<10000000;i++);
    }
    //pthread_exit(NULL);
    return 0;
}
