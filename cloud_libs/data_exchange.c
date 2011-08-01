#include "data_exchange.h"

void DATA_EXCHANGE_init() {
    PRINTW("DATA_EXCHANGE_init");
    int i;
    data_t data;
    data.type=EMPTY;
    for (i = 0; i < NUM_OF_DATA_TYPE; ++i)
    {
        data_exchange_state.busy_positions[i]=FALSE;
        data_exchange_state.db[i].data=data;
    }
};

void DATA_EXCHANGE_close() {
    PRINTW("DATA_EXCHANGE_close");
    int pos;
    for (pos = 0; pos < NUM_OF_DATA_TYPE; ++pos) {
        DATA_EXCHANGE_unsubscribe(pos);
    }
    //TODO VERIFICARE CHE TUTTE LE POSIZIONI SIANO LIBERE ED EFFETTUARE UNA CHIUSURA PULITA
};


void DATA_EXCHANGE_access_mutex_init(access_mutex_t* a_m)
{
    pthread_mutex_init(&(a_m->w),NULL);
    pthread_mutex_init(&(a_m->r),NULL);
    pthread_mutex_init(&(a_m->n),NULL);
    a_m->acc=0;
}

void DATA_EXCHANGE_access_mutex_close(access_mutex_t* a_m)
{
    pthread_mutex_destroy(&(a_m->w));
    pthread_mutex_destroy(&(a_m->r));
    pthread_mutex_destroy(&(a_m->n));
    a_m->acc=0;
}


void DATA_EXCHANGE_mutex_init(data_type_e pos) {
    DATA_EXCHANGE_access_mutex_init(&(data_exchange_state.db[pos].spec_m));
    DATA_EXCHANGE_access_mutex_init(&(data_exchange_state.db[pos].data_m));
}

void DATA_EXCHANGE_mutex_close(data_type_e pos) {
    DATA_EXCHANGE_access_mutex_close(&(data_exchange_state.db[pos].data_m));
    DATA_EXCHANGE_access_mutex_close(&(data_exchange_state.db[pos].spec_m));
}

boolean DATA_EXCHANGE_subcribed(data_type_e pos) {
    //PRINTA("Posizione %d subscribed = %d", pos,data_exchange_state.busy_positions[pos]);
	if (pos < NUM_OF_DATA_TYPE) {
		return data_exchange_state.busy_positions[pos];
	} else {
		return FALSE;
	}
};

boolean DATA_EXCHANGE_subscribe(data_type_e pos) {
	PRINTW("DATA_EXCHANGE_subscribe");
	PRINTW("DATA_EXCHANGE_subscribe sottoscrivo la posizione %d",pos);
    if (DATA_EXCHANGE_subcribed(pos)) {
        return FALSE;
    } else {
        DATA_EXCHANGE_mutex_init(pos);
        data_exchange_state.busy_positions[pos]=TRUE;
        return TRUE;
    }
};

boolean DATA_EXCHANGE_rwlock_subscribe(data_type_e pos) {
    if (DATA_EXCHANGE_subcribed(pos)) {
        return FALSE;
    } else {
        pthread_rwlock_init(&(data_exchange_state.db[pos].rwlock),NULL);
        data_exchange_state.busy_positions[pos]=TRUE;
        return TRUE;
    }
};

void DATA_EXCHANGE_rwlock_set(data_t data) {
    data_type_e pos=data.type;
    PRINTW("Metto %d in posizione %d",data.type,pos);
    if (DATA_EXCHANGE_subcribed(pos)) {
        pthread_rwlock_wrlock(&(data_exchange_state.db[pos].rwlock));
        if (DATA_EXCHANGE_subcribed(pos)) {
            data_exchange_state.db[pos].data=data;				/** Scrivo i dati */
        }
        pthread_rwlock_unlock(&(data_exchange_state.db[pos].rwlock));	/** Unlock sul mutex di scrittura */
    }
};

data_t DATA_EXCHANGE_rwlock_get(data_type_e pos) {
    PRINTW("DATA_EXCHANGE_get");
    int prev,current;
    data_t data;
    data.type=EMPTY;
    if (DATA_EXCHANGE_subcribed(pos)) {
        pthread_rwlock_rdlock(&(data_exchange_state.db[pos].rwlock));
        data=data_exchange_state.db[pos].data; 	/** Leggo i dati */
        PRINTA("Leggo %d dalla posizione %d",data.type,pos);
        pthread_rwlock_unlock(&(data_exchange_state.db[pos].rwlock));
    }
    return data;
};


