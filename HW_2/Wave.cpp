#include "mbed.h"

void wave_tri(AnalogOut &aout, AnalogIn &ain, int freq, float adcData[], int sample){

    int k = 0;
    //float ADCdata[65535];
    while(1){
        int i =0;
        while(i<58982){
            aout.write_u16(i);
             i = i+1;
        }
        while(i>0){
            aout.write_u16(i);
            i = i-9;
        }
    }
   
}