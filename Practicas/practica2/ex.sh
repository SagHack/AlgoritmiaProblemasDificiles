#!/bin/bash

num_ejecuciones=10
archivo_resultados="resultados.txt"

# Bucle para variar la dimensión
for dimension in {5..100..5}; do
    # Bucle para variar el porcentaje
    for porcentaje in {0,10,20,30,40,50,60,70,80,90,100}; do
        echo "Dimensión: $dimension, Porcentaje: $porcentaje%" >> "$archivo_resultados"
        
        # Bucle para ejecutar los comandos múltiples veces
        for ((i=1; i<=$num_ejecuciones; i++)); do
            echo "Ejecución $i:" >> "$archivo_resultados"
            
            # Ejecutar los comandos y redirigir la salida al archivo
            ./build/main generarCL "ficheros/fichero_salida_CL_parcial_$dimension_$porcentaje%" "$dimension" "$porcentaje" >> "$archivo_resultados"
            # ./main resolverCL_SAT <fichero_entrada_CL_parcial> <fichero_salida_CL_resuelto> "$dimension" >> "$archivo_resultados"
            # Añadir aquí los demás comandos con la dimensión y porcentaje correspondientes

            echo -e "\n" >> "$archivo_resultados"
        done

        echo -e "\n" >> "$archivo_resultados"
    done
done

echo "Todas las ejecuciones han sido completadas. Los resultados se encuentran en $archivo_resultados"
