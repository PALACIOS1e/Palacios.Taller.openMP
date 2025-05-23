/******************************************
* Pontificia Universidad Javeriana
* Fecha: 22 - 05 - 2025
* Autor: Dary Palacios
* Materia: Sistemas Operativos 
* Tópico : Uso de OMP OpenMP
* Descripción: OpenMP aprovecha para distribuir las iteraciones de un bucle (for) entre varios hilos simultáneamente. La variable (a) se maneja de forma independiente en cada hilo, y en cada paso se determina un valor actualizado para (b = a + i) Se revela la cantidad más alta de hilos que se pueden usar y el número de hilos que están activos.
*******************************************/

#include <stdio.h> // -> Funciones de entrada/salida  
#include <stdlib.h> // -> Funciones como atoi() y exit()
#include <omp.h> // -> Librería de OpenMP para paralelismo con múltiples hilos

int main(int argc, char *argv[]){
  // -> Verifica que el usuario haya ingresado un argumento (NumHilos). Si no, se muestra un mensaje y se termina el programa con exit(0)
  if (argc < 2){
    printf("Entrada por consola \n\t $./ejecutable NumHilos\n");
    exit(0);
  }

  int i; // -> Variable para el bucle (for)
  int a = 50; // -> Variable constante que se va a sumar en cada iteración del bucle (for)
  int b = 0; // -> Variable que se va a actualizar en cada iteración del bucle (for)
  const int N = 1000; // -> Almacenamos el resultado de las sumas

  int hilos = atoi(argv[1]); // -> Convierte el argumento argv[1] en un número entero este número representa la cantidad de hilos                
  int maxHilos = omp_get_max_threads();  // -> Número máximo de hilos que el sistema permite usar con OpenMP
  omp_set_num_threads(hilos); // -> Número de hilos que se van a usar el programa               
  #pragma omp parallel // -> Se ejecuta una vez por cada hilo
  { // -> Devuelve cuántos hilos están ejecutándose actualmente
    printf("Maxhilos %d \t Equipo de hilos impuestos = %d\n", maxHilos, omp_get_num_threads());
  }

  #pragma omp parallel for private(a, i) //->cada hilo usa su propia copia de a e i. El bucle (for) se divide entre los hilos 
  for (i = 0; i < N; i++){ // -> Se va a ejecutar en paralelo
    b += a + i; // -> Actualiza el valor de b en cada iteración 
  }

  printf("El valor de a=%d \t el valor de b= %d (se espera que sea a = 50, b = 50+51+...+1049) \n", a, b); // -> Imprime los valores de a y b

  return 0;
}

/********************************************
Conclusión: Este programa sirve para ilustrar cómo se puede sacar partido del paralelismo que brinda OpenMP. La idea es repartir el trabajo de un bucle entre varios hilos, se logra así una mejora en la velocidad al realizar tareas repetitivas o con mucha información. Como se puede ver, cada hilo tiene la libertad de trabajar por su cuenta con variables privadas, y si se usan bien técnicas como la de "reduction", se pueden juntar los resultados poco a poco sin que haya problemas por trabajar varios hilos a la vez.
********************************************/
