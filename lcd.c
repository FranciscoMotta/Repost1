#include <xc.h> 

#define _XTAL_FREQ 20000000UL 
#define limpiar_lcd 0x01
#define puertoSalidaLCD LATB
void comando (void);
void caracter (void);
void enable (void);
void inicioDePuertos(void);

void main (void){
    inicioDePuertos();
    int matriz_de_conf[4]= {limpiar_lcd, 0x38, 0x0C, 0x06};
    int mensaje_muestra[4] = {'P', 'O', 'G', 'L', 'A'};
    int mensaje_muestra_linea_2[9] = {'S', 'I', 'N', ' ', 'H','U','E','V','O'};
    int variableDeCuenta = 0;
CONFIG: 
    comando();
    for(variableDeCuenta = 0 ; variableDeCuenta < 4 ; variableDeCuenta ++){
       puertoSalidaLCD = matriz_de_conf[variableDeCuenta];
       enable();
    }
    puertoSalidaLCD = 0x85;
    enable();
MUESTREO:
    caracter();
    for (variableDeCuenta = 0 ; variableDeCuenta < 5 , variableDeCuenta ++){
        puertoSalidaLCD = mensaje_muestra[variableDeCuenta];
        enable();
    }
CAMBIAR_POS:
    comando();
    puertoSalidaLCD = 0xC3;
    enable();
SEGUNDO_MENSAJE:
    caracter();
    for (variableDeCuenta = 0 ; variableDeCuenta < 9 ; variableDeCuenta ++){
        puertoSalidaLCD = mensaje_muestra_linea_2[variableDeCuenta];
        enable();
    }
    while (1);
    return;
}

void inicioDePuertos (void) {
    TRISB = 0x00;
    TRISCbits.RC0 = 0; //RS salida 
    TRISCbits.RC1 = 0; //ENABLE salida 
}

void comando (void){
    PORTCbits.RC0 = 0 ; // RS = 0
    __delay_ms(5);
}

void caracter (void){
    PORTCbits.RC0 = 1; //RS = 1
    __delay_ms(5);
}

void enable (void){
    PORTCbits.RC1 = 1; // Enable = 1
    __delay_ms(3);
    PORTCbits.RC1 = 0; // Enable = 0 
    __delay_ms(2); 
}