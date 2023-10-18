#!/bin/bash

mensajeError() {
    printf "\nNúmero incorrecto de parámetros.\n" 1>&2;
    printf "Ejecuciones correctas:\n" 1>&2;
    printf "\t ./ejecutar1.sh pruebas\n" 1>&2;
    printf "\t ./ejecutar1.sh pruebas <num_prueba> siendo num_prueba un número entre 1 y $CASOS_PRUEBA\n" 1>&2;
    printf "\t ./ejecutar1.sh generar_datos_sinteticos\n" 1>&2;
    printf "\t ./ejecutar1.sh generar_datos_sinteticos <num_caso_datos_sinteticos> siendo num_caso_datos_sinteticos un número entre 1 y $CASOS_SINTETICOS\n" 1>&2;
    printf "\t ./ejecutar1.sh clean\n\n" 1>&2;
    exit 1;
}

CASOS_PRUEBA=7
CASOS_SINTETICOS=6
DIR_DATOS="ficherosEntradaPruebas"
DIR_DATOS_INTENSIVAS="ficherosEntradaPruebasIntensivas"

if [ "$#" -eq 1 ]; then
    if [ "$1" != "pruebas" ] && [ "$1" != "clean" ] && [ "$1" != "generar_datos_sinteticos" ]; then
        mensajeError
    fi
elif [ "$#" -eq 2 ]; then
    if [ "$1" == "pruebas" ]; then
        if [ "$2" -le 0 ] || [ "$2" -gt "$CASOS_PRUEBA" ]; then
            mensajeError
        fi
    elif [ "$1" == "generar_datos_sinteticos" ]; then
        if [ "$2" -le 0 ] || [ "$2" -gt "$CASOS_SINTETICOS" ]; then
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

if [ "$1" == "pruebas" ]; then
    if [ ! -d "build" ]; then
        mkdir "build"
    fi
    if [ ! -d "bin" ]; then
        mkdir "bin"
    fi

    make pruebas

    if [ "$?" -ne 0 ]; then
        exit 1;
    fi
    
    if [ ! -d "$DIR_DATOS" ]; then
        echo "Error: no existe el directorio $DIR_DATOS_"
        exit 1
    fi

    cd "$DIR_DATOS"

    if [ "$#" -ne 2 ]; then
        for ((numero = 1; numero <= CASOS_PRUEBA; numero++))
        do
            ./../bin/pruebas "$numero"
            if [ "$?" -eq 0 ]; then
                echo "Se ha realizado el caso $numero de pruebas correctamente"
            fi
        done 
    else
        ./../bin/pruebas "$2" 
        if [ "$?" -eq 0 ]; then
            echo "Se ha realizado el caso $2 de pruebas correctamente"
        fi
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
    if [ "$?" -ne 0 ]; then
        exit 1;
    fi

    if [ ! -d "$DIR_DATOS_INTENSIVAS" ]; then
        mkdir "$DIR_DATOS_INTENSIAS"
    fi
        
    cd "$DIR_DATOS_INTENSIVAS"
    if [ "$#" -eq 2 ]; then 
        ./../bin/generarDatosSinteticos "$2"
        if [ "$?" -eq 0 ]; then
            echo "Se han generado los ficheros del caso $2 de pruebas intensivas correctamente"
        fi
    else 
        for ((numero = 1; numero <= CASOS_SINTETICOS; numero++))
        do
            ./../bin/generarDatosSinteticos "$numero"
            if [ "$?" -eq 0 ]; then
                echo "Se han generado los ficheros del caso $numero de pruebas intensivas correctamente"
            fi
        done
    fi 

fi
    






