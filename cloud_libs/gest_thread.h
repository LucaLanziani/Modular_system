#ifndef _GEST_THREADS_
#define _GEST_THREADS_ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "data.h"
#include "debug.h"
#include "gest_module.h"
#include <sys/types.h>
#include <signal.h>

typedef struct {
  boolean presence; 
  pthread_t thread;
} pthread_reg_t;

/**
* Struttura che rappresenta lo stato
*/
typedef struct {
  int terminate;  
  pthread_reg_t *threads;
} gest_thread_state_t;

gest_thread_state_t gest_thread_state;

/**
 * @brief inizializzo lo stato del modulo
**/
void GEST_THREAD_init();

/**
 * @brief "Chiede" ai thread di terminarsi, settando gest_thread_stata.terminate a TRUE
**/
void GEST_THREAD_terminate_all();

/**
 * @brief chiude il thread relativo al modulo ennesimo
**/
void GEST_THREAD_close_thread(int module_number);

/**
 * @brief Immerge la funzione MODULE_RUN relativa al modulo ennesimo all'interno di un ciclo while
 * 		  Termina nel momento in cui la variabile gest_thread_state.terminate diventa uguale a TRUE
**/
void *GEST_THREAD_start_function(void *);

/**
 * @brief Lancia un thread con la funzione RUN del modulo ennesimo
**/
void GEST_THREAD_start_thread(int module_number);

/**
 * @brief Ritorna il descrittore del thread riferito al modulo Ennesimo.
 * 			-1 se il modulo non è stato lanciato in un thread.
**/
pthread_t GEST_THREAD_get(int module_number);

/**
 * @brief Effettua il cancel su tutti i thread lanciati
**/
void GEST_THREAD_close_all();

/**
  * Effettua il join su tutti i thread 
**/
void GEST_THREAD_join_all();


//void GEST_THREAD_close_function(void* num);











#endif