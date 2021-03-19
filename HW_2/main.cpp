#include "mbed.h"

#include "uLCD_4DGL.h"


uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
BusIn selections(D13, D12, D11);
DigitalOut out(D10);
AnalogOut Aout(PA_4);
void wave_tri(AnalogOut &aout);
int main()

{
    // basic printf demo = 16 by 18 characters on screen
    uLCD.printf("\nHello uLCD World\n"); //Default Green on black text
    

    uLCD.printf("\n  Starting Demo...");
    uLCD.cls();
    uLCD.printf("frequency_1\n");
    uLCD.printf("frequency_2\n");
    uLCD.printf("frequency_3\n");
    
    while(1){
        
        out = 1;
        int flag = 0;
        switch(selections){
            case 0x4 : printf("up\n");break;
            case 0x2 : printf("confirm\n");flag =1 ;break;
            case 0x1 : printf("down\n");break;
        }
        if(flag ==1){
            printf("fuck you\n");
            uLCD.printf("fuck you\n");
            wave_tri(Aout);
            break;
        }
    }

}