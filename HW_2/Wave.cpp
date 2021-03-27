#include "mbed.h"

void wave_tri(AnalogOut &aout, AnalogIn &ain, float adcData[], int sample, int steps){

    
    

    while(1){
        int i =0;
        int n = 0;
        while(i<90){
            aout = 0.01*i;
            i = i+0.001*steps;
            adcData[n]= ain*3.3;
            printf("%f\r\n", adcData[n]);
            n = n + 1;
        }
        while(i>0){
            aout = 0.01*i;
            i = i-0.009*steps;
            adcData[n] = ain*3.3;
            printf("%f\r\n", adcData[n]);
            n = n + 1;
        }
        
        

    }
   
}