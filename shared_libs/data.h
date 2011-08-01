#ifndef _DATA_H_
#define _DATA_H_
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif
#define DATA_EXPIRE_TIME 200000000 /**< data expire time in nsec */
#define MAX_MODULE_NAME_LENGTH 21

/**
 * @brief ...
 **/
typedef unsigned int boolean;
typedef char data_name_t[MAX_MODULE_NAME_LENGTH]; 

#define SUB(module)  DATA_EXCHANGE_subscribe(module)
#define SET_D(data_t)  DATA_EXCHANGE_set_data(data_t)
#define GET_D(module)  DATA_EXCHANGE_get_data(module)
#define SET_S(spec_t)  DATA_EXCHANGE_set_spec(spec_t)
#define GET_S(module)  DATA_EXCHANGE_get_spec(module)
#define UNSUB(module) DATA_EXCHANGE_unsubscribe(module)

#define ISDATAVALID(data_t,spec_t) COMMON_FNCS_is_data_valid(data_t,spec_t)
#define SETDATATIMESTAMP(data_p) COMMON_FNCS_set_data_timestamp(data_p)
#define INIT_DATA_SPEC(name,type,unit,range,exp_time_ms,accuracy) COMMON_FNCS_init_data_spec(name,type,unit,range,exp_time_ms,accuracy)
#define INIT_DATA(name,type,value_spec) COMMON_FNCS_init_data(name,type,value_spec)
#define INIT_VALUE_SPEC(type,range,dimensions) COMMON_FNCS_init_value_spec(type,range,dimensions)

#define INIT_RANGE(min,max) COMMON_FNCS_init_range(min,max)

/**
 * @brief ...
 **/
typedef struct {
	int number[10];
	int last;
} listofnumber;

/**
 * @brief ...
 **/
typedef enum {
	EMPTY=0,
	IR,
	GYRO,
  	ACC,
	MAGNETO,
	ODO_POSITION,
	ODO_ORIENTATION,
	WREF,
	VREF
} data_type_e;

#define NUM_OF_DATA_TYPE 9

/**
 * @brief Contiene i tipi di valore ammissibili per i dati es unsigned int[5] IR
 **/
typedef union {
	unsigned int IR[5];
	int MAGNETO[2];
	float GYRO[2];
	int ACC[3];
	float ODO_POSITION[2];
	float ODO_ORIENTATION;
	float WREF;
	float VREF;
	float FLOAT;
	int INT;
} data_value_u;

typedef struct timespec timespec_t;

/**
 * @brief enum delle unità di misura ammissibili per i dati
 *
 **/
typedef enum {
  undef=0,
  m,
  cm,
  dm,
  mm,
  rad,
  m_s2,
  rad_s,
  cm_s,
} data_unit_e;

/**
 * @brief rappresenta il range ammissibile per un dato
 * @todo se min e max sono entrambi uguali a 0, il range è indefinito 
 **/
typedef struct {
	double min;
	double max;
} range_t;


/**
 * @brief ...
 **/
typedef struct {
	data_name_t name;
	data_type_e type;
	data_unit_e unit;
	range_t range;
	long int exp_time_ms;
	long int accuracy;
} data_spec_t;


typedef enum {
	UNDEF=0,
	UINT,
	CHAR,
	INT,
	DOUBLE,
	FLOAT,
	STRUCT
} data_value_type_e;

/**
 * @brief rappresenta le specifiche sul tipo di dato acquisito dal sensore, 
 **/
typedef struct {
  data_value_type_e type;
  range_t range;
  int dimensions;
  int *max_elements; /**< rappresenta il massimo numero di elementi per ogni dimensione ex [3,4,5] questo vuol dire che la prima dimensione va da 0 a 2*/ 
} data_value_spec_t;

/**
 * @brief contiene le informazioni sul dato acquisito dal sensore
 **/
typedef struct {
	data_name_t name;
	data_type_e type;
	data_value_u value;
	data_value_spec_t value_spec;
	timespec_t timestamp;
} data_t;




#endif
