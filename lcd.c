#include <xc.h> 

#define _XTAL_FREQ 20000000
#define limpiar_lcd 0x01
#define puertoSalidaLCD LATD

#define RS LATCbits.RC0
#define EN LATCbits.RC1

#define NIVEL_ALTO 1
#define NIVEL_BAJO 0

int variableDeCuenta2 = 0;

void comando (void);
void caracter (void);
void enable (void);
void inicioDePuertos(void);
void tiempo (void);
void inicializar_lcd(void);
void funciones_de_salto(int linea, int pos);
void limpiarLCD (void);

void main (void){
INICIO:
    int mensaje_muestra[4] = {'R', 'O', 'G', 'L', 'A'};
    int mensaje_muestra_linea_2[9] = {'C', 'O', 'N', ' ', 'H','U','E','V','O'};
    int mensaje_final[6] = {'B', 'Y', 'E',' ',':',')'};
    int variableDeCuenta = 0;
    inicializar_lcd();
    funciones_de_salto(1, 5); //Estamos en la primera linea
MUESTREO:
    caracter();
    for (variableDeCuenta2 = 0 ; variableDeCuenta2 < 5 , variableDeCuenta2 ++){
        puertoSalidaLCD = mensaje_muestra[variableDeCuenta];
        enable();
    }
CAMBIAR_POS:
    funciones_de_salto(2, 3); // Cambiamos a la segunda linea
SEGUNDO_MENSAJE:
    caracter();
    for (variableDeCuenta2 = 0 ; variableDeCuenta2 < 9 ; variableDeCuenta2 ++){
        puertoSalidaLCD = mensaje_muestra_linea_2[variableDeCuenta];
        enable();
    }
    tiempo();
BORRADO: 
    comando();
    puertoSalidaLCD = 0x01;
    enable();
ULTIMO_MENSAJE:
    limpiarLCD();
    caracter();
    limpiar
    for (variableDeCuenta2 = 0 ; variableDeCuenta2 < 6 ; variableDeCuenta2 ++){
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
    TRISB = limpiar_lcd;
    TRISCbits.RC0 = NIVEL_BAJO; //RS salida 
    TRISCbits.RC1 = NIVEL_BAJO; //ENABLE salida 
}

void comando (void){
    RS = NIVEL_BAJO; // RS = 0
    __delay_ms(3);
}

void caracter (void){
    RS = NIVEL_ALTO; //RS = 1
    __delay_ms(3);
}

void enable (void){
    EN = NIVEL_ALTO; // Enable = 1
    __delay_ms(3);
    EN = NIVEL_BAJO; // Enable = 0 
    __delay_ms(3); 
}

void limpiarLCD (void){
    int varProb = 0 ;
PROB: 
    puertoSalidaLCD = limpiar_lcd;
    enable();
LIMPIEZA_PROB: 
    if (varProb == 1){
        return ;
    } else {
        varProb ++;
        goto PROB;
    }
}  
