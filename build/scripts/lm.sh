#!/bin/bash
# -
. ./script_conf.sh
. ./script_functions.sh

usage()
{
cat << EOF
Usage: $0 [-l| -r] module-name -o NN

This script link/unlink modules.

OPTIONS:
   -h               Show this message
   -i libfoo        Enable libfoo module
   -r libfoo        Disable libfoo module
   -o NN            Startup order of the module 
   -l               List of avviable modules
   -L               List of enabled modules

EXAMPLE:
   $0 -i libfoo -o 01    Link $MODULES_DIR/libfoo.so to ./S01libfoo.so
   $0 -r libfoo -o 02    Remove the link ./S02libfoo.so
   $0 -l                    List all the avviable module on $MODULES_DIR

EOF
}

link()
{
    if [[ -e $MODULES_DIR/$INSTALL$MODULES_SUFF ]]
    then
        #echo "ln -s $MODULES_DIR/$INSTALL$MODULES_SUFF ./S$ORDER$INSTALL$MODULES_SUFF"
        ln -siv "$MODULES_DIR/$INSTALL$MODULES_SUFF" "./S$ORDER$INSTALL$MODULES_SUFF"
    else
        echo "Il modulo $MODULES_DIR/$INSTALL$MODULES_SUFF non esiste"
    fi
}

unlink()
{
    if [[ -e ./S$ORDER$REMOVE$MODULES_SUFF ]]
    then
        #echo "rm ./S$ORDER$REMOVE$MODULES_SUFF"
        rm -iv "./S$ORDER$REMOVE$MODULES_SUFF"
    else
        echo "Il link ./S$ORDER$REMOVE$MODULES_SUFF non esiste"
    fi
}


INSTALL=
REMOVE=
ORDER=
while getopts “hi:r:o:lL” OPTION
do
     case $OPTION in
         h)
             usage
             exit 1
             ;;
         i)
             INSTALL=$OPTARG
             ;;
         r)
             REMOVE=$OPTARG
             ;;
         o)
             ORDER=$OPTARG
             ;;
         l)
             echo "==Avviable modules are=="
             list_a
             exit 1
             ;;
         L) 
             echo "==Enabled modules are=="
             list_e
             exit 1
             ;;
         ?)
             usage
             exit
             ;;
     esac
done

if [[ -n $ORDER ]]
then

    if [[ -z $INSTALL ]] && [[ -z $REMOVE ]]
    then
         usage
         echo "===> Specificare ALMENO UN opzione tra -i e -r <==="
         exit 1
    fi

    if [[ -n $INSTALL ]] && [[ -n $REMOVE ]]
    then
        usage
        echo "===> Specificare UNA SOLA opzione tra -i e -r <==="
        exit 1
    fi

    if [[ -n $INSTALL ]]
    then
        link
    else
        unlink
    fi

else 
    usage
    echo "===> E' necessario specificare l'ordine con l'opzione -o <==="
fi
