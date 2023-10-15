#*****************************************************************
# Fichero: 	Makefile
# Autores: 	Diego García Aranda 820506ç
#			Simón Alonso Gutiérrez 821038
# Fecha entrega:	18/10/2023
# Coms:   Makefile para la práctica 1 de Algoritmia para Problemas Difíciles
#		  "make pruebas" construye el ejecutable para las pruebas automáticas
#		  "make clean" destruye archivos .o y ejecutables
#*****************************************************************

#---------------------------------------------------------
CODIGO_DIR=codigo
BUILD_DIR=build
BIN_DIR=bin

QUICKSORT=quicksort
RADIXSORT=radixsort
MERGESORT=mergesort

PRUEBAS=pruebaAlgoritmos

CC=g++

CPPFLAGS=-std=c++11 # Flags compilacion

MKDIR=mkdir
RM=rm

CHECK_BUILD_DIR=checkdirectoriobuild
CHECK_BIN_DIR=checkdirectoriobin

#----------------------------------------------------------------------------
# QUICKSORT
# Compilacion
${QUICKSORT}.o: ${CODIGO_DIR}/${QUICKSORT}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${QUICKSORT}.cpp -o ${BUILD_DIR}/${QUICKSORT}.o
#----------------------------------------------------------------------------
# RADIXSORT
# Compilacion
${RADIXSORT}.o: ${CODIGO_DIR}/${RADIXSORT}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${RADIXSORT}.cpp -o ${BUILD_DIR}/${RADIXSORT}.o
#----------------------------------------------------------------------------
#----------------------------------------------------------------------------
# MERGESORT
# Compilacion
${MERGESORT}.o: ${CODIGO_DIR}/${MERGESORT}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${MERGESORT}.cpp -o ${BUILD_DIR}/${MERGESORT}.o
#----------------------------------------------------------------------------
#-----------------------------------------------------------
# PRUEBAS
# Compilacion
${PRUEBAS}.o: ${CODIGO_DIR}/${PRUEBAS}.cpp
	${CC} -c ${CPPFLAGS} ${CODIGO_DIR}/${PRUEBAS}.cpp -o ${BUILD_DIR}/${PRUEBAS}.o
# Linkado
${PRUEBAS}: ${CHECK_BUILD_DIR} ${CHECK_BIN_DIR} ${PRUEBAS}.o ${QUICKSORT}.o ${MERGESORT}.o ${RADIXSORT}.o 
	${CC} ${BUILD_DIR}/${QUICKSORT}.o ${BUILD_DIR}/${MERGESORT}.o ${BUILD_DIR}/${RADIXSORT}.o ${BUILD_DIR}/${PRUEBAS}.o -o ${BIN_DIR}/${PRUEBAS}
#-----------------------------------------------------------
# LIMPIEZA
clean:
	if [ ! -d $(BUILD_DIR) ]; then \
    	$(RM) -r $(BUILD_DIR); \
    fi
	if [ ! -d $(BIN_DIR) ]; then \
        $(RM) -r $(BIN_DIR); \
    fi
#-----------------------------------------------------------
# VERIFICAR EXISTENCIA DIRECTORIOS
${CHECK_BUILD_DIR}:
	if [ ! -d $(BUILD_DIR) ]; then \
        mkdir -p $(BUILD_DIR); \
    fi

${CHECK_BIN_DIR}:
	if [ ! -d $(BIN_DIR) ]; then \
        mkdir -p $(BIN_DIR); \
    fi
