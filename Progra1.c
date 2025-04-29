#include <stdio.h>
#include <string.h>

#define NUM_PARTIDOS 6
#define NUM_EQUIPOS 4


void limpiarBuffer() {
    while (getchar() != '\n'); 
}


int leerEnteroPositivo() {
    int valor;
    int val;
    
    while (1) {
        val = scanf("%d", &valor);
        
        if (val == 0 || valor < 0) {
            printf("Por favor, ingrese un numero entero no negativo: ");
            limpiarBuffer();  
        } else {
            limpiarBuffer();  
            return valor;
        }
    }
}

int main() {
    char nombresEquipos[NUM_EQUIPOS][50]; 
    int goles[NUM_EQUIPOS] = {0}; 
    int golesContra[NUM_EQUIPOS] = {0}; 
    int puntos[NUM_EQUIPOS] = {0};
    int diferenciaGoles[NUM_EQUIPOS] = {0}; 
    int i, j, partido, golesEquipo1, golesEquipo2;
    int equipoIndice1, equipoIndice2;
    int finalista1 = 0, finalista2 = 0;
    
    
    for (i = 0; i < NUM_EQUIPOS; i++) {
        printf("Ingrese el nombre del equipo %d: ", i + 1);
        scanf("%s", nombresEquipos[i]);
        limpiarBuffer(); 
    }
    
    int enfrentamientos[NUM_PARTIDOS][2] = {
        {0, 1}, 
        {0, 2}, 
        {0, 3}, 
        {1, 2}, 
        {1, 3}, 
        {2, 3}  
    };

    for (partido = 0; partido < NUM_PARTIDOS; partido++) {
        equipoIndice1 = enfrentamientos[partido][0];
        equipoIndice2 = enfrentamientos[partido][1];
        
        printf("\nIngrese los resultados del partido %d:\n", partido + 1);
        printf("Equipo 1: %s vs Equipo 2: %s\n", nombresEquipos[equipoIndice1], nombresEquipos[equipoIndice2]);

       
        printf("Ingrese los goles de %s: ", nombresEquipos[equipoIndice1]);
        golesEquipo1 = leerEnteroPositivo();
        printf("Ingrese los goles de %s: ", nombresEquipos[equipoIndice2]);
        golesEquipo2 = leerEnteroPositivo();

    
        goles[equipoIndice1] += golesEquipo1;
        goles[equipoIndice2] += golesEquipo2;
        golesContra[equipoIndice1] += golesEquipo2;
        golesContra[equipoIndice2] += golesEquipo1;
        
      
        if (golesEquipo1 > golesEquipo2) {
            puntos[equipoIndice1] += 3; 
        } else if (golesEquipo1 < golesEquipo2) {
            puntos[equipoIndice2] += 3; 
        } else {
            puntos[equipoIndice1] += 1; 
            puntos[equipoIndice2] += 1; 
        }
    }

    for (i = 0; i < NUM_EQUIPOS; i++) {
        diferenciaGoles[i] = goles[i] - golesContra[i];
    }

    for (i = 1; i < NUM_EQUIPOS; i++) {
        if (puntos[i] > puntos[finalista1] || 
            (puntos[i] == puntos[finalista1] && diferenciaGoles[i] > diferenciaGoles[finalista1])) {
            finalista1 = i;
        }
    }

    finalista2 = (finalista1 == 0) ? 1 : 0; 
    
    for (i = 0; i < NUM_EQUIPOS; i++) {
        if (i != finalista1) { 
            if (puntos[i] > puntos[finalista2] || 
                (puntos[i] == puntos[finalista2] && diferenciaGoles[i] > diferenciaGoles[finalista2])) {
                finalista2 = i;
            }
        }
    }

 
    printf("\nResultados finales:\n");
    printf("----------------------------------------\n");
    printf("| %-15s | %5s | %5s | %5s |\n", "Equipo", "Goles", "Puntos", "Dif.");
    printf("----------------------------------------\n");
    for (i = 0; i < NUM_EQUIPOS; i++) {
        printf("| %-15s | %5d | %5d | %5d |\n", nombresEquipos[i], goles[i], puntos[i], diferenciaGoles[i]);
    }
    printf("----------------------------------------\n\n");

 
    printf("Los finalistas son:\n");
    printf("1. %s con %d puntos y diferencia de goles: %d\n", 
           nombresEquipos[finalista1], puntos[finalista1], diferenciaGoles[finalista1]);
    printf("2. %s con %d puntos y diferencia de goles: %d\n", 
           nombresEquipos[finalista2], puntos[finalista2], diferenciaGoles[finalista2]);

    return 0;
}