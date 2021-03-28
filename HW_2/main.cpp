#include "mbed.h"

#include "uLCD_4DGL.h"

using namespace std::chrono;

EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread thread;


uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
BusIn selections(D13, D12, D11);
DigitalOut out(D10);
AnalogOut Aout(PA_4);
AnalogIn Ain(A0);

void sampling(int rate);
void wave_gen(AnalogOut &aout, AnalogIn &ain, float adcData[], int steps);
void menu(int i);

float ADCdata[10000] = {0};

int main(){
    uLCD.printf("\nHello uLCD World\n");
    uLCD.printf("\n  Starting Demo...");
    uLCD.cls();
    int i = 0;
    out = 1;
    menu(i);
    int flag = 0;
    while(1){
        switch(selections){
            case 0x4 : // down
              if(i >= 2){
                  i=0;
                  uLCD.cls();
                  menu(i);
              } 
              else{
                  i++;
                  uLCD.cls();
                  menu(i);
              }
              ThisThread::sleep_for(10ms);
              break;
            case 0x2 : flag =1 ;break;
            case 0x1 : // up
              if(i <= 0){
                  i = 2;
                  uLCD.cls();
                  menu(i);
              } 
              else{
                  i--;
                  uLCD.cls();
                  menu(i);
              }
              ThisThread::sleep_for(10ms);
              break;
        }
        if(flag ==1){
            queue.call(&sampling, 820);
            Thread eventThread(osPriorityNormal);
            eventThread.start(callback(&queue,&EventQueue::dispatch_forever));
            
            if(i == 0){
                wave_gen(Aout, Ain, ADCdata,  100); // 135Hz
            }
            else if(i == 1){
                wave_gen(Aout, Ain,  ADCdata, 200);//  270Hz
            }
            else if(i == 2){
                wave_gen(Aout, Ain,  ADCdata, 300);//  410Hz
            }
        }
    }
}
    


void menu(int i){
    const char *options[3] = { "135Hz", "270Hz", 
                             "410Hz" };
    for(int j = 0; j<3; j++){
        if(i == j){
            uLCD.color(RED);
            uLCD.printf(options[j]);
            uLCD.printf("\n");
            uLCD.color(GREEN);
        }
        else{
            uLCD.printf(options[j]);
            uLCD.printf("\n");
        }
    }
}

void wave_gen(AnalogOut &aout, AnalogIn &ain, float adcData[],  int steps){
    
    
    while(1){
        int i =0;
        while(i<90){
            aout = 0.01*i;
            i = i+0.01*steps;
            wait_us(50);
        }
        while(i>0){
            aout = 0.01*i;
            i = i-0.09*steps;
            wait_us(50);
        }
    }
   
}


void sampling(int rate){
    while(1){
        for(int i=0; i<1000; i++){
            ADCdata[i] = Ain*3.3;
            ThisThread::sleep_for(1000ms/rate);
        }
        for(int i=0; i<1000;i++){
            printf("%f\r\n", ADCdata[i]);
        }
        ThisThread::sleep_for(rate*10ms);
    }
}