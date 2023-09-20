#include<iostream>
using namespace std;

enviarByte(byte dato);
encenderTodosLosLEDs();
setup();
loop();

int main(){

    // Definiciones de pines para los 74HC595
    int DS =11;   // Pin de Datos Serie
    int STCP =12; // Pin de Almacenamiento de Registro
    int SHCP =13; // Pin de Reloj de Desplazamiento

    // Tamaño de la matriz
    const int filas = 8;
    const int columnas = 8;

    return 0;
}

// Función para encender todos los LEDs
void enviarByte(byte dato) {
    digitalWrite(STCP, LOW); // Inicio de la transmisión
    for (int i = 7; i >= 0; i--) {
        digitalWrite(DS, (dato >> i) & 1); // Envía el siguiente bit
        digitalWrite(SHCP, HIGH); // Pulso de reloj
        digitalWrite(SHCP, LOW);
    }
    digitalWrite(STCP, HIGH); // Fin de la transmisión
}

// Función para encender todos los LEDs
void encenderTodosLosLEDs() {
    byte datos = B11111111; // Todos los bits en 1 para encender todos los LEDs
    for (int i = 0; i < filas; i++) {
        enviarByte(datos); // Envía el mismo byte a todas las columnas
    }
}

void setup() {
    pinMode(DS, OUTPUT);
    pinMode(STCP, OUTPUT);
    pinMode(SHCP, OUTPUT);
    // Configura los pines de los registros 74HC595

    digitalWrite(STCP, LOW); // Inicializa el pin STCP en LOW
    encenderTodosLosLEDs(); // Enciende todos los LEDs al inicio
}

void loop() {
    // Enciende todos los LEDs cada 2 segundos
    encenderTodosLosLEDs();
    delay(2000);
    encenderTodosLosLEDs(); // Apaga todos los LEDs al final
    delay(2000);
}
