#!/bin/bash

. ./script_conf.sh

if [ ! -d $CONFDIR ]; then
	mkdir $CONFDIR
fi


if [ -e $MODULES_ORDER_FILE ]; then
	echo S*.so > $MODULES_ORDER_FILE_TMP
	cmp -s $MODULES_ORDER_FILE_TMP $MODULES_ORDER_FILE
	if [ ! $? -eq 0 ]; then
		#E' cambiato l'ordine dei moduli, devo rilanciarne il setup
		mv $MODULES_ORDER_FILE_TMP $MODULES_ORDER_FILE
		./ms.sh
	fi
	./saetta
else
	echo S*.so > $MODULES_ORDER_FILE
	./ms.sh
	./saetta
fi 
