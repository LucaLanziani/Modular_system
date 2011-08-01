#ifndef _BASEMODULE_H_
#define	_BASEMODULE_H_
#include <stdlib.h>
#include <stdio.h>
#include "module.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct{
	/* data_t othermodule_data */
} BASEMODULE_t;

BASEMODULE_t BASEMODULE_state;
data_spec_t BASEMODULE_data_spec;
data_t BASEMODULE_data;
range_t range;
data_value_spec_t BASEMODULE_data_value_spec;


void BASEMODULE_init();
void BASEMODULE_run();
void BASEMODULE_close();

#ifdef	__cplusplus
}
#endif

#endif	/* TEST_H */

