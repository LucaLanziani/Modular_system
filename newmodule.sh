#!/bin/bash
# -
#. ./script_conf
#. ./script_functions.sh

usage()
{
cat << EOF
Usage: $0 module-name

This script download the basemodules and prepare the scaffold of the new module
EOF
}

toLower() {
echo $1 | tr "[:upper:]" "[:lower:]"
}

toUpper() {
echo $1 | tr  "[:lower:]" "[:upper:]"
}

function define_var
{
	CONTACT="Attilio"
}

function define_color
{
RED='\E[0;31m'
NORMAL='\E[0m'
GREEN='\E[0;32m'
YELLOW='\E[1;33m'
}

function if_error
{
	if [[ $? -ne 0 ]]; then
		echo -e $RED"$1"$NORMAL 1>&2
	        echo -e $RED"Per maggiori informazioni contattare $CONTACT"$NORMAL 1>&2
		exit $?
	fi
}

function message
{
    COLOR=$GREEN
	if [ ! -z "$2" ]; then
		COLOR=$2
	fi
	echo -e $COLOR"$1"$NORMAL
}

define_var
#SE SI E' SU LINUX DECOMMENTARE LA RIGA SOTTOSTANTE
define_color

if [[ -z $1 ]]
   then
        usage
        exit 1
fi

LOWER=$(toLower $1)
UPPER=$(toUpper $1)

[[ -e $(which git) ]] 
if_error "Install git before continue"

[[ -e modules ]] && message "Attenzione lo script crea una directory modules e sembra che ve ne sia già un altra..." && exit
git clone -q git@labrobwiki.dia.uniroma3.it:modules.git
if_error "Problem to access to GIT repository"

cd modules
if_error "Verificare l'esistenza della directory"

git branch -r | grep "origin/$LOWER\$" && message "--> ATTENZIONE!!! Esiste già un branch/modulo con questo nome\nProvare con un altro nome" && exit
git branch $LOWER
git checkout $LOWER
if_error "Problemi nella creazione del branch"
git mv BASEMODULE lib$LOWER 
if_error "Problemi nel rinominare la directory BASEMODULE"

sed -i.bak -e "s/BASEMODULE/$UPPER/g" -e "s/basemodule/$LOWER/g" ./lib$LOWER/BASEMODULE.*
sed -i.bak -e "s/BASEMODULE/$UPPER/g" -e "s/basemodule/$LOWER/g" ./lib$LOWER/CMakeLists.txt

git mv lib$LOWER/BASEMODULE.c lib$LOWER/$LOWER.c
git mv lib$LOWER/BASEMODULE.h lib$LOWER/$LOWER.h

rm lib$LOWER/*.bak

git add .
git commit -a -m "$UPPER module init"
git push origin $LOWER:$LOWER