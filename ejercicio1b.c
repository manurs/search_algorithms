/***********************************************/
/* Programa: ejercicio1     Fecha:             */
/* Autores:                                    */
/*                                             */
/* Programa que comprueba el funcionamiento de */
/* la busqueda lineal                          */
/*                                             */
/* Entrada: Linea de comandos                  */
/*   -tamanio: numero elementos diccionario    */
/*   -clave:   clave a buscar                  */
/*                                             */
/* Salida: 0: OK, -1: ERR                      */
/***********************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

#include "ordenar.h"
#include "busqueda.h"

int main(int argc, char** argv)
{
  int i, nob, pos;
  unsigned int clave, tamanio;
  char funcion[32], orden [4];
  PDICC pdicc;
  int *perm;

  srand(time(NULL));

  if (argc != 9) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -funcion <string> -orden <string> -tamanio <int> -clave <int>\n", argv[0]);
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, " -funcion : funcion a usar.\n");
    fprintf(stderr, " -orden : si o no.\n");
    fprintf(stderr, " -tamanio : numero elementos de la tabla.\n");
    fprintf(stderr, " -clave : clave a buscar.\n");
    exit(-1);
  }

  printf("Practica numero 3, apartado 1\n");
  printf("Realizada por: Manuel Reyes y Adrian Bueno\n");
  printf("Grupo: 126\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc; i++) {
    if(strcmp(argv[i], "-funcion") == 0) {
      strcpy(funcion, argv[++i]);
    } else if(strcmp(argv[i], "-orden") == 0) {
      strcpy(orden, argv[++i]);
    } else if(strcmp(argv[i], "-tamanio") == 0) {
      tamanio = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-clave") == 0) {
      clave = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
    }
  }

  if (strcmp(orden, "no") == 0 && strcmp(funcion, "bbin") == 0){
    printf("La busqueda binaria requiere datos ordenados");
    exit(-1);
  }

  if (strcmp(orden, "no") == 0 && strcmp(funcion, "bbin_nrec") == 0){
    printf("La busqueda binaria requiere datos ordenados");
    exit(-1);
  }

  if (strcmp(orden, "si") == 0){
    pdicc = ini_diccionario(tamanio,ORDENADO);
  } else if (strcmp(orden, "no") == 0){
    pdicc = ini_diccionario(tamanio,NO_ORDENADO);
  } else {
    printf("El orden debe debe ser si o no");
    exit(-1);
  }

  if (pdicc == NULL) {
    /* error */
    printf("Error: No se puede Iniciar el diccionario\n");
    exit(-1);
  }

  perm = genera_perm(tamanio);

  if (perm == NULL) {
    /* error */
    printf("Error: No hay memoria\n");
    libera_diccionario(pdicc);
    exit(-1);
  }

  nob = insercion_masiva_diccionario(pdicc, perm, tamanio);

  if (nob == ERR) {
    /* error */
    printf("Error: No se puede crear el diccionario memoria\n");
    free(perm);
    libera_diccionario(pdicc);
    exit(-1);
  }

  if (strcmp(funcion, "bbin") == 0){
     nob = busca_diccionario(pdicc,clave,&pos,bbin);
  } else if (strcmp(funcion, "bbin_nrec") == 0){
     nob = busca_diccionario(pdicc,clave,&pos,bbin_nrec);
  } else if (strcmp(funcion, "blin") == 0){
     nob = busca_diccionario(pdicc,clave,&pos,blin);
  } else if (strcmp(funcion, "blin_rec") == 0){
     nob = busca_diccionario(pdicc,clave,&pos,blin_rec);
  } else if (strcmp(funcion, "blin_auto") == 0){
     nob = busca_diccionario(pdicc,clave,&pos,blin_auto);
  } else {
     printf ("Funcion no contemplada, prueba con:\n bbin\n bbin_nrec \n blin\n blin_rec\n blin_auto");
     free(perm);
     libera_diccionario(pdicc);
     exit(-1);
  }

  if(nob >= 0) {
    printf("Clave %d encontrada en la posicion %d en %d op. basicas\n",clave,pos,nob);
  } else if (nob==NO_ENCONTRADO) {
    printf("La clave %d no se encontro en la tabla\n",clave);
  } else {
    printf("Error al buscar la clave %d\n",clave);
  }

  free(perm);
  libera_diccionario(pdicc);

  return 0;
}

