#include "mbed.h"

void wave_tri(AnalogOut &aout){
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