boolean DATA_EXCHANGE_rwlock_unsubscribe(data_type_e pos) {
    if (DATA_EXCHANGE_subcribed(pos)) {									/** Controllo che sia stato effettuato un subscribe sulla posizione */
        pthread_rwlock_wrlock(&(data_exchange_state.db[pos].rwlock));
        data_exchange_state.busy_positions[pos]=FALSE;
        /** Effettuo l'unsubscribe*/
        pthread_rwlock_unlock(&(data_exchange_state.db[pos].rwlock));
        pthread_rwlock_destroy(&(data_exchange_state.db[pos].rwlock));
        /** Unlock sul mutex di scrittura */
        return TRUE;													/** Ritorno il successo dell'operazione */
    } else {
        return FALSE; 													/** Non era stato effettuato alcun subscribe in questa posizione */
    }
};

/** TODO Tornare un errore se non si è effettuato il subscribe **/
/** il pos lo posso ricavare dal type del dato **/
void DATA_EXCHANGE_set_data(data_t data) {
    data_type_e pos=data.type;
    PRINTW("Metto %d in posizione %d",data.type,pos);
    if (DATA_EXCHANGE_subcribed(pos)) {
        pthread_mutex_lock(&(data_exchange_state.db[pos].data_m.w)); 	/** Lock sul mutex di scrittura (Blocco nuovi accessi in lettura/scrittura) */
        if (DATA_EXCHANGE_subcribed(pos)) {
            pthread_mutex_lock(&(data_exchange_state.db[pos].data_m.r));		/** Lock sul mutex di lettura (Aspetto che tutti abbiano finito di leggere) */
            pthread_mutex_unlock(&(data_exchange_state.db[pos].data_m.r));	/** Unlock sul mutex di lettura */
            data_exchange_state.db[pos].data=data;				/** Scrivo i dati */
        }
        pthread_mutex_unlock(&(data_exchange_state.db[pos].data_m.w));	/** Unlock sul mutex di scrittura */
    }
};


void DATA_EXCHANGE_set_spec(data_spec_t spec) {
  data_type_e pos=spec.type;
  PRINTW("Metto %d in posizione %d",spec.type,pos);
  if (DATA_EXCHANGE_subcribed(pos)) {
    pthread_mutex_lock(&(data_exchange_state.db[pos].spec_m.w)); 	/** Lock sul mutex di scrittura (Blocco nuovi accessi in lettura/scrittura) */
    if (DATA_EXCHANGE_subcribed(pos)) {
      pthread_mutex_lock(&(data_exchange_state.db[pos].spec_m.r));		/** Lock sul mutex di lettura (Aspetto che tutti abbiano finito di leggere) */
      pthread_mutex_unlock(&(data_exchange_state.db[pos].spec_m.r));	/** Unlock sul mutex di lettura */
      data_exchange_state.db[pos].spec=spec;				/** Scrivo i dati */
    }
    pthread_mutex_unlock(&(data_exchange_state.db[pos].spec_m.w));	/** Unlock sul mutex di scrittura */
  }
};

data_t DATA_EXCHANGE_get_data(data_type_e pos) {
    PRINTW("DATA_EXCHANGE_get_data");
    int prev,current;
    data_t data;
    data.type=EMPTY;
    if (DATA_EXCHANGE_subcribed(pos)) {
		PRINTW("DATA_EXCHANGE_get_data position subscribed");
        pthread_mutex_lock(&(data_exchange_state.db[pos].data_m.w)); 	/** Lock sul mutex di scrittura */
        pthread_mutex_lock(&(data_exchange_state.db[pos].data_m.n)); 	/** Lock sul mutex relativo al contatore di accessi in lettura */
        prev=data_exchange_state.db[pos].data_m.acc++; 					/** Salvo il valore del contatore e lo incremento di uno */
        pthread_mutex_unlock(&(data_exchange_state.db[pos].data_m.n)); 	/** Unlock sul mutex relativo al contatore di accessi in lettura */
        if (prev==0) {
            pthread_mutex_lock(&(data_exchange_state.db[pos].data_m.r));	/** Se il contatore valeva 0 (nessuno stava leggendo) Lock sul mutex di lettura */
        }
        pthread_mutex_unlock(&(data_exchange_state.db[pos].data_m.w)); 	/** Unlock sul mutex di scrittura */

        data=data_exchange_state.db[pos].data; 	/** Leggo i dati */

        PRINTA("Leggo %d dalla posizione %d",data.type,pos);
        pthread_mutex_lock(&(data_exchange_state.db[pos].data_m.n));		/** Lock sul mutex relativo al contatore di accessi in lettura */
        current=(--data_exchange_state.db[pos].data_m.acc); 				/** Decremento il valore del contatore e ne salvo il valore in current */
        pthread_mutex_unlock(&(data_exchange_state.db[pos].data_m.n));	/** Unlock sul mutex relativo al contatore di accessi in lettura */
        if (current==0) {
            pthread_mutex_unlock(&(data_exchange_state.db[pos].data_m.r));/** Se current vale 0 (nessuno sta leggendo) Unlock sul mutex di lettura */
        }
    }
    return data;
};



