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

./gCL "CL.txt" "$n" "$p"

if [ "$?" -ne 0 ]; then
    exit 1
fi

./main "CL.txt" "$n"

if [ "$?" -ne 0 ]; then
    exit 1
fi

if [ "$1" == "$OPCION_PRUEBA" ]; then






elif [ "$1" == "$OPCION_PRUEBAS_INTENSIVAS" ]; then


    for ((numero = 5; numero <= MAX_DIMENSION; numero++))
    do

    

    done

elif [ "$1" == "$OPCION_CLEAN" ]; then


fi


./minisat-master/build/minisat "clauses.txt" "resultado.txt"
./mostrarResultado "$n"