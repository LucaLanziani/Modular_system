#include "gest_module.h"

void GEST_MODULE_test() {
    PRINTW("ciao");
};


void GEST_MODULE_init_state() {
    PRINTW("GEST_MODULES_init_state");
    int i;
    for (i=0;i<NUM_OF_CONF_FILES;i++) {
        gest_module_state.conf_files_path[i]=calloc(BUF_LEN,sizeof(char));
        gest_module_state.conf_files_ptr[i]=NULL;
    }
    gest_module_state.num_of_modules=-1;
    gest_module_state.fncs.init_fncs=NULL;
    gest_module_state.fncs.run_fncs=NULL;
    gest_module_state.fncs.close_fncs=NULL;
}


void GEST_MODULE_free_state() {
    PRINTW("GEST_MODULES_free_state");
    int i;
    for (i=0;i<NUM_OF_CONF_FILES;i++) {
        free(gest_module_state.conf_files_path[i]);
    }
    PRINTW("GEST_MODULES_free_state");
}

void GEST_MODULE_init_config_files_path() {
    PRINTW("GEST_MODULE_init_config_files");
    strcpy(gest_module_state.conf_files_path[CONF_MODULE_NUM],CONF_MODULE_NUM_PATH);
    strcpy(gest_module_state.conf_files_path[CONF_MODULE_NAME],CONF_MODULE_NAME_PATH);
    strcpy(gest_module_state.conf_files_path[CONF_INIT_FNCS],CONF_INIT_FNCS_PATH);
    strcpy(gest_module_state.conf_files_path[CONF_RUN_FNCS],CONF_RUN_FNCS_PATH);
    strcpy(gest_module_state.conf_files_path[CONF_CLOSE_FNCS],CONF_CLOSE_FNCS_PATH);
    GEST_MODULE_open_config_files();
    PRINTW("GEST_MODULE_init_config_files");
}

void GEST_MODULE_open_config_files() {
    PRINTW("GEST_MODULE_open_config_files");
    int i=0;
    int err=0; //TODO - Migliorare la gestione degli errori
    //creo i puntatori ai file di configurazione
    for (i=0;i<NUM_OF_CONF_FILES;i++) {
        gest_module_state.conf_files_ptr[i]=fopen(gest_module_state.conf_files_path[i],"r");
        if (gest_module_state.conf_files_ptr[i]==NULL) {
            PRINTE("Impossibile aprire il file %s",gest_module_state.conf_files_path[i]);
            err=-1;
        };
    }
}


void GEST_MODULE_close_config_files() {
    PRINTW("GEST_MODULE_close_config_files");
    int i=0;
    int err=0; //TODO - Migliorare la gestione degli errori
    //creo i puntatori ai file di configurazione
    for (i=0;i<NUM_OF_CONF_FILES;i++) {
        //Verifico che i puntatori siano allocati prima di fare la close
        //In questo modo evito che venga usata la close due volte
        if (gest_module_state.conf_files_ptr[i]!=NULL) {
            if (fclose(gest_module_state.conf_files_ptr[i])==0) {
                gest_module_state.conf_files_ptr[i]=NULL;
            }
        }
    }
}


void GEST_MODULE_init_modules_and_fncs_ptns() {
    PRINTW("GEST_MODULE_init_modules_and_fncs_ptns");
    int i;
    fscanf(gest_module_state.conf_files_ptr[CONF_MODULE_NUM],"%d\n",&(gest_module_state.num_of_modules));
    PRINTW("Si vogliono caricare %d moduli",gest_module_state.num_of_modules);
    //Inizializzo l'array di strutture che contengono i nomi e i link ai moduli
    gest_module_state.modules=(modules_p)calloc(gest_module_state.num_of_modules,sizeof(modules_t));
    for (i = 0; i < gest_module_state.num_of_modules; ++i)
    {
        bzero(gest_module_state.modules[i].name,sizeof(gest_module_state.modules[i].name));
        gest_module_state.modules[i].handle=NULL;
    }
    //Inizializzo gli array che conterranno i puntatori alle funzioni dei moduli
    gest_module_state.fncs.init_fncs=(fnc_pointer_p)calloc(gest_module_state.num_of_modules,sizeof(fnc_pointer_t));
    gest_module_state.fncs.run_fncs=(fnc_pointer_p)calloc(gest_module_state.num_of_modules,sizeof(fnc_pointer_t));
    gest_module_state.fncs.close_fncs=(fnc_pointer_p)calloc(gest_module_state.num_of_modules,sizeof(fnc_pointer_t));

    //Creo in link agli array di puntatori a funzione
    gest_module_state.fncs.all_fncs[INIT_FNCS]=gest_module_state.fncs.init_fncs;
    gest_module_state.fncs.all_fncs[RUN_FNCS]=gest_module_state.fncs.run_fncs;
    gest_module_state.fncs.all_fncs[CLOSE_FNCS]=gest_module_state.fncs.close_fncs;
}



