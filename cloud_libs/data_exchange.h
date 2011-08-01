#ifndef _DATA_EXCHANGE_
#define _DATA_EXCHANGE_ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "data.h"
#include "debug.h"



/**
 * @brief coniente i mutex necessari per regolare l'accesso ad una risorsa
 * 
 **/
typedef struct {
  pthread_mutex_t w; /**< mutex per regolare l'accesso in scrittura */
  pthread_mutex_t r; /**< mutex per regolare l'accesso in lettura */
  pthread_mutex_t n; /**< mutex per regolare l'accesso al contatore di processi attivi in lettura */
  int acc; /**< contatore di processi attivi in lettura */
} access_mutex_t;


/**
 * @brief Struttura che immagazzina i dati da scambiare
 **/
typedef struct{
	access_mutex_t data_m; /**< struttura dei mutex per regolare l'accesso contemporaneo al dato */ 
	access_mutex_t spec_m; /**< struttura dei mutex per regolare l'accesso contemporaneo alle specifiche del dato */
	data_t data; /**< il dato */
	data_spec_t spec; /**< specifiche sul dato */
	pthread_rwlock_t rwlock;
} data_exchange_db_t;


/**
 * @brief tipo di dato reltivo al "database" dei dati scambiati dai moduli
 **/
typedef struct {
  data_exchange_db_t db[NUM_OF_DATA_TYPE]; /**< Array che contiene tutti i dati e le relative specifiche dei moduli */
  int busy_positions[NUM_OF_DATA_TYPE]; /**< Contiene 1 se il dato è utilizzato 0 altrimenti */
} data_exchange_state_t;

data_exchange_state_t data_exchange_state; /**< Contiene tutti i dati che vengono scambiati tra moduli */

/**
 * @brief inizializza il modulo Data Exchange e le strutture collegate
 *
 * @return void
 **/
void DATA_EXCHANGE_init();

/**
 * @brief effettua la pulizia della memoria e chiude eventuali descrittori rimasti aperti
 *
 * @return void
 **/
void DATA_EXCHANGE_close();

/**
 * @brief inizializza i mutex necessari per regolamentare l'accesso ai dati da parte di più moduli
 *
 * @param  mutexs struttura dei mutex necessari per regolare l'acceso ad una risorsa
 * @return void
 **/
void DATA_EXCHANGE_access_mutex_init(access_mutex_t *mutexs);

/**
 * @brief si occupa di terminare correttamente i mutex
 *
 * @param  mutexs struttura dei mutex necessari per regolare l'accesso ad una risorsa
 * @return void
 **/
void DATA_EXCHANGE_access_mutex_close(access_mutex_t *mutexs);

/**
 * @brief si occupa di inizializzare i mutex per l'accesso ai dati e alle specifiche degli stessi
 *
 * @param type il dato per cui si vogliono inizializzare i mutex di accesso 
 * @return void
 **/
void DATA_EXCHANGE_mutex_init(data_type_e type);

/**
 * @brief si occupa di terminare correttamente i mutex per l'accesso ai dati e alle specifiche degli stessi
 *
 * @param type il dato per cui si vogliono terminare i mutex di accesso
 * @return void
 **/
void DATA_EXCHANGE_mutex_close(data_type_e type);

/**
 * @brief si occupa di segnalare se qualcuno si è segnato come utilizzatore di un tipo di dato
 *
 * @param type il tipo di dato da controllare
 * @return boolean ritorna true se il dato è utilizzato false altrimenti
 **/
boolean DATA_EXCHANGE_subcribed(data_type_e type);

/**
 * @brief Effettua il subscribe del modulo
 *
 * @param type tipo del dato che verrà caricato dal modulo
 * @return boolean ritorna true se l'operazione ha avuto successo false altrimenti
 **/
boolean DATA_EXCHANGE_subcribe(data_type_e type);

/**
 * @brief ...
 *
 * @param pos ...
 * @return boolean
 **/
boolean DATA_EXCHANGE_rwlock_subscribe(data_type_e pos);

/**
 * @brief ...
 *
 * @param data ...
 * @return void
 **/
void DATA_EXCHANGE_rwlock_set(data_t data);

/**
 * @brief ...
 *
 * @param pos ...
 * @return data_t
 **/
data_t DATA_EXCHANGE_rwlock_get(data_type_e pos);

/**
 * @brief ...
 *
 * @param pos ...
 * @return boolean
 **/
boolean DATA_EXCHANGE_rwlock_unsubscribe(data_type_e pos);

/**
 * @brief Inserisce il nuovo dato nella "nuvola"
 *
 * @param  data il dato da caricare
 * @return void
 **/
void DATA_EXCHANGE_set_data(data_t data);

/**
 * @brief Prende il dato dalla "nuvola"
 *
 * @param  type il dato che si vuole scaricare
 * @return data_t la struttura che rappresenta il dato
 **/
data_t DATA_EXCHANGE_get_data(data_type_e type);

/**
 * @brief Setta le specifiche del dato nella "nuvola"
 *
 * @param  spec la struttura che rappresenta le specifiche
 * @return void
 **/
void DATA_EXCHANGE_set_spec(data_spec_t spec);

/**
 * @brief Prende le specifiche del dato dalla "nuvola"
 *
 * @param  type il tipo di dato di cui scaricare le specifiche
 * @return data_spec_t
 **/
data_spec_t DATA_EXCHANGE_get_spec(data_type_e type);

/**
 * @brief Effettua l'unsubscribe del dato così da permettere di liberare le aree di memoria
 *
 * @param  type il tipo del dato di cui si sta effettuando l'unsubscribe
 * @return boolean
 **/
boolean DATA_EXCHANGE_unsubscribe(data_type_e type);


void DATA_EXCHANGE_print_data(data_t);

#endif