data_spec_t DATA_EXCHANGE_get_spec(data_type_e pos)
{   PRINTW("DATA_EXCHANGE_get_spec");
    int prev,current;
    data_spec_t spec;
    spec.type=EMPTY;
    if (DATA_EXCHANGE_subcribed(pos)) {
        pthread_mutex_lock(&(data_exchange_state.db[pos].spec_m.w)); 	/** Lock sul mutex di scrittura */
        pthread_mutex_lock(&(data_exchange_state.db[pos].spec_m.n)); 	/** Lock sul mutex relativo al contatore di accessi in lettura */
        prev=data_exchange_state.db[pos].spec_m.acc++; 					/** Salvo il valore del contatore e lo incremento di uno */
        pthread_mutex_unlock(&(data_exchange_state.db[pos].spec_m.n)); 	/** Unlock sul mutex relativo al contatore di accessi in lettura */
        if (prev==0) {
            pthread_mutex_lock(&(data_exchange_state.db[pos].spec_m.r));	/** Se il contatore valeva 0 (nessuno stava leggendo) Lock sul mutex di lettura */
        }
        pthread_mutex_unlock(&(data_exchange_state.db[pos].spec_m.w)); 	/** Unlock sul mutex di scrittura */

        spec=data_exchange_state.db[pos].spec; 	/** Leggo i dati */

        PRINTA("Leggo %d dalla posizione %d",spec.type,pos);
        pthread_mutex_lock(&(data_exchange_state.db[pos].spec_m.n));		/** Lock sul mutex relativo al contatore di accessi in lettura */
        current=(--data_exchange_state.db[pos].spec_m.acc); 				/** Decremento il valore del contatore e ne salvo il valore in current */
        pthread_mutex_unlock(&(data_exchange_state.db[pos].spec_m.n));	/** Unlock sul mutex relativo al contatore di accessi in lettura */
        if (current==0) {
            pthread_mutex_unlock(&(data_exchange_state.db[pos].spec_m.r));/** Se current vale 0 (nessuno sta leggendo) Unlock sul mutex di lettura */
        }
    }
    return spec;
}



boolean DATA_EXCHANGE_unsubscribe(data_type_e pos) {
    if (DATA_EXCHANGE_subcribed(pos)) {	/** Controllo che sia stato effettuato un subscribe sulla posizione */
      
	pthread_mutex_lock(&(data_exchange_state.db[pos].spec_m.w)); 	/** Lock sul mutex di scrittura (Blocco nuovi accessi in lettura/scrittura) */
        pthread_mutex_lock(&(data_exchange_state.db[pos].spec_m.r));		/** Lock sul mutex di lettura (Aspetto che tutti abbiano finito di leggere) */
        pthread_mutex_unlock(&(data_exchange_state.db[pos].spec_m.r));	/** Unlock sul mutex di lettura */

        pthread_mutex_lock(&(data_exchange_state.db[pos].data_m.w)); 	/** Lock sul mutex di scrittura (Blocco nuovi accessi in lettura/scrittura) */
        pthread_mutex_lock(&(data_exchange_state.db[pos].data_m.r));		/** Lock sul mutex di lettura (Aspetto che tutti abbiano finito di leggere) */
        pthread_mutex_unlock(&(data_exchange_state.db[pos].data_m.r));	/** Unlock sul mutex di lettura */

        data_exchange_state.busy_positions[pos]=FALSE; /** Effettuo l'unsubscribe marcando la posizione come libera*/
	
        pthread_mutex_unlock(&(data_exchange_state.db[pos].data_m.w));
	pthread_mutex_unlock(&(data_exchange_state.db[pos].spec_m.w));
        DATA_EXCHANGE_mutex_close(pos);
        /** Unlock sul mutex di scrittura */
        return TRUE;	/** Ritorno il successo dell'operazione */
    } else {
        return FALSE; 	/** Non era stato effettuato alcun subscribe in questa posizione */
    }


};
