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
#define BAT_CURRENT 1
#define FEEDBACK_VOLTAGE 2

float battery_current, feedback_voltage;

 void startPWM1(float freq, int duty){
        CCP1CON = 0x0F;
        float periodt = 1.0/freq;
        PR2 = (periodt * _XTAL_FREQ) / 16 - 1;
        CCPR1L = duty;
        TMR2ON = 1;
    }
 void startPWM2(float freq, int duty){
        CCP2CON = 0x0F;
        float periodt = 1.0/freq;
        PR2 = (periodt * _XTAL_FREQ) / 16 - 1;
        CCPR2L = duty;
        TMR2ON = 1;
    }
 int readADC(char ADCpin){
     CHS0 = ADCpin & 001;
     CHS1 = ADCpin & 010;
     CHS2 = ADCpin & 100;
     ADON = 1;
     __delay_us(40);
     GO_nDONE = 1;
     while(GO_nDONE);
     ADON = 0;
    int res =  ADRESL + 128* ADRESH;
    return res;
 }
void main(void) {
    TRISC1 = 0;
    TRISC2 = 0;
    ADCON1 = 0b01000010;   // FOSC/4, left justified, RA0-RA4 are analog rest are digital pins
    ADCS0 = 0;// FOSC/4
    ADCS1 = 0;// FOSC/4
    
    
    while(1){
        
        // 
        startPWM1(5000, 90);
        startPWM2(1000, 30);
        /// read ADC values
        battery_current = 0.00488 * readADC(BAT_CURRENT);
        feedback_voltage =5.55* (0.00488 * readADC(FEEDBACK_VOLTAGE));
     /*  if(feedback_voltage < 12){
        
        }else if(feedback_voltage > 12){
        
        }*/
    }
    
    return;
}