void GEST_MODULE_free_modules_and_fncs_ptns() {
    PRINTW("GEST_MODULE_free_modules_and_fncs_ptns");
    free(gest_module_state.fncs.close_fncs);
    free(gest_module_state.fncs.run_fncs);
    free(gest_module_state.fncs.init_fncs);
    free(gest_module_state.modules);
}


void GEST_MODULE_link_modules() {
    PRINTW("GEST_MODULE_link_modules");
    int i=0;
    FILE *inputFilePtr = gest_module_state.conf_files_ptr[CONF_MODULE_NAME];
    //fgets(gest_module_state.modules[i].name, sizeof(gest_module_state.modules[i].name), inputFilePtr);
    while (EOF!=fscanf(inputFilePtr,"%s\n",gest_module_state.modules[i].name)) {
        gest_module_state.modules[i].handle=dlopen(gest_module_state.modules[i].name,RTLD_LAZY);
#ifdef DEBUG_MODULE
        if (gest_module_state.modules[i].handle==NULL) {
            PRINTW("Problema \"%s\" nel caricare il modulo %s",dlerror(),gest_module_state.modules[i].name);
        } else {
            PRINTW("Il modulo %s è stato caricato in %p",gest_module_state.modules[i].name,gest_module_state.modules[i].handle);
        }
#endif
        i++;
    }
}


void GEST_MODULE_unlink_modules() {
    PRINTW("GEST_MODULE_unlink_modules");
    int i;
    for (i = 0; i < gest_module_state.num_of_modules; ++i)
    {
        if (dlclose(gest_module_state.modules[i].handle)!=0) {
            PRINTW("Problem \"%s\" nel scaricare il modulo %s",dlerror(),gest_module_state.modules[i].name);
        }
    }
}

//La funzione va chiamata 3 volte passando rispettivamente
//CONF_INIT_FNCS, gest_module_state.fncs.init_fncs
//CONF_RUN_FNCS, gest_module_state.fncs.run_fncs
//CONF_CLOSE_FNCS, gest_module_state.fncs.close_fncs
void GEST_MODULE_link_fncs(conf_file_e conf_file,fnc_pointer_p kind_of_fncs) {
    PRINTW("GEST_MODULE_link_fncs");
    
    FILE *inputFilePtr = gest_module_state.conf_files_ptr[conf_file];
    int i=0;
    char fnc_name[BUF_LEN];
   
    //Verifico la correttezza del primo parametro
    if ((conf_file!=CONF_INIT_FNCS) && (conf_file!=CONF_RUN_FNCS) && (conf_file!=CONF_CLOSE_FNCS)) {
        PRINTE("Parametro conf_file=%d non corretto",conf_file);
        return;
    }
    
    //fgets(fnc_name, sizeof(fnc_name), inputFilePtr);
    while (EOF!=fscanf(inputFilePtr,"%s\n",fnc_name)) {
        kind_of_fncs[i]=dlsym(gest_module_state.modules[i].handle,fnc_name);
#ifdef DEBUG_MODULE
        if (kind_of_fncs[i]==NULL) {
            PRINTW("Problemi nel caricare la funzione di init del modulo %s",gest_module_state.modules[i].name);
        }
#endif
        i++;
    }
}


void GEST_MODULE_link_all_fncs() {
    PRINTW("GEST_MODULE_link_all_fncs");
    GEST_MODULE_link_fncs(CONF_INIT_FNCS,gest_module_state.fncs.init_fncs);
    GEST_MODULE_link_fncs(CONF_RUN_FNCS,gest_module_state.fncs.run_fncs);
    GEST_MODULE_link_fncs(CONF_CLOSE_FNCS,gest_module_state.fncs.close_fncs);
}


void GEST_MODULE_init() {
    PRINTW("GEST_MODULE_init");
    GEST_MODULE_init_state();
    GEST_MODULE_init_config_files_path();
    GEST_MODULE_init_modules_and_fncs_ptns();
    GEST_MODULE_link_modules();
    GEST_MODULE_link_all_fncs();
    //chiudo i file di configurazione, non dovrebbero più servire
    GEST_MODULE_close_config_files();
};


void GEST_MODULE_close() {
    PRINTW("GEST_MODULE_close");
    GEST_MODULE_unlink_modules();
    GEST_MODULE_free_modules_and_fncs_ptns();
    GEST_MODULE_close_config_files();
    GEST_MODULE_free_state();
};


fnc_pointer_p GEST_MODULE_get_fncs(fncs_type_e type_of_fnc) {
    PRINTW("GEST_MODULE_get_fncs");
    return gest_module_state.fncs.all_fncs[type_of_fnc];
};


int GEST_MODULE_get_num_of_modules() {
    PRINTW("GEST_MODULE_get_num_of_modules");
    return gest_module_state.num_of_modules;
};
