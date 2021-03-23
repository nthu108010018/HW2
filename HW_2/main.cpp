#include "mbed.h"

#include "uLCD_4DGL.h"


uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
BusIn selections(D13, D12, D11);
DigitalOut out(D10);
AnalogOut Aout(PA_4);
AnalogIn Ain(A0);
void wave_tri(AnalogOut &aout, AnalogIn &ain, int freq, float adcData[], int sample, int steps);
/*void menu(char **options, int i){
    uLCD.cls();
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
}*/
float ADCdata[128];

int main(){
    
    uLCD.printf("\nHello uLCD World\n");
    

    uLCD.printf("\n  Starting Demo...");
    uLCD.cls();
    const char *options[3] = { "frequency_1", "frequency_2", 
                             "frequency_3" };
    for(int i = 0; i<3; i++){
        if(i==0){
            uLCD.color(RED);
            uLCD.printf(options[i]);
            uLCD.printf("\n");
            uLCD.color(GREEN);
        }
        else{
            uLCD.printf(options[i]);
            uLCD.printf("\n");
        }
    }
    int i = 0;
    //menu(options, i);
    while(1){
        
        out = 1;
        int flag = 0;
        switch(selections){
            case 0x4 : // down
              if(i >= 2){
                  uLCD.printf("Invalid Input1\n");
              } 
              else{
                  i++;
                  uLCD.cls();
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
              ThisThread::sleep_for(10ms);
              break;
            case 0x2 : flag =1 ;break;

            case 0x1 : // up
              if(i <= 0){
                  uLCD.printf("Invalid Input2\n");
                  i = 0;
              } 
              else{
                  i--;
                  uLCD.cls();
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
              ThisThread::sleep_for(10ms);
              break;
        }
       
        if(flag ==1){
            uLCD.cls();
            uLCD.printf(options[i]);
            if(i == 0){
                wave_tri(Aout, Ain, 500, ADCdata, 128, 200);//1333.33Hz
            }
            else if(i == 1){
                wave_tri(Aout, Ain, 500, ADCdata, 128, 100);//697Hz
            }
            else if(i == 2){
                wave_tri(Aout, Ain, 500, ADCdata, 128, 150);
            }
            
            break;
        }
        
    }
    

}   