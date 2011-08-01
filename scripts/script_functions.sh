#!/bin/bash
# initscripts functions
#

toLower() {
	echo $1 | tr "[:upper:]" "[:lower:]"
}

toUpper() {
	echo $1 | tr  "[:lower:]" "[:upper:]"
}


list_a()
{
	cd $MODULES_DIR
	#MI CREO LA LISTA DI MODULI
	MODULES=*$MODULES_SUFF
	shopt -s nullglob
	for i in $MODULES; do
	    echo "${i%$MODULES_SUFF}"
	done
	cd ..
}

list_e()
{
	MODULES=$MODULES_PREF*$MODULES_SUFF
	#echo $MODULES
	#echo "$MODULES_PREF*$MODULES_SUFF"
	shopt -s nullglob
	for i in $MODULES; do
		echo "${i%$MODULES_SUFF}"
	done
}
