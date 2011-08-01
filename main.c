#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include "main.h"

void MAIN_init() {
	DATA_EXCHANGE_init();
    GEST_MODULE_init();
	GEST_THREAD_init();
	int i;
	for (i=0; i < GEST_MODULE_get_num_of_modules(); ++i)
	{GEST_MODULE_get_fncs(INIT_FNCS)[i](NULL);}
}

void MAIN_setup_termination() {
    if (signal(SIGINT, MAIN_close) == SIG_IGN) signal(SIGINT, SIG_IGN);
    if (signal(SIGHUP, MAIN_close) == SIG_IGN) signal(SIGHUP, SIG_IGN);
    if (signal(SIGTERM, MAIN_close) == SIG_IGN) signal(SIGTERM, SIG_IGN);
}

void MAIN_close(int signal) {
  //GEST_THREAD_cancel_all_thread();
  //GEST_THREAD_terminate_all();
	int i;
	for (i=0; i < GEST_MODULE_get_num_of_modules(); ++i)
	{GEST_MODULE_get_fncs(CLOSE_FNCS)[i](NULL);}
	GEST_THREAD_close_all();
	GEST_MODULE_close();
	DATA_EXCHANGE_close();
  	
}

int main(int argc, char** argv) {
    struct timespec start,stop,a,b,period;
	int i;
    printf("MAIN\n");
    MAIN_init();	
    //DATA_EXCHANGE_init();
    MAIN_setup_termination();
/*
    int i;
    int j=0;
	int count=10;
   
//GEST_MODULE_test();
	GEST_MODULE_init();
	GEST_THREAD_init();
	for (i=0; i < GEST_MODULE_get_num_of_modules(); ++i)
		{GEST_MODULE_get_fncs(INIT_FNCS)[i](NULL);}
	clock_gettime(CLOCK_REALTIME,&start);
	a=start;

	for (j=0; j<100000; j++) {
		for (i=0; i < GEST_MODULE_get_num_of_modules(); ++i)
			{GEST_MODULE_get_fncs(RUN_FNCS)[i](NULL);}
		clock_gettime(CLOCK_REALTIME,&b);
		COMMON_FNCS_timeval_subtract(&period,&b,&a);
		printf("%ld\t%ld\n",period.tv_sec,period.tv_nsec);
		a=b;
	}
	clock_gettime(CLOCK_REALTIME,&stop);
	COMMON_FNCS_timeval_subtract(&period,&stop,&start);
	printf("%ld\t%ld\n",period.tv_sec,period.tv_nsec);

	for (i=0; i < GEST_MODULE_get_num_of_modules(); ++i)
		{GEST_MODULE_get_fncs(CLOSE_FNCS)[i](NULL);}

	//for (i=0; i < GEST_MODULE_get_num_of_modules(); ++i){GEST_THREAD_start_thread(i);}
	//GEST_THREAD_join_all();
	GEST_MODULE_close();
//*/

//*
	data_t wref,vref;
	pthread_t CORE_MAIN_run_thread;
//*/	
	while (1) {
		wref=GET_D(WREF);
		vref=GET_D(VREF);
		for (i=0; i < GEST_MODULE_get_num_of_modules(); ++i)
		{GEST_MODULE_get_fncs(RUN_FNCS)[i](NULL);}
	//	printf("MAIN_VREF: %f\nMAIN_WREF: %f\n",vref.value.VREF,wref.value.WREF);
		//sleep(1);
	}
    //DATA_EXCHANGE_close();
    //sleep(3);
    exit(0);
}
