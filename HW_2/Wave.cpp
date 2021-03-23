#include "mbed.h"

void wave_tri(AnalogOut &aout, AnalogIn &ain, int freq, float adcData[], int sample, int steps){

    int k = 0;
    while(1){
        int i =0;
        while(i<90){
            aout = 0.01*i;
            i = i+0.01*steps;
            
        }
        while(i>0){
            aout = 0.01*i;
            i = i-0.09*steps;
        }
    }
   
}