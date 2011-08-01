#ifndef TERZO_H
#define	TERZO_H
#include <stdlib.h>
#include <stdio.h>
#include "module.h"


#ifdef	__cplusplus
extern "C" {
#endif

typedef struct{
	double atan;
	data_t data;
} state_t;

state_t terzo_state;

    void terzo_init();
    void terzo_run();
    void terzo_close();

#ifdef	__cplusplus
}
#endif

#endif	/* TEST_H */

