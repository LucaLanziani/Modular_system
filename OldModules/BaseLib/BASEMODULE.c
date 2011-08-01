#include "BASEMODULE.h"

void BASEMODULE_init() {
	PRINTA("BASEMODULE_INIT");
	
	range=INIT_RANGE(-1,-1);
	BASEMODULE_data_spec=INIT_DATA_SPEC(ACC,m_s2,range,250,-1);
	range=INIT_RANGE(-1,-1);
	BASEMODULE_data_value_spec=INIT_VALUE_SPEC(UINT,range,0);
	BASEMODULE_data=INIT_DATA(ACC,BASEMODULE_data_value_spec);
    SUB(BASEMODULE_data_spec.type);
	SET_S(BASEMODULE_data_spec);
	
    /*
   test_state.nums=(int*)malloc(sizeof(int)*3);
   test_state.nums[0]=3;
   test_state.nums[1]=2;
   test_state.nums[2]=1;
  */
}
 
void BASEMODULE_run() {
  PRINTA("BASEMODULE_RUN");
 
  SETDATATIMESTAMP(&BASEMODULE_data);
  SET_D(BASEMODULE_data);
};

void BASEMODULE_close() {
  PRINTA("BASEMODULE_CLOSE");
  UNSUB(BASEMODULE_data_spec.type);
}
