#include "basemodule.h"

void BASEMODULE_init() {
	PRINTA("BASEMODULE_INIT");
	int i;
	/*
	Il range sotto fa riferimento alla misura del sensore
	_MIN_ double che rappresenta il valore minimo
	_MAX_ double che rappresenta il valore massimo
	*/
	range=INIT_RANGE(_MIN_,_MAX_);
	/*
	Specifiche relative alla misura del sensore 
	DATA_TYPE_E è un enum definito in data.h va aggiunto un campo tipicamente corrispondente al nome del modulo
	DATA_UNIT_E è un enum definito in data.h va aggiunta se non presente l'unità di misura con cui il dato viene rappresentato 
	EXP_TIME_MS un long int che rappresenta i ms dopo cui il dato va considerato non più valido
	ACCURACY un long int che rappresenta l'accuratezza del dato
	*/
	BASEMODULE_data_spec=INIT_DATA_SPEC("BASEMODULE",DATA_TYPE_E,DATA_UNIT_E,range,EXP_TIME_MS,ACCURACY);
	/*
	Il range sotto fa riferimento al dato grezzo acquisito dal sensore
	_MIN_ double che rappresenta il valore minimo
	_MAX_ double che rappresenta il valore massimo
	*/
	range=INIT_RANGE(_MIN_,_MIN_);
	
	/*
	Specifiche relative al dato grezzo letto dal sensore
	DATA_VALUE_TYPE_E è un enum definito in data.h va aggiunto un campo se non presente che indica di che tipo è il singolo dato EX. INT,FLOAT ecc ecc
	data_dimensions le dimensioni effettive del dato raccolto Ex. 0=scalare 1=vettore 2=matrice 3=matrice tridimensionale n=matrice n-dimensionale
	*/
	int data_dimensions=0; 
	BASEMODULE_data_value_spec=INIT_VALUE_SPEC(DATA_VALUE_TYPE_E,range,data_dimensions);
	if (data_dimensions>0) {
		/*
		Definire il numero di elementi massimi per ogni dimensione 
		BASEMODULE_data_value_spec.max_elements[0]=_MAX_ELEMENTS_
		BASEMODULE_data_value_spec.max_elements[1]=_MAX_ELEMENTS_
		..
		..
		BASEMODULE_data_value_spec.max_elements[data_dimensions-1]=_MAX_ELEMENTS_
		*/
	}
	/*
	Il dato
	DATA_TYPE_E è un enum definito in data.h va aggiunto un campo tipicamente corrispondente al nome del modulo
	*/
	BASEMODULE_data=INIT_DATA("BASEMODULE",DATA_TYPE_E,BASEMODULE_data_value_spec);
    SUB(BASEMODULE_data_spec.type);
	SET_S(BASEMODULE_data_spec);
}
 
void BASEMODULE_run() {
  PRINTA("BASEMODULE_RUN");
  /*
	BASEMODULE_data.othermodule_data=GET_D(OTHERMODULE);
	BASEMODULE_data.othermodule_data.value.OTHERMODULE
  */	
  /**
	IL valore del dato
	DATA_VALUE_U è una union definita in data.h, va aggiunto il tipo di dato EX float o int[5] e il realtivo nome
  **/
  BASEMODULE_data.value.DATA_VALUE_U
  SETDATATIMESTAMP(&BASEMODULE_data);
  SET_D(BASEMODULE_data);
}

void BASEMODULE_close() {
  PRINTA("BASEMODULE_CLOSE");
  UNSUB(BASEMODULE_data_spec.type);
}
