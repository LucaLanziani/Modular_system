#include "primo.h"

void primo_init() {
	PRINTA("PRIMO_INIT");
	PRINTA("SECONDO = %d",SECONDO);
	PRINTA("TERZO  = %d",TERZO);
	
	range=INIT_RANGE(-1,-1);
	primo_spec=INIT_DATA_SPEC(ACC,m_s2,range,250,-1);
	value_spec=INIT_VALUE_SPEC(UINT,range,0);
	acc_data=INIT_DATA(ACC,value_spec);
    SUB(acc_spec.type);
	SET_S(acc_spec);
	
    /*
   test_state.nums=(int*)malloc(sizeof(int)*3);
   test_state.nums[0]=3;
   test_state.nums[1]=2;
   test_state.nums[2]=1;
  */
}
 
void primo_run() {
  PRINTA("PRIMO_RUN");
  boolean result,y_v;
  double max=10000;
  data_t atan;
  //atan=GET(TERZO);
  //result=ISDATAVALID(atan);
  
#ifdef DEBUG
  if (result==TRUE) {
   PRINTE("atan2 = %f",atan.value.atan); 
  }
#endif
  primo_state.x+=1;
  primo_data.value.x=primo_state.x;
  SETDATATIMESTAMP(&primo_data);
  SET_D(primo_data);
   /*
   int i=0;
   for(i=0;i++;i<3) {
   	insertdata(test_state.nums[i]);
   }
   */
};

void primo_close() {
  PRINTA("PRIMO_CLOSE");
  UNSUB(PRIMO);
}
