
#include <xc.h> 

#define _XTAL_FREQ 4000000UL
/*
Cambiamos la frecuencia del oscilador para ver la variación 
de los ciclos de instrucción
*/
#define puertoDeLeds LATB 
#define trisDePuertoDeLeds TRISB 
#define puertoDeLeds2 LATD
#define trisDePuertoDeLeds2 TRISD 

void inicioPuertos (void);
int variableDeCuenta = 0;

void main (void){
    inicioPuertos();
CUENTA:
    for (variableDeCuenta = 0 ; variableDeCuenta < 255 ; variableDeCuenta ++){
        puertoDeLeds = variableDeCuenta;
        puertoDeLeds2 = ~variableDeCuenta;
        __delay_ms(100);
    }
CUENTA2:
    for (variableDeCuenta = 255 ; variableDeCuenta >= 0 ; variableDeCuenta --){
        puertoDeLeds = ~variableDeCuenta;
        puertoDeLeds = variableDeCuenta;
        __delay_ms(100);
    }
    goto CUENTA;
}

void inicioPuertos (void){
    trisDePuertoDeLeds = 0x00;
    trisDePuertoDeLeds2 = 0x00;
}