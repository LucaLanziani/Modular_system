#ifndef SECONDO_H
#define	SECONDO_H
#include <stdlib.h>
#include <stdio.h>
#include "module.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct{
	double y;
	data_t data;
} state_t;

state_t secondo_state;


    void secondo_init();
    void secondo_run();
    void secondo_close();

#ifdef	__cplusplus
}
#endif

#endif	/* TEST_H */

