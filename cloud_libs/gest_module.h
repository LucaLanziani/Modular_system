#ifndef _GEST_MODULE_
#define _GEST_MODULE_ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "debug.h"
#include "data.h"


#define BUF_LEN 255


#define NUM_OF_CONF_FILES 5 /**< Number of configuration files */
/**
 * Position of configuration file
 * If you change this remember to change also NUM_OF_CONF_FILES
 *
 **/
typedef enum {
    CONF_MODULE_NUM, /**< Position of CONF_MODULE_NUM_PATH */
    CONF_MODULE_NAME, /**< Position of CONF_MODULE_NAME_PATH */
    CONF_INIT_FNCS, /**< Position of CONF_INIT_FNCS_PATH */
    CONF_RUN_FNCS, /**< Position of CONF_RUN_FNCS_PATH */
    CONF_CLOSE_FNCS /**< Position of CONF_CLOSE_FNCS_PATH */
} conf_file_e;

#define CONF_MODULE_NUM_PATH "./conf/num_of_modules.conf\0" /**< Path of MODULE_NUM configuration files, the file contains the number of module who will be activated*/
#define CONF_MODULE_NAME_PATH "./conf/link_name.conf\0" /**< Path of LINK_NAME configuration files, the file contains the number of module who will be activated*/
#define CONF_INIT_FNCS_PATH "./conf/init_functions.conf\0" /**< Path of INIT_FUNCTIONS configuration files, the file contains the number of module who will be activated*/
#define CONF_RUN_FNCS_PATH "./conf/run_functions.conf\0" /**< Path of RUN_FUNCTIONS configuration files, the file contains the number of module who will be activated*/
#define CONF_CLOSE_FNCS_PATH "./conf/close_functions.conf\0" /**< Path of CLOSE_FUNCTIONS configuration files, the file contains the number of module who will be activated*/

typedef enum {
    TEST_MODULE,
    TEST1_MODULE,
    TEST2_MODULE,
} modules_e;


typedef void (*fnc_pointer_t)(); /**< Type of functions pointer */
typedef fnc_pointer_t* fnc_pointer_p; /**< Type of pointer to "function pointer" needed for create an array of functions pointers */

/**
* @brief Position in all_fncs of the init/run/close functions
*
*/
typedef enum {
    INIT_FNCS, /**< Position of init functions */
    RUN_FNCS, /**< Position of run functions */
    CLOSE_FNCS /**< Position of close functions */
} fncs_type_e;

#define TYPE_OF_FNCS 3 /**< Number of types of functions */


/**
 * @brief Contains all the functions pointers
 **/
typedef struct {
    fnc_pointer_p all_fncs[TYPE_OF_FNCS]; /**< Contains the references of init_fncs run_fncs and close_fncs */
    fnc_pointer_p init_fncs; /**< Contains the pointers of all init functions */
    fnc_pointer_p run_fncs; /**< Contains the pointers of all run functions */
    fnc_pointer_p close_fncs; /**< Contains the pointers of all close functions */
} fncs_pointers_t;

/**
* Rappresent a module
* Contains the name and the pointer of module
*/
typedef struct {
    char name[BUF_LEN];
    void *handle;
} modules_t;

typedef modules_t* modules_p;

typedef struct {
    char *conf_files_path[NUM_OF_CONF_FILES]; /**< Contains the paths of configuration files */
    FILE *conf_files_ptr[NUM_OF_CONF_FILES]; /**< Contains the pointer of opened configuration files */
    int num_of_modules; /**< Number of modules to load */
    modules_p modules; /**< Array of modules_t struct, it will contain the links and the name of linked libraries*/
    fncs_pointers_t fncs; /**< Contains the pointers of init/run/close functions */
} gest_module_state_t;

gest_module_state_t gest_module_state; /**< Contains all the variables needed by the module */


//*
//Aggiungere una slash difronte alla riga precedente per rendere i metodi pubblici

/**
 * @brief Inizializza lo stato del modulo
 * \sa gest_module_state_t gest_module_state;
 * @return void
 */
void GEST_MODULE_init_state();

