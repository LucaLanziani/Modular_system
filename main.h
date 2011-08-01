#ifndef _MAIN_H_
#define _MAIN_H_

#include "gest_module.h"
#include "data_exchange.h"
#include "common_fncs.h"
#include "gest_thread.h"


#include <signal.h>
#include <sys/time.h>
#include <time.h>


#define DEBUG

void MAIN_close(int signal);
void MAIN_setup_termination();
void MAIN_init();


#endif