#ifndef _PRIMO_H_
#define	_PRIMO_H_
#include <stdlib.h>
#include <stdio.h>
#include "module.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct{
	double x;
} state_t;

state_t primo_state;
data_spec_t primo_data_spec;
data_t primo_data;
range_t range;
data_value_spec_t data_value_spec;

typedef int primo_t;

    void primo_init();
    void primo_run();
    void primo_close();

#ifdef	__cplusplus
}
#endif

#endif	/* TEST_H */