/**
 * @brief Libera lo spazio allocato dallo stato
 *
 * @return void
 **/
void GEST_MODULE_free_state();

/**
 * @brief Inizializzo la truttura che contiene i percorsi dei file
 *
 * @return void
 **/
void GEST_MODULE_init_config_files_path();

/**
 * @brief Verifica l'esistenza dei file di configurazione e li apre salvando i descrittori
 *
 * @return void
 **/
void GEST_MODULE_open_config_files();

/**
 * @brief Chiude i descrittori dei file di configurazione
 *
 * @return void
 **/
void GEST_MODULE_close_config_files();

/**
 * @brief Alloca lo spazio per i puntatori a moduli e funzioni
 *
 * @todo Controllare "la correttezza" del numero acquisito da file
 * @return void
 **/
void GEST_MODULE_init_modules_and_fncs_ptns();

/**
 * @brief Libera lo spazio dei puntatori a moduli e funzioni
 *
 * @return void
 **/
void GEST_MODULE_free_modules_and_fncs_ptns();

/**
 * @brief Crea i link con i moduli
 * 
 * @todo per ora si usa la fscanf e si legge per righe, bisognerebbe controllare la lunghezza dell'input da file
 * 
 * @code
 * 	dlopen(gest_module_state.modules[i].name,RTLD_LAZY);
 * @endcode
 * @return void
 **/
void GEST_MODULE_link_modules();

/**
 * @brief Libera i moduli linkati
 * @code
 *	dlclose(gest_module_state.modules[i].handle)
 * @endcode
 *
 * @return void
 **/
void GEST_MODULE_unlink_modules();

/**
 * @brief Effettua i link alle funzioni leggendone i nomi dai file di configurazione
 *
 * Un esempio di come invocarlo:
 * @code
 *  GEST_MODULE_link_fncs(CONF_INIT_FNCS,gest_module_state.fncs.init_fncs);
 * @endcode
 * @todo Per ora si usa la fscanf per leggere ad file, effettuare un controllo sulle stringhe
 *
 * \sa void GEST_MODULE_link_all_fncs();
 *
 * @param[in] conf_file può valere @code CONF_INIT_FNCS o CONF_RUN_FNCS o CONF_CLOSE_FNCS @endcode
 * @param[in] kind_of_fncs riferimento all'array che contiene i puntatori alle funzioni
 *
 * @return void
 **/
void GEST_MODULE_link_fncs(conf_file_e conf_file,fnc_pointer_p kind_of_fncs);

/**
 * @brief Inizializza tutti i puntatori a funzione
 * Chiama semplicemente più volte la funzione GEST_MODULE_link_fncs
 * \sa void GEST_MODULE_link_fncs(conf_file_e conf_file,fnc_pointer_p kind_of_fncs);
 * @return void
 **/
void GEST_MODULE_link_all_fncs();

/**
 * @brief Funzione da chiamare per inizializzare il modulo
 * - Alloca lo spazio necessario
 * - Apre i file di configurazione
 * - Crea i link ai moduli
 * - Crea i link alle funzioni di init/run/close
 * - Chiude i file di configurazione
 *
 * @return void
 **/
void GEST_MODULE_init();

/**
 * @brief Funzione da chiamare per chiudere il modulo
 * - Termina i link con i moduli
 * - Dealloca lo spazio occupato dai puntatori a moduli/funzioni
 * - Chiude i file di configurazione (se non è stato fatto precedentemente)
 * - Dealloca lo spazio dello stato
 *
 * @return void
 **/
void GEST_MODULE_close();

/**
 * @brief Permette di ottenere i puntatori alle funzioni di init/run/close
 *
 * @param type_of_fnc permette di pecificare che tipo di funzioni vogliamo
 * @return fnc_pointer_p ritorna un array di puntatori a funzioni
 **/
fnc_pointer_p GEST_MODULE_get_fncs(fncs_type_e type_of_fnc);

/**
 * @brief Ritorna il numero di moduli caricati
 *
 * @return int -> Numero dei moduli caricati
 **/
int GEST_MODULE_get_num_of_modules();
#endif