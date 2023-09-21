#include<Arduino.h>

// Definiciones de pines para los 74HC595
#define DS 11   // Pin de Datos Serie
#define STCP 12 // Pin de Almacenamiento de Registro
#define SHCP 13 // Pin de Reloj de Desplazamiento

// Tamaño de la matriz
const int filas = 8;
const int columnas = 8;

byte* matrizDeDatos; // Puntero a un arreglo de bytes para representar el estado de las filas

// Función para enviar un byte a los registros 74HC595
void enviarByte(byte dato) {
    digitalWrite(STCP, LOW);
    shiftOut(DS, SHCP, MSBFIRST, dato);
    digitalWrite(STCP, HIGH);
}

// Función para inicializar la matriz de LEDs
void inicializarMatriz() {
    matrizDeDatos = new byte[filas];
    memset(matrizDeDatos, 0, filas);
}

// Función para liberar la memoria utilizada por la matriz de LEDs
void liberarMatriz() {
    delete[] matrizDeDatos;
}

// Función para encender todos los LEDs
void encenderTodosLosLEDs() {
    for (int i = 0; i < filas; i++) {
        matrizDeDatos[i] = 0xFF;
    }
}

// Función para apagar todos los LEDs
void apagarTodosLosLEDs() {
    for (int i = 0; i < filas; i++) {
        matrizDeDatos[i] = 0x00;
    }
}

// Función para verificar que todos los LEDs funcionan correctamente
void verificacion() {
    encenderTodosLosLEDs();
    delay(1000); // Espera 1 segundo
    apagarTodosLosLEDs();
    delay(1000); // Espera 1 segundo
}

// Función para mostrar un patrón ingresado por el usuario
void imagen() {
    // Limpiar la matriz de datos
    apagarTodosLosLEDs();

    // Solicitar al usuario ingresar el patrón por el monitor serial
    Serial.println("Ingrese el patron (8 filas de 8 bits):");

    for (int i = 0; i < filas; i++) {
        // Leer una línea de bits del usuario y almacenarla en la matriz de datos
        while (Serial.available() <= 0);
        matrizDeDatos[i] = Serial.parseInt();
    }
}

void setup() {
    pinMode(DS, OUTPUT);
    pinMode(STCP, OUTPUT);
    pinMode(SHCP, OUTPUT);

    Serial.begin(9600);

    // Inicializar la matriz de LEDs
    inicializarMatriz();
}

void loop() {
    // Verificación de LEDs
    verificacion();

    // Mostrar un patrón personalizado
    imagen();

    // Enviar los datos a la matriz de LEDs
    for (int i = 0; i < filas; i++) {
        enviarByte(matrizDeDatos[i]);
    }
}

// Liberar la memoria al final del programa
void __cxa_pure_virtual() {}
