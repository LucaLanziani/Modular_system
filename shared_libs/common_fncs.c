#include "common_fncs.h"

/*
 * @brief Inizializza le specifiche relative al dato
 * @param[in]
 * @param[out]
*/
data_spec_t COMMON_FNCS_init_data_spec(char* name,data_type_e type,data_unit_e unit, range_t range,long int exp_time_ms,long int accuracy) {
  data_spec_t spec;
  if (type>=NUM_OF_DATA_TYPE) {
    //PRINT_E("Attenzione: Tipo di dato non esistente");
    spec.type=EMPTY;
  } else {
	memset(spec.name,'\0',MAX_MODULE_NAME_LENGTH);
	strncpy(spec.name,name,MAX_MODULE_NAME_LENGTH-1);
    spec.type=type;
    spec.unit=unit;
    spec.range=range;
    spec.exp_time_ms=exp_time_ms;
    spec.accuracy=accuracy;
  }
  return spec;
}; 

data_t COMMON_FNCS_init_data(char* name,data_type_e type, data_value_spec_t value_spec) {
  data_t data;
  if (type>=NUM_OF_DATA_TYPE) {
    data.type=EMPTY;
  } else {
	memset(data.name,'\0',MAX_MODULE_NAME_LENGTH);
	strncpy(data.name,name,MAX_MODULE_NAME_LENGTH-1);
    data.type=type;
    data.value_spec=value_spec;
  }
  return data;
}

data_value_spec_t COMMON_FNCS_init_value_spec(data_value_type_e type,range_t range,int dimensions) {
  data_value_spec_t value_spec;
  value_spec.type=type;
  value_spec.range=range;
  value_spec.dimensions=dimensions;
  value_spec.max_elements=calloc(dimensions,sizeof(int));
  return value_spec;
};


range_t COMMON_FNCS_init_range(double min,double max) {
  range_t range;
  range.min=min;
  range.max=max;
  return range;
}

int COMMON_FNCS_timeval_subtract(timespec_t *result,timespec_t *timeb,timespec_t *timea) {
	/* Perform the carry for the later subtraction by updating y. */
	if (timeb->tv_nsec < timea->tv_nsec) {
 		int nsec = (timea->tv_nsec - timeb->tv_nsec) / 1000000000 + 1;
 		timea->tv_nsec -= 1000000000 * nsec;
 		timea->tv_sec += nsec;
	}
	if (timeb->tv_nsec - timea->tv_nsec > 1000000000) {
 		int nsec = (timeb->tv_nsec - timea->tv_nsec) / 1000000000;
 		timea->tv_nsec += 1000000000 * nsec;
		timea->tv_sec -= nsec;
	}

	/* Compute the time remaining to wait.
	tv_usec is certainly positive. */
	if (result!=NULL) {
	  result->tv_sec = timeb->tv_sec - timea->tv_sec;
	  result->tv_nsec = timeb->tv_nsec - timea->tv_nsec;
	}
	/* Return 1 if result is negative. */
	return timeb->tv_sec < timea->tv_sec;
}

boolean COMMON_FNCS_is_data_valid(data_t data,data_spec_t spec) {
    timespec_t current_time,diff,exptime;
    clock_gettime(CLOCK_REALTIME,&current_time);
    COMMON_FNCS_timeval_subtract(&diff,&current_time,&data.timestamp);
    exptime.tv_sec=spec.exp_time_ms/1000;
    exptime.tv_nsec=(spec.exp_time_ms%1000)*1000000;
    PRINTA("===>Sono passati %ld usec",diff.tv_nsec);
    if ((data.type!=EMPTY) && (COMMON_FNCS_timeval_subtract(NULL,&exptime,&diff)!=1))
    {
        return TRUE;
    } else {
        return FALSE;
    };
};

void COMMON_FNCS_set_data_timestamp(data_t *data) {
	clock_gettime(CLOCK_REALTIME,&(data->timestamp));
};
