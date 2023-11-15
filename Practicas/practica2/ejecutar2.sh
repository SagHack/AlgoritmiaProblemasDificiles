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
    
    cd ..


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

    DIR_RESUELTO=CL_resueltos
    DIR_ENTRADA=CL_parciales

    if [ ! -d "$DIR_ENTRADA" ]; then
        mkdir "$DIR_ENTRADA"
    fi

    if [ ! -d "$DIR_RESUELTO" ]; then
        mkdir "$DIR_RESUELTO"
    fi

    fS1="${DIR_ENTRADA}/CL_parcial_${2}_${3}.txt"
    fS2="${DIR_RESUELTO}/CL_resuelto_SAT_${2}_${3}.txt"
    fS3="${DIR_RESUELTO}/CL_resuelto_SAT_simp_${2}_${3}.txt"
    fS4="${DIR_RESUELTO}/CL_resuelto_Backtracking_${2}_${3}.txt"

    ./build/main "generarCL" "$fS1" "$2" "$3"
    ./build/main "resolverCL_SAT" "$fS1" "$fS2" "$2"
    ./build/main "resolverCL_simplificado_SAT" "$fS1" "$fS3" "$2"
    ./build/main "resolverCL_Backtracking" "$fS1" "$fS4" "$2"


elif [ "$1" == "$OPCION_PRUEBAS_INTENSIVAS" ]; then

    compilar

    DIR_EN_PRUEBAS_INTENSIVAS=entrada_pruebas_intensivas
    DIR_SAL_PRUEBAS_INTENSIVAS=salida_pruebas_intensivas
    DIR_RESUL_PRUEBAS_INTENSIVAS=resultados_pruebas_intensivas
    NINI=5
    MAX_DIMENSION=100
    PORCS=(10 20 30 40 50 100)


    if [ ! -d "$DIR_EN_PRUEBAS_INTENSIVAS" ]; then
        mkdir "$DIR_EN_PRUEBAS_INTENSIVAS"
        for ((numero = NINI; numero <= MAX_DIMENSION; numero+=NINI))
        do
            for porcentaje in "${PORCS[@]}"
            do 
                ficheroSalida="CL_parcial_${numero}_${porcentaje}.txt"
                ./build/main "generarCL" "$DIR_EN_PRUEBAS_INTENSIVAS/$ficheroSalida" "$numero" "$porcentaje"
            done

        done
    fi

    if [ ! -d "$DIR_SAL_PRUEBAS_INTENSIVAS" ]; then
        mkdir "$DIR_SAL_PRUEBAS_INTENSIVAS"
    fi

    if [ ! -d "$DIR_RESUL_PRUEBAS_INTENSIVAS" ]; then
        mkdir "$DIR_RESUL_PRUEBAS_INTENSIVAS"
    fi

    for ((numero = NINI; numero <= MAX_DIMENSION; numero+=NINI))
    do
        for porcentaje in "${PORCS[@]}"
        do 
            ficheroEntrada="CL_parcial_${numero}_${porcentaje}.txt"
            ficheroSalida1="CL_resuelto_SAT_${numero}_${porcentaje}.txt"
            ficheroSalida2="CL_resuelto_simplifcado_SAT${numero}_${porcentaje}.txt"
            ficheroSalida3="CL_resuelto_Backtracking${numero}_${porcentaje}.txt"
            ficheroResultados="resultados_${numero}_${porcentaje}.txt"

            if [ -e "$DIR_EN_PRUEBAS_INTENSIVAS/$ficheroEntrada" ]; then
                ./build/main "resolverCL_comparacion" "$DIR_EN_PRUEBAS_INTENSIVAS/$ficheroEntrada" "$DIR_SAL_PRUEBAS_INTENSIVAS/$ficheroSalida1" "$DIR_SAL_PRUEBAS_INTENSIVAS/$ficheroSalida2" "$DIR_SAL_PRUEBAS_INTENSIVAS/$ficheroSalida3" "$numero" > "$DIR_RESUL_PRUEBAS_INTENSIVAS/$ficheroResultados"
            fi
            done

    done


elif [ "$1" == "$OPCION_CLEAN" ]; then

    DIR_EN_PRUEBAS_INTENSIVAS=entrada_pruebas_intensivas
    DIR_SAL_PRUEBAS_INTENSIVAS=salida_pruebas_intensivas
    DIR_RESUL_PRUEBAS_INTENSIVAS=resultados_pruebas_intensivas
    DIR_RESUELTO=CL_resueltos
    DIR_PARCIALES=CL_parciales

    if [ -d "$DIR_BUILD" ]; then
        rm -r "$DIR_BUILD"
    fi

    if [ -d "$DIR_EN_PRUEBAS_INTENSIVAS" ]; then
        rm -r "$DIR_EN_PRUEBAS_INTENSIVAS"
    fi

    if [ -d "$DIR_SAL_PRUEBAS_INTENSIVAS" ]; then
        rm -r "$DIR_SAL_PRUEBAS_INTENSIVAS"
    fi

    if [ -d "$DIR_RESUL_PRUEBAS_INTENSIVAS" ]; then
        rm -r "$DIR_RESUL_PRUEBAS_INTENSIVAS"
    fi

    if [ -d "$DIR_RESUELTO" ]; then
        rm -r "$DIR_RESUELTO"
    fi

    if [ -d "$DIR_PARCIALES" ]; then
        rm -r "$DIR_PARCIALES"
    fi

    
    

fi