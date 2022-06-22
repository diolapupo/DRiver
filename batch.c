// config  
#include <xc.h>
#pragma config FOSC = HS        
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF      
#pragma config BOREN = OFF     
#pragma config LVP = OFF        
#pragma config CPD = OFF        
#pragma config WRT = OFF         
#pragma config CP = OFF   

#define _XTAL_FREQ 20000000

 void startPWM1(float freq, int duty){
        CCP1CON = 0x0F;
        float periodt = 1/freq;
        PR2 = (periodt * _XTAL_FREQ) / 16 - 1;
        CCPR1L = duty;
        TMR2ON = 1;
    }
 void startPWM2(float freq, int duty){
        CCP2CON = 0x0F;
        float periodt = 1/freq;
        PR2 = (periodt * _XTAL_FREQ) / 16 - 1;
        CCPR2L = duty;
        TMR2ON = 1;
    }

void main(void) {
    TRISC1 = 0;
    TRISC2 = 0;
 
    while(1){
        startPWM1(5000, 90);
        startPWM2(1000, 30);
    }
    
    return;
}
