#!/bin/bash
#
. ./script_conf.sh
. ./script_functions.sh

INIT_FNC_CONF=$CONFDIR/init_functions.conf
RUN_FNC_CONF=$CONFDIR/run_functions.conf
CLOSE_FNC_CONF=$CONFDIR/close_functions.conf
LINK_NANE_CONF=$CONFDIR/link_name.conf
MODULES_NAME_CONF=$CONFDIR/modules_name.conf
NUM_OF_MODULES_CONF=$CONFDIR/num_of_modules.conf
MODULES_ORDER_FILE=$CONFDIR/modules_order.conf

if [ -d $CONFDIR ]; then
	rm -rf $INIT_FNC_CONF $RUN_FNC_CONF $CLOSE_FNC_CONF $LINK_NANE_CONF $MODULES_NAME_CONF $NUM_OF_MODULES_CONF
else
	mkdir $CONFDIR
	echo S*.so > $MODULES_ORDER_FILE
fi


echo "I moduli verranno avviati nel seguente ordine"

for i in $(list_e); do
	echo "./$i$MODULES_SUFF" >> $LINK_NANE_CONF
	echo ${i#$MODULES_PREF} >> $MODULES_NAME_CONF
	echo ${i#$MODULES_PREF}
done 

#for i in $(ls $MODULES_PREF*$MODULES_SUFF); do
#	echo "./$i" >> $LINK_NANE_CONF
#	RES=${i#$MODULES_PREF}
#	echo ${RES%$MODULES_SUFF} >> $MODULES_NAME_CONF
#	echo ${RES%$MODULES_SUFF}
#done

for i in $(cat $MODULES_NAME_CONF); do 
	UPPER= $(toUpper $i)
	echo $UPPER"_init" >> $INIT_FNC_CONF;
	echo $UPPER"_run" >> $RUN_FNC_CONF;
	echo $UPPER"_close" >> $CLOSE_FNC_CONF;
done

cat $MODULES_NAME_CONF | wc -l > $NUM_OF_MODULES_CONF
