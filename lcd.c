#include <xc.h> 

#define _XTAL_FREQ 20000000UL 
#define limpiar_lcd 0x01
#define puertoSalidaLCD LATB

void comando (void);
void caracter (void);
void enable (void);
void inicioDePuertos(void);
void tiempo (void);
void inicializar_lcd(void);
void funciones_de_salto(int linea, int pos);

void main (void){
    int mensaje_muestra[4] = {'P', 'O', 'G', 'L', 'A'};
    int mensaje_muestra_linea_2[9] = {'S', 'I', 'N', ' ', 'H','U','E','V','O'};
    int mensaje_final[6] = {'B', 'Y', 'E',' ',':',')'};
    int variableDeCuenta = 0;
    inicializar_lcd();
    funciones_de_salto(1, 4); //Estamos en la primera linea
MUESTREO:
    caracter();
    for (variableDeCuenta = 0 ; variableDeCuenta < 5 , variableDeCuenta ++){
        puertoSalidaLCD = mensaje_muestra[variableDeCuenta];
        enable();
    }
CAMBIAR_POS:
    funciones_de_salto(2, 3); // Cambiamos a la segunda linea
SEGUNDO_MENSAJE:
    caracter();
    for (variableDeCuenta = 0 ; variableDeCuenta < 9 ; variableDeCuenta ++){
        puertoSalidaLCD = mensaje_muestra_linea_2[variableDeCuenta];
        enable();
    }
    tiempo();
BORRADO: 
    comando();
    puertoSalidaLCD = 0x01;
    enable();
ULTIMO_MENSAJE:
    for (variableDeCuenta = 0 ; variableDeCuenta < 6 ; variableDeCuenta ++){
        puertoSalidaLCD = mensaje_final[variableDeCuenta];
        enable();
    }
    while (1);
    return;
}
void inicializar_lcd (void){
    inicioDePuertos();
    int matriz_de_conf[4]= {limpiar_lcd, 0x38, 0x0C, 0x06};
    CONFIG: 
    comando();
    for(variableDeCuenta = 0 ; variableDeCuenta < 4 ; variableDeCuenta ++){
       puertoSalidaLCD = matriz_de_conf[variableDeCuenta];
       enable();
    }
    puertoSalidaLCD = 0x85;
    enable();
}

void funciones_de_salto (int linea, int pos){
    /*
    Esta funcion busca modificar la posición del cursor de 
    lcd para poder ir a donde queramos
    */
    char dataLine = 0x00;
    comando();
    switch (linea){
        case 1: 
        dataLine = 0x80; 
        break;
        case 2:
        dataLine = 0xC0;
        break;
        default:
        dataLine = 0x80;
        break;
    }
    puertoSalidaLCD = dataLine + pos;
    enable();
}

void tiempo (void){
    for (variableDeCuenta = 0 ; variableDeCuenta < 100 ; variableDeCuenta ++ ){
        __delay_ms(10);
    }
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