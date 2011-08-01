#include "gest_thread.h"



void GEST_THREAD_init() { 
  int i;
  int num_of_modules=GEST_MODULE_get_num_of_modules();
  /*
  *Alloco lo spazio necessario a contenere i riferimenti ai thread
  */
 gest_thread_state.terminate=FALSE; 
 gest_thread_state.threads=(pthread_reg_t*)calloc(num_of_modules,sizeof(pthread_reg_t));
 for (i = 0; i < num_of_modules; ++i)
 {	gest_thread_state.threads[i].presence=FALSE;
 	gest_thread_state.threads[i].thread=-1;
 }
};



void GEST_THREAD_terminate_all() {
  gest_thread_state.terminate=TRUE;
}


void GEST_THREAD_close_thread(int module_number) {
  PRINTE("CANCELLA IL THREAD NUMERO %d",module_number);
  pthread_cancel(gest_thread_state.threads[module_number].thread);
  gest_thread_state.threads[module_number].presence=FALSE;
}


void* GEST_THREAD_start_function(void* num) {
  int module_number=*(int*)num;
  PRINTE("IL NUMERO DA AVVIARE È %d",(int)num);
  //pthread_cleanup_push(GEST_MODULE_get_fncs(CLOSE_FNCS)[module_number],num); //preparo la funzione da chiamare in chiusura
  while(1) {
    GEST_MODULE_get_fncs(RUN_FNCS)[module_number]();
    if (gest_thread_state.terminate) {
      GEST_MODULE_get_fncs(CLOSE_FNCS)[module_number]();
      pthread_exit(0);
    }
  }
  //pthread_cleanup_pop(1);
}


void GEST_THREAD_start_thread(int module_number) {
  PRINTE("Module number %d",module_number);
  int *pointer=&module_number;
  PRINTE("Module number pointed %d",*pointer);
  
  gest_thread_state.threads[module_number].presence=TRUE;
  if (0 != pthread_create(&(gest_thread_state.threads[module_number].thread),NULL,GEST_THREAD_start_function,(void*)pointer)) {
        PRINTE("Error on pthread_create of module %s\n");
  }
  //pthread_detach(gest_thread_state.threads[module_number].thread);
};


pthread_t GEST_THREAD_get(int module_number) {
  return gest_thread_state.threads[module_number].thread;
};

/**
* Effettua la cancel sui thread lanciati
**/
void GEST_THREAD_close_all() {
  int i;
  int num_of_modules=GEST_MODULE_get_num_of_modules();
  PRINTA("Chiamato da %d",pthread_self());
  for (i = 0; i < num_of_modules; ++i)
  { if (gest_thread_state.threads[i].presence) {
      PRINTA("Cancello il %d",gest_thread_state.threads[i].thread);
      pthread_cancel(gest_thread_state.threads[i].thread);
      gest_thread_state.threads[i].presence=FALSE;
    }
  }
}


void GEST_THREAD_join_all() {
  int i;
  int num_of_modules=GEST_MODULE_get_num_of_modules();
  for (i = 0; i < num_of_modules; ++i)
  {	if (gest_thread_state.threads[i].presence) {
	  pthread_join(gest_thread_state.threads[i].thread,NULL);
	}
  }
};
