#!/bin/bash
mensajeError() {
    printf "\nNúmero incorrecto de parámetros.\n" 1>&2;
    printf "Ejecuciones correctas:\n" 1>&2;
    printf "\t ./ejecutar2.sh pruebas <dimensión cuadrado latino> \n" 1>&2;
    printf "\t ./ejecutar2.sh pruebas_intensivas\n" 1>&2;
    printf "\t ./ejecutar2.sh clean\n\n" 1>&2;
    exit 1;
}

DIR_BUILD=build

compilar(){

    if [ ! -d "$DIR_BUILD" ]; then
        mkdir "$DIR_BUILD"
    fi

    cd "$DIR_BUILD"
    cmake ..

    make 
    
    if [ "$?" -ne 0 ]; then
        echo "Se ha producido un error al compilar"
        exit 1
    fi

}

OPCION_PRUEBA=prueba
OPCION_PRUEBAS_INTENSIVAS=pruebas_intensivas
OPCION_CLEAN=clean

if [ "$#" -eq 1 ]; then
    if [ "$1" != "pruebas" ] && [ "$1" != "pruebas_intensivas" ] && [ "$1" != "generar_datos_sinteticos" ]; then
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

if [ "$1" == "$OPCION_PRUEBA" ]; then

    




elif [ "$1" == "$OPCION_PRUEBAS_INTENSIVAS" ]; then

    if [ ]

    DIR_PRUEBAS_INTENSIVAS=entrada_pruebas_intensivas
    NINI=5
    MAX_DIMENSION=100
    PORCS=(10 20 30 40 50 100)


    if [ ! -d "$DIR_PRUEBAS_INTENSIVAS" ]; then
        mkdir "$DIR_PRUEBAS_INTENSIVAS"
        for ((numero = INC; numero <= MAX_DIMENSION; numero++))
        do
            for porcentaje in "${PORCS[@]}"
            do 
                ficheroSalida="CL_parcial_${numero}_${porcentaje}.txt"
                ./build/main "generarCL" "$DIR_PRUEBAS_INTENSIVAS/$ficheroSalida" "$numero" "$porcentaje"
            done

        done

    fi

    

elif [ "$1" == "$OPCION_CLEAN" ]; then


fi