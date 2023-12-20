#!/bin/bash
mensajeError() {
    printf "\nParámetros incorrectos.\n" 1>&2;
    printf "Ejecuciones correctas:\n" 1>&2;
    printf "\t ./ejecutar3.sh prueba\n" 1>&2;
    printf "\t ./ejecutar3.sh pruebas_intensivas\n" 1>&2;
    printf "\t ./ejecutar3.sh clean\n\n" 1>&2;
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
    if [ "$1" != "$OPCION_CLEAN" ] && [ "$1" != "$OPCION_PRUEBAS_INTENSIVAS" ] && [ "$1" != "$OPCION_PRUEBA" ]; then
        mensajeError
    fi
else
    mensajeError
fi


RUTA=$(pwd)/$(dirname "$0")
cd "$RUTA"

if [ "$1" == "$OPCION_PRUEBA" ]; then

    DIR_ENTRADA=entradas_pruebas
    DIR_SALIDA=salida_pruebas

    if [ ! -d "$DIR_ENTRADA" ]; then
        echo "No existe el directorio que almacena las entradas de las pruebas."
        exit 1
    fi

    if [ ! -d "$DIR_SALIDA" ]; then
        mkdir "$DIR_SALIDA"
    fi


    compilar

    ./bin/prueba "$DIR_ENTRADA/prueba2.txt" 1000 100


elif [ "$1" == "$OPCION_PRUEBAS_INTENSIVAS" ]; then

    compilar

    DIR_ENTRADA=entradas_pruebas
    DIR_SALIDA=salida_pruebas


    if [ ! -d "$DIR_ENTRADA" ]; then
        echo "No existe el directorio que almacena las entradas de las pruebas."
        exit 1
    fi
    

    if [ ! -d "$DIR_SALIDA" ]; then
        mkdir "$DIR_SALIDA"
    fi

    simulaciones=(100 1000 10000)
    limitesTiempo=(500 500 500 500 500)
    pruebas=("prueba1_1.txt" "prueba1_2.txt" "prueba1_3.txt" "prueba1_4.txt" "prueba1_5.txt")

    size=${#pruebas[@]}
    sims=${#simulaciones[@]}
    
    for ((i = 0; i < size; i++)); do
        if [ -f "$DIR_ENTRADA/${pruebas[i]}" ]; then
            echo "" > "$DIR_SALIDA/salida_${pruebas[i]}"
            for ((s = 0; s < sims; s++)) do
                echo -e "Prueba con ${simulaciones[s]} simulaciones\n" >> "$DIR_SALIDA/salida_${pruebas[i]}"
                ./bin/prueba "$DIR_ENTRADA/${pruebas[i]}" "${simulaciones[s]}" "${limitesTiempo[i]}" >> "$DIR_SALIDA/salida_${pruebas[i]}"
                echo -e "\n----------------------------------------------------------\n" >> "$DIR_SALIDA/salida_${pruebas[i]}"
            done
        else
            echo "El fichero ${pruebas[i]} del directorio $DIR_ENTRADA no existe o no es un fichero regular."
        fi
    done

elif [ "$1" == "$OPCION_CLEAN" ]; then

    DIR_SALIDA=salida_pruebas

    if [ -d "$DIR_BUILD" ]; then
        rm -r "$DIR_BUILD"
    fi

    if [ -d "$DIR_BIN" ]; then
        rm -r "$DIR_BIN"
    fi

    if [ -d "$DIR_SALIDA" ]; then
        rm -r "$DIR_SALIDA"
    fi

fi