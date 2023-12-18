#!/bin/bash
mensajeError() {
    printf "\nParámetros incorrectos.\n" 1>&2;
    printf "Ejecuciones correctas:\n" 1>&2;
    printf "\t ./ejecutar2.sh prueba <dimensión cuadrado latino> <porcentaje celdas a rellenar>\n\t\tsiendo <porcentaje celdas a rellenar> un decimal entre 1 y 100\n" 1>&2;
    printf "\t ./ejecutar2.sh pruebas_intensivas\n" 1>&2;
    printf "\t ./ejecutar2.sh clean\n\n" 1>&2;
    exit 1;
}

DIR_BUILD=build
DIR_BIN=bin

compilar(){

    if [ ! -d "$DIR_BUILD" ]; then
        mkdir "$DIR_BUILD"
    fi

    if [ ! -d "$DIR_BIN" ]; then
        mkdir "$DIR_BIN"
    fi

    make pruebas
    
    if [ "$?" -ne 0 ]; then
        echo "Se ha producido un error al compilar"
        exit 1
    fi

}

OPCION_PRUEBA=prueba
OPCION_PRUEBAS_INTENSIVAS=pruebas_intensivas
OPCION_CLEAN=clean

if [ "$#" -eq 1 ]; then
    if [ "$1" != "$OPCION_CLEAN" ] && [ "$1" != "$OPCION_PRUEBAS_INTENSIVAS" ]; then
        mensajeError
    fi
elif [ "$#" -eq 3 ]; then
    if [ "$1" == "$OPCION_PRUEBA" ]; then
        if ! [[ "$2" =~ ^[0-9]+$ ]] || ! [[ "$3" =~ ^[0-9]+$ ]] || [ "$3" -le 1 ] || [ "$2" -gt 100 ]; then
            mensajeError
        fi
    else
        mensajeError
    fi
else
    mensajeError
fi


RUTA=$(pwd)/$(dirname "$0")
cd "$RUTA"

if [ "$1" == "$OPCION_PRUEBA" ]; then

    compilar

    DIR_ENTRADA=entrada_pruebas
    DIR_SALIDA=salida_pruebas

    if [ ! -d "$DIR_SALIDA" ]; then
        mkdir "$DIR_SALIDA"
    fi


elif [ "$1" == "$OPCION_PRUEBAS_INTENSIVAS" ]; then

    compilar

    DIR_ENTRADA=entrada_pruebas
    DIR_SALIDA=salida_pruebas


    if [ ! -d "$DIR_ENTRADA" ]; then
        
    fi
    

    if [ ! -d "$DIR_SALIDA" ]; then
        mkdir "$DIR_SALIDA"
    fi




elif [ "$1" == "$OPCION_CLEAN" ]; then

    DIR_EN_PRUEBAS_INTENSIVAS=entrada_pruebas_intensivas
    DIR_SAL_PRUEBAS_INTENSIVAS=salida_pruebas_intensivas

    if [ -d "$DIR_BUILD" ]; then
        rm -r "$DIR_BUILD"
    fi

    if [ -d "$DIR_BIN" ]; then
        rm -r "$DIR_BIN"
    fi

    if [ -d "$DIR_EN_PRUEBAS_INTENSIVAS" ]; then
        rm -r "$DIR_EN_PRUEBAS_INTENSIVAS"
    fi

    if [ -d "$DIR_SAL_PRUEBAS_INTENSIVAS" ]; then
        rm -r "$DIR_SAL_PRUEBAS_INTENSIVAS"
    fi

fi