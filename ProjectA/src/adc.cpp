#include "adc.h"
#include <time.h>
#define BASE 777 //defines base for the chip of the analog pins
#define VREF 3.3 //reference voltage
#define VZERO 0.5 //reference temperature voltage
#define TC 0.01 //temp -Coefficient
using namespace std;

int adcCh;
int firstAlarm = 1;
int reads [3];
bool alarmErr = false;
bool startStop = false; // false = stop, true = start
long lastInterruptTime = 0;
long lastAlarm = 0;

void start_stop_isr(void){
    //Start stop monitoring
    long interruptTime = millis();

    if(interruptTime-lastInterruptTime>200){
	if(!startStop){
	    printf("Stopped\n");
	}
	else{
	    printf("Starting\n");
	}
	alarmErr = false; //invert the state of playing
    }
    lastInterruptTime = interruptTime;
}

void setup_gpio(void){
    //Set up wiring Pi
    printf("Setting Up\n");
    if(wiringPiSetup()==-1){
	printf("Error setting up\n");
    }
    printf("Setting Button\n");
    mcp3004Setup(BASE, SPI_CHAN);
    pinMode(26,OUTPUT);//LED test
    pinMode(START_STOP_BTN,INPUT);
    pullUpDnControl(START_STOP_BTN,PUD_UP);
    wiringPiISR(START_STOP_BTN,INT_EDGE_FALLING,start_stop_isr);
    printf("Set up success\n");
}

double Vout(void){
    /*Alarm detection variable*/
    long timeNow = millis();
    double vout =1;
    vout =  (reads[1]/1023.0)*voltageConvert(0);
    if(vout<0.65 || vout>2.65){
	if(firstAlarm){
	    alarmErr = true;
	    lastAlarm = timeNow;
	    firstAlarm = 0;
	}
	else if (timeNow-lastAlarm>180000){
	    alarmErr = true; //alarm sound
	    lastAlarm = timeNow;
	}
    }
	/*else{
	    alarmErr = false;
	}
    }
    else{
	alarmErr = false; //operating stage is fine
    }*/
    //lastAlarm = timeNow;
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
	//while(startStop){
	for(adcCh=0; adcCh<3;adcCh++){
	    reads[adcCh] = analogRead(BASE+adcCh);
	}
	printf("Pot: %3.2f V\t Light sen: %d \t Temp: %3.2f *C \t Vout: %3.2f\n", voltageConvert(0),reads[1],tempConvert(2),Vout());
	if(alarmErr){
	    digitalWrite(26,1);
	}
	else{
	    digitalWrite(26,0);
	}
	for(int i = 0; i<10000000;i++);
//	}
    }
    //pthread_exit(NULL);
    return 0;
}
