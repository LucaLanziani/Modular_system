#ifndef _COMMON_FNCS_
#define _COMMON_FNCS_ value
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "debug.h"

/*
typedef struct {
  data_type_e type;
  data_unit_e unit;
  range_t range;
  long int exp_time_ms;
  long int accuracy;
} spec_t;
*/

/**
 * @brief ...
 *
 * @param name ..
 * @param type ...
 * @param unit ...
 * @param range ...
 * @param exp_time_ms ...
 * @param accuracy ...
 * @return spec_t
 * 
 * @todo controllare la consistenza dei dati
 * @todo permette di verificare l'effettiva inizializzazione di spec
 **/
data_spec_t COMMON_FNCS_init_data_spec(data_name_t name,data_type_e type,data_unit_e unit, range_t range,long int exp_time_ms,long int accuracy); 
data_t COMMON_FNCS_init_data(data_name_t name,data_type_e type,data_value_spec_t value_spec);
data_value_spec_t COMMON_FNCS_init_value_spec(data_value_type_e type,range_t range,int dimensions);
range_t COMMON_FNCS_init_range(double min,double max);

int COMMON_FNCS_timeval_subtract(timespec_t *result, timespec_t *timeb, timespec_t *timea);
boolean COMMON_FNCS_is_data_valid(data_t,data_spec_t);
void COMMON_FNCS_set_data_timestamp(data_t*);

#endif
