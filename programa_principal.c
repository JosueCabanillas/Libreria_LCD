#include "xc.h"
#include "Configuracion.h"
#include <libpic30.h>
#include <stdint.h>
#include <stdio.h>
#include "LCD_Libreria.h"
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void);
void I2C_Nack(void);
void I2C_Tx(char);
char I2C_Rx(void);
void I2C_Start(void);
void ADC_Init(void);
int i;
uint16_t valor_adc = 0;
float voltaje = 0.0;
char datos[10];
int main(void) {
    ADC_Init();
    I2CCONbits.I2CEN = 1; //Habilitamos el I2C
    IFS0bits.MI2CIF = 0;
    I2CBRG = 181; //FSCL = 100KHz
    while(1){
     ADCON1bits.SAMP = 1;
     __delay_ms(100);
     ADCON1bits.SAMP = 0;
     while(!ADCON1bits.DONE);
      valor_adc = ADCBUF0;
      voltaje = valor_adc*(5.0/4096);// 5/ 4096
      sprintf(datos,"Voltaje es: %0.2f V",voltaje);//2.45
      LCD_XY(0,0);
      LCD_String(datos);
    } 
}

void I2C_Start(void){
    IFS0bits.MI2CIF = 0;
    I2CCONbits.SEN = 1;
    while( IFS0bits.MI2CIF == 0);
}
void I2C_Stop(void){
    IFS0bits.MI2CIF = 0;
    I2CCONbits.PEN = 1; 
    while( IFS0bits.MI2CIF == 0);
}
void I2C_Ack(void){
    IFS0bits.MI2CIF = 0; 
    I2CCONbits.ACKEN = 1;
    I2CCONbits.ACKDT = 0;
    while( IFS0bits.MI2CIF == 0);
}
void I2C_Nack(void){
    IFS0bits.MI2CIF = 0;
    I2CCONbits.ACKEN = 1;
    I2CCONbits.ACKDT = 1;
    while( IFS0bits.MI2CIF == 0);
}
void I2C_Tx(char data1){
    IFS0bits.MI2CIF = 0;
    I2CTRN = data1;
    while( IFS0bits.MI2CIF == 0);
    
}
char I2C_Rx(void){
    IFS0bits.MI2CIF = 0;
    I2CCONbits.RCEN = 1;
    while( IFS0bits.MI2CIF == 0);
    return I2CRCV;
}
void Timer3_config(void){
    T3CONbits.TON = 1;
    T3CONbits.TSIDL = 0;
    T3CONbits.TCKPS = 0;
    IFS0bits.T3IF = 0;
    IPC1bits.T3IP = 2;
    IEC0bits.T3IE = 1;
    
}
void ADC_Init(void){
    ADPCFG = 0x1FFE; //RB0 Analog
    ADCON2bits.VCFG = 0b000; //Avss(minimo) = 0v Avdd(máximo) = +5v
    ADCHSbits.CH0SA = 0b0000; // channel 0 positive input is AN0
    ADCON3bits.ADCS = 26; //TAD = 667nS TCY = 1/20MHz
    ADCON3bits.ADRC = 0;
    ADCON3bits.SAMC = 25;
    ADCON1bits.SSRC = 0b000;
    ADCON1bits.FORM = 0b00;
    ADCON1bits.ADON = 1;
}
