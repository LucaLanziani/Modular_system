#include "secondo.h"

void secondo_init() {
    PRINTA("SECONDO_INIT");
    secondo_state.y=0;
    secondo_state.data.type=SECONDO;
    //secondo_state.data.unit=mm;
    //secondo_state.data.value.y=secondo_state.y;
    SUB(SECONDO);
    /*
    test1_state.nums=(int*)malloc(sizeof(int)*3);
    test1_state.nums[0]=1;
    test1_state.nums[1]=2;
    test1_state.nums[2]=3;
    */
}
 
void secondo_run() {
  PRINTA("SECONDO_RUN");
  boolean result;
  data_t data_primo;
  //data_primo=GET(PRIMO);
  //result=ISDATAVALID(data_primo);
  /*
  if (TRUE==result) {
    secondo_state.data.value.y=sqrt(pow(50000,2)-pow(data_primo.value.x,2));
    SETDATATIMESTAMP(&secondo_state.data);
    SET(secondo_state.data);
  } else {
    printf("==> nessun dato\n");
  }
*/
   /*
   int i=0;
   for(i=0;i++;i<3) {
   	insertdata(test1_state.nums[i]);
   }
   */
};

void secondo_close() {
  UNSUB(SECONDO);
  PRINTA("SECONDO_CLOSE");
}