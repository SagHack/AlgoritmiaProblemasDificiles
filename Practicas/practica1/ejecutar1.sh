#!/bin/bash
mensajeError() {
    printf "\nNúmero incorrecto de parámetros.\n" 1>&2;
    printf "Ejecuciones correctas:\n" 1>&2;
    printf "\t ./ejecutar1.sh pruebas\n" 1>&2;
    printf "\t ./ejecutar1.sh pruebas <num_prueba> siendo num_prueba un número entre 1 y $CASOS_PRUEBA\n" 1>&2;
    printf "\t ./ejecutar1.sh generar_datos_sinteticos <num_caso_datos_sinteticos> siendo num_caso_datos_sinteticos un número entre 1 y $CASOS_SINTETICOS\n" 1>&2;
    printf "\t ./ejecutar1.sh clean\n" 1>&2;
    exit 1;
}

CASOS_PRUEBA=7
CASOS_SINTETICOS=6

if [ "$#" -eq 1 ]; then
    if [ "$1" != "pruebas" ] && [ "$1" != "clean" ] && [ "$1" != "generar_datos_sinteticos" ]; then
        mensajeError
    fi
elif [ "$#" -eq 2 ]; then
    if [ "$1" != "pruebas" ]; then
        mensajeError
    elif [ "$2" -le 0 ] || [ "$2" -ge "$CASOS_PRUEBA" ]; then
        mensajeError
    fi
else
    mensajeError
fi

RUTA=$(pwd)/$(dirname "$0")
cd "$RUTA"

if [ "$1" == "pruebas" ]; then
    if [ ! -d "build" ]; then
        mkdir "build"
    fi
    if [ ! -d "bin" ]; then
        mkdir "bin"
    fi

    make pruebas

    if [ "$#" -eq 2 ]; then

    else
        ./pruebas "$2" 
    fi


elif [ "$1" == "clean" ]; then

    if [ -d "build" ]; then
        rm -r "build"
    fi
    if [ -d "bin" ]; then
        rm -r "bin"
    fi





elif [ "$1" == "generar_datos_sinteticos" ]; then

    if [ ! -d "build" ]; then
        mkdir "build"
    fi
    if [ ! -d "bin" ]; then
        mkdir "bin"
    fi

    make datosSinteticos
    
    if [ ! -d "ficherosEntradaPruebas" ]; then
        mkdir "ficherosEntradaPruebas"
    fi
    
    cd 
    if [ "$#" -eq 2 ]; then

    else
        /pruebas "$2" 
    fi

fi
